# 128-Bit Integers

_[Core utility library by Ross Smith](index.html)_

```c++
#include "rs-core/uint128.hpp"
namespace RS;
```

## 128-bit integers

```c++
class Uint128;
using uint128_t = [see below];
```

The `Uint128` class implements 128-bit arithmetic using a pair of 64-bit
integers internally, and is described in detail below. The `uint128_t` type
is defined as a convenience alias for the native 128-bit type if one exists,
otherwise for the `Uint128` class.

```c++
using Uint128::word = std::uint64_t;
```

The internal word size.

```c++
constexpr Uint128::Uint128() noexcept;
```

The default constructor sets the value to zero.

```c++
template <std::integral T> constexpr [conditionally explicit]
    Uint128::Uint128(T t) noexcept;
```

Conversion constructor from any primitive integer type. This is implicit if
the argument type is unsigned and no larger than 128 bits, otherwise
explicit. If `T` is signed, negative arguments will be represented using twos
complement.

```c++
constexpr Uint128::Uint128(std::uint64_t hi, std::uint64_t lo) noexcept;
```

Constructor from the high and low 64-bit halves.

```c++
explicit Uint128::Uint128(std::string_view str, int base = 10);
```

Constructor from a string. This will throw `std::out_of_range` if the base is
out of range (2-36), or `std:invalid_argument` if the string is empty or
contains a character that is not a valid digit in the specified base. Values
out of range will be truncated to their low 128 bits.

```c++
constexpr Uint128::~Uint128() noexcept;
constexpr Uint128::Uint128(const Uint128& u) noexcept;
constexpr Uint128::Uint128(Uint128&& u) noexcept;
constexpr Uint128& Uint128::operator=(const Uint128& u) noexcept;
constexpr Uint128& Uint128::operator=(Uint128&& u) noexcept;
```

Other life cycle functions.

```c++
explicit constexpr Uint128::operator bool() const noexcept;
```

Explicit boolean conversion operator. As usual, this returns true if the value
is not zero.

```c++
template <std::integral T>
    constexpr explicit Uint128::operator T() const noexcept;
```

Explicit conversion operator to a primitive integer type. For unsigned types,
the value will be truncated to the number of bits in the return type; for
signed types, behaviour is undefined if the value does not fit in the return
type.

```c++
constexpr Uint128& Uint128::operator++() noexcept;
constexpr Uint128 Uint128::operator++(int) noexcept;
constexpr Uint128& Uint128::operator--() noexcept;
constexpr Uint128 Uint128::operator--(int) noexcept;
constexpr Uint128& Uint128::operator+=(Uint128 y) noexcept;
constexpr Uint128& Uint128::operator-=(Uint128 y) noexcept;
constexpr Uint128& Uint128::operator*=(Uint128 y) noexcept;
constexpr Uint128& Uint128::operator/=(Uint128 y) noexcept;
constexpr Uint128& Uint128::operator%=(Uint128 y) noexcept;
constexpr Uint128 operator+(Uint128 x, Uint128 y) noexcept;
constexpr Uint128 operator-(Uint128 x, Uint128 y) noexcept;
constexpr Uint128 operator*(Uint128 x, Uint128 y) noexcept;
constexpr Uint128 operator/(Uint128 x, Uint128 y) noexcept;
constexpr Uint128 operator%(Uint128 x, Uint128 y) noexcept;
```

Arithmetic operators. These all have their normal behaviour for unsigned
integers.

```c++
constexpr Uint128 Uint128::operator~() const noexcept;
constexpr Uint128& Uint128::operator&=(Uint128 y) noexcept;
constexpr Uint128& Uint128::operator|=(Uint128 y) noexcept;
constexpr Uint128& Uint128::operator^=(Uint128 y) noexcept;
constexpr Uint128& Uint128::operator<<=(int y) noexcept;
constexpr Uint128& Uint128::operator>>=(int y) noexcept;
constexpr Uint128 operator&(Uint128 x, Uint128 y) noexcept;
constexpr Uint128 operator|(Uint128 x, Uint128 y) noexcept;
constexpr Uint128 operator^(Uint128 x, Uint128 y) noexcept;
constexpr Uint128 operator<<(Uint128 x, int y) noexcept;
constexpr Uint128 operator>>(Uint128 x, int y) noexcept;
```

Bitwise operators. These all have their normal behaviour.

```c++
constexpr bool operator==(Uint128 x, Uint128 y) noexcept;
constexpr bool operator!=(Uint128 x, Uint128 y) noexcept;
constexpr bool operator<(Uint128 x, Uint128 y) noexcept;
constexpr bool operator>(Uint128 x, Uint128 y) noexcept;
constexpr bool operator<=(Uint128 x, Uint128 y) noexcept;
constexpr bool operator>=(Uint128 x, Uint128 y) noexcept;
constexpr std::strong_ordering operator<=>(Uint128 x, Uint128 y) noexcept;
```

Comparison operators. These all have their normal behaviour.

```c++
constexpr int Uint128::bit_width() const noexcept;
```

Returns the number of bits in the value's binary representation.

```c++
constexpr std::pair<Uint128, Uint128>
    Uint128::divide(Uint128 y) const noexcept;
```

Returns the quotient and remainder of the division. Behaviour is undefined on
division by zero.

```c++
constexpr std::uint64_t Uint128::high() const noexcept;
constexpr std::uint64_t Uint128::low() const noexcept;
```

Return the high and low 64-bit halves of the value.

```c++
std::string Uint128::str(int base = 10, std::size_t digits = 1) const;
std::string Uint128::hex() const { return str(16, 32); }
```

Formats the value as a string, in the specified base and with at least the
specified number of digits. This will throw `std::out_of_range` if the base
is out of range (2-36). The `hex()` function displays the full length of the
value as hex digits.

## Specializations

```c++
template <typename T> struct std::common_type<Uint128, T>;
template <typename T> struct std::common_type<T, Uint128>;
```

Common types. These follow the usual rules for integer types.

```c++
template <> struct std::formatter<Uint128>;
```

Formatter for `Uint128` objects. The only formatting flags recognized are
`'b'` for binary output, and `'x'` for hexadecimal output. The minimum number
of digits can also be supplied.

```c++
template <> struct std::hash<Uint128>;
```

Hash function.

```c++
template <> class std::numeric_limits<Uint128>;
```

Numeric limits.
