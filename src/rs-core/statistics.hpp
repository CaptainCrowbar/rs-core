#pragma once

#include "rs-core/global.hpp"
#include <algorithm>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <limits>

namespace RS {

    // https://www.johndcook.com/blog/standard_deviation/
    // https://www.johndcook.com/blog/skewness_kurtosis/
    // https://www.johndcook.com/blog/running_regression/

    template <std::floating_point T = double>
    class Statistics {

    public:

        constexpr Statistics() = default;

        constexpr Statistics& operator()(T x) noexcept;
        constexpr Statistics& operator()(T x, T y) noexcept;
        constexpr Statistics operator+(const Statistics& s) const noexcept;
        constexpr Statistics& operator+=(const Statistics& s) noexcept { return *this = *this + s; }

        constexpr void clear() noexcept;
        constexpr T count() const noexcept { return static_cast<T>(count_); }
        constexpr std::size_t icount() const noexcept { return count_; }

        constexpr T min() const noexcept { return x_min(); }
        constexpr T max() const noexcept { return x_max(); }
        constexpr T mean() const noexcept { return x_mean(); }
        constexpr T variance() const noexcept { return x_variance(); }
        T sd() const noexcept { return x_sd(); }
        constexpr T raw_variance() const noexcept { return x_raw_variance(); }
        T raw_sd() const noexcept { return x_raw_sd(); }
        T skewness() const noexcept { return x_skewness(); }
        T kurtosis() const noexcept { return x_kurtosis(); }

        constexpr T x_min() const noexcept { return check(min_x_, 1); }
        constexpr T x_max() const noexcept { return check(max_x_, 1); }
        constexpr T x_mean() const noexcept { return check(mean_x_, 1); }
        constexpr T x_variance() const noexcept { return check(mean_x2_ / (count() - T{1}), 2); }
        T x_sd() const noexcept { return std::sqrt(x_variance()); }
        constexpr T x_raw_variance() const noexcept { return check(mean_x2_ / count(), 1); }
        T x_raw_sd() const noexcept { return std::sqrt(x_raw_variance()); }
        T x_skewness() const noexcept { return check(std::sqrt(count()) * mean_x3_ / std::pow(mean_x2_, T{3} / T{2}), 2); }
        T x_kurtosis() const noexcept { return check(count() * mean_x4_ / (mean_x2_ * mean_x2_) - T{3}, 2); }

        constexpr T y_min() const noexcept { return check(min_y_, 1); }
        constexpr T y_max() const noexcept { return check(max_y_, 1); }
        constexpr T y_mean() const noexcept { return check(mean_y_, 1); }
        constexpr T y_variance() const noexcept { return check(mean_y2_ / (count() - T{1}), 2); }
        T y_sd() const noexcept { return std::sqrt(y_variance()); }
        constexpr T y_raw_variance() const noexcept { return check(mean_y2_ / count(), 1); }
        T y_raw_sd() const noexcept { return std::sqrt(y_raw_variance()); }
        T y_skewness() const noexcept { return check(std::sqrt(count()) * mean_y3_ / std::pow(mean_y2_, T{3} / T{2}), 2); }
        T y_kurtosis() const noexcept { return check(count() * mean_y4_ / (mean_y2_ * mean_y2_) - T{3}, 2); }

        T r() const noexcept { return check(sum_xy_ / (x_sd() * y_sd() * (count() - T{1})), 1); }
        T a() const noexcept { return check(sum_xy_ / (x_variance() * (count() - T{1})), 1); }
        T b() const noexcept { return check(mean_y_ - a() * mean_x_, 1); }
        T inv_a() const noexcept { return check(sum_xy_ / (y_variance() * (count() - T{1})), 1); }
        T inv_b() const noexcept { return check(mean_x_ - inv_a() * mean_y_, 1); }

    private:

        using limits = std::numeric_limits<T>;

        std::size_t count_ {0};
        T mean_x_ {0};
        T mean_x2_ {0};
        T mean_x3_ {0};
        T mean_x4_ {0};
        T min_x_ {limits::max()};
        T max_x_ {limits::min()};
        T mean_y_ {0};
        T mean_y2_ {0};
        T mean_y3_ {0};
        T mean_y4_ {0};
        T min_y_ {limits::max()};
        T max_y_ {limits::min()};
        T sum_xy_ {0};

        constexpr T check(T t, std::size_t min_count) const noexcept { return count_ < min_count ? T{0} : t; }

    };

    template <std::floating_point T>
    constexpr Statistics<T>& Statistics<T>::operator()(T x) noexcept {

        ++count_;

        min_x_ = std::min(min_x_, x);
        max_x_ = std::max(max_x_, x);

        auto x_delta = x - mean_x_;
        auto x_delta_n = x_delta / count();
        auto x_delta_n2 = x_delta_n * x_delta_n;
        auto x_term = x_delta * x_delta_n * (count() - T{1});

        mean_x_ += x_delta_n;
        mean_x4_ += x_term * x_delta_n2 * (count() * count() - T{3} * count() + T{3})
            + T{6} * x_delta_n2 * mean_x2_ - T{4} * x_delta_n * mean_x3_;
        mean_x3_ += x_term * x_delta_n * (count() - T{2}) - T{3} * x_delta_n * mean_x2_;
        mean_x2_ += x_term;

        return *this;

    }

    template <std::floating_point T>
    constexpr Statistics<T>& Statistics<T>::operator()(T x, T y) noexcept {

        sum_xy_ += (x_mean() - x ) * (y_mean() - y) * count() / (count() + 1);

        ++count_;

        min_x_ = std::min(min_x_, x);
        max_x_ = std::max(max_x_, x);

        auto x_delta = x - mean_x_;
        auto x_delta_n = x_delta / count();
        auto x_delta_n2 = x_delta_n * x_delta_n;
        auto x_term = x_delta * x_delta_n * (count() - T{1});

        mean_x_ += x_delta_n;
        mean_x4_ += x_term * x_delta_n2 * (count() * count() - T{3} * count() + T{3})
            + T{6} * x_delta_n2 * mean_x2_ - T{4} * x_delta_n * mean_x3_;
        mean_x3_ += x_term * x_delta_n * (count() - T{2}) - T{3} * x_delta_n * mean_x2_;
        mean_x2_ += x_term;

        min_y_ = std::min(min_y_, y);
        max_y_ = std::max(max_y_, y);

        auto y_delta = y - mean_y_;
        auto y_delta_n = y_delta / count();
        auto y_delta_n2 = y_delta_n * y_delta_n;
        auto y_term = y_delta * y_delta_n * (count() - T{1});

        mean_y_ += y_delta_n;
        mean_y4_ += y_term * y_delta_n2 * (count() * count() - T{3} * count() + T{3})
            + T{6} * y_delta_n2 * mean_y2_ - T{4} * y_delta_n * mean_y3_;
        mean_y3_ += y_term * y_delta_n * (count() - T{2}) - T{3} * y_delta_n * mean_y2_;
        mean_y2_ += y_term;

        return *this;

    }

    template <std::floating_point T>
    constexpr Statistics<T> Statistics<T>::operator+(const Statistics& s) const noexcept {

        Statistics result;

        result.count_ = count_ + s.count_;
        result.min_x_ = std::min(min_x_, s.min_x_);
        result.max_x_ = std::max(max_x_, s.max_x_);
        result.min_y_ = std::min(min_y_, s.min_y_);
        result.max_y_ = std::max(max_y_, s.max_y_);

        auto t_count2 = count() * count();
        auto s_count2 = s.count() * s.count();
        auto r_count2 = result.count() * result.count();
        auto r_count3 = result.count() * r_count2;
        auto x_delta = s.mean_x_ - mean_x_;
        auto x_delta2 = x_delta * x_delta;
        auto x_delta3 = x_delta * x_delta2;
        auto x_delta4 = x_delta2 * x_delta2;
        auto y_delta = s.mean_y_ - mean_y_;
        auto y_delta2 = y_delta * y_delta;
        auto y_delta3 = y_delta * y_delta2;
        auto y_delta4 = y_delta2 * y_delta2;

        result.mean_x_ = (count() * mean_x_ + s.count() * s.mean_x_) / result.count();
        result.mean_x2_ = mean_x2_ + s.mean_x2_ + x_delta2 * count() * s.count() / result.count();
        result.mean_x3_ = mean_x3_ + s.mean_x3_ + x_delta3 * count() * s.count() * (count() - s.count()) / r_count2
            + T{3} * x_delta * (count() * s.mean_x2_ - s.count() * mean_x2_) / result.count();
        result.mean_x4_ = mean_x4_ + s.mean_x4_ + x_delta4 * count() * s.count() * (t_count2 - count() * s.count() + s_count2) / r_count3
            + T{6} * x_delta2 * (t_count2 * s.mean_x2_ + s_count2 * mean_x2_) / r_count2
            + T{4} * x_delta * (count() * s.mean_x3_ - s.count() * mean_x3_) / result.count();

        result.mean_y_ = (count() * mean_y_ + s.count() * s.mean_y_) / result.count();
        result.mean_y2_ = mean_y2_ + s.mean_y2_ + y_delta2 * count() * s.count() / result.count();
        result.mean_y3_ = mean_y3_ + s.mean_y3_ + y_delta3 * count() * s.count() * (count() - s.count()) / r_count2
            + T{3} * y_delta * (count() * s.mean_y2_ - s.count() * mean_y2_) / result.count();
        result.mean_y4_ = mean_y4_ + s.mean_y4_ + y_delta4 * count() * s.count() * (t_count2 - count() * s.count() + s_count2) / r_count3
            + T{6} * y_delta2 * (t_count2 * s.mean_y2_ + s_count2 * mean_y2_) / r_count2
            + T{4} * y_delta * (count() * s.mean_y3_ - s.count() * mean_y3_) / result.count();

        result.sum_xy_ = sum_xy_ + s.sum_xy_ + count() * s.count() * x_delta * y_delta / result.count();

        return result;

    }

    template <std::floating_point T>
    constexpr void Statistics<T>::clear() noexcept {
        count_ = 0;
        mean_x_ = mean_x2_ = mean_x3_ = mean_x4_ = T{0};
        mean_y_ = mean_y2_ = mean_y3_ = mean_y4_ = T{0};
        sum_xy_ = T{0};
        min_x_ = min_y_ = limits::max();
        max_x_ = max_y_ = limits::min();
    }

}
