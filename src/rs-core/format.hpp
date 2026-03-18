#pragma once

#include "rs-core/character.hpp"
#include "rs-core/global.hpp"
#include <algorithm>
#include <cerrno>
#include <concepts>
#include <cstdlib>
#include <format>
#include <iterator>
#include <limits>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>

namespace RS {

    // Number parsing

    enum class ParseNumber: int {
        ok,
        invalid_base,
        invalid_number,
        out_of_range,
    };

    namespace Detail {

        inline void check_parse_result(ParseNumber rc, std::string_view str, int base = 0) {
            switch (rc) {
                case ParseNumber::invalid_base:    throw std::invalid_argument(std::format("Invalid number base: {}", base));
                case ParseNumber::invalid_number:  throw std::invalid_argument(std::format("Invalid number: {:?}", str));
                case ParseNumber::out_of_range:    throw std::out_of_range(std::format("Number is out of range: {}", str));
                default:                           break;
            }
        }

        template <std::unsigned_integral T>
        ParseNumber parse_unsigned_integer(std::string_view str, T& t, int base) {

            using limits = std::numeric_limits<T>;

            if (str.empty()) {
                return ParseNumber::invalid_number;
            }

            if (base == 0) {
                if (str.size() >= 2 && str[0] == '0') {
                    switch (str[1]) {
                        case 'B': case 'b':  return parse_unsigned_integer(str.substr(2), t, 2);
                        case 'O': case 'o':  return parse_unsigned_integer(str.substr(2), t, 8);
                        case 'X': case 'x':  return parse_unsigned_integer(str.substr(2), t, 16);
                        default:             break;
                    }
                }
                base = 10;
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
            } else if (u > max_value + static_cast<U>(negative)) {
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

    template <std::integral T>
    T try_parse_number(std::string_view str, int base = 10) {
        T t {};
        Detail::check_parse_result(parse_number(str, t, base), str, base);
        return t;
    }

    template <std::floating_point T>
    T try_parse_number(std::string_view str) {
        T t {};
        Detail::check_parse_result(parse_number(str, t), str);
        return t;
    }

    // Standard formatter helpers

    // Type agnostic formatter base class

    struct CommonFormatter {

    public:

        template <typename ParseContext>
        constexpr auto parse(ParseContext& ctx) {
            if (ctx.begin() != ctx.end() && *ctx.begin() != '}') {
                throw std::format_error("Unknown formatting flag");
            }
            return ctx.begin();
        }

    protected:

        template <typename ParseContext>
        constexpr auto parse_helper(ParseContext& ctx, std::string_view allowed_flags,
                std::string* flags = nullptr, unsigned* number = nullptr) {

            enum class phase { before, during, after };

            auto it = ctx.begin();
            auto long_number = 0ull;
            auto number_phase = phase::before;

            for (; it != ctx.end(); ++it) {

                if (*it == '}') {

                    break;

                } else if (number != nullptr && *it >= '0' && *it <= '9') {

                    if (number_phase == phase::after) {
                        throw std::format_error{"Multiple integers in format"};
                    }

                    number_phase = phase::during;
                    long_number = 10 * long_number + static_cast<unsigned>(*it - '0');

                    if (long_number > std::numeric_limits<unsigned>::max()) {
                        throw std::format_error{"Integer out of range in format"};
                    }

                } else if (flags != nullptr && *it >= ' ' && *it <= '~' && allowed_flags.contains(*it)) {

                    if (number_phase == phase::during) {
                        number_phase = phase::after;
                    }

                    *flags += *it;

                } else {

                    throw std::format_error{"Unknown formatting flag"};

                }

            }

            if (number_phase != phase::before) {
                *number = static_cast<unsigned>(long_number);
            }

            return it;

        }

        template <std::output_iterator<char> Out>
        static Out write_out(std::string_view str, Out out) {
            return std::copy(str.begin(), str.end(), out);
        }

        template <std::output_iterator<char> Out>
        static Out write_out(char32_t c, Out out) {

            if (c <= 0x7f) {
                return *out++ = static_cast<char>(c);
            } else if ((c >= 0xd800 && c <= 0xdfff) || c >= 0x11'0000) {
                return write_out("\ufffd", out);
            }

            auto len = c <= 0x7ff ? 2 : c <= 0xffff ? 3 : 4;
            auto shift = 6 * (len - 1);
            unsigned char and_mask = 0xff;
            unsigned char or_mask = ~ (0xff >> len);

            while (shift >= 0) {
                auto unit = ((c >> shift) & and_mask) | or_mask;
                *out++ = static_cast<char>(unit);
                shift -= 6;
                and_mask = 0x3f;
                or_mask = 0x80;
            }

            return out;

        }

        template <std::output_iterator<char> Out>
        static Out write_out(std::u32string_view str, Out out) {
            for (auto c: str) {
                out = write_out(c, out);
            }
            return out;
        }

    };

    // Type specific formatter base class

    template <typename T>
    struct BasicFormatter:
    CommonFormatter {

        template <typename FormatContext>
        requires requires (const T t) {
            { t.to_string() } -> std::convertible_to<std::string>;
        }
        auto format(const T& t, FormatContext& ctx) const {
            return write_out(t.to_string(), ctx.out());
        }

        template <typename FormatContext>
        requires requires (const T t) {
            { to_string(t) } -> std::convertible_to<std::string>;
        }
        auto format(const T& t, FormatContext& ctx) const {
            return write_out(to_string(t), ctx.out());
        }

    };

}
