#pragma once

#include "rs-core/global.hpp"
#include <algorithm>
#include <array>
#include <concepts>
#include <cstddef>
#include <format>
#include <ranges>
#include <string>
#include <string_view>
#include <type_traits>

namespace RS::Detail {

    template <typename T>
    concept StringOrView = std::convertible_to<T, std::string>
        || std::convertible_to<T, std::string_view>;

    template <typename T>
    concept FormatByMemberFunction = requires (const T t) {
        { t.rs_core_format() } -> StringOrView;
    };

    template <typename T>
    concept FormatByMemberFunctionWithFlags = requires (const T t, std::string_view s) {
        { t.rs_core_format(s) } -> StringOrView;
    };

    template <typename T>
    concept FormatByMemberFunctionWithSize = requires (const T t, std::size_t n) {
        { t.rs_core_format(n) } -> StringOrView;
    };

    template <typename T>
    concept FormatByMemberFunctionWithBoth = requires (const T t, std::string_view s, std::size_t n) {
        { t.rs_core_format(s, n) } -> StringOrView;
    };

    template <typename T>
    concept FormatByFreeFunction = requires (const T t) {
        { rs_core_format(t) } -> StringOrView;
    };

    template <typename T>
    concept FormatByFreeFunctionWithFlags = requires (const T t, std::string_view s) {
        { rs_core_format(t, s) } -> StringOrView;
    };

    template <typename T>
    concept FormatByFreeFunctionWithSize = requires (const T t, std::size_t n) {
        { rs_core_format(t, n) } -> StringOrView;
    };

    template <typename T>
    concept FormatByFreeFunctionWithBoth = requires (const T t, std::string_view s, std::size_t n) {
        { rs_core_format(t, s, n) } -> StringOrView;
    };

    template <typename T>
    concept AutoFormat = FormatByMemberFunction<T>
        || FormatByMemberFunctionWithFlags<T>
        || FormatByMemberFunctionWithSize<T>
        || FormatByMemberFunctionWithBoth<T>
        || FormatByFreeFunction<T>
        || FormatByFreeFunctionWithFlags<T>
        || FormatByFreeFunctionWithSize<T>
        || FormatByFreeFunctionWithBoth<T>;

}

template <::RS::Detail::AutoFormat T>
struct std::formatter<T> {

private:

    static constexpr auto max_flags = 16uz;

    static constexpr auto with_flags =
        ::RS::Detail::FormatByMemberFunctionWithFlags<T>
        || ::RS::Detail::FormatByMemberFunctionWithBoth<T>
        || ::RS::Detail::FormatByFreeFunctionWithFlags<T>
        || ::RS::Detail::FormatByFreeFunctionWithBoth<T>;

    static constexpr auto with_size =
        ::RS::Detail::FormatByMemberFunctionWithSize<T>
        || ::RS::Detail::FormatByMemberFunctionWithBoth<T>
        || ::RS::Detail::FormatByFreeFunctionWithSize<T>
        || ::RS::Detail::FormatByFreeFunctionWithBoth<T>;

    template <int> class empty_type {};

    struct flags_base {
        std::array<char, max_flags> flags;
        std::size_t n_flags = 0;
    };

    struct size_base {
        std::size_t size = 0;
    };

    struct info_type:
    std::conditional_t<with_flags, flags_base, empty_type<1>>,
    std::conditional_t<with_size, size_base, empty_type<2>> {};

    info_type info_;

    constexpr std::string_view flags() const noexcept {
        if constexpr (with_flags) {
            return std::string_view(info_.flags.data(), info_.n_flags);
        } else {
            return {};
        }
    }

    static constexpr bool legit_flag(char c) noexcept {
        return c != 0 && c != '{' && c != '}'
            && (c < '0' || c > '9');
    }

public:

    constexpr auto parse(std::format_parse_context& ctx) {

        auto it = ctx.begin();

        for (; it != ctx.end() && *it != '}'; ++it) {

            if constexpr (with_flags) {
                if (legit_flag(*it) && info_.n_flags < max_flags) {
                    info_.flags[info_.n_flags++] = *it;
                    continue;
                }
            }

            if constexpr (with_size) {
                if (*it >= '0' && *it <= '9') {
                    info_.size = info_.size * 10uz + static_cast<std::size_t>(*it - '0');
                    continue;
                }
            }

            throw std::format_error{std::format("Invalid format: {:?}", *it)};

        }

        return it;

    }

    // The gratuitous template here is a workaround for a libc++ bug
    // https://github.com/llvm/llvm-project/issues/66466

    template <typename FormatContext>
    auto format(const T& t, FormatContext& ctx) const {

        using namespace ::RS::Detail;

        std::string out;

        if constexpr (FormatByMemberFunctionWithBoth<T>) {
            out = t.rs_core_format(flags(), info_.size);
        } else if constexpr (FormatByMemberFunctionWithFlags<T>) {
            out = t.rs_core_format(flags());
        } else if constexpr (FormatByMemberFunctionWithSize<T>) {
            out = t.rs_core_format(info_.size);
        } else if constexpr (FormatByMemberFunction<T>) {
            out = t.rs_core_format();
        } else if constexpr (FormatByFreeFunctionWithBoth<T>) {
            out = rs_core_format(t, flags(), info_.size);
        } else if constexpr (FormatByFreeFunctionWithFlags<T>) {
            out = rs_core_format(t, flags());
        } else if constexpr (FormatByFreeFunctionWithSize<T>) {
            out = rs_core_format(t, info_.size);
        } else if constexpr (FormatByFreeFunction<T>) {
            out = rs_core_format(t);
        } else {
            static_assert(::RS::dependent_false<T>);
        }

        return std::ranges::copy(out, ctx.out()).out;

    }

};
