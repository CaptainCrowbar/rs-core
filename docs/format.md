# Format helpers

_[Core utility library by Ross Smith](index.html)_

```c++
#include "rs-core/alias.hpp"
namespace RS;
```

## Contents

* TOC
{:toc}

## Type agnostic formatter base class

```c++
struct CommonFormatter;
```

Base class providing some helper functions for writing custom type
formatters.

```c++
template <typename ParseContext> constexpr [output iterator]
    CommonFormatter::parse(ParseContext& ctx);
```

The base class supplies a trivial `parse()` function that does not recognize
any formatting codes.

```c++
template <typename ParseContext>
    constexpr [output iterator] CommonFormatter::parse_helper
    (ParseContext& ctx, std::string_view allowed_flags,
    std::string* flags = nullptr, unsigned* number = nullptr);
```

This can be used to parse formatters with simple options. To use this, give
the `formatter` specialization a string or number field, or both, and add a
trivial `parse()` function that calls this.

If the `flags` argument is non-null, any character in the format string that
is found in `allowed_flags` will be appended to the flags string. Formatting
flags must be printable ASCII characters, excluding `'}'` (which is reserved
by the standard); if the `number` argument is set, the digits are also
excluded. Characters in `allowed_flags` that are outside this range are
ignored. Parsing will fail if a character not present in `allowed_flags` is
found in the format string. The `allowed_flags` argument is ignored if
`flags` is null.

If the `number` argument is non-null, an unsigned integer value can be
included in the format string, which will be copied into the variable. The
variable will be left unchanged if no digits are found in the format string.
This will fail if the value supplied in the format string is out of range for
an `unsigned int,` or if more than one integer is present in the format
string.

```c++
protected template <std::output_iterator<char> Out> static Out
    CommonFormatter::write_out(std::string_view str, Out out);
protected template <std::output_iterator<char> Out> static Out
    CommonFormatter::write_out(char32_t c, Out out);
protected template <std::output_iterator<char> Out> static Out
    CommonFormatter::write_out(std::u32string_view str, Out out);
```

The `write_out()` functions are utilities for easily writing a string to the
formatted output. The first version copies an arbitrary byte string; it does
not check for valid UTF-8. The second and third versions will convert their
UTF-32 argument to UTF-8; invalid Unicode scalar values will be replaced with
the expansion of the standard replacement character `(U+FFFD).`

## Type specific formatter base class

```c++
template <typename T> struct BasicFormatter:
    CommonFormatter;
```

CRTP base class.

```c++
template <typename FormatContext> [output iterator]
    BasicFormatter::format(const T& t, FormatContext& ctx) const;
```

The `format()` function requires the argument type to have its own string
formatting function, and simply copies the output of that function to the
formatted output. `T` must support a `to_string()` function, which can be
either a member function or a free function.
