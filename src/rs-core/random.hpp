#pragma once

#include "rs-core/global.hpp"
#include <algorithm>
#include <bit>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <initializer_list>
#include <iterator>
#include <limits>
#include <map>
#include <random>
#include <ranges>
#include <utility>
#include <vector>

namespace RS {

    namespace Detail {

        struct Uint128 {

            std::uint64_t high {};
            std::uint64_t low {};

            constexpr Uint128() = default;
            constexpr Uint128(std::uint64_t lo) noexcept: low{lo} {}
            constexpr Uint128(std::uint64_t hi, std::uint64_t lo) noexcept: high{hi}, low{lo} {}

            constexpr Uint128 operator<<(int y) const noexcept {
                if (y >= 64) {
                    return {low << (y - 64), 0};
                } else if (y >= 1) {
                    return {(high << y) + (low >> (64 - y)), low << y};
                } else {
                    return *this;
                }
            }

            constexpr Uint128 operator>>(int y) const noexcept {
                if (y >= 64) {
                    return high >> (y - 64);
                } else if (y >= 1) {
                    return {high >> y, (low >> y) + (high << (64 - y))};
                } else {
                    return *this;
                }
            }

            constexpr Uint128 operator|(Uint128 y) const noexcept {
                return {high | y.high, low | y.low};
            }

            constexpr Uint128 operator+(Uint128 y) const noexcept {
                Uint128 z{high + y.high, low + y.low};
                if (z.low < low) {
                    ++z.high;
                }
                return z;
            }

            constexpr Uint128 operator*(Uint128 y) const noexcept {
                static constexpr std::uint64_t max32 = (1ull << 32) - 1;
                Uint128 z;
                for (auto a = 0; a < 128; a += 32) {
                    auto c = (*this >> a).low & max32;
                    for (auto b = 0; b < 128; b += 32) {
                        auto d = (y >> b).low & max32;
                        z = z + (Uint128{c * d} << (a + b));
                    }
                }
                return z;
            }

        };

    }

    // PCG64-DXSM algorithm
    // Based on code by Melissa O'Neill and Tony Finch
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
        constexpr static std::uint64_t max() noexcept { return ~ std::uint64_t{}; }

    private:

        static constexpr std::uint64_t default_seed = 0xcafe'f00d'd15e'a5e5ull;

        Detail::Uint128 state_;
        Detail::Uint128 delta_;

    };

        constexpr std::uint64_t Pcg::operator()() noexcept {
            static constexpr std::uint64_t k = 0xda94'2042'e4dd'58b5ull;
            auto u = state_;
            state_ = u * k + delta_;
            auto x = (u >> 64).low;
            auto y = (u | 1).low;
            x ^= x >> 32;
            x *= k;
            x ^= x >> 48;
            x *= y;
            return x;
        }

        constexpr void Pcg::seed(std::uint64_t s0, std::uint64_t s1, std::uint64_t s2, std::uint64_t s3) noexcept {
            state_ = {s0, s1};
            delta_ = {s2, s3};
            delta_ = (delta_ << 1) | 1;
            state_ = state_ + delta_;
            (*this)();
        }

    // 64-bit random device

    using RandomDevice64 = std::independent_bits_engine<std::random_device, 64, std::uint64_t>;

    // Uniform integer distribution

    template <std::integral T>
    class UniformInteger {

    public:

        using result_type = T;

        UniformInteger() noexcept;
        explicit UniformInteger(T range) noexcept; // UB if range<=0
        explicit UniformInteger(T min, T max) noexcept;

        template <std::uniform_random_bit_generator RNG>
            T operator()(RNG& rng) const;

        T min() const noexcept { return min_; }
        T max() const noexcept;

    private:

        T min_{0};
        std::uint64_t range_{0};
        std::uint64_t threshold_{0}; // Highest multiple of range that fits in a uint64_t

        void update() noexcept;

    };

        template <std::integral T>
        UniformInteger<T>::UniformInteger() noexcept:
        min_(0),
        range_(static_cast<std::uint64_t>(std::numeric_limits<T>::max()) + 1) {
            update();
        }

        template <std::integral T>
        UniformInteger<T>::UniformInteger(T range) noexcept:
        min_(0),
        range_(static_cast<std::uint64_t>(range)) {
            update();
        }

        template <std::integral T>
        UniformInteger<T>::UniformInteger(T min, T max) noexcept {
            if (min > max) {
                std::swap(min, max);
            }
            min_ = min;
            range_ = static_cast<std::uint64_t>(max - min) + 1;
            update();
        }

        template <std::integral T>
        template <std::uniform_random_bit_generator RNG>
        T UniformInteger<T>::operator()(RNG& rng) const {
            std::uint64_t x;
            do {
                x = rng();
            } while (threshold_ != 0 && x >= threshold_);
            if (range_ != 0) {
                x %= range_;
            }
            return min_ + static_cast<T>(x);
        }

        template <std::integral T>
        T UniformInteger<T>::max() const noexcept {
            auto half_range = range_ / 2;
            auto t1 = static_cast<T>(half_range);
            auto t2 = static_cast<T>(range_ - half_range - 1);
            return min_ + t1 + t2;
        }

        template <std::integral T>
        void UniformInteger<T>::update() noexcept {
            if (! std::has_single_bit(range_)) {
                auto max64 = std::numeric_limits<std::uint64_t>::max();
                auto rem = max64 % range_;
                threshold_ = max64 - rem;
            }
        }

    // Uniform floating point distribution

    template <std::floating_point T>
    class UniformReal {

    public:

        using result_type = T;

        UniformReal() = default;
        explicit UniformReal(T range) noexcept: UniformReal(T{0}, range) {}
        explicit UniformReal(T min, T max) noexcept;

        template <std::uniform_random_bit_generator RNG>
            T operator()(RNG& rng) const;

        T min() const noexcept { return min_; }
        T max() const noexcept { return min_ + range_; }

    private:

        T min_{0};
        T range_{1};

    };

        template <std::floating_point T>
        UniformReal<T>::UniformReal(T min, T max) noexcept {
            if (min > max) {
                std::swap(min, max);
            }
            min_ = min;
            range_ = max - min;
        }

        template <std::floating_point T>
        template <std::uniform_random_bit_generator RNG>
        T UniformReal<T>::operator()(RNG& rng) const {
            auto x = rng() - rng.min();
            auto y = rng.max() - rng.min();
            auto z = static_cast<T>(x) / static_cast<T>(y);
            return min_ + range_ * z;
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

    // Weighted choice class

    namespace Detail {

        template <typename T> struct UniformDistribution;
        template <std::integral T> struct UniformDistribution<T> {
            using type = UniformInteger<T>;
        };
        template <std::floating_point T> struct UniformDistribution<T> {
            using type = UniformReal<T>;
        };

    }

    template <std::regular T, typename W = int>
    requires std::integral<W> || std::floating_point<W>
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

        template <std::regular T, typename W>
        requires std::integral<W> || std::floating_point<W>
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

        template <std::regular T, typename W>
        requires std::integral<W> || std::floating_point<W>
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

        template <std::regular T, typename W>
        requires std::integral<W> || std::floating_point<W>
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
