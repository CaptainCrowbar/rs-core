# Type List Metaprogramming

_[Core utility library by Ross Smith](index.html)_

```c++
#include "rs-core/typelist.hpp"
namespace RS;
```

## Contents

* TOC
{:toc}

## Introduction

Metafunctions are templates that operate on types; usually they take one or
more types as arguments and "return" another type via a member type, but
non-type template arguments and return types are also possible.

Two versions of each metafunction are supplied, one (with a name prefixed
with "Meta") that returns its result as a member type or constant, and one
(with no prefix) that evaluates directly to the resulting type or value.

Metafunctions can be divided into three categories ("Function" represents the
actual function name):

1. Metafunctions that return a type:
    * `using MetaFunction<...>::type = [result type];`
    * `using Function<...> = [result type];`
1. Metafunctions that return an integer value:
    * `constexpr [integer type] MetaFunction<...>::value = [integer value];`
    * `constexpr [integer type] Function<...> = [integer value];`
1. Predicate metafunctions that return a boolean value:
    * `constexpr bool MetaFunction<...>::value = [boolean value];`
    * `concept Function<...>`

Example:

    using SignedTypes = Typelist<short, int, long>;
    using UnsignedTypes = Typelist<unsigned short, unsigned int,
        unsigned long>;
    using IntegerTypes = Concat<SignedTypes, UnsignedTypes>;
    static constexpr auto n_types = IntegerTypes::count; // 6

In the documentation below, the following abbreviations (optionally followed
by a distinguishing integer) are used to indicate the requirements on
template parameters:

| Symbol  | Description             | Signature       |
| ------  | -----------             | ---------       |
| `T`     | Arbitrary type          |                 |
| `TS`    | Sequence of types       |                 |
| `TL`    | Instance of `Typelist`  |                 |
| `SL`    | Sorted typelist         |                 |
| `UF`    | Unary function          | `T → T`         |
| `UP`    | Unary predicate         | `T → bool`      |
| `BF`    | Binary function         | `T × T → T`     |
| `BP`    | Binary predicate        | `T × T → bool`  |
| `EP`    | Equality predicate      | `T × T → bool`  |
| `CP`    | Comparison predicate    | `T × T → bool`  |
| `N`     | Integer                 |                 |

Indexing into typelists is zero-based; functions that return an index will
return -1 to indicate failure. A comparison predicate is expected to have
less-than semantics, in the same way as the comparison predicates used for
ordering in the STL.

## Type lists ##

```c++
template <typename... TS> struct Typelist {
    static constexpr auto count = sizeof...(TS);
};
```

A template representing an arbitrary list of types. No assumptions are made
about the individual types, not even that they are complete.

```c++
using Nil = Typelist<>;
```

`Nil` is a synonym for the empty typelist.

```c++
template <typename T> concept TypelistInstance;
```

True if `T` is an instance of the `Typelist` template.

### Type list conversions

```c++
template <typename From, template <typename...> class To>
    struct MetaConvert;
template <typename From, template <typename...> class To>
    using Convert = typename MetaConvert<From, To>::type;
```

Conversion from one typelist-like template to another. The only requirements
on the `From` and `To` types is that they must be templates that take a
parameter pack of types.

## Type-valued metafunctions

### Typelist composition and decomposition

| Name                       | Returns  | Description                                      |
| ----                       | -------  | -----------                                      |
| `[Meta]Append<TL,T>`       | `TL`     | Insert T at the end of TL                        |
| `[Meta]Concat<TS...>`      | `TL`     | Concatenate typelists or types                   |
| `[Meta]Insert<STL,T,CP>`   | `TL`     | Insert T in a sorted list                        |
| `[Meta]InsertAt<TL,T,N>`   | `TL`     | Insert T at index N in TL                        |
| `[Meta]Prefix<T,TL>`       | `TL`     | Insert T at the beginning of TL                  |
| `[Meta]Repeat<T,N>`        | `TL`     | List containing N copies of T                    |
| `[Meta]RepeatList<TL,N>`   | `TL`     | Concatenate N copies of TL                       |
| `[Meta]Resize<TL,N,T>`     | `TL`     | Resize list to length N; use T for padding       |
| `[Meta]Skip<TL,N>`         | `TL`     | Discard the first N elements from TL             |
| `[Meta]Sublist<TL,N1,N2>`  | `TL`     | Discard N1 elements and return next N2 elements  |
| `[Meta]Take<TL,N>`         | `TL`     | First N elements in TL                           |

### Type selection

| Name                   | Returns  | Description                                              |
| ----                   | -------  | -----------                                              |
| `[Meta]AtIndex<TL,N>`  | `T`      | Nth element in TL; Nil if N is out of bounds             |
| `[Meta]Head<TL>`       | `T`      | First element in TL; Nil if empty                        |
| `[Meta]Last<TL>`       | `T`      | Last element in TL; Nil if empty                         |
| `[Meta]Max<TL,CP>`     | `T`      | Maximum element in TL according to CP; Nil if TL is Nil  |
| `[Meta]Min<TL,CP>`     | `T`      | Minimum element in TL according to CP; Nil if TL is Nil  |
| `[Meta]Most<TL>`       | `TL`     | All but the last element in TL; Nil if count\<2          |
| `[Meta]Tail<TL>`       | `TL`     | All but the first element in TL; Nil if count\<2         |

### Typelist transformation

| Name                             | Returns  | Description                                                    |
| ----                             | -------  | -----------                                                    |
| `[Meta]FoldLeft<TL,BF,T>`        | `T`      | Left-to-right reduce, with T as initial value                  |
| `[Meta]FoldRight<TL,BF,T>`       | `T`      | Right-to-left reduce, with T as initial value                  |
| `[Meta]FullyUnique<TL>`          | `TL`     | Drop all duplicate elements                                    |
| `[Meta]MakeSet<TL,CP>`           | `TL`     | Sort followed by Unique                                        |
| `[Meta]Map<TL,UF>`               | `TL`     | Replace each element T in TL with UF\<T\>                      |
| `[Meta]PartialReduce<TL,EP,BF>`  | `TL`     | Reduce adjacent elements matched with EP                       |
| `[Meta]Reduce<TL,BF>`            | `T`      | Left-to-right reduce, with no initial value; Nil if TL is Nil  |
| `[Meta]Remove<TL,T>`             | `TL`     | Remove all occurrences of T in TL                              |
| `[Meta]RemoveIf<TL,UP>`          | `TL`     | Remove all elements for which UP is true                       |
| `[Meta]Reverse<TL>`              | `TL`     | Reverse the order of TL                                        |
| `[Meta]Select<TL,UP>`            | `TL`     | All elements in TL for which UP is true                        |
| `[Meta]Sort<TL,CP>`              | `TL`     | Sort TL according to CP (stable sort)                          |
| `[Meta]Unique<TL>`               | `TL`     | Drop adjacent duplicate elements                               |
| `[Meta]Zip<TL1,TL2,BF>`          | `TL`     | Map each pair of elements to BF\<T1,T2\>; lengths must match   |

## Integer-valued metafunctions

| Name                       | Returns  | Description                                                     |
| ----                       | -------  | -----------                                                     |
| `[Meta]Count<TL,T>`        | `int`    | Number of times T occurs in TL                                  |
| `[Meta]CountIf<TL,UP>`     | `int`    | Number of elements in TL for which UP is true                   |
| `[Meta]CountIfNot<TL,UP>`  | `int`    | Number of elements in TL for which UP is false                  |
| `[Meta]Find<TL,T>`         | `int`    | Index of the first T in TL; -1 if not found                     |
| `[Meta]FindIf<TL,UP>`      | `int`    | Index of the first matching element in TL; -1 if not found      |
| `[Meta]FindIfNot<TL,UP>`   | `int`    | Index of the first non-matching element in TL; -1 if not found  |

## Predicate metafunctions

| Name                     | Returns  | Description                                               |
| ----                     | -------  | -----------                                               |
| `[Meta]AllOf<TL,UP>`     | `bool`   | True if all types match UP; true if TL is Nil             |
| `[Meta]AnyOf<TL,UP>`     | `bool`   | True if at least one type matches UP; false if TL is Nil  |
| `[Meta]Contains<TL,T>`   | `bool`   | True if T is in TL                                        |
| `[Meta]IsSorted<TL,CP>`  | `bool`   | True if TL is in sorted order; true if Nil                |
| `[Meta]IsUnique<TL>`     | `bool`   | True if TL contains no duplicates                         |
| `[Meta]NoneOf<TL,UP>`    | `bool`   | True if no types match UP; true if TL is Nil              |
