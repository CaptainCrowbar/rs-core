#pragma once

#include "rs-core/format.hpp"
#include "rs-core/global.hpp"
#include "rs-core/hash.hpp"
#include <algorithm>
#include <bit>
#include <compare>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <format>
#include <functional>
#include <limits>
#include <ranges>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>

namespace RS {

    class Uint128 {

    public:

        using word = std::uint64_t;

        constexpr Uint128() = default;
        template <std::integral T>
            constexpr explicit(std::signed_integral<T> || sizeof(T) > 2 * sizeof(word))
            Uint128(T t) noexcept;
        constexpr Uint128(word hi, word lo) noexcept: hi_{hi}, lo_{lo} {}
        explicit Uint128(std::string_view str, int base = 10);

        explicit constexpr operator bool() const noexcept { return hi_ != 0 || lo_ != 0; }
        template <std::integral T> constexpr explicit operator T() const noexcept;

        constexpr Uint128 operator~() const noexcept { return {~ hi_, ~ lo_}; }
        constexpr Uint128& operator++() noexcept { if (++lo_ == 0) { ++hi_; } return *this; }
        constexpr Uint128 operator++(int) noexcept { auto x = *this; ++*this; return x; }
        constexpr Uint128& operator--() noexcept { if (lo_-- == 0) { --hi_; } return *this; }
        constexpr Uint128 operator--(int) noexcept { auto x = *this; --*this; return x; }
        constexpr Uint128& operator+=(Uint128 y) noexcept;
        constexpr Uint128& operator-=(Uint128 y) noexcept;
        constexpr Uint128& operator*=(Uint128 y) noexcept;
        constexpr Uint128& operator/=(Uint128 y) noexcept { return *this = divide(y).first; }
        constexpr Uint128& operator%=(Uint128 y) noexcept { return *this = divide(y).second; }
        constexpr Uint128& operator&=(Uint128 y) noexcept { hi_ &= y.hi_; lo_ &= y.lo_; return *this; }
        constexpr Uint128& operator|=(Uint128 y) noexcept { hi_ |= y.hi_; lo_ |= y.lo_; return *this; }
        constexpr Uint128& operator^=(Uint128 y) noexcept { hi_ ^= y.hi_; lo_ ^= y.lo_; return *this; }
        constexpr Uint128& operator<<=(int y) noexcept;
        constexpr Uint128& operator>>=(int y) noexcept;

        constexpr int bit_width() const noexcept;
        constexpr std::pair<Uint128, Uint128> divide(Uint128 y) const noexcept;
        constexpr word high() const noexcept { return hi_; }
        constexpr word low() const noexcept { return lo_; }
        std::string str(int base = 10, std::size_t digits = 1) const;
        std::string hex() const { return str(16, 32); }

        friend constexpr bool operator==(Uint128 x, Uint128 y) noexcept = default;
        friend constexpr auto operator<=>(Uint128 x, Uint128 y) noexcept = default;

    private:

        word hi_ = 0;
        word lo_ = 0;

    };

        #ifdef __GNUC__
            using uint128_t = __uint128_t;
        #else
            using uint128_t = Uint128;
        #endif

        template <std::integral T>
        constexpr Uint128::Uint128(T t) noexcept {

            if constexpr (std::signed_integral<T>) {

                using limits = std::numeric_limits<T>;
                using U = std::make_unsigned_t<T>;

                U u;

                if (t >= 0) {
                    u = static_cast<U>(t);
                } else if (t == limits::min()) {
                    u = static_cast<U>(limits::max());
                } else {
                    u = static_cast<U>(- t) - 1;
                }

                *this = static_cast<Uint128>(u);

                if (t < 0) {
                    *this = ~ *this;
                }

            } else if constexpr (sizeof(T) > sizeof(word)) {

                hi_ = static_cast<word>(t >> 64);
                lo_ = static_cast<word>(t);

            } else {

                lo_ = t;

            }

        }

        inline Uint128::Uint128(std::string_view str, int base) {

            if (base < 2 || base > 36) {
                throw std::out_of_range(std::format("Number base ({}) is out of range (2-36)", base));
            } else if (str.empty()) {
                throw std::invalid_argument("Invalid number: empty string");
            }

            auto scale = static_cast<Uint128>(base);

            for (auto c: str) {

                auto digit = -1;

                if (c >= '0' && c <= '9') {
                    digit = c - '0';
                } else if (base > 10) {
                    if (c >= 'A' && c <= 'Z') {
                        digit = c - 'A' + 10;
                    } else if (c >= 'a' && c <= 'z') {
                        digit = c - 'a' + 10;
                    }
                }

                if (digit == -1) {
                    throw std::invalid_argument(std::format("Invalid base {} number: {:?}", base, str));
                }

                *this *= scale;
                *this += static_cast<Uint128>(digit);

            }

        }

        template <std::integral T>
        constexpr Uint128::operator T() const noexcept {
            if constexpr (sizeof(T) > sizeof(word)) {
                return (static_cast<T>(hi_) << 64) + static_cast<T>(lo_);
            } else {
                return static_cast<T>(lo_);
            }
        }

        constexpr Uint128 operator+(Uint128 x, Uint128 y) noexcept { auto z = x; z += y; return z; }
        constexpr Uint128 operator-(Uint128 x, Uint128 y) noexcept { auto z = x; z -= y; return z; }
        constexpr Uint128 operator/(Uint128 x, Uint128 y) noexcept { return x.divide(y).first; }
        constexpr Uint128 operator%(Uint128 x, Uint128 y) noexcept { return x.divide(y).second; }
        constexpr Uint128 operator&(Uint128 x, Uint128 y) noexcept { auto z = x; z &= y; return z; }
        constexpr Uint128 operator|(Uint128 x, Uint128 y) noexcept { auto z = x; z |= y; return z; }
        constexpr Uint128 operator^(Uint128 x, Uint128 y) noexcept { auto z = x; z ^= y; return z; }
        constexpr Uint128 operator<<(Uint128 x, int y) noexcept { auto z = x; z <<= y; return z; }
        constexpr Uint128 operator>>(Uint128 x, int y) noexcept { auto z = x; z >>= y; return z; }

        constexpr Uint128 operator*(Uint128 x, Uint128 y) noexcept {

            Uint128 z;

            for (auto a = 0; a < 128; a += 32) {
                auto c = (x >> a).low() & max32;
                for (auto b = 0; b < 128; b += 32) {
                    auto d = (y >> b).low() & max32;
                    z = z + (Uint128{c * d} << (a + b));
                }
            }

            return z;

        }

        constexpr Uint128& Uint128::operator+=(Uint128 y) noexcept {
            lo_ += y.lo_;
            hi_ += y.hi_ + static_cast<word>(lo_ < y.lo_);
            return *this;
        }

        constexpr Uint128& Uint128::operator-=(Uint128 y) noexcept {
            auto borrow = static_cast<word>(lo_ < y.lo_);
            lo_ -= y.lo_;
            hi_ -= y.hi_ + borrow;
            return *this;
        }

        constexpr Uint128& Uint128::operator*=(Uint128 y) noexcept {
            return *this = *this * y;
        }

        constexpr Uint128& Uint128::operator<<=(int y) noexcept {

            if (y >= 128) {
                hi_ = lo_ = 0;
            } else if (y >= 64) {
                hi_ = lo_ << (y - 64);
                lo_ = 0;
            } else if (y >= 1) {
                hi_ = (hi_ << y) + (lo_ >> (64 - y));
                lo_ <<= y;
            }

            return *this;

        }

        constexpr Uint128& Uint128::operator>>=(int y) noexcept {

            if (y >= 128) {
                hi_ = lo_ = 0;
            } else if (y >= 64) {
                lo_ = hi_ >> (y - 64);
                hi_ = 0;
            } else if (y >= 1) {
                lo_ = (lo_ >> y) + (hi_ << (64 - y));
                hi_ >>= y;
            }

            return *this;

        }

        constexpr int Uint128::bit_width() const noexcept {
            auto high_bits = std::bit_width(hi_);
            if (high_bits == 0) {
                return std::bit_width(lo_);
            } else {
                return high_bits + 64;
            }
        }

        constexpr std::pair<Uint128, Uint128> Uint128::divide(Uint128 y) const noexcept {

            if (*this < y) {
                return {{}, *this};
            }

            auto shift = bit_width() - y.bit_width();
            auto a = y << shift;
            auto b = Uint128{1} << shift;
            auto q = Uint128{0};
            auto r = *this;

            for (auto i = 0; i <= shift && r; ++i, a >>= 1, b >>= 1) {
                if (a <= r) {
                    r -= a;
                    q += b;
                }
            }

            return {q, r};

        }

        inline std::string Uint128::str(int base, std::size_t digits) const {

            if (base < 2 || base > 36) {
                throw std::out_of_range(std::format("Number base ({}) is out of range (2-36)", base));
            }

            std::string s;
            auto x = *this;
            auto y = static_cast<Uint128>(base);

            while (x) {
                auto [q,r] = x.divide(y);
                auto digit = static_cast<int>(r);
                if (digit < 10) {
                    digit += '0';
                } else {
                    digit += 'a' - 10;
                }
                s += static_cast<char>(digit);
                x = q;
            }

            std::ranges::reverse(s);

            if (s.size() < digits) {
                s.insert(0, digits - s.size(), '0');
            }

            return s;

        }

}

template <std::integral T>
struct std::common_type<RS::Uint128, T> {
    using type = RS::Uint128;
};

template <std::floating_point T>
struct std::common_type<RS::Uint128, T> {
    using type = T;
};

template <typename T>
struct std::common_type<T, RS::Uint128>:
std::common_type<RS::Uint128, T> {};

template <>
struct std::formatter<RS::Uint128>:
RS::CommonFormatter {

    int base = 10;
    std::size_t digits = 0;

    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {

        auto it = ctx.begin();

        for (; it != ctx.end() && *it != '}'; ++it) {
            if (*it == 'b' && base == 10) {
                base = 2;
            } else if (*it == 'x' && base == 10) {
                base = 16;
            } else if (*it >= '0' && *it <= '9') {
                digits = 10 * digits + static_cast<std::size_t>(*it - '0');
            } else {
                throw std::format_error{std::format("Invalid format: {:?}", *it)};
            }
        }

        if (digits == 0) {
            digits = 1;
        }

        return it;

    }

    template <typename FormatContext>
    auto format(RS::Uint128 u, FormatContext& ctx) const {
        return write_out(u.str(base, digits), ctx.out());
    }

};

template <>
struct std::hash<RS::Uint128> {
    constexpr std::size_t operator()(RS::Uint128 u) const noexcept {
        using subhash = hash<RS::Uint128::word>;
        return RS::hash_mix(subhash()(u.high()), subhash()(u.low()));
    }
};

template <>
class std::numeric_limits<RS::Uint128>:
public std::numeric_limits<void> {

public:

    static constexpr bool is_specialized  = true;
    static constexpr bool is_bounded      = true;
    static constexpr bool is_exact        = true;
    static constexpr bool is_integer      = true;
    static constexpr bool is_modulo       = true;
    static constexpr bool is_signed       = false;
    static constexpr int radix            = 2;
    static constexpr bool traps           = false;
    static constexpr int digits           = 128;
    static constexpr int digits10         = 38;

    static constexpr auto lowest() noexcept  { return RS::Uint128{}; }
    static constexpr auto max() noexcept     { return ~ RS::Uint128{}; }
    static constexpr auto min() noexcept     { return RS::Uint128{}; }

};
