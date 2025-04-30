# Global Definitions

_[Core utilty library by Ross Smith](index.html)_

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
constexpr auto npos = ~ 0uz;
```

Defined for convenience.

## Bitmask functions

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

## Metaprogramming utilities

```c++
template <typename> constexpr bool dependent_false = false;
```

Used when the equivalent of `static_assert(false)` is needed in a dependent
context.

## Range functions

```c++
template <std::input_or_output_iterator I, std::sentinel_for<I> S>
std::ranges::subrange<I, S> as_range(std::pair<I, S> pair) noexcept {
    return std::ranges::subrange(pair.first, pair.second);
}
```

Turns an iterator pair returned by `equal_range()` into an actual range.
