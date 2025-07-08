#pragma once

#include "rs-core/arithmetic.hpp"
#include "rs-core/enum.hpp"
#include "rs-core/global.hpp"
#include "rs-core/hash.hpp"
#include <compare>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <format>
#include <functional>
#include <iterator>
#include <ranges>
#include <type_traits>
#include <utility>

namespace RS {

    namespace Detail {

        template <typename T> concept Reference = std::is_reference_v<T>;
        template <typename T> concept NonReference = ! std::is_reference_v<T>;

        template <typename T> struct MutableReferenceType: std::false_type {};
        template <typename T> struct MutableReferenceType<T&>: std::true_type {};
        template <typename T> struct MutableReferenceType<const T&>: std::false_type {};
        template <typename T> concept MutableReference = MutableReferenceType<T>::value;

        template <typename T>
        concept Formattable = requires {
            std::formatter<std::remove_cvref_t<T>>();
        };

    }

    RS_BITMASK(AliasFlags, std::uint8_t,
        none       = 0,
        compare    = 1,
        construct  = 2,
        convert    = 4,
    )

    template <typename T, typename Tag = void, AliasFlags Flags = AliasFlags::none>
    class Alias {

    private:

        static constexpr bool compare_heterogeneous = has_bit(Flags, AliasFlags::compare);
        static constexpr bool implicit_construct = has_bit(Flags, AliasFlags::construct);
        static constexpr bool implicit_convert = has_bit(Flags, AliasFlags::convert);

        T value_;

    public:

        // Parameter visibility

        using underlying_type = T;
        using tag_type = Tag;

        static constexpr auto flags = Flags;

        // Life cycle operations

        template <bool OK = std::default_initializable<T>, std::enable_if_t<OK, int> = 0>
            Alias(): value_{} {}

        template <bool OK = std::copyable<T>, std::enable_if_t<OK, int> = 0>
            Alias(const Alias& a): value_(a.value_) {}
        template <bool OK = std::movable<T>, std::enable_if_t<OK, int> = 0>
            Alias(Alias&& a): value_(std::move(a.value_)) {}
        template <bool OK = std::copyable<T>, std::enable_if_t<OK, int> = 0>
            Alias& operator=(const Alias& a) { value_ = a.value_; return *this; }
        template <bool OK = std::movable<T>, std::enable_if_t<OK, int> = 0>
            Alias& operator=(Alias&& a) { value_ = std::move(a.value_); return *this; }

        template <bool OK = std::copyable<T>, std::enable_if_t<OK, int> = 0>
            explicit(! implicit_construct) Alias(const T& t): value_(t) {}
        template <bool OK = std::movable<T>, std::enable_if_t<OK, int> = 0>
            explicit(! implicit_construct) Alias(T&& t): value_(std::move(t)) {}
        template <bool OK = implicit_construct && std::copyable<T>, std::enable_if_t<OK, int> = 0>
            Alias& operator=(const T& t) { value_ = t; return *this; }
        template <bool OK = implicit_construct && std::movable<T>, std::enable_if_t<OK, int> = 0>
            Alias& operator=(T&& t) { value_ = std::move(t); return *this; }

        template <typename Tag2, AliasFlags F2, bool OK = std::copyable<T>, std::enable_if_t<OK, int> = 0>
            explicit Alias(const Alias<T, Tag2, F2>& a): value_(a.value_) {}
        template <typename Tag2, AliasFlags F2, bool OK = std::movable<T>, std::enable_if_t<OK, int> = 0>
            explicit Alias(Alias<T, Tag2, F2>&& a): value_(std::move(a.value_)) {}

        template <typename... TS, std::enable_if_t<std::constructible_from<T, TS...>, int> = 0>
            explicit Alias(TS&&... args): value_(std::forward<TS>(args)...) {}

        // Conversion operators

        explicit(! implicit_convert) operator T() const { return value_; }

        template <bool OK = std::constructible_from<bool, T>, std::enable_if_t<OK, int> = 0>
            explicit(! std::convertible_to<T, bool>) operator bool() const { return bool(value_); }

        // Access operators

        T& operator*() noexcept { return value_; }
        const T& operator*() const noexcept { return value_; }
        T* operator->() noexcept { return &value_; }
        const T* operator->() const noexcept { return &value_; }

        // Arithmetic operators

        template <bool OK = requires (T t) { { + t } -> std::convertible_to<T>; }, std::enable_if_t<OK, int> = 0>
            Alias operator+() const { return Alias(+ value_); }
        template <bool OK = requires (T t) { { - t } -> std::convertible_to<T>; }, std::enable_if_t<OK, int> = 0>
            Alias operator-() const { return Alias(- value_); }
        template <bool OK = requires (T t) { { ~ t } -> std::convertible_to<T>; }, std::enable_if_t<OK, int> = 0>
            Alias operator~() const { return Alias(~ value_); }

        template <bool OK = requires (T& t) { { ++ t }; }, std::enable_if_t<OK, int> = 0>
            Alias& operator++() { ++ value_; return *this; }
        template <bool OK = requires (T& t) { { t ++ }; }, std::enable_if_t<OK, int> = 0>
            Alias operator++(int) { auto old = *this; value_ ++; return old; }
        template <bool OK = requires (T& t) { { -- t }; }, std::enable_if_t<OK, int> = 0>
            Alias& operator--() { -- value_; return *this; }
        template <bool OK = requires (T& t) { { t -- }; }, std::enable_if_t<OK, int> = 0>
            Alias operator--(int) { auto old = *this; value_ --; return old; }

        template <bool OK = requires (T& t, T u) { { t += u }; }, std::enable_if_t<OK, int> = 0>
            Alias& operator+=(const Alias& a) { value_ += a.value_; return *this; }
        template <bool OK = requires (T& t, T u) { { t -= u }; }, std::enable_if_t<OK, int> = 0>
            Alias& operator-=(const Alias& a) { value_ -= a.value_; return *this; }
        template <bool OK = requires (T& t, T u) { { t *= u }; }, std::enable_if_t<OK, int> = 0>
            Alias& operator*=(const Alias& a) { value_ *= a.value_; return *this; }
        template <bool OK = requires (T& t, T u) { { t /= u }; }, std::enable_if_t<OK, int> = 0>
            Alias& operator/=(const Alias& a) { value_ /= a.value_; return *this; }
        template <bool OK = requires (T& t, T u) { { t %= u }; }, std::enable_if_t<OK, int> = 0>
            Alias& operator%=(const Alias& a) { value_ %= a.value_; return *this; }
        template <bool OK = requires (T& t, T u) { { t &= u }; }, std::enable_if_t<OK, int> = 0>
            Alias& operator&=(const Alias& a) { value_ &= a.value_; return *this; }
        template <bool OK = requires (T& t, T u) { { t |= u }; }, std::enable_if_t<OK, int> = 0>
            Alias& operator|=(const Alias& a) { value_ |= a.value_; return *this; }
        template <bool OK = requires (T& t, T u) { { t ^= u }; }, std::enable_if_t<OK, int> = 0>
            Alias& operator^=(const Alias& a) { value_ ^= a.value_; return *this; }
        template <bool OK = requires (T& t, int i) { { t <<= i }; }, std::enable_if_t<OK, int> = 0>
            Alias& operator<<=(int j) { value_ <<= j; return *this; }
        template <bool OK = requires (T& t, int i) { { t >>= i }; }, std::enable_if_t<OK, int> = 0>
            Alias& operator>>=(int j) { value_ >>= j; return *this; }

        template <bool OK = requires (T t, T u) { { t + u } -> std::convertible_to<T>; }, std::enable_if_t<OK, int> = 0>
            friend Alias operator+(const Alias& a, const Alias& b) { return Alias(a.value_ + b.value_); }
        template <bool OK = requires (T t, T u) { { t - u } -> std::convertible_to<T>; }, std::enable_if_t<OK, int> = 0>
            friend Alias operator-(const Alias& a, const Alias& b) { return Alias(a.value_ - b.value_); }
        template <bool OK = requires (T t, T u) { { t * u } -> std::convertible_to<T>; }, std::enable_if_t<OK, int> = 0>
            friend Alias operator*(const Alias& a, const Alias& b) { return Alias(a.value_ * b.value_); }
        template <bool OK = requires (T t, T u) { { t / u } -> std::convertible_to<T>; }, std::enable_if_t<OK, int> = 0>
            friend Alias operator/(const Alias& a, const Alias& b) { return Alias(a.value_ / b.value_); }
        template <bool OK = requires (T t, T u) { { t % u } -> std::convertible_to<T>; }, std::enable_if_t<OK, int> = 0>
            friend Alias operator%(const Alias& a, const Alias& b) { return Alias(a.value_ % b.value_); }
        template <bool OK = requires (T t, T u) { { t & u } -> std::convertible_to<T>; }, std::enable_if_t<OK, int> = 0>
            friend Alias operator&(const Alias& a, const Alias& b) { return Alias(a.value_ & b.value_); }
        template <bool OK = requires (T t, T u) { { t | u } -> std::convertible_to<T>; }, std::enable_if_t<OK, int> = 0>
            friend Alias operator|(const Alias& a, const Alias& b) { return Alias(a.value_ | b.value_); }
        template <bool OK = requires (T t, T u) { { t ^ u } -> std::convertible_to<T>; }, std::enable_if_t<OK, int> = 0>
            friend Alias operator^(const Alias& a, const Alias& b) { return Alias(a.value_ ^ b.value_); }
        template <bool OK = requires (T t, int i) { { t << i } -> std::convertible_to<T>; }, std::enable_if_t<OK, int> = 0>
            friend Alias operator<<(const Alias& a, int j) { return Alias(a.value_ << j); }
        template <bool OK = requires (T t, int i) { { t >> i } -> std::convertible_to<T>; }, std::enable_if_t<OK, int> = 0>
            friend Alias operator>>(const Alias& a, int j) { return Alias(a.value_ >> j); }

        // Comparison operators

        template <bool OK = std::equality_comparable<T>, std::enable_if_t<OK, int> = 0>
            friend bool operator==(const Alias& a, const Alias& b) { return a.value_ == b.value_; }
        template <bool OK = std::three_way_comparable<T>, std::enable_if_t<OK, int> = 0>
            friend auto operator<=>(const Alias& a, const Alias& b) { return a.value_ <=> b.value_; }
        template <bool OK = std::equality_comparable<T> && compare_heterogeneous, std::enable_if_t<OK, int> = 0>
            friend bool operator==(const Alias& a, const T& t) { return a.value_ == t; }
        template <bool OK = std::three_way_comparable<T> && compare_heterogeneous, std::enable_if_t<OK, int> = 0>
            friend auto operator<=>(const Alias& a, const T& t) { return a.value_ <=> t; }

        // Range access

        template <bool OK = requires (T& t) { { t[0] } -> Detail::MutableReference; }, std::enable_if_t<OK, int> = 0>
            auto& operator[](std::size_t i) { return value_[i]; }
        template <bool OK = requires (const T& t) { { t[0] } -> Detail::Reference; }, std::enable_if_t<OK, int> = 0>
            const auto& operator[](std::size_t i) const { return value_[i]; }
        template <bool OK = requires (const T& t) { { t[0] } -> Detail::NonReference; }, std::enable_if_t<OK, int> = 0>
            auto operator[](std::size_t i) const { return value_[i]; }

        template <bool OK = requires (T& t) { { std::ranges::begin(t) }; }, std::enable_if_t<OK, int> = 0>
            auto begin() { return std::ranges::begin(value_); }
        template <bool OK = requires (const T& t) { { std::ranges::begin(t) }; }, std::enable_if_t<OK, int> = 0>
            auto begin() const { return std::ranges::begin(value_); }
        template <bool OK = requires (T& t) { { std::ranges::end(t) }; }, std::enable_if_t<OK, int> = 0>
            auto end() { return std::ranges::end(value_); }
        template <bool OK = requires (const T& t) { { std::ranges::end(t) }; }, std::enable_if_t<OK, int> = 0>
            auto end() const { return std::ranges::end(value_); }

        template <bool OK = requires (const T& t) { { std::ranges::size(t) }; }, std::enable_if_t<OK, int> = 0>
            std::size_t size() const { return std::size_t(std::ranges::size(value_)); }
        template <bool OK = requires (const T& t) { { std::ranges::empty(t) }; }, std::enable_if_t<OK, int> = 0>
            bool empty() const { return std::ranges::empty(value_); }

        // String functions

        template <bool OK = requires (const T& t) { { t.substr(0, 1) } -> std::convertible_to<T>; }, std::enable_if_t<OK, int> = 0>
            Alias substr(std::size_t pos, std::size_t len = npos) const { return Alias(value_.substr(pos, len)); }

    };

}

template <typename T, typename Tag, RS::AliasFlags Flags>
requires RS::Detail::Formattable<T>
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
