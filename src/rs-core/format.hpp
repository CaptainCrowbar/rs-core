#pragma once

#include "rs-core/global.hpp"
#include <algorithm>
#include <concepts>
#include <format>
#include <iterator>
#include <string>
#include <string_view>

namespace RS {

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
