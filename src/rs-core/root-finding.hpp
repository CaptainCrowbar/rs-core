#pragma once

#include "rs-core/arithmetic.hpp"
#include "rs-core/global.hpp"
#include <cmath>
#include <concepts>
#include <cstdlib>
#include <format>
#include <stdexcept>

namespace RS {

    // Concepts

    template <typename F, typename T>
    concept Endomorphism = std::invocable<F, T>
        && requires (T t, F f) {
            { f(t) } -> std::convertible_to<T>;
        };

    // Root finder base class

    template <std::floating_point T>
    class RootFinder {

    public:

        static constexpr T default_epsilon = static_cast<T>(sizeof(T) < sizeof(double) ? 1e-4 : 1e-10);
        static constexpr int default_limit = 1000;

        virtual ~RootFinder() noexcept {}

        T solve(T y = 0, T x = 0) {
            auto r = do_solve(y, x, x + T(1));
            check();
            return r;
        }

        T solve(T y, T x1, T x2) {
            auto r = do_solve(y, x1, x2);
            check();
            return r;
        }

        T epsilon() const noexcept { return epsilon_; }
        void set_epsilon(T e) noexcept { epsilon_ = e; }
        int limit() const noexcept { return limit_; }
        void set_limit(int n) noexcept { limit_ = n; }
        T error() const noexcept { return error_; }
        int count() const noexcept { return count_; }

    protected:

        RootFinder() = default;

        virtual T do_solve(T y, T x1, T x2) = 0;
        void reset() noexcept { error_ = T{0}; count_ = 0; }
        void set_error(T err) noexcept { error_ = std::abs(err); }
        void increment() noexcept { ++count_; }

    private:

        T epsilon_ = default_epsilon;
        int limit_ = default_limit;
        T error_ = T{0};
        int count_ = 0;

        void check() const {
            if (count_ >= limit_ && error_ > epsilon_) {
                throw std::range_error("Root finder failed to converge");
            }
        }

    };

    // Bisection algorithm

    template <std::floating_point T, Endomorphism<T> F>
    class Bisection:
    public RootFinder<T> {

    public:

        explicit Bisection(F f): f_{f} {}

    protected:

        T do_solve(T y, T x1, T x2) override {

            this->reset();
            auto y1 = static_cast<T>(f_(x1)) - y;
            this->set_error(y1);

            if (this->error() <= this->epsilon()) {
                return x1;
            } else if (x1 == x2) {
                throw std::domain_error(std::format("Invalid arguments for bisection: {}, {}", x1, x2));
            }

            auto y2 = static_cast<T>(f_(x2)) - y;
            this->set_error(y2);

            if (this->error() <= this->epsilon()) {
                return x2;
            }

            auto s1 = std::signbit(y1);
            auto s2 = std::signbit(y2);

            if (s1 == s2) {
                throw std::domain_error(std::format("Invalid arguments for bisection: {}, {}", x1, x2));
            }

            while (this->count() < this->limit()) {

                this->increment();
                auto x3 = (x1 + x2) / T{2};
                auto y3 = static_cast<T>(f_(x3)) - y;
                this->set_error(y3);

                if (this->error() <= this->epsilon()) {
                    return x3;
                } else if (std::signbit(y3) == s1) {
                    x1 = x3;
                } else {
                    x2 = x3;
                }

            }

            return (x1 + x2) / T{2};

        }

    private:

        F f_;

    };

    template <std::floating_point T, Endomorphism<T> F>
    auto bisection(F f) {
        return Bisection<T, F>{f};
    }

    // FalsePosition algorithm

    template <std::floating_point T, Endomorphism<T> F>
    class FalsePosition:
    public RootFinder<T> {

    public:

        explicit FalsePosition(F f): f_{f} {}

    protected:

        T do_solve(T y, T x1, T x2) override {

            this->reset();
            auto y1 = static_cast<T>(f_(x1)) - y;
            this->set_error(y1);

            if (this->error() <= this->epsilon()) {
                return x1;
            } else if (x1 == x2) {
                throw std::domain_error(std::format("Invalid arguments for false position: {}, {}", x1, x2));
            }

            auto y2 = static_cast<T>(f_(x2)) - y;
            this->set_error(y2);

            if (this->error() <= this->epsilon()) {
                return x2;
            }

            auto s1 = std::signbit(y1);
            auto s2 = std::signbit(y2);

            if (s1 == s2) {
                throw std::domain_error(std::format("Invalid arguments for false position: {}, {}", x1, x2));
            }

            while (this->count() < this->limit()) {

                this->increment();
                auto x3 = x2 - y2 * (x2 - x1) / (y2 - y1);
                auto y3 = static_cast<T>(f_(x3)) - y;
                this->set_error(y3);

                if (this->error() <= this->epsilon()) {
                    return x3;
                } else if (std::signbit(y3) == s1) {
                    x1 = x3;
                } else {
                    x2 = x3;
                }

            }

            return (x1 + x2) / T{2};

        }

    private:

        F f_;

    };

    template <std::floating_point T, Endomorphism<T> F>
    auto false_position(F f) {
        return FalsePosition<T, F>{f};
    }

    // Newton-Raphson algorithm

    template <std::floating_point T, Endomorphism<T> F, Endomorphism<T> DF>
    class NewtonRaphson:
    public RootFinder<T> {

    public:

        NewtonRaphson(F f, DF df): f_{f}, df_{df} {}

    protected:

        T do_solve(T y, T x1, T /*x2*/) override {

            this->reset();

            while (this->count() < this->limit()) {

                this->increment();
                auto y1 = static_cast<T>(f_(x1)) - y;
                this->set_error(y1);

                if (this->error() <= this->epsilon()) {
                    break;
                }

                auto slope = this->df_(x1);

                if (slope == T{0}) {
                    x1 += T{100} * this->epsilon();
                } else {
                    x1 -= y1 / slope;
                }

            }

            return x1;

        }

    private:

        F f_;
        DF df_;

    };

    template <std::floating_point T, Endomorphism<T> F, Endomorphism<T> DF>
    auto newton_raphson(F f, DF df) {
        return NewtonRaphson<T, F, DF>{f, df};
    }

}
