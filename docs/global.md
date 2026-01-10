# Global Utilities

_[Core utility library by Ross Smith](index.html)_

```c++
#include "rs-core/global.hpp"
namespace RS;
```

## Contents

* TOC
{:toc}

## Constants

```c++
constexpr std::string_view ascii_whitespace = "\t\n\r ";
constexpr auto max32 = ~ std::uint32_t{0};
constexpr auto max64 = ~ std::uint64_t{0};
constexpr auto npos = ~ 0uz;
```

Defined for convenience.

## Concepts

```c++
template <typename T> concept SignedIntegral;
template <typename T> concept UnsignedIntegral;
template <typename T> concept Integral;
template <typename T> concept FloatingPoint;
template <typename T> concept FixedPointArithmetic;
template <typename T> concept RationalArithmetic;
template <typename T> concept Arithmetic;
```

`SignedIntegral, UnsignedIntegral, Integral,` and `FloatingPoint` match the
same types as the similarly named standard library concepts, as well as any
type that has a specialization of `numeric_limits` with the appropriate
values for `is_integer` and `is_signed.`

The `FixedPointArithmetic` and `RationalArithmetic` concepts are based purely
on the type's specialization of `numeric_limits,` checking for additional
custom constants, `is_fixed_point` and `is_rational.` Any type that matches
either of these is excluded from matching any of the integer or floating
point concepts even if their properties would otherwise qualify them.

The `Arithmetic` concept matches any type that matches any of the other
concepts listed here.

The `bool` type is excluded from all of these concepts.

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
template <typename R, typename V> concept ReadWriteRange
    = ReadableRange<R, V> && WritableRange<R, V>;
template <typename R, typename V> concept ReadWriteForwardRange
    = ReadableForwardRange<R, V> && WritableForwardRange<R, V>;
template <typename R, typename V> concept ReadWriteBidirectionalRange
    = ReadableBidirectionalRange<R, V> && WritableBidirectionalRange<R, V>;
template <typename R, typename V> concept ReadWriteRandomAccessRange
    = ReadableRandomAccessRange<R, V> && WritableRandomAccessRange<R, V>;
template <typename R, typename V> concept ReadWriteContiguousRange
    = ReadableContiguousRange<R, V> && WritableContiguousRange<R, V>;
```

Range concepts compatible with specific value types. All of these require `R`
to be a range of the appropriate type. `ReadableRange` also requires a
dereferenced iterator to be assignable to a `V` object; `WritableRange` also
requires a dereferenced iterator to be assignable from a `V` object.

## Metaprogramming utilities

```c++
template <typename> constexpr bool dependent_false = false;
```

Used when the equivalent of `static_assert(false)` is needed in a dependent
context.

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
