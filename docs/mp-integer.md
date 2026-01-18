# Multiple Precision Integers

_[Core utility library by Ross Smith](index.html)_

```c++
#include "rs-core/mp-integer.hpp"
namespace RS;
```

## Contents

* TOC
{:toc}

## Concepts

```c++
template <typename T> concept Mpitype;
```

The `Mpitype` concept is satisfied by `Natural` or `Integer`.

## Multiple precision integer classes

```c++
class Integer;
class Natural;
```

The `Integer` and `Natural` classes represent signed and unsigned arbitrary
precision integers. The size of the values they can hold are limited only by
available memory.

In the descriptions of functions and operators here, where a type is given as
`Mpitype` this indicates that the function or operator is defined for both
types. The specific types `Integer` or `Natural` are mentioned only where the
interface differs significantly between the two classes.

### Life cycle operations

```c++
Mpitype::Mpitype() noexcept;
```

The default constructor sets the value to zero.

```c++
template <std::integral T> [maybe explicit] Mpitype::Mpitype(T t);
```

Conversion constructor from primitive integer types. This is explicit if the
input is a signed integer and the output is unsigned; in this case a negative
argument will be clamped to zero. Otherwise, the conversion is implicit, and
always yields the correct value.

```c++
Integer::Integer(const Natural& x);
```

Conversion constructor from a `Natural` to an `Integer.`

```c++
Natural::Natural(std::initializer_list<std::uint64_t> list);
```

Constructor from a list of 64-bit integers, which are concatenated in big
endian order to make a `Natural.`

```c++
explicit Mpitype::Mpitype(std::string_view str, unsigned base = 10);
```

Constructor from the string representation of a number. If the base is zero,
the conventional `"0b"` (binary) and `"0x"` (hexadecimal) prefixes will be
recognized, with the base defaulting to 10 if neither prefix is present.

Parsing is case insensitive. Apostrophe or underscore delimiters between
digits will be ignored. This constructor will throw `std::out_of_range` if
the base is out of range (2-36) and is not zero, or `std::invalid_argument`
if the string is not a valid integer in the specified base.

```c++
Mpitype::Mpitype(const Mpitype& x);
Mpitype::Mpitype(Mpitype&& x) noexcept;
Mpitype::~Mpitype() noexcept;
Mpitype& Mpitype::operator=(const Mpitype& x);
Mpitype& Mpitype::operator=(Mpitype&& x) noexcept;
```

Other life cycle operations.

### Arithmetic functions

```c++
bool Mpitype::operator!() const noexcept;
```

Returns true if the value is zero.

```c++
Mpitype Mpitype::operator+() const;
Integer Integer::operator-() const;
```

Unary operators. The unsigned type does not have a unary minus operator.

```c++
Mpitype& Mpitype::operator++();
Mpitype Mpitype::operator++(int);
Mpitype& Mpitype::operator--();
Mpitype Mpitype::operator--(int);
```

Increment and decrement operators. For the unsigned type, decrementing from
zero will simply yield zero.

```c++
Mpitype& Mpitype::operator+=(const Mpitype& y);
Mpitype& Mpitype::operator-=(const Mpitype& y);
Mpitype& Mpitype::operator*=(const Mpitype& y);
Mpitype& Mpitype::operator/=(const Mpitype& y);
Mpitype& Mpitype::operator%=(const Mpitype& y);
Mpitype operator+(const Mpitype& x, const Mpitype& y);
Mpitype operator-(const Mpitype& x, const Mpitype& y);
Mpitype operator*(const Mpitype& x, const Mpitype& y);
Mpitype operator/(const Mpitype& x, const Mpitype& y);
Mpitype operator%(const Mpitype& x, const Mpitype& y);
```

Arithmetic operators. For the unsigned type, subtraction yields zero if the
true result would be negative. For the signed type, the division operators
perform Euclidean division, where the remainder is always positive if the
division is not exact.

```c++
Natural& Natural::operator&=(const Natural& y);
Natural& Natural::operator|=(const Natural& y);
Natural& Natural::operator^=(const Natural& y);
Natural& Natural::operator<<=(int y);
Natural& Natural::operator>>=(int y);
Natural operator&(const Natural& x, const Natural& y);
Natural operator|(const Natural& x, const Natural& y);
Natural operator^(const Natural& x, const Natural& y);
Natural operator<<(const Natural& x, int y);
Natural operator>>(const Natural& x, int y);
```

Bitwise arithmetic operators. These are defined only for the unsigned type.
For the shift operators, behaviour is undefined if the RHS is negative.

```c++
std::pair<Mpitype, Mpitype> Mpitype::divide(const Mpitype& y) const;
```

Returns the quotient and remainder (the same values returned by the operators)
in a single call.

### Bit manipulation functions

All of these are defined only for the unsigned type.

```c++
std::size_t Natural::bits() const noexcept;
```

Returns the number of bits in the smallest binary representation of the value
(zero if the value is zero).

```c++
bool Natural::get_bit(std::size_t i) const noexcept;
void Natural::set_bit(std::size_t i, bool b = true);
void Natural::flip_bit(std::size_t i);
```

Query, set, or invert a specific bit (bit 0 is the least significant bit).

```c++
std::size_t Natural::popcount() const noexcept;
```

Returns the number of 1 bits in the value.

### Comparison functions

```c++
bool operator==(const Mpitype& x, const Mpitype& y) noexcept;
bool operator!=(const Mpitype& x, const Mpitype& y) noexcept;
bool operator<(const Mpitype& x, const Mpitype& y) noexcept;
bool operator>(const Mpitype& x, const Mpitype& y) noexcept;
bool operator<=(const Mpitype& x, const Mpitype& y) noexcept;
bool operator>=(const Mpitype& x, const Mpitype& y) noexcept;
```

Conventional comparison operators.

```c++
std::strong_ordering operator<=>(const Mpitype& x, const Mpitype& y) noexcept;
```

Three-way comparison operator.

### Conversion functions

```c++
explicit Mpitype::operator bool() const noexcept;
```

Returns true if the value is not zero.

```c++
double Mpitype::as_double() const noexcept;
explicit Mpitype::operator double() const noexcept;
```

Convert the value to floating point. This may only be approximate, depending
on the size of the value.

```c++
template <std::integral T> bool Mpitype::in_range() const noexcept;
```

True if the value is within the range of the specified primitive integer
type.

```c++
template <std::integral T> std::optional<T>
    Mpitype::checked_cast() const noexcept;
```

Returns the value as a primitive integer type, or a null optional if the value
is out of range for the return type.

```c++
template <std::integral T> T Mpitype::unchecked_cast() const noexcept;
```

Returns the value as a primitive integer type. Behaviour is undefined if the
value is out of range for the return type.

```c++
template <std::integral T> explicit Mpitype::operator T() const noexcept;
```

Explicit conversion operator to a primitive integer type. This will return
zero if the value is out of range for the integer type.

```c++
explicit Integer::operator Natural() const;
```

Explicit conversion operator from an `Integer` to a `Natural.` This will
return zero if the value is negative.

### Property queries

```c++
Natural Integer::abs() const;
```

Returns the absolute value of a signed integer.

```c++
int Integer::sign() const noexcept;
```

Returns the sign (-1 if negative, 0 if zero, +1 if positive).

```c++
std::size_t Mpitype::hash() const noexcept;
```

Hash function.

### String functions

```c++
static std::optional<Mpitype> Mpitype::parse(std::string_view str,
    unsigned base = 10);
```

Parse a string to an integer. This will return a null optional if the string
argument is not a valid integer in the specified base. If the base is zero,
the conventional `"0b"`(binary) and `"0x"` (hexadecimal) prefixes will be
recognized, with the base defaulting to 10 if neither prefix is present.

Parsing is case insensitive. Apostrophe or underscore delimiters between
digits will be ignored. This will throw `std::out_of_range` if the base is
out of range (2-36) and is not zero.

```c++
std::string Mpitype::to_string(unsigned base = 10,
    std::size_t digits = 1) const;
```

Formats the value as a string, with at least the specified number of digits.
This will throw `std::out_of_range` if the base is out of range (2-36).

## Literals

```c++
namespace Literals {
    Natural operator""_N(const char* raw);
    Integer operator""_Z(const char* raw);
};
```

Custom literals.

## Specializations

```c++
template <typename T> struct std::common_type<Mpitype, T>;
template <typename T> struct std::common_type<T, Mpitype>;
```

Common type. This follows these rules:

* Common type of `Natural` and `Integer` is `Integer.`
* Common type of `Natural` and any signed primitive integral type is `Integer.`
* Common type of `Natural` and any unsigned primitive integral type is `Natural.`
* Common type of `Integer` and any primitive integral type is `Integer.`
* Common type of `Natural` or `Integer` and any primitive floating point type
  is the larger of the floating point type and `double.`

```c++
struct std::formatter<Mpitype>;
```

Standard formatter. The only flags recognized are `"b"` (binary) and `"x"`
(hexadecimal); if neither flag is present the value will be returned in
decimal; the result is unspecified if both are present.

```c++
struct std::hash<Mpitype>;
```

Hash function.

```c++
class std::numeric_limits<Mpitype>;
```

Numeric type properties.
