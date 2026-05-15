#include "rs-core/random.hpp"
#include "rs-core/linear-algebra.hpp"
#include "rs-core/unit-test.hpp"
#include <cmath>
#include <concepts>
#include <cstddef>
#include <print>
#include <random>

using namespace RS;

namespace {

    template <std::floating_point T, std::size_t N>
    void spherical_surface_test() {

        // std::println("{}", N);

        static constexpr auto iterations = 10'000uz;

        SphericalSurfaceDistribution<T, N> gen {10};
        std::minstd_rand rng {42};
        Vector<T, N> count_positive, point, total;

        for (auto i = 0uz; i < iterations; ++i) {
            TRY(point = gen(rng));
            TEST_NEAR(point.r(), 10, 1e-5);
            for (auto j = 0uz; j < N; ++j) {
                if (point[j] > 0) {
                    ++count_positive[j];
                }
            }
            total += point;
        }

        auto epsilon = T{20} / std::sqrt(static_cast<T>(iterations));

        for (auto& c: count_positive) {
            c /= static_cast<T>(iterations);
            TEST_NEAR(c, 0.5, epsilon);
        }

        total /= static_cast<T>(iterations);
        TEST_NEAR(total.r(), 0, 2 * epsilon); // more variance in surface points

    }

    template <std::floating_point T, std::size_t N>
    void spherical_volume_test() {

        // std::println("{}", N);

        static constexpr auto iterations = 10'000uz;

        SphericalVolumeDistribution<T, N> gen {10};
        std::minstd_rand rng {42};
        Vector<T, N> count_positive, point, total;
        T count_inner {0};

        for (auto i = 0uz; i < iterations; ++i) {
            TRY(point = gen(rng));
            for (auto j = 0uz; j < N; ++j) {
                if (point[j] > 0) {
                    ++count_positive[j];
                }
            }
            if (point.r() < T{5}) {
                ++count_inner;
            }
            total += point;
        }

        auto epsilon = T{20} / std::sqrt(static_cast<T>(iterations));
        auto expect_inner = std::pow(T{2}, - T{N});

        for (auto& c: count_positive) {
            c /= static_cast<T>(iterations);
            TEST_NEAR(c, 0.5, epsilon);
        }

        total /= iterations;
        count_inner /= static_cast<T>(iterations);
        TEST_NEAR(total.r(), 0, epsilon);
        TEST_NEAR(count_inner, expect_inner, epsilon);

    }

}

void test_rs_core_random_spherical_surface_distribution() {

    spherical_surface_test<float, 1>();
    spherical_surface_test<float, 2>();
    spherical_surface_test<float, 3>();
    spherical_surface_test<float, 4>();
    spherical_surface_test<float, 5>();
    spherical_surface_test<float, 6>();
    spherical_surface_test<float, 7>();
    spherical_surface_test<float, 8>();
    spherical_surface_test<float, 9>();
    spherical_surface_test<float, 10>();

    spherical_surface_test<double, 1>();
    spherical_surface_test<double, 2>();
    spherical_surface_test<double, 3>();
    spherical_surface_test<double, 4>();
    spherical_surface_test<double, 5>();
    spherical_surface_test<double, 6>();
    spherical_surface_test<double, 7>();
    spherical_surface_test<double, 8>();
    spherical_surface_test<double, 9>();
    spherical_surface_test<double, 10>();

}

void test_rs_core_random_spherical_volume_distribution() {

    spherical_volume_test<float, 1>();
    spherical_volume_test<float, 2>();
    spherical_volume_test<float, 3>();
    spherical_volume_test<float, 4>();
    spherical_volume_test<float, 5>();
    spherical_volume_test<float, 6>();
    spherical_volume_test<float, 7>();
    spherical_volume_test<float, 8>();
    spherical_volume_test<float, 9>();
    spherical_volume_test<float, 10>();

    spherical_volume_test<double, 1>();
    spherical_volume_test<double, 2>();
    spherical_volume_test<double, 3>();
    spherical_volume_test<double, 4>();
    spherical_volume_test<double, 5>();
    spherical_volume_test<double, 6>();
    spherical_volume_test<double, 7>();
    spherical_volume_test<double, 8>();
    spherical_volume_test<double, 9>();
    spherical_volume_test<double, 10>();

}
