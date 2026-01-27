#pragma once

#include "rs-core/global.hpp"
#include <algorithm>
#include <concepts>
#include <functional>
#include <iterator>
#include <ranges>
#include <utility>
#include <vector>

namespace RS {

    // Concepts

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
