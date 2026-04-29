#pragma once

#include "rs-core/arithmetic.hpp"
#include "rs-core/character.hpp"
#include "rs-core/enum.hpp"
#include "rs-core/format.hpp"
#include "rs-core/iterator.hpp"
#include "rs-core/random.hpp"
#include "rs-core/range.hpp"
#include "rs-core/rational.hpp"
#include <algorithm>
#include <cmath>
#include <compare>
#include <concepts>
#include <cstddef>
#include <format>
#include <functional>
#include <initializer_list>
#include <iterator>
#include <numeric>
#include <optional>
#include <random>
#include <ranges>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

namespace RS {

    template <Integral Int>
    struct DiceStateGroup {
        Int value;
        Int count;
    };

    template <Integral Int, FloatingPoint Flt>
    class DiceState {

    public:

        using integer_type = Int;
        using real_type = Flt;
        using group_type = DiceStateGroup<Int>;

        DiceState() = default;
        explicit DiceState(Int number, Int faces = Int{6}, Int value = Int{1});

        Int number() const { return static_cast<Int>(results_.size()); }
        Int faces() const { return faces_; }
        Int count(Int x) const;
        Int sum() const { return std::accumulate(results_.begin(), results_.end(), Int{0}); }
        Flt probability() const;

        auto asc() const { return std::ranges::subrange{results_}; }
        auto desc() const { return results_ | std::views::reverse; }
        auto asc_groups() const;
        auto desc_groups() const;

        bool next();

        friend bool operator==(const DiceState& a, const DiceState& b) noexcept = default;
        friend auto operator<=>(const DiceState& a, const DiceState& b) noexcept = default;

        static DiceState from_list(Int faces, std::initializer_list<Int> list);
        template <ReadableRange<Int> R> static DiceState from_range(Int faces, const R& r);

    private:

        Int faces_ = Int{6};
        std::vector<Int> results_; // Ascending order

        struct make_group;

    };

        template <Integral Int, FloatingPoint Flt>
        DiceState<Int, Flt>::DiceState(Int number, Int faces, Int value):
        faces_{faces} {

            if (number < Int{0}) {
                throw std::length_error{"Number of dice may not be negative"};
            } else if (faces < Int{1}) {
                throw std::length_error{"Number of faces must be at least 1"};
            } else if (value < Int{1} || value > faces) {
                throw std::out_of_range{std::format("Dice value ({}) is out of range (1-{})", value, faces_)};
            }

            results_.resize(static_cast<std::size_t>(number), value);

        }

        template <Integral Int, FloatingPoint Flt>
        Int DiceState<Int, Flt>::count(Int x) const {
            auto [i,j] = std::ranges::equal_range(results_, x);
            return static_cast<Int>(j - i);
        }

        template <Integral Int, FloatingPoint Flt>
        Flt DiceState<Int, Flt>::probability() const {

            using std::exp;
            using std::lgamma;
            using std::log;

            auto f = static_cast<Flt>(faces_);
            auto n = static_cast<Flt>(results_.size());
            auto log_p = lgamma(n + Flt{1}) - log(f) * n;

            for (auto [v,c]: asc_groups()) {
                if (c > Int{1}) {
                    log_p -= lgamma(static_cast<Flt>(c + Int{1}));
                }
            }

            return exp(log_p);

        }

        template <Integral Int, FloatingPoint Flt>
        auto DiceState<Int, Flt>::asc_groups() const {
            return results_
                | std::views::chunk_by(std::equal_to<Int>{})
                | std::views::transform(make_group{});
        }

        template <Integral Int, FloatingPoint Flt>
        auto DiceState<Int, Flt>::desc_groups() const {
            return results_
                | std::views::reverse
                | std::views::chunk_by(std::equal_to<Int>{})
                | std::views::transform(make_group{});
        }

        template <Integral Int, FloatingPoint Flt>
        bool DiceState<Int, Flt>::next() {

            if (results_.empty() || results_[0] == faces_) {
                return false;
            }

            auto it = std::ranges::find(results_, faces_) - 1;
            std::fill(it, results_.end(), *it + Int{1});

            return true;

        }

        template <Integral Int, FloatingPoint Flt>
        DiceState<Int, Flt> DiceState<Int, Flt>::from_list(Int faces, std::initializer_list<Int> list) {

            if (faces < Int{1}) {
                throw std::length_error{"Number of faces must be at least 1"};
            }

            auto fail = std::ranges::find_if(list, [faces] (Int x) { return x < Int{1} || x > faces; });

            if (fail != list.end()) {
                throw std::out_of_range{std::format("Dice value ({}) is out of range (1-{})", *fail, faces)};
            }

            DiceState ds;
            ds.faces_ = faces;
            ds.results_ = list;
            std::ranges::sort(ds.results_);

            return ds;

        }

        template <Integral Int, FloatingPoint Flt>
        template <ReadableRange<Int> R>
        DiceState<Int, Flt> DiceState<Int, Flt>::from_range(Int faces, const R& r) {

            if (faces < Int{1}) {
                throw std::length_error{"Number of faces must be at least 1"};
            }

            auto fail = std::ranges::find_if(r, [faces] (Int x) { return x < Int{1} || x > faces; });

            if (fail != std::ranges::end(r)) {
                throw std::out_of_range{std::format("Dice value ({}) is out of range (1-{})", *fail, faces)};
            }

            DiceState ds;
            ds.faces_ = faces;
            ds.results_ = {std::from_range, r};
            std::ranges::sort(ds.results_);

            return ds;

        }

        template <Integral Int, FloatingPoint Flt>
        struct DiceState<Int, Flt>::make_group {
            template <ReadableRange<Int> R>
            group_type operator()(const R& r) const {
                return {*std::ranges::begin(r), static_cast<Int>(std::ranges::distance(r))};
            }
        };

    template <Integral Int, FloatingPoint Flt>
    class DiceStateIterator:
    public Iterator<DiceStateIterator<Int, Flt>, DiceState<Int, Flt>, std::forward_iterator_tag> {

    public:

        DiceStateIterator() = default;
        explicit DiceStateIterator(Int number, Int faces = 6);
        explicit DiceStateIterator(const DiceState<Int, Flt>& state): state_{state} {}

        const DiceState<Int, Flt>& operator*() const noexcept { return *state_; }
        DiceStateIterator& operator++();
        bool operator==(const DiceStateIterator& it) const noexcept { return state_ == it.state_; }
        bool operator==(std::nullptr_t) const noexcept { return ! state_; }

    private:

        std::optional<DiceState<Int, Flt>> state_;

    };

        template <Integral Int, FloatingPoint Flt>
        DiceStateIterator<Int, Flt>::DiceStateIterator(Int number, Int faces):
        state_{DiceState<Int, Flt>{number, faces}} {}

        template <Integral Int, FloatingPoint Flt>
        DiceStateIterator<Int, Flt>& DiceStateIterator<Int, Flt>::operator++() {
            if (! state_->next()) {
                state_ = {};
            }
            return *this;
        }

    template <Integral Int = int, FloatingPoint Flt = double>
    class Dice {

    public:

        using integer_type = Int;
        using real_type = Flt;
        using state_type = DiceState<Int, Flt>;
        using state_iterator = DiceStateIterator<Int, Flt>;
        using state_range = std::ranges::subrange<state_iterator, std::nullptr_t>;

        Dice() = default;
        explicit Dice(Int number, Int faces = Int{6});
        explicit Dice(std::string_view str);

        template <std::uniform_random_bit_generator RNG> Int operator()(RNG& rng) const;

        Int number() const noexcept { return number_; }
        Int faces() const noexcept { return single_.max(); }
        Int min() const noexcept { return number(); }
        Int max() const noexcept { return number() * faces(); }
        Flt mean() const noexcept;
        Flt sd() const noexcept;
        Flt variance() const noexcept;
        Flt pdf(Int x) const;
        Flt cdf(Int x) const;
        Flt ccdf(Int x) const;

        state_range states() const;

    private:

        using distribution = UniformInteger<Int>;

        Int number_ = Int{1};
        distribution single_ {Int{1}, Int{6}};

    };

        template <Integral Int, FloatingPoint Flt>
        Dice<Int, Flt>::Dice(Int number, Int faces):
        number_{number},
        single_{Int{1}, faces} {
            if (number < Int{0}) {
                throw std::length_error{"Number of dice may not be negative"};
            } else if (faces < Int{1}) {
                throw std::length_error{"Number of faces must be at least 1"};
            }
        }

        template <Integral Int, FloatingPoint Flt>
        Dice<Int, Flt>::Dice(std::string_view str) {

            auto fail =[str] [[noreturn]] {
                throw std::invalid_argument{std::format("Invalid dice expression: {:?}", str)};
            };

            auto get_int = [&fail] (std::string_view sv) {
                if constexpr (std::integral<Int>) {
                    auto opt_number = parse_number_maybe<Int>(sv);
                    if (opt_number) {
                        return *opt_number;
                    } else {
                        fail();
                    }
                } else {
                    return Int{sv};
                }
            };

            if (str.empty()) {
                fail();
            }

            auto end_prefix = std::ranges::find_if_not(str, ascii_isdigit);

            if (end_prefix != str.begin()) {
                std::string_view prefix {str.begin(), end_prefix};
                number_ = get_int(prefix);
            }

            if (end_prefix == str.end() || ascii_toupper(*end_prefix) != 'D') {
                fail();
            }

            ++end_prefix;

            if (end_prefix != str.end()) {
                std::string_view tail {end_prefix, str.end()};
                if (std::ranges::find_if_not(tail, ascii_isdigit) != tail.end()) {
                    fail();
                }
                auto faces = get_int(tail);
                if (faces < Int{1}) {
                    fail();
                }
                single_ = distribution {Int{1}, faces};
            }

        }

        // }

        template <Integral Int, FloatingPoint Flt>
        template <std::uniform_random_bit_generator RNG>
        Int Dice<Int, Flt>::operator()(RNG& rng) const {
            Int sum {0};
            for (auto _: std::views::iota(Int{0}, number_)) {
                sum += single_(rng);
            }
            return sum;
        }

        template <Integral Int, FloatingPoint Flt>
        Flt Dice<Int, Flt>::mean() const noexcept {
            auto fn = static_cast<Flt>(number());
            auto ff = static_cast<Flt>(faces());
            return fn * (ff + Flt{1}) / Flt{2};
        }

        template <Integral Int, FloatingPoint Flt>
        Flt Dice<Int, Flt>::sd() const noexcept {
            using std::sqrt;
            return sqrt(variance());
        }

        template <Integral Int, FloatingPoint Flt>
        Flt Dice<Int, Flt>::variance() const noexcept {
            auto fn = static_cast<Flt>(number());
            auto ff = static_cast<Flt>(faces());
            return fn * (ff * ff - Flt{1}) / Flt{12};
        }

        template <Integral Int, FloatingPoint Flt>
        Flt Dice<Int, Flt>::pdf(Int x) const {

            using std::pow;

            if (x < min() || x > max()) {
                return Flt{0};
            }

            auto fx = static_cast<Flt>(x);
            auto fn = static_cast<Flt>(number());
            auto ff = static_cast<Flt>(faces());
            auto divisor = std::pow(ff, fn);
            Flt sum {0};
            Flt sign {1};

            for (auto i: std::views::iota(Int{0}, number_)) {
                auto fi = static_cast<Flt>(i);
                auto a = binomial(fn, fi);
                auto b = binomial(fx - ff * fi - Flt{1}, fn - Flt{1});
                sum += sign * a * b;
                sign = - sign;
            }

            return sum / divisor;

        }

        template <Integral Int, FloatingPoint Flt>
        Flt Dice<Int, Flt>::cdf(Int x) const {

            using std::pow;

            if (x < min()) {
                return Flt{0};
            } else if (x >= max()) {
                return Flt{1};
            }

            auto fx = static_cast<Flt>(x);
            auto fn = static_cast<Flt>(number());
            auto ff = static_cast<Flt>(faces());
            auto divisor = std::pow(ff, fn);
            Flt sum {0};
            Flt sign {1};

            for (auto i: std::views::iota(Int{0}, number_)) {
                auto fi = static_cast<Flt>(i);
                auto a = binomial(fn, fi);
                auto b = binomial(fx - ff * fi, fn);
                sum += sign * a * b;
                sign = - sign;
            }

            return sum / divisor;

        }

        template <Integral Int, FloatingPoint Flt>
        Flt Dice<Int, Flt>::ccdf(Int x) const {

            using std::pow;

            if (x <= min()) {
                return Flt{1};
            } else if (x > max()) {
                return Flt{0};
            }

            auto fx = static_cast<Flt>(x);
            auto fn = static_cast<Flt>(number());
            auto ff = static_cast<Flt>(faces());
            auto divisor = std::pow(ff, fn);
            Flt sum {0};
            Flt sign {1};

            for (auto i: std::views::iota(Int{0}, number_)) {
                auto fi = static_cast<Flt>(i);
                auto a = binomial(fn, fi);
                auto b = binomial(ff * (fn - fi) + fn - fx, fn);
                sum += sign * a * b;
                sign = - sign;
            }

            return sum / divisor;

        }

        template <Integral Int, FloatingPoint Flt>
        typename Dice<Int, Flt>::state_range Dice<Int, Flt>::states() const {
            state_iterator begin {number(), faces()};
            return {begin, nullptr};
        }

        template <Integral Int, FloatingPoint Flt>
        bool operator==(const Dice<Int, Flt>& a, const Dice<Int, Flt>& b) noexcept {
            return a.number() == b.number() && a.faces() == b.faces();
        }

    template <SignedIntegral Int = int, FloatingPoint Flt = double>
    class DiceSet {

    public:

        using dice_type = Dice<Int, Flt>;
        using integer_type = Int;
        using rational_type = Rational<Int>;
        using real_type = Flt;

        struct element_type {
            dice_type dice;
            rational_type factor;
        };

        using iterator = std::vector<element_type>::const_iterator;

        DiceSet() = default;
        DiceSet(const dice_type& d);
        DiceSet(rational_type r): offset_{r} {}
        DiceSet(Int n): offset_{n} {}
        explicit DiceSet(const dice_type& d, rational_type factor);
        explicit DiceSet(Int number, Int faces, rational_type factor = rational_type{1});
        explicit DiceSet(std::string_view str);

        template <std::uniform_random_bit_generator RNG> rational_type operator()(RNG& rng) const;

        iterator begin() const noexcept { return elements_.begin(); }
        iterator end() const noexcept { return elements_.end(); }
        bool empty() const noexcept { return elements_.empty(); }
        std::size_t size() const noexcept { return elements_.size(); }
        rational_type offset() const { return offset_; }
        rational_type min() const;
        rational_type max() const;
        Flt mean() const;
        Flt sd() const;
        Flt variance() const;

        DiceSet operator+() const { return *this; }
        DiceSet operator-() const { return *this * rational_type{-1}; }
        DiceSet& operator+=(const DiceSet& d);
        DiceSet& operator+=(const dice_type& d) { return *this += DiceSet{d}; }
        DiceSet& operator+=(rational_type r) { offset_ += r; return *this; }
        DiceSet& operator+=(Int n) { return *this += rational_type{n}; }
        DiceSet& operator-=(const DiceSet& d) { return *this += - d; }
        DiceSet& operator-=(const dice_type& d) { return *this += - DiceSet{d}; }
        DiceSet& operator-=(rational_type r) { offset_ -= r; return *this; }
        DiceSet& operator-=(Int n) { return *this -= rational_type{n}; }
        DiceSet& operator*=(rational_type r);
        DiceSet& operator*=(Int n) { return *this *= rational_type{n}; }
        DiceSet& operator/=(rational_type r) { return *this *= r.inverse(); }
        DiceSet& operator/=(Int n) { return *this /= rational_type{n}; }

        friend bool operator==(const DiceSet& a, const DiceSet& b) = default;

    private:

        std::vector<element_type> elements_;
        rational_type offset_ {};

        void normalize();

    };

        template <SignedIntegral Int, FloatingPoint Flt>
        DiceSet<Int, Flt>::DiceSet(const dice_type& d) {
            if (d.number() != Int{0}) {
                elements_.emplace_back(d, rational_type{1});
            }
            normalize();
        }

        template <SignedIntegral Int, FloatingPoint Flt>
        DiceSet<Int, Flt>::DiceSet(const dice_type& d, rational_type factor) {
            if (d.number() != Int{0} && factor != rational_type{0}) {
                elements_.emplace_back(d, factor);
            }
            normalize();
        }

        template <SignedIntegral Int, FloatingPoint Flt>
        DiceSet<Int, Flt>::DiceSet(Int number, Int faces, rational_type factor) {
            if (number != Int{0} && factor != rational_type{0}) {
                dice_type d {number, faces};
                elements_.emplace_back(d, factor);
            }
            normalize();
        }

        template <SignedIntegral Int, FloatingPoint Flt>
        DiceSet<Int, Flt>::DiceSet(std::string_view str) {

            using namespace std::literals;

            std::string s {str};
            std::erase_if(s, ascii_isspace);
            std::string_view sv {s};
            auto i = 0uz;

            while (i < s.size()) {

                auto j = s.find_first_of("+-", i + 1);
                auto elem_str = sv.substr(i, j - i);

                if (elem_str.find_first_of("Dd") == npos) {

                    offset_ += rational_type{elem_str};

                } else {

                    auto negative = elem_str[0] == '-';

                    if (elem_str[0] == '+' || elem_str[0] == '-') {
                        elem_str = elem_str.substr(1);
                    }

                    auto end_dice = std::ranges::find_if_not(elem_str,
                        [] (char c) { return ascii_isdigit(c) || c == 'D' || c == 'd';});
                    std::string_view dice_str {elem_str.begin(), end_dice};
                    element_type elem;
                    elem.dice = dice_type{dice_str};

                    if (end_dice == elem_str.end()) {

                        elem.factor = rational_type{1};

                    } else {

                        auto tail = std::string_view{end_dice, elem_str.end()};

                        if (tail[0] == '*' || tail[0] == 'x') {
                            elem.factor = rational_type{tail.substr(1)};
                        } else if (tail[0] == '/') {
                            elem.factor = rational_type{tail.substr(1)}.inverse();
                        } else {
                            throw std::invalid_argument{std::format("Invalid dice expression: {:?}", elem_str)};
                        }

                    }

                    if (negative) {
                        elem.factor = - elem.factor;
                    }

                    elements_.push_back(elem);

                }

                i = j;

            }

            normalize();

        }

        template <SignedIntegral Int, FloatingPoint Flt>
        template <std::uniform_random_bit_generator RNG>
        Rational<Int> DiceSet<Int, Flt>::operator()(RNG& rng) const {
            auto sum = offset_;
            for (const auto& elem: elements_) {
                sum += elem.dice(rng) * elem.factor;
            }
            return sum;
        }

        template <SignedIntegral Int, FloatingPoint Flt>
        Rational<Int> DiceSet<Int, Flt>::min() const {
            auto sum = offset_;
            for (const auto& elem: elements_) {
                if (elem.factor > rational_type{0}) {
                    sum += elem.dice.min() * elem.factor;
                } else {
                    sum += elem.dice.max() * elem.factor;
                }
            }
            return sum;
        }

        template <SignedIntegral Int, FloatingPoint Flt>
        Rational<Int> DiceSet<Int, Flt>::max() const {
            auto sum = offset_;
            for (const auto& elem: elements_) {
                if (elem.factor > rational_type{0}) {
                    sum += elem.dice.max() * elem.factor;
                } else {
                    sum += elem.dice.min() * elem.factor;
                }
            }
            return sum;
        }

        template <SignedIntegral Int, FloatingPoint Flt>
        Flt DiceSet<Int, Flt>::mean() const {
            auto sum = offset_.template to_floating<Flt>();
            for (const auto& elem: elements_) {
                sum += elem.dice.mean() * elem.factor.template to_floating<Flt>();
            }
            return sum;
        }

        template <SignedIntegral Int, FloatingPoint Flt>
        Flt DiceSet<Int, Flt>::sd() const {
            using std::sqrt;
            return sqrt(variance());
        }

        template <SignedIntegral Int, FloatingPoint Flt>
        Flt DiceSet<Int, Flt>::variance() const {
            Flt sum {0};
            for (const auto& elem: elements_) {
                auto sd = elem.dice.sd() * elem.factor.template to_floating<Flt>();
                sum += sd * sd;
            }
            return sum;
        }

        template <SignedIntegral Int, FloatingPoint Flt>
        DiceSet<Int, Flt>& DiceSet<Int, Flt>::operator+=(const DiceSet& d) {
            elements_.append_range(d.elements_);
            offset_ += d.offset_;
            normalize();
            return *this;
        }

        template <SignedIntegral Int, FloatingPoint Flt>
        DiceSet<Int, Flt>& DiceSet<Int, Flt>::operator*=(rational_type r) {
            if (r == rational_type{0}) {
                elements_.clear();
                offset_ = rational_type{0};
            } else {
                for (auto& elem: elements_) {
                    elem.factor *= r;
                }
                offset_ *= r;
            }
            return *this;
        }

        template <SignedIntegral Int, FloatingPoint Flt>
        void DiceSet<Int, Flt>::normalize() {

            std::erase_if(elements_,
                [] (const element_type& elem) {
                    return elem.factor == rational_type{0};
                });

            std::ranges::sort(elements_,
                [] (const element_type& a, const element_type& b) {
                    auto adf = a.dice.faces();
                    auto adn = a.dice.number();
                    auto bdf = b.dice.faces();
                    auto bdn = b.dice.number();
                    return adf == bdf ? adn < bdn : adf > bdf;
                });

            auto i = 0uz;

            while (i + 1 < elements_.size()) {

                auto& a {elements_[i]};
                auto& b {elements_[i + 1]};

                if (a.dice == b.dice) {
                    a.factor += b.factor;
                    elements_.erase(elements_.begin() + static_cast<std::ptrdiff_t>(i + 1));
                } else {
                    ++i;
                }

            }

            i = 0uz;

            while (i + 1 < elements_.size()) {

                auto& a {elements_[i]};
                auto j = i + 1;

                while (j < elements_.size() && a.dice.faces() == elements_[j].dice.faces()) {

                    auto& b {elements_[j]};

                    if (a.factor == b.factor) {
                        a.dice = dice_type{a.dice.number() + b.dice.number(), a.dice.faces()};
                        elements_.erase(elements_.begin() + static_cast<std::ptrdiff_t>(j));
                    } else {
                        ++j;
                    }

                }

                ++i;

            }

        }

        template <SignedIntegral Int, FloatingPoint Flt>
        DiceSet<Int, Flt> operator+(const DiceSet<Int, Flt>& a, const DiceSet<Int, Flt>& b) {
            auto c = a;
            c += b;
            return c;
        }

        template <SignedIntegral Int, FloatingPoint Flt>
        DiceSet<Int, Flt> operator+(const DiceSet<Int, Flt>& a, Rational<Int> b) {
            auto c = a;
            c += b;
            return c;
        }

        template <SignedIntegral Int, FloatingPoint Flt>
        DiceSet<Int, Flt> operator+(const DiceSet<Int, Flt>& a, Int b) {
            auto c = a;
            c += b;
            return c;
        }

        template <SignedIntegral Int, FloatingPoint Flt>
        DiceSet<Int, Flt> operator+(Rational<Int> a, const DiceSet<Int, Flt>& b) {
            auto c = b;
            c += a;
            return c;
        }

        template <SignedIntegral Int, FloatingPoint Flt>
        DiceSet<Int, Flt> operator+(Int a, const DiceSet<Int, Flt>& b) {
            auto c = b;
            c += a;
            return c;
        }

        template <SignedIntegral Int, FloatingPoint Flt>
        DiceSet<Int, Flt> operator-(const DiceSet<Int, Flt>& a, const DiceSet<Int, Flt>& b) {
            auto c = a;
            c -= b;
            return c;
        }

        template <SignedIntegral Int, FloatingPoint Flt>
        DiceSet<Int, Flt> operator-(const DiceSet<Int, Flt>& a, Rational<Int> b) {
            auto c = a;
            c -= b;
            return c;
        }

        template <SignedIntegral Int, FloatingPoint Flt>
        DiceSet<Int, Flt> operator-(const DiceSet<Int, Flt>& a, Int b) {
            auto c = a;
            c -= b;
            return c;
        }

        template <SignedIntegral Int, FloatingPoint Flt>
        DiceSet<Int, Flt> operator-(Rational<Int> a, const DiceSet<Int, Flt>& b) {
            auto c = - b;
            c += a;
            return c;
        }

        template <SignedIntegral Int, FloatingPoint Flt>
        DiceSet<Int, Flt> operator-(Int a, const DiceSet<Int, Flt>& b) {
            auto c = - b;
            c += a;
            return c;
        }

        template <SignedIntegral Int, FloatingPoint Flt>
        DiceSet<Int, Flt> operator*(const DiceSet<Int, Flt>& a, Rational<Int> b) {
            auto c = a;
            c *= b;
            return c;
        }

        template <SignedIntegral Int, FloatingPoint Flt>
        DiceSet<Int, Flt> operator*(const DiceSet<Int, Flt>& a, Int b) {
            return a * Rational<Int>{b};
        }

        template <SignedIntegral Int, FloatingPoint Flt>
        DiceSet<Int, Flt> operator*(Rational<Int> a, const DiceSet<Int, Flt>& b) {
            return b * a;
        }

        template <SignedIntegral Int, FloatingPoint Flt>
        DiceSet<Int, Flt> operator*(Int a, const DiceSet<Int, Flt>& b) {
            return b * a;
        }

        template <SignedIntegral Int, FloatingPoint Flt>
        DiceSet<Int, Flt> operator/(const DiceSet<Int, Flt>& a, Rational<Int> b) {
            return a * b.inverse();
        }

        template <SignedIntegral Int, FloatingPoint Flt>
        DiceSet<Int, Flt> operator/(const DiceSet<Int, Flt>& a, Int b) {
            return a / Rational<Int>{b};
        }

}

template <RS::Integral Int>
struct std::formatter<RS::DiceStateGroup<Int>>:
RS::CommonFormatter {

    template <typename FormatContext>
    auto format(const RS::DiceStateGroup<Int>& dg, FormatContext& ctx) const {
        formatter<Int> format_integer;
        format_integer.format(dg.value, ctx);
        *ctx.out() = ':';
        format_integer.format(dg.count, ctx);
        return ctx.out();
    }

};

template <RS::Integral Int, RS::FloatingPoint Flt>
struct std::formatter<RS::DiceState<Int, Flt>>:
RS::CommonFormatter {

    // c = Show counts per value instead of raw values
    // d = Descending order

    bool group_counts = false;
    bool descending_order = false;

    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {

        auto it = ctx.begin();

        for (; it != ctx.end(); ++it) {
            switch (*it) {
                case 'c':  group_counts = true; break;
                case 'd':  descending_order = true; break;
                case '}':  return it;
                default:   throw format_error{"Unknown formatting flag"};
            }
        }

        return it;

    }

    template <typename FormatContext>
    auto format(const RS::DiceState<Int, Flt>& ds, FormatContext& ctx) const {

        if (ds.number() == 0) {

            write_out("[]", ctx.out());

        } else {

            auto sep = '[';

            if (group_counts) {

                using group_type = RS::DiceStateGroup<Int>;

                formatter<group_type> format_group;

                auto write_group = [&ctx,&format_group,&sep] (group_type g) {
                    *ctx.out() = sep;
                    sep = ',';
                    format_group.format(g, ctx);
                };

                if (descending_order) {
                    for (auto g: ds.desc_groups()) {
                        write_group(g);
                    }
                } else {
                    for (auto g: ds.asc_groups()) {
                        write_group(g);
                    }
                }

            } else {

                formatter<Int> format_integer;

                auto write_element = [&ctx,&format_integer,&sep] (Int x) {
                    *ctx.out() = sep;
                    sep = ',';
                    format_integer.format(x, ctx);
                };

                if (descending_order) {
                    for (auto x: ds.desc()) {
                        write_element(x);
                    }
                } else {
                    for (auto x: ds.asc()) {
                        write_element(x);
                    }
                }

            }

            *ctx.out() = ']';

        }

        return ctx.out();

    }

};

template <RS::Integral Int, RS::FloatingPoint Flt>
struct std::formatter<RS::Dice<Int, Flt>>:
RS::CommonFormatter {

    // D = Capital letter
    // p = Short prefix (elide leading 1)
    // s = Short suffix (elide trailing 6)

    char dice_symbol = 'd';
    bool elide_prefix = false;
    bool elide_suffix = false;

    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {

        auto it = ctx.begin();

        for (; it != ctx.end(); ++it) {
            switch (*it) {
                case 'D':  dice_symbol = 'D'; break;
                case 'p':  elide_prefix = true; break;
                case 's':  elide_suffix = true; break;
                case '}':  return it;
                default:   throw format_error{"Unknown formatting flag"};
            }
        }

        return it;

    }

    template <typename FormatContext>
    auto format(const RS::Dice<Int, Flt>& d, FormatContext& ctx) const {

        formatter<Int> format_integer;
        auto n = d.number();
        auto f = d.faces();

        if (! elide_prefix || n != Int{1}) {
            format_integer.format(n, ctx);
        }

        *ctx.out() = dice_symbol;

        if (! elide_suffix || f != Int{6}) {
            format_integer.format(f, ctx);
        }

        return ctx.out();

    }

};

template <RS::SignedIntegral Int, RS::FloatingPoint Flt>
struct std::formatter<RS::DiceSet<Int, Flt>>:
RS::CommonFormatter {

    // D = Capital letter
    // p = Short prefix (elide leading 1)
    // s = Short suffix (elide trailing 6)
    // x = Multiplication symbol

    using dice_type = RS::Dice<Int, Flt>;

    formatter<dice_type> format_dice;
    char multiply_symbol = '*';

    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {

        auto it = ctx.begin();

        for (; it != ctx.end(); ++it) {
            switch (*it) {
                case 'D':  format_dice.dice_symbol = 'D'; break;
                case 'p':  format_dice.elide_prefix = true; break;
                case 's':  format_dice.elide_suffix = true; break;
                case 'x':  multiply_symbol = *it; break;
                case '}':  return it;
                default:   throw format_error{"Unknown formatting flag"};
            }
        }

        return it;

    }

    template <typename FormatContext>
    auto format(const RS::DiceSet<Int, Flt>& set, FormatContext& ctx) const {

        using rational_type = RS::Rational<Int>;

        formatter<Int> format_integer;
        formatter<rational_type> format_rational;

        for (const auto& elem: set) {

            if (elem.factor < rational_type{0}) {
                *ctx.out() = '-';
            } else if (&elem != &*set.begin()) {
                *ctx.out() = '+';
            }

            format_dice.format(elem.dice, ctx);
            auto abs_factor = elem.factor.abs();

            if (abs_factor == rational_type{1}) {
                // Do nothing
            } else if (abs_factor.num() == Int{1}) {
                *ctx.out() = '/';
                format_integer.format(abs_factor.den(), ctx);
            } else {
                *ctx.out() = multiply_symbol;
                format_rational.format(abs_factor, ctx);
            }

        }

        if (! set.empty() && set.offset() > rational_type{0}) {
            *ctx.out() = '+';
        }

        if (set.empty() || set.offset() != rational_type{0}) {
            format_rational.format(set.offset(), ctx);
        }

        return ctx.out();

    }

};
