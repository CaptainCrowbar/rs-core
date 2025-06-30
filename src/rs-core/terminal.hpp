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

        // Terminal properties

        bool is_colour() const noexcept { return colour_; }

        static std::size_t columns() noexcept { return getenv_size("COLUMNS", 80); }
        static std::size_t lines() noexcept { return getenv_size("LINES", 25); }
        static XtermMode guess_mode() noexcept;
        static bool is_tty(std::FILE* stream = stdout) noexcept;
        static bool is_tty(int fd) noexcept;

        // Cursor control sequences

        static std::string_view home() noexcept           { return "\x1b[0G"; }
        static std::string_view left() noexcept           { return "\x1b[D"; }
        static std::string_view right() noexcept          { return "\x1b[C"; }
        static std::string_view up() noexcept             { return "\x1b[A"; }
        static std::string_view down() noexcept           { return "\x1b[B"; }
        static std::string left(int n)                    { return "\x1b[" + std::to_string(n) + "D"; }
        static std::string right(int n)                   { return "\x1b[" + std::to_string(n) + "C"; }
        static std::string up(int n)                      { return "\x1b[" + std::to_string(n) + "A"; }
        static std::string down(int n)                    { return "\x1b[" + std::to_string(n) + "B"; }
        static std::string move_to(int x, int y)          { return "\x1b[" + std::to_string(y) + ";" + std::to_string(x) + "H"; }
        static std::string_view save_position() noexcept  { return "\x1b[s"; }
        static std::string_view load_position() noexcept  { return "\x1b[u"; }
        static std::string_view erase_left() noexcept     { return "\x1b[1K"; }
        static std::string_view erase_right() noexcept    { return "\x1b[K"; }
        static std::string_view erase_above() noexcept    { return "\x1b[1J"; }
        static std::string_view erase_below() noexcept    { return "\x1b[J"; }
        static std::string_view erase_line() noexcept     { return "\x1b[2K"; }
        static std::string_view clear_screen() noexcept   { return "\x1b[2J"; }

        // Format control sequences

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
            if (stream == stdin) {
                return is_tty(0);
            } else if (stream == stdout) {
                return is_tty(1);
            } else if (stream == stderr) {
                return is_tty(2);
            } else {
                return false;
            }
        }

        inline bool Xterm::is_tty(int fd) noexcept {
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
