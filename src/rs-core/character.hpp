#pragma once

#include "rs-core/global.hpp"
#include <algorithm>
#include <string>
#include <string_view>

namespace RS {

    // Character property functions

    constexpr bool is_ascii(char c) noexcept         { return static_cast<unsigned char>(c) <= 0x7f; }
    constexpr bool ascii_iscntrl(char c) noexcept    { auto b = static_cast<unsigned char>(c); return b <= 0x1f || b == 0x7f; }
    constexpr bool ascii_isblank(char c) noexcept    { return c == '\t' || c == ' '; }
    constexpr bool ascii_isspace(char c) noexcept    { return (c >= '\t' && c <= '\r') || c == ' '; }
    constexpr bool ascii_isdigit(char c) noexcept    { return c >= '0' && c <= '9'; }
    constexpr bool ascii_isxdigit(char c) noexcept   { return ascii_isdigit(c) || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'); }
    constexpr bool ascii_isupper(char c) noexcept    { return c >= 'A' && c <= 'Z'; }
    constexpr bool ascii_islower(char c) noexcept    { return c >= 'a' && c <= 'z'; }
    constexpr bool ascii_isalpha(char c) noexcept    { return ascii_isupper(c) || ascii_islower(c); }
    constexpr bool ascii_isalnum(char c) noexcept    { return ascii_isdigit(c) || ascii_isalpha(c); }
    constexpr bool ascii_isgraph(char c) noexcept    { return c >= '!' && c <= '~'; }
    constexpr bool ascii_isprint(char c) noexcept    { return c >= ' ' && c <= '~'; }
    constexpr bool ascii_ispunct(char c) noexcept    { return ascii_isgraph(c) && ! ascii_isalnum(c); }
    constexpr bool ascii_isalpha_w(char c) noexcept  { return ascii_isalpha(c) || c == '_'; }
    constexpr bool ascii_isalnum_w(char c) noexcept  { return ascii_isalnum(c) || c == '_'; }
    constexpr bool ascii_ispunct_w(char c) noexcept  { return ascii_ispunct(c) && c != '_'; }
    constexpr char ascii_tolower(char c) noexcept    { return static_cast<char>(ascii_isupper(c) ? c + 0x20 : c); }
    constexpr char ascii_toupper(char c) noexcept    { return static_cast<char>(ascii_islower(c) ? c - 0x20 : c); }

    constexpr bool is_ascii32(char32_t c) noexcept           { return c <= 0x7f; }
    constexpr bool ascii_iscntrl32(char32_t c) noexcept      { return c <= 0x1f || c == 0x7f; }
    constexpr bool ascii_isblank32(char32_t c) noexcept      { return c == U'\t' || c == U' '; }
    constexpr bool ascii_isspace32(char32_t c) noexcept      { return (c >= U'\t' && c <= U'\r') || c == U' '; }
    constexpr bool ascii_isdigit32(char32_t c) noexcept      { return c >= U'0' && c <= U'9'; }
    constexpr bool ascii_isxdigit32(char32_t c) noexcept     { return ascii_isdigit32(c) || (c >= U'A' && c <= U'F') || (c >= U'a' && c <= U'f'); }
    constexpr bool ascii_isupper32(char32_t c) noexcept      { return c >= U'A' && c <= U'Z'; }
    constexpr bool ascii_islower32(char32_t c) noexcept      { return c >= U'a' && c <= U'z'; }
    constexpr bool ascii_isalpha32(char32_t c) noexcept      { return ascii_isupper32(c) || ascii_islower32(c); }
    constexpr bool ascii_isalnum32(char32_t c) noexcept      { return ascii_isdigit32(c) || ascii_isalpha32(c); }
    constexpr bool ascii_isgraph32(char32_t c) noexcept      { return c >= U'!' && c <= U'~'; }
    constexpr bool ascii_isprint32(char32_t c) noexcept      { return c >= U' ' && c <= U'~'; }
    constexpr bool ascii_ispunct32(char32_t c) noexcept      { return ascii_isgraph32(c) && ! ascii_isalnum32(c); }
    constexpr bool ascii_isalpha_w32(char32_t c) noexcept    { return ascii_isalpha32(c) || c == U'_'; }
    constexpr bool ascii_isalnum_w32(char32_t c) noexcept    { return ascii_isalnum32(c) || c == U'_'; }
    constexpr bool ascii_ispunct_w32(char32_t c) noexcept    { return ascii_ispunct32(c) && c != U'_'; }
    constexpr char32_t ascii_tolower32(char32_t c) noexcept  { return ascii_isupper32(c) ? c + 0x20 : c; }
    constexpr char32_t ascii_toupper32(char32_t c) noexcept  { return ascii_islower32(c) ? c - 0x20 : c; }

    // String functions

    inline std::string ascii_lowercase(std::string_view str) {
        std::string out(str);
        std::transform(out.begin(), out.end(), out.begin(), ascii_tolower);
        return out;
    }

    inline std::string ascii_uppercase(std::string_view str) {
        std::string out(str);
        std::transform(out.begin(), out.end(), out.begin(), ascii_toupper);
        return out;
    }

}
