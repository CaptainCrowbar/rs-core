# Dice

_[Core utility library by Ross Smith](index.html)_

```c++
#include "rs-core/dice.hpp"
namespace RS;
```

## Contents

* TOC
{:toc}

## Dice class template

```c++
template <Integral Int = int, FloatingPoint Flt = double> class Dice;
```

A `Dice` object represents a specified number of dice, each with a specified
number of faces, with faces numbered from 1 to the face count. The template
parameters are the integer type representing numbers and faces, and the
floating point type used for statistical properties such as mean and standard
deviation. Behaviour is undefined if the maximum possible value is out of
range for the integer type.

```c++
using Dice::integer_type = Int;
using Dice::real_type = Flt;
using Dice::state_type = DiceState<Int, Flt>;
using Dice::state_iterator = [see below];
```

Member types. The `DiceState` class is described below.

```c++
Dice::Dice();
explicit Dice::Dice(Int number, Int faces = 6);
```

These constructors create a set of a specified number of dice (defaulting to
1) with a specified number of faces (defaulting to 6). The constructor will
throw `length_error` if `number<0` or `faces<1.`

```c++
explicit Dice::Dice(std::string_view str);
```

This constructor parses the string representation of a set of dice. The format
always contains the letter `'D'` or `'d',` optionally preceded by an integer
representing the number of dice (defaulting to 1), and optionally followed by
an integer representing the number of faces (defaulting to 6). This will
throw `invalid_argument` if the argument is not a valid string
representation.

```c++
Dice::~Dice() noexcept;
Dice::Dice(const Dice& d);
Dice::Dice(Dice&& d) noexcept;
Dice& Dice::operator=(const Dice& d);
Dice& Dice::operator=(Dice&& d) noexcept;
```

Other life cycle operations.

```c++
template <std::uniform_random_bit_generator RNG>
    Int Dice::operator()(RNG& rng) const;
```

Generates the result of rolling the dice.

```c++
Int Dice::number() const noexcept;
Int Dice::faces() const noexcept;
```

The number of dice and the number of faces on each.

```c++
Int Dice::min() const noexcept;
Int Dice::max() const noexcept;
```

The minimum and maximum possible results.

```c++
Flt Dice::mean() const noexcept;
Flt Dice::sd() const noexcept;
Flt Dice::variance() const noexcept;
```

The mean and standard deviation.

```c++
Flt Dice::pdf(Int x) const;
Flt Dice::cdf(Int x) const;
Flt Dice::ccdf(Int x) const;
```

These functions calculate the probability density function, cumulative density
function, and complementary cumulative density function. These correspond
respectively to the probability of generating a result exactly equal to `x,`
less than or equal to `x,` and greater than or equal to `x.`

```c++
[state_iterator range] Dice::states() const;
```

Forward iterators over a list of possible states of the dice. The `DiceState`
class is described below.

```c++
bool operator==(const Dice& a, const Dice& b) noexcept;
bool operator!=(const Dice& a, const Dice& b) noexcept;
```

Comparison operators.

```c++
struct std::formatter<Dice>;
```

The formatter returns conventional dice notation, e.g. `"3d6"`. The following
formatting flags are supported:

* `D` = Use a capital `D`
* `p` = Leave out the prefix if it is 1
* `s` = Leave out the suffix if it is 6

## DiceState class template

```c++
template <Integral Int, FloatingPoint Flt> class DiceState;
```

This represents one possible result of rolling a set of dice, containing a
list of the faces showing on each. The order of individual dice is not
important. For example, the result of rolling `3d6` has 56 possible states:

    [1,1,1]
    [1,1,2]
    [1,1,3]
    ...
    [5,5,6]
    [5,6,6]
    [6,6,6]

A set of dice can be viewed either as a sequence of integers, or as a sequence
of `(value,count)` pairs:

    [1:3]
    [1:2,2:1]
    [1:2,3:1]
    ...
    [5:2,6:1]
    [5:1,6:2]
    [6:3]

Either view can be iterated in ascending or descending order.

This type should not normally be constructed directly by user code; instead it
should be accessed through the `Dice::state_iterator` type.

```c++
using DiceState::integer_type = Int;
using DiceState::real_type = Flt;
```

Member types.

```c++
struct DiceState::group_type {
    Int value;
    Int count;
};
```

Structure representing a group of equal values.

```c++
Int DiceState::number() const;
Int DiceState::faces() const;
```

The dice and face counts from the generating dice set.

```c++
Int DiceState::count(Int x) const;
```

Returns the number of values equal to `x` (i.e. the number of dice showing
`x`) in the current state.

```c++
Int DiceState::sum() const;
```

Returns the sum of the dice in the current state.

```c++
Flt DiceState::probability() const;
```

Returns the probability of the current state.

```c++
[range type] asc() const;
[range type] desc() const;
```

These ranges iterate over the individual results, in ascending or descending
order.

```c++
[range type] asc_groups() const;
[range type] desc_groups() const;
```

These ranges iterate over the grouped results, in ascending or descending
order. An iterator dereferences to the `group_type` structure.

```c++
bool DiceState::next();
```

Advances the current object to the next state (in ascending order). If the
object is already in its final state, this will do nothing and return false.

```c++
bool operator==(const DiceState& a, const DiceState& b) noexcept;
bool operator!=(const DiceState& a, const DiceState& b) noexcept;
bool operator<(const DiceState& a, const DiceState& b) noexcept;
bool operator>(const DiceState& a, const DiceState& b) noexcept;
bool operator<=(const DiceState& a, const DiceState& b) noexcept;
bool operator>=(const DiceState& a, const DiceState& b) noexcept;
std::strong_ordering
    operator<=>(const DiceState& a, const DiceState& b) noexcept;
```

Comparison functions.

```c++
struct std::formatter<DiceState>:
```

Formats the dice state as a comma delimited list of integers, enclosed in
square brackets. If grouped output is requested, each group is written in
`"value:count"` format.

The following formatting flags are supported:

* `c` = Show counts per value (groups) instead of individual values
* `d` = Display in descending order

## DiceSet class template

```c++
template <SignedIntegral Int = int, FloatingPoint Flt = double>
    class DiceSet;
```

A `DiceSet` object represents a collection of dice of multiple sizes, each
with an optional multiplier, plus a constant added to the total of the
dice (e.g. `3d6x2+d10+5`). Note that, unlike the `Dice` class, the integer
type here must be signed. Behaviour is undefined if the maximum or minimum
possible value is out of range for the integer type.

```c++
using DiceSet::dice_type = Dice<Int, Flt>;
using DiceSet::integer_type = Int;
using DiceSet::rational_type = Rational<Int>;
using DiceSet::real_type = Flt;
```

Member types.

```c++
struct DiceSet::element_type {
    dice_type dice;
    rational_type factor;
};
```

An element of the dice set, containing a subset of identical dice and a
multiplier.

```c++
class DiceSet::iterator;
```

A random access iterator over the elements of a dice set.

```c++
DiceSet::DiceSet();
```

The default constructor creates an empty dice set that always generates a
result of zero.

```c++
DiceSet::DiceSet(rational_type r);
DiceSet::DiceSet(Int n);
```

Constructors from a constant. The new dice set contains only an offset and no
dice, and will always generate this value.

```c++
DiceSet::DiceSet(const dice_type& d);
explicit DiceSet::DiceSet(const dice_type& d, rational_type factor);
explicit DiceSet::DiceSet(Int number, Int faces, rational_type factor = 1);
```

Constructors from a set of identical dice and an optional multiplier. The
resulting dice set has a single element (unless the factor is zero).

```c++
explicit DiceSet::DiceSet(std::string_view str);
```

This constructor parses the string representation of a dice expression,
consisting of any number of subsets of identical dice, each optionally
followed by a multiplier or divisor, separated with plus or minus signs,
optionally also containing any number of constant offsets. Multiplication can
be represented by either the `'x'` or `'*'` characters. White space is
ignored. This will throw `invalid_argument` if the argument is not a valid
string representation.

```c++
DiceSet::~DiceSet() noexcept;
DiceSet::DiceSet(const DiceSet& d);
DiceSet::DiceSet(DiceSet&& d) noexcept;
DiceSet& DiceSet::operator=(const DiceSet& d);
DiceSet& DiceSet::operator=(DiceSet&& d) noexcept;
```

Other life cycle operations.

```c++
template <std::uniform_random_bit_generator RNG>
    DiceSet::rational_type DiceSet::operator()(RNG& rng) const;
```

Generates the result of rolling the dice.

```c++
DiceSet::iterator DiceSet::begin() const noexcept;
DiceSet::iterator DiceSet::end() const noexcept;
```

Iterators over the elements of the dice set.

```c++
bool DiceSet::empty() const noexcept;
```

True if the dice set contains no elements (it may still contain a constant
value).

```c++
std::size_t DiceSet::size() const noexcept;
```

The number of elements in the dice set (not counting any constant offset).

```c++
DiceSet::rational_type DiceSet::offset() const;
```

The constant offset.

```c++
DiceSet::rational_type DiceSet::min() const;
DiceSet::rational_type DiceSet::max() const;
```

The minimum and maximum possible results.

```c++
Flt DiceSet::mean() const;
Flt DiceSet::sd() const;
Flt DiceSet::variance() const;
```

The mean and standard deviation.

```c++
DiceSet operator+() const;
DiceSet operator-() const;
DiceSet& operator+=(const DiceSet& d);
DiceSet& operator+=(const dice_type& d);
DiceSet& operator+=(rational_type r);
DiceSet& operator+=(Int n);
DiceSet& operator-=(const DiceSet& d);
DiceSet& operator-=(const dice_type& d);
DiceSet& operator-=(rational_type r);
DiceSet& operator-=(Int n);
DiceSet& operator*=(rational_type r);
DiceSet& operator*=(Int n);
DiceSet& operator/=(rational_type r);
DiceSet& operator/=(Int n);
DiceSet operator+(const DiceSet& a, const DiceSet& b);
DiceSet operator+(const DiceSet& a, rational_type b);
DiceSet operator+(const DiceSet& a, Int b);
DiceSet operator+(rational_type a, const DiceSet& b);
DiceSet operator+(Int a, const DiceSet& b);
DiceSet operator-(const DiceSet& a, const DiceSet& b);
DiceSet operator-(const DiceSet& a, rational_type b);
DiceSet operator-(const DiceSet& a, Int b);
DiceSet operator-(rational_type a, const DiceSet& b);
DiceSet operator-(Int a, const DiceSet& b);
DiceSet operator*(const DiceSet& a, rational_type b);
DiceSet operator*(const DiceSet& a, Int b);
DiceSet operator*(rational_type a, const DiceSet& b);
DiceSet operator*(Int a, const DiceSet& b);
DiceSet operator/(const DiceSet& a, rational_type b);
DiceSet operator/(const DiceSet& a, Int b);
```

Arithmetic operators.

```c++
bool operator==(const DiceSet& a, const DiceSet& b) noexcept;
bool operator!=(const DiceSet& a, const DiceSet& b) noexcept;
```

Comparison operators.

```c++
struct std::formatter<DiceSet>;
```

The formatter lists the dice sets using the standard syntax, in descending
order of dice size, with the offset value at the end if it is non-zero. The
`[Dps]` formatting flags from `formatter<Dice>` are recognised, as well as
the following:

* x = Use an `x` as the multiplication symbol (default is `*`)
