#pragma once

#include "rs-core/arithmetic.hpp"
#include "rs-core/enum.hpp"
#include "rs-core/global.hpp"
#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <string_view>

#ifdef _WIN32

    extern "C" {
        void* __stdcall GetStdHandle(unsigned long nStdHandle);
        int __stdcall GetConsoleMode(void* hConsoleHandle, unsigned long* lpMode);
    }

#else

    #include <unistd.h>

#endif

namespace RS {

    RS_ENUM(XtermMode, int,
        unknown,
        light,
        dark,
    )

    class Xterm {

    public:

        using enum XtermMode;

        using colour = std::array<int, 3>;

        Xterm() noexcept: colour_(is_tty(stdout)) {}
        explicit Xterm(bool use_colour) noexcept: colour_(use_colour) {}

        bool is_colour() const noexcept { return colour_; }

        std::string_view reset() const noexcept       { return colour_ ? "\x1b[0m" : ""; }
        std::string_view bold() const noexcept        { return colour_ ? "\x1b[1m" : ""; }
        std::string_view under() const noexcept       { return colour_ ? "\x1b[4m" : ""; }
        std::string_view bold_off() const noexcept    { return colour_ ? "\x1b[22m" : ""; }
        std::string_view under_off() const noexcept   { return colour_ ? "\x1b[24m" : ""; }
        std::string_view colour_off() const noexcept  { return colour_ ? "\x1b[39m" : ""; }
        std::string_view black() const noexcept       { return colour_ ? "\x1b[30m" : ""; }
        std::string_view red() const noexcept         { return colour_ ? "\x1b[31m" : ""; }
        std::string_view green() const noexcept       { return colour_ ? "\x1b[32m" : ""; }
        std::string_view yellow() const noexcept      { return colour_ ? "\x1b[33m" : ""; }
        std::string_view blue() const noexcept        { return colour_ ? "\x1b[34m" : ""; }
        std::string_view magenta() const noexcept     { return colour_ ? "\x1b[35m" : ""; }
        std::string_view cyan() const noexcept        { return colour_ ? "\x1b[36m" : ""; }
        std::string_view white() const noexcept       { return colour_ ? "\x1b[37m" : ""; }
        std::string_view black_bg() const noexcept    { return colour_ ? "\x1b[40m" : ""; }
        std::string_view red_bg() const noexcept      { return colour_ ? "\x1b[41m" : ""; }
        std::string_view green_bg() const noexcept    { return colour_ ? "\x1b[42m" : ""; }
        std::string_view yellow_bg() const noexcept   { return colour_ ? "\x1b[43m" : ""; }
        std::string_view blue_bg() const noexcept     { return colour_ ? "\x1b[44m" : ""; }
        std::string_view magenta_bg() const noexcept  { return colour_ ? "\x1b[45m" : ""; }
        std::string_view cyan_bg() const noexcept     { return colour_ ? "\x1b[46m" : ""; }
        std::string_view white_bg() const noexcept    { return colour_ ? "\x1b[47m" : ""; }

        // Grey index is clamped to 0-23
        // RGB indices are clamped to 0-5

        std::string grey(int y) const;
        std::string grey_bg(int y) const;
        std::string rgb(int r, int g, int b) const;
        std::string rgb_bg(int r, int g, int b) const;
        std::string rgb(colour c) const { return rgb(c[0], c[1], c[2]); }
        std::string rgb_bg(colour c) const { return rgb_bg(c[0], c[1], c[2]); }

        static std::size_t columns() noexcept { return getenv_size("COLUMNS", 80); }
        static std::size_t lines() noexcept { return getenv_size("LINES", 25); }
        static XtermMode guess_mode() noexcept;
        static bool is_tty(std::FILE* stream) noexcept;

    private:

        bool colour_;

        static std::size_t getenv_size(const char* name, std::size_t default_value) noexcept;
        static int grey_index(int y) noexcept { return std::clamp(y, 0, 23) + 232; }
        static int rgb_index(int r, int g, int b) noexcept;

    };

        inline std::string Xterm::grey(int y) const {
            return colour_ ? "\x1b[38;5;" + std::to_string(grey_index(y)) + "m" : "";
        }

        inline std::string Xterm::grey_bg(int y) const {
            return colour_ ? "\x1b[48;5;" + std::to_string(grey_index(y)) + "m" : "";
        }

        inline std::string Xterm::rgb(int r, int g, int b) const {
            return colour_ ? "\x1b[38;5;" + std::to_string(rgb_index(r, g, b)) + "m" : "";
        }

        inline std::string Xterm::rgb_bg(int r, int g, int b) const {
            return colour_ ? "\x1b[48;5;" + std::to_string(rgb_index(r, g, b)) + "m" : "";
        }

        inline XtermMode Xterm::guess_mode() noexcept {

            if (! is_tty(stdout)) {
                return unknown;
            }

            auto env = std::getenv("COLORFGBG");

            if (env == nullptr || *env == 0) {
                return unknown;
            }

            std::string_view envstr{env};
            auto semi = envstr.find_last_of(';');

            if (semi == npos) {
                return unknown;
            }

            auto bg = parse_number_maybe<unsigned>(envstr.substr(semi + 1));

            if (! bg) {
                return unknown;
            } else if (*bg == 7 || *bg >= 9) {
                return light;
            } else {
                return dark;
            }

        }

        inline bool Xterm::is_tty(std::FILE* stream) noexcept {

            int fd;

            if (stream == stdin) {
                fd = 0;
            } else if (stream == stdout) {
                fd = 1;
            } else if (stream == stderr) {
                fd = 2;
            } else {
                return false;
            }

            #ifdef _WIN32
                static constexpr auto std_input_handle = static_cast<unsigned long>(-10);
                auto handle = GetStdHandle(std_input_handle - fd);
                auto mode = 0ul;
                return GetConsoleMode(handle, &mode) != 0;
            #else
                return isatty(fd) != 0;
            #endif

        }

        inline std::size_t Xterm::getenv_size(const char* name, std::size_t default_value) noexcept {

            auto env = std::getenv(name);

            if (env == nullptr) {
                return default_value;
            }

            auto size = parse_number_maybe<std::size_t>(env);

            if (size && *size > 0) {
                return *size;
            } else {
                return default_value;
            }

        }

        inline int Xterm::rgb_index(int r, int g, int b) noexcept {
            r = std::clamp(r, 0, 5);
            g = std::clamp(g, 0, 5);
            b = std::clamp(b, 0, 5);
            return 36 * r + 6 * g + b + 16;
        }

}
