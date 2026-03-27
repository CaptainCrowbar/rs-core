# Arithmetic Types and Functions

_[Core utility library by Ross Smith](index.html)_

```c++
#include "rs-core/arithmetic.hpp"
namespace RS;
```

## Contents

* TOC
{:toc}

## Arithmetic functions

```c++
template <typename T> constexpr [see below] binomial(T a, T b);
```

Returns the binomial coefficient of `(a,b).` Returns zero if `a<0, b<0,` or
`b>a.` The return type is `double` if `T` is integral, otherwise `T`.
Behaviour is undefined if the correct result would be out of range for the
return type.

```c++
template <typename T>
    constexpr std::pair<T, T> euclidean_divide(T x, T y);
```

Returns the quotient and remainder under Euclidean division, in which the
remainder is always positive if the division is not exact. Behaviour is
undefined if the divisor is zero or if the correct result is outside the
range of the type.

```c++
template <typename T> constexpr T gcd(T x, T y);
template <typename T> constexpr T lcm(T x, T y);
```

Greatest common divisor and least common multiple algorithms. Generalized
versions are provided here because the standard library versions are
restricted to primitive types.

If `T` is signed, the signs of the arguments are ignored. The `gcd()` function
will return zero if both arguments are zero; `lcm()` will return zero if
either argument is zero. For the `lcm()` function, behaviour is undefined if
the correct result would be out of range for the type.

```c++
template <typename T> constexpr T int_power(T x, int y);
```

Calculates `x` to the power of `y` quickly using a binary algorithm. `T` can
be any type that supports multiplication. Behaviour is undefined if `y` is
negative, or if the result would be out of range for the return type.

## Bitmask operations

```c++
template <[integer or enum] T1, [integer or enum] T2>
    constexpr bool has_bit(T1 x, T2 y) noexcept;
template <[integer or enum] T1, [integer or enum] T2>
    constexpr bool has_bits(T1 x, T2 y) noexcept;
```

Check whether specific bits are present in a bitmask. The `has_bit()` function
returns true if the arguments have any bits in common; `has_bits()` returns
true if all bits in the second argument are also present in the first. Both
functions will always return false if either argument is zero. Arguments can
be any integer or enumeration type.

## Conversion functions

```c++
template <std::integral To, std::integral From>
    constexpr std::optional<To> checked_cast(From x) noexcept;
template <std::integral To, std::integral From>
    constexpr std::optional<To> checked_cast(std::optional<From> x) noexcept;
```

Convert an integer to a different type, returning null if the argument is out
of range for the return type.

```c++
template <std::floating_point T> constexpr T degrees(T rad) noexcept;
template <std::floating_point T> constexpr T radians(T deg) noexcept;
namespace Literals {
    constexpr float operator""_degf(long double rad) noexcept;
    constexpr float operator""_degf(unsigned long long rad) noexcept;
    constexpr double operator""_deg(long double rad) noexcept;
    constexpr double operator""_deg(unsigned long long rad) noexcept;
    constexpr long double operator""_degld(long double rad) noexcept;
    constexpr long double operator""_degld(unsigned long long rad) noexcept;
}
```

Degree/radian conversions.

## Geometry functions

```c++
template <std::size_t N = 3, std::floating_point T>
    requires (N >= 1)
    T sphere_area_from_radius(T r) noexcept;
template <std::size_t N = 3, std::floating_point T>
    requires (N >= 1)
    T sphere_volume_from_radius(T r) noexcept;
template <std::size_t N = 3, std::floating_point T>
    requires (N >= 2)
    T sphere_radius_from_area(T s) noexcept;
template <std::size_t N = 3, std::floating_point T>
    requires (N >= 1)
    T sphere_radius_from_volume(T v) noexcept;
```

Surface area and volume of a sphere in `N` dimensions.

The `sphere_radius_from_area()` function is restricted to `N>=2` because
the "surface" of a 1-sphere is always two points, so no radius can be
deduced.

## Integer literals

```c++
namespace Literals {
    constexpr std::int8_t operator""_i8(unsigned long long x) noexcept;
    constexpr std::uint8_t operator""_u8(unsigned long long x) noexcept;
    constexpr std::int16_t operator""_i16(unsigned long long x) noexcept;
    constexpr std::uint16_t operator""_u16(unsigned long long x) noexcept;
    constexpr std::int32_t operator""_i32(unsigned long long x) noexcept;
    constexpr std::uint32_t operator""_u32(unsigned long long x) noexcept;
    constexpr std::int64_t operator""_i64(unsigned long long x) noexcept;
    constexpr std::uint64_t operator""_u64(unsigned long long x) noexcept;
}
```

Defined for convenience.
