#pragma once

#include "rs-core/character.hpp"
#include "rs-core/global.hpp"
#include "rs-core/mp-integer.hpp"
#include <algorithm>
#include <bit>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <limits>
#include <numbers>
#include <optional>
#include <stdexcept>
#include <type_traits>
#include <utility>

namespace RS {

    // Arithmetic functions

    template <typename T>
    constexpr std::conditional_t<Integral<T>, double, T>
    binomial(T a, T b) {

        using R = std::conditional_t<Integral<T>, double, T>;

        if (a < T{0} || b < T{0} || b > a) {
            return R{0};
        } else if (b == T{0} || b == a) {
            return R{1};
        } else if (b == T{1} || b == a - T{1}) {
            return static_cast<R>(a);
        }

        auto result = static_cast<R>(a);
        auto limit = std::min(b, a - b);
        auto i = T{2};
        auto j = a - T{1};

        while (i <= limit) {
            result *= static_cast<R>(j);
            result /= static_cast<R>(i);
            j -= T{1};
            i += T{1};
        }

        return result;

    }

    template <typename T>
    constexpr std::pair<T, T> euclidean_divide(T x, T y) {

        T q, r;

        if constexpr (std::floating_point<T>) {

            q = x / y;
            auto negative = q < T{0};
            q = std::abs(q);

            if (q <= static_cast<T>(std::numeric_limits<std::uintmax_t>::max())) {
                q = static_cast<T>(static_cast<std::uintmax_t>(q));
            }

            if (negative) {
                q = - q;
            }

            r = x - q * y;

        } else {

            q = x / y;
            r = x % y;

        }

        if (r < T{0}) {
            if (y < T{0}) {
                q += T{1};
                r -= y;
            } else {
                q -= T{1};
                r += y;
            }
        }

        return {q, r};

    }

    template <typename T>
    constexpr T gcd(T x, T y) {

        auto a = x < T{0} ? T{0} - x : x;
        auto b = y < T{0} ? T{0} - y : y;

        if (a < b) {
            std::swap(a, b);
        }

        T r;

        while (b != T{0}) {
            r = a % b;
            if (r == T{0}) {
                return b;
            }
            a = std::move(b);
            b = std::move(r);
        }

        return a;

    }

    template <typename T>
    constexpr T lcm(T x, T y) {

        if (x == T{0} || y == T{0}) {

            return T{0};

        } else {

            auto div = gcd(x, y);
            auto z = (x / div) * y;

            return z < T{0} ? T{0} - z : z;

        }

    }

    template <typename T>
    constexpr T int_power(T x, int y) {

        if (y == 0) {

            return T{1};

        } else if (y == 1) {

            return x;

        } else {

            auto bits = std::bit_width(static_cast<unsigned>(y));
            auto z = T{1};

            for (auto bit = bits - 1; bit >= 0; --bit) {
                z *= z;
                if (((y >> bit) & 1) == 1) {
                    z *= x;
                }
            }

            return z;

        }

    }

    // Bitmask functions

    namespace Detail {

        template <std::integral T>
        constexpr auto force_unsigned(T t) noexcept {
            return static_cast<std::make_unsigned_t<T>>(t);
        }

        template <typename T>
        requires std::is_enum_v<T>
        constexpr auto force_unsigned(T t) noexcept {
            return force_unsigned(static_cast<std::underlying_type_t<T>>(t));
        }

    }

    template <typename T1, typename T2>
    requires (std::integral<T1> || std::is_enum_v<T1>)
        && (std::integral<T2> || std::is_enum_v<T2>)
    constexpr bool has_bit(T1 x, T2 y) noexcept {
        using namespace Detail;
        auto u = force_unsigned(x);
        auto v = force_unsigned(y);
        return (u & v) != 0;
    }

    template <typename T1, typename T2>
    requires (std::integral<T1> || std::is_enum_v<T1>)
        && (std::integral<T2> || std::is_enum_v<T2>)
    constexpr bool has_bits(T1 x, T2 y) noexcept {
        using namespace Detail;
        auto u = force_unsigned(x);
        auto v = force_unsigned(y);
        return v != 0 && (u & v) == v;
    }

    // Conversion functions

    template <std::integral To, std::integral From>
    constexpr std::optional<To> maybe_cast(From x) noexcept {

        static constexpr auto from_signed = std::signed_integral<From>;
        static constexpr auto to_signed = std::signed_integral<To>;
        static constexpr auto min_to = std::numeric_limits<To>::min();
        static constexpr auto max_to = std::numeric_limits<To>::max();

        if constexpr (from_signed == to_signed) {

            // Same signedness

            if constexpr (sizeof(To) < sizeof(From)) {
                if (x < static_cast<From>(min_to) || x > static_cast<From>(max_to)) {
                    return {};
                }
            }

        } else if constexpr (from_signed) {

            // Signed to unsigned

            if (x < 0) {
                return {};
            }

            if constexpr (sizeof(To) < sizeof(From)) {
                if (x > static_cast<From>(max_to)) {
                    return {};
                }
            }

        } else {

            // Unsigned to signed

            if constexpr (sizeof(To) <= sizeof(From)) {
                if (x > static_cast<From>(max_to)) {
                    return {};
                }
            }

        }

        return static_cast<To>(x);

    }

    template <std::integral To, std::integral From>
    constexpr std::optional<To> maybe_cast(std::optional<From> x) noexcept {
        if (x) {
            return maybe_cast<To>(*x);
        } else {
            return {};
        }
    }

    template <std::integral To, std::integral From>
    constexpr To try_cast(From x) {
        auto opt = maybe_cast<To>(x);
        if (! opt) {
            throw std::out_of_range("Value is out of range for cast type");
        }
        return *opt;
    }

    template <std::integral To, std::integral From>
    constexpr std::optional<To> try_cast(std::optional<From> x) {
        if (x) {
            return try_cast<To>(*x);
        } else {
            return {};
        }
    }

    // Geometry functions

    template <std::floating_point T>
    constexpr T degrees(T rad) noexcept {
        return rad * T{180} * std::numbers::inv_pi_v<T>;
    }

    template <std::floating_point T>
    constexpr T radians(T deg) noexcept {
        return deg * std::numbers::pi_v<T> / T{180};
    }

    namespace Detail {

        template <std::size_t N, std::floating_point T>
        inline const T sphere_surface_coeff
            = T{2} * std::exp((T{N} / T{2}) * std::log(std::numbers::pi_v<T>) - std::lgamma(T{N} / T{2}));

        template <std::floating_point T>
        inline const T sphere_surface_coeff<0, T> = T{1};

        template <std::floating_point T>
        inline const T sphere_surface_coeff<1, T> = T{2};

        template <std::floating_point T>
        inline const T sphere_surface_coeff<2, T> = T{2} * std::numbers::pi_v<T>;

        template <std::floating_point T>
        inline const T sphere_surface_coeff<3, T> = T{4} * std::numbers::pi_v<T>;

        template <std::size_t N, std::floating_point T>
        inline const T sphere_volume_coeff
            = std::exp((T{N} / T{2}) * std::log(std::numbers::pi_v<T>) - std::lgamma(T{N} / T{2} + T{1}));

        template <std::floating_point T>
        inline const T sphere_volume_coeff<0, T> = T{1};

        template <std::floating_point T>
        inline const T sphere_volume_coeff<1, T> = T{2};

        template <std::floating_point T>
        inline const T sphere_volume_coeff<2, T> = std::numbers::pi_v<T>;

        template <std::floating_point T>
        inline const T sphere_volume_coeff<3, T> = (T{4} / T{3}) * std::numbers::pi_v<T>;

    }

    template <std::size_t N = 3, std::floating_point T>
    requires (N >= 1)
    T sphere_area_from_radius(T r) noexcept {
        return Detail::sphere_surface_coeff<N, T> * std::pow(r, T{N - 1});
    }

    template <std::size_t N = 3, std::floating_point T>
    requires (N >= 1)
    T sphere_volume_from_radius(T r) noexcept {
        return Detail::sphere_volume_coeff<N, T> * std::pow(r, T{N});
    }

    template <std::size_t N = 3, std::floating_point T>
    requires (N >= 2)
    T sphere_radius_from_area(T s) noexcept {
        return std::pow(s / Detail::sphere_surface_coeff<N, T>, T{1} / T{N - 1});
    }

    template <std::size_t N = 3, std::floating_point T>
    requires (N >= 1)
    T sphere_radius_from_volume(T v) noexcept {
        return std::pow(v / Detail::sphere_volume_coeff<N, T>, T{1} / T{N});
    }

    // Literals

    namespace Literals {

        constexpr float operator""_degf(long double rad) noexcept { return radians(static_cast<float>(rad)); }
        constexpr float operator""_degf(unsigned long long rad) noexcept { return radians(static_cast<float>(rad)); }
        constexpr double operator""_deg(long double rad) noexcept { return radians(static_cast<double>(rad)); }
        constexpr double operator""_deg(unsigned long long rad) noexcept { return radians(static_cast<double>(rad)); }
        constexpr long double operator""_degld(long double rad) noexcept { return radians(rad); }
        constexpr long double operator""_degld(unsigned long long rad) noexcept { return radians(static_cast<long double>(rad)); }

        constexpr std::int8_t operator""_i8(unsigned long long x) noexcept { return try_cast<std::int8_t>(x); }
        constexpr std::uint8_t operator""_u8(unsigned long long x) noexcept { return try_cast<std::uint8_t>(x); }
        constexpr std::int16_t operator""_i16(unsigned long long x) noexcept { return try_cast<std::int16_t>(x); }
        constexpr std::uint16_t operator""_u16(unsigned long long x) noexcept { return try_cast<std::uint16_t>(x); }
        constexpr std::int32_t operator""_i32(unsigned long long x) noexcept { return try_cast<std::int32_t>(x); }
        constexpr std::uint32_t operator""_u32(unsigned long long x) noexcept { return try_cast<std::uint32_t>(x); }
        constexpr std::int64_t operator""_i64(unsigned long long x) noexcept { return try_cast<std::int64_t>(x); }
        constexpr std::uint64_t operator""_u64(unsigned long long x) noexcept { return try_cast<std::uint64_t>(x); }

    }

}
