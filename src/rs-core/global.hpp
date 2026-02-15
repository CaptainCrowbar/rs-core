#pragma once

#include <concepts>
#include <cstdint>
#include <limits>
#include <print>
#include <string_view>
#include <type_traits>

namespace RS {

    // Sanity check

    static_assert(std::numeric_limits<unsigned char>::digits == 8);

    // Primitive concepts

    template <typename T> struct MetaMutableReference: std::false_type {};
    template <typename T> struct MetaMutableReference<T&>: std::true_type {};
    template <typename T> struct MetaMutableReference<const T&>: std::false_type {};
    template <typename T> concept Reference = std::is_reference_v<T>;
    template <typename T> concept MutableReference = MetaMutableReference<T>::value;
    template <typename T> concept ConstReference = Reference<T> && ! MutableReference<T>;
    template <typename T> concept NonReference = ! std::is_reference_v<T>;

    // Arithmetic concepts

    template <typename T>
    concept Arithmetic = std::numeric_limits<T>::is_specialized
        && ! std::same_as<T, bool>;

    template <typename T>
    concept FixedPointArithmetic = Arithmetic<T>
        && std::numeric_limits<T>::is_fixed_point;

    template <typename T>
    concept RationalArithmetic = Arithmetic<T>
        && std::numeric_limits<T>::is_rational;

    template <typename T>
    concept FloatingPoint = Arithmetic<T>
        && ! FixedPointArithmetic<T>
        && ! RationalArithmetic<T>
        && ! std::numeric_limits<T>::is_integer;

    template <typename T>
    concept Integral = Arithmetic<T>
        && ! FixedPointArithmetic<T>
        && ! RationalArithmetic<T>
        && std::numeric_limits<T>::is_integer;

    template <typename T>
    concept SignedIntegral = Integral<T>
        && std::numeric_limits<T>::is_signed;

    template <typename T>
    concept UnsignedIntegral = Integral<T>
        && ! std::numeric_limits<T>::is_signed;

    // Constants

    constexpr std::string_view ascii_whitespace = "\t\n\r ";
    constexpr auto max32 = ~ std::uint32_t{0};
    constexpr auto max64 = ~ std::uint64_t{0};
    constexpr auto npos = ~ 0uz;

    // Metaprogramming utilities

    template <typename> constexpr bool dependent_false = false;

}
