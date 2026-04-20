# Global Definitions

_[Core utility library by Ross Smith](index.html)_

```c++
#include "rs-core/global.hpp"
namespace RS;
```

## Contents

* TOC
{:toc}

## Concepts

### Primitive concepts

```c++
template <typename T> concept Character;
```

Matches any standard character type: `char, char8_t, char16_t, char32_t,
wchar_t.`

```c++
template <typename T> concept Reference;
template <typename T> concept MutableReference;
template <typename T> concept ConstReference;
template <typename T> concept NonReference;
```

Reference type concepts. The names should be self-explanatory.

### Arithmetic concepts

```c++
template <typename T> concept Integral;
template <typename T> concept SignedIntegral;
template <typename T> concept UnsignedIntegral;
template <typename T> concept FloatingPoint;
template <typename T> concept FixedPointArithmetic;
template <typename T> concept RationalArithmetic;
template <typename T> concept Arithmetic;
```

`Integral, SignedIntegral, UnsignedIntegral,` and `FloatingPoint` match the
same types as the similarly named standard library concepts, as well as any
type that has a specialization of `numeric_limits` with the appropriate
values for `is_integer` and `is_signed.`

The `FixedPointArithmetic` and `RationalArithmetic` concepts are based purely
on the type's specialization of `numeric_limits,` checking for additional
custom constants, `is_fixed_point` and `is_rational.` Any type that matches
either of these is excluded from matching any of the integer or floating
point concepts even if their properties would otherwise qualify them. It is
legal for a type to match both of these.

The `Arithmetic` concept matches any type that matches any of the other
concepts listed here.

The `bool` type, and all character types, are excluded from all of these
concepts.

## Constants

```c++
constexpr std::string_view ascii_whitespace = "\t\n\r ";
constexpr std::uint8_t max8 = [maximum value of a uint8_t];
constexpr std::uint16_t max16 = [maximum value of a uint16_t];
constexpr std::uint32_t max32 = [maximum value of a uint32_t];
constexpr std::uint64_t max64 = [maximum value of a uint64_t];
constexpr std::size_t npos = [maximum value of a size_t];
```

Defined for convenience.

## Metaprogramming utilities

```c++
template <typename> constexpr bool dependent_false = false;
```

Used when the equivalent of `static_assert(false)` is needed in a dependent
context.

```c++
template <typename T> concept MaybeNontypeParameter;
```

Checks whether a type can be used as a non-type template parameter.
