# Rs Core

By Ross Smith

_[GitHub repository](https://github.com/CaptainCrowbar/rs-core)_

## Overview

```c++
#include "rs-core.hpp"
namespace RS;
```

## Introduction

This is a set of basic utilities that I use throughout my C++ code, collected
here to avoid widespread duplication. Most of the contents are generic
metaprogramming utilities used in the definition of more specialized classes
and functions in specific projects.

Most of the utilities are combined into the `"rs-core/core.hpp"` header,
because I frequently use many of them together. Those that implicitly import
system headers that are not part of the C++ standard library are in separate
headers of their own, to avoid unnecessary dependencies.

Requires C++23.

## Index of headers

* [`rs-core/core.hpp` -- Core utilities](core.html)
* [`rs-core/version.hpp` -- Version information](version.html)

## Using the library

There is a `CMakeLists.txt` file, but this is usually only needed if you want
to run the unit tests. The library is header-only and can be installed simply
by copying or linking the `rs-core` directory into somewhere on your include
path. Running

```sh
cmake --build . --config Release --target install
```

will do this, or you can just copy or symlink it by hand.

To use the library, just `#include` the headers you want. No special link-time
options are needed.
