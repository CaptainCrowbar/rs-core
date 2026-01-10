#pragma once

#include <algorithm>
#include <concepts>
#include <cstdint>
#include <functional>
#include <iterator>
#include <limits>
#include <print>
#include <ranges>
#include <string_view>
#include <utility>
#include <vector>

namespace RS {

    // Sanity check

    static_assert(std::numeric_limits<unsigned char>::digits == 8);

    // Concepts

    template <typename T>
    concept FixedPointArithmetic = std::numeric_limits<T>::is_specialized
        && std::numeric_limits<T>::is_fixed_point;

    template <typename T>
    concept RationalArithmetic = std::numeric_limits<T>::is_specialized
        && std::numeric_limits<T>::is_rational;

    template <typename T>
    concept SignedIntegral = (std::signed_integral<T>
            || (std::numeric_limits<T>::is_specialized
                && std::numeric_limits<T>::is_integer
                && std::numeric_limits<T>::is_signed))
        && ! (FixedPointArithmetic<T> || RationalArithmetic<T>);

    template <typename T>
    concept UnsignedIntegral = (std::unsigned_integral<T>
            || (std::numeric_limits<T>::is_specialized
                && std::numeric_limits<T>::is_integer
                && ! std::numeric_limits<T>::is_signed))
        && ! (FixedPointArithmetic<T> || RationalArithmetic<T>
            || std::same_as<T, bool>);

    template <typename T>
    concept Integral = SignedIntegral<T> || UnsignedIntegral<T>;

    template <typename T>
    concept FloatingPoint = (std::floating_point<T>
            || (std::numeric_limits<T>::is_specialized
                && ! std::numeric_limits<T>::is_integer))
        && ! (FixedPointArithmetic<T> || RationalArithmetic<T>);

    template <typename T>
    concept Arithmetic = Integral<T>
        || FloatingPoint<T>
        || FixedPointArithmetic<T>
        || RationalArithmetic<T>;

    namespace Detail {

        template <typename R, typename V>
        concept CanReadRange = std::assignable_from<V&, std::ranges::range_reference_t<R>>;

        template <typename R, typename V>
        concept CanWriteRange = std::assignable_from<std::ranges::range_reference_t<R>&, V>;

    }

    template <typename R, typename V>
    concept ReadableRange = std::ranges::range<R> && Detail::CanReadRange<R, V>;

    template <typename R, typename V>
    concept ReadableForwardRange = std::ranges::forward_range<R> && Detail::CanReadRange<R, V>;

    template <typename R, typename V>
    concept ReadableBidirectionalRange = std::ranges::bidirectional_range<R> && Detail::CanReadRange<R, V>;

    template <typename R, typename V>
    concept ReadableRandomAccessRange = std::ranges::random_access_range<R> && Detail::CanReadRange<R, V>;

    template <typename R, typename V>
    concept ReadableContiguousRange = std::ranges::contiguous_range<R> && Detail::CanReadRange<R, V>;

    template <typename R, typename V>
    concept WritableRange = std::ranges::range<R> && Detail::CanWriteRange<R, V>;

    template <typename R, typename V>
    concept WritableForwardRange = std::ranges::forward_range<R> && Detail::CanWriteRange<R, V>;

    template <typename R, typename V>
    concept WritableBidirectionalRange = std::ranges::bidirectional_range<R> && Detail::CanWriteRange<R, V>;

    template <typename R, typename V>
    concept WritableRandomAccessRange = std::ranges::random_access_range<R> && Detail::CanWriteRange<R, V>;

    template <typename R, typename V>
    concept WritableContiguousRange = std::ranges::contiguous_range<R> && Detail::CanWriteRange<R, V>;

    template <typename R, typename V>
    concept ReadWriteRange = ReadableRange<R, V> && WritableRange<R, V>;

    template <typename R, typename V>
    concept ReadWriteForwardRange = ReadableForwardRange<R, V> && WritableForwardRange<R, V>;

    template <typename R, typename V>
    concept ReadWriteBidirectionalRange = ReadableBidirectionalRange<R, V> && WritableBidirectionalRange<R, V>;

    template <typename R, typename V>
    concept ReadWriteRandomAccessRange = ReadableRandomAccessRange<R, V> && WritableRandomAccessRange<R, V>;

    template <typename R, typename V>
    concept ReadWriteContiguousRange = ReadableContiguousRange<R, V> && WritableContiguousRange<R, V>;

    // Constants

    constexpr std::string_view ascii_whitespace = "\t\n\r ";
    constexpr auto max32 = ~ std::uint32_t{0};
    constexpr auto max64 = ~ std::uint64_t{0};
    constexpr auto npos = ~ 0uz;

    // Metaprogramming utilities

    template <typename> constexpr bool dependent_false = false;

    // Range functions

    template <std::input_or_output_iterator I, std::sentinel_for<I> S>
    std::ranges::subrange<I, S> as_range(std::pair<I, S> pair) noexcept {
        return std::ranges::subrange(pair.first, pair.second);
    }

    template <std::ranges::range Range,
        std::strict_weak_order<std::ranges::range_value_t<Range>, std::ranges::range_value_t<Range>> Compare>
    std::vector<std::ranges::range_value_t<Range>> sorted(const Range& range, Compare compare) {
        auto vec = std::vector(std::from_range, range);
        std::ranges::sort(vec, compare);
        return vec;
    }

    template <std::ranges::range Range>
    std::vector<std::ranges::range_value_t<Range>> sorted(const Range& range) {
        return sorted(range, std::less<std::ranges::range_value_t<Range>>{});
    }

}
