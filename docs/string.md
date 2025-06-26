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

## XML/HTML Markup

The `Htag` and `Xtag` classes write an HTML or XML tag in the constructor,
then write the corresponding closing tag in the destructor. Output can go to
a string or an output file, defaulting to standard output. A default
constructed object will do nothing on construction or destruction.

The opening tag can be supplied with or without enclosing angle brackets. The
constructor does not attempt any validation of the tag's format; the output
will be nonsense if the element argument is not a valid HTML/XML tag.

If the opening tag is standalone, the text will simply be written as is, and
no closing tag will be written. Standalone tags can be identified by a
closing slash.

The `Htag` class is also aware of the
[standard HTML5 list of self closing tags](https://www.w3.org/TR/html5/syntax.html#void-elements).
This is the only difference between `Htag` and `Xtag`.

If the element string ends with one line feed, a line feed will be written
after the closing tag, but not the opening one; if it ends with two line
feeds, one will be written after both tags.

The constructors that take a file stream will throw `std::system_error` if the
stream is not open for output, or if any other I/O error occurs. Errors while
writing the closing tag are ignored.

Behaviour is undefined if the output destination (string or file stream) is
destroyed or closed while any tag attached to it still exists.

### XML element class

```c++
class Xtag {
    Xtag();
    explicit Xtag(const std::string& element);
    explicit Xtag(const std::string& element, std::string& out);
    explicit Xtag(const std::string& element, std::FILE* out);
    explicit Xtag(const std::string& element, RS::Cstdio& out);
    Xtag(Xtag&& t) noexcept;
    virtual ~Xtag() noexcept;
    Xtag& operator=(Xtag&& t) noexcept;
};
```

### HTML element class

```c++
class Htag: public Xtag {
    Htag();
    explicit Htag(const std::string& element);
    explicit Htag(const std::string& element, std::string& out);
    explicit Htag(const std::string& element, std::FILE* out);
    explicit Htag(const std::string& element, RS::Cstdio& out);
    Htag(Htag&& t) noexcept;
    virtual ~Htag() noexcept;
    Htag& operator=(Htag&& t) noexcept;
};
```
