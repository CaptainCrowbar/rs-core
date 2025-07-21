# Random Number Generators

_[Core utility library by Ross Smith](index.html)_

```c++
#include "rs-core/random.hpp"
namespace RS;
```

## Contents

* TOC
{:toc}

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
constexpr Pcg::~Pcg() noexcept;
constexpr Pcg::Pcg(const Pcg& p) noexcept;
constexpr Pcg::Pcg(Pcg&& p) noexcept;
constexpr Pcg& Pcg::operator=(const Pcg& p) noexcept;
constexpr Pcg& Pcg::operator=(Pcg&& p) noexcept;
```

Other life cycle functions.

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

### Uniform integer distribution

```c++
template <std::integral T>
class UniformInteger {
    using result_type = T;
    UniformInteger() noexcept;
    explicit UniformInteger(T range) noexcept;
    explicit UniformInteger(T min, T max) noexcept;
    UniformInteger(const UniformInteger& ui) noexcept;
    UniformInteger(UniformInteger&& ui) noexcept;
    ~UniformInteger() noexcept;
    UniformInteger& operator=(const UniformInteger& ui) noexcept;
    UniformInteger& operator=(UniformInteger&& ui) noexcept;
    template <std::uniform_random_bit_generator RNG>
        T operator()(RNG& rng) const;
    T min() const noexcept;
    T max() const noexcept;
};
```

This is functionally the same as `std::uniform_int_distribution,` except that
the function call operator is `const,` and that this will provide predictable
results on different C++ implementations.

The default constructor generates values from zero to the maximum positive
value of `T.` The second generates values from zero to `range-1;` behaviour
is undefined if `range<1.` The third generates numbers from `min` to `max`
inclusive; the bounds will be swapped if they are in the wrong order.

### Uniform floating point distribution

```c++
template <std::floating_point T>
class UniformReal {
    using result_type = T;
    UniformReal() noexcept;
    explicit UniformReal(T range) noexcept;
    explicit UniformReal(T min, T max) noexcept;
    UniformReal(const UniformReal& ur) noexcept;
    UniformReal(UniformReal&& ur) noexcept;
    ~UniformReal() noexcept;
    UniformReal& operator=(const UniformReal& ur) noexcept;
    UniformReal& operator=(UniformReal&& ur) noexcept;
    template <std::uniform_random_bit_generator RNG>
        T operator()(RNG& rng) const;
    T min() const noexcept;
    T max() const noexcept;
};
```

This is functionally the same as `std::uniform_real_distribution,` except that
the function call operator is `const.` This uses the same algorithm
regardless of the standard C++ implementation, but cannot guarantee
predictable results because of nondeterministic floating point arithmetic.

The default constructor generates values from 0 to 1. The second generates
values from zero to `range;` in this case `range` may be negative. The third
generates numbers from `min` to `max;` the bounds will be swapped if they are
in the wrong order.

In all cases (except a degenerate range that always returns the same value),
it is unspecified whether or not values exactly equal to either of the bounds
can be returned.

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
    RandomChoice(const RandomChoice& rc);
    RandomChoice(RandomChoice&& rc) noexcept;
    ~RandomChoice() noexcept;
    RandomChoice& operator=(const RandomChoice& rc);
    RandomChoice& operator=(RandomChoice&& rc) noexcept;
    template <std::uniform_random_bit_generator RNG>
        const T& operator()(RNG& rng) const;
    void insert(const T& t);
    std::size_t size() const noexcept;
    bool empty() const noexcept;
};
```

Selects a random item from the supplied list. The items can be supplied to the
constructor as an explicit list or a range (which will be copied), or one at
a time through the `insert()` function.

The `size()` function returns the number of items in the list (note that this
may include duplicates). Behaviour is undefined if the function call operator
is called on an empty list.

### Weighted choice class

```c++
template <std::regular T, typename W = int>
requires std::integral<W> || std::floating_point<W>
class WeightedChoice {
    using result_type = T;
    using weight_type = W;
    WeightedChoice();
    WeightedChoice(std::initializer_list<std::pair<T, W>> list);
    WeightedChoice(const WeightedChoice& wc);
    WeightedChoice(WeightedChoice&& wc) noexcept;
    ~WeightedChoice() noexcept;
    WeightedChoice& operator=(const WeightedChoice& wc);
    WeightedChoice& operator=(WeightedChoice&& wc) noexcept;
    template <std::uniform_random_bit_generator RNG>
        const T& operator()(RNG& rng) const;
    void insert(const T& t, W w);
    std::size_t size() const noexcept;
    bool empty() const noexcept;
};
```

Selects a random item from a list of values and weights. The value-weight
pairs can be supplied to the constructor as an explicit list of pairs, or one
at a time through the `insert()` function. Pairs with a weight less than or
equal to zero are discarded.

The `size()` function returns the number of items in the list (note that this
may include duplicate `T` values). Entries that were discarded because the
weight was not positive are not counted. Behaviour is undefined if the
function call operator is called on an empty list.
