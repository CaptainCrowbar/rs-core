# Scope Guards

_[Core utility library by Ross Smith](index.html)_

```c++
#include "rs-core/scope-guard.hpp"
namespace RS;
```

## Contents

* TOC
{:toc}

## Scope guards

```c++
enum class ScopeMode: unsigned char {
    success  = 1,
    failure  = 2,
    exit     = success | failure,
};
```

This is used to control the behaviour of a scope guard:

* `success` = Invoke the callback on normal exit, but not when the scope is unwinding due to an exception
* `failure` = Invoke the callback when the scope is unwinding due to an exception, but not on normal exit
* `exit` = Invoke the callback unconditionally on destruction

```c++
template <std::invocable F, ScopeMode M> class BasicScopeGuard {
    explicit BasicScopeGuard(F&& f);
    ~BasicScopeGuard() noexcept;
    void release() noexcept;
};
```

The basic scope guard object. This is normally created using one of the
functions below rather than being explicitly constructed. The callback type
`F` must be a function object that can be called with no arguments.

Calling `release()` cancels all destructor behaviour; the callback will never
be invoked after release.

Behaviour is undefined if the callback is a null function pointer, or if the
callback's function call operator, or its copy or move constructor, throws an
exception.

```c++
template <std::invocable F> [scope guard] on_scope_success(F&& f);
template <std::invocable F> [scope guard] on_scope_failure(F&& f);
template <std::invocable F> [scope guard] on_scope_exit(F&& f);
```

These construct scope guards that will invoke their callbacks under the
appropriate conditions.
