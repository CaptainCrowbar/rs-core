#pragma once

#include "rs-core/character.hpp"
#include "rs-core/global.hpp"
#include <algorithm>
#include <cerrno>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <format>
#include <iterator>
#include <limits>
#include <optional>
#include <ranges>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>

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

    // Integer formatting

    template <std::integral T>
    void append_integer(std::string& str, T t, int base = 10, std::size_t digits = 1) {

        using limits = std::numeric_limits<T>;
        using U = std::make_unsigned_t<T>;

        auto u_base = static_cast<U>(base);
        U u;

        if constexpr (std::signed_integral<T>) {
            if (t < 0) {
                str += '-';
                if (t == limits::lowest()) {
                    u = static_cast<U>(limits::max()) + 1;
                } else {
                    u = static_cast<U>(- t);
                }
            } else {
                u = static_cast<U>(t);
            }
        } else {
            u = t;
        }

        auto start_pos = str.size();
        auto min_size = start_pos + digits;

        while (u != 0) {
            auto digit = u % u_base;
            u /= u_base;
            if (digit < 10) {
                str += static_cast<char>(digit + '0');
            } else {
                str += static_cast<char>(digit - 10 + 'a');
            }
        }

        if (str.size() < min_size) {
            str.append(min_size - str.size(), '0');
        }

        std::reverse(str.begin() + static_cast<std::ptrdiff_t>(start_pos), str.end());

    }

    // Floating point formatting

    namespace Detail {

        constexpr auto null_exponent = std::numeric_limits<int>::lowest();

        // Significand has an implicit decimal point after the first digit

        template <std::floating_point T>
        void format_float_exponent_breakdown(T t, std::size_t prec, std::string& sig, int& exp) {

            using limits = std::numeric_limits<T>;

            static constexpr auto exp_bits = 8 * sizeof(T) - static_cast<std::size_t>(limits::digits) - 1;
            static constexpr auto exp_digits10 = (exp_bits + 2) / 3;

            auto print_size = exp_digits10 + prec + 6;
            sig.resize(print_size, '\0');
            auto print_prec = std::max(static_cast<int>(prec) - 1, 0);
            int rc;

            if constexpr (sizeof(T) <= sizeof(double)) {
                rc = std::snprintf(sig.data(), sig.size(), "%.*e", print_prec, static_cast<double>(t));
            } else {
                rc = std::snprintf(sig.data(), sig.size(), "%.*Le", print_prec, static_cast<long double>(t));
            }

            sig.resize(static_cast<std::size_t>(rc));
            auto e_pos = sig.find('e');
            exp = *parse_number_maybe<int>(sig.substr(e_pos + 1));
            sig.resize(e_pos);

            if (sig.size() > 1) {
                sig.erase(1, 1);
            }

        }

        inline void format_float_digits_compose(std::string& sig, int& exp) {

            auto prec = static_cast<int>(sig.size());

            if (exp < 0) {
                auto zeros = static_cast<std::size_t>(- exp - 1);
                sig.insert(0, "0.");
                sig.insert(2, zeros, '0');
            } else if (exp < prec - 1) {
                auto pos = static_cast<std::size_t>(exp + 1);
                sig.insert(pos, 1, '.');
            } else {
                auto zeros = static_cast<std::size_t>(exp - prec + 1);
                sig.append(zeros, '0');
            }

            exp = null_exponent;

        }

        inline void format_float_exponent_compose(std::string& sig) {
            if (sig.size() >= 2) {
                sig.insert(1, 1, '.');
            }
        }

        template <std::floating_point T>
        void format_float_fixed(T t, std::size_t prec, std::string& sig) {

            auto print_size = prec + 4;

            if (t > T{1}) {
                print_size += static_cast<std::size_t>(std::ceil(std::log10(t)));
            }

            sig.resize(print_size, '\0');
            int rc;

            if constexpr (sizeof(T) <= sizeof(double)) {
                rc = std::snprintf(sig.data(), sig.size(), "%.*f", static_cast<int>(prec), static_cast<double>(t));
            } else {
                rc = std::snprintf(sig.data(), sig.size(), "%.*Lf", static_cast<int>(prec), static_cast<long double>(t));
            }

            sig.resize(static_cast<std::size_t>(rc));

        }

        template <std::floating_point T>
        void format_float_general(T t, std::size_t prec, std::string& sig, int& exp) {

            format_float_exponent_breakdown(t, prec, sig, exp);
            auto threshold = std::max(static_cast<int>(prec), 1);

            if (exp >= -4 && exp < threshold) {
                format_float_digits_compose(sig, exp);
            } else {
                format_float_exponent_compose(sig);
            }

        }

    }

    template <std::floating_point T>
    std::string format_float(T t, std::string_view fmt = {}) {

        static constexpr std::string_view base_formats{"DdEeFfGg"};

        auto base = 'g';
        auto mods = fmt;

        if (! mods.empty() && base_formats.contains(mods[0])) {
            base = mods[0];
            mods = mods.substr(1);
        }

        auto first_digit = std::ranges::find_if(mods, ascii_isdigit);
        std::size_t prec;

        if (first_digit == mods.end()) {
            prec = 6;
        } else {
            prec = 0;
            for (auto it = first_digit; it != mods.end() && ascii_isdigit(*it); ++it) {
                prec = 10uz * prec + static_cast<std::size_t>(*it - '0');
            }
        }

        mods = {mods.begin(), first_digit};
        auto upper = ascii_isupper(base);
        auto abs_t = std::abs(t);
        std::string sig;
        auto exp = Detail::null_exponent;

        if (std::isinf(t)) {

            sig = upper ? "INF" : "inf";

        } else if (std::isnan(t)) {

            sig = upper ? "NAN" : "nan";

        } else {

            switch (base) {
                case 'D': case 'd':
                    Detail::format_float_exponent_breakdown(abs_t, prec, sig, exp);
                    Detail::format_float_digits_compose(sig, exp);
                    break;
                case 'E': case 'e':
                    Detail::format_float_exponent_breakdown(abs_t, prec, sig, exp);
                    Detail::format_float_exponent_compose(sig);
                    break;
                case 'F': case 'f':
                    Detail::format_float_fixed(abs_t, prec, sig);
                    break;
                default:
                    Detail::format_float_general(abs_t, prec, sig, exp);
                    break;
            }

        }

        std::string str;

        if (std::signbit(t)) {
            str = "-";
        } else if (mods.contains('s')) {
            str = "+";
        }

        str += sig;

        if (exp != Detail::null_exponent) {
            str += upper ? 'E' : 'e';
            if (exp >= 0 && mods.contains('S')) {
                str += '+';
            }
            append_integer(str, exp);
        }

        return str;

    }

    // Roman numerals

    inline std::string roman(int n) {

        if (n < 1) {
            return {};
        }

        static constexpr std::pair<int, const char*> table[] = {
            { 900, "CM" }, { 500, "D" }, { 400, "CD" }, { 100, "C" },
            { 90, "XC" }, { 50, "L" }, { 40, "XL" }, { 10, "X" },
            { 9, "IX" }, { 5, "V" }, { 4, "IV" }, { 1, "I" },
        };

        std::string r(static_cast<std::size_t>(n / 1000), 'M');
        n %= 1000;

        for (auto [div,str]: table) {
            for (auto q = n / div; q > 0; --q) {
                r += str;
            }
            n %= div;
        }

        return r;

    }

    inline int parse_roman(std::string_view str) {

        static constexpr auto max_value = static_cast<unsigned long long>(std::numeric_limits<int>::max());

        struct group_info {
            int factor;
            char one;
            char five;
            char ten;
        };

        struct group_result {
            int value = 0;
            std::size_t length = 0;
        };

        static const group_info groups[] = {
            { 100,  'C', 'D', 'M' },
            { 10,   'X', 'L', 'C' },
            { 1,    'I', 'V', 'X' },
        };

        static const auto read_group = [] (std::string_view str, const group_info& group) -> group_result {

            auto count = std::min(str.find_first_not_of(group.one), str.size());
            auto next = count == str.size() ? 0 :
                str[count] == group.five ? 5 :
                str[count] == group.ten ? 10 : 0;

            if (next == 0) {
                return {static_cast<int>(count) * group.factor, count};
            } else if (next > 0 && count > 1) {
                return {-1, 0};
            } else if (next > 0 && count == 1) {
                return {(next - 1) * group.factor, 2};
            } else if (next > 0 && str.size() == 1) {
                return {next * group.factor, 1};
            }

            count = std::min(str.find_first_not_of(group.one, 1), str.size());
            auto value = next + static_cast<int>(count - 1);

            return {value * group.factor, count};

        };

        if (str.empty()) {
            return -1;
        }

        auto pos = std::min(str.find_first_not_of('M'), str.size());
        auto result = 1000ull * static_cast<unsigned long long>(pos);
        auto tail = str.substr(pos);

        for (const auto& group: groups) {
            auto rc = read_group(tail, group);
            if (rc.value == -1) {
                return -1;
            } else if (rc.value > 0) {
                result += static_cast<unsigned long long>(rc.value);
                tail = tail.substr(rc.length);
            }
        }

        if (tail.empty() && result <= max_value) {
            return static_cast<int>(result);
        } else {
            return -1;
        }

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
            auto and_mask = static_cast<unsigned char>(0xff);
            auto or_mask = static_cast<unsigned char>(~ (0xff >> len));

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
