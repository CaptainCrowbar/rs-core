#pragma once

#include <concepts>
#include <cstdint>
#include <iterator>
#include <limits>
#include <ranges>
#include <string_view>
#include <type_traits>
#include <utility>

namespace RS {

    // Sanity check

    static_assert(std::numeric_limits<unsigned char>::digits == 8);

    // Constants

    constexpr std::string_view ascii_whitespace = "\t\n\r ";
    constexpr auto npos = ~ 0uz;

    // Bitmask functions

    namespace Detail {

        template <std::integral T>
        constexpr auto force_unsigned(T t) noexcept {
            return static_cast<std::make_unsigned_t<T>>(t);
        }

        template <typename T>
        requires std::is_enum_v<T>
        constexpr auto force_unsigned(T t) noexcept {
            return force_unsigned(static_cast<std::underlying_type_t<T>>(t));
        }

    }

    template <typename T1, typename T2>
    requires (std::integral<T1> || std::is_enum_v<T1>)
        && (std::integral<T2> || std::is_enum_v<T2>)
    constexpr bool has_bit(T1 x, T2 y) noexcept {
        using namespace Detail;
        auto u = force_unsigned(x);
        auto v = force_unsigned(y);
        return (u & v) != 0;
    }

    template <typename T1, typename T2>
    requires (std::integral<T1> || std::is_enum_v<T1>)
        && (std::integral<T2> || std::is_enum_v<T2>)
    constexpr bool has_bits(T1 x, T2 y) noexcept {
        using namespace Detail;
        auto u = force_unsigned(x);
        auto v = force_unsigned(y);
        return v != 0 && (u & v) == v;
    }

    // Character functions

    constexpr bool is_ascii(char c) noexcept { return static_cast<unsigned char>(c) <= 0x7f; }
    constexpr bool ascii_iscntrl(char c) noexcept { auto b = static_cast<unsigned char>(c); return b <= 0x1f || b == 0x7f; }
    constexpr bool ascii_isblank(char c) noexcept { return c == '\t' || c == ' '; }
    constexpr bool ascii_isspace(char c) noexcept { return (c >= '\t' && c <= '\r') || c == ' '; }
    constexpr bool ascii_isdigit(char c) noexcept { return c >= '0' && c <= '9'; }
    constexpr bool ascii_isxdigit(char c) noexcept { return ascii_isdigit(c) || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'); }
    constexpr bool ascii_isupper(char c) noexcept { return c >= 'A' && c <= 'Z'; }
    constexpr bool ascii_islower(char c) noexcept { return c >= 'a' && c <= 'z'; }
    constexpr bool ascii_isalpha(char c) noexcept { return ascii_isupper(c) || ascii_islower(c); }
    constexpr bool ascii_isalnum(char c) noexcept { return ascii_isdigit(c) || ascii_isalpha(c); }
    constexpr bool ascii_isgraph(char c) noexcept { return c >= '!' && c <= '~'; }
    constexpr bool ascii_isprint(char c) noexcept { return c >= ' ' && c <= '~'; }
    constexpr bool ascii_ispunct(char c) noexcept { return ascii_isgraph(c) && ! ascii_isalnum(c); }
    constexpr char ascii_tolower(char c) noexcept { return static_cast<char>(ascii_isupper(c) ? c + 0x20 : c); }
    constexpr char ascii_toupper(char c) noexcept { return static_cast<char>(ascii_islower(c) ? c - 0x20 : c); }

    // Integer literals

    constexpr std::int8_t operator""_i8(unsigned long long x) noexcept { return static_cast<std::int8_t>(x); }
    constexpr std::int16_t operator""_i16(unsigned long long x) noexcept { return static_cast<std::int16_t>(x); }
    constexpr std::int32_t operator""_i32(unsigned long long x) noexcept { return static_cast<std::int32_t>(x); }
    constexpr std::int64_t operator""_i64(unsigned long long x) noexcept { return static_cast<std::int64_t>(x); }
    constexpr std::uint8_t operator""_u8(unsigned long long x) noexcept { return static_cast<std::uint8_t>(x); }
    constexpr std::uint16_t operator""_u16(unsigned long long x) noexcept { return static_cast<std::uint16_t>(x); }
    constexpr std::uint32_t operator""_u32(unsigned long long x) noexcept { return static_cast<std::uint32_t>(x); }
    constexpr std::uint64_t operator""_u64(unsigned long long x) noexcept { return static_cast<std::uint64_t>(x); }

    // Metaprogramming utilities

    template <typename> constexpr bool dependent_false = false;

    // Range functions

    template <std::input_or_output_iterator I, std::sentinel_for<I> S>
    std::ranges::subrange<I, S> as_range(std::pair<I, S> pair) noexcept {
        return std::ranges::subrange(pair.first, pair.second);
    }

}
