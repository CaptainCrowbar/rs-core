#pragma once

#include "rs-core/arithmetic.hpp"
#include "rs-core/format.hpp"
#include "rs-core/global.hpp"
#include "rs-core/hash.hpp"
#include "rs-core/mp-integer.hpp"
#include <cstddef>
#include <compare>
#include <concepts>
#include <format>
#include <functional>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>

namespace RS {

    template <typename T>
    class Rational {

    public:

        using integer_type = T;

        constexpr Rational() = default;
        constexpr Rational(const T& t): num_(t), den_(1) {}
        constexpr Rational(const T& n, const T& d): num_(n), den_(d) { reduce(); }
        constexpr Rational(const T& i, const T& n, const T& d);
        explicit Rational(std::string_view str);

        constexpr T num() const { return num_; }
        constexpr T den() const { return den_; }
        constexpr Rational abs() const { return num_ >= T{0} ? *this : - *this; }
        constexpr int sign() const noexcept { return num_ > T{0} ? 1 : num_ == T{0} ? 0 : -1; }
        constexpr T whole() const;
        constexpr Rational fraction() const;
        constexpr T truncate() const;
        constexpr Rational signed_fraction() const;
        constexpr std::size_t hash() const noexcept { std::hash<T> ht; return hash_mix(ht(num_), ht(den_)); }
        std::string mixed() const;
        std::string str() const;
        std::string rs_core_format(std::string_view flags) const;

        constexpr explicit operator bool() const noexcept { return num_ != T{0}; }
        constexpr bool operator!() const noexcept { return num_ == T{0}; }
        constexpr Rational operator+() const { return *this; }
        constexpr Rational operator-() const { return unchecked(- num_, den_); }
        constexpr Rational& operator+=(const Rational& y) { return *this = *this + y;  }
        constexpr Rational& operator-=(const Rational& y) { return *this = *this - y;  }
        constexpr Rational& operator*=(const Rational& y) { num_ *= y.num_; den_ *= y.den_; reduce(); return *this; }
        constexpr Rational& operator/=(const Rational& y) { num_ *= y.den_; den_ *= y.num_; reduce(); return *this; }

        static std::optional<Rational> parse(std::string_view str);

    private:

        T num_{0};
        T den_{1}; // Always positive

        constexpr void reduce();

        constexpr static Rational unchecked(const T& n, const T& d);

    };

    using IntRational = Rational<int>;
    using MPRational = Rational<Integer>;

    template <typename T>
    constexpr Rational<T>::Rational(const T& i, const T& n, const T& d):
    num_(i * d), den_(d) {
        num_ += i < T{0} ? - n : n;
        reduce();
    }

    template <typename T>
    Rational<T>::Rational(std::string_view str) {
        auto r = parse(str);
        if (! r) {
            throw std::invalid_argument(std::format("Invalid rational: {:?}", str));
        }
        *this = std::move(*r);
    }

    template <typename T>
    constexpr T Rational<T>::whole() const {
        auto abs_this = abs();
        auto quo = abs_this.num_ / abs_this.den_;
        auto rem = abs_this.num_ % abs_this.den_;
        if (num_ < T{0}) {
            quo = - quo;
            if (rem != T{0}) {
                quo -= T{1};
            }
        }
        return quo;
    }

    template <typename T>
    constexpr Rational<T> Rational<T>::fraction() const {
        auto abs_this = abs();
        auto rem = abs_this.num_ % abs_this.den_;
        if (rem == T{0}) {
            return {};
        }
        if (num_ < T{0}) {
            rem = den_ - rem;
        }
        return {rem, den_};
    }

    template <typename T>
    constexpr T Rational<T>::truncate() const {
        auto abs_this = abs();
        auto quo = abs_this.num_ / abs_this.den_;
        if (num_ < T{0}) {
            quo = - quo;
        }
        return quo;
    }

    template <typename T>
    constexpr Rational<T> Rational<T>::signed_fraction() const {
        auto abs_this = abs();
        auto rem = abs_this.num_ % abs_this.den_;
        if (num_ < T{0}) {
            rem = - rem;
        }
        return {rem, den_};
    }

    template <typename T>
    std::string Rational<T>::mixed() const {

        if (num_ == T{0}) {
            return "0";
        }

        std::string out;

        if (num_ < T{0}) {
            out += '-';
        }

        auto abs_this = abs();
        auto quo = abs_this.num_ / abs_this.den_;
        auto rem = abs_this.num_ % abs_this.den_;

        if (quo != T{0}) {
            out += std::format("{}", quo);
            if (rem != T{0}) {
                out += ' ';
            }
        }

        if (rem != T{0}) {
            out += std::format("{}/{}", rem, den_);
        }

        return out;

    }

    template <typename T>
    std::string Rational<T>::str() const {
        if (den_ == T{1}) {
            return std::format("{}", num_);
        } else {
            return std::format("{}/{}", num_, den_);
        }
    }

    template <typename T>
    std::string Rational<T>::rs_core_format(std::string_view flags) const {
        return flags.contains('m') ? mixed() : str();
    }

    template <typename T>
    constexpr Rational<T> operator+(const Rational<T>& x, const Rational<T>& y) {
        auto multiple = lcm(x.den(), y.den());
        auto lhs = x.num() * (multiple / x.den());
        auto rhs = y.num() * (multiple / y.den());
        return {lhs + rhs, multiple};
    }

    template <typename T>
    constexpr Rational<T> operator-(const Rational<T>& x, const Rational<T>& y) {
        return x + - y;
    }

    template <typename T>
    constexpr Rational<T> operator*(const Rational<T>& x, const Rational<T>& y) {
        auto z = x;
        z *= y;
        return z;
    }

    template <typename T>
    constexpr Rational<T> operator/(const Rational<T>& x, const Rational<T>& y) {
        auto z = x;
        z /= y;
        return z;
    }

    template <typename T>
    constexpr bool operator==(const Rational<T>& x, const Rational<T>& y) noexcept {
        return x.num() == y.num() && x.den() == y.den();
    }

    template <typename T>
    constexpr std::strong_ordering operator<=>(const Rational<T>& x, const Rational<T>& y) noexcept {
        auto multiple = lcm(x.den(), y.den());
        auto lhs = x.num() * (multiple / x.den());
        auto rhs = y.num() * (multiple / y.den());
        return lhs <=> rhs;
    }

    template <typename T>
    std::optional<Rational<T>> Rational<T>::parse(std::string_view str) {

        static const auto t_parser = [] (std::string_view s) {
            if constexpr (std::integral<T>) {
                return parse_number_maybe<T>(s);
            } else if constexpr (std::same_as<T, Integer>) {
                return Integer::parse(s);
            } else {
                static_assert(dependent_false<T>, "Not supported");
            }
        };

        if (str.empty()) {
            return {};
        }

        std::string_view int_str, num_str, den_str;
        auto tail = str;
        auto space_pos = str.find_first_of(" \t");

        if (space_pos == 0) {
            return {};
        }

        if (space_pos != npos) {
            int_str = str.substr(0, space_pos);
            auto next_pos = str.find_first_not_of(" \t", space_pos);
            if (next_pos == npos) {
                return {};
            }
            tail = str.substr(next_pos);
        }

        auto slash_pos = tail.find('/');

        if (slash_pos == 0 || slash_pos == tail.size() - 1) {
            return {};
        } else if (slash_pos != npos) {
            num_str = tail.substr(0, slash_pos);
            den_str = tail.substr(slash_pos + 1);
        } else if (! int_str.empty()) {
            return {};
        } else {
            num_str = tail;
        }

        std::optional<T> i{0};
        std::optional<T> n{0};
        std::optional<T> d{1};

        if (! int_str.empty()) {
            i = t_parser(int_str);
        }

        if (! num_str.empty()) {
            n = t_parser(num_str);
        }

        if (! den_str.empty()) {
            d = t_parser(den_str);
        }

        if (i && n && d) {
            return Rational{*i, *n, *d};
        } else {
            return {};
        }

    }

    template <typename T>
    constexpr void Rational<T>::reduce() {
        if (den_ < T{0}) {
            num_ = - num_;
            den_ = - den_;
        }
        auto common = gcd(num_, den_);
        num_ /= common;
        den_ /= common;
    }

    template <typename T>
    constexpr Rational<T> Rational<T>::unchecked(const T& n, const T& d) {
        Rational r;
        r.num_ = n;
        r.den_ = d;
        return r;
    }

}

template <typename T>
struct std::hash<RS::Rational<T>> {
    std::size_t operator()(const RS::Rational<T>& r) const noexcept { return r.hash(); }
};
