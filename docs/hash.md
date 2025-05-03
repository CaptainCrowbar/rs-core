# Hash Function Helpers

_[Core utilty library by Ross Smith](index.html)_

```c++
#include "rs-core/hash.hpp"
namespace RS;
```

## Contents

* TOC
{:toc}

## Automatic hash specialization

```c++
template <typename T> struct std::hash<T>;
```

If this header is included, a standard hash specialization is automatically
generated for any type for which a function exists with the signature:

```c++
[void] rs_core_hash(T);
```

The function need not be defined; the existence of the declaration is enough.
The return type is not important and will never be used. As well as the dummy
signalling function, the type must have a `hash()` member function that will
be called by the `std::hash` specialization.

(I chose this approach, with a dummy function declared to request the creation
of a hash specialization, rather than having this function generate the hash
itself, to make it easier to add a standard hash after the fact to existing
types.)

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
