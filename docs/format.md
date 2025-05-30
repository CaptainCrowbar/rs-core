# Formatting Helpers

_[Core utility library by Ross Smith](index.html)_

```c++
#include "rs-core/format.hpp"
namespace RS;
```

## Contents

* TOC
{:toc}

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
