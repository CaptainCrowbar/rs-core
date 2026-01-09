# Rational Numbers

_[Core utility library by Ross Smith](index.html)_

```c++
#include "rs-core/rational.hpp"
namespace RS;
```

## Contents

* TOC
{:toc}

## Rational class

```c++
template <SignedIntegral T> class Rational;
```

This represents a rational number. The underlying integer type is expected to
be either a signed primitive integer type, or the `[Integer]
(mp-integer.html)` type from this library.

Rationals are always kept in their lowest terms. The numerator contains the
sign; the denominator is always positive.

Operations on `Rational` objects are `constexpr` if the required operations on
the underlying integer type are, and strings are not involved. Because of
this conditionality, individual functions are not labelled as `constexpr`
here.

```c++
using integer_type = T;
```

The underlying integer type.

```c++
Rational::Rational();
```

The default constructor sets the value to zero.

```c++
Rational::Rational(const T& t);
```

Sets the rational's value to an integer.

```c++
Rational::Rational(const T& n, const T& d);
```

Sets the rational's value from a numerator and denominator. Behaviour is
undefined if the denominator is zero.

```c++
Rational::Rational(const T& i, const T& n, const T& d);
```

Sets the rational's value from a mixed fraction consisting of an integer, a
numerator, and a denominator. Following the usual way mixed fractions are
written, the sign of the numerator will be reversed if the integer part is
negative (e.g. `Rational(-1,2,3)` is interpreted as -1 2/3 or -5/3).
Behaviour is undefined if the denominator is zero.

```c++
explicit Rational::Rational(std::string_view str);
```

This constructor parses the string representation of a rational number. The
input can be an integer, a simple fraction such as `"9/4",` or a mixed
fraction such as `"2 1/4".` This will throw `std::invalid_argument` if the
argument is not a valid rational number. Behaviour is undefined if the string
is a valid rational expression that contains values outside the range of the
underlying integer type.

```c++
T Rational::num() const;
T Rational::den() const;
```

These return the numerator and denominator.

```c++
explicit Rational::operator bool() const noexcept;
bool Rational::operator!() const noexcept;
```

Boolean conversions. These follow the usual convention that any non-zero value
is true.

```c++
Rational Rational::operator+() const;
Rational Rational::operator-() const;
Rational& Rational::operator+=(const Rational& y);
Rational& Rational::operator-=(const Rational& y);
Rational& Rational::operator*=(const Rational& y);
Rational& Rational::operator/=(const Rational& y);
Rational operator+(const Rational& x, const Rational& y);
Rational operator-(const Rational& x, const Rational& y);
Rational operator*(const Rational& x, const Rational& y);
Rational operator/(const Rational& x, const Rational& y);
```

Arithmetic operators. These all have their usual meanings. Behaviour is
undefined on division by zero, or if the result of an arithmetic operation
would be out of range for the underlying integer type.

```c++
bool operator==(const Rational& x, const Rational& y) noexcept;
bool operator!=(const Rational& x, const Rational& y) noexcept;
bool operator<(const Rational& x, const Rational& y) noexcept;
bool operator>(const Rational& x, const Rational& y) noexcept;
bool operator<=(const Rational& x, const Rational& y) noexcept;
bool operator>=(const Rational& x, const Rational& y) noexcept;
std::strong_ordering operator<=>(const Rational& x, const Rational& y) noexcept;
```

Comparison operators.

```c++
Rational Rational::abs() const;
```

Returns the absolute value of the rational number.

```c++
int sign() const noexcept;
```

Returns the sign of the rational number (-1 if negative, 0 if zero, +1 if
positive).

```c++
T Rational::whole() const;
Rational Rational::fraction() const;
```

These split a rational into a whole and fractional part. The whole part is
rounded toward negative infinity; if the original value is not an integer,
the fractional part will always be positive.

```c++
T Rational::truncate() const;
Rational Rational::signed_fraction() const;
```

These also split a rational into a whole and fractional part, but with
truncation toward zero. If the original value is not an integer, the
fractional part will have the same sign as the original rational number.

```c++
std::size_t Rational::hash() const noexcept;
```

Hash function.

```c++
std::string str() const;
std::string mixed() const;
```

Format a rational number as a string, either as a simple fraction or a mixed
fraction (both will return a single number if the value is an integer).

```c++
static std::optional<Rational> parse(std::string_view str);
```

Parses a string into a rational number. This works the same way as the
constructor that takes a string argument, except that an invalid argument
will result in a null optional instead of an exception.

## Specializations

```c++
template <typename T, typename U> struct std::common_type<Rational<T>, U>;
template <typename T, typename U> struct std::common_type<T, Rational<U>>;
```

Common types. The common type of two `Rational` instances is a rational based
on the common type of their underlying integer types. The common type of a
`Rational` and any other type is a rational based on the common type of the
rational's integer type and the other type; if this underlying common type is
not an integer or rational type, the rational and the second type have no
common type.

```c++
struct std::formatter<Rational>;
```

The formatter recognizes only one flag, `'m'` causing the value to be
formatted as a mixed fraction instead of a vulgar fraction.

```c++
struct std::hash<Rational>;
```

Hash function.

```c++
class std::numeric_limits<Rational>;
```

Numeric limits.
