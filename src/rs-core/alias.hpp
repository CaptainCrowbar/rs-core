#pragma once

#include "rs-core/arithmetic.hpp"
#include "rs-core/enum.hpp"
#include "rs-core/format.hpp"
#include "rs-core/global.hpp"
#include "rs-core/hash.hpp"
#include <compare>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <format>
#include <functional>
#include <iterator>
#include <limits>
#include <ranges>
#include <type_traits>
#include <utility>

namespace RS {

    namespace Detail {

        template <typename T> struct MutableReferenceType: std::false_type {};
        template <typename T> struct MutableReferenceType<T&>: std::true_type {};
        template <typename T> struct MutableReferenceType<const T&>: std::false_type {};
        template <typename T> concept MutableReference = MutableReferenceType<T>::value;
        template <typename T> concept Reference = std::is_reference_v<T>;
        template <typename T> concept NonReference = ! std::is_reference_v<T>;

    }

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

        Alias operator+() const requires requires (T t) { { + t } -> std::convertible_to<T>; } { return Alias(+ value_); }
        Alias operator-() const requires requires (T t) { { - t } -> std::convertible_to<T>; } { return Alias(- value_); }
        Alias operator~() const requires requires (T t) { { ~ t } -> std::convertible_to<T>; } { return Alias(~ value_); }

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
            requires requires (T t, T u) { { t + u } -> std::convertible_to<T>; } { return Alias(a.value_ + b.value_); }
        friend Alias operator-(const Alias& a, const Alias& b)
            requires requires (T t, T u) { { t - u } -> std::convertible_to<T>; } { return Alias(a.value_ - b.value_); }
        friend Alias operator*(const Alias& a, const Alias& b)
            requires requires (T t, T u) { { t * u } -> std::convertible_to<T>; } { return Alias(a.value_ * b.value_); }
        friend Alias operator/(const Alias& a, const Alias& b)
            requires requires (T t, T u) { { t / u } -> std::convertible_to<T>; } { return Alias(a.value_ / b.value_); }
        friend Alias operator%(const Alias& a, const Alias& b)
            requires requires (T t, T u) { { t % u } -> std::convertible_to<T>; } { return Alias(a.value_ % b.value_); }
        friend Alias operator&(const Alias& a, const Alias& b)
            requires requires (T t, T u) { { t & u } -> std::convertible_to<T>; } { return Alias(a.value_ & b.value_); }
        friend Alias operator|(const Alias& a, const Alias& b)
            requires requires (T t, T u) { { t | u } -> std::convertible_to<T>; } { return Alias(a.value_ | b.value_); }
        friend Alias operator^(const Alias& a, const Alias& b)
            requires requires (T t, T u) { { t ^ u } -> std::convertible_to<T>; } { return Alias(a.value_ ^ b.value_); }
        friend Alias operator<<(const Alias& a, int j)
            requires requires (T t, int i) { { t << i } -> std::convertible_to<T>; } { return Alias(a.value_ << j); }
        friend Alias operator>>(const Alias& a, int j)
            requires requires (T t, int i) { { (t >> i) } -> std::convertible_to<T>; } { return Alias(a.value_ >> j); }

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
            requires requires (T& t) { { t[0] } -> Detail::MutableReference; } { return value_[i]; }
        const auto& operator[](std::size_t i) const
            requires requires (const T& t) { { t[0] } -> Detail::Reference; } { return value_[i]; }
        auto operator[](std::size_t i) const
            requires requires (const T& t) { { t[0] } -> Detail::NonReference; } { return value_[i]; }

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
            { return Alias(value_.substr(pos, len)); }

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
