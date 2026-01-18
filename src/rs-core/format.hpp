#pragma once

#include "rs-core/global.hpp"
#include <algorithm>
#include <concepts>
#include <format>
#include <iterator>
#include <string>
#include <string_view>

namespace RS {

    namespace Detail {

        template <typename T>
        concept FormatViaMemberStr = requires (const T t) {
            { t.str() } -> std::convertible_to<std::string>;
        };

        template <typename T>
        concept FormatViaToString = ! FormatViaMemberStr<T>
            && requires (const T t) {
                { to_string(t) } -> std::convertible_to<std::string>;
            };

    }

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

            auto n = c <= 0x7f    ? 1
                : c <= 0x7ff      ? 2
                : c <= 0xd7ff     ? 3
                : c <= 0xdfff     ? 0
                : c <= 0xffff     ? 3
                : c <= 0x10'ffff  ? 4 : 0;

            if (n == 0) {
                return write_out("\ufffd", out);
            } else if (n == 1) {
                return *out++ = static_cast<char>(c);
            }

            unsigned char and_mask = 0xff;
            unsigned char or_mask = ~ (0xff >> n);

            for (auto shift = 6 * (n - 1); shift >= 0; shift -= 6, and_mask = 0x3f, or_mask = 0x80) {
                auto masked = ((c >> shift) & and_mask) | or_mask;
                *out++ = static_cast<char>(masked);
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
        requires (Detail::FormatViaMemberStr<T>)
        auto format(const T& t, FormatContext& ctx) const {
            return write_out(t.str(), ctx.out());
        }

        template <typename FormatContext>
        requires (Detail::FormatViaToString<T>)
        auto format(const T& t, FormatContext& ctx) const {
            return write_out(to_string(t), ctx.out());
        }

    };

}
