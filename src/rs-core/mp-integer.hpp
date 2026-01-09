#pragma once

#include "rs-core/character.hpp"
#include "rs-core/format.hpp"
#include "rs-core/global.hpp"
#include "rs-core/hash.hpp"
#include <algorithm>
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
#include <optional>
#include <ranges>
#include <stdexcept>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

namespace RS {

    // Unsigned integer class

    class Natural {

    public:

        Natural() = default;
        template <std::unsigned_integral T> Natural(T t);
        template <std::signed_integral T> explicit Natural(T t) { if (t > 0) { *this = Natural(static_cast<std::make_unsigned_t<T>>(t)); } }
        Natural(std::initializer_list<std::uint64_t> list); // Big endian order
        explicit Natural(std::string_view str, unsigned base = 10);

        explicit operator bool() const noexcept { return ! words_.empty(); }
        bool operator!() const noexcept { return words_.empty(); }
        Natural operator+() const { return *this; }
        Natural& operator++() { return *this += 1u; }
        Natural operator++(int) { auto x = *this; ++*this; return x; }
        Natural& operator--() { return *this -= 1u; }
        Natural operator--(int) { auto x = *this; ++*this; return x; }
        Natural& operator+=(const Natural& y);
        Natural& operator-=(const Natural& y); // Subtraction saturates at zero if the true result would be negative
        Natural& operator*=(const Natural& y) { return *this = *this * y; }
        Natural& operator/=(const Natural& y) { return *this = divide(y).first; }
        Natural& operator%=(const Natural& y) { return *this = divide(y).second; }
        Natural& operator&=(const Natural& y);
        Natural& operator|=(const Natural& y);
        Natural& operator^=(const Natural& y);
        Natural& operator<<=(int y); // UB if y<0
        Natural& operator>>=(int y); // UB if y<0

        friend Natural operator+(const Natural& x, const Natural& y) { auto z = x; z += y; return z; }
        friend Natural operator-(const Natural& x, const Natural& y) { auto z = x; z -= y; return z; }
        friend Natural operator*(const Natural& x, const Natural& y);
        friend Natural operator/(const Natural& x, const Natural& y) { return x.divide(y).first; }
        friend Natural operator%(const Natural& x, const Natural& y) { return x.divide(y).second; }
        friend Natural operator&(const Natural& x, const Natural& y) { auto z = x; z &= y; return z; }
        friend Natural operator|(const Natural& x, const Natural& y) { auto z = x; z |= y; return z; }
        friend Natural operator^(const Natural& x, const Natural& y) { auto z = x; z ^= y; return z; }
        friend Natural operator<<(const Natural& x, int y) { auto z = x; z <<= y; return z; }
        friend Natural operator>>(const Natural& x, int y) { auto z = x; z >>= y; return z; }
        friend bool operator==(const Natural& x, const Natural& y) noexcept;
        friend std::strong_ordering operator<=>(const Natural& x, const Natural& y) noexcept;

        std::pair<Natural, Natural> divide(const Natural& y) const;
        std::size_t bits() const noexcept;
        bool get_bit(std::size_t i) const noexcept;
        void set_bit(std::size_t i, bool b = true);
        void flip_bit(std::size_t i);
        std::size_t popcount() const noexcept;
        double as_double() const noexcept;
        explicit operator double() const noexcept { return as_double(); }
        template <std::integral T> bool in_range() const noexcept;
        template <std::integral T> std::optional<T> checked_cast() const noexcept;
        template <std::integral T> T unchecked_cast() const noexcept; // UB if out of range
        template <std::integral T> explicit operator T() const noexcept { return checked_cast<T>().value_or(0); }
        std::size_t hash() const noexcept;
        std::string str(unsigned base = 10, std::size_t digits = 1) const;
        std::string rs_core_format(std::string_view flags, std::size_t digits) const;

        static std::optional<Natural> parse(std::string_view str, unsigned base = 10);

    private:

        friend class Integer;

        using word = std::uint32_t;
        using double_word = std::uint64_t;

        static constexpr auto word_bits_size = 8uz * sizeof(word);
        static constexpr auto word_bits_int = static_cast<int>(word_bits_size);
        static constexpr auto word_mask = ~ word{0};

        std::vector<word> words_; // Little endian order

        void normalize() noexcept;

    };

    template <std::unsigned_integral T>
    Natural::Natural(T t) {
        if constexpr (sizeof(T) <= sizeof(word)) {
            if (t > 0) {
                words_.push_back(t);
            }
        } else {
            while (t > 0) {
                words_.push_back(static_cast<word>(t));
                t >>= word_bits_int;
            }
        }
    }

    inline Natural::Natural(std::initializer_list<std::uint64_t> list):
    words_(2 * list.size()) {
        auto j = words_.size();
        for (auto i: list) {
            words_[--j] = static_cast<word>(i >> word_bits_int);
            words_[--j] = static_cast<word>(i);
        }
        normalize();
    }

    inline Natural::Natural(std::string_view str, unsigned base) {
        auto opt = parse(str, base);
        if (! opt) {
            throw std::invalid_argument(std::format("Invalid number: {:?}", str));
        }
        *this = std::move(*opt);
    }

    inline Natural& Natural::operator+=(const Natural& y) {

        auto common = std::min(words_.size(), y.words_.size());
        words_.resize(std::max(words_.size(), y.words_.size()), 0);
        double_word sum = 0;

        for (auto i = 0uz; i < common; ++i) {
            sum += words_[i];
            sum += y.words_[i];
            words_[i] = static_cast<word>(sum);
            sum >>= word_bits_int;
        }

        const auto* rptr = &words_;

        if (y.words_.size() > common) {
            rptr = &y.words_;
        }

        for (auto i = common; i < words_.size(); ++i) {
            sum += (*rptr)[i];
            words_[i] = static_cast<word>(sum);
            sum >>= word_bits_int;
        }

        if (sum) {
            words_.push_back(static_cast<word>(sum));
        }

        normalize();

        return *this;

    }

    inline Natural& Natural::operator-=(const Natural& y) {

        if (words_.size() >= y.words_.size()) {

            auto common = std::min(words_.size(), y.words_.size());
            auto borrow = false;

            for (auto i = 0uz; i < common; ++i) {

                auto will_borrow = words_[i] < y.words_[i] || (borrow && words_[i] == y.words_[i]);
                words_[i] -= y.words_[i];

                if (borrow) {
                    --words_[i];
                }

                borrow = will_borrow;

            }

            for (auto i = common; borrow && i < words_.size(); ++i) {
                borrow = --words_[i] == word_mask;
            }

            normalize();

        } else {

            words_.clear();

        }

        return *this;

    }

    inline Natural& Natural::operator&=(const Natural& y) {

        auto common = std::min(words_.size(), y.words_.size());
        words_.resize(common);

        for (auto i = 0uz; i < common; ++i) {
            words_[i] &= y.words_[i];
        }

        normalize();

        return *this;

    }

    inline Natural& Natural::operator|=(const Natural& y) {

        auto common = std::min(words_.size(), y.words_.size());
        words_.resize(std::max(words_.size(), y.words_.size()));

        for (auto i = 0uz; i < common; ++i) {
            words_[i] |= y.words_[i];
        }

        return *this;

    }

    inline Natural& Natural::operator^=(const Natural& y) {

        auto common = std::min(words_.size(), y.words_.size());
        words_.resize(std::max(words_.size(), y.words_.size()));

        for (auto i = 0uz; i < common; ++i) {
            words_[i] ^= y.words_[i];
        }

        normalize();

        return *this;

    }

    inline Natural& Natural::operator<<=(int y) {

        if (y == 0) {
            return *this;
        }

        auto words = static_cast<std::size_t>(y / word_bits_int);
        auto bits = y % word_bits_int;
        word prev = 0;

        if (bits > 0) {
            for (auto& word: words_) {
                auto next = word >> (word_bits_int - bits);
                word = (word << bits) | prev;
                prev = next;
            }
        }

        if (prev) {
            words_.push_back(prev);
        }

        words_.insert(words_.begin(), words, 0);

        return *this;

    }

    inline Natural& Natural::operator>>=(int y) {

        if (y == 0) {
            return *this;
        }

        auto words = static_cast<std::size_t>(y / word_bits_int);
        auto bits = y % word_bits_int;

        if (words >= words_.size()) {

            words_.clear();

        } else {

            words_.erase(words_.begin(), words_.begin() + static_cast<std::ptrdiff_t>(words));

            if (bits > 0) {

                word prev = 0;

                for (auto i = words_.size() - 1; i != npos; --i) {
                    auto next = words_[i] << (word_bits_int - bits);
                    words_[i] = (words_[i] >> bits) | prev;
                    prev = next;
                }

            }

        }

        normalize();

        return *this;

    }

    inline Natural operator*(const Natural& x, const Natural& y) {

        Natural z;

        if (! x || ! y) {
            return z;
        }

        auto m = x.words_.size();
        auto n = y.words_.size();
        z.words_.assign(m + n, 0);
        Natural::double_word carry = 0;

        for (auto k = 0uz; k <= m + n - 2; ++k) {

            carry += z.words_[k];
            z.words_[k] = static_cast<Natural::word>(carry);
            carry >>= Natural::word_bits_int;
            auto i_min = k < n ? 0uz : k - n + 1;
            auto i_max = k < m ? k : m - 1;

            for (auto i = i_min; i <= i_max; ++i) {
                Natural::double_word p = x.words_[i];
                p *= y.words_[k - i];
                p += z.words_[k];
                z.words_[k] = static_cast<Natural::word>(p);
                carry += p >> Natural::word_bits_int;
            }

        }

        z.words_[m + n - 1] = static_cast<Natural::word>(carry);
        z.normalize();

        return z;

    }

    inline bool operator==(const Natural& x, const Natural& y) noexcept {
        if (x.words_.size() != y.words_.size()) {
            return false;
        }
        for (auto i = 0uz; i < x.words_.size(); ++i) {
            if (x.words_[i] != y.words_[i]) {
                return false;
            }
        }
        return true;
    }

    inline std::strong_ordering operator<=>(const Natural& x, const Natural& y) noexcept {

        auto c = x.words_.size() <=> y.words_.size();

        if (c != 0) {
            return c;
        }

        for (auto i = x.words_.size() - 1; i != npos; --i) {
            c = x.words_[i] <=> y.words_[i];
            if (c != 0) {
                return c;
            }
        }

        return std::strong_ordering::equal;

    }

    inline std::pair<Natural, Natural> Natural::divide(const Natural& y) const {

        if (words_.empty()) {
            return {};
        } else if (words_.size() == 1 && y.words_.size() == 1) {
            auto a = words_[0];
            auto b = y.words_[0];
            auto q = a / b;
            auto r = a % b;
            return {q, r};
        }

        auto cmp = *this <=> y;

        if (cmp == std::strong_ordering::less) {
            return {{}, *this};
        } else if (cmp == std::strong_ordering::equal) {
            return {{1u}, {}};
        }

        Natural q;
        Natural r{*this};

        auto shift = static_cast<int>(bits() - y.bits());
        auto r_sub = y << shift;

        if (r_sub > *this) {
            --shift;
            r_sub >>= 1;
        }

        auto q_add = Natural{1} << shift;

        while (q_add) {

            if (r >= r_sub) {
                q += q_add;
                r -= r_sub;
            }

            r_sub >>= 1;
            q_add >>= 1;

        }

        return {q, r};

    }

    inline std::size_t Natural::bits() const noexcept {
        auto n = word_bits_size * words_.size();
        if (! words_.empty()) {
            n -= word_bits_size - static_cast<std::size_t>(std::bit_width(words_.back()));
        }
        return n;
    }

    inline bool Natural::get_bit(std::size_t i) const noexcept {
        if (i < word_bits_int * words_.size()) {
            return (words_[i / word_bits_int] >> (i % word_bits_int)) & 1;
        } else {
            return false;
        }
    }

    inline void Natural::set_bit(std::size_t i, bool b) {

        bool in_rep = i < word_bits_int * words_.size();

        if (b) {

            if (! in_rep) {
                words_.resize(i / word_bits_int + 1, 0);
            }

            words_[i / word_bits_int] |= word{1} << (i % word_bits_int);

        } else if (in_rep) {

            words_[i / word_bits_int] &= ~ (word{1} << (i % word_bits_int));
            normalize();

        }

    }

    inline void Natural::flip_bit(std::size_t i) {
        if (i >= word_bits_int * words_.size()) {
            words_.resize(i / word_bits_int + 1, 0);
        }
        words_[i / word_bits_int] ^= word{1} << (i % word_bits_int);
        normalize();
    }

    inline std::size_t Natural::popcount() const noexcept {
        auto n = 0uz;
        for (auto i: words_) {
            n += static_cast<std::size_t>(std::popcount(i));
        }
        return n;
    }

    inline double Natural::as_double() const noexcept {

        if (words_.size() <= 2) {

            return static_cast<double>(unchecked_cast<std::uint64_t>());

        } else {

            auto shift = static_cast<int>(bits()) - 64;
            auto shifted = (*this >> shift).unchecked_cast<std::uint64_t>();

            return std::ldexp(shifted, shift);

        }

    }

    template <std::integral T>
    bool Natural::in_range() const noexcept {
        using limits = std::numeric_limits<T>;
        using unsigned_type = std::make_unsigned_t<T>;
        static const Natural t_max = static_cast<unsigned_type>(limits::max());
        return *this <= t_max;
    }

    template <std::integral T>
    std::optional<T> Natural::checked_cast() const noexcept {
        if (in_range<T>()) {
            return unchecked_cast<T>();
        } else {
            return {};
        }
    }

    template <std::integral T>
    T Natural::unchecked_cast() const noexcept {

        static const auto t_bits = static_cast<int>(8uz * sizeof(T));

        T t = 0;
        int bit = 0;

        for (auto word: words_) {
            if (bit >= t_bits) {
                break;
            }
            t += static_cast<T>(word) << bit;
            bit += word_bits_int;
        }

        return t;

    }

    inline std::size_t Natural::hash() const noexcept {
        return hash_mix(words_ | std::views::transform(std::hash<word>()));
    }

    inline std::string Natural::str(unsigned base, std::size_t digits) const {

        if (base < 2 || base > 36) {
            throw std::out_of_range(std::format("Invalid number base: {}", base));
        }

        auto num = *this;
        std::string out;

        if (std::has_single_bit(base)) {

            auto shift = std::bit_width(base) - 1;
            auto mask = (Natural{1} << shift) - 1u;

            while (num || out.size() < digits) {
                auto remainder = static_cast<int>(num & mask);
                auto code = remainder + (remainder < 10 ? '0' : 'a' - 10);
                out += static_cast<char>(code);
                num >>= shift;
            }

        } else {

            Natural nat_base{base};

            while (num || out.size() < digits) {
                auto [quo,rem] = num.divide(nat_base);
                auto remainder = static_cast<int>(rem);
                auto code = remainder + (remainder < 10 ? '0' : 'a' - 10);
                out += static_cast<char>(code);
                num = std::move(quo);
            }

        }

        std::ranges::reverse(out);

        return out;

    }

    inline std::string Natural::rs_core_format(std::string_view flags, std::size_t digits) const {
        digits = std::max(digits, 1uz);
        if (flags.contains('b')) {
            return str(2, digits);
        } else if (flags.contains('x')) {
            return str(16, digits);
        } else {
            return str(10, digits);
        }
    }

    inline std::optional<Natural> Natural::parse(std::string_view str, unsigned base) {

        auto body = str;

        if (base == 0) {
            base = 10;
            if (str.size() >= 2 && str[0] == '0') {
                if (str[1] == 'B' || str[1] == 'b') {
                    base = 2;
                    body = str.substr(2);
                } else if (str[1] == 'X' || str[1] == 'x') {
                    base = 16;
                    body = str.substr(2);
                }
            }
        } else if (base < 2 || base > 36) {
            throw std::out_of_range(std::format("Invalid number base: {}", base));
        }

        if (body.empty()) {
            return {};
        }

        Natural factor{base};
        Natural value;
        unsigned digit{};

        for (auto c: body) {
            if (c == '\'' || c == '_') {
                continue;
            } else if (ascii_isdigit(c)) {
                digit = static_cast<unsigned>(c - '0');
            } else if (ascii_isupper(c)) {
                digit = static_cast<unsigned>(c - 'A' + 10);
            } else if (ascii_islower(c)) {
                digit = static_cast<unsigned>(c - 'a' + 10);
            } else {
                return {};
            }
            if (digit >= base) {
                return {};
            }
            value = value * factor + digit;
        }

        return value;

    }

    inline void Natural::normalize() noexcept {
        auto i = words_.size() - 1;
        while (i != npos && words_[i] == 0) {
            --i;
        }
        words_.resize(i + 1);
    }

    // Signed integer class

    class Integer {

    public:

        Integer() = default;
        template <std::integral T> Integer(T t);
        Integer(const Natural& x): mag_(x), sign_(false) {}
        explicit Integer(std::string_view str, unsigned base = 10);

        explicit operator bool() const noexcept { return static_cast<bool>(mag_); }
        bool operator!() const noexcept { return ! mag_; }
        Integer operator+() const { return *this; }
        Integer operator-() const;
        Integer& operator++() { return *this += 1; }
        Integer operator++(int) { auto x = *this; ++*this; return x; }
        Integer& operator--() { return *this -= 1; }
        Integer operator--(int) { auto x = *this; ++*this; return x; }
        Integer& operator+=(const Integer& y);
        Integer& operator-=(const Integer& y) { return *this += - y; }
        Integer& operator*=(const Integer& y) { return *this = *this * y; }
        Integer& operator/=(const Integer& y) { return *this = divide(y).first; }
        Integer& operator%=(const Integer& y) { return *this = divide(y).second; }

        friend Integer operator+(const Integer& x, const Integer& y) { auto z = x; z += y; return z; }
        friend Integer operator-(const Integer& x, const Integer& y) { auto z = x; z -= y; return z; }
        friend Integer operator*(const Integer& x, const Integer& y);
        friend Integer operator/(const Integer& x, const Integer& y) { return x.divide(y).first; }
        friend Integer operator%(const Integer& x, const Integer& y) { return x.divide(y).second; }
        friend bool operator==(const Integer& x, const Integer& y) noexcept { return x.sign_ == y.sign_ && x.mag_ == y.mag_; }
        friend std::strong_ordering operator<=>(const Integer& x, const Integer& y) noexcept;

        std::pair<Integer, Integer> divide(const Integer& y) const;
        double as_double() const noexcept;
        explicit operator double() const noexcept { return as_double(); }
        template <std::integral T> bool in_range() const noexcept;
        template <std::integral T> std::optional<T> checked_cast() const noexcept;
        template <std::integral T> T unchecked_cast() const noexcept; // UB if out of range
        template <std::integral T> explicit operator T() const noexcept { return checked_cast<T>().value_or(0); }
        explicit operator Natural() const { return sign_ ? Natural{} : mag_; }
        Natural abs() const { return mag_; }
        std::size_t hash() const noexcept;
        int sign() const noexcept { return sign_ ? -1 : mag_ ? 1 : 0; }
        std::string str(unsigned base = 10, std::size_t digits = 1) const;
        std::string rs_core_format(std::string_view flags, std::size_t digits) const;

        static std::optional<Integer> parse(std::string_view str, unsigned base = 10);

    private:

        Natural mag_;
        bool sign_ = false; // true = negative

    };

    template <std::integral T>
    Integer::Integer(T t):
    sign_(t < 0) {

        using limits = std::numeric_limits<T>;
        using unsigned_type = std::make_unsigned_t<T>;

        if (t == limits::min()) {
            mag_ = static_cast<unsigned_type>(limits::max()) + 1u;
        } else if (sign_) {
            mag_ = static_cast<unsigned_type>(T{0} - t);
        } else {
            mag_ = static_cast<unsigned_type>(t);
        }

    }

    inline Integer::Integer(std::string_view str, unsigned base) {
        auto opt = parse(str, base);
        if (! opt) {
            throw std::invalid_argument(std::format("Invalid number: {:?}", str));
        }
        *this = std::move(*opt);
    }

    inline Integer Integer::operator-() const {
        Integer z = *this;
        if (z) {
            z.sign_ = ! z.sign_;
        }
        return z;
    }

    inline Integer& Integer::operator+=(const Integer& y) {

        if (! y.mag_) {

            // do nothing

        } else if (! mag_) {

            mag_ = y.mag_;
            sign_ = y.sign_;

        } else if (sign_ == y.sign_) {

            mag_ += y.mag_;

        } else {

            auto c = mag_ <=> y.mag_;

            if (c == std::strong_ordering::less) {
                mag_ = y.mag_ - mag_;
                sign_ = ! sign_;
            } else if (c == std::strong_ordering::greater) {
                mag_ -= y.mag_;
            } else {
                mag_ = {};
                sign_ = false;
            }

        }

        return *this;

    }

    inline Integer operator*(const Integer& x, const Integer& y) {
        Integer z;
        z.mag_ = x.mag_ * y.mag_;
        z.sign_ = x.sign_ != y.sign_ && static_cast<bool>(x) && static_cast<bool>(y);
        return z;
    }

    inline std::strong_ordering operator<=>(const Integer& x, const Integer& y) noexcept {
        auto c = y.sign_ <=> x.sign_;
        if (c != 0) {
            return c;
        } else if (x.sign_) {
            return y.mag_ <=> x.mag_;
        } else {
            return x.mag_ <=> y.mag_;
        }
    }

    inline std::pair<Integer, Integer> Integer::divide(const Integer& y) const {

        std::pair<Integer, Integer> qr;
        std::tie(qr.first.mag_, qr.second.mag_) = mag_.divide(y.mag_);

        if (qr.second.mag_ && (sign_ || y.sign_)) {
            if (sign_) {
                ++qr.first.mag_;
                qr.second.mag_ = y.mag_ - qr.second.mag_;
            }
        }

        qr.first.sign_ = sign_ != y.sign_ && static_cast<bool>(qr.first.mag_);

        return qr;

    }

    inline double Integer::as_double() const noexcept {
        auto x = mag_.as_double();
        return sign_ ? - x : x;
    }

    template <std::integral T>
    bool Integer::in_range() const noexcept {

        using limits = std::numeric_limits<T>;

        static const Integer max = limits::max();
        static const Integer min = std::signed_integral<T> ? - max - 1 : 0;

        return *this >= min && *this <= max;

    }

    template <std::integral T>
    std::optional<T> Integer::checked_cast() const noexcept {
        if (in_range<T>()) {
            return unchecked_cast<T>();
        } else {
            return {};
        }
    }

    template <std::integral T>
    T Integer::unchecked_cast() const noexcept {

        using limits = std::numeric_limits<T>;
        using unsigned_type = std::make_unsigned_t<T>;

        auto u = mag_.unchecked_cast<unsigned_type>();

        if (! sign_) {
            return static_cast<T>(u);
        } else if (u > static_cast<unsigned_type>(limits::max())) {
            return limits::min();
        } else {
            return T{0} - static_cast<T>(u);
        }

    }

    inline std::size_t Integer::hash() const noexcept {
        auto x = mag_.hash();
        auto y = std::hash<bool>()(sign_);
        return hash_mix(x, y);
    }

    inline std::string Integer::str(unsigned base, std::size_t digits) const {
        auto out = mag_.str(base, digits);
        if (sign_) {
            out.insert(0, 1, '-');
        }
        return out;
    }

    inline std::string Integer::rs_core_format(std::string_view flags, std::size_t digits) const {
        digits = std::max(digits, 1uz);
        if (flags.contains('b')) {
            return str(2, digits);
        } else if (flags.contains('x')) {
            return str(16, digits);
        } else {
            return str(10, digits);
        }
    }

    inline std::optional<Integer> Integer::parse(std::string_view str, unsigned base) {

        if (str.empty()) {
            return {};
        }

        Integer num;
        auto sign = str[0] == '-';

        if (sign || str[0] == '+') {
            str = str.substr(1);
        }

        auto opt = Natural::parse(str, base);

        if (! opt) {
            return {};
        }

        num.mag_ = std::move(*opt);
        num.sign_ = sign && static_cast<bool>(num.mag_);

        return num;

    }

    // Concepts

    template <typename T>
    concept Mpitype = std::same_as<T, Natural> || std::same_as<T, Integer>;

    template <typename T>
    concept SignedIntegral =
        (std::signed_integral<T> || std::same_as<T, Integer>)
        && ! std::same_as<T, bool>;

    template <typename T>
    concept UnsignedIntegral =
        (std::unsigned_integral<T> || std::same_as<T, Natural>)
        && ! std::same_as<T, bool>;

    template <typename T>
    concept Integral = SignedIntegral<T> || UnsignedIntegral<T>;

    template <typename T>
    concept Arithmetic = Integral<T> || std::floating_point<T>;

    // Literals

    namespace Literals {

        inline Natural operator""_N(const char* raw) { return Natural(raw, 0); }
        inline Integer operator""_Z(const char* raw) { return Integer(raw, 0); }

    }

}

namespace std {

    // Specializations

    template <RS::Mpitype M, typename T>
    struct common_type<M, T> {};

    template <>
    struct common_type<RS::Natural, RS::Integer> {
        using type = RS::Integer;
    };

    template <signed_integral T>
    struct common_type<RS::Natural, T> {
        using type = RS::Integer;
    };

    template <unsigned_integral T>
    struct common_type<RS::Natural, T> {
        using type = RS::Natural;
    };

    template <integral T>
    struct common_type<RS::Integer, T> {
        using type = RS::Integer;
    };

    template <RS::Mpitype M>
    struct common_type<M, float> {
        using type = double;
    };

    template <RS::Mpitype M>
    struct common_type<M, double> {
        using type = double;
    };

    template <RS::Mpitype M>
    struct common_type<M, long double> {
        using type = long double;
    };

    template <RS::Mpitype M, floating_point T>
    struct common_type<M, T> {
        using type = conditional_t<(sizeof(T) < sizeof(double)), double, T>;
    };

    template <typename T, RS::Mpitype M>
    struct common_type<T, M>:
    common_type<M, T> {};

    template <>
    struct hash<RS::Natural> {
        auto operator()(const RS::Natural& x) const noexcept { return x.hash(); }
    };

    template <>
    struct hash<RS::Integer> {
        auto operator()(const RS::Integer& x) const noexcept { return x.hash(); }
    };

    template <RS::Mpitype M>
    class numeric_limits<M>:
    public std::numeric_limits<void> {
    public:
        static const bool is_exact = true;
        static const bool is_integer = true;
        static const bool is_signed = std::same_as<M, RS::Integer>;
        static const bool is_specialized = true;
        static const int radix = 2;
        static const M lowest() noexcept { return {}; }
        static const M max() noexcept { return {}; }
        static const M min() noexcept { return {}; }
    };

}
