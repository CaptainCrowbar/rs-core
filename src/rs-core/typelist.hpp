#pragma once

#include "rs-core/global.hpp"
#include <concepts>
#include <type_traits>

namespace RS {

    // Typelist primitives

    template <typename... TS>
    struct Typelist {
        static constexpr auto count = sizeof...(TS);
    };

    using Nil = Typelist<>;

    template <typename T>
        struct MetaTypelistInstance:
        std::false_type {};
    template <typename... TS>
        struct MetaTypelistInstance<Typelist<TS...>>:
        std::true_type {};
    template <typename T>
        concept TypelistInstance = MetaTypelistInstance<T>::value;

    template <typename From, template <typename...> class To>
        struct MetaConvert;
    template <template <typename...> class From, typename... TS, template <typename...> class To>
        struct MetaConvert<From<TS...>, To>
        { using type = To<TS...>; };
    template <typename From, template <typename...> class To>
        using Convert = typename MetaConvert<From, To>::type;

    // Typelist composition and decomposition metafunctions

    template <TypelistInstance TL, typename T>
        struct MetaAppend;
    template <typename... TS, typename T>
        struct MetaAppend<Typelist<TS...>, T>
        { using type = Typelist<TS..., T>; };
    template <typename... TS>
        struct MetaAppend<Typelist<TS...>, Nil>
        { using type = Typelist<TS...>; };
    template <TypelistInstance TL, typename T>
        using Append = typename MetaAppend<TL, T>::type;

    template <typename... TS>
        struct MetaConcat;
    template <typename T, typename... TS>
        struct MetaConcat<T, TS...>:
        MetaConcat<T, typename MetaConcat<TS...>::type> {};
    template <typename T1, typename T2>
        struct MetaConcat<T1, T2>
        { using type = Typelist<T1, T2>; };
    template <typename T, typename... TS>
        struct MetaConcat<T, Typelist<TS...>>
        { using type = Typelist<T, TS...>; };
    template <typename... TS, typename T>
        struct MetaConcat<Typelist<TS...>, T>
        { using type = Typelist<TS..., T>; };
    template <typename... TS1, typename... TS2>
        struct MetaConcat<Typelist<TS1...>, Typelist<TS2...>>
        { using type = Typelist<TS1..., TS2...>; };
    template <typename T>
        struct MetaConcat<T>
        { using type = Typelist<T>; };
    template <typename... TS>
        struct MetaConcat<Typelist<TS...>>
        { using type = Typelist<TS...>; };
    template <>
        struct MetaConcat<Nil>
        { using type = Nil; };
    template <>
        struct MetaConcat<>
        { using type = Nil; };
    template <typename... TS>
        using Concat = typename MetaConcat<TS...>::type;

    template <typename T, TypelistInstance TL>
        struct MetaPrefix;
    template <typename T, typename... TS>
        struct MetaPrefix<T, Typelist<TS...>>
        { using type = Typelist<T, TS...>; };
    template <typename T, TypelistInstance TL>
        using Prefix = typename MetaPrefix<T, TL>::type;

    template <TypelistInstance STL, typename T, template <typename, typename> class CP>
        struct MetaInsert;
    template <typename T1, typename... TS, typename T2, template <typename, typename> class CP>
        struct MetaInsert<Typelist<T1, TS...>, T2, CP>:
        std::conditional<CP<T1, T2>::value,
            Prefix<T1, typename MetaInsert<Typelist<TS...>, T2, CP>::type>,
            Typelist<T2, T1, TS...>> {};
    template <typename T, template <typename, typename> class CP>
        struct MetaInsert<Nil, T, CP>
        { using type = Typelist<T>; };
    template <TypelistInstance STL, typename T, template <typename, typename> class CP>
        using Insert = typename MetaInsert<STL, T, CP>::type;

    template <typename T, int N>
        struct MetaRepeat:
        MetaPrefix<T, typename MetaRepeat<T, N - 1>::type> {};
    template <typename T>
        struct MetaRepeat<T, 0>
        { using type = Nil; };
    template <typename T, int N>
        using Repeat = typename MetaRepeat<T, N>::type;

    template <TypelistInstance TL, int N>
        struct MetaRepeatList:
        MetaConcat<TL, typename MetaRepeatList<TL, N - 1>::type> {};
    template <TypelistInstance TL>
        struct MetaRepeatList<TL, 0>
        { using type = Nil; };
    template <TypelistInstance TL, int N>
        using RepeatList = typename MetaRepeatList<TL, N>::type;

    template <TypelistInstance TL, int N, typename T>
        struct MetaResize;
    template <typename T1, typename... TS, int N, typename T2>
        struct MetaResize<Typelist<T1, TS...>, N, T2>:
        MetaConcat<T1, typename MetaResize<Typelist<TS...>, N - 1, T2>::type> {};
    template <typename T1, typename... TS, typename T2>
        struct MetaResize<Typelist<T1, TS...>, 0, T2>
        { using type = Nil; };
    template <int N, typename T>
        struct MetaResize<Nil, N, T>:
        MetaRepeat<T, N> {};
    template <typename T>
        struct MetaResize<Nil, 0, T>
        { using type = Nil; };
    template <TypelistInstance TL, int N, typename T>
        using Resize = typename MetaResize<TL, N, T>::type;

    template <TypelistInstance TL, int N>
        struct MetaSkip;
    template <typename T, typename... TS, int N>
        struct MetaSkip<Typelist<T, TS...>, N>:
        MetaSkip<Typelist<TS...>, N - 1> {};
    template <typename T, typename... TS>
        struct MetaSkip<Typelist<T, TS...>, 0>
        { using type = Typelist<T, TS...>; };
    template <int N>
        struct MetaSkip<Nil, N>
        { using type = Nil; };
    template <>
        struct MetaSkip<Nil, 0>
        { using type = Nil; };
    template <TypelistInstance TL, int N>
        using Skip = typename MetaSkip<TL, N>::type;

    template <TypelistInstance TL, int N>
        struct MetaTake;
    template <typename T, typename... TS, int N>
        struct MetaTake<Typelist<T, TS...>, N>:
        MetaConcat<T, typename MetaTake<Typelist<TS...>, N - 1>::type> {};
    template <typename T, typename... TS>
        struct MetaTake<Typelist<T, TS...>, 0>
        { using type = Nil; };
    template <int N>
        struct MetaTake<Nil, N>
        { using type = Nil; };
    template <>
        struct MetaTake<Nil, 0>
        { using type = Nil; };
    template <TypelistInstance TL, int N>
        using Take = typename MetaTake<TL, N>::type;

    template <TypelistInstance TL, typename T, int N>
        struct MetaInsertAt:
        MetaConcat<typename MetaTake<TL, (N < 1 ? 0 : N)>::type, T,
            typename MetaSkip<TL, (N < 1 ? 0 : N)>::type> {};
    template <TypelistInstance TL, typename T, int N>
        using InsertAt = typename MetaInsertAt<TL, T, N>::type;

    template <TypelistInstance TL, int N1, int N2>
        struct MetaSublist:
        MetaTake<typename MetaSkip<TL, N1>::type, N2> {};
    template <TypelistInstance TL, int N1, int N2>
        using Sublist = typename MetaSublist<TL, N1, N2>::type;

    // Type selection metafunctions

    template <TypelistInstance TL, int N>
        struct MetaAtIndex;
    template <typename T, typename... TS, int N>
        struct MetaAtIndex<Typelist<T, TS...>, N>:
        MetaAtIndex<Typelist<TS...>, (N > 0 ? N - 1 : -1)> {};
    template <typename T, typename... TS>
        struct MetaAtIndex<Typelist<T, TS...>, 0>
        { using type = T; };
    template <typename T, typename... TS>
        struct MetaAtIndex<Typelist<T, TS...>, -1>
        { using type = Nil; };
    template <int N>
        struct MetaAtIndex<Nil, N>
        { using type = Nil; };
    template <TypelistInstance TL, int N>
        using AtIndex = typename MetaAtIndex<TL, N>::type;

    template <TypelistInstance TL>
        struct MetaHead;
    template <typename T, typename... TS>
        struct MetaHead<Typelist<T, TS...>> { using type = T; };
    template <>
        struct MetaHead<Nil> { using type = Nil; };
    template <TypelistInstance TL>
        using Head = typename MetaHead<TL>::type;

    template <TypelistInstance TL>
        struct MetaTail;
    template <typename T, typename... TS>
        struct MetaTail<Typelist<T, TS...>> { using type = Typelist<TS...>; };
    template <>
        struct MetaTail<Nil> { using type = Nil; };
    template <TypelistInstance TL>
        using Tail = typename MetaTail<TL>::type;

    template <TypelistInstance TL>
        struct MetaMost;
    template <typename T, typename... TS>
        struct MetaMost<Typelist<T, TS...>>:
        MetaPrefix<T, typename MetaMost<Typelist<TS...>>::type> {};
    template <typename T>
        struct MetaMost<Typelist<T>>
        { using type = Nil; };
    template <>
        struct MetaMost<Nil>
        { using type = Nil; };
    template <TypelistInstance TL>
        using Most = typename MetaMost<TL>::type;

    template <TypelistInstance TL>
        struct MetaLast;
    template <typename T, typename... TS>
        struct MetaLast<Typelist<T, TS...>>:
        MetaLast<Typelist<TS...>> {};
    template <typename T>
        struct MetaLast<Typelist<T>>
        { using type = T; };
    template <>
        struct MetaLast<Nil>
        { using type = Nil; };
    template <TypelistInstance TL>
        using Last = typename MetaLast<TL>::type;

    template <TypelistInstance TL, template <typename, typename> class CP>
        struct MetaMax;
    template <typename T, typename... TS, template <typename, typename> class CP>
        struct MetaMax<Typelist<T, TS...>, CP>:
        MetaMax<Typelist<T, typename MetaMax<Typelist<TS...>, CP>::type>, CP> {};
    template <typename T1, typename T2, template <typename, typename> class CP>
        struct MetaMax<Typelist<T1, T2>, CP>:
        std::conditional<CP<T1, T2>::value, T2, T1> {};
    template <typename T, template <typename, typename> class CP>
        struct MetaMax<Typelist<T>, CP>
        { using type = T; };
    template <template <typename, typename> class CP>
        struct MetaMax<Nil, CP>
        { using type = Nil; };
    template <TypelistInstance TL, template <typename, typename> class CP>
        using Max = typename MetaMax<TL, CP>::type;

    template <TypelistInstance TL, template <typename, typename> class CP>
        struct MetaMin;
    template <typename T, typename... TS, template <typename, typename> class CP>
        struct MetaMin<Typelist<T, TS...>, CP>:
        MetaMin<Typelist<T, typename MetaMin<Typelist<TS...>, CP>::type>, CP> {};
    template <typename T1, typename T2, template <typename, typename> class CP>
        struct MetaMin<Typelist<T1, T2>, CP>:
        std::conditional<CP<T1, T2>::value, T1, T2> {};
    template <typename T, template <typename, typename> class CP>
        struct MetaMin<Typelist<T>, CP>
        { using type = T; };
    template <template <typename, typename> class CP>
        struct MetaMin<Nil, CP>
        { using type = Nil; };
    template <TypelistInstance TL, template <typename, typename> class CP>
        using Min = typename MetaMin<TL, CP>::type;

    // Typelist transformation metafunctions

    template <TypelistInstance TL, template <typename, typename> class BF, typename T>
        struct MetaFoldLeft;
    template <typename T1, typename... TS, template <typename, typename> class BF, typename T2>
        struct MetaFoldLeft<Typelist<T1, TS...>, BF, T2>:
        MetaFoldLeft<Typelist<TS...>, BF, BF<T2, T1>> {};
    template <template <typename, typename> class BF, typename T>
        struct MetaFoldLeft<Nil, BF, T>
        { using type = T; };
    template <TypelistInstance TL, template <typename, typename> class BF, typename T>
        using FoldLeft = typename MetaFoldLeft<TL, BF, T>::type;

    template <TypelistInstance TL, template <typename, typename> class BF, typename T>
        struct MetaFoldRight;
    template <typename T1, typename... TS, template <typename, typename> class BF, typename T2>
        struct MetaFoldRight<Typelist<T1, TS...>, BF, T2>:
        MetaFoldRight<typename MetaMost<Typelist<T1, TS...>>::type, BF,
            BF<typename MetaLast<Typelist<T1, TS...>>::type, T2>> {};
    template <template <typename, typename> class BF, typename T>
        struct MetaFoldRight<Nil, BF, T>
        { using type = T; };
    template <TypelistInstance TL, template <typename, typename> class BF, typename T>
        using FoldRight = typename MetaFoldRight<TL, BF, T>::type;

    template <TypelistInstance TL, template <typename> class UF>
        struct MetaMap;
    template <typename T, typename... TS, template <typename> class UF>
        struct MetaMap<Typelist<T, TS...>, UF>:
        MetaPrefix<UF<T>, typename MetaMap<Typelist<TS...>, UF>::type> {};
    template <template <typename> class UF>
        struct MetaMap<Nil, UF> { using type = Nil; };
    template <TypelistInstance TL, template <typename> class UF>
        using Map = typename MetaMap<TL, UF>::type;

    template <TypelistInstance TL, template <typename, typename> class EP,
            template <typename, typename> class BF>
        struct MetaPartialReduce;
    template <typename T1, typename T2, template <typename, typename> class EP,
            template <typename, typename> class BF, bool Match, typename... TS>
        struct PartialReduceHelper:
        MetaPartialReduce<Typelist<BF<T1, T2>, TS...>, EP, BF> {};
    template <typename T1, typename T2, template <typename, typename> class EP,
            template <typename, typename> class BF, typename... TS>
        struct PartialReduceHelper<T1, T2, EP, BF, false, TS...>:
        MetaPrefix<T1, typename MetaPartialReduce<Typelist<T2, TS...>, EP, BF>::type> {};
    template <typename T1, typename T2, typename... TS, template <typename, typename> class EP,
            template <typename, typename> class BF>
        struct MetaPartialReduce<Typelist<T1, T2, TS...>, EP, BF>:
        PartialReduceHelper<T1, T2, EP, BF, EP<T1, T2>::value, TS...> {};
    template <typename T, template <typename, typename> class EP,
            template <typename, typename> class BF>
        struct MetaPartialReduce<Typelist<T>, EP, BF> { using type = Typelist<T>; };
    template <template <typename, typename> class EP, template <typename, typename> class BF>
        struct MetaPartialReduce<Nil, EP, BF> { using type = Nil; };
    template <TypelistInstance TL, template <typename, typename> class EP, template <typename, typename> class BF>
        using PartialReduce = typename MetaPartialReduce<TL, EP, BF>::type;

    template <TypelistInstance TL, template <typename, typename> class BF>
        struct MetaReduce;
    template <typename T1, typename T2, typename... TS, template <typename, typename> class BF>
        struct MetaReduce<Typelist<T1, T2, TS...>, BF>:
        MetaReduce<Typelist<BF<T1, T2>, TS...>, BF> {};
    template <typename T, template <typename, typename> class BF>
        struct MetaReduce<Typelist<T>, BF>
        { using type = T; };
    template <template <typename, typename> class BF>
        struct MetaReduce<Nil, BF>
        { using type = Nil; };
    template <TypelistInstance TL, template <typename, typename> class BF>
        using Reduce = typename MetaReduce<TL, BF>::type;

    template <TypelistInstance TL, typename T>
        struct MetaRemove;
    template <typename T1, typename... TS, typename T2>
        struct MetaRemove<Typelist<T1, TS...>, T2>:
        MetaPrefix<T1, typename MetaRemove<Typelist<TS...>, T2>::type> {};
    template <typename T, typename... TS>
        struct MetaRemove<Typelist<T, TS...>, T>:
        MetaRemove<Typelist<TS...>, T> {};
    template <typename T>
        struct MetaRemove<Nil, T> { using type = Nil; };
    template <TypelistInstance TL, typename T>
        using Remove = typename MetaRemove<TL, T>::type;

    template <TypelistInstance TL, template <typename> class UP>
        struct MetaRemoveIf;
    template <typename T, typename... TS, template <typename> class UP>
        struct MetaRemoveIf<Typelist<T, TS...>, UP>:
        std::conditional<UP<T>::value, typename MetaRemoveIf<Typelist<TS...>, UP>::type,
            Prefix<T, typename MetaRemoveIf<Typelist<TS...>, UP>::type>> {};
    template <template <typename> class UP>
        struct MetaRemoveIf<Nil, UP> { using type = Nil; };
    template <TypelistInstance TL, template <typename> class UP>
        using RemoveIf = typename MetaRemoveIf<TL, UP>::type;

    template <TypelistInstance TL>
        struct MetaReverse;
    template <typename T, typename... TS>
        struct MetaReverse<Typelist<T, TS...>>:
        MetaAppend<typename MetaReverse<Typelist<TS...>>::type, T> {};
    template <typename T>
        struct MetaReverse<Typelist<T, Nil>>
        { using type = Typelist<T, Nil>; };
    template <>
        struct MetaReverse<Nil>
        { using type = Nil; };
    template <TypelistInstance TL>
        using Reverse = typename MetaReverse<TL>::type;

    template <TypelistInstance TL, template <typename> class UP>
        struct MetaSelect;
    template <typename T, typename... TS, template <typename> class UP>
        struct MetaSelect<Typelist<T, TS...>, UP>:
        std::conditional<UP<T>::value,
            Prefix<T, typename MetaSelect<Typelist<TS...>, UP>::type>,
            typename MetaSelect<Typelist<TS...>, UP>::type> {};
    template <template <typename> class UP>
        struct MetaSelect<Nil, UP>
        { using type = Nil; };
    template <TypelistInstance TL, template <typename> class UP>
        using Select = typename MetaSelect<TL, UP>::type;

    template <TypelistInstance TL, template <typename, typename> class CP>
        struct MetaSort;
    template <typename T, typename... TS, template <typename, typename> class CP>
        struct MetaSort<Typelist<T, TS...>, CP>:
        MetaInsert<typename MetaSort<Typelist<TS...>, CP>::type, T, CP> {};
    template <template <typename, typename> class CP>
        struct MetaSort<Nil, CP> { using type = Nil; };
    template <TypelistInstance TL, template <typename, typename> class CP>
        using Sort = typename MetaSort<TL, CP>::type;

    template <TypelistInstance TL>
        struct MetaUnique;
    template <typename T, typename... TS>
        struct MetaUnique<Typelist<T, T, TS...>>:
        MetaUnique<Typelist<T, TS...>> {};
    template <typename T, typename... TS>
        struct MetaUnique<Typelist<T, TS...>>:
        MetaPrefix<T, typename MetaUnique<Typelist<TS...>>::type> {};
    template <>
        struct MetaUnique<Nil>
        { using type = Nil; };
    template <TypelistInstance TL>
        using Unique = typename MetaUnique<TL>::type;

    template <TypelistInstance TL>
        struct MetaFullyUnique;
    template <typename T, typename... TS>
        struct MetaFullyUnique<Typelist<T, TS...>>
        { using type = Prefix<T,
            typename MetaFullyUnique<typename MetaRemove<Typelist<TS...>, T>::type>::type>; };
    template <>
        struct MetaFullyUnique<Nil>
        { using type = Nil; };
    template <TypelistInstance TL>
        using FullyUnique = typename MetaFullyUnique<TL>::type;

    template <TypelistInstance TL1, TypelistInstance TL2, template <typename, typename> class BF>
        requires (TL1::count == TL2::count)
        struct MetaZip;
    template <typename T1, typename... TS1, typename T2, typename... TS2,
            template <typename, typename> class BF>
        requires (sizeof...(TS1) == sizeof...(TS2))
        struct MetaZip<Typelist<T1, TS1...>, Typelist<T2, TS2...>, BF>:
        MetaPrefix<BF<T1, T2>, typename MetaZip<Typelist<TS1...>, Typelist<TS2...>, BF>::type> {};
    template <template <typename, typename> class BF>
        struct MetaZip<Nil, Nil, BF>
        { using type = Nil; };
    template <TypelistInstance TL1, TypelistInstance TL2, template <typename, typename> class BF>
        requires (TL1::count == TL2::count)
        using Zip = typename MetaZip<TL1, TL2, BF>::type;

    template <TypelistInstance TL, template <typename, typename> class CP>
        struct MetaMakeSet:
        MetaUnique<typename MetaSort<TL, CP>::type> {};
    template <TypelistInstance TL, template <typename, typename> class CP>
        using MakeSet = typename MetaMakeSet<TL, CP>::type;

    // Typelist integer metafunctions

    template <TypelistInstance TL, typename T>
        struct MetaCount;
    template <typename T1, typename... TS, typename T2>
        struct MetaCount<Typelist<T1, TS...>, T2>
        { static constexpr int value = std::is_same<T1, T2>::value
            + MetaCount<Typelist<TS...>, T2>::value; };
    template <typename T>
        struct MetaCount<Nil, T>
        { static constexpr int value = 0; };
    template <TypelistInstance TL, typename T>
        constexpr int Count = MetaCount<TL, T>::value;

    template <TypelistInstance TL, template <typename> class UP>
        struct MetaCountIf;
    template <typename T, typename... TS, template <typename> class UP>
        struct MetaCountIf<Typelist<T, TS...>, UP>
        { static constexpr int value = UP<T>::value + MetaCountIf<Typelist<TS...>, UP>::value; };
    template <template <typename> class UP>
        struct MetaCountIf<Nil, UP>
        { static constexpr int value = 0; };
    template <TypelistInstance TL, template <typename> class UP>
        constexpr int CountIf = MetaCountIf<TL, UP>::value;

    template <TypelistInstance TL, template <typename> class UP>
        struct MetaCountIfNot;
    template <typename T, typename... TS, template <typename> class UP>
        struct MetaCountIfNot<Typelist<T, TS...>, UP>
        { static constexpr int value = ! UP<T>::value + MetaCountIfNot<Typelist<TS...>, UP>::value; };
    template <template <typename> class UP>
        struct MetaCountIfNot<Nil, UP>
        { static constexpr int value = 0; };
    template <TypelistInstance TL, template <typename> class UP>
        constexpr int CountIfNot = MetaCountIfNot<TL, UP>::value;

    template <TypelistInstance TL, typename T>
        struct MetaFind;
    template <typename T1, typename... TS, typename T2>
        struct MetaFind<Typelist<T1, TS...>, T2>
        { static constexpr int value = (MetaFind<Typelist<TS...>, T2>::value >= 0) ?
            MetaFind<Typelist<TS...>, T2>::value + 1 : -1; };
    template <typename T, typename... TS>
        struct MetaFind<Typelist<T, TS...>, T>
        { static constexpr int value = 0; };
    template <typename T>
        struct MetaFind<Nil, T>
        { static constexpr int value = -1; };
    template <TypelistInstance TL, typename T>
        constexpr int Find = MetaFind<TL, T>::value;

    template <TypelistInstance TL, template <typename> class UP>
        struct MetaFindIf;
    template <typename T, typename... TS, template <typename> class UP>
        struct MetaFindIf<Typelist<T, TS...>, UP>
        { static constexpr int value = UP<T>::value ? 0 : (MetaFindIf<Typelist<TS...>, UP>::value >= 0) ?
            MetaFindIf<Typelist<TS...>, UP>::value + 1 : -1; };
    template <template <typename> class UP>
        struct MetaFindIf<Nil, UP>
        { static constexpr int value = -1; };
    template <TypelistInstance TL, template <typename> class UP>
        constexpr int FindIf = MetaFindIf<TL, UP>::value;

    template <TypelistInstance TL, template <typename> class UP>
        struct MetaFindIfNot;
    template <typename T, typename... TS, template <typename> class UP>
        struct MetaFindIfNot<Typelist<T, TS...>, UP>
        { static constexpr int value = ! UP<T>::value ? 0 : (MetaFindIfNot<Typelist<TS...>, UP>::value >= 0) ?
            MetaFindIfNot<Typelist<TS...>, UP>::value + 1 : -1; };
    template <template <typename> class UP>
        struct MetaFindIfNot<Nil, UP>
        { static constexpr int value = -1; };
    template <TypelistInstance TL, template <typename> class UP>
        constexpr int FindIfNot = MetaFindIfNot<TL, UP>::value;

    // Typelist predicate metafunctions

    template <TypelistInstance TL, template <typename> class UP>
        struct MetaAllOf;
    template <typename T, typename... TS, template <typename> class UP>
        struct MetaAllOf<Typelist<T, TS...>, UP>
        { static constexpr bool value = UP<T>::value && MetaAllOf<Typelist<TS...>, UP>::value; };
    template <template <typename> class UP>
        struct MetaAllOf<Nil, UP>: std::true_type {};
    template <typename TL, template <typename> class UP>
        concept AllOf = MetaAllOf<TL, UP>::value;

    template <TypelistInstance TL, template <typename> class UP>
        struct MetaAnyOf;
    template <typename T, typename... TS, template <typename> class UP>
        struct MetaAnyOf<Typelist<T, TS...>, UP>
        { static constexpr bool value = UP<T>::value || MetaAnyOf<Typelist<TS...>, UP>::value; };
    template <template <typename> class UP>
        struct MetaAnyOf<Nil, UP>: std::false_type {};
    template <typename TL, template <typename> class UP>
        concept AnyOf = MetaAnyOf<TL, UP>::value;

    template <TypelistInstance TL, template <typename> class UP>
        struct MetaNoneOf;
    template <typename T, typename... TS, template <typename> class UP>
        struct MetaNoneOf<Typelist<T, TS...>, UP>
        { static constexpr bool value = ! UP<T>::value && MetaNoneOf<Typelist<TS...>, UP>::value; };
    template <template <typename> class UP>
        struct MetaNoneOf<Nil, UP>: std::true_type {};
    template <typename TL, template <typename> class UP>
        concept NoneOf = MetaNoneOf<TL, UP>::value;

    template <TypelistInstance TL, typename T>
        struct MetaContains;
    template <typename T1, typename... TS, typename T2>
        struct MetaContains<Typelist<T1, TS...>, T2>:
        MetaContains<Typelist<TS...>, T2> {};
    template <typename T, typename... TS>
        struct MetaContains<Typelist<T, TS...>, T>:
        std::true_type {};
    template <typename T>
        struct MetaContains<Nil, T>:
        std::false_type {};
    template <typename TL, typename T>
        concept Contains = MetaContains<TL, T>::value;

    template <TypelistInstance TL, template <typename, typename> class CP>
        struct MetaIsSorted;
    template <template <typename, typename> class CP>
        struct MetaIsSorted<Nil, CP>: std::true_type {};
    template <typename T, template <typename, typename> class CP>
        struct MetaIsSorted<Typelist<T>, CP>: std::true_type {};
    template <typename T1, typename T2, typename... TS, template <typename, typename> class CP>
        struct MetaIsSorted<Typelist<T1, T2, TS...>, CP> {
            static constexpr bool value = ! CP<T2, T1>::value
                && MetaIsSorted<Typelist<T2, TS...>, CP>::value;
        };
    template <typename TL, template <typename, typename> class CP>
        concept IsSorted = MetaIsSorted<TL, CP>::value;

    template <TypelistInstance TL>
        struct MetaIsUnique:
        std::true_type {};
    template <typename T, typename... TS>
        struct MetaIsUnique<Typelist<T, TS...>>
        { static constexpr bool value = Count<Typelist<TS...>, T> == 0
            && MetaIsUnique<Typelist<TS...>>::value; };
    template <typename TL>
        concept IsUnique = MetaIsUnique<TL>::value;

}
