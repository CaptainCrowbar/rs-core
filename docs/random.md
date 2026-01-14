# Random Number Generators

_[Core utility library by Ross Smith](index.html)_

```c++
#include "rs-core/random.hpp"
namespace RS;
```

## Contents

* TOC
{:toc}

## Introduction

Several of the classes and functions here are functional duplicates of
standard library features. These are supplied here because the C++ standard
usually does not specify a particular algorithm for a given random number
distribution, only its statistical properties, and I frequently want to be
able to reliably produce the same pseudo-random sequence on different
computers and C++ implementations. This is not actually possible for floating
point distributions, because of the nondeterministic nature of floating point
arithmetic, but some floating point distributions are duplicated here anyway
because the standard versions inconveniently have a non-`const` function call
operator.

All of the random number engine and distribution classes described here are
regular value types. To save space, the boilerplate life cycle operations
common to all (copy and move constructors and assignment operators, and
destructor) are not individually documented. Their conventional signatures
and behaviour can be assumed.

## Random number engines

### PCG engine

```c++
class Pcg;
```

Implementation of the PCG64-DXSM random number engine, based on code by
[Melissa O'Neill](http://www.pcg-random.org/) and
[Tony Finch](https://dotat.at/@/2023-06-21-pcg64-dxsm.html).

```c++
using Pcg::result_type = std::uint64_t;
```

Member types.

```c++
constexpr Pcg::Pcg() noexcept;
constexpr explicit Pcg::Pcg(std::uint64_t s) noexcept;
constexpr explicit Pcg::Pcg(std::uint64_t s0, std::uint64_t s1) noexcept;
constexpr explicit Pcg::Pcg(std::uint64_t s0, std::uint64_t s1,
    std::uint64_t s2, std::uint64_t s3) noexcept;
```

Constructors from one or more seeds. The default constructor uses a standard
seed.

```c++
constexpr std::uint64_t Pcg::operator()() noexcept;
```

Random number generation operator.

```c++
constexpr void Pcg::seed(std::uint64_t s) noexcept;
constexpr void Pcg::seed(std::uint64_t s0, std::uint64_t s1) noexcept;
constexpr void Pcg::seed(std::uint64_t s0, std::uint64_t s1,
    std::uint64_t s2, std::uint64_t s3) noexcept;
```

Re-seed the generator.

```c++
constexpr static std::uint64_t Pcg::min() noexcept;
constexpr static std::uint64_t Pcg::max() noexcept;
```

Minimum and maximum values.

### RandomDevice64 engine

```c++
class RandomDevice64;
```

This performs the same function as `std::random_device` but generates 64-bit
integers instead of 32-bit.

## Random distributions

### Bernoulli distribution

```c++
class BernoulliDistribution {
    using result_type = bool;
    constexpr BernoulliDistribution() noexcept;
    constexpr explicit BernoulliDistribution(double p) noexcept;
    constexpr explicit BernoulliDistribution(std::uint64_t num,
        std::uint64_t den) noexcept;
    template <std::uniform_random_bit_generator RNG>
        constexpr bool operator()(RNG& rng) const;
    constexpr static bool min() noexcept { return false; }
    constexpr static bool max() noexcept { return true; }
};
```

This is functionally the same as `std::bernoulli_distribution,` except that
the function call operator is `const,` and that this will provide predictable
results on different C++ implementations (with a caveat noted below).

The default constructor gives a 50% chance of success. The second and third
constructors accept an explicit probability of success, expressed either as a
floating point number in the unit interval, or a fraction expressed as a
numerator and denominator. In the second and third cases the probability is
clamped to the range 0 to 1 (inclusive).

If the constructor that takes a floating point argument is used, reproducible
behaviour cannot be guaranteed because of the nondeterministic nature of
floating point arithmetic.

### Uniform integer distribution

```c++
template <Integral T>
class UniformInteger {
    using result_type = T;
    constexpr UniformInteger() noexcept;
    constexpr explicit UniformInteger(T range) noexcept;
    constexpr explicit UniformInteger(T min, T max) noexcept;
    template <std::uniform_random_bit_generator RNG>
        constexpr T operator()(RNG& rng) const;
    constexpr T min() const noexcept;
    constexpr T max() const noexcept;
};
```

This is functionally the same as `std::uniform_int_distribution,` except that
the function call operator is `const,` and that this will provide predictable
results on different C++ implementations.

The default constructor generates values from zero to the maximum positive
value of `T,` if `T` is bounded; otherwise, the resulting generator will
always return zero. The second constructor generates values from zero to
`range-1;` behaviour is undefined if `range<1.` The third constructor
generates numbers from `min` to `max` inclusive; the bounds will be swapped
if they are in the wrong order.

This uses
[Lemire's algorithm](https://lemire.me/blog/2016/06/27/a-fast-alternative-to-the-modulo-reduction/).

_TODO: The current implementation exhibits undefined behaviour if the output
range is larger than that of a 64-bit unsigned integer._

### Dice roll distribution

```c++
template <Integral T>
class Dice {
    using result_type = T;
    constexpr Dice() noexcept;
    constexpr explicit Dice(T number, T faces = 6) noexcept;
    template <std::uniform_random_bit_generator RNG>
        constexpr T operator()(RNG& rng) const;
    constexpr T min() const noexcept;
    constexpr T max() const noexcept;
    constexpr T number() const noexcept;
    constexpr T faces() const noexcept;
    double pdf(T x) const;
    double cdf(T x) const;
    double ccdf(T x) const;
};

template <Integral T> class std::formatter<Dice<T>>;
```

Generates the result of rolling `number` dice (default 1), each numbered from
1 to `faces` (default 6). Behaviour is undefined if `number<0, faces<1,` or
the maximum possible value is out of range for the return type.

The `pdf(), cdf(),` and `ccdf()` functions calculate the probability density
function, cumulative density function, and complementary cumulative density
function. These correspond respectively to the probability of generating a
result exactly equal to `x,` less than or equal to `x,` and greater than or
equal to `x.`

The formatter returns conventional dice notation, e.g. `"3d6"`.

### Uniform floating point distribution

```c++
template <std::floating_point T>
class UniformReal {
    using result_type = T;
    constexpr UniformReal() noexcept;
    constexpr explicit UniformReal(T range) noexcept;
    constexpr explicit UniformReal(T min, T max) noexcept;
    template <std::uniform_random_bit_generator RNG>
        constexpr T operator()(RNG& rng) const;
    constexpr T min() const noexcept;
    constexpr T max() const noexcept;
};
```

This is functionally the same as `std::uniform_real_distribution,` except that
the function call operator is `const.` This uses the same algorithm
regardless of the standard C++ implementation, but cannot guarantee
predictable results because of nondeterministic floating point arithmetic.

The default constructor generates values from 0 to 1. The second generates
values from zero to `range;` in this case `range` may be negative. The third
generates numbers from `min` to `max.`

If the range is degenerate (the bounds are equal), the call operator will
always return a value equal to the bounds. If the bounds differ by only one
bit in the last place, with no values between them, it will return one of the
bounds at random. Otherwise, it will never return a value exactly equal to
either of the bounds.

This uses
[Badizadegan's algorithm](https://specbranch.com/posts/fp-rand/).

_TODO: The current implementation does not fill all bits in floating point
types larger than 64 bits; in these cases it simply generates a 64-bit
result and casts to the result type._

### Normal distribution

```c++
template <std::floating_point T> class NormalDistribution {
    using result_type = T;
    constexpr NormalDistribution() noexcept;
    constexpr explicit NormalDistribution(T mean, T sd) noexcept;
    template <std::uniform_random_bit_generator RNG>
        constexpr T operator()(RNG& rng) const;
    constexpr T min() const noexcept;
    constexpr T max() const noexcept;
    constexpr T mean() const noexcept;
    constexpr T sd() const noexcept;
    T pdf(T x) const noexcept;
    T cdf(T x) const noexcept;
    T ccdf(T x) const noexcept;
    T quantile(T p) const noexcept;
    T cquantile(T q) const noexcept;
};
```

This is functionally the same as `std::normal_distribution,` except that the
function call operator is `const.` This uses the same algorithm regardless of
the standard C++ implementation, but cannot guarantee predictable results
because of nondeterministic floating point arithmetic.

The default constructor sets the mean to 0 and the standard deviation to 1. In
the second constructor, the internal standard deviation is set to the
absolute value of the `sd` argument.

The five statistics functions are:

* `pdf(x)` = Probability density function
* `cdf(x)` = Cumulative density function = Probability of a result less than `x`
* `ccdf(x)` = Complementary cumulative density function = Probability of a result greater than `x`
* `quantile(p)` = Quantile function = Value of `x` for a given value of `cdf(x).`
* `cquantile(q)` = Complementary quantile function = Value of `x` for a given value of `ccdf(x).`

For all of the statistics functions, behaviour is undefined if the standard
deviation is zero. For the quantile functions, behaviour is undefined if the
argument is less than or equal to zero or greater than or equal to 1.

### Random choice class

```c++
template <std::regular T>
class RandomChoice {
    using result_type = T;
    RandomChoice();
    RandomChoice(std::initializer_list<T> list);
    template <std::ranges::range R>
        requires std::convertible_to<std::ranges::range_value_t<R>, T>
        explicit RandomChoice(const R& r);
    template <std::uniform_random_bit_generator RNG>
        const T& operator()(RNG& rng) const;
    void insert(const T& t);
    bool empty() const noexcept;
    std::size_t size() const noexcept;
};
```

Selects a random item from the supplied list. The items can be supplied to the
constructor as an explicit list or a range (which will be copied), or one at
a time through the `insert()` function.

The `size()` function returns the number of items in the list (note that this
may include duplicates). Behaviour is undefined if the function call operator
is called on an empty list.

### Random choice function

```c++
template <std::ranges::range R, std::uniform_random_bit_generator RNG>
    [reference type] random_choice(const R& range, RNG& rng);
```

Convenience function to select an item from a range. Complexity is `O(1)` for
random access or contiguous ranges, `O(n)` for other ranges. Behaviour is
undefined if the range is empty.

### Weighted choice class

```c++
template <std::regular T, Arithmetic W = int>
class WeightedChoice {
    using result_type = T;
    using weight_type = W;
    struct entry_type {
        T value;
        W weight;
        template <std::convertible_to<T> U> entry_type(const U& u);
        template <std::convertible_to<T> U> entry_type(const U& u, W w);
    };
    WeightedChoice();
    WeightedChoice(std::initializer_list<entry_type> list);
    template <std::uniform_random_bit_generator RNG>
        const T& operator()(RNG& rng) const;
    void insert(const T& t, W w = 1);
    bool empty() const noexcept;
    std::size_t size() const noexcept;
    W total() const;
};
```

Selects a random item from a list of values and weights. The value-weight
pairs can be supplied to the constructor as an explicit list of pairs, or one
at a time through the `insert()` function. The weight defaults to 1 if not
explicitly supplied. Pairs with a zero or negative weight are discarded.

The `size()` function returns the number of items in the list (note that this
may include duplicate `T` values). The `total()` function returns the sum of
all weights. Entries that were discarded because the weight was not positive
are not counted towards `empty(), size(),` or `total().`

Behaviour is undefined if the function call operator is called on an empty
list.

## Random algorithms

```c++
template <AutoEnum E, [E or int] Min, std::uniform_random_bit_generator RNG>
    E random_enum(RNG& rng);
```

Select a random one of the possible values of an enumeration type, which must
have been defined using the `RS_ENUM()` or `RS_BITMAP()` macros. Optionally,
a minimum return value can be supplied, either as an integer or an explicit
enumeration value. If an integer is supplied, it does not need to match any
named enumeration value. If no minimum value is supplied, any of the named
values may be returned.

Behaviour is undefined if the enumeration type contains values that are out of
range for an `int` or if an explicitly supplied minimum value is greater than
the maximum named value of the enumeration type.

```c++
template <std::ranges::random_access_range R,
        std::uniform_random_bit_generator RNG>
    void shuffle(R& range, RNG& rng);
```

Shuffles an array into random order. Supplied in place of the standard
algorithm for consistent behaviour.
