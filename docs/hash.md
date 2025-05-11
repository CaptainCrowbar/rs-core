# Hash Function Helpers

_[Core utilty library by Ross Smith](index.html)_

```c++
#include "rs-core/hash.hpp"
namespace RS;
```

## Contents

* TOC
{:toc}

## Concepts

```c++
template <typename T> concept Hashable;
```

Matches any type for which a valid specialization of `std::hash` exists.

## Hash functions

```c++
constexpr std::size_t hash_mix() noexcept { return 0; }
constexpr std::size_t hash_mix(std::size_t x) noexcept { return x; }
constexpr std::size_t hash_mix(std::size_t x, std::size_t y) noexcept;
template <std::convertible_to<std::size_t>... TS>
    constexpr std::size_t hash_mix(std::size_t x, std::size_t y,
        TS... ts) noexcept;
template <std::ranges::range Range>
    requires (std::convertible_to<[range value], std::size_t>)
    std::size_t hash_mix(const Range& range, std::size_t init = 0);
```

Hash mixing functions, for an arbitrary number of input hash values supplied
either as an explicit list or a range.

```c++
constexpr std::uint32_t kernighan_hash(const void* ptr, std::size_t len,
    std::uint32_t seed = 0) noexcept;
```

An implementation of Brian Kernighan's simple general purpose hash function.
