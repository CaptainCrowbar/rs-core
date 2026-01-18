# Format helpers

_[Core utility library by Ross Smith](index.html)_

```c++
#include "rs-core/alias.hpp"
namespace RS;
```

## Contents

* TOC
{:toc}

## Formatter base classes

```c++
struct CommonFormatter {
public:
    template <typename ParseContext>
        constexpr [output iterator] parse(ParseContext& ctx);
protected:
    template <std::output_iterator<char> Out>
        static Out write_out(std::string_view str, Out out);
    template <std::output_iterator<char> Out>
        static Out write_out(char32_t c, Out out);
    template <std::output_iterator<char> Out>
        static Out write_out(std::u32string_view str, Out out);
};
```

Base class providing some convenience functions for writing custom type
formatters. This supplies a trivial `parse()` function that does not
recognize any formatting codes.

The `write_out()` functions are useful utilities for easily writing a string
to the formatted output. The second and third versions will convert the
argument to UTF-8. Invalid Unicode scalar values will be replaced with the
expansion of the standard replacement character `(U+FFFD).`

```c++
template <typename T> struct BasicFormatter:
CommonFormatter {
    template <typename FormatContext>
        [output iterator] format(const T& t, FormatContext& ctx) const;
};
```

CRTP base class that requires the argument type to have its own string
formatting function, and simply copies the output of that function to the
formatted output. `T` mus support either a `T::str()` member function or a
`to_string(T)` free function that returns a string.
