#pragma once

#include "rs-core/arithmetic.hpp"
#include "rs-core/bitwise-integer.hpp"
#include "rs-core/enum.hpp"
#include "rs-core/format.hpp"
#include "rs-core/global.hpp"
#include "rs-core/iterator.hpp"
#include "rs-core/mp-integer.hpp"
#include <algorithm>
#include <bit>
#include <cmath>
#include <compare>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <initializer_list>
#include <iterator>
#include <limits>
#include <map>
#include <numbers>
#include <random>
#include <ranges>
#include <type_traits>
#include <vector>

namespace RS {

    // Good LCG transformations for 32 and 64 bit integers
    // Pierre L'Ecuyer (1999), "Tables of Linear Congruential Generators of Different Sizes and Good Lattice Structure"
    // http://www.ams.org/journals/mcom/1999-68-225/S0025-5718-99-00996-5/S0025-5718-99-00996-5.pdf

    constexpr std::uint32_t lcg32(std::uint32_t x) noexcept {
        constexpr std::uint32_t m = 32'310'901ul;
        constexpr std::uint32_t c = 850'757'001ul;
        return m * x + c;
    }

    constexpr std::uint64_t lcg64(std::uint64_t x) noexcept {
        constexpr std::uint64_t m = 3'935'559'000'370'003'845ull;
        constexpr std::uint64_t c = 8'831'144'850'135'198'739ull;
        return m * x + c;
    }

    constexpr uint128_t lcg128(uint128_t x) noexcept {
        constexpr auto m = make_uint128(0x2360'ed05'1fc6'5da4ull, 0x4385'df64'9fcc'f645ull);
        constexpr auto c = make_uint128(0x55bf'e625'0318'f820ull, 0xe2d4'afe5'108d'a1e3ull);
        return m * x + c;
    }

    template <UnsignedIntegral U>
    class LcgBase {
    public:
        using result_type = U;
        constexpr bool operator==(const LcgBase& rhs) const = default;
        constexpr void seed(U s) noexcept { state_ = s; }
        constexpr static U min() noexcept { return 0; }
        constexpr static U max() noexcept { return ~ U(0); }
    protected:
        constexpr LcgBase() noexcept = default;
        constexpr explicit LcgBase(U s) noexcept: state_(s) {}
        constexpr U get_state() const noexcept { return state_; }
    private:
        U state_ = 0;
    };

    class Lcg32:
    public LcgBase<std::uint32_t> {
    public:
        constexpr Lcg32() noexcept = default;
        constexpr explicit Lcg32(std::uint32_t s) noexcept: LcgBase<std::uint32_t>{s} {}
        constexpr std::uint32_t operator()() noexcept { seed(lcg32(get_state())); return get_state(); }
    };

    class Lcg64:
    public LcgBase<std::uint64_t> {
    public:
        constexpr Lcg64() noexcept = default;
        constexpr explicit Lcg64(std::uint64_t s) noexcept: LcgBase<std::uint64_t>(s) {}
        std::uint64_t constexpr operator()() noexcept { seed(lcg64(get_state())); return get_state(); }
    };

    class Lcg128:
    public LcgBase<uint128_t> {
    public:
        constexpr Lcg128() noexcept = default;
        constexpr explicit Lcg128(uint128_t s) noexcept: LcgBase<uint128_t>(s) {}
        constexpr explicit Lcg128(std::uint64_t s1, std::uint64_t s2) noexcept: LcgBase<uint128_t>{make_uint128(s1, s2)} {}
        uint128_t constexpr operator()() noexcept { seed(lcg128(get_state())); return get_state(); }
        void constexpr seed(uint128_t s) noexcept { LcgBase<uint128_t>::seed(s); }
        void constexpr seed(std::uint64_t s1, std::uint64_t s2) noexcept { seed(make_uint128(s1, s2)); }
    };

    // PCG64-DXSM algorithm by Melissa O'Neill and Tony Finch
    // http://www.pcg-random.org/
    // https://dotat.at/@/2023-06-21-pcg64-dxsm.html

    class Pcg {

    public:

        using result_type = std::uint64_t;

        constexpr Pcg() noexcept { seed(default_seed); }
        constexpr explicit Pcg(std::uint64_t s) noexcept { seed(s); }
        constexpr explicit Pcg(std::uint64_t s0, std::uint64_t s1) noexcept { seed(s0, s1); }
        constexpr explicit Pcg(std::uint64_t s0, std::uint64_t s1, std::uint64_t s2, std::uint64_t s3) noexcept
            { seed(s0, s1, s2, s3); }

        constexpr std::uint64_t operator()() noexcept;

        constexpr void seed(std::uint64_t s) noexcept { seed(0, s, 0, 0); }
        constexpr void seed(std::uint64_t s0, std::uint64_t s1) noexcept { seed(s0, s1, 0, 0); }
        constexpr void seed(std::uint64_t s0, std::uint64_t s1, std::uint64_t s2, std::uint64_t s3) noexcept;

        constexpr static std::uint64_t min() noexcept { return 0; }
        constexpr static std::uint64_t max() noexcept { return max64; }

        constexpr friend bool operator==(const Pcg& a, const Pcg& b) noexcept
            { return a.state_ == b.state_ && a.delta_ == b.delta_; }

    private:

        constexpr static std::uint64_t default_seed = 0xcafe'f00d'd15e'a5e5ull;

        uint128_t state_;
        uint128_t delta_;

    };

        constexpr std::uint64_t Pcg::operator()() noexcept {
            constexpr static std::uint64_t k = 0xda94'2042'e4dd'58b5ull;
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

    // Concepts

    template <typename D, typename E>
    concept RandomDistributionWithEngine =
        std::uniform_random_bit_generator<E>
        && std::copyable<D>
        && std::copyable<typename D::result_type>
        && requires (D dst, E rng) {
            { dst(rng) } -> std::convertible_to<typename D::result_type>;
        };

    template <typename D>
    concept RandomDistribution =
        RandomDistributionWithEngine<D, std::minstd_rand>
        && RandomDistributionWithEngine<D, std::mt19937>
        && RandomDistributionWithEngine<D, std::mt19937_64>
        && RandomDistributionWithEngine<D, Pcg>;

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
            constexpr static auto bits_out = std::numeric_limits<T>::digits;
            constexpr static auto good_bits = std::bit_width(RNG::max() - RNG::min() + 1) - 1;
            constexpr static auto mask = (R{1} << good_bits) - 1;
            constexpr static auto n_calls = (bits_out + good_bits - 1) / good_bits;
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

        template <std::uniform_random_bit_generator RNG> constexpr T operator()(RNG& rng) const;

        constexpr T min() const noexcept { return min_; }
        constexpr T max() const noexcept { return max_; }
        constexpr double mean() const noexcept;
        double sd() const noexcept;

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

        template <Integral T>
        constexpr double UniformInteger<T>::mean() const noexcept {
            auto a = static_cast<double>(min_);
            auto b = static_cast<double>(max_);
            return 0.5 * (a + b);
        }

        template <Integral T>
        double UniformInteger<T>::sd() const noexcept {
            auto a = static_cast<double>(min_);
            auto b = static_cast<double>(max_);
            auto c = b - a + 1.0;
            return std::sqrt((c * c - 1.0) / 12.0);
        }

    // Bernoulli distribution

    class BernoulliDistribution {

    public:

        constexpr BernoulliDistribution() = default;
        constexpr explicit BernoulliDistribution(double p) noexcept;
        constexpr explicit BernoulliDistribution(std::uint64_t num, std::uint64_t den) noexcept;

        template <std::uniform_random_bit_generator RNG> constexpr bool operator()(RNG& rng) const;

        constexpr static bool min() noexcept { return false; }
        constexpr static bool max() noexcept { return true; }

    private:

        constexpr static auto max64 = static_cast<std::uint64_t>(-1);

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
            return dist_(rng) < threshold_;
        }

    // Uniform floating point distribution

    // Badizadegan's algorithm
    // https://specbranch.com/posts/fp-rand/

    namespace Detail {

        template <std::floating_point T, std::unsigned_integral U, std::uniform_random_bit_generator RNG>
        constexpr T generate_real(RNG& r) noexcept {

            static_assert(sizeof(T) == sizeof(U));

            using limits = std::numeric_limits<T>;

            constexpr static auto significand_bits = limits::digits - 1;
            constexpr static auto exponent_range = static_cast<U>(significand_bits) << significand_bits;
            constexpr static auto underflow_tail = (limits::max_exponent - 1) % significand_bits;
            constexpr static auto underflow_shift = significand_bits - underflow_tail;

            auto generate_bits = [&r] (int bits) {
                constexpr static UniformInteger<U> uniform_bits;
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
        constexpr explicit UniformReal(T a, T b) noexcept;

        template <std::uniform_random_bit_generator RNG> constexpr T operator()(RNG& rng) const;

        constexpr T min() const noexcept { return min_; }
        constexpr T max() const noexcept { return max_; }
        constexpr T mean() const noexcept { return min_ / T{2} + max_ / T{2}; }
        T sd() const noexcept { return (max_ - min_) / std::sqrt(T{12}); }

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
        constexpr UniformReal<T>::UniformReal(T a, T b) noexcept:
        min_(a),
        max_(b) {

            if (min_ > max_) {
                std::swap(min_, max_);
            }

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
                    constexpr static auto threshold = RNG::min() + (RNG::max() - RNG::min()) / 2;
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

    template <std::floating_point T>
    class LogUniform {

    public:

        using result_type = T;

        constexpr LogUniform() = default;
        constexpr explicit LogUniform(T a, T b) noexcept;

        template <std::uniform_random_bit_generator RNG> constexpr T operator()(RNG& rng) const;

        constexpr T min() const noexcept { return min_; }
        constexpr T max() const noexcept { return max_; }
        T mean() const noexcept;
        T sd() const noexcept;

    private:

        UniformReal<T> dist_{T{0}};
        T min_{1};
        T max_{1};

    };

        template <std::floating_point T>
        constexpr LogUniform<T>::LogUniform(T a, T b) noexcept:
        dist_{std::log(a), std::log(b)}, min_{a}, max_{b} {
            if (min_ > max_) {
                std::swap(min_, max_);
            }
        }

        template <std::floating_point T>
        template <std::uniform_random_bit_generator RNG>
        constexpr T LogUniform<T>::operator()(RNG& rng) const {
            return std::clamp(std::exp(dist_(rng)), min_, max_);
        }

        template <std::floating_point T>
        T LogUniform<T>::mean() const noexcept {
            return (max_ - min_) / std::log(max_ / min_);
        }

        template <std::floating_point T>
        T LogUniform<T>::sd() const noexcept {
            auto m = mean();
            auto c = (max_ * max_ - min_ * min_) / (T{2} * std::log(max_ / min_));
            return std::sqrt(c - m * m);
        }

    // Normal distribution

    namespace Detail {

        template <std::floating_point T>
        T inverse_erfc(T x) noexcept {

            using namespace std::numbers;

            using Limits = std::numeric_limits<T>;

            constexpr static auto epsilon = T{2} * Limits::epsilon();
            constexpr static auto sqrtpi_over_2 = T{1} / (T{2} * inv_sqrtpi_v<T>);

            static const auto inverse_derivative = [] (T x) {
                return - sqrtpi_over_2 * std::exp(x * x);
            };

            if (x > T{1}) {
                return - inverse_erfc(T{2} - x);
            }

            auto y = std::sqrt(- std::log(x));

            for (;;) {
                auto z = std::erfc(y) - x;
                if (z == T{0}) {
                    return y;
                }
                auto delta = - z * inverse_derivative(y);
                if (std::abs(delta) < epsilon * std::abs(y)) {
                    return y + delta / T{2};
                }
                y += delta;
            }

        }

    }

    template <std::floating_point T>
    class NormalDistribution {

    public:

        using result_type = T;

        constexpr NormalDistribution() = default;
        constexpr explicit NormalDistribution(T mean, T sd) noexcept;

        template <std::uniform_random_bit_generator RNG> constexpr T operator()(RNG& rng) const;

        constexpr T min() const noexcept { return - std::numeric_limits<T>::infinity(); }
        constexpr T max() const noexcept { return std::numeric_limits<T>::infinity(); }
        constexpr T mean() const noexcept { return mean_; }
        constexpr T sd() const noexcept { return sd_; }

        T pdf(T x) const noexcept { return pdf_z((x - mean_) / sd_); }
        T cdf(T x) const noexcept { return cdf_z((x - mean_) / sd_); }
        T ccdf(T x) const noexcept { return cdf_z((mean_ - x) / sd_); }
        T quantile(T p) const noexcept { return mean_ + sd_ * q_z(p); }
        T cquantile(T q) const noexcept { return mean_ - sd_ * q_z(q); }

    private:

        T mean_{0};
        T sd_{1};

        T pdf_z(T z) const noexcept;
        T cdf_z(T z) const noexcept;
        T q_z(T p) const noexcept;

    };

        template <std::floating_point T>
        constexpr NormalDistribution<T>::NormalDistribution(T mean, T sd) noexcept:
        mean_(mean),
        sd_(std::abs(sd)) {}

        template <std::floating_point T>
        template <std::uniform_random_bit_generator RNG>
        constexpr T NormalDistribution<T>::operator()(RNG& rng) const {
            using namespace std::numbers;
            UniformReal<T> unit;
            auto u = unit(rng);
            auto v = unit(rng);
            auto z = std::sqrt(T{-2} * std::log(u)) * std::cos(T{2} * pi_v<T> * v);
            return mean_ + z * sd_;
        }

        template <std::floating_point T>
        T NormalDistribution<T>::pdf_z(T z) const noexcept {
            using namespace std::numbers;
            constexpr static auto k = inv_sqrtpi_v<T> / sqrt2_v<T>;
            return k * std::exp(- z * z / T{2});
        }

        template <std::floating_point T>
        T NormalDistribution<T>::cdf_z(T z) const noexcept {
            using namespace std::numbers;
            constexpr static auto k = T{1} / sqrt2_v<T>;
            return std::erfc(- k * z) / T{2};
        }

        template <std::floating_point T>
        T NormalDistribution<T>::q_z(T p) const noexcept {
            using namespace std::numbers;
            return - sqrt2_v<T> * Detail::inverse_erfc(T{2} * p);
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
        bool empty() const noexcept { return vec_.empty(); }
        std::size_t size() const noexcept { return vec_.size(); }

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

        struct entry_type {
            T value;
            W weight;
            template <std::convertible_to<T> U> entry_type(const U& u): value(u), weight(1) {}
            template <std::convertible_to<T> U> entry_type(const U& u, W w): value(u), weight(w) {}
        };

        WeightedChoice() = default;
        WeightedChoice(std::initializer_list<entry_type> list);

        template <std::uniform_random_bit_generator RNG>
            const T& operator()(RNG& rng) const; // UB if empty

        void insert(const T& t, W w = static_cast<W>(1)); // Ignored if w<=0
        bool empty() const noexcept { return map_.empty(); }
        std::size_t size() const noexcept { return map_.size(); }
        W total() const { return empty() ? W{} : std::prev(map_.end())->first; }

    private:

        using weight_dist = Detail::UniformDistribution<W>::type;

        std::map<W, T> map_;
        weight_dist dist_;

    };

        template <std::regular T, Arithmetic W>
        WeightedChoice<T, W>::WeightedChoice(std::initializer_list<entry_type> list) {
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

    template <typename T, std::uniform_random_bit_generator RNG>
    requires (std::integral<T> || std::is_enum_v<T>)
    T random_bit(T mask, RNG& rng) {

        unsigned long long umask;

        if constexpr (std::is_enum_v<T>) {
            using UT = std::underlying_type_t<T>;
            auto utmask = static_cast<UT>(mask);
            if constexpr (std::signed_integral<UT>) {
                umask = static_cast<std::make_unsigned_t<UT>>(utmask);
            } else {
                umask = utmask;
            }
        } else if constexpr (std::signed_integral<T>) {
            umask = static_cast<std::make_unsigned_t<T>>(mask);
        } else {
            umask = mask;
        }

        auto n_bits = std::popcount(umask);

        if (n_bits <= 1) {
            return mask;
        }

        auto index = UniformInteger<int>{n_bits}(rng) + 1;
        auto count = 0;
        unsigned long long rc = 1;

        for (;;) {
            if (has_bit(rc, mask) && ++count == index) {
                return static_cast<T>(rc);
            }
            rc <<= 1;
        }

    }

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

    // Random iterators

    template <RandomDistribution D, std::uniform_random_bit_generator E>
    class RandomIterator:
    public Iterator<RandomIterator<D, E>, const typename D::result_type, std::forward_iterator_tag> {
    public:
        RandomIterator() = default;
        explicit RandomIterator(const D& d, const E& e): dist_{d}, engine_{e} {}
        const D::result_type& operator*() const;
        RandomIterator& operator++() { ready_ = false; return *this; }
        bool operator==(const RandomIterator& j) const noexcept { return engine_ == j.engine_; }
        bool operator==(std::nullptr_t) const noexcept { return false; }
    private:
        mutable D dist_;
        mutable E engine_;
        mutable D::result_type value_;
        mutable bool ready_ = false;
    };

        template <RandomDistribution D, std::uniform_random_bit_generator E>
        const D::result_type& RandomIterator<D, E>::operator*() const {
            if (! ready_) {
                value_ = dist_(engine_);
                ready_ = true;
            }
            return value_;
        }

    template <RandomDistribution D, std::uniform_random_bit_generator E>
    auto random_range(const D& d, const E& e) {
        RandomIterator<D, E> i{d, e};
        return std::ranges::subrange{i, nullptr};
    }

    template <RandomDistribution D, std::uniform_random_bit_generator E>
    class IndirectRandomIterator:
    public Iterator<IndirectRandomIterator<D, E>, const typename D::result_type, std::forward_iterator_tag> {
    public:
        IndirectRandomIterator() = default;
        explicit IndirectRandomIterator(const D& d, E& e): dist_{d}, engine_{&e} {}
        const D::result_type& operator*() const;
        IndirectRandomIterator& operator++() { ready_ = false; return *this; }
        bool operator==(const IndirectRandomIterator& j) const noexcept { return engine_ == j.engine_; }
        bool operator==(std::nullptr_t) const noexcept { return false; }
    private:
        mutable D dist_;
        E* engine_;
        mutable D::result_type value_;
        mutable bool ready_ = false;
    };

        template <RandomDistribution D, std::uniform_random_bit_generator E>
        const D::result_type& IndirectRandomIterator<D, E>::operator*() const {
            if (! ready_) {
                value_ = dist_(*engine_);
                ready_ = true;
            }
            return value_;
        }

    template <RandomDistribution D, std::uniform_random_bit_generator E>
    auto indirect_random_range(const D& d, E& e) {
        IndirectRandomIterator<D, E> i{d, e};
        return std::ranges::subrange{i, nullptr};
    }


}
