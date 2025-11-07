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

## Interpolation functions

```c++
enum class Lerp: std::uint8_t {
    none = 0,
    log_x,
    log_y,
    log_xy = log_x | log_y,
};
```

Bitmask values used to select linear or logarithmic interpolation.

```c++
template <Lerp Mode = Lerp::none, std::floating_point X, typename Y>
    constexpr Y interpolate(X x1, Y y1, X x2, Y y2, X x3) noexcept;
```

Performs linear or logarithmic interpolation. The `Mode` argument indicates
whether interpolation should be linear or logarithmic on the X or Y axis.

Type `Y` does not have to be a floating point type unless the `log_y` flag is
used. The only requirements are that it support addition and subtraction, and
that multiplying an `X` by a `Y` is supported, yielding a `Y.`

Behaviour is undefined if any of the following is true:

* `x1=x2`
* The `log_x` flag is used, and `x1<=0, x2<=0,` or `x3<=0`
* The `log_y` flag is used, and `y1<=0` or `y2<=0`

## Number parsing

```c++
enum class ParseNumber: int {
    ok,              // Successful parse
    invalid_base,    // Number base is invalid (expected 0 or 2-36)
    invalid_number,  // String does not contain a valid number
    out_of_range,    // Number is valid but out of range for the type
};
```

Return status from the `parse_number()` functions.

```c++
template <std::integral T>
    ParseNumber parse_number(std::string_view str, T& t,
        int base = 10);
template <std::floating_point T>
    ParseNumber parse_number(std::string_view str, T& t);
```

Parse an integer or floating point number. On a successful parse, the result
is written into the `t` argument. A leading sign is allowed only for signed
integers and floating point. For the integer parser, if the base is zero,
base 10 is used unless a leading `"0b"` or `"0x"` prefix is present,
indicating a binary or hexadecimal number. The floating point parser will
recognize the usual conventions for infinities and NaNs. All number formats
are case insensitive.

```c++
template <std::integral T>
    std::optional<T> parse_number_maybe(std::string_view str,
        int base = 10);
template <std::floating_point T>
    std::optional<T> parse_number_maybe(std::string_view str);
```

These perform the same functions as `parse_number(),` but the arithmetic type
must be specified explicitly, and the return value is an optional instead of
a more detailed status.

```c++
template <std::integral T>
    T try_parse_number(std::string_view str, int base = 10);
template <std::floating_point T>
    T try_parse_number(std::string_view str);
```

These perform the same functions as `parse_number_maybe(),` but a failed
conversion will throw `std::invalid_argument` or `std::out_of_range` instead
of returning a null optional.
