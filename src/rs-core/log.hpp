#pragma once

#include "rs-core/arithmetic.hpp"
#include "rs-core/enum.hpp"
#include "rs-core/global.hpp"
#include "rs-core/io.hpp"
#include "rs-core/terminal.hpp"
#include <chrono>
#include <concepts>
#include <condition_variable>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <deque>
#include <filesystem>
#include <format>
#include <functional>
#include <mutex>
#include <source_location>
#include <string>
#include <string_view>
#include <thread>
#include <type_traits>

#ifdef _WIN32

    extern "C" {
        unsigned long GetCurrentProcessId();
        unsigned long GetCurrentThreadId();
    }

#else

    #include <pthread.h>
    #include <unistd.h>

    // If these fail some smarter code will be needed
    static_assert(std::integral<pid_t>);
    static_assert(std::is_pointer_v<pthread_t>);

#endif

namespace RS {

    RS_BITMASK(LogFlags, std::uint16_t,
        none      = 0,
        // Context flags
        all       = 0x0fff,
        date      = 0x0001,
        time      = 0x0002,
        process   = 0x0004,
        thread    = 0x0008,
        path      = 0x0010,
        file      = 0x0020,
        pretty    = 0x0040,
        function  = 0x0080,
        line      = 0x0100,
        column    = 0x0200,
        // Other flags
        enabled   = 0x1000,
    )

    class Log {

    public:

        using enum LogFlags;

        class message {
        public:
            template <typename... Args> message(std::format_string<const Args&...> fmt, const Args&... args):
                callback_([=] { return std::format(fmt, args...); }) {}
        private:
            friend class Log;
            std::function<std::string()> callback_;
        };

        static constexpr auto defaults = file | line;

        Log(): out_(stderr) {}
        explicit Log(const std::filesystem::path& path, LogFlags flags = defaults);
        explicit Log(std::FILE* out, LogFlags flags = defaults);
        ~Log() noexcept;

        Log(const Log&) = delete;
        Log(Log&&) = delete;
        Log& operator=(const Log&) = delete;
        Log& operator=(Log&&) = delete;

        void enable(bool flag = true);
        void operator()(const message& msg, const std::source_location loc = std::source_location::current());

    private:

        using clock = std::chrono::system_clock;

        #ifdef _WIN32
            using process_id = unsigned long;
            using thread_id = unsigned long;
        #else
            using process_id = pid_t;
            using thread_id = std::uintptr_t;
        #endif

        struct log_entry {
            std::source_location where;
            message what;
            clock::time_point when;
            process_id process;
            thread_id thread;
            log_entry(std::source_location loc, const message& msg):
                where(loc), what(msg), when(clock::now()),
                process(get_current_process()), thread(get_current_thread()) {}
        };

        std::deque<log_entry> queue_;
        std::mutex mutex_;
        std::condition_variable cv_;
        std::thread thread_;
        std::filesystem::path path_;
        Cstdio out_;
        LogFlags flags_{defaults};
        bool stop_request_{};

        std::string add_context(const log_entry& entry) const;
        void payload();

        static std::string file_leaf_name(std::string_view path);
        static std::string function_leaf_name(std::string_view pretty);
        static process_id get_current_process();
        static thread_id get_current_thread();

    };

        inline Log::Log(const std::filesystem::path& path, LogFlags flags):
        path_(path), flags_(flags) {
            enable(has_bit(flags_, enabled));
        }

        inline Log::Log(std::FILE* out, LogFlags flags):
        out_(out), flags_(flags) {
            enable(has_bit(flags_, enabled));
        }

        inline Log::~Log() noexcept {
            {
                auto lock = std::unique_lock{mutex_};
                stop_request_ = true;
                cv_.notify_one();
            }
            thread_.join();
        }

        inline void Log::payload() {

            auto lock = std::unique_lock{mutex_};

            while (! stop_request_ || ! queue_.empty()) {

                cv_.wait(lock, [this] { return stop_request_ || ! queue_.empty(); });

                if (stop_request_ && queue_.empty()) {
                    break;
                }

                auto text = add_context(queue_.front());
                text += queue_.front().what.callback_();
                text += '\n';
                out_.write(text);
                out_.flush();
                queue_.pop_front();

            }

            queue_.clear();
            out_.close();

        }

        inline void Log::enable(bool flag) {

            {

                auto lock = std::unique_lock{mutex_};
                auto running = thread_.joinable();

                if (flag == running) {
                    return;
                }

                stop_request_ = ! flag;

                if (flag) {
                    if (! path_.empty()) {
                        out_ = Cstdio{path_, "wb"};
                    }
                    thread_ = std::thread{&Log::payload, this};
                }

            }

            if (! flag) {
                cv_.notify_one();
                thread_.join();
                out_ = {};
            }

        }

        inline void Log::operator()(const message& msg, const std::source_location loc) {
            if (thread_.joinable()) {
                auto lock = std::unique_lock{mutex_};
                if (thread_.joinable()) {
                    queue_.push_back(log_entry{loc, msg});
                    cv_.notify_one();
                }
            }
        }

        inline std::string Log::add_context(const log_entry& entry) const {

            if (! has_bit(flags_, all)) {
                return {};
            }

            std::string text;

            auto field = [this,&text] <typename T> (LogFlags mask, std::format_string<const T&> fmt, const T& t) {
                if (! has_bit(flags_, mask)) {
                    return false;
                }
                text += std::format(fmt, t);
                return true;
            };

            field(date, ":{0:%Y}{0:%m}{0:%d}-{0:%H}{0:%M}{0:%S}", entry.when)
                || field(time, ":{0:%H}{0:%M}{0:%S}", entry.when);
            field(process, ":P{:x}", entry.process);
            field(thread, ":T{:x}", entry.thread);
            field(path, ":{}", entry.where.file_name())
                || field(file, ":{}", file_leaf_name(entry.where.file_name()));
            field(pretty, ":{}", entry.where.function_name())
                || field(function, ":{}", function_leaf_name(entry.where.function_name()));
            field(line | column, ":{}", entry.where.line());
            field(column, ":{}", entry.where.column());
            text[0] = '[';
            text += "] ";

            return text;

        }

        inline std::string Log::file_leaf_name(std::string_view path) {
            std::size_t last_delimiter;
            #ifdef _WIN32
                last_delimiter = path.find_last_of("/\\");
            #else
                last_delimiter = path.find_last_of('/');
            #endif
            return std::string(path, last_delimiter + 1, npos);
        }

        inline std::string Log::function_leaf_name(std::string_view pretty) {

            if (pretty.empty()) {
                return {};
            }

            static const auto name_char = [] (char c) {
                return ascii_isalnum(c) || c == '_' || static_cast<unsigned char>(c) >= 0x80;
            };

            auto paren_pos = 0uz;

            do {
                paren_pos = pretty.find('(', paren_pos + 1);
                if (paren_pos == npos) {
                    return std::string{pretty};
                }
            } while (! name_char(pretty[paren_pos - 1]));

            auto end_name = pretty.begin() + paren_pos;
            auto begin_name = end_name - 1;

            while (begin_name != pretty.begin() && name_char(begin_name[-1])) {
                --begin_name;
            }

            return std::string{begin_name, end_name};

        }

        inline Log::process_id Log::get_current_process() {
            #ifdef _WIN32
                return GetCurrentProcessId();
            #else
                return getpid();
            #endif
        }

        inline Log::thread_id Log::get_current_thread() {
            #ifdef _WIN32
                return GetCurrentThreadId();
            #else
                return reinterpret_cast<thread_id>(pthread_self());
            #endif
        }

}
