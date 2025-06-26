# Global Utilities

_[Core utility library by Ross Smith](index.html)_

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
