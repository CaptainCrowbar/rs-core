#pragma once

#include "rs-core/arithmetic.hpp"
#include "rs-core/enum.hpp"
#include "rs-core/global.hpp"
#include "rs-core/hash.hpp"
#include <cmath>
#include <compare>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <format>
#include <functional>
#include <iterator>
#include <limits>
#include <numbers>
#include <ranges>
#include <utility>

namespace RS {

    RS_BITMASK(AliasFlags, std::uint8_t,
        none                 = 0,
        cross_compare        = 1,  // Heterogeneous comparison operators
        implicit_from_alias  = 2,  // Implicit conversion from Alias to T
        implicit_to_alias    = 4,  // Implicit conversion from T to Alias
    )

    template <typename T, typename Tag = void, AliasFlags Flags = AliasFlags::none>
    class Alias {

    private:

        static constexpr bool cross_compare = has_bit(Flags, AliasFlags::cross_compare);
        static constexpr bool implicit_to_alias = has_bit(Flags, AliasFlags::implicit_to_alias);
        static constexpr bool implicit_from_alias = has_bit(Flags, AliasFlags::implicit_from_alias);

        T value_;

    public:

        // Parameter visibility

        using underlying_type = T;
        using tag_type = Tag;

        static constexpr auto flags = Flags;

        // Life cycle operations

        Alias() requires std::default_initializable<T>: value_{} {}

        Alias(const Alias& a) requires std::copyable<T>: value_(a.value_) {}
        Alias(Alias&& a) requires std::movable<T>: value_(std::move(a.value_)) {}
        Alias& operator=(const Alias& a) requires std::copyable<T> { value_ = a.value_; return *this; }
        Alias& operator=(Alias&& a) requires std::movable<T> { value_ = std::move(a.value_); return *this; }

        explicit(! implicit_to_alias) Alias(const T& t) requires std::copyable<T>: value_(t) {}
        explicit(! implicit_to_alias) Alias(T&& t) requires std::movable<T>: value_(std::move(t)) {}
        Alias& operator=(const T& t) requires implicit_to_alias && std::copyable<T> { value_ = t; return *this; }
        Alias& operator=(T&& t) requires implicit_to_alias && std::movable<T> { value_ = std::move(t); return *this; }

        template <typename Tag2, AliasFlags F2> explicit Alias(const Alias<T, Tag2, F2>& a)
            requires std::copyable<T>: value_(a.value_) {}
        template <typename Tag2, AliasFlags F2> explicit Alias(Alias<T, Tag2, F2>&& a)
            requires std::movable<T>: value_(std::move(a.value_)) {}

        template <typename... TS> explicit Alias(TS&&... args)
            requires std::constructible_from<T, TS...>: value_(std::forward<TS>(args)...) {}

        // Conversion operators

        explicit(! implicit_from_alias) operator T() const { return value_; }
        explicit(! std::convertible_to<T, bool>) operator bool() const
            requires std::constructible_from<bool, T> { return bool(value_); }

        // Access operators

        T& operator*() noexcept { return value_; }
        const T& operator*() const noexcept { return value_; }
        T* operator->() noexcept { return &value_; }
        const T* operator->() const noexcept { return &value_; }

        // Arithmetic operators

        Alias operator+() const requires requires (T t) { { + t } -> std::convertible_to<T>; } { return Alias{+ value_}; }
        Alias operator-() const requires requires (T t) { { - t } -> std::convertible_to<T>; } { return Alias{- value_}; }
        Alias operator~() const requires requires (T t) { { ~ t } -> std::convertible_to<T>; } { return Alias{~ value_}; }

        Alias& operator++() requires requires (T& t) { { ++ t }; } { ++ value_; return *this; }
        Alias operator++(int) requires requires (T& t) { { t ++ }; } { auto old = *this; value_ ++; return old; }
        Alias& operator--() requires requires (T& t) { { -- t }; } { -- value_; return *this; }
        Alias operator--(int) requires requires (T& t) { { t -- }; } { auto old = *this; value_ --; return old; }

        Alias& operator+=(const Alias& a) requires requires (T& t, T u) { { t += u }; } { value_ += a.value_; return *this; }
        Alias& operator-=(const Alias& a) requires requires (T& t, T u) { { t -= u }; } { value_ -= a.value_; return *this; }
        Alias& operator*=(const Alias& a) requires requires (T& t, T u) { { t *= u }; } { value_ *= a.value_; return *this; }
        Alias& operator/=(const Alias& a) requires requires (T& t, T u) { { t /= u }; } { value_ /= a.value_; return *this; }
        Alias& operator%=(const Alias& a) requires requires (T& t, T u) { { t %= u }; } { value_ %= a.value_; return *this; }
        Alias& operator&=(const Alias& a) requires requires (T& t, T u) { { t &= u }; } { value_ &= a.value_; return *this; }
        Alias& operator|=(const Alias& a) requires requires (T& t, T u) { { t |= u }; } { value_ |= a.value_; return *this; }
        Alias& operator^=(const Alias& a) requires requires (T& t, T u) { { t ^= u }; } { value_ ^= a.value_; return *this; }
        Alias& operator<<=(int j) requires requires (T& t, int i) { { t <<= i }; } { value_ <<= j; return *this; }
        Alias& operator>>=(int j) requires requires (T& t, int i) { { t >>= i }; } { value_ >>= j; return *this; }

        friend Alias operator+(const Alias& a, const Alias& b)
            requires requires (T t, T u) { { t + u } -> std::convertible_to<T>; } { return Alias{a.value_ + b.value_}; }
        friend Alias operator-(const Alias& a, const Alias& b)
            requires requires (T t, T u) { { t - u } -> std::convertible_to<T>; } { return Alias{a.value_ - b.value_}; }
        friend Alias operator*(const Alias& a, const Alias& b)
            requires requires (T t, T u) { { t * u } -> std::convertible_to<T>; } { return Alias{a.value_ * b.value_}; }
        friend Alias operator/(const Alias& a, const Alias& b)
            requires requires (T t, T u) { { t / u } -> std::convertible_to<T>; } { return Alias{a.value_ / b.value_}; }
        friend Alias operator%(const Alias& a, const Alias& b)
            requires requires (T t, T u) { { t % u } -> std::convertible_to<T>; } { return Alias{a.value_ % b.value_}; }
        friend Alias operator&(const Alias& a, const Alias& b)
            requires requires (T t, T u) { { t & u } -> std::convertible_to<T>; } { return Alias{a.value_ & b.value_}; }
        friend Alias operator|(const Alias& a, const Alias& b)
            requires requires (T t, T u) { { t | u } -> std::convertible_to<T>; } { return Alias{a.value_ | b.value_}; }
        friend Alias operator^(const Alias& a, const Alias& b)
            requires requires (T t, T u) { { t ^ u } -> std::convertible_to<T>; } { return Alias{a.value_ ^ b.value_}; }
        friend Alias operator<<(const Alias& a, int j)
            requires requires (T t, int i) { { t << i } -> std::convertible_to<T>; } { return Alias{a.value_ << j}; }
        friend Alias operator>>(const Alias& a, int j)
            requires requires (T t, int i) { { (t >> i) } -> std::convertible_to<T>; } { return Alias{a.value_ >> j}; }

        // Comparison operators

        friend bool operator==(const Alias& a, const Alias& b)
            requires std::equality_comparable<T> { return a.value_ == b.value_; }
        friend auto operator<=>(const Alias& a, const Alias& b)
            requires std::three_way_comparable<T> { return a.value_ <=> b.value_; }
        friend bool operator==(const Alias& a, const T& t)
            requires std::equality_comparable<T> && cross_compare { return a.value_ == t; }
        friend auto operator<=>(const Alias& a, const T& t)
            requires std::three_way_comparable<T> && cross_compare { return a.value_ <=> t; }

        // Range access

        auto& operator[](std::size_t i)
            requires requires (T& t) { { t[0] } -> MutableReference; } { return value_[i]; }
        const auto& operator[](std::size_t i) const
            requires requires (const T& t) { { t[0] } -> Reference; } { return value_[i]; }
        auto operator[](std::size_t i) const
            requires requires (const T& t) { { t[0] } -> NonReference; } { return value_[i]; }
        auto begin() requires requires (T& t) { { std::ranges::begin(t) }; } { return std::ranges::begin(value_); }
        auto begin() const requires requires (const T& t) { { std::ranges::begin(t) }; } { return std::ranges::begin(value_); }
        auto end() requires requires (T& t) { { std::ranges::end(t) }; } { return std::ranges::end(value_); }
        auto end() const requires requires (const T& t) { { std::ranges::end(t) }; } { return std::ranges::end(value_); }

        std::size_t size() const
            requires requires (const T& t) { { std::ranges::size(t) }; } { return std::size_t(std::ranges::size(value_)); }
        bool empty() const
            requires requires (const T& t) { { std::ranges::empty(t) }; } { return std::ranges::empty(value_); }

        // String functions

        Alias substr(std::size_t pos, std::size_t len = npos) const
            requires requires (const T& t) { { t.substr(0, 1) } -> std::convertible_to<T>; }
            { return Alias{value_.substr(pos, len)}; }

        // Maths functions

        // (T) -> T
        #define RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_YIELDS_T(function) \
            friend auto function(Alias a) \
            requires requires (T x) { { std::function(x) } -> std::convertible_to<T>; } \
                    || requires (T x) { { function(x) } -> std::convertible_to<T>; } { \
                using std::function; \
                return Alias{function(*a)}; \
            }

        // (T) -> RT
        #define RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_YIELDS_RT(function, RT) \
            friend auto function(Alias a) \
            requires requires (T x) { { std::function(x) } -> std::convertible_to<RT>; } \
                    || requires (T x) { { function(x) } -> std::convertible_to<RT>; } { \
                using std::function; \
                return Alias{function(*a)}; \
            }

        // (T, T) -> T
        #define RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_T_YIELDS_T(function) \
            friend auto function(Alias a, Alias b) \
            requires requires (T x, T y) { { std::function(x, y) } -> std::convertible_to<T>; } \
                    || requires (T x, T y) { { function(x, y) } -> std::convertible_to<T>; } { \
                using std::function; \
                return Alias{function(*a, *b)}; \
            }

        // (T, T) -> RT
        #define RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_T_YIELDS_RT(function, RT) \
            friend auto function(Alias a, Alias b) \
            requires requires (T x, T y) { { std::function(x, y) } -> std::convertible_to<RT>; } \
                    || requires (T x, T y) { { function(x, y) } -> std::convertible_to<RT>; } { \
                using std::function; \
                return Alias{function(*a, *b)}; \
            }

        // (T, T*) -> T
        #define RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_TPTR_YIELDS_T(function) \
            friend auto function(Alias a, Alias* b) \
            requires requires (T x, T* y) { { std::function(x, y) } -> std::convertible_to<T>; } \
                    || requires (T x, T* y) { { function(x, y) } -> std::convertible_to<T>; } { \
                using std::function; \
                T t{}; \
                Alias r{function(*a, &t)}; \
                *b = Alias{t}; \
                return r; \
            }

        // (T, U) -> T
        #define RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_U_YIELDS_T(function, U) \
            friend auto function(Alias a, U b) \
            requires requires (T x, U y) { { std::function(x, y) } -> std::convertible_to<T>; } \
                    || requires (T x, U y) { { function(x, y) } -> std::convertible_to<T>; } { \
                using std::function; \
                return Alias{function(*a, b)}; \
            }

        // (T, U*) -> T
        #define RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_UPTR_YIELDS_T(function, U) \
            friend auto function(Alias a, U* b) \
            requires requires (T x, U* y) { { std::function(x, y) } -> std::convertible_to<T>; } \
                    || requires (T x, U* y) { { function(x, y) } -> std::convertible_to<T>; } { \
                using std::function; \
                return Alias{function(*a, b)}; \
            }

        // (U, T) -> T
        #define RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_U_T_YIELDS_T(function, U) \
            friend auto function(U a, Alias b) \
            requires requires (U x, T y) { { std::function(x, y) } -> std::convertible_to<T>; } \
                    || requires (U x, T y) { { function(x, y) } -> std::convertible_to<T>; } { \
                using std::function; \
                return Alias{function(a, *b)}; \
            }

        // (T, T, T) -> T
        #define RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_T_T_YIELDS_T(function) \
            friend auto function(Alias a, Alias b, Alias c) \
            requires requires (T x, T y, T z) { { std::function(x, y, z) } -> std::convertible_to<T>; } \
                    || requires (T x, T y, T z) { { function(x, y, z) } -> std::convertible_to<T>; } { \
                using std::function; \
                return Alias{function(*a, *b, *c)}; \
            }

        // (T, T, U*) -> T
        #define RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_T_UPTR_YIELDS_T(function, U) \
            friend auto function(Alias a, Alias b, U* c) \
            requires requires (T x, T y, U* z) { { std::function(x, y, z) } -> std::convertible_to<T>; } \
                    || requires (T x, T y, U* z) { { function(x, y, z) } -> std::convertible_to<T>; } { \
                using std::function; \
                return Alias{function(*a, *b, c)}; \
            }

        // (U, U, T) -> T
        #define RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_U_U_T_YIELDS_T(function, U) \
            friend auto function(U a, U b, Alias c) \
            requires requires (U x, U y, T z) { { std::function(x, y, z) } -> std::convertible_to<T>; } \
                    || requires (U x, U y, T z) { { function(x, y, z) } -> std::convertible_to<T>; } { \
                using std::function; \
                return Alias{function(a, b, *c)}; \
            }

        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (acos)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (acosh)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (asin)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (asinh)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (atan)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_T_YIELDS_T       (atan2)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (atanh)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (cbrt)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (ceil)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_T_YIELDS_T       (copysign)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (cos)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (cosh)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (erf)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (erfc)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (exp)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (exp2)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (expm1)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (fabs)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_T_YIELDS_T       (fdim)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (floor)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_T_T_YIELDS_T     (fma)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_T_YIELDS_T       (fmax)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_T_YIELDS_T       (fmin)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_T_YIELDS_T       (fmod)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_YIELDS_RT        (fpclassify, int)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_UPTR_YIELDS_T    (frexp, int)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_T_T_YIELDS_T     (hypot)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_T_YIELDS_T       (hypot)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_YIELDS_RT        (ilogb, int)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_YIELDS_RT        (isfinite, bool)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_T_YIELDS_RT      (isgreater, bool)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_T_YIELDS_RT      (isgreaterequal, bool)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_YIELDS_RT        (isinf, bool)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_T_YIELDS_RT      (isless, bool)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_T_YIELDS_RT      (islessequal, bool)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_T_YIELDS_RT      (islessgreater, bool)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_YIELDS_RT        (isnan, bool)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_YIELDS_RT        (isnormal, bool)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_T_YIELDS_RT      (isunordered, bool)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_U_YIELDS_T       (ldexp, int)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_T_T_YIELDS_T     (lerp)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (lgamma)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_YIELDS_RT        (llrint, long long)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_YIELDS_RT        (llround, long long)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (log)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (log10)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (log1p)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (log2)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (logb)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_YIELDS_RT        (lrint, long)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_YIELDS_RT        (lround, long)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_TPTR_YIELDS_T    (modf)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (nearbyint)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_T_YIELDS_T       (nextafter)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_U_YIELDS_T       (nexttoward, long double)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_T_YIELDS_T       (pow)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_T_YIELDS_T       (remainder)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_T_UPTR_YIELDS_T  (remquo, int)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (rint)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (round)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_U_YIELDS_T       (scalbln, long)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_U_YIELDS_T       (scalbn, int)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_YIELDS_RT        (signbit, bool)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (sin)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (sinh)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (sqrt)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (tan)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (tanh)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (tgamma)
        RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (trunc)

        #if __cpp_lib_math_special_functions >= 201603L

            RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_U_U_T_YIELDS_T  (assoc_laguerre, unsigned)
            RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_U_U_T_YIELDS_T  (assoc_legendre, unsigned)
            RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_T_YIELDS_T    (beta)
            RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_YIELDS_T      (comp_ellint_1)
            RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_YIELDS_T      (comp_ellint_2)
            RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_T_YIELDS_T    (comp_ellint_3)
            RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_T_YIELDS_T    (cyl_bessel_i)
            RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_T_YIELDS_T    (cyl_bessel_j)
            RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_T_YIELDS_T    (cyl_bessel_k)
            RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_T_YIELDS_T    (cyl_neumann)
            RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_T_YIELDS_T    (ellint_1)
            RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_T_YIELDS_T    (ellint_2)
            RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_T_T_YIELDS_T  (ellint_3)
            RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_YIELDS_T      (expint)
            RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_U_T_YIELDS_T    (hermite, unsigned)
            RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_U_T_YIELDS_T    (laguerre, unsigned)
            RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_U_T_YIELDS_T    (legendre, unsigned)
            RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_T_YIELDS_T      (riemann_zeta)
            RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_U_T_YIELDS_T    (sph_bessel, unsigned)
            RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_U_U_T_YIELDS_T  (sph_legendre, unsigned)
            RS_CORE_DEFINE_ALIAS_MATHS_FUNCTION_U_T_YIELDS_T    (sph_neumann, unsigned)

        #endif

    };

}

template <typename T, typename Tag, RS::AliasFlags Flags>
requires std::formattable<T, char>
struct std::formatter<RS::Alias<T, Tag, Flags>>:
std::formatter<T> {
    template <typename FormatContext>
    auto format(const RS::Alias<T, Tag, Flags>& a, FormatContext& ctx) const {
        return std::formatter<T>::format(*a, ctx);
    }
};

template <typename T, typename Tag, RS::AliasFlags Flags>
requires RS::Hashable<T>
struct std::hash<RS::Alias<T, Tag, Flags>> {
    std::size_t operator()(const RS::Alias<T, Tag, Flags>& a) const {
        return std::hash<T>()(*a);
    }
};

#define RS_CORE_DEFINE_ALIAS_STD_NUMBERS_CONSTANT(constant) \
    template <typename T, typename Tag, RS::AliasFlags Flags> \
    requires requires { { std::numbers::constant ## _v<T> } -> std::convertible_to<T>; } \
    RS::Alias<T, Tag, Flags> constant ## _v <RS::Alias<T, Tag, Flags>>{constant ## _v<T>};

namespace std::numbers {

    RS_CORE_DEFINE_ALIAS_STD_NUMBERS_CONSTANT(e)
    RS_CORE_DEFINE_ALIAS_STD_NUMBERS_CONSTANT(egamma)
    RS_CORE_DEFINE_ALIAS_STD_NUMBERS_CONSTANT(inv_pi)
    RS_CORE_DEFINE_ALIAS_STD_NUMBERS_CONSTANT(inv_sqrt3)
    RS_CORE_DEFINE_ALIAS_STD_NUMBERS_CONSTANT(inv_sqrtpi)
    RS_CORE_DEFINE_ALIAS_STD_NUMBERS_CONSTANT(ln10)
    RS_CORE_DEFINE_ALIAS_STD_NUMBERS_CONSTANT(ln2)
    RS_CORE_DEFINE_ALIAS_STD_NUMBERS_CONSTANT(log10e)
    RS_CORE_DEFINE_ALIAS_STD_NUMBERS_CONSTANT(log2e)
    RS_CORE_DEFINE_ALIAS_STD_NUMBERS_CONSTANT(phi)
    RS_CORE_DEFINE_ALIAS_STD_NUMBERS_CONSTANT(pi)
    RS_CORE_DEFINE_ALIAS_STD_NUMBERS_CONSTANT(sqrt2)
    RS_CORE_DEFINE_ALIAS_STD_NUMBERS_CONSTANT(sqrt3)

}

template <typename T, typename Tag, RS::AliasFlags Flags>
requires std::numeric_limits<T>::is_specialized
class std::numeric_limits<RS::Alias<T, Tag, Flags>>:
public std::numeric_limits<T> {

private:

    using alias = RS::Alias<T, Tag, Flags>;
    using t_limits = std::numeric_limits<T>;

public:

    static alias denorm_min()     { return static_cast<alias>(t_limits::denorm_min()); }
    static alias epsilon()        { return static_cast<alias>(t_limits::epsilon()); }
    static alias infinity()       { return static_cast<alias>(t_limits::infinity()); }
    static alias lowest()         { return static_cast<alias>(t_limits::lowest()); }
    static alias max()            { return static_cast<alias>(t_limits::max()); }
    static alias min()            { return static_cast<alias>(t_limits::min()); }
    static alias quiet_NaN()      { return static_cast<alias>(t_limits::quiet_NaN()); }
    static alias round_error()    { return static_cast<alias>(t_limits::round_error()); }
    static alias signaling_NaN()  { return static_cast<alias>(t_limits::signaling_NaN()); }

};
