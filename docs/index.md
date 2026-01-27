# Core Utilities Library

By Ross Smith

_[GitHub repository](https://github.com/CaptainCrowbar/rs-core)_

## Introduction

This is a set of basic utilities that I use throughout my C++ code, collected
here to avoid widespread duplication. Basically I put stuff in here when I
get tired of re-implementing it in multiple projects.

Requires C++23. Not yet tested on all compilers.

## Index of headers

* General utilities
    * [`rs-core/global.hpp` -- Global definitions](global.html)
    * [`rs-core/hash.hpp` -- Hash functions](hash.html)
    * [`rs-core/range.hpp` -- Range utilities](range.html)
    * [`rs-core/scope.hpp` -- Scope guards](scope.html)
    * [`rs-core/uuid.hpp` -- UUID class](uuid.html)
    * [`rs-core/version.hpp` -- Version information](version.html)
* I/O utilities
    * [`rs-core/io.hpp` -- I/O utilities](io.html)
    * [`rs-core/log.hpp` -- Logging](log.html)
    * [`rs-core/terminal.hpp` -- Terminal control](terminal.html)
* Mathematical utilities
    * [`rs-core/arithmetic.hpp` -- Arithmetic types and functions](arithmetic.html)
    * [`rs-core/constants.hpp` -- Physical constants](constants.html)
    * [`rs-core/linear-algebra.hpp` -- Linear algebra](linear-algebra.html)
    * [`rs-core/mp-integer.hpp` -- Multiple precision integers](mp-integer.html)
    * [`rs-core/random.hpp` -- Random number generators](random.html)
    * [`rs-core/rational.hpp` -- Rational numbers](rational.html)
    * [`rs-core/uint128.hpp` -- 129-bit integers](uint128.html)
* Text utilities
    * [`rs-core/character.hpp` -- Character functions](character.html)
    * [`rs-core/format.hpp` -- Formatting helpers](format.html)
    * [`rs-core/markup.hpp` -- Text markup](markup.html)
* Type system utilities
    * [`rs-core/alias.hpp` -- Hard type alias](alias.html)
    * [`rs-core/enum.hpp` -- Enumeration helpers](enum.html)
    * [`rs-core/iterator.hpp` -- Iterator base classes](iterator.html)
    * [`rs-core/typelist.hpp` -- Type list metaprogramming](typelist.html)
    * [`rs-core/typename.hpp` -- Type names](typename.html)

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
