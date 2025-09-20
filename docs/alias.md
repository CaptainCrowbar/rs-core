# Hard Type Alias

_[Core utility library by Ross Smith](index.html)_

```c++
#include "rs-core/alias.hpp"
namespace RS;
```

## Contents

* TOC
{:toc}

## Supporting types

```c++
enum class AliasFlags: uint8_t {
    none,
    cross_compare,        // Define comparison operators between T and Alias
    implicit_from_alias,  // Define implicit conversion from Alias to T
    implicit_to_alias,    // Define implicit conversion from T to Alias
};
```

Bitmask enumeration for flags selecting features of the `Alias` template. All
of the usual bitwise operators are defined.

## Alias class template

```c++
template <typename T, typename Tag = void,
        AliasFlags Flags = AliasFlags::none>
    class Alias;
```

This template wrapper creates a "hard type alias" -- a new type with the same
behaviour as `T`, as far as possible in C++. The new type will usually
support all the same operators as `T`, apart from the dereference operators,
which are used to access the underlying `T` value.

Most of the member functions of `T` can be called using the arrow operator. A
few are explicitly implemented as special cases, providing direct member
functions of `Alias` (for example, if `T` has a `substr()` function, we
expect `Alias::substr()` to return another `Alias` instead of the plain `T`
that `Alias->substr()` would return).

Explicit conversion operators always exist in both directions between `T` and
`Alias<T>`, and between different instantiations of `Alias` for the same
`T`.

The second template argument, `Tag`, can be used to distinguish different
instantiations with the same underlying type. This can be any type, and does
not need to be complete; only its identity is used. When aliases from
different sources may be used together and distinguishing them is necessary,
incomplete dummy types can be created to give aliases a unique identity.

The third template argument, `Flags`, specifies optional behaviour for the
alias:

* `AliasFlags::cross_compare` -- If this is supplied, heterogeneous comparison
  operators between `Alias<T>` and `T` will be defined. By default, only
  homogeneous comparison operators are defined. This has no effect if `T` is
  not comparable.
* `AliasFlags::implicit_from_alias` -- If this is supplied, an implicit
  conversion operator from `Alias<T>` to `T` is defined. By default, this
  conversion is explicit.
* `AliasFlags::implicit_to_alias` -- If this is supplied, an implicit
  conversion constructor from `T` to `Alias<T>` is defined. By default, this
  conversion is explicit.

Combining `implicit_to_alias` and `implicit_from_alias` is legal but likely to
lead to ambiguous overload resolution issues.

Behaviour is undefined if instantiations of `Alias` exist with the same
underlying type and tag type but different flags.

### Parameter visibility

```c++
using Alias::underlying_type = T;
using Alias::tag_type = Tag;
```

Member types.

```c++
static constexpr AliasFlags Alias::flags = Flags;
```

Member constants.

### Life cycle operations

```c++
Alias::Alias();
```

Default constructor. This is only defined if `T` is default constructible.

```c++
Alias::Alias(const Alias& a);
Alias& Alias::operator=(const Alias& a);
```

Copy operations. These are only defined if `T` is copyable.

```c++
Alias::Alias(Alias&& a);
Alias& Alias::operator=(Alias&& a);
```

Move operations. These are only defined if `T` is movable.

```c++
[optionally explicit] Alias::Alias(const T& t);
[optionally explicit] Alias::Alias(T&& t);
Alias& Alias::operator=(const T& t);
Alias& Alias::operator=(T&& t);
```

Conversions from a `T` to an `Alias.` Conversion constructors are always
defined, and are explicit by default; implicit conversions and assignment
operators are defined if the `implicit_to_alias` flag is present and `T` has
the necessary properties.

```c++
template <typename Tag2, AliasFlags F2>
    explicit Alias::Alias(const Alias<T, Tag2, F2>& a);
template <typename Tag2, AliasFlags F2>
    explicit Alias::Alias(Alias<T, Tag2, F2>&& a);
```

Conversion constructors between different aliases based on the same underlying
type. These are always defined if the corresponding operation on `T` is
defined, and are always explicit.

```c++
explicit Alias::Alias(TS&&... args);
```

Constructor from an arbitrary argument list. This is defined for any given
argument list if the corresponding constructor for `T` exists, and is always
explicit regardless of whether the underlying `T` constructor is explicit.

```c++
Alias::~Alias() noexcept;
```

Destructor.

### Conversion operators

```c++
[optionally explicit] Alias::operator T() const;
```

Conversion operator from an `Alias` to a `T`. This conversion operator is
always defined, and is explicit by default; an implicit conversion operator
is defined if the `implicit_from_alias` flag is present.

```c++
[optionally explicit] Alias::operator bool() const;
```

Conversion operator to `bool`. This is defined if the corresponding conversion
is defined for `T`, and will have the same explicitness.

### Access operators

```c++
T& Alias::operator*() noexcept;
const T& Alias::operator*() const noexcept;
T* Alias::operator->() noexcept;
const T* Alias::operator->() const noexcept;
```

Obtain a reference to the underlying `T` object.

### Arithmetic operators

```c++
Alias Alias::operator+() const;
Alias Alias::operator-() const;
Alias Alias::operator~() const;
Alias& Alias::operator++();
Alias Alias::operator++(int);
Alias& Alias::operator--();
Alias Alias::operator--(int);
Alias& Alias::operator+=(const Alias& a);
Alias& Alias::operator-=(const Alias& a);
Alias& Alias::operator*=(const Alias& a);
Alias& Alias::operator/=(const Alias& a);
Alias& Alias::operator%=(const Alias& a);
Alias& Alias::operator&=(const Alias& a);
Alias& Alias::operator|=(const Alias& a);
Alias& Alias::operator^=(const Alias& a);
Alias& Alias::operator<<=(int i);
Alias& Alias::operator>>=(int i);
Alias operator+(const Alias& a, const Alias& b);
Alias operator-(const Alias& a, const Alias& b);
Alias operator*(const Alias& a, const Alias& b);
Alias operator/(const Alias& a, const Alias& b);
Alias operator%(const Alias& a, const Alias& b);
Alias operator&(const Alias& a, const Alias& b);
Alias operator|(const Alias& a, const Alias& b);
Alias operator^(const Alias& a, const Alias& b);
Alias operator<<(const Alias& a, int i);
Alias operator>>(const Alias& a, int i);
```

Arithmetic operators. Each of these is defined if the corresponding operator
is defined for `T`. Only homogeneous operators are defined, except for the
bitwise shift operators.

### Comparison operators

```c++
bool operator==(const Alias& a, const Alias& b);
bool operator!=(const Alias& a, const Alias& b);
bool operator<(const Alias& a, const Alias& b);
bool operator>(const Alias& a, const Alias& b);
bool operator<=(const Alias& a, const Alias& b);
bool operator>=(const Alias& a, const Alias& b);
[comparison type] operator<=>(const Alias& a, const Alias& b);
```

Homogeneous comparison operators. Each of these is defined if the
corresponding operator is defined for `T`. The three way comparison operator
returns the same type as the corresponding operator for `T`.

```c++
bool operator==(const Alias& a, const T& t);
bool operator==(const T& t, const Alias& a);
bool operator!=(const Alias& a, const T& t);
bool operator!=(const T& t, const Alias& a);
bool operator<(const Alias& a, const T& t);
bool operator<(const T& t, const Alias& a);
bool operator>(const Alias& a, const T& t);
bool operator>(const T& t, const Alias& a);
bool operator<=(const Alias& a, const T& t);
bool operator<=(const T& t, const Alias& a);
bool operator>=(const Alias& a, const T& t);
bool operator>=(const T& t, const Alias& a);
[comparison type] operator<=>(const Alias& a, const T& t);
[comparison type] operator<=>(const T& t, const Alias& a);
```

Heterogeneous comparison operators. Each of these is defined if the
`cross_compare` flag is present and the corresponding operator is defined for
`T`.

### Range access

```c++
[value type]& Alias::operator[](std::size_t i);
const [value type]& Alias::operator[](std::size_t i) const;
[value type] Alias::operator[](std::size_t i) const;
```

Indexing operator. Defined if the corresponding operator for `T` is defined.
The `const` version can return either a reference or a value, whichever is
returned by the underlying operator.

```c++
[iterator] Alias::begin();
[iterator] Alias::begin() const;
[iterator or sentinel] Alias::end();
[iterator or sentinel] Alias::end() const;
```

Range access functions. Defined if `std::ranges::begin/end(T)` are defined,
and returning the same type as those functions.

```c++
bool Alias::empty() const;
std::size_t Alias::size() const;
```

Range property functions. Defined if `std::ranges::empty/size(T)` are valid.

### String functions

```c++
Alias Alias::substr(std::size_t pos, std::size_t len = npos) const;
```

Defined if `T::substr()` is defined and returns a `T` or a type convertible to
it. This returns an `Alias` wrapped around the substring, instead of the raw
`T` substring that `Alias->substr()` would return.

### Formatting functions

```c++
struct std::formatter<Alias>;
```

Standard formatter. This is defined if `std::formatter<T>` is defined, and
accepts the same formatting flags.

### Hash functions

```c++
class std::hash<Alias>;
```

Hash functions This is defined if `std::hash<T>` is defined, and returns the
same value.
