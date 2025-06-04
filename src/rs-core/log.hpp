#pragma once

#include "rs-core/arithmetic.hpp"
#include "rs-core/enum.hpp"
#include "rs-core/global.hpp"
#include "rs-core/io.hpp"
#include "rs-core/terminal.hpp"
#include <atomic>
#include <chrono>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <filesystem>
#include <format>
#include <functional>
#include <mutex>
#include <source_location>
#include <string>
#include <string_view>
#include <type_traits>

#ifdef _WIN32

    extern "C" {
        unsigned long GetCurrentProcessId();
        unsigned long GetCurrentThreadId();
    }

#else

    #include <pthread.h>
    #include <unistd.h>

    static_assert(std::integral<pid_t>);
    static_assert(std::is_pointer_v<pthread_t>);

#endif

namespace RS {

    RS_BITMASK(LogFlags, std::uint16_t,
        none      = 0,
        // Context flags
        all       = 0x0fff,
        time      = 0x0001,
        process   = 0x0002,
        thread    = 0x0004,
        path      = 0x0008,
        file      = 0x0010,
        pretty    = 0x0020,
        function  = 0x0040,
        line      = 0x0080,
        column    = 0x0100,
        // Other flags
        enabled   = 0x1000,
    )

    class Log {

    public:

        struct message;

        using enum LogFlags;

        static constexpr auto defaults = file | line;

        Log(): out_(stderr) {}
        explicit Log(std::FILE* out, LogFlags flags = defaults): out_(out), flags_(flags) { init(); }
        explicit Log(const std::filesystem::path& path, LogFlags flags = defaults): path_(path), flags_(flags) { init(); }
        ~Log() = default;

        Log(const Log&) = delete;
        Log(Log&&) = delete;
        Log& operator=(const Log&) = delete;
        Log& operator=(Log&&) = delete;

        void enable(bool flag = true);
        void operator()(const message& msg, const std::source_location loc = std::source_location::current());

    private:

        std::mutex mutex_;
        std::atomic<bool> enabled_{false};
        std::filesystem::path path_;
        Cstdio out_;
        LogFlags flags_{defaults};

        std::string context(const std::source_location location) const;
        void init() { enable(has_bit(flags_, enabled)); }

        static std::string file_leaf_name(std::string_view path);
        static std::string function_leaf_name(std::string_view pretty);

    };

        struct Log::message {
            std::function<std::string()> make;
            template <typename... Args> message(std::format_string<const Args&...> fmt, const Args&... args):
                make([=] { return std::format(fmt, args...); }) {}
        };

        inline void Log::enable(bool flag) {
            auto lock = std::unique_lock{mutex_};
            if (! path_.empty()) {
                if (flag && ! enabled_) {
                    out_ = Cstdio{path_, "wb"};
                } else if (! flag && enabled_) {
                    out_.close();
                }
            }
            enabled_ = flag;
        }

        inline void Log::operator()(const message& msg, const std::source_location loc) {
            if (enabled_) {
                auto lock = std::unique_lock{mutex_};
                if (enabled_) {
                    auto text = context(loc) + msg.make() + '\n';
                    out_.write(text);
                    out_.flush();
                }
            }
        }

        inline std::string Log::context(const std::source_location loc) const {

            using namespace std::chrono;

            if (! has_bit(flags_, all)) {
                return {};
            }

            std::string text;

            if (has_bit(flags_, time)) {
                text += std::format(":{0:%Y}{0:%m}{0:%d}-{0:%H}{0:%M}{0:%S}", system_clock::now());
            }

            if (has_bit(flags_, process)) {
                auto id =
                    #ifdef _WIN32
                        GetCurrentProcessId();
                    #else
                        getpid();
                    #endif
                text += std::format(":P{:x}", id);
            }

            if (has_bit(flags_, thread)) {
                auto id =
                    #ifdef _WIN32
                        GetCurrentThreadId();
                    #else
                        reinterpret_cast<std::uintptr_t>(pthread_self());
                    #endif
                text += std::format(":T{:x}", id);
            }

            if (has_bit(flags_, path)) {
                text += std::format(":{}", loc.file_name());
            } else if (has_bit(flags_, file)) {
                text += std::format(":{}", file_leaf_name(loc.file_name()));
            }

            if (has_bit(flags_, pretty)) {
                text += std::format(":{}", loc.function_name());
            } else if (has_bit(flags_, function)) {
                text += std::format(":{}", function_leaf_name(loc.function_name()));
            }

            if (has_bit(flags_, line | column)) {
                text += std::format(":{}", loc.line());
            }

            if (has_bit(flags_, column)) {
                text += std::format(":{}", loc.column());
            }

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

}
