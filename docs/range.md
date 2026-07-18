# Range utilities

_[Core utility library by Ross Smith](index.html)_

```c++
#include "rs-core/range.hpp"
namespace RS;
```

## Contents

* TOC
{:toc}

## Concepts

```c++
template <typename R, typename V> concept ReadableRange;
template <typename R, typename V> concept ReadableForwardRange;
template <typename R, typename V> concept ReadableBidirectionalRange;
template <typename R, typename V> concept ReadableRandomAccessRange;
template <typename R, typename V> concept ReadableContiguousRange;
template <typename R, typename V> concept WritableRange;
template <typename R, typename V> concept WritableForwardRange;
template <typename R, typename V> concept WritableBidirectionalRange;
template <typename R, typename V> concept WritableRandomAccessRange;
template <typename R, typename V> concept WritableContiguousRange;
template <typename R, typename V> concept ReadWriteRange;
template <typename R, typename V> concept ReadWriteForwardRange;
template <typename R, typename V> concept ReadWriteBidirectionalRange;
template <typename R, typename V> concept ReadWriteRandomAccessRange;
template <typename R, typename V> concept ReadWriteContiguousRange;
```

Range concepts compatible with specific value types. All of these require `R`
to be a range of the appropriate type. `ReadableRange` also requires a
dereferenced iterator to be assignable to a `V` object; `WritableRange`
requires a dereferenced iterator to be assignable from a `V` object.

## Range functions

```c++
template <std::input_or_output_iterator I, std::sentinel_for<I> S>
std::ranges::subrange<I, S> as_range(std::pair<I, S> pair) noexcept {
    return std::ranges::subrange(pair.first, pair.second);
}
```

Turns an iterator pair returned by `equal_range()` into an actual range.

```c++
template <std::ranges::range Range>
    std::vector<[value type]> sorted(const Range& range);
template <std::ranges::range Range,
        std::strict_weak_order<[value type]> Compare>
    std::vector<[value type]> sorted(const Range& range,
        Compare compare);
```

Return a sorted copy of the range.

## Range algorithms

### Cartesian power

```c++
template <std::ranges::forward_range Range>
class CartesianPowerIterator {
    using iterator_category = std::forward_iterator_tag;
    using value_type = std::vector<[range value type]>;
    CartesianPowerIterator();
    explicit CartesianPowerIterator(const Range& range, std::size_t k);
};

template <std::ranges::forward_range Range>
    std::ranges::subrange<CartesianPowerIterator<Range>>
    cartesian_power(const Range& range, std::size_t k);
```

This iterates over the Cartesian power `k` of the input range, i.e.
`range×range×...×range`. The dereferenced vector contains `k` elements from
the input range. The output range contains _n<sup>k</sup>_ elements, where
`n` is the size of the input range. The output elements are in their natural
order based on the order of the input range, with the last element varying
fastest.
