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
here to avoid widespread duplication. Most of the contents are
metaprogramming utilities used in the definition of more specialized classes
and functions.

Requires C++23.

## Index of headers

* [`rs-core/global.hpp` -- Global definitions](global.html)
* [`rs-core/enum.hpp` -- Enumeration helpers](enum.html)
* [`rs-core/format.hpp` -- Formatting helpers](format.html)
* [`rs-core/hash.hpp` -- Hash function helpers](hash.html)
* [`rs-core/iterator.hpp` -- Iterator helpers](iterator.html)
* [`rs-core/scope-guard.hpp` -- Scope guards](scope-guard.html)
* [`rs-core/version.hpp` -- Version information](version.html)

## Using the library

There is a `CMakeLists.txt` file, but this is usually only needed if you want
to run the unit tests. The library is header-only and can be installed simply
by copying the `rs-core` directory and the `rs-core.hpp` header (under `src`)
into somewhere on your include path. Running

```sh
cmake --build . --config Release --target install
```

will do this, or you can just copy or symlink it by hand.

To use the library, `#include` either the individual headers you want, or
`rs-core.hpp` to include all of them. No special link-time options are
needed.
