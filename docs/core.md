# Core Utilities

_[Core utility library by Ross Smith](index.html)_

```c++
#include "rs-core/core.hpp"
namespace RS;
```

## Contents

* TOC
{:toc}

## Constants

```c++
constexpr std::string_view ascii_whitespace = "\t\n\r ";
constexpr auto npos = ~ 0uz;
```

Defined for convenience.

## Arithmetic utilities

### Bitmask functions

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

### Integer literals

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

### Number parsing

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

## Character functions

```c++
constexpr bool is_ascii(char c) noexcept;
constexpr bool ascii_isalnum(char c) noexcept;   // 0-9 A-Z a-z
constexpr bool ascii_isalpha(char c) noexcept;   // A-Z a-z
constexpr bool ascii_isblank(char c) noexcept;   // HT SP
constexpr bool ascii_iscntrl(char c) noexcept;   // \x00-\x1f \x7f
constexpr bool ascii_isdigit(char c) noexcept;   // 0-9
constexpr bool ascii_isgraph(char c) noexcept;   // !-~
constexpr bool ascii_islower(char c) noexcept;   // a-z
constexpr bool ascii_isprint(char c) noexcept;   // SP-~
constexpr bool ascii_ispunct(char c) noexcept;   // !-/ :-@ [-`{-~
constexpr bool ascii_isspace(char c) noexcept;   // HT LF VT FF CR SP
constexpr bool ascii_isupper(char c) noexcept;   // A-Z
constexpr bool ascii_isxdigit(char c) noexcept;  // 0-9 A-F a-f
constexpr char ascii_tolower(char c) noexcept;
constexpr char ascii_toupper(char c) noexcept;
```

Locale independent ASCII character properties.

## Enumeration helpers

### Scoped enumeration types

```c++
#define RS_ENUM(EnumType, IntType, ...)
```

This macro defines a scoped enumeration type with a user-supplied list of
values. It also defines a few additional features around the new type:

* `const std::set<EnumType>& enum_values(EnumType)`
    * Returns a collection of all the enumeration values. This uses a dummy
      argument to identify the type (instead of a template parameter) so the
      function can be found by ADL.
* `std::string to_string(EnumType t)`
    * Returns the unqualified enumeration value name as a string.
* `std::formatter<EnumType>`
    * Formatter that calls `to_strig().`

The list of enumeration values can include explicit integer values, but the
macro does not understand values based on other identifiers or arithmetic
expressions. For example, `my_volue=0x100` is fine, but
`my_value=another_value+2` will not work.

Example:

```c++
RS_ENUM(MyEnum, int,
    alpha = 1,
    bravo,
    charlie,
)
```

This is equivalent to:

```c++
enum class MyEnum: int {
    alpha = 1,
    bravo,
    charlie,
};

const std::set<MyEnum>& enum_values(MyEnum);
std::string to_string(MyEnum t);
template <> struct std::formatter<MyEnum>;
```

### Bitmask types

```c++
#define RS_BITMASK(EnumType, IntType, ...)
```

This generates all the same features as `RS_ENUM(),` but also creates a full
set of operators that perform bitwise operations on the enumeration type:

```c++
constexpr bool operator!(EnumType t) noexcept;
constexpr EnumType operator~(EnumType t) noexcept;
constexpr EnumType operator&(EnumType t, EnumType u) noexcept;
constexpr EnumType operator|(EnumType t, EnumType u) noexcept;
constexpr EnumType operator^(EnumType t, EnumType u) noexcept;
constexpr EnumType& operator&=(EnumType& t, EnumType u) noexcept;
constexpr EnumType& operator|=(EnumType& t, EnumType u) noexcept;
constexpr EnumType& operator^=(EnumType& t, EnumType u) noexcept;
```

The version of `to_string()` generated for bitmasks will break down a
composite value into its individual named bitmask elements.

Example:

```c++
RS_BITMASK(MyBitmask, unsigned,
    none     = 0,
    alpha    = 1,
    bravo    = 2,
    charlie  = 4,
)

auto mask = MyBitmask::alpha | MyBitmask::bravo | MyBitmask::charlie;
std::println("{}", mask);
```

This will print `"alpha|bravo|charlie".`

## Formatting helpers

```c++
template <typename T> struct std::formatter<T>;
```

A formatter is automatically generated for any user defined type for which a
function named `rs_core_format()` exists. This can be a member function or a
free function in the same namespace as the UDT. It can optionally take a
formatting flags argument (a string or string view), a size argument
(an integer), or both. The return type can be a string or string view.

Any of the following signatures will be recognized (in this order of
preference):

* `[string or view] T::rs_core_format(std::string_view flags,
    std::size_t size) const;`
* `[string or view] rs_core_format(const T& t, std::string_view flags,
    std::size_t size) const;`
* `[string or view] T::rs_core_format(std::string_view flags) const;`
* `[string or view] rs_core_format(const T& t,
    std::string_view flags) const;`
* `[string or view] T::rs_core_format(std::size_t size) const;`
* `[string or view] rs_core_format(const T& t, std::size_t size) const;`
* `[string or view] T::rs_core_format() const;`
* `[string or view] rs_core_format(const T& t) const;`

If the formatting function takes a flags argument, the generated formatter
will accept any character except null, digits, or braces as part of the flags
argument; interpreting them is up to the user defined formatting function.
The flags in a formatting call are limited to a maximum of 16 bytes.

Formatting to output string types other than plain `std::string` is not
supported.

Example:

```c++
class MyClass {
    std::string str(std::string_view flags) const;
};
std::string rs_core_format(const MyClass& x, std::string_view flags) {
    return x.str(flags);
}

MyClass x;
std::println("{}", x);      // OK, generates default format
std::println("{:abc}", x);  // OK, calls x.str("abc")
std::println("{:42}", x);   // Compile error, no int argument allowed
```

## Hash functions

### Hash concepts

```c++
template <typename T> concept Hashable;
```

Matches any type for which a valid specialization of `std::hash` exists.

### Hash functions

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

## Iterator base classes

In this document:

* `I` is the iterator class being defined
* `V` is the iterator's value type
* `CV` is either `V` or `const V` depending on whether we want a mutable or constant iterator
* `i, j` are objects of the iterator type
* `v` is an object of the value type
* `n` is an integer

```c++
template <typename I> class OutputIterator;
template <typename I, typename CV> class InputIterator;
template <typename I, typename CV> class ForwardIterator;
template <typename I, typename CV> class BidirectionalIterator;
template <typename I, typename CV> class RandomAccessIterator;
template <typename I, typename CV> class ContiguousIterator;
```

These are a set of mixin classes that can be used to easily create iterators
using the CRTP pattern.

Example:

```c++
class MyIterator:
public RS::ForwardIterator<MyIterator, const int> {
public:
    const int& operator*() const;
    MyIterator& operator++();
    bool operator==(const MyIterator& i) const;
};
```

The table below shows which operations must be defined for each category of
iterator, and which are automatically generated by the mixin base class.

Mixin class                                     | Requires           | Defines
-----------                                     | --------           | -------
`OutputIterator`                                | `i=v`              | `*i ++i i++`
`InputIterator`<br>`ForwardIterator`            | `*i ++i i==j`      | `i-> i++ i!=j i<=>j`
`BidirectionalIterator`                         | `*i ++i --i i==j`  | `i-> i++ i-- i!=j i<=>j`
`RandomAccessIterator`<br>`ContiguousIterator`  | `*i i+=n i-j`      | `i-> i[n] ++i i++ --i i-- i-=n i+n n+i`<br>`i-n i==j i!=j i<j i>j i<=j i>=j i<=>j`

## Metaprogramming utilities

```c++
template <typename> constexpr bool dependent_false = false;
```

Used when the equivalent of `static_assert(false)` is needed in a dependent
context.

## Random number generators

```c++
class Pcg;
```

Implementation of the PCG64-DXSM random number engine, based on code by
[Melissa O'Neill](http://www.pcg-random.org/) and
[Tony Finch](https://dotat.at/@/2023-06-21-pcg64-dxsm.html).

```c++
using Pcg::result_type = std::uint64_t;
```

Member types.

```c++
constexpr Pcg::Pcg() noexcept;
constexpr explicit Pcg::Pcg(std::uint64_t s) noexcept;
constexpr explicit Pcg::Pcg(std::uint64_t s0, std::uint64_t s1) noexcept;
constexpr explicit Pcg::Pcg(std::uint64_t s0, std::uint64_t s1,
    std::uint64_t s2, std::uint64_t s3) noexcept;
```

Constructors from one or more seeds. The default constructor uses a standard
seed.

```c++
constexpr Pcg::~Pcg() noexcept;
constexpr Pcg::Pcg(const Pcg& p) noexcept;
constexpr Pcg::Pcg(Pcg&& p) noexcept;
constexpr Pcg& Pcg::operator=(const Pcg& p) noexcept;
constexpr Pcg& Pcg::operator=(Pcg&& p) noexcept;
```

Other life cycle functions.

```c++
constexpr std::uint64_t Pcg::operator()() noexcept;
```

Random number generation operator.

```c++
constexpr void Pcg::seed(std::uint64_t s) noexcept;
constexpr void Pcg::seed(std::uint64_t s0, std::uint64_t s1) noexcept;
constexpr void Pcg::seed(std::uint64_t s0, std::uint64_t s1,
    std::uint64_t s2, std::uint64_t s3) noexcept;
```

Re-seed the generator.

```c++
constexpr static std::uint64_t Pcg::min() noexcept;
constexpr static std::uint64_t Pcg::max() noexcept;
```

Minimum and maximum values.

## Range functions

```c++
template <std::input_or_output_iterator I, std::sentinel_for<I> S>
std::ranges::subrange<I, S> as_range(std::pair<I, S> pair) noexcept {
    return std::ranges::subrange(pair.first, pair.second);
}
```

Turns an iterator pair returned by `equal_range()` into an actual range.

## Scope guards

```c++
enum class ScopeMode: unsigned char {
    success  = 1,
    failure  = 2,
    exit     = success | failure,
};
```

This is used to control the behaviour of a scope guard:

* `success` = Invoke the callback on normal exit, but not when the scope is unwinding due to an exception
* `failure` = Invoke the callback when the scope is unwinding due to an exception, but not on normal exit
* `exit` = Invoke the callback unconditionally on destruction

```c++
template <std::invocable F, ScopeMode M> class BasicScopeGuard {
    explicit BasicScopeGuard(F&& f);
    ~BasicScopeGuard() noexcept;
    void release() noexcept;
};
```

The basic scope guard object. This is normally created using one of the
functions below rather than being explicitly constructed. The callback type
`F` must be a function object that can be called with no arguments.

Calling `release()` cancels all destructor behaviour; the callback will never
be invoked after release.

Behaviour is undefined if the callback is a null function pointer, or if the
callback's function call operator, or its copy or move constructor, throws an
exception.

```c++
template <std::invocable F> [scope guard] on_scope_success(F&& f);
template <std::invocable F> [scope guard] on_scope_failure(F&& f);
template <std::invocable F> [scope guard] on_scope_exit(F&& f);
```

These construct scope guards that will invoke their callbacks under the
appropriate conditions.

## UUID

```c++
class Uuid;
```

A class representing a 128-bit universally unique identifier.

```c++
constexpr Uuid::Uuid() noexcept;
```

The default constructor creates an all-zero UUID.

```c++
constexpr Uuid::Uuid(std::uint8_t a, std::uint8_t b, std::uint8_t c, std::uint8_t d,
    std::uint8_t e, std::uint8_t f, std::uint8_t g, std::uint8_t h,
    std::uint8_t i, std::uint8_t j, std::uint8_t k, std::uint8_t l,
    std::uint8_t m, std::uint8_t n, std::uint8_t o, std::uint8_t p) noexcept;
```

Constructor from an explicit list of bytes.

```c++
explicit Uuid::Uuid(std::string_view str);
```

Constructor from a string. The string must contain exactly 32 hex digits,
grouped in any way as long as each group contains an even number of digits.
Groups may be separated by any combination of ASCII punctuation, spaces, or
tabs; groups may be prefixed with `"0x"` (case insensitive). An empty string
is interpreted as a default constructed UUID. Otherwise, this will throw
`std::invalid_argument` if the string is not a valid UUID.

```c++
constexpr Uuid::~Uuid() noexcept;
constexpr Uuid::Uuid(const Uuid& u) noexcept;
constexpr Uuid::Uuid(Uuid&& u) noexcept;
constexpr Uuid& Uuid::operator=(const Uuid& u) noexcept;
constexpr Uuid& Uuid::operator=(Uuid&& u) noexcept;
```

Other life cycle functions.

```c++
constexpr std::uint8_t& Uuid::operator[](std::size_t i) noexcept;
constexpr const std::uint8_t& Uuid::operator[](std::size_t i) const noexcept;
```

Access to individual bytes. Behaviour is undefined if `i>=16.`

```c++
constexpr std::uint8_t* Uuid::begin() noexcept;
constexpr const std::uint8_t* Uuid::begin() const noexcept;
constexpr std::uint8_t* Uuid::end() noexcept;
constexpr const std::uint8_t* Uuid::end() const noexcept;
```

These allow iteration over the bytes in a UUID, starting with the most
significant.

```c++
constexpr std::size_t Uuid::hash() const noexcept;
struct std::hash<Uuid>;
```

Hash function.

```c++
std::string Uuid::str() const;
explicit Uuid::operator std::string() const;
struct std::formatter<Uuid>;
```

These convert the UUID to a string, in the standard format:
`"xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx".`

```c++
constexpr static Uuid Uuid::read(const void* ptr) noexcept;
```

Copies the bytes of a UUID from a block of memory. Behaviour is undefined if
the pointer is null or does not point to a valid array of at least 16 bytes.

```c++
constexpr bool operator==(const Uuid& u, const Uuid& v) noexcept;
constexpr bool operator!=(const Uuid& u, const Uuid& v) noexcept;
constexpr bool operator<(const Uuid& u, const Uuid& v) noexcept;
constexpr bool operator>(const Uuid& u, const Uuid& v) noexcept;
constexpr bool operator<=(const Uuid& u, const Uuid& v) noexcept;
constexpr bool operator>=(const Uuid& u, const Uuid& v) noexcept;
constexpr std::strong_ordering operator<=>(const Uuid& u, const Uuid& v) noexcept;
```

Comparison operators.
