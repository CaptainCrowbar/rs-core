#pragma once

#include "rs-core/enum.hpp"
#include "rs-core/global.hpp"
#include <algorithm>
#include <cerrno>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <limits>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>

namespace RS {

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

    // Conversion functions

    template <std::integral To, std::integral From>
    constexpr std::optional<To> checked_cast(From x) noexcept {

        static constexpr auto from_signed = std::signed_integral<From>;
        static constexpr auto to_signed = std::signed_integral<To>;
        static constexpr auto min_to = std::numeric_limits<To>::min();
        static constexpr auto max_to = std::numeric_limits<To>::max();

        if constexpr (from_signed == to_signed) {

            // Same signedness

            if constexpr (sizeof(To) < sizeof(From)) {
                if (x < static_cast<From>(min_to) || x > static_cast<From>(max_to)) {
                    return {};
                }
            }

        } else if constexpr (from_signed) {

            // Signed to unsigned

            if (x < 0) {
                return {};
            }

            if constexpr (sizeof(To) < sizeof(From)) {
                if (x > static_cast<From>(max_to)) {
                    return {};
                }
            }

        } else {

            // Unsigned to signed

            if constexpr (sizeof(To) <= sizeof(From)) {
                if (x > static_cast<From>(max_to)) {
                    return {};
                }
            }

        }

        return static_cast<To>(x);

    }

    template <std::integral To, std::integral From>
    constexpr std::optional<To> checked_cast(std::optional<From> x) noexcept {
        if (x) {
            return checked_cast<To>(*x);
        } else {
            return {};
        }
    }

    // Integer literals

    namespace Detail {

        template <std::integral To, std::integral From>
        constexpr To static_checked_cast(From x) {
            auto opt = checked_cast<To>(x);
            if (! opt) {
                throw std::range_error("Integer out of range");
            }
            return *opt;
        }

    }

    constexpr std::int8_t operator""_i8(unsigned long long x) noexcept { return Detail::static_checked_cast<std::int8_t>(x); }
    constexpr std::uint8_t operator""_u8(unsigned long long x) noexcept { return Detail::static_checked_cast<std::uint8_t>(x); }
    constexpr std::int16_t operator""_i16(unsigned long long x) noexcept { return Detail::static_checked_cast<std::int16_t>(x); }
    constexpr std::uint16_t operator""_u16(unsigned long long x) noexcept { return Detail::static_checked_cast<std::uint16_t>(x); }
    constexpr std::int32_t operator""_i32(unsigned long long x) noexcept { return Detail::static_checked_cast<std::int32_t>(x); }
    constexpr std::uint32_t operator""_u32(unsigned long long x) noexcept { return Detail::static_checked_cast<std::uint32_t>(x); }
    constexpr std::int64_t operator""_i64(unsigned long long x) noexcept { return Detail::static_checked_cast<std::int64_t>(x); }
    constexpr std::uint64_t operator""_u64(unsigned long long x) noexcept { return Detail::static_checked_cast<std::uint64_t>(x); }

    // Interpolation fucntions

    RS_BITMASK(Lerp, std::uint8_t,
        none    = 0,
        log_x   = 1,
        log_y   = 2,
        log_xy  = 3,
    )

    template <Lerp Mode = Lerp::none, std::floating_point X, typename Y>
    requires requires (X x, Y y, Y yy) {
        { y + yy } -> std::convertible_to<Y>;
        { y - yy } -> std::convertible_to<Y>;
        { x * y } -> std::convertible_to<Y>;
    } && (
        ! has_bit(Mode, Lerp::log_y)
        || std::floating_point<Y>
    )
    Y interpolate(X x1, Y y1, X x2, Y y2, X x3) noexcept {
        if constexpr (has_bit(Mode, Lerp::log_x)) {
            x1 = std::log(x1);
            x2 = std::log(x2);
            x3 = std::log(x3);
        }
        if constexpr (has_bit(Mode, Lerp::log_y)) {
            y1 = std::log(y1);
            y2 = std::log(y2);
        }
        auto fraction = (x3 - x1) / (x2 - x1);
        auto y3 = y1 + fraction * (y2 - y1);
        if constexpr (has_bit(Mode, Lerp::log_y)) {
            y3 = std::exp(y3);
        }
        return y3;
    }

    // Number formatting

    template <std::unsigned_integral T>
    std::string& append_number(std::string& str, T t, std::size_t digits = 1, int base = 10) {
        static constexpr auto zero_offset = static_cast<T>('0');
        static constexpr auto alpha_offset = static_cast<T>('a' - 10);
        auto pos = str.size();
        auto t_base = static_cast<T>(base);
        for (auto i = 0uz; i < digits || t != 0; ++i, t /= t_base) {
            auto digit = t % t_base;
            if (digit < 10) {
                str += static_cast<char>(digit + zero_offset);
            } else {
                str += static_cast<char>(digit + alpha_offset);
            }
        }
        std::reverse(str.begin() + pos, str.end());
        return str;
    }

    template <std::signed_integral T>
    std::string& append_number(std::string& str, T t, std::size_t digits = 1, int base = 10) {
        using U = std::make_unsigned_t<T>;
        auto u = static_cast<U>(t);
        if (t < 0) {
            str += '-';
            u = U{} - u;
        }
        return append_number(str, u, digits, base);
    }

    // Number parsing

    RS_ENUM(ParseNumber, int,
        ok,
        invalid_base,
        invalid_number,
        out_of_range,
    )

    namespace Detail {

        template <std::unsigned_integral T>
        ParseNumber parse_unsigned_integer(std::string_view str, T& t, int base) {

            using limits = std::numeric_limits<T>;

            if (str.empty()) {
                return ParseNumber::invalid_number;
            }

            if (base == 0 && str.size() >= 3 && str[0] == '0') {
                if (str[1] == 'B' || str[1] == 'b') {
                    return parse_unsigned_integer(str.substr(2), t, 2);
                } else if (str[1] == 'X' || str[1] == 'x') {
                    return parse_unsigned_integer(str.substr(2), t, 16);
                }
            }

            auto t_base = static_cast<T>(base);
            auto max_before_multiply = limits::max() / t_base;
            T digit {};
            T value {};

            for (auto c: str) {

                if (ascii_isdigit(c)) {
                    digit = static_cast<T>(c - '0');
                } else if (base >= 11 && ascii_isupper(c)) {
                    digit = static_cast<T>(c - 'A' + 10);
                } else if (base >= 11 && ascii_islower(c)) {
                    digit = static_cast<T>(c - 'a' + 10);
                } else {
                    return ParseNumber::invalid_number;
                }

                if (digit >= t_base) {
                    return ParseNumber::invalid_number;
                } else if (value > max_before_multiply) {
                    return ParseNumber::out_of_range;
                }

                value = t_base * value + digit;

                if (value < digit) {
                    return ParseNumber::out_of_range;
                }

            }

            t = value;

            return ParseNumber::ok;

        }

        template <std::signed_integral T>
        ParseNumber parse_signed_integer(std::string_view str, T& t, int base) {

            using U = std::make_unsigned_t<T>;
            using limits = std::numeric_limits<T>;

            static constexpr auto max_value = static_cast<U>(limits::max());

            auto negative = false;

            if (! str.empty()) {
                negative = str[0] == '-';
                if (negative || str[0] == '+') {
                    str = str.substr(1);
                }
            }

            U u {};
            auto rc = parse_unsigned_integer<U>(str, u, base);

            if (rc != ParseNumber::ok) {
                return rc;
            } else if (u > max_value + static_cast<T>(negative)) {
                return ParseNumber::out_of_range;
            }

            if (negative && u != 0) {
                t = T{-1} - static_cast<T>(u - 1);
            } else {
                t = static_cast<T>(u);
            }

            return ParseNumber::ok;

        }

    }

    template <std::integral T>
    ParseNumber parse_number(std::string_view str, T& t, int base = 10) {
        if (base < 0 || base == 1 || base > 36) {
            return ParseNumber::invalid_base;
        }
        if constexpr (std::signed_integral<T>) {
            return Detail::parse_signed_integer<T>(str, t, base);
        } else {
            return Detail::parse_unsigned_integer<T>(str, t, base);
        }
    }

    template <std::floating_point T>
    ParseNumber parse_number(std::string_view str, T& t) {

        if (str.empty() || ! ascii_isgraph(str[0])) {
            return ParseNumber::invalid_number;
        }

        T rc;
        std::string str_copy {str};
        char* endptr {nullptr};
        errno = 0;

        if constexpr (sizeof(T) <= sizeof(float)) {
            rc = static_cast<T>(std::strtof(str_copy.data(), &endptr));
        } else if constexpr (sizeof(T) <= sizeof(double)) {
            rc = static_cast<T>(std::strtod(str_copy.data(), &endptr));
        } else {
            rc = static_cast<T>(std::strtold(str_copy.data(), &endptr));
        }

        int err = errno;

        if (err == 0) {
            t = rc;
            if (endptr == str_copy.data() + str_copy.size()) {
                return ParseNumber::ok;
            } else {
                return ParseNumber::invalid_number;
            }
        } else if (err == ERANGE) {
            return ParseNumber::out_of_range;
        } else {
            return ParseNumber::invalid_number;
        }

    }

    template <std::integral T>
    std::optional<T> parse_number_maybe(std::string_view str, int base = 10) {
        T t {};
        if (parse_number(str, t, base) == ParseNumber::ok) {
            return t;
        } else {
            return {};
        }
    }

    template <std::floating_point T>
    std::optional<T> parse_number_maybe(std::string_view str) {
        T t {};
        if (parse_number(str, t) == ParseNumber::ok) {
            return t;
        } else {
            return {};
        }
    }

}
