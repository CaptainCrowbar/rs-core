#include "rs-core/random.hpp"
#include "rs-core/mp-integer.hpp"
#include "rs-core/unit-test.hpp"
#include <cmath>
#include <cstdint>

using namespace RS;

void test_rs_core_random_bernoulli_distribution() {

    static constexpr auto n = 10'000;
    static constexpr auto nx = static_cast<double>(n);
    static const auto tolerance = std::sqrt(nx);

    {

        Pcg rng(42);
        BernoulliDistribution dist;

        auto count = 0.0;
        auto expect = 0.5 * nx;
        bool x{};

        for (auto i = 0; i < n; ++i) {
            TRY(x = dist(rng));
            if (x) {
                count += 1.0;
            }
        }

        TEST_NEAR(count, expect, tolerance);

    }

    {

        Pcg rng(42);
        BernoulliDistribution dist(0.25);

        auto count = 0.0;
        auto expect = 0.25 * nx;
        bool x{};

        for (auto i = 0; i < n; ++i) {
            TRY(x = dist(rng));
            if (x) {
                count += 1.0;
            }
        }

        TEST_NEAR(count, expect, tolerance);

    }

    {

        Pcg rng(42);
        BernoulliDistribution dist(300, 400);

        auto count = 0.0;
        auto expect = 0.75 * nx;
        bool x{};

        for (auto i = 0; i < n; ++i) {
            TRY(x = dist(rng));
            if (x) {
                count += 1.0;
            }
        }

        TEST_NEAR(count, expect, tolerance);

    }

}

void test_rs_core_random_uniform_integer() {

    static constexpr auto n = 10'000;
    static constexpr auto nx = static_cast<double>(n);

    {

        Pcg rng(42);
        UniformInteger<int> dist(1, 100);

        TEST_EQUAL(dist.min(), 1);
        TEST_EQUAL(dist.max(), 100);

        auto xmin = static_cast<double>(dist.min());
        auto xmax = static_cast<double>(dist.max());
        auto expect_mean = 0.5 * (xmin + xmax);
        auto expect_sd = (xmax - xmin + 1.0) / std::sqrt(12.0);
        auto tolerance = (xmax - xmin) / std::sqrt(nx);
        auto sum = 0.0;
        auto sum2 = 0.0;
        int x{};

        for (auto i = 0; i < n; ++i) {
            TRY(x = dist(rng));
            TEST(x >= dist.min());
            TEST(x <= dist.max());
            auto y = static_cast<double>(x);
            sum += y;
            sum2 += y * y;
        }

        auto mean = sum / nx;
        auto sd = std::sqrt((nx / (nx - 1.0)) * (sum2 / nx - mean * mean));

        TEST_NEAR(mean, expect_mean, tolerance);
        TEST_NEAR(sd, expect_sd, tolerance);

    }

    {

        Pcg rng(42);
        UniformInteger<int> dist(1000);

        TEST_EQUAL(dist.min(), 0);
        TEST_EQUAL(dist.max(), 999);

        auto xmin = static_cast<double>(dist.min());
        auto xmax = static_cast<double>(dist.max());
        auto expect_mean = 0.5 * (xmin + xmax);
        auto expect_sd = (xmax - xmin + 1.0) / std::sqrt(12.0);
        auto tolerance = (xmax - xmin) / std::sqrt(nx);
        auto sum = 0.0;
        auto sum2 = 0.0;
        int x{};

        for (auto i = 0; i < n; ++i) {
            TRY(x = dist(rng));
            TEST(x >= dist.min());
            TEST(x <= dist.max());
            auto y = static_cast<double>(x);
            sum += y;
            sum2 += y * y;
        }

        auto mean = sum / nx;
        auto sd = std::sqrt((nx / (nx - 1.0)) * (sum2 / nx - mean * mean));

        TEST_NEAR(mean, expect_mean, tolerance);
        TEST_NEAR(sd, expect_sd, tolerance);

    }

    {

        Pcg rng(42);
        UniformInteger<std::int16_t> dist;

        TEST_EQUAL(dist.min(), 0);
        TEST_EQUAL(dist.max(), 32767);

        auto xmin = static_cast<double>(dist.min());
        auto xmax = static_cast<double>(dist.max());
        auto expect_mean = 0.5 * (xmin + xmax);
        auto expect_sd = (xmax - xmin + 1.0) / std::sqrt(12.0);
        auto tolerance = (xmax - xmin) / std::sqrt(nx);
        auto sum = 0.0;
        auto sum2 = 0.0;
        std::int16_t x{};

        for (auto i = 0; i < n; ++i) {
            TRY(x = dist(rng));
            TEST(x >= dist.min());
            TEST(x <= dist.max());
            auto y = static_cast<double>(x);
            sum += y;
            sum2 += y * y;
        }

        auto mean = sum / nx;
        auto sd = std::sqrt((nx / (nx - 1.0)) * (sum2 / nx - mean * mean));

        TEST_NEAR(mean, expect_mean, tolerance);
        TEST_NEAR(sd, expect_sd, tolerance);

    }

    {

        Pcg rng(42);
        UniformInteger<std::uint16_t> dist;

        TEST_EQUAL(dist.min(), 0u);
        TEST_EQUAL(dist.max(), 65535u);

        auto xmin = static_cast<double>(dist.min());
        auto xmax = static_cast<double>(dist.max());
        auto expect_mean = 0.5 * (xmin + xmax);
        auto expect_sd = (xmax - xmin + 1.0) / std::sqrt(12.0);
        auto tolerance = (xmax - xmin) / std::sqrt(nx);
        auto sum = 0.0;
        auto sum2 = 0.0;
        std::uint16_t x{};

        for (auto i = 0; i < n; ++i) {
            TRY(x = dist(rng));
            TEST(x >= dist.min());
            TEST(x <= dist.max());
            auto y = static_cast<double>(x);
            sum += y;
            sum2 += y * y;
        }

        auto mean = sum / nx;
        auto sd = std::sqrt((nx / (nx - 1.0)) * (sum2 / nx - mean * mean));

        TEST_NEAR(mean, expect_mean, tolerance);
        TEST_NEAR(sd, expect_sd, tolerance);

    }

    {

        Pcg rng(42);
        UniformInteger<std::uint64_t> dist;

        TEST_EQUAL(dist.min(), 0u);
        TEST_EQUAL(dist.max(), 0xffff'ffff'ffff'ffffull);

        auto xmin = static_cast<double>(dist.min());
        auto xmax = static_cast<double>(dist.max());
        auto expect_mean = 0.5 * (xmin + xmax);
        auto expect_sd = (xmax - xmin + 1.0) / std::sqrt(12.0);
        auto tolerance = (xmax - xmin) / std::sqrt(nx);
        auto sum = 0.0;
        auto sum2 = 0.0;
        std::uint64_t x{};

        for (auto i = 0; i < n; ++i) {
            TRY(x = dist(rng));
            TEST(x >= dist.min());
            TEST(x <= dist.max());
            auto y = static_cast<double>(x);
            sum += y;
            sum2 += y * y;
        }

        auto mean = sum / nx;
        auto sd = std::sqrt((nx / (nx - 1.0)) * (sum2 / nx - mean * mean));

        TEST_NEAR(mean, expect_mean, tolerance);
        TEST_NEAR(sd, expect_sd, tolerance);

    }

}

void test_rs_core_random_uniform_mp_integer() {

    static constexpr auto n = 1000;
    static constexpr auto nx = static_cast<double>(n);

    {

        Pcg rng(42);
        UniformInteger<Integer> dist(1, 100);

        TEST_EQUAL(dist.min(), 1);
        TEST_EQUAL(dist.max(), 100);

        auto xmin = static_cast<double>(dist.min());
        auto xmax = static_cast<double>(dist.max());
        auto expect_mean = 0.5 * (xmin + xmax);
        auto expect_sd = (xmax - xmin + 1.0) / std::sqrt(12.0);
        auto tolerance = (xmax - xmin) / std::sqrt(nx);
        auto sum = 0.0;
        auto sum2 = 0.0;
        Integer x{};

        for (auto i = 0; i < n; ++i) {
            TRY(x = dist(rng));
            TEST(x >= dist.min());
            TEST(x <= dist.max());
            auto y = static_cast<double>(x);
            sum += y;
            sum2 += y * y;
        }

        auto mean = sum / nx;
        auto sd = std::sqrt((nx / (nx - 1.0)) * (sum2 / nx - mean * mean));

        TEST_NEAR(mean, expect_mean, tolerance);
        TEST_NEAR(sd, expect_sd, tolerance);

    }

}

void test_rs_core_random_quick_integer() {

    static constexpr auto n = 1000;
    static constexpr auto nx = static_cast<double>(n);

    {

        Pcg rng(42);
        QuickRandom<int> dist(1, 100);

        TEST_EQUAL(dist.min(), 1);
        TEST_EQUAL(dist.max(), 100);

        auto xmin = static_cast<double>(dist.min());
        auto xmax = static_cast<double>(dist.max());
        auto expect_mean = 0.5 * (xmin + xmax);
        auto expect_sd = (xmax - xmin + 1.0) / std::sqrt(12.0);
        auto tolerance = (xmax - xmin) / std::sqrt(nx);
        auto sum = 0.0;
        auto sum2 = 0.0;
        int x{};

        for (auto i = 0; i < n; ++i) {
            TRY(x = dist(rng));
            TEST(x >= dist.min());
            TEST(x <= dist.max());
            auto y = static_cast<double>(x);
            sum += y;
            sum2 += y * y;
        }

        auto mean = sum / nx;
        auto sd = std::sqrt((nx / (nx - 1.0)) * (sum2 / nx - mean * mean));

        TEST_NEAR(mean, expect_mean, tolerance);
        TEST_NEAR(sd, expect_sd, tolerance);

    }

}
