# Fixed Size Unsigned Integers

_[Core utility library by Ross Smith](index.html)_

```c++
#include "rs-core/bitwise-integer.hpp"
namespace RS;
```

## Contents

* TOC
{:toc}

## Fixed size integer classes

```c++
template <std::size_t N> class SmallUint;
template <std::size_t N> class LargeUint;
template <std::size_t N> using Uint =
    [SmallUint if N<=64, otherwise LargeUint];
```

All of these classes represent unsigned integers with `N` bits. `SmallUint`
stores its value in a single native integer of an appropriate size;
`LargeUint` uses an array of integers, in little endian order. Normally you
should just use the `Uint` alias; nearly all of the functions described below
are common to both templates (except that, where a function is documented as
taking a `Uint` argument by value, usually the `LargeUint` version actually
takes its argument by reference).

```c++
template <typename T> concept SmallUintInstance;
template <typename T> concept LargeUintInstance;
template <typename T> concept UintInstance;
```

Concepts that match any instantiation of one or both templates.

```c++
using Uint128 = Uint<128>;
using Uint256 = Uint<256>;
using Uint512 = Uint<512>;
using Uint1024 = Uint<1024>;
```

Defined for convenience.

```c++
using uint128_t = [see below];
```

This is defined to be the native 128-bit unsigned integer type if one exists,
otherwise as an alias for `Uint128.`

```c++
constexpr auto max128 = ~ uint128_t{0};
```

The maximum value of the native (if possible) 128-bit type.

```c++
using Uint::word_type = [see below];
```

The data type used in the class's internal storage. For `SmallUint` this is
the smallest fixed size integer type with at least `N` bits. For `LargeUint`
this is always `std::uint32_t.`

```c++
static constexpr std::size_t Uint::bits = N;
static constexpr std::size_t Uint::bytes = [total bytes in representation];
static constexpr std::size_t Uint::hex_digits = [maximum hex digits in value];
```

Member constants.

```c++
constexpr Uint::Uint() noexcept;
```

The default constructor sets the value to zero.

```c++
template <std::unsigned_integral T>
    requires (sizeof(T) <= N / 8)
    constexpr Uint::Uint(T t) noexcept;
template <std::unsigned_integral T>
    requires (sizeof(T) > N / 8)
    constexpr explicit Uint::Uint(T t) noexcept;
template <std::signed_integral T>
    constexpr explicit Uint::Uint(T t) noexcept;
```

Constructors from primitive integer types. These are implicit only if the type
is unsigned and is small enough that the conversion is always safe.

```c++
template <std::size_t M>
    requires (M < N)
    constexpr SmallUint::SmallUint(SmallUint<M> x) noexcept;
template <std::size_t M>
    requires (M > N)
    constexpr explicit SmallUint::SmallUint(SmallUint<M> x) noexcept;
template <std::size_t M>
    requires (M < N)
    constexpr LargeUint::LargeUint(SmallUint<M> x) noexcept;
template <std::size_t M>
    requires (M > N)
    constexpr explicit LargeUint::LargeUint(SmallUint<M> x) noexcept;
template <std::size_t M>
    requires (M < N)
    constexpr LargeUint::LargeUint(LargeUint<M> x) noexcept;
template <std::size_t M>
    requires (M > N)
    constexpr explicit LargeUint::LargeUint(LargeUint<M> x) noexcept;
```

Constructors from another `Uint` object. These are implicit only if the
argument type is smaller than the type being constructed.

```c++
constexpr explicit
    Uint::Uint(std::initializer_list<std::uint64_t> init) noexcept;
```

Constructor from a list of 64-bit integers, in big-endian order. Any excess
bits are discarded.

```c++
explicit Uint::Uint(std::string_view str, int base = 0);
```

The string constructor calls `parse()` and follows the same rules.

```c++
constexpr Uint::Uint(const Uint& x) noexcept;
constexpr Uint::Uint(Uint&& x) noexcept;
constexpr Uint::~Uint() noexcept;
constexpr Uint& Uint::operator=(const Uint& x) noexcept;
constexpr Uint& Uint::operator=(Uint&& x) noexcept;
```

Other life cycle operations.

```c++
constexpr [iterator] LargeUint::begin() noexcept;
constexpr [const iterator] LargeUint::begin() const noexcept;
constexpr [iterator] LargeUint::end() noexcept;
constexpr [const iterator] LargeUint::end() const noexcept;
constexpr LargeUint::word_type&
    LargeUint::operator[](std::size_t i) noexcept;
constexpr const LargeUint::word_type&
    LargeUint::operator[](std::size_t i) const noexcept;
```

Accessors for the internal array. The words are in little endian order. If `N`
is not a multiple of the word size, the padding bits (the unused high bits of
the last word) will always be zero when read, but behaviour is undefined if
these bits are changed through these functions.

```c++
std::string Uint::bin() const;
std::string Uint::dec() const;
std::string Uint::hex() const;
std::string Uint::to_string() const;
class std::formatter<Uint>;
```

String formatting. The `to_string()` function is a synonym for `dec()`. The
`bin()` and `hex()` functions always return a fixed number of digits, equal
to `bits` or `hex_digits` respectively, while `dec()` and `to_string()` write
only the number of digits needed, with no leading zeroes(unless the value is
zero).

The formatter calls `dec()` by default. It recognizes only two flags, `'b'` or
`'x',` calling `bin()` or `hex()` respectively.

```c++
constexpr void Uint::clear() noexcept;
```

Sets the value to zero.

```c++
constexpr unsigned char* Uint::data() noexcept;
constexpr const unsigned char* Uint::data() const noexcept;
```

Pointers to the internal representation, which will consist of a number of
bytes equal to the `bytes` constant, in little endian order.

```c++
template <Arithmetic T> constexpr bool Uint::fits_in() const noexcept;
```

True if the current value of the `Uint` will fit in a `T` without loss of
information.

```c++
constexpr std::size_t Uint::hash() const noexcept;
struct std::hash<Uint>;
```

Hash function.

```c++
constexpr std::size_t Uint::significant_bits() const noexcept;
```

Returns the number of significant bits in the value.

```c++
constexpr explicit Uint::operator bool() const noexcept;
```

True if the value is not zero.

```c++
template <Arithmetic T> constexpr explicit
    Uint::operator T() const noexcept;
template <std::size_t M> constexpr explicit
    LargeUint::operator SmallUint<M>() const noexcept;
```

Converts a bitwise integer into a standard integer or floating point type, or
another bitwise integer type. The usual arithmetic overflow rules apply if
the value is out of range for the result type. Behaviour is undefined if `T`
is a signed integer and `fits_in<T>()` is false.

```c++
Uint Uint::operator+() const noexcept;
Uint Uint::operator-() const noexcept;
Uint& Uint::operator++() noexcept;
Uint Uint::operator++(int) noexcept;
Uint& Uint::operator--() noexcept;
Uint Uint::operator--(int) noexcept;
Uint& Uint::operator+=(Uint y) noexcept;
Uint& Uint::operator-=(Uint y) noexcept;
Uint& Uint::operator*=(Uint y) noexcept;
Uint& Uint::operator/=(Uint y) noexcept;
Uint& Uint::operator%=(Uint y) noexcept;
Uint operator+(Uint x, Uint y) noexcept;
Uint operator-(Uint x, Uint y) noexcept;
Uint operator*(Uint x, Uint y) noexcept;
Uint operator/(Uint x, Uint y) noexcept;
Uint operator%(Uint x, Uint y) noexcept;
```

Arithmetic operations. Most of these just have the obvious semantics, with the
usual wraparound behaviour on overflow or underflow. For all of the division
and remainder operations, behaviour is undefined if the divisor is zero.

```c++
Uint Uint::operator~() const noexcept;
Uint& Uint::operator&=(Uint y) noexcept;
Uint& Uint::operator|=(Uint y) noexcept;
Uint& Uint::operator^=(Uint y) noexcept;
Uint& Uint::operator<<=(int y) noexcept;
Uint& Uint::operator>>=(int y) noexcept;
Uint operator&(Uint x, Uint y) noexcept;
Uint operator|(Uint x, Uint y) noexcept;
Uint operator^(Uint x, Uint y) noexcept;
Uint operator<<(Uint x, int y) noexcept;
Uint operator>>(Uint x, int y) noexcept;
Uint rotl(Uint x, int y) noexcept;
Uint rotr(Uint x, int y) noexcept;
```

Bitwise operations. These have their usual semantics. The bit count argument
to the shift and rotate operations can be any value, including out of range
or negative values; a negative shift or rotate is interpreted as a positive
one in the opposite direction.

```c++
static void Uint::divide(Uint x, Uint y, Uint& q, Uint& r) noexcept;
```

Calculates the quotient and remainder of `x/y`. Behaviour is undefined if
`y==0`.

```c++
static Uint Uint::from_double(double x) noexcept;
```

Conversion from a `double` yields the equivalent of converting the significand
exactly and then shifting by a number of bits based on the exponent.
Behaviour is undefined if the argument is negative.

```c++
static Uint Uint::max() noexcept;
```

Returns the maximum value of the type (the complement of zero).

```c++
static Uint Uint::parse(std::string_view str, int base = 0);
static bool Uint::try_parse(std::string_view str, Uint& x, int base = 0);
```

These attempt to parse a string as an unsigned integer. If the base is zero,
the `"0b"` and `"0x"` prefixes are recognized. Apostrophe delimiters are
allowed. The `parse()` function returns the parsed value, and throws
`std::invalid_argument` on failure; `try_parse()` modifies the supplied
reference and returns true on success, false on failure. Both functions will
throw `std::invalid_argument` if the base is negative, 1, or greater than
36.

```c++
bool operator==(Uint x, Uint y) noexcept;
bool operator!=(Uint x, Uint y) noexcept;
bool operator<(Uint x, Uint y) noexcept;
bool operator>(Uint x, Uint y) noexcept;
bool operator<=(Uint x, Uint y) noexcept;
bool operator>=(Uint x, Uint y) noexcept;
std::strong_ordering operator<=>(Uint x, Uint y) noexcept;
```

Comparison operators.

```c++
constexpr uint128_t make_uint128(std::uint64_t hi,
    std::uint64_t lo) noexcept;
```

Constructs a `uint128_t` from a pair of 64-bit integers. This can be used
regardless of whether `uint128_t` is an alias for `Uint<128>` or a native
type.

```c++
namespace Literals {
    Uint128 operator""_u128(const char* ptr);
    Uint256 operator""_u256(const char* ptr);
    Uint512 operator""_u512(const char* ptr);
    Uint1024 operator""_u1024(const char* ptr);
}
```

Custom literals. These perform the same parsing as the `parse()` methods.

```c++
template <std::size_t N> class std::numeric_limits<Crow::Uint<N>>;
```

Numeric limits specializations.
