# Numerical Interpolation

_[Core utility library by Ross Smith](index.html)_

```c++
#include "rs-core/interpolate.hpp"
namespace RS;
```

## Contents

* TOC
{:toc}

## Supporting types

```c++
enum class Lerp: unsigned char {
    linear = 0,
    log_x,
    log_y,
    log_xy = log_x | log_y,
};
```

Bitmask values used to select linear or logarithmic interpolation.

## Concepts

```c++
template <typename U, typename T, Lerp Mode>
concept InterpolateFrom = std::floating_point<U>
    || (! has_bit(Mode, Lerp::log_y) && requires (T x, U y) {
        { y + y } -> std::convertible_to<U>;
        { y - y } -> std::convertible_to<U>;
        { x * y } -> std::convertible_to<U>;
        { y * x } -> std::convertible_to<U>;
    });
```

Checks the argument type to the `interpolate()` function. Type `U` does not
have to be a floating point type unless the `log_y` flag is used. The only
requirements are that it support addition and subtraction, and that
multiplying a `T` by a `U` is supported, yielding a `U.`

(This only applies to the `interpolate()` function and the `LinearMap` class;
the other multipoint interpolation classes always require both axes to be the
same floating point type.)

## Linear interpolation over an interval

```c++
template <Lerp Mode = Lerp::linear, std::floating_point T,
        InterpolateFrom<T, Mode> U>
    constexpr U interpolate(T x1, U y1, T x2, U y2, T x3) noexcept;
```

Performs linear or logarithmic interpolation. The `Mode` argument indicates
whether interpolation should be linear or logarithmic on the X or Y axis.

Behaviour is undefined if any of the following is true:

* `x1=x2`
* The `log_x` flag is used, and `x1<=0, x2<=0,` or `x3<=0`
* The `log_y` flag is used, and `y1<=0` or `y2<=0`

## Interpolated maps

These classes perform multipoint interpolation using different algorithms. All
of them have the following behaviour in common:

* There are three constructors:
    * Default constructor, which creates an empty set of control points.
    * A constructor from an explicit initializer list of control points
      (XY pairs).
    * An explicit constructor from a range or container of control points.
* The function call operator performs interpolation.
* The `size()` function returns the number of control points; `empty
  ()` returns `size()==0.`
* The constructors will throw `std::domain_error` if there are two points with
  the same X coordinate, or if the `log_x` or `log_y` flag is used and any X
  or Y coordinate, respectively, is less than or equal to zero.
* Behaviour of the function call operator is undefined if the `log_x` flag is
  used and the argument is less than or equal to zero.

### Multipoint linear interpolation

```c++
template <std::floating_point T, typename U = T, Lerp Mode = Lerp::linear>
requires InterpolateFrom<U, T, Mode>
class LinearMap {

    using x_type = T;
    using y_type = U;

    static constexpr Lerp mode = Mode;
    static constexpr bool is_log_x = has_bit(Mode, Lerp::log_x);
    static constexpr bool is_log_y = has_bit(Mode, Lerp::log_y);

    LinearMap();
    LinearMap(std::initializer_list<std::pair<T, U>> list);
    explicit LinearMap(ReadableRange<std::pair<T, U>> auto points);

    U operator()(T x) const;
    void insert(T x, U y);
    bool empty() const noexcept;
    std::size_t size() const noexcept;

};
```

This performs piecewise linear interpolation. Values outside the set of
control points are extrapolated from the nearest end of the range.

### Lagrange polynomial interpolation

```c++
template <std::floating_point T, Lerp Mode = Lerp::linear>
class LagrangePolynomial {

    using scalar_type = T;

    static constexpr Lerp mode = Mode;
    static constexpr bool is_log_x = has_bit(Mode, Lerp::log_x);
    static constexpr bool is_log_y = has_bit(Mode, Lerp::log_y);

    LagrangePolynomial();
    LagrangePolynomial(std::initializer_list<std::pair<T, T>> list);
    explicit LagrangePolynomial(ReadableRange<std::pair<T, T>> auto points);

    T operator()(T x) const;
    bool empty() const noexcept;
    std::size_t size() const noexcept;

};
```

This performs interpolation via Lagrange polynomials.

### Cubic spline interpolation

```c++
template <std::floating_point T, Lerp Mode = Lerp::linear>
class CubicSpline {

    using scalar_type = T;

    static constexpr Lerp mode = Mode;
    static constexpr bool is_log_x = has_bit(Mode, Lerp::log_x);
    static constexpr bool is_log_y = has_bit(Mode, Lerp::log_y);

    CubicSpline();
    CubicSpline(std::initializer_list<std::pair<T, T>> list);
    explicit CubicSpline(ReadableRange<std::pair<T, T>> auto points);

    T operator()(T x) const;
    bool empty() const noexcept;
    std::size_t size() const noexcept;

};
```

This performs interpolation via cubic splines. The list or range based
constructors will throw `std::domain_error` if too few control points are
supplied (cubic splines require a minimum of 4 points).
