# Arithmetic Types and Functions

_[Core utility library by Ross Smith](index.html)_

```c++
#include "rs-core/arithmetic.hpp"
namespace RS;
```

## Contents

* TOC
{:toc}

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

## Integer literals

```c++
constexpr std::int8_t operator""_i8(unsigned long long x) noexcept;
constexpr std::int16_t operator""_i16(unsigned long long x) noexcept;
constexpr std::int32_t operator""_i32(unsigned long long x) noexcept;
constexpr std::int64_t operator""_i64(unsigned long long x) noexcept;
constexpr std::uint8_t operator""_u8(unsigned long long x) noexcept;
constexpr std::uint16_t operator""_u16(unsigned long long x) noexcept;
constexpr std::uint32_t operator""_u32(unsigned long long x) noexcept;
constexpr std::uint64_t operator""_u64(unsigned long long x) noexcept;
```

Defined for convenience.

## Number formatting

```c++
template <std::unsigned_integral T>
    std::string& append_number(std::string& str, T t, std::size_t digits = 1,
        int base = 10);
template <std::signed_integral T>
    std::string& append_number(std::string& str, T t, std::size_t digits = 1,
        int base = 10);
```

Simple formatters to append an integer to a string.

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
