#pragma once

#include "rs-core/format.hpp"
#include "rs-core/global.hpp"
#include "rs-core/hash.hpp"
#include <algorithm>
#include <array>
#include <bit>
#include <cmath>
#include <compare>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <format>
#include <functional>
#include <initializer_list>
#include <limits>
#include <ranges>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>

namespace RS {

    template <std::size_t N> class SmallUint;
    template <std::size_t N> class LargeUint;
    template <std::size_t N> using Uint = std::conditional_t<(N <= 64), SmallUint<N>, LargeUint<N>>;

    template <typename T> struct MetaSmallUintInstance: std::false_type {};
    template <std::size_t N> struct MetaSmallUintInstance<SmallUint<N>>: std::true_type {};
    template <typename T> concept SmallUintInstance = MetaSmallUintInstance<T>::value;
    template <typename T> struct MetaLargeUintInstance: std::false_type {};
    template <std::size_t N> struct MetaLargeUintInstance<LargeUint<N>>: std::true_type {};
    template <typename T> concept LargeUintInstance = MetaLargeUintInstance<T>::value;
    template <typename T> concept UintInstance = SmallUintInstance<T> || LargeUintInstance<T>;

    using Uint128 = Uint<128>;
    using Uint256 = Uint<256>;
    using Uint512 = Uint<512>;
    using Uint1024 = Uint<1024>;

    #ifdef __GNUC__
        using uint128_t = __uint128_t;
    #else
        using uint128_t = Uint128;
    #endif

    namespace Detail {

        constexpr int find_digits10(std::size_t bits) noexcept {
            // Approximation to log10(2) is good for ~1e9 bits
            return static_cast<int>(bits * 8'651uz / 28'738uz);
        }

        template <std::unsigned_integral T>
        std::string unsigned_to_binary(T t, std::size_t digits = 8 * sizeof(T)) {
            std::string s(digits, '0');
            for (auto i = digits - 1; i != npos && t != 0; --i, t /= 2) {
                s[i] = static_cast<char>('0' + static_cast<int>(t % 2));
            }
            return s;
        }

        template <std::unsigned_integral T>
        std::string unsigned_to_hex(T t, std::size_t digits = 2 * sizeof(T)) {
            static constexpr const char* xdigits = "0123456789abcdef";
            std::string s(digits, '0');
            for (auto i = digits - 1; i != npos && t != 0; --i, t /= 16) {
                s[i] = xdigits[t % 16];
            }
            return s;
        }

        template <UintInstance U>
        bool parse_bitwise_integer(U& u, std::string_view str, int base, bool check) {

            if (base < 0 || base == 1 || base > 36) {
                throw std::invalid_argument(std::format("Invalid number base: {}", base));
            }

            if (str.empty()) {
                if (check) {
                    throw std::invalid_argument(std::format("Invalid base {} number: \"\"", base));
                } else {
                    return false;
                }
            }

            if (base == 0) {
                if (str.size() >= 2 && str[0] == '0' && (str[1] == 'B' || str[1] == 'b')) {
                    return parse_bitwise_integer(u, str.substr(2), 2, check);
                } else if (str.size() >= 2 && str[0] == '0' && (str[1] == 'X' || str[1] == 'x')) {
                    return parse_bitwise_integer(u, str.substr(2), 16, check);
                } else {
                    return parse_bitwise_integer(u, str, 10, check);
                }
            }

            auto max_d = static_cast<char>(base < 10 ? '0' + base : '9');
            auto max_uc = static_cast<char>(base + 'A' - 11);
            auto max_lc = static_cast<char>(max_uc + 32);
            auto digit = 0;
            U result;
            auto u_base = static_cast<U>(base);

            for (auto c: str) {
                if (c == '\'') {
                    continue;
                } else if (c >= '0' && c <= max_d) {
                    digit = c - '0';
                } else if (c >= 'A' && c <= max_uc) {
                    digit = c - 'A' + 10;
                } else if (c >= 'a' && c <= max_lc) {
                    digit = c - 'a' + 10;
                } else if (check) {
                    throw std::invalid_argument(std::format("Invalid base {} number: {:?}", base, str));
                } else {
                    return false;
                }
                result = u_base * result + static_cast<unsigned>(digit);
            }

            u = result;

            return true;

        }

    }

    template <std::size_t N>
    class SmallUint {

    private:

        static_assert(N >= 1 && N <= 64);

        using value_type = std::conditional_t<(N <= 8), std::uint8_t,
            std::conditional_t<(N <= 16), std::uint16_t,
            std::conditional_t<(N <= 32), std::uint32_t, std::uint64_t>>>;

        static constexpr value_type mask = static_cast<value_type>(1ull << N / 2 << (N + 1) / 2) - value_type{1};

        value_type value_ = 0;

    public:

        static constexpr std::size_t bits = N;
        static constexpr std::size_t bytes = sizeof(value_type);
        static constexpr std::size_t hex_digits = (N + 3) / 4;

        constexpr SmallUint() noexcept = default;
        template <std::unsigned_integral T> requires (sizeof(T) <= N / 8) constexpr SmallUint(T t) noexcept;
        template <std::unsigned_integral T> requires (sizeof(T) > N / 8) constexpr explicit SmallUint(T t) noexcept;
        template <std::signed_integral T> constexpr explicit SmallUint(T t) noexcept;
        template <std::size_t M> requires (M < N) constexpr SmallUint(SmallUint<M> x) noexcept;
        template <std::size_t M> requires (M > N) constexpr explicit SmallUint(SmallUint<M> x) noexcept;
        constexpr explicit SmallUint(std::initializer_list<std::uint64_t> init) noexcept;
        explicit SmallUint(std::string_view str, int base = 0) { *this = parse(str, base); }

        std::string bin() const { return Detail::unsigned_to_binary(value_, N); }
        std::string dec() const { return std::to_string(value_); }
        std::string hex() const { return Detail::unsigned_to_hex(value_, hex_digits); }
        constexpr void clear() noexcept { value_ = 0; }
        constexpr unsigned char* data() noexcept { return reinterpret_cast<unsigned char*>(&value_); }
        constexpr const unsigned char* data() const noexcept { return reinterpret_cast<const unsigned char*>(&value_); }
        template <Arithmetic T> constexpr bool fits_in() const noexcept { return significant_bits() <= std::numeric_limits<T>::digits; }
        constexpr std::size_t hash() const noexcept { return std::hash<value_type>{}(value_); }
        constexpr std::size_t significant_bits() const noexcept { return static_cast<std::size_t>(std::bit_width(value_)); }

        constexpr explicit operator bool() const noexcept { return value_ != 0; }
        template <Arithmetic T> constexpr explicit operator T() const noexcept { return static_cast<T>(value_); }

        constexpr SmallUint operator+() const noexcept { return *this; }
        constexpr SmallUint operator-() const noexcept { auto x = ~ *this; ++x; return x; }
        constexpr SmallUint operator~() const noexcept { return static_cast<SmallUint>(~ static_cast<std::uint64_t>(value_)); }
        constexpr SmallUint& operator++() noexcept { ++value_; value_ &= mask; return *this; }
        constexpr SmallUint operator++(int) noexcept { auto x = *this; ++*this; return x; }
        constexpr SmallUint& operator--() noexcept { --value_; value_ &= mask; return *this; }
        constexpr SmallUint operator--(int) noexcept { auto x = *this; --*this; return x; }
        constexpr SmallUint& operator+=(SmallUint y) noexcept { value_ += y.value_; value_ &= mask; return *this; }
        constexpr SmallUint& operator-=(SmallUint y) noexcept { value_ -= y.value_; value_ &= mask; return *this; }
        constexpr SmallUint& operator*=(SmallUint y) noexcept { value_ *= y.value_; value_ &= mask; return *this; }
        constexpr SmallUint& operator/=(SmallUint y) noexcept { value_ /= y.value_; return *this; }
        constexpr SmallUint& operator%=(SmallUint y) noexcept { value_ %= y.value_; return *this; }
        constexpr SmallUint& operator&=(SmallUint y) noexcept { value_ &= y.value_; return *this; }
        constexpr SmallUint& operator|=(SmallUint y) noexcept { value_ |= y.value_; return *this; }
        constexpr SmallUint& operator^=(SmallUint y) noexcept { value_ ^= y.value_; return *this; }
        constexpr SmallUint& operator<<=(int y) noexcept;
        constexpr SmallUint& operator>>=(int y) noexcept;

        constexpr static void divide(SmallUint x, SmallUint y, SmallUint& q, SmallUint& r) noexcept { q = x / y; r = x % y; }
        static SmallUint from_double(double x) noexcept { return static_cast<SmallUint>(static_cast<std::uint64_t>(x)); }
        constexpr static SmallUint max() noexcept { return static_cast<SmallUint>(mask); }
        static SmallUint parse(std::string_view str, int base = 0) { SmallUint x; Detail::parse_bitwise_integer(x, str, base, true); return x; }
        static bool try_parse(std::string_view str, SmallUint& x, int base = 0) noexcept { return Detail::parse_bitwise_integer(x, str, base, false); }

        friend constexpr SmallUint rotl(SmallUint x, int y) noexcept { y %= static_cast<int>(N); return (x << y) | (x >> (static_cast<int>(N) - y)); }
        friend constexpr SmallUint rotr(SmallUint x, int y) noexcept { y %= static_cast<int>(N); return (x >> y) | (x << (static_cast<int>(N) - y)); }
        friend constexpr SmallUint operator+(SmallUint x, SmallUint y) noexcept { auto z = x; z += y; return z; }
        friend constexpr SmallUint operator-(SmallUint x, SmallUint y) noexcept { auto z = x; z -= y; return z; }
        friend constexpr SmallUint operator*(SmallUint x, SmallUint y) noexcept { auto z = x; z *= y; return z; }
        friend constexpr SmallUint operator/(SmallUint x, SmallUint y) noexcept { auto z = x; z /= y; return z; }
        friend constexpr SmallUint operator%(SmallUint x, SmallUint y) noexcept { auto z = x; z %= y; return z; }
        friend constexpr SmallUint operator&(SmallUint x, SmallUint y) noexcept { auto z = x; z &= y; return z; }
        friend constexpr SmallUint operator|(SmallUint x, SmallUint y) noexcept { auto z = x; z |= y; return z; }
        friend constexpr SmallUint operator^(SmallUint x, SmallUint y) noexcept { auto z = x; z ^= y; return z; }
        friend constexpr SmallUint operator<<(SmallUint x, int y) noexcept { auto z = x; z <<= y; return z; }
        friend constexpr SmallUint operator>>(SmallUint x, int y) noexcept { auto z = x; z >>= y; return z; }
        friend constexpr bool operator==(SmallUint x, SmallUint y) noexcept = default;
        friend constexpr auto operator<=>(SmallUint x, SmallUint y) noexcept = default;

        friend std::string to_string(SmallUint x) { return x.dec(); }

    };

        template <std::size_t N>
        template <std::unsigned_integral T>
        requires (sizeof(T) <= N / 8)
        constexpr SmallUint<N>::SmallUint(T t) noexcept:
        value_{static_cast<value_type>(t)} {
            value_ &= mask;
        }

        template <std::size_t N>
        template <std::unsigned_integral T>
        requires (sizeof(T) > N / 8)
        constexpr SmallUint<N>::SmallUint(T t) noexcept:
        value_{static_cast<value_type>(t)} {
            value_ &= mask;
        }

        template <std::size_t N>
        template <std::signed_integral T>
        constexpr SmallUint<N>::SmallUint(T t) noexcept:
        value_{static_cast<value_type>(t)} {
            value_ &= mask;
        }

        template <std::size_t N>
        template <std::size_t M>
        requires (M < N)
        constexpr SmallUint<N>::SmallUint(SmallUint<M> x) noexcept:
        SmallUint{static_cast<value_type>(x)} {
            value_ &= mask;
        }

        template <std::size_t N>
        template <std::size_t M>
        requires (M > N)
        constexpr SmallUint<N>::SmallUint(SmallUint<M> x) noexcept:
        SmallUint{static_cast<value_type>(x)} {
            value_ &= mask;
        }

        template <std::size_t N>
        constexpr SmallUint<N>::SmallUint(std::initializer_list<std::uint64_t> init) noexcept {
            if (init.size() > 0) {
                value_ = static_cast<value_type>(*init.begin());
            }
            value_ &= mask;
        }

        template <std::size_t N>
        constexpr SmallUint<N>& SmallUint<N>::operator<<=(int y) noexcept {
            if (y < 0) {
                *this >>= - y;
            } else if (std::size_t(y) < N) {
                value_ = (value_ << y) & mask;
            } else {
                value_ = 0;
            }
            return *this;
        }

        template <std::size_t N>
        constexpr SmallUint<N>& SmallUint<N>::operator>>=(int y) noexcept {
            if (y < 0) {
                *this <<= - y;
            } else if (std::size_t(y) < N) {
                value_ >>= y;
            } else {
                value_ = 0;
            }
            return *this;
        }

    template <std::size_t N>
    class LargeUint {

    private:

        static_assert(N >= 1);

        using unit_type = std::uint32_t;

        static constexpr std::size_t unit_bytes = sizeof(unit_type);
        static constexpr std::size_t unit_bits = 8 * unit_bytes;
        static constexpr std::size_t units = (N + unit_bits - 1) / unit_bits;
        static constexpr std::size_t final_bits = N % unit_bits ? N % unit_bits : unit_bits;
        static constexpr std::size_t final_hex_digits = (final_bits + 3) / 4;
        static constexpr std::size_t excess_bits = unit_bits - final_bits;
        static constexpr auto unit_mask = ~ unit_type(0);
        static constexpr auto high_mask = unit_mask >> excess_bits;

        std::array<unit_type, units> array_ {{}}; // Little endian order

    public:

        static constexpr std::size_t bits = N;
        static constexpr std::size_t bytes = units * unit_bytes;
        static constexpr std::size_t hex_digits = (N + 3) / 4;

        constexpr LargeUint() noexcept = default;
        template <std::unsigned_integral T> requires (sizeof(T) <= N / 8) constexpr LargeUint(T t) noexcept;
        template <std::unsigned_integral T> requires (sizeof(T) > N / 8) constexpr explicit LargeUint(T t) noexcept;
        template <std::signed_integral T> constexpr explicit LargeUint(T t) noexcept;
        template <std::size_t M> requires (M < N) constexpr LargeUint(SmallUint<M> x) noexcept;
        template <std::size_t M> requires (M > N) constexpr explicit LargeUint(SmallUint<M> x) noexcept;
        template <std::size_t M> requires (M < N) constexpr LargeUint(LargeUint<M> x) noexcept;
        template <std::size_t M> requires (M > N) constexpr explicit LargeUint(LargeUint<M> x) noexcept;
        constexpr explicit LargeUint(std::initializer_list<std::uint64_t> init) noexcept;
        explicit LargeUint(std::string_view str, int base = 0) { *this = parse(str, base); }

        std::string bin() const;
        std::string dec() const;
        std::string hex() const;
        constexpr void clear() noexcept { array_ = {{}}; }
        constexpr unsigned char* data() noexcept { return reinterpret_cast<unsigned char*>(array_.data()); }
        constexpr const unsigned char* data() const noexcept { return reinterpret_cast<const unsigned char*>(array_.data()); }
        template <Arithmetic T> constexpr bool fits_in() const noexcept { return significant_bits() <= std::numeric_limits<T>::digits; }
        constexpr std::size_t hash() const noexcept;
        constexpr std::size_t significant_bits() const noexcept;

        constexpr explicit operator bool() const noexcept;
        template <Arithmetic T> constexpr explicit operator T() const noexcept;
        template <std::size_t M> constexpr explicit operator SmallUint<M>() const noexcept;

        constexpr LargeUint operator+() const noexcept { return *this; }
        constexpr LargeUint operator-() const noexcept { auto x = ~ *this; ++x; return x; }
        constexpr LargeUint operator~() const noexcept;
        constexpr LargeUint& operator++() noexcept;
        constexpr LargeUint operator++(int) noexcept { auto x = *this; ++*this; return x; }
        constexpr LargeUint& operator--() noexcept;
        constexpr LargeUint operator--(int) noexcept { auto x = *this; --*this; return x; }
        constexpr LargeUint& operator+=(const LargeUint& y) noexcept;
        constexpr LargeUint& operator-=(const LargeUint& y) noexcept;
        constexpr LargeUint& operator*=(const LargeUint& y) noexcept;
        constexpr LargeUint& operator/=(const LargeUint& y) noexcept { LargeUint q, r; divide(*this, y, q, r); *this = q; return *this; }
        constexpr LargeUint& operator%=(const LargeUint& y) noexcept { LargeUint q, r; divide(*this, y, q, r); *this = r; return *this; }
        constexpr LargeUint& operator&=(const LargeUint& y) noexcept;
        constexpr LargeUint& operator|=(const LargeUint& y) noexcept;
        constexpr LargeUint& operator^=(const LargeUint& y) noexcept;
        constexpr LargeUint& operator<<=(int y) noexcept;
        constexpr LargeUint& operator>>=(int y) noexcept;

        constexpr static void divide(const LargeUint& x, const LargeUint& y, LargeUint& q, LargeUint& r) noexcept;
        static LargeUint from_double(double x) noexcept;
        constexpr static LargeUint max() noexcept;
        static LargeUint parse(std::string_view str, int base = 0) { LargeUint x; Detail::parse_bitwise_integer(x, str, base, true); return x; }
        static bool try_parse(std::string_view str, LargeUint& x, int base = 0) noexcept { return Detail::parse_bitwise_integer(x, str, base, false); }

        friend constexpr LargeUint rotl(const LargeUint& x, int y) noexcept { y %= static_cast<int>(N); return (x << y) | (x >> (static_cast<int>(N) - y)); }
        friend constexpr LargeUint rotr(const LargeUint& x, int y) noexcept { y %= static_cast<int>(N); return (x >> y) | (x << (static_cast<int>(N) - y)); }
        friend constexpr LargeUint operator+(const LargeUint& x, const LargeUint& y) noexcept { auto z = x; z += y; return z; }
        friend constexpr LargeUint operator-(const LargeUint& x, const LargeUint& y) noexcept { auto z = x; z -= y; return z; }
        friend constexpr LargeUint operator*(const LargeUint& x, const LargeUint& y) noexcept { auto z = x; z *= y; return z; }
        friend constexpr LargeUint operator/(const LargeUint& x, const LargeUint& y) noexcept { auto z = x; z /= y; return z; }
        friend constexpr LargeUint operator%(const LargeUint& x, const LargeUint& y) noexcept { auto z = x; z %= y; return z; }
        friend constexpr LargeUint operator&(const LargeUint& x, const LargeUint& y) noexcept { auto z = x; z &= y; return z; }
        friend constexpr LargeUint operator|(const LargeUint& x, const LargeUint& y) noexcept { auto z = x; z |= y; return z; }
        friend constexpr LargeUint operator^(const LargeUint& x, const LargeUint& y) noexcept { auto z = x; z ^= y; return z; }
        friend constexpr LargeUint operator<<(const LargeUint& x, int y) noexcept { auto z = x; z <<= y; return z; }
        friend constexpr LargeUint operator>>(const LargeUint& x, int y) noexcept { auto z = x; z >>= y; return z; }
        friend constexpr bool operator==(const LargeUint& x, const LargeUint& y) noexcept { return x.compare(y) == 0; }
        friend constexpr auto operator<=>(const LargeUint& x, const LargeUint& y) noexcept { return x.compare(y); }

        friend std::string to_string(LargeUint x) { return x.dec(); }

    private:

        constexpr std::strong_ordering compare(const LargeUint& y) const noexcept;
        constexpr void do_mask() noexcept { array_[units - 1] &= high_mask; }

        constexpr static void add_with_carry(unit_type& x, unit_type y, unit_type& c) noexcept;

    };

        template <std::size_t N>
        template <std::unsigned_integral T>
        requires (sizeof(T) <= N / 8)
        constexpr LargeUint<N>::LargeUint(T t) noexcept {
            array_[0] = static_cast<unit_type>(t);
            if constexpr (units > 1 && sizeof(T) > sizeof(unit_type)) {
                array_[1] = static_cast<unit_type>(t >> unit_bits);
            }
            do_mask();
        }

        template <std::size_t N>
        template <std::unsigned_integral T>
        requires (sizeof(T) > N / 8)
        constexpr LargeUint<N>::LargeUint(T t) noexcept {
            array_[0] = static_cast<unit_type>(t);
            if constexpr (units > 1 && sizeof(T) > sizeof(unit_type)) {
                array_[1] = static_cast<unit_type>(t >> unit_bits);
            }
            do_mask();
        }

        template <std::size_t N>
        template <std::signed_integral T>
        constexpr LargeUint<N>::LargeUint(T t) noexcept {
            array_[0] = static_cast<unit_type>(t);
            if constexpr (units > 1 && sizeof(T) > sizeof(unit_type)) {
                array_[1] = static_cast<unit_type>(t >> unit_bits);
            }
            do_mask();
        }

        template <std::size_t N>
        template <std::size_t M>
        requires (M < N)
        constexpr LargeUint<N>::LargeUint(SmallUint<M> x) noexcept:
        LargeUint{static_cast<std::uint64_t>(x)} {
            do_mask();
        }

        template <std::size_t N>
        template <std::size_t M>
        requires (M > N)
        constexpr LargeUint<N>::LargeUint(SmallUint<M> x) noexcept:
        LargeUint{static_cast<std::uint64_t>(x)} {
            do_mask();
        }

        template <std::size_t N>
        template <std::size_t M>
        requires (M < N)
        constexpr LargeUint<N>::LargeUint(LargeUint<M> x) noexcept {
            auto common_units = (M + unit_bits - 1) / unit_bits;
            auto xdata = reinterpret_cast<const unit_type*>(x.data());
            auto i = 0uz;
            for (; i < common_units; ++i) {
                array_[i] = xdata[i];
            }
            do_mask();
        }

        template <std::size_t N>
        template <std::size_t M>
        requires (M > N)
        constexpr LargeUint<N>::LargeUint(LargeUint<M> x) noexcept {
            auto common_units = (N + unit_bits - 1) / unit_bits;
            auto xdata = reinterpret_cast<const unit_type*>(x.data());
            auto i = 0uz;
            for (; i < common_units; ++i) {
                array_[i] = xdata[i];
            }
            do_mask();
        }

        template <std::size_t N>
        constexpr LargeUint<N>::LargeUint(std::initializer_list<std::uint64_t> init) noexcept {
            auto ptr = init.begin();
            auto len = init.size();
            for (auto i = len - 1uz, j = 0uz; i != npos && j < units; --i, j += 2) {
                array_[j] = static_cast<unit_type>(ptr[i]);
                if (j + 1 < units) {
                    array_[j + 1] = static_cast<unit_type>(ptr[i] >> unit_bits);
                }
            }
            do_mask();
        }

        template <std::size_t N>
        std::string LargeUint<N>::bin() const {
            std::string s;
            s.reserve(N);
            s = Detail::unsigned_to_binary(array_[units - 1], final_bits);
            for (auto i = units - 2; i != npos; --i) {
                s += Detail::unsigned_to_binary(array_[i]);
            }
            return s;
        }

        template <std::size_t N>
        std::string LargeUint<N>::dec() const {
            std::string s;
            auto x = *this;
            LargeUint base{10};
            LargeUint q, r;
            do {
                divide(x, base, q, r);
                s += static_cast<char>(static_cast<int>(r.array_[0]) + '0');
                x = q;
            } while (x);
            std::ranges::reverse(s);
            return s;
        }

        template <std::size_t N>
        std::string LargeUint<N>::hex() const {
            std::string s;
            s.reserve(hex_digits);
            s = Detail::unsigned_to_hex(array_[units - 1], final_hex_digits);
            for (auto i = units - 2; i != npos; --i) {
                s += Detail::unsigned_to_hex(array_[i]);
            }
            return s;
        }

        template <std::size_t N>
        constexpr std::size_t LargeUint<N>::hash() const noexcept {
            return hash_mix(array_);
            // auto h = 0uz;
            // for (auto x: array_) {
            //     h ^= (h << 6) + (h >> 2) + std::hash<std::uint64_t>()(x) + 0x9e3779b9ul;
            // }
            // return h;
        }

        template <std::size_t N>
        constexpr std::size_t LargeUint<N>::significant_bits() const noexcept {
            auto i = units - 1;
            while (i != npos && array_[i] == 0) {
                --i;
            }
            return i == npos ? 0uz : unit_bits * i + static_cast<std::size_t>(std::bit_width(array_[i]));
        }

        template <std::size_t N>
        constexpr LargeUint<N>::operator bool() const noexcept {
            for (auto u: array_) {
                if (u) {
                    return true;
                }
            }
            return false;
        }

        template <std::size_t N>
        template <Arithmetic T>
        constexpr LargeUint<N>::operator T() const noexcept {
            using L = std::numeric_limits<T>;
            using U = std::conditional_t<! L::is_integer, T,
                std::conditional_t<L::is_signed, std::int64_t, std::uint64_t>>;
            constexpr auto unit_factor = static_cast<U>(1ull << unit_bits);
            U result = 0;
            for (auto i = units - 1; i != npos; --i) {
                result = result * unit_factor + array_[i];
            }
            return static_cast<T>(result);
        }

        template <std::size_t N>
        template <std::size_t M>
        constexpr LargeUint<N>::operator SmallUint<M>() const noexcept {
            return static_cast<SmallUint<M>>(static_cast<std::uint64_t>(*this));
        }

        template <std::size_t N>
        constexpr LargeUint<N> LargeUint<N>::operator~() const noexcept {
            auto y = *this;
            for (auto& u: y.array_) {
                u = ~ u;
            }
            y.do_mask();
            return y;
        }

        template <std::size_t N>
        constexpr LargeUint<N>& LargeUint<N>::operator++() noexcept {
            ++array_[0];
            for (auto i = 1uz; i < units && array_[i - 1] == 0; ++i) {
                ++array_[i];
            }
            do_mask();
            return *this;
        }

        template <std::size_t N>
        constexpr LargeUint<N>& LargeUint<N>::operator--() noexcept {
            --array_[0];
            for (auto i = 1uz; i < units && array_[i - 1] == unit_mask; ++i) {
                --array_[i];
            }
            do_mask();
            return *this;
        }

        template <std::size_t N>
        constexpr LargeUint<N>& LargeUint<N>::operator+=(const LargeUint& y) noexcept {
            unit_type carry = 0;
            for (auto i = 0uz; i < units; ++i) {
                add_with_carry(array_[i], y.array_[i], carry);
            }
            do_mask();
            return *this;
        }

        template <std::size_t N>
        constexpr LargeUint<N>& LargeUint<N>::operator-=(const LargeUint& y) noexcept {
            unit_type borrow = 0;
            unit_type next = 0;
            for (auto i = 0uz; i < units; ++i) {
                next = static_cast<unit_type>(array_[i] < y.array_[i] || (array_[i] == y.array_[i] && borrow));
                array_[i] -= y.array_[i] + borrow;
                borrow = next;
            }
            do_mask();
            return *this;
        }

        template <std::size_t N>
        constexpr LargeUint<N>& LargeUint<N>::operator*=(const LargeUint& y) noexcept {
            LargeUint z;
            for (auto i = 0uz; i < units; ++i) {
                for (auto j = 0uz; j < units - i; ++j) {
                    auto k = i + j;
                    auto p = static_cast<std::uint64_t>(array_[i]) * static_cast<std::uint64_t>(y.array_[j]);
                    unit_type carry = 0;
                    add_with_carry(z.array_[k], unit_type(p), carry);
                    if (++k < units) {
                        add_with_carry(z.array_[k], unit_type(p >> unit_bits), carry);
                        for (++k; k < units && carry; ++k) {
                            add_with_carry(z.array_[k], 0, carry);
                        }
                    }
                }
            }
            *this = z;
            do_mask();
            return *this;
        }

        template <std::size_t N>
        constexpr LargeUint<N>& LargeUint<N>::operator&=(const LargeUint& y) noexcept {
            for (auto i = 0uz; i < units; ++i) {
                array_[i] &= y.array_[i];
            }
            return *this;
        }

        template <std::size_t N>
        constexpr LargeUint<N>& LargeUint<N>::operator|=(const LargeUint& y) noexcept {
            for (auto i = 0uz; i < units; ++i) {
                array_[i] |= y.array_[i];
            }
            return *this;
        }

        template <std::size_t N>
        constexpr LargeUint<N>& LargeUint<N>::operator^=(const LargeUint& y) noexcept {
            for (auto i = 0uz; i < units; ++i) {
                array_[i] ^= y.array_[i];
            }
            return *this;
        }

        template <std::size_t N>
        constexpr LargeUint<N>& LargeUint<N>::operator<<=(int y) noexcept {
            if (y < 0) {
                *this >>= - y;
            } else if (static_cast<std::size_t>(y) >= N) {
                clear();
            } else {
                auto int_unit_bits = static_cast<int>(unit_bits);
                auto skip = static_cast<std::size_t>(y / int_unit_bits);
                auto keep = units - skip;
                if (skip) {
                    for (auto i = keep - 1; i != npos; --i) {
                        array_[i + skip] = array_[i];
                    }
                    for (auto i = 0uz; i < skip; ++i) {
                        array_[i] = 0;
                    }
                    y %= int_unit_bits;
                }
                unit_type carry = 0;
                unit_type next = 0;
                if (y) {
                    for (auto i = skip; i < units; ++i) {
                        next = array_[i] >> (int_unit_bits - y);
                        array_[i] <<= y;
                        array_[i] += carry;
                        carry = next;
                    }
                }
                do_mask();
            }
            return *this;
        }

        template <std::size_t N>
        constexpr LargeUint<N>& LargeUint<N>::operator>>=(int y) noexcept {
            if (y < 0) {
                *this <<= - y;
            } else if (static_cast<std::size_t>(y) >= N) {
                clear();
            } else {
                auto int_unit_bits = static_cast<int>(unit_bits);
                auto skip = static_cast<std::size_t>(y / int_unit_bits);
                auto keep = units - skip;
                if (skip) {
                    for (auto i = 0uz; i < keep; ++i) {
                        array_[i] = array_[i + skip];
                    }
                    for (auto i = keep; i < units; ++i) {
                        array_[i] = 0;
                    }
                    y %= int_unit_bits;
                }
                unit_type carry = 0;
                unit_type next = 0;
                if (y) {
                    for (auto i = keep - 1; i != npos; --i) {
                        next = array_[i] << (int_unit_bits - y);
                        array_[i] >>= y;
                        array_[i] += carry;
                        carry = next;
                    }
                }
            }
            return *this;
        }

        template <std::size_t N>
        constexpr void LargeUint<N>::divide(const LargeUint& x, const LargeUint& y, LargeUint& q, LargeUint& r) noexcept {
            q.clear();
            r = x;
            if (x < y) {
                return;
            }
            auto shift = static_cast<int>(x.significant_bits()) - static_cast<int>(y.significant_bits());
            auto a = y << shift;
            auto b = LargeUint{1} << shift;
            for (auto i = 0; i <= shift && r; ++i, a >>= 1, b >>= 1) {
                if (a <= r) {
                    r -= a;
                    q += b;
                }
            }
        }

        template <std::size_t N>
        LargeUint<N> LargeUint<N>::from_double(double x) noexcept {
            auto exp = 0;
            auto sig = std::frexp(x, &exp);
            auto shift = std::min(static_cast<int>(N), 63);
            sig = std::ldexp(sig, shift);
            exp -= shift;
            auto num = static_cast<LargeUint>(static_cast<std::uint64_t>(sig));
            num <<= exp;
            return num;
        }

        template <std::size_t N>
        constexpr LargeUint<N> LargeUint<N>::max() noexcept {
            LargeUint x;
            for (auto& u: x.array_) {
                u = unit_mask;
            }
            x.do_mask();
            return x;
        }

        template <std::size_t N>
        constexpr std::strong_ordering LargeUint<N>::compare(const LargeUint& y) const noexcept {
            for (auto i = units - 1; i != npos; --i) {
                auto c = array_[i] <=> y.array_[i];
                if (c != 0) {
                    return c;
                }
            }
            return std::strong_ordering::equal;
        }

        template <std::size_t N>
        constexpr void LargeUint<N>::add_with_carry(unit_type& x, unit_type y, unit_type& c) noexcept {
            x += y + c;
            c = static_cast<unit_type>(x < y || (x == y && c != 0));
        }

    constexpr auto max128 = ~ uint128_t{0};

    namespace Literals {

        inline Uint128 operator""_u128(const char* ptr) { return Uint128{std::string_view{ptr}}; }
        inline Uint256 operator""_u256(const char* ptr) { return Uint256{std::string_view{ptr}}; }
        inline Uint512 operator""_u512(const char* ptr) { return Uint512{std::string_view{ptr}}; }
        inline Uint1024 operator""_u1024(const char* ptr) { return Uint1024{std::string_view{ptr}}; }

    }

}

template <std::size_t N>
struct std::formatter<RS::SmallUint<N>>:
RS::CommonFormatter {

    std::string flags;

    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return parse_helper(ctx, "bx", &flags);
    }

    template <typename FormatContext>
    auto format(RS::SmallUint<N> x, FormatContext& ctx) const {
        std::string s;
        switch (flags[0]) {
            case 'b':  s = x.bin(); break;
            case 'x':  s = x.hex(); break;
            default:   s = x.dec(); break;
        }
        write_out(s, ctx.out());
        return ctx.out();
    }

};

template <std::size_t N>
struct std::formatter<RS::LargeUint<N>>:
RS::CommonFormatter {

    std::string flags;

    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return parse_helper(ctx, "bx", &flags);
    }

    template <typename FormatContext>
    auto format(RS::LargeUint<N> x, FormatContext& ctx) const {
        std::string s;
        switch (flags[0]) {
            case 'b':  s = x.bin(); break;
            case 'x':  s = x.hex(); break;
            default:   s = x.dec(); break;
        }
        write_out(s, ctx.out());
        return ctx.out();
    }

};

template <std::size_t N>
struct std::hash<RS::SmallUint<N>> {
    auto operator()(RS::SmallUint<N> x) const noexcept { return x.hash(); }
};

template <std::size_t N>
struct std::hash<RS::LargeUint<N>> {
    auto operator()(RS::LargeUint<N> x) const noexcept { return x.hash(); }
};

template <std::size_t N>
class std::numeric_limits<RS::SmallUint<N>> {

private:

    using U = RS::SmallUint<N>;

public:

    static constexpr bool is_specialized = true;                   // All specializations
    static constexpr bool is_bounded = true;                       // Finite set of values
    static constexpr bool is_exact = true;                         // Exact representation
    static constexpr bool is_integer = true;                       // Integer
    static constexpr bool is_modulo = true;                        // Modulo arithmetic
    static constexpr bool is_signed = false;                       // Signed
    static constexpr bool traps = false;                           // Trap value exists
    static constexpr int digits = static_cast<int>(N);             // Radix digits in significand
    static constexpr int radix = 2;                                // Base of representation
    static constexpr int digits10 = RS::Detail::find_digits10(N);  // Decimals represented without change
    constexpr U lowest() noexcept { return U{0}; }                 // Min finite value
    constexpr U max() noexcept { return ~ U{0}; }                  // Max ﬁnite value
    constexpr U min() noexcept { return U{0}; }                    // Min positive float or min finite int
    static constexpr bool has_denorm_loss = false;                 // Loss of accuracy as denormalization
    static constexpr bool has_infinity = false;                    // Has positive infinity
    static constexpr bool has_quiet_NaN = false;                   // Has quiet NaN
    static constexpr bool has_signaling_NaN = false;               // Has signaling NaN
    static constexpr bool is_iec559 = false;                       // IEC 559 standard
    static constexpr bool tinyness_before = false;                 // Tinyness detected before rounding
    static constexpr int max_digits10 = 0;                         // Decimals required for different values
    static constexpr int max_exponent10 = 0;                       // Max positive decimal exponent
    static constexpr int max_exponent = 0;                         // Max positive exponent
    static constexpr int min_exponent10 = 0;                       // Min negative decimal exponent
    static constexpr int min_exponent = 0;                         // Min negative exponent
    constexpr U denorm_min() noexcept { return {}; }               // Min positive denormalized value
    constexpr U epsilon() noexcept { return {}; }                  // Difference between 1 and next value
    constexpr U infinity() noexcept { return {}; }                 // Positive infinity
    constexpr U quiet_NaN() noexcept { return {}; }                // Quiet NaN
    constexpr U round_error() noexcept { return {}; }              // Max rounding error
    constexpr U signaling_NaN() noexcept { return {}; }            // Signaling NaN
    static constexpr float_round_style round_style = {};           // Rounding style

};

template <std::size_t N>
class std::numeric_limits<RS::LargeUint<N>> {

private:

    using U = RS::LargeUint<N>;

public:

    static constexpr bool is_specialized = true;                   // All specializations
    static constexpr bool is_bounded = true;                       // Finite set of values
    static constexpr bool is_exact = true;                         // Exact representation
    static constexpr bool is_integer = true;                       // Integer
    static constexpr bool is_modulo = true;                        // Modulo arithmetic
    static constexpr bool is_signed = false;                       // Signed
    static constexpr bool traps = false;                           // Trap value exists
    static constexpr int digits = static_cast<int>(N);             // Radix digits in significand
    static constexpr int radix = 2;                                // Base of representation
    static constexpr int digits10 = RS::Detail::find_digits10(N);  // Decimals represented without change
    constexpr U lowest() noexcept { return U{0}; }                 // Min finite value
    constexpr U max() noexcept { return ~ U{0}; }                  // Max ﬁnite value
    constexpr U min() noexcept { return U{0}; }                    // Min positive float or min finite int
    static constexpr bool has_denorm_loss = false;                 // Loss of accuracy as denormalization
    static constexpr bool has_infinity = false;                    // Has positive infinity
    static constexpr bool has_quiet_NaN = false;                   // Has quiet NaN
    static constexpr bool has_signaling_NaN = false;               // Has signaling NaN
    static constexpr bool is_iec559 = false;                       // IEC 559 standard
    static constexpr bool tinyness_before = false;                 // Tinyness detected before rounding
    static constexpr int max_digits10 = 0;                         // Decimals required for different values
    static constexpr int max_exponent10 = 0;                       // Max positive decimal exponent
    static constexpr int max_exponent = 0;                         // Max positive exponent
    static constexpr int min_exponent10 = 0;                       // Min negative decimal exponent
    static constexpr int min_exponent = 0;                         // Min negative exponent
    constexpr U denorm_min() noexcept { return {}; }               // Min positive denormalized value
    constexpr U epsilon() noexcept { return {}; }                  // Difference between 1 and next value
    constexpr U infinity() noexcept { return {}; }                 // Positive infinity
    constexpr U quiet_NaN() noexcept { return {}; }                // Quiet NaN
    constexpr U round_error() noexcept { return {}; }              // Max rounding error
    constexpr U signaling_NaN() noexcept { return {}; }            // Signaling NaN
    static constexpr float_round_style round_style = {};           // Rounding style

};
