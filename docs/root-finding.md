# Root Finding

_[Core utility library by Ross Smith](index.html)_

```c++
#include "rs-core/root-finding.hpp"
namespace RS;
```

## Contents

* TOC
{:toc}

## Concepts

```c++
template <typename F, typename T>
concept Endomorphism = std::invocable<F, T>
    && requires (T t, F f) {
        { f(t) } -> std::convertible_to<T>;
    };
```

A function that maps a single argument to a result of the same type.

## Root finder base class

```c++
template <std::floating_point T>
class RootFinder {
public:
    static constexpr T default_epsilon = [see below];
    static constexpr int default_limit = 1000;
    virtual ~RootFinder() noexcept;
    T solve(T y = 0, T x = 0);
    T solve(T y, T x1, T x2);
    T epsilon() const noexcept;
    void set_epsilon(T e) noexcept;
    int limit() const noexcept;
    void set_limit(int n) noexcept;
    T error() const noexcept;
    int count() const noexcept;
};
```

The abstract base class for root finding algorithms.

The `solve()` functions perform root finding, solving `f(x)=y`. These call the
virtual `do_solve()` function, which implements the actual root finding
algorithm in derived classes. For algorithms that require two initial values,
if only one is supplied, `x+1` will be used as the second initial value. For
algorithms that require only one initial value, the second one is ignored.
Implementations may throw `std::domain_error` if it is possible to detect
that the equation cannot be solved from the given initial values, but such
detection cannot be guaranteed.

The `epsilon` parameter defines the maximum error allowed before the root
finder reports success. The default epsilon is 10<sup>-4</sup> if `T` is
`float`, otherwise 10<sup>-10</sup>.

The `limit` parameter defines the maximum number of cycles of the root finding
algorithm to run before giving up and throwing an exception. The default
limit is 1000. The `solve()` functions will throw `std::range_error` if the
algorithm has not converged to within the tolerance defined by `epsilon` when
the iteration limit is reached.

The `error()` and `count()` functions retrieve the actual error (absolute
value of the difference between `f(x)` and `y`) and number of cycles for the
last call to `solve()`. Initially they will both return 0.

Behaviour is undefined if either `epsilon` or `limit` is less than or equal to
zero.

## Concrete root finders

### Bisection algorithm

```c++
template <std::floating_point T, Endomorphism<T> F>
class Bisection:
public RootFinder<T> {
    explicit Bisection(F f);
};
```

This implements the bisection algorithm to find a root of a function. The
`solve()` functions use two initial values. It will throw `std::domain_error`
if neither of the initial values is an immediate solution, and either
`x1=x2`, or `f(x1)-y` and `f(x2)-y` have the same sign.

```c++
template <std::floating_point T, Endomorphism<T> F>
    Bisection<T> bisection(F f);
```

This function can be used to construct a root finder more simply (note that
the type `T` must still be specified explicitly).

### False position algorithm

```c++
template <std::floating_point T, Endomorphism<T> F>
class FalsePosition:
public RootFinder<T> {
    explicit FalsePosition(F f);
};
```

This implements the false position algorithm to find a root of a function. The
`solve()` functions use two initial values. It will throw `std::domain_error`
if neither of the initial values is an immediate solution, and either
`x1=x2`, or `f(x1)-y` and `f(x2)-y` have the same sign.

```c++
template <std::floating_point T, Endomorphism<T> F>
    FalsePosition<T> false_position(F f);
```

This function can be used to construct a root finder more simply (note that
the type `T` must still be specified explicitly).

### Newton-Raphson algorithm

```c++
template <std::floating_point T, Endomorphism<T> F, Endomorphism<T> DF>
class NewtonRaphson: public RootFinder<T> {
    NewtonRaphson(F f, DF df);
};
```

This implements the
[Newton-Raphson algorithm](https://en.wikipedia.org/wiki/Newton%27s_method)
to find a root of a function. The arguments are the function and its
derivative (or a close approximation to it). The `solve()` functions use one
initial value.

```c++
template <std::floating_point T, Endomorphism<T> F, Endomorphism<T> DF>
    NewtonRaphson<T> newton_raphson(F f, DF df);
```

This function can be used to construct a root finder more simply (note that
the type `T` must still be specified explicitly).
