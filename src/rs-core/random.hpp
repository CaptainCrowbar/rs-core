#pragma once

#include "rs-core/enum.hpp"
#include "rs-core/global.hpp"
#include "rs-core/mp-integer.hpp"
#include "rs-core/uint128.hpp"
#include <algorithm>
#include <bit>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <initializer_list>
#include <iterator>
#include <limits>
#include <map>
#include <random>
#include <ranges>
#include <type_traits>
#include <utility>
#include <vector>

namespace RS {

    // PCG64-DXSM algorithm by Melissa O'Neill and Tony Finch
    // http://www.pcg-random.org/
    // https://dotat.at/@/2023-06-21-pcg64-dxsm.html

    class Pcg {

    public:

        using result_type = std::uint64_t;

        constexpr Pcg() noexcept { seed(default_seed); }
        constexpr explicit Pcg(std::uint64_t s) noexcept { seed(s); }
        constexpr explicit Pcg(std::uint64_t s0, std::uint64_t s1) noexcept { seed(s0, s1); }
        constexpr explicit Pcg(std::uint64_t s0, std::uint64_t s1, std::uint64_t s2, std::uint64_t s3) noexcept {
            seed(s0, s1, s2, s3);
        }

        constexpr std::uint64_t operator()() noexcept;

        constexpr void seed(std::uint64_t s) noexcept { seed(0, s, 0, 0); }
        constexpr void seed(std::uint64_t s0, std::uint64_t s1) noexcept { seed(s0, s1, 0, 0); }
        constexpr void seed(std::uint64_t s0, std::uint64_t s1, std::uint64_t s2, std::uint64_t s3) noexcept;

        constexpr static std::uint64_t min() noexcept { return 0; }
        constexpr static std::uint64_t max() noexcept { return max64; }

    private:

        static constexpr std::uint64_t default_seed = 0xcafe'f00d'd15e'a5e5ull;

        uint128_t state_;
        uint128_t delta_;

    };

        constexpr std::uint64_t Pcg::operator()() noexcept {
            static constexpr std::uint64_t k = 0xda94'2042'e4dd'58b5ull;
            auto u = state_;
            state_ = u * k + delta_;
            auto x = static_cast<std::uint64_t>(u >> 64);
            auto y = static_cast<std::uint64_t>(u | 1);
            x ^= x >> 32;
            x *= k;
            x ^= x >> 48;
            x *= y;
            return x;
        }

        constexpr void Pcg::seed(std::uint64_t s0, std::uint64_t s1, std::uint64_t s2, std::uint64_t s3) noexcept {
            state_ = (uint128_t{s0} << 64) + s1;
            delta_ = (uint128_t{s2} << 64) + s3;
            delta_ = (delta_ << 1) | 1;
            state_ = state_ + delta_;
            (*this)();
        }

    // 64-bit random device

    using RandomDevice64 = std::independent_bits_engine<std::random_device, 64, std::uint64_t>;

    // Uniform integer distribution

    // Lemire's algorithm
    // https://lemire.me/blog/2016/06/27/a-fast-alternative-to-the-modulo-reduction/

    namespace Detail {

        template <typename T>
        concept LessThan32Engine = std::uniform_random_bit_generator<T>
            && T::max() <= max32
            && (T::min() != 0 || T::max() < max32);

        template <typename T>
        concept Exact32Engine = std::uniform_random_bit_generator<T>
            && T::min() == 0
            && T::max() == max32;

        template <typename T>
        concept LessThan64Engine = std::uniform_random_bit_generator<T>
            && T::max() > max32
            && T::max() <= max64
            && (T::min() != 0 || T::max() < max64);

        template <typename T>
        concept Exact64Engine = std::uniform_random_bit_generator<T>
            && T::min() == 0
            && T::max() == max64;

        constexpr std::uint32_t lemire32(std::uint64_t r, std::uint64_t delta) noexcept {
            return static_cast<std::uint32_t>((r * (delta + 1)) >> 32);
        }

        constexpr std::uint64_t lemire64(std::uint64_t r, std::uint64_t delta) noexcept {
            return static_cast<std::uint64_t>((uint128_t{r} * (uint128_t{delta} + 1)) >> 64);
        }

        // Will only be called on inexact engines
        template <std::uniform_random_bit_generator RNG, std::unsigned_integral T>
        constexpr void synthesize_bits(RNG& rng, T& out) {
            using R = typename RNG::result_type;
            static constexpr auto bits_out = std::numeric_limits<T>::digits;
            static constexpr auto good_bits = std::bit_width(RNG::max() - RNG::min() + 1) - 1;
            static constexpr auto mask = (R{1} << good_bits) - 1;
            static constexpr auto n_calls = (bits_out + good_bits - 1) / good_bits;
            out = 0;
            for (auto i = 0uz; i < n_calls; ++i) {
                out = (out << good_bits) + (rng() & mask);
            }
        }

    }

    template <Integral T>
    class UniformInteger {

    public:

        using result_type = T;

        constexpr UniformInteger() noexcept = default;
        constexpr explicit UniformInteger(T range) noexcept: min_{0}, max_{range - 1} {} // UB if range<1
        constexpr explicit UniformInteger(T min, T max) noexcept;

        template <std::uniform_random_bit_generator RNG>
            constexpr T operator()(RNG& rng) const;

        constexpr T min() const noexcept { return min_; }
        constexpr T max() const noexcept { return max_; }

    private:

        T min_{0};
        T max_{std::numeric_limits<T>::max()};

    };

        template <Integral T>
        constexpr UniformInteger<T>::UniformInteger(T min, T max) noexcept:
        min_(min), max_(max) {
            if (min_ > max_) {
                std::swap(min_, max_);
            }
        }

        template <Integral T>
        template <std::uniform_random_bit_generator RNG>
        constexpr T UniformInteger<T>::operator()(RNG& rng) const {

            using namespace Detail;

            auto delta = static_cast<std::uint64_t>(max_ - min_);
            std::uint64_t x;

            if constexpr (Exact64Engine<RNG>) {

                if (delta == max64) {
                    x = rng();
                } else {
                    x = lemire64(rng(), delta);
                }

            } else if constexpr (Exact32Engine<RNG>) {

                if (delta == max32) {
                    x = rng();
                } else if (delta < max32) {
                    x = lemire32(rng(), delta);
                } else {
                    std::uint64_t y = rng();
                    y = (y << 32) + rng();
                    x = lemire64(y, delta);
                }

            } else {

                if (delta <= max32) {
                    std::uint32_t y;
                    synthesize_bits(rng, y);
                    x = lemire32(y, delta);
                } else {
                    std::uint64_t y;
                    synthesize_bits(rng, y);
                    x = lemire64(y, delta);
                }

            }

            return min_ + static_cast<T>(x);

        }

    // Bernoulli distribution

    class BernoulliDistribution {

    public:

        constexpr BernoulliDistribution() = default;
        constexpr explicit BernoulliDistribution(double p) noexcept;
        constexpr explicit BernoulliDistribution(std::uint64_t num, std::uint64_t den) noexcept;

        template <std::uniform_random_bit_generator RNG>
            constexpr bool operator()(RNG& rng) const;

        constexpr static bool min() noexcept { return false; }
        constexpr static bool max() noexcept { return true; }

    private:

        static constexpr auto max64 = static_cast<std::uint64_t>(-1);

        UniformInteger<std::uint64_t> dist_;
        std::uint64_t threshold_{max64 >> 1};

    };

        constexpr BernoulliDistribution::BernoulliDistribution(double p) noexcept:
        dist_(),
        threshold_(static_cast<std::uint64_t>(std::clamp(p, 0.0, 1.0) * static_cast<double>(max64))) {}

        constexpr BernoulliDistribution::BernoulliDistribution(std::uint64_t num, std::uint64_t den) noexcept:
        dist_(den),
        threshold_(std::clamp(num, std::uint64_t{}, den)) {}

        template <std::uniform_random_bit_generator RNG>
        constexpr bool BernoulliDistribution::operator()(RNG& rng) const {
            return dist_(rng) <= threshold_;
        }

    // Uniform floating point distribution

    // Badizadegan's algorithm
    // https://specbranch.com/posts/fp-rand/

    namespace Detail {

        template <std::floating_point T, std::unsigned_integral U, std::uniform_random_bit_generator RNG>
        constexpr T generate_real(RNG& r) noexcept {

            static_assert(sizeof(T) == sizeof(U));

            using limits = std::numeric_limits<T>;

            static constexpr auto significand_bits = limits::digits - 1;
            static constexpr auto exponent_range = static_cast<U>(significand_bits) << significand_bits;
            static constexpr auto underflow_tail = (limits::max_exponent - 1) % significand_bits;
            static constexpr auto underflow_shift = significand_bits - underflow_tail;

            auto generate_bits = [&r] (int bits) {
                static constexpr UniformInteger<U> uniform_bits;
                auto u = uniform_bits(r);
                auto mask = (U{1} << bits) - 1;
                return u & mask;
            };

            auto one_scaled = std::bit_cast<U>(T{1});
            auto tail_bits = 0;
            auto significand = generate_bits(significand_bits);

            while (significand == 0) {
                one_scaled -= exponent_range;
                if (one_scaled < exponent_range) {
                    significand = generate_bits(underflow_tail) << underflow_shift;
                    tail_bits = underflow_shift;
                    break;
                }
                significand = generate_bits(significand_bits);
            }

            auto fp_number = std::bit_cast<T>(one_scaled | significand) - std::bit_cast<T>(one_scaled);
            auto uint_number = std::bit_cast<U>(fp_number);
            tail_bits += (one_scaled >> significand_bits) - (uint_number >> significand_bits);
            tail_bits = std::min(tail_bits, significand_bits);
            auto tail = (generate_bits(tail_bits) + 1) >> 1;

            return std::bit_cast<T>(uint_number + tail);

        }

    }

    template <std::floating_point T>
    class UniformReal {

    public:

        using result_type = T;

        constexpr UniformReal() = default;
        constexpr explicit UniformReal(T range) noexcept: UniformReal(T{0}, range) {}
        constexpr explicit UniformReal(T min, T max) noexcept;

        template <std::uniform_random_bit_generator RNG>
            constexpr T operator()(RNG& rng) const;

        constexpr T min() const noexcept { return min_; }
        constexpr T max() const noexcept { return max_; }

    private:

        enum class range_mode: unsigned char {
            empty,    // Empty range, bounds are equal, range is not set
            one_ulp,  // Bounds differ by 1 ulp, range is not set
            two_ulp,  // Bounds differ by 2 ulp, range is the intervening value
            general,  // General case, range is the difference between bounds
        };

        T min_{0};
        T max_{1};
        T range_{1};
        range_mode mode_{range_mode::general};

    };

        template <std::floating_point T>
        constexpr UniformReal<T>::UniformReal(T min, T max) noexcept:
        min_(std::min(min, max)),
        max_(std::max(min, max)) {

            if (min_ == max_) {
                mode_ = range_mode::empty;
                return;
            }

            auto next1 = std::nextafter(min_, max_);

            if (next1 == max_) {
                mode_ = range_mode::one_ulp;
                return;
            }

            auto next2 = std::nextafter(next1, max_);

            if (next2 == max_) {
                range_ = next1;
                mode_ = range_mode::two_ulp;
            } else {
                range_ = max_ - min_;
                mode_ = range_mode::general;
            }

        }

        template <std::floating_point T>
        template <std::uniform_random_bit_generator RNG>
        constexpr T UniformReal<T>::operator()(RNG& rng) const {

            switch (mode_) {

                case range_mode::empty: {
                    return min_;
                }

                case range_mode::one_ulp: {
                    static constexpr auto threshold = RNG::min() + (RNG::max() - RNG::min()) / 2;
                    return rng() < threshold ? min_ : max_;
                }

                case range_mode::two_ulp: {
                    return range_;
                }

                default: {
                    T x;
                    do {
                        if constexpr (sizeof(T) <= sizeof(float)) {
                            x = static_cast<T>(Detail::generate_real<float, std::uint32_t>(rng));
                        } else {
                            x = static_cast<T>(Detail::generate_real<double, std::uint64_t>(rng));
                        }
                        x = min_ + x * range_;
                    } while (x <= min_ || x >= max_);
                    return x;
                }

            }

        }

    // Random choice class

    template <std::regular T>
    class RandomChoice {

    public:

        using result_type = T;

        RandomChoice() = default;
        RandomChoice(std::initializer_list<T> list): vec_(list) { update(); }
        template <std::ranges::range R>
            requires std::convertible_to<std::ranges::range_value_t<R>, T>
            explicit RandomChoice(const R& r):
            vec_(std::from_range, r) { update(); }

        template <std::uniform_random_bit_generator RNG>
            const T& operator()(RNG& rng) const; // UB if empty

        void insert(const T& t) { vec_.push_back(t); update(); }
        std::size_t size() const noexcept { return vec_.size(); }
        bool empty() const noexcept { return vec_.empty(); }

    private:

        using size_dist = UniformInteger<std::size_t>;

        std::vector<T> vec_;
        size_dist dist_;

        void update();

    };

        template <std::regular T>
        template <std::uniform_random_bit_generator RNG>
        const T& RandomChoice<T>::operator()(RNG& rng) const {
            auto i = dist_(rng);
            return vec_[i];
        }

        template <std::regular T>
        void RandomChoice<T>::update() {
            dist_ = size_dist{vec_.size()};
        }

    template <std::ranges::range R, std::uniform_random_bit_generator RNG>
    typename std::ranges::range_reference_t<const R> random_choice(const R& range, RNG& rng) {
        auto n = std::ranges::ssize(range);
        auto dist = UniformInteger(n);
        auto it = std::ranges::begin(range);
        std::advance(it, dist(rng));
        return *it;
    }

    // Weighted choice class

    namespace Detail {

        template <typename T> struct UniformDistribution;
        template <Integral T> struct UniformDistribution<T> {
            using type = UniformInteger<T>;
        };
        template <std::floating_point T> struct UniformDistribution<T> {
            using type = UniformReal<T>;
        };

    }

    template <std::regular T, Arithmetic W = int>
    class WeightedChoice {

    public:

        using result_type = T;
        using weight_type = W;

        WeightedChoice() = default;
        WeightedChoice(std::initializer_list<std::pair<T, W>> list);

        template <std::uniform_random_bit_generator RNG>
            const T& operator()(RNG& rng) const; // UB if empty

        void insert(const T& t, W w); // Ignored if w<=0
        std::size_t size() const noexcept { return map_.size(); }
        bool empty() const noexcept { return map_.empty(); }

    private:

        using weight_dist = Detail::UniformDistribution<W>::type;

        std::map<W, T> map_;
        weight_dist dist_;

    };

        template <std::regular T, Arithmetic W>
        WeightedChoice<T, W>::WeightedChoice(std::initializer_list<std::pair<T, W>> list) {
            W sum{};
            for (const auto& [t,w]: list) {
                if (w > 0) {
                    sum += w;
                    map_.insert({sum, t});
                }
            }
            dist_ = weight_dist(sum);
        }

        template <std::regular T, Arithmetic W>
        template <std::uniform_random_bit_generator RNG>
        const T& WeightedChoice<T, W>::operator()(RNG& rng) const {
            auto x = dist_(rng);
            auto it = map_.upper_bound(x);
            if constexpr (std::floating_point<W>) {
                // Possible because of FP rounding errors
                if (it == map_.end()) {
                    --it;
                }
            }
            return it->second;
        }

        template <std::regular T, Arithmetic W>
        void WeightedChoice<T, W>::insert(const T& t, W w) {
            if (w > 0) {
                if (! map_.empty()) {
                    w += std::prev(map_.end())->first;
                }
                map_.insert({w, t});
                dist_ = weight_dist(w);
            }
        }

    // Random algorithms

    namespace Detail {

        template <AutoEnum E>
        constexpr int select_enum_minimum =
            std::unsigned_integral<std::underlying_type_t<E>> ? 0 :
            sizeof(E) >= sizeof(int) ? std::numeric_limits<int>::min() :
            static_cast<int>(std::numeric_limits<std::underlying_type_t<E>>::min());

        template <AutoEnum E, E Min>
        const auto& select_enum_values() {
            static const auto values = enum_values(E{})
                | std::views::drop_while([] (E x) { return x < Min; })
                | std::ranges::to<std::vector>();
            return values;
        }

    }

    template <AutoEnum E,
        int Min = Detail::select_enum_minimum<E>,
        std::uniform_random_bit_generator RNG = std::minstd_rand>
    requires (std::signed_integral<std::underlying_type_t<E>> || Min >= 0)
    E random_enum(RNG& rng) {
        return random_choice(Detail::select_enum_values<E, static_cast<E>(Min)>(), rng);
    }

    template <AutoEnum E, E Min, std::uniform_random_bit_generator RNG>
    E random_enum(RNG& rng) {
        return random_choice(Detail::select_enum_values<E, Min>(), rng);
    }

    template <std::ranges::random_access_range R, std::uniform_random_bit_generator RNG>
    void shuffle(R& range, RNG& rng) {

        auto size = std::ranges::size(range);

        if (size < 2) {
            return;
        }

        for (auto i = 0uz; i < size - 1; ++i) {
            UniformInteger<std::size_t> dist(i, size - 1);
            auto j = dist(rng);
            if (i != j) {
                std::swap(range[i], range[j]);
            }
        }

    }

}
