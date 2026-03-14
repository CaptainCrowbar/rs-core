#pragma once

#include "rs-core/arithmetic.hpp"
#include "rs-core/enum.hpp"
#include "rs-core/global.hpp"
#include "rs-core/range.hpp"
#include <algorithm>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <initializer_list>
#include <map>
#include <ranges>
#include <stdexcept>
#include <utility>
#include <vector>

namespace RS {

    // Supporting types

    RS_BITMASK(Lerp, unsigned char,
        linear  = 0,
        log_x   = 1,
        log_y   = 2,
        log_xy  = 3,
    )

    // Concepts

    template <typename U, typename T, Lerp Mode>
    concept InterpolateFrom = std::floating_point<U>
        || (! has_bit(Mode, Lerp::log_y) && requires (T x, U y) {
            { y + y } -> std::convertible_to<U>;
            { y - y } -> std::convertible_to<U>;
            { x * y } -> std::convertible_to<U>;
            { y * x } -> std::convertible_to<U>;
        });

    // Linear interpolation over an interval

    template <Lerp Mode = Lerp::linear, std::floating_point T, InterpolateFrom<T, Mode> U>
    U interpolate(T x1, U y1, T x2, U y2, T x3) noexcept {

        if constexpr (has_bit(Mode, Lerp::log_x)) {
            x1 = std::log(x1);
            x2 = std::log(x2);
            x3 = std::log(x3);
        }

        if constexpr (has_bit(Mode, Lerp::log_y)) {
            y1 = std::log(y1);
            y2 = std::log(y2);
        }

        auto fraction = (x3 - x1) / (x2 - x1);
        auto y3 = y1 + fraction * (y2 - y1);

        if constexpr (has_bit(Mode, Lerp::log_y)) {
            y3 = std::exp(y3);
        }

        return y3;

    }

    // Multipoint linear interpolation

    template <std::floating_point T, typename U = T, Lerp Mode = Lerp::linear>
    requires InterpolateFrom<U, T, Mode>
    class LinearMap {

    public:

        using x_type = T;
        using y_type = U;

        static constexpr Lerp mode = Mode;
        static constexpr bool is_log_x = has_bit(Mode, Lerp::log_x);
        static constexpr bool is_log_y = has_bit(Mode, Lerp::log_y);

        LinearMap() = default;
        LinearMap(std::initializer_list<std::pair<T, U>> list) { for (auto [x,y]: list) { insert(x, y); } }
        explicit LinearMap(ReadableRange<std::pair<T, U>> auto points) { for (auto [x,y]: points) { insert(x, y); } }

        U operator()(T x) const;
        void insert(T x, U y);
        bool empty() const noexcept { return map_.empty(); }
        std::size_t size() const noexcept { return map_.size(); }

    private:

        std::map<T, U> map_;

    };

        template <std::floating_point T, typename U, Lerp Mode>
        requires InterpolateFrom<U, T, Mode>
        U LinearMap<T, U, Mode>::operator()(T x) const {

            if (map_.empty()) {
                return {};
            }

            auto fix_y = [] (U y) {
                if constexpr (is_log_y) {
                    return std::exp(y);
                } else {
                    return y;
                }
            };

            if (map_.size() == 1) {
                return fix_y(map_.begin()->second);
            }

            if constexpr (is_log_x) {
                x = std::log(x);
            }

            auto i = map_.lower_bound(x);

            if (i == map_.end()) {
                --i;
            } else if (i->first == x) {
                return fix_y(i->second);
            }

            auto j = i;

            if (i == map_.begin()) {
                ++j;
            } else {
                --i;
            }

            auto y = interpolate(i->first, i->second, j->first, j->second, x);
            y = fix_y(y);

            return y;

        }

        template <std::floating_point T, typename U, Lerp Mode>
        requires InterpolateFrom<U, T, Mode>
        void LinearMap<T, U, Mode>::insert(T x, U y) {

            if constexpr (is_log_x) {
                if (x <= T{0}) {
                    throw std::domain_error("Invalid X value in logarithmic interpolation");
                }
                x = std::log(x);
            }

            if constexpr (is_log_y) {
                if (y <= T{0}) {
                    throw std::domain_error("Invalid Y value in logarithmic interpolation");
                }
                y = std::log(y);
            }

            if (! map_.emplace(x, y).second) {
                throw std::domain_error("Degenerate points in Lagrange polynomial");
            }

        }

    // Lagrange polynomial interpolation

    template <std::floating_point T, Lerp Mode = Lerp::linear>
    class LagrangePolynomial {

    public:

        using scalar_type = T;

        static constexpr Lerp mode = Mode;
        static constexpr bool is_log_x = has_bit(Mode, Lerp::log_x);
        static constexpr bool is_log_y = has_bit(Mode, Lerp::log_y);

        LagrangePolynomial() = default;
        LagrangePolynomial(std::initializer_list<std::pair<T, T>> list): points_{list} { init(); }
        explicit LagrangePolynomial(ReadableRange<std::pair<T, T>> auto points): points_{std::from_range, points} { init(); }

        T operator()(T x) const;
        bool empty() const noexcept { return points_.empty(); }
        std::size_t size() const noexcept { return points_.size(); }

    private:

        std::vector<std::pair<T, T>> points_;
        std::vector<T> denominators_;

        void init();

    };

        template <std::floating_point T, Lerp Mode>
        T LagrangePolynomial<T, Mode>::operator()(T x) const {

            if constexpr (is_log_x) {
                x = std::log(x);
            }

            T y{0};

            for (auto i = 0uz; i < points_.size(); ++i) {
                T numerator{1};
                for (auto j = 0uz; j < points_.size(); ++j) {
                    if (j != i) {
                        numerator *= x - points_[j].first;
                    }
                }
                y += points_[i].second * numerator / denominators_[i];
            }

            if constexpr (is_log_y) {
                y = std::exp(y);
            }

            return y;

        }

        template <std::floating_point T, Lerp Mode>
        void LagrangePolynomial<T, Mode>::init() {

            denominators_.assign(points_.size(), T{1});
            std::ranges::sort(points_);
            auto it = std::ranges::adjacent_find(points_);

            if (it != points_.end()) {
                throw std::domain_error("Degenerate points in Lagrange polynomial");
            }

            if constexpr (Mode != Lerp::linear) {
                for (auto& [x,y]: points_) {
                    if constexpr (is_log_x) {
                        x = std::log(x);
                    }
                    if constexpr (is_log_y) {
                        y = std::log(y);
                    }
                }
            }

            for (auto i = 0uz; i < points_.size(); ++i) {
                for (auto j = 0uz; j < points_.size(); ++j) {
                    if (j != i) {
                        denominators_[i] *= points_[i].first - points_[j].first;
                    }
                }
            }

        }

    // Cubic spline interpolation

    template <std::floating_point T, Lerp Mode = Lerp::linear>
    class CubicSpline {

    public:

        using scalar_type = T;

        static constexpr Lerp mode = Mode;
        static constexpr bool is_log_x = has_bit(Mode, Lerp::log_x);
        static constexpr bool is_log_y = has_bit(Mode, Lerp::log_y);

        CubicSpline() = default;
        CubicSpline(std::initializer_list<std::pair<T, T>> list): points_{list} { init(); }
        explicit CubicSpline(ReadableRange<std::pair<T, T>> auto points): points_{points} { init(); }

        T operator()(T x) const;
        bool empty() const noexcept { return points_.empty(); }
        std::size_t size() const noexcept { return points_.size(); }

    private:

        std::vector<std::pair<T, T>> points_;
        std::vector<T> deriv2_;
        std::size_t count_ = 0;

        void init();
        T px(std::size_t i) const noexcept { return points_[i].first; }
        T py(std::size_t i) const noexcept { return points_[i].second; }

    };

        template <std::floating_point T, Lerp Mode>
        T CubicSpline<T, Mode>::operator()(T x) const {

            if constexpr (is_log_x) {
                x = std::log(x);
            }

            auto it = std::ranges::upper_bound(points_, std::make_pair(x, 0.0));

            if (it == points_.end()) {
                --it;
            }

            if (it != points_.begin()) {
                --it;
            }

            auto j = static_cast<std::size_t>(it - points_.begin());
            auto dx = px(j + 1) - px(j);
            auto q_prev = (x - px(j)) / dx;
            auto q_next = (px(j + 1) - x) / dx;
            auto qp_cubic = q_prev * (q_prev * q_prev - 1);
            auto qn_cubic = q_next * (q_next * q_next - 1);
            auto d20 = deriv2_[j];
            auto d21 = deriv2_[j + 1];
            auto y = q_next * py(j) + q_prev * py(j + 1) + dx * dx * (qn_cubic * d20 + qp_cubic * d21) / T{6};

            if constexpr (is_log_y) {
                y = std::exp(y);
            }

            return y;

        }

        template <std::floating_point T, Lerp Mode>
        void CubicSpline<T, Mode>::init() {

            count_ = points_.size();

            if (count_ < 4) {
                throw std::domain_error("Not enough points for cubic spline");
            }

            std::ranges::sort(points_);
            auto it = std::ranges::adjacent_find(points_);

            if (it != points_.end()) {
                throw std::domain_error("Degenerate points in cubic spline");
            }

            if constexpr (Mode != Lerp::linear) {
                for (auto& [x,y]: points_) {
                    if constexpr (is_log_x) {
                        x = std::log(x);
                    }
                    if constexpr (is_log_y) {
                        y = std::log(y);
                    }
                }
            }

            deriv2_.resize(points_.size(), 0.0);
            std::vector<T> d2_offset(count_ - 1, 0.0);

            for (auto i = 1uz; i < count_ - 1; ++i) {
                auto dx_prev = px(i) - px(i - 1);
                auto dx_next = px(i + 1) - px(i);
                auto dy_prev = py(i) - py(i - 1);
                auto dy_next = py(i + 1) - py(i);
                auto delta_d = dy_next / dx_next - dy_prev / dx_prev;
                auto divisor = dx_prev * (deriv2_[i - 1] + T{2}) + dx_next * T{2};
                deriv2_[i] = - dx_next / divisor;
                d2_offset[i] = (delta_d * T{6} - dx_prev * d2_offset[i - 1]) / divisor;
            }

            for (auto i = count_ - 1; i > 0; --i) {
                deriv2_[i - 1] = deriv2_[i - 1] * deriv2_[i] + d2_offset[i - 1];
            }

        }

}
