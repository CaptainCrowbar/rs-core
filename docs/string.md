# String Operations

_[Core utility library by Ross Smith](index.html)_

```c++
#include "rs-core/string.hpp"
namespace RS;
```

## Contents

* TOC
{:toc}

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

```c++
constexpr bool ascii_isalnum_w(char c) noexcept;
constexpr bool ascii_isalpha_w(char c) noexcept;
constexpr bool ascii_ispunct_w(char c) noexcept;
```

These return the same results as the similarly named functions above, except
that the underscore character is counted as a letter (of neither case)
instead of a punctuation mark. (The `_w` suffix is intended to suggest a
connection with the `\w` symbol in regular expressions.)

## String manipulation functions

```c++
std::string ascii_lowercase(std::string_view str);
std::string ascii_uppercase(std::string_view str);
```

Convert case in a string. Non-ASCII bytes are copied unchanged.
