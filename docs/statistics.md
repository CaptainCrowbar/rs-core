# Statistics

_[Core utility library by Ross Smith](index.html)_

```c++
#include "rs-core/statistics.hpp"
namespace RS;
```

## Contents

* TOC
{:toc}

## Statistics class

```c++
template <std::floating_point T = double> class Statistics;
```

A `Statistics` object keeps running statistics for one or two variables.

Member functions with an`x_` or `y_` prefix return the statistics for that
variable. The versions with no prefix are synonyms for the `x_` version, for
convenience when only one variable is being tallied.

```c++
constexpr Statistics::Statistics() noexcept;
constexpr Statistics::Statistics(const Statistics& s) noexcept;
constexpr Statistics::Statistics(Statistics&& s) noexcept;
constexpr Statistics::~Statistics() noexcept;
constexpr Statistics& Statistics::operator=(const Statistics& s) noexcept;
constexpr Statistics& Statistics::operator=(Statistics&& s) noexcept;
```

Life cycle functions.

```c++
constexpr Statistics& Statistics::operator()(T x) noexcept;
constexpr Statistics& Statistics::operator()(T x, T y) noexcept;
```

The function call operator adds a new value, or a new pair of values, to the
statistics. Calling `stats(x)` is equivalent to `stats(x,0)` but skips
redundant arithmetic.

```c++
constexpr Statistics Statistics::operator+(const Statistics& s) const noexcept;
constexpr Statistics& Statistics::operator+=(const Statistics& s) noexcept;
```

The addition operators combine sets of statistics.

```c++
constexpr void Statistics::clear() noexcept;
```

Resets all statistics to their initial empty state.

```c++
constexpr T Statistics::count() const noexcept;
constexpr std::size_t Statistics::icount() const noexcept;
```

Return the number of items entered, as an integer or floating point number.

```c++
constexpr T Statistics::min() const noexcept;
constexpr T Statistics::x_min() const noexcept;
constexpr T Statistics::y_min() const noexcept;
constexpr T Statistics::max() const noexcept;
constexpr T Statistics::x_max() const noexcept;
constexpr T Statistics::y_max() const noexcept;
```

Return the minimum and maximum values. These will return zero if `N<1`.

```c++
constexpr T Statistics::mean() const noexcept;
constexpr T Statistics::x_mean() const noexcept;
constexpr T Statistics::y_mean() const noexcept;
```

Return the mean values. These will return zero if `N<1`.

```c++
constexpr T Statistics::variance() const noexcept;
constexpr T Statistics::x_variance() const noexcept;
constexpr T Statistics::y_variance() const noexcept;
T Statistics::sd() const noexcept;
T Statistics::x_sd() const noexcept;
T Statistics::y_sd() const noexcept;
constexpr T Statistics::raw_variance() const noexcept;
constexpr T Statistics::x_raw_variance() const noexcept;
constexpr T Statistics::y_raw_variance() const noexcept;
T Statistics::raw_sd() const noexcept;
T Statistics::x_raw_sd() const noexcept;
T Statistics::y_raw_sd() const noexcept;
```

Return the sample (with Bessel correction) and population (no Bessel
correction) variance and standard deviation. The corrected measures will
return zero if `N<2`; the uncorrected measures will return zero if `N<1`.

```c++
T Statistics::skewness() const noexcept;
T Statistics::x_skewness() const noexcept;
T Statistics::y_skewness() const noexcept;
T Statistics::kurtosis() const noexcept;
T Statistics::x_kurtosis() const noexcept;
T Statistics::y_kurtosis() const noexcept;
```

Return the skewness (third standard moment) and kurtosis (Pearson's modified
fourth moment) of the sample. All of these will return zero if `N<2`.

```c++
T Statistics::r() const noexcept;
```

Returns the Pearson coefficient of correlation. This will return zero if
`N<1`.

```c++
T Statistics::a() const noexcept;
T Statistics::b() const noexcept;
T Statistics::inv_a() const noexcept;
T Statistics::inv_b() const noexcept;
```

Return the linear regression coefficients in `y=a*x+b`. The `inv_*()`
functions return the inverse coefficients in `x=a'*y+b'`. All of these will
return zero if `N<1`.
