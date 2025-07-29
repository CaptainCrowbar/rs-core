#include "rs-core/random.hpp"
#include "rs-core/unit-test.hpp"
#include <cmath>

using namespace RS;

void test_rs_core_random_uniform_real() {

    static constexpr auto n = 10'000;
    static constexpr auto nx = static_cast<double>(n);

    {

        Pcg rng(42);
        UniformReal<double> dist;

        TEST_EQUAL(dist.min(), 0.0);
        TEST_EQUAL(dist.max(), 1.0);

        auto expect_mean = 0.5 * (dist.min() + dist.max());
        auto expect_sd = (dist.max() - dist.min()) / std::sqrt(12.0);
        auto tolerance = (dist.max() - dist.min()) / std::sqrt(nx);
        auto sum = 0.0;
        auto sum2 = 0.0;
        double x{};

        for (auto i = 0; i < n; ++i) {
            TRY(x = dist(rng));
            TEST(x >= dist.min());
            TEST(x <= dist.max());
            sum += x;
            sum2 += x * x;
        }

        auto mean = sum / nx;
        auto sd = std::sqrt((nx / (nx - 1.0)) * (sum2 / nx - mean * mean));

        TEST_NEAR(mean, expect_mean, tolerance);
        TEST_NEAR(sd, expect_sd, tolerance);

    }

    {

        Pcg rng(42);
        UniformReal<double> dist(10.0);

        TEST_EQUAL(dist.min(), 0.0);
        TEST_EQUAL(dist.max(), 10.0);

        auto expect_mean = 0.5 * (dist.min() + dist.max());
        auto expect_sd = (dist.max() - dist.min()) / std::sqrt(12.0);
        auto tolerance = (dist.max() - dist.min()) / std::sqrt(nx);
        auto sum = 0.0;
        auto sum2 = 0.0;
        double x{};

        for (auto i = 0; i < n; ++i) {
            TRY(x = dist(rng));
            TEST(x >= dist.min());
            TEST(x <= dist.max());
            sum += x;
            sum2 += x * x;
        }

        auto mean = sum / nx;
        auto sd = std::sqrt((nx / (nx - 1.0)) * (sum2 / nx - mean * mean));

        TEST_NEAR(mean, expect_mean, tolerance);
        TEST_NEAR(sd, expect_sd, tolerance);

    }

    {

        Pcg rng(42);
        UniformReal<double> dist(100.0, -100.0);

        TEST_EQUAL(dist.min(), -100.0);
        TEST_EQUAL(dist.max(), 100.0);

        auto expect_mean = 0.5 * (dist.min() + dist.max());
        auto expect_sd = (dist.max() - dist.min()) / std::sqrt(12.0);
        auto tolerance = (dist.max() - dist.min()) / std::sqrt(nx);
        auto sum = 0.0;
        auto sum2 = 0.0;
        double x{};

        for (auto i = 0; i < n; ++i) {
            TRY(x = dist(rng));
            TEST(x >= dist.min());
            TEST(x <= dist.max());
            sum += x;
            sum2 += x * x;
        }

        auto mean = sum / nx;
        auto sd = std::sqrt((nx / (nx - 1.0)) * (sum2 / nx - mean * mean));

        TEST_NEAR(mean, expect_mean, tolerance);
        TEST_NEAR(sd, expect_sd, tolerance);

    }

}
