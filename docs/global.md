# Global Definitions

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

## Metaprogramming utilities

```c++
template <typename> constexpr bool dependent_false = false;
```

Used when the equivalent of `static_assert(false)` is needed in a dependent
context.
