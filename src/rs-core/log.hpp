#pragma once

#include <algorithm>
#include <cerrno>
#include <chrono>
#include <concepts>
#include <condition_variable>
#include <cstdint>
#include <cstdio>
#include <deque>
#include <exception>
#include <filesystem>
#include <format>
#include <functional>
#include <mutex>
#include <random>
#include <source_location>
#include <string>
#include <string_view>
#include <system_error>
#include <thread>
#include <type_traits>

#ifdef _WIN32

    extern "C" {
        _declspec(dllimport) int __stdcall GetConsoleMode(void* hConsoleHandle, unsigned long* lpMode);
        _declspec(dllimport) unsigned long __stdcall GetCurrentProcessId();
        _declspec(dllimport) unsigned long __stdcall GetCurrentThreadId();
        _declspec(dllimport) void* __stdcall GetStdHandle(unsigned long nStdHandle);
    }

#else

    #include <pthread.h>
    #include <unistd.h>

    static_assert(std::is_pointer_v<pthread_t>  // Apple
        || std::unsigned_integral<pthread_t>);  // Linux

#endif

namespace RS {

    enum class LogFlags: std::uint32_t {
        none      = 0,
        // Context flags
        all       = 0x0000'ffff,
        date      = 0x0000'0001,
        time      = 0x0000'0002,
        process   = 0x0000'0004,
        thread    = 0x0000'0008,
        path      = 0x0000'0010,
        file      = 0x0000'0020,
        pretty    = 0x0000'0040,
        function  = 0x0000'0080,
        line      = 0x0000'0100,
        // Other flags
        append    = 0x0001'0000,
        colour    = 0x0002'0000,
        quiet     = 0x0004'0000,
    };

    constexpr LogFlags operator|(LogFlags a, LogFlags b) noexcept {
        using U = std::underlying_type_t<LogFlags>;
        return static_cast<LogFlags>(static_cast<U>(a) | static_cast<U>(b));
    }

    constexpr LogFlags operator&(LogFlags a, LogFlags b) noexcept {
        using U = std::underlying_type_t<LogFlags>;
        return static_cast<LogFlags>(static_cast<U>(a) & static_cast<U>(b));
    }

    class Log {

    public:

        using enum LogFlags;

        static constexpr auto defaults = file | line | colour;

        struct message {
            std::function<std::string()> get_message;
            template <typename... Args> message(std::format_string<const Args&...> fmt, const Args&... args):
                get_message{[=] { return std::format(fmt, args...); }} {}
        };

        Log(): out_{stderr} {}
        explicit Log(const std::filesystem::path& path, LogFlags flags = defaults);
        explicit Log(std::FILE* out, LogFlags flags = defaults);
        ~Log() noexcept;

        Log(const Log&) = delete;
        Log(Log&&) = delete;
        Log& operator=(const Log&) = delete;
        Log& operator=(Log&&) = delete;

        void enable(bool state);
        void operator()(const message& msg, const std::source_location loc = std::source_location::current());

    private:

        using clock = std::chrono::system_clock;

        #ifdef _WIN32

            using process_id = unsigned long;
            using thread_id = unsigned long;

            static constexpr const char* path_delimiters = "/\\";

        #else

            using process_id = pid_t;
            using thread_id = std::conditional_t<std::integral<pthread_t>, pthread_t, std::uintptr_t>;

            static constexpr const char* path_delimiters = "/";

        #endif

        struct log_entry {

            std::source_location where;
            message what;
            clock::time_point when;
            process_id process;
            thread_id thread;

            log_entry(std::source_location loc, const message& msg):
                where{loc},
                what{msg},
                when{clock::now()},
                process{get_current_process()},
                thread{get_current_thread()} {}

        };

        std::deque<log_entry> queue_;
        std::mutex mutex_;
        std::condition_variable cv_;
        std::jthread thread_;
        std::filesystem::path path_;
        std::FILE* out_ {nullptr};
        LogFlags flags_ {defaults};
        bool stop_request_ {false};

        void add_context(const log_entry& entry, std::string& text) const;
        void payload() noexcept;

        static std::string_view file_leaf_name(std::string_view path);
        static std::string_view function_leaf_name(std::string_view pretty);
        static process_id get_current_process();
        static thread_id get_current_thread();
        static std::string make_prefix();
        static bool xterm_is_tty(std::FILE* fp) noexcept;
        static const char* xterm_reset() noexcept { return "\x1b[0m"; }
        static std::string xterm_rgb(int r, int g, int b);

    };

        inline Log::Log(const std::filesystem::path& path, LogFlags flags):
        path_{path},
        flags_{flags} {
            enable((flags_ & quiet) == none);
        }

        inline Log::Log(std::FILE* out, LogFlags flags):
        out_{out},
        flags_{flags} {
            enable((flags_ & quiet) == none);
        }

        inline Log::~Log() noexcept {

            if (thread_.joinable()) {

                {
                    std::unique_lock lock {mutex_};
                    stop_request_ = true;
                    cv_.notify_one();
                }

                thread_.join();

            }

            if (! path_.empty() && out_ != nullptr) {
                std::fclose(out_);
            }

        }

        inline void Log::enable(bool state) {

            {

                std::unique_lock lock {mutex_};
                auto running = thread_.joinable();

                if (state == running) {
                    return;
                }

                stop_request_ = ! state;

                if (state) {

                    if (! path_.empty() && out_ == nullptr) {

                        const char* mode = (flags_ & append) == none ? "wb" : "ab";
                        errno = 0;
                        out_ = std::fopen(path_.c_str(), mode);
                        int err = errno;

                        if (out_ == nullptr) {
                            throw std::system_error(std::error_code(err, std::system_category()), path_.string());
                        }

                    }

                    thread_ = std::jthread{&Log::payload, this};

                }

            }

            if (! state) {
                cv_.notify_one();
                thread_.join();
            }

        }

        inline void Log::operator()(const message& msg, const std::source_location loc) {
            if (thread_.joinable()) {
                std::unique_lock lock {mutex_};
                queue_.push_back(log_entry{loc, msg});
                cv_.notify_one();
            }
        }

        inline void Log::add_context(const log_entry& entry, std::string& text) const {

            if ((flags_ & all) == none) {
                return;
            }

            auto field = [this,&text] <typename T> (LogFlags mask, std::format_string<const T&> fmt, const T& t) {
                if ((flags_ & mask) == none) {
                    return false;
                }
                text += std::format(fmt, t);
                text += ':';
                return true;
            };

            text += '[';

            field(date, "{0:%Y}{0:%m}{0:%d}-{0:%H}{0:%M}{0:%S}", entry.when)
                || field(time, "{0:%H}{0:%M}{0:%S}", entry.when);
            field(process, "P{:x}", entry.process);
            field(thread, "T{:x}", entry.thread);
            field(path, "{}", entry.where.file_name())
                || field(file, "{}", file_leaf_name(entry.where.file_name()));
            field(pretty, "{}", entry.where.function_name())
                || field(function, "{}", function_leaf_name(entry.where.function_name()));
            field(line, "{}", entry.where.line());

            text.pop_back();
            text += "] ";

        }

        inline void Log::payload() noexcept {

            try {

                std::string prefix, suffix;

                if ((flags_ & colour) != none && xterm_is_tty(out_))  {
                    prefix = make_prefix();
                    suffix = xterm_reset();
                }

                std::unique_lock lock {mutex_};

                while (! stop_request_ || ! queue_.empty()) {

                    cv_.wait(lock, [this] { return stop_request_ || ! queue_.empty(); });

                    if (stop_request_ && queue_.empty()) {
                        break;
                    }

                    auto text{prefix};
                    add_context(queue_.front(), text);
                    text += queue_.front().what.get_message();
                    text += suffix;
                    text += '\n';
                    std::fputs(text.data(), out_);
                    std::fflush(out_);
                    queue_.pop_front();

                }

                queue_.clear();

            }

            catch (const std::exception& ex) {
                std::fputs("Exception while logging\n", stderr);
                std::fputs(ex.what(), stderr);
                std::fputs("\n", stderr);
            }

            catch (...) {
                std::fputs("Unknown exception while logging", stderr);
            }

        }

        inline std::string_view Log::file_leaf_name(std::string_view path) {
            auto last_delimiter = path.find_last_of(path_delimiters);
            return path.substr(last_delimiter + 1);
        }

        inline std::string_view Log::function_leaf_name(std::string_view pretty) {

            if (pretty.empty()) {
                return {};
            }

            static constexpr std::string_view anon_text = "anonymous namespace";

            auto anon_pos = pretty.find(anon_text);

            if (anon_pos != std::string::npos) {
                pretty = pretty.substr(anon_pos + anon_text.size() + 1);
            }

            static const auto name_char = [] (char c) {
                return (c >= '0' && c <= '9')
                    || (c >= 'A' && c <= 'Z')
                    || (c >= 'a' && c <= 'z')
                    || c == '_'
                    || static_cast<unsigned char>(c) >= 0x80;
            };

            auto end_name = pretty.find('(');

            if (end_name == 0 || end_name == std::string::npos) {
                return pretty;
            }

            if (pretty[end_name - 1] == '>') {
                auto depth = 0;
                do {
                    --end_name;
                    if (pretty[end_name] == '<') {
                        --depth;
                    } else if (pretty[end_name] == '>') {
                        ++depth;
                    }
                } while (end_name != 0 && depth > 0);
                if (end_name == 0) {
                    return pretty;
                }
            }

            auto begin_name = end_name;

            while (begin_name > 0 && name_char(pretty[begin_name - 1])) {
                --begin_name;
            }

            return pretty.substr(begin_name, end_name - begin_name);

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

        inline std::string Log::make_prefix() {

            auto id = static_cast<std::uint64_t>(get_current_thread());
            auto seed = static_cast<std::uint32_t>((id >> 32) | id);
            std::minstd_rand rng {seed};
            std::uniform_int_distribution<int> random_channel {0, 5};
            int r, g, b;

            do {
                r = random_channel(rng);
                g = random_channel(rng);
                b = random_channel(rng);
            } while (r + g + b < 1 || r + g + b > 14);

            return xterm_rgb(r, g, b);

        }

        inline bool Log::xterm_is_tty(std::FILE* fp) noexcept {

            int fd;

            if (fp == stdin) {
                fd = 0;
            } else if (fp == stdout) {
                fd = 1;
            } else if (fp == stderr) {
                fd = 2;
            } else {
                return false;
            }

            #ifdef _WIN32

                auto handle_num = static_cast<unsigned long>(-10 - fd);
                auto handle = GetStdHandle(handle_num);
                auto mode = 0ul;

                return GetConsoleMode(handle, &mode) != 0;

            #else

                return ::isatty(fd) != 0;

            #endif

        }

        inline std::string Log::xterm_rgb(int r, int g, int b) {
            r = std::clamp(r, 0, 5);
            g = std::clamp(g, 0, 5);
            b = std::clamp(b, 0, 5);
            auto index = 36 * r + 6 * g + b + 16;
            return "\x1b[38;5;" + std::to_string(index) + "m";
        }

}
