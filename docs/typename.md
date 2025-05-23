# Type Names

_[Core utility library by Ross Smith](index.html)_

```c++
#include "rs-core/typename.hpp"
namespace RS;
```

## Type names

This header provides human readable type names on compilers that don't supply
those by default (Clang and GCC). It's in a separate header because it needs
to import the `<cxxabi.h>` header.

```c++
template <typename T> std::string type_name();
```

Returns the name of the type `T`.

```c++
template <typename T> std::string type_name(T&& t);
```

Returns the name of the dynamic type of the argument.
