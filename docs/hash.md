# Hash Functions

_[Core utility library by Ross Smith](index.html)_

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

### Hash utility functions

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

### Basic hash functions

```c++
constexpr std::uint32_t kernighan_hash(const void* ptr,
    std::size_t len) noexcept;
```

An implementation of Brian Kernighan's simple general purpose hash function.

### SipHash

```c++
class SipHash {
    SipHash() noexcept;
    explicit SipHash(std::uint64_t key0, std::uint64_t key1) noexcept;
    explicit SipHash(const void* key) noexcept;
    SipHash(const SipHash& sh) noexcept;
    SipHash(SipHash&& sh) noexcept;
    ~SipHash() noexcept;
    SipHash& operator=(const SipHash& sh) noexcept;
    SipHash& operator=(SipHash&& sh) noexcept;
    std::uint64_t operator()(const void* ptr, std::size_t len) const noexcept;
    std::uint64_t operator()(std::string_view view) const noexcept;
};
```

SipHash-2-4-64 by Jean-Philippe Aumasson and Daniel J Bernstein.

The key can be supplied either as a pair of 64-bit integers or as raw bytes.
The default constructor uses a key consisting of ascending bytes. If the
third constructor is used, the key pointer must point to an array of at least
16 bytes.
