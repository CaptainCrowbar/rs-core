#include "rs-core/random.hpp"
#include "rs-core/mp-integer.hpp"
#include "rs-core/unit-test.hpp"
#include <cmath>
#include <cstdint>
#include <random>
#include <unordered_map>

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
        BernoulliDistribution dist(3, 4);

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

        std::minstd_rand rng(42);
        UniformInteger<int> dist(10);

        TEST_EQUAL(dist.min(), 0);
        TEST_EQUAL(dist.max(), 9);
        TEST_EQUAL(dist.mean(), 4.5);
        TEST_NEAR(dist.sd(), 2.872281, 1e-6);

        std::unordered_map<int, int> census;
        int x{};

        for (auto i = 0; i < n; ++i) {
            TRY(x = dist(rng));
            TEST(x >= dist.min());
            TEST(x <= dist.max());
            ++census[x];
        }

        TEST_NEAR(census[0] / nx, 0.1, 0.01);
        TEST_NEAR(census[1] / nx, 0.1, 0.01);
        TEST_NEAR(census[2] / nx, 0.1, 0.01);
        TEST_NEAR(census[3] / nx, 0.1, 0.01);
        TEST_NEAR(census[4] / nx, 0.1, 0.01);
        TEST_NEAR(census[5] / nx, 0.1, 0.01);
        TEST_NEAR(census[6] / nx, 0.1, 0.01);
        TEST_NEAR(census[7] / nx, 0.1, 0.01);
        TEST_NEAR(census[8] / nx, 0.1, 0.01);
        TEST_NEAR(census[9] / nx, 0.1, 0.01);

    }

    {

        std::mt19937 rng(42);
        UniformInteger<int> dist(-5, 5);

        TEST_EQUAL(dist.min(), -5);
        TEST_EQUAL(dist.max(), 5);
        TEST_EQUAL(dist.mean(), 0);
        TEST_NEAR(dist.sd(), 3.162278, 1e-6);

        std::unordered_map<int, int> census;
        int x{};

        for (auto i = 0; i < n; ++i) {
            TRY(x = dist(rng));
            TEST(x >= dist.min());
            TEST(x <= dist.max());
            ++census[x];
        }

        TEST_NEAR(census[-5] / nx, 0.091, 0.01);
        TEST_NEAR(census[-4] / nx, 0.091, 0.01);
        TEST_NEAR(census[-3] / nx, 0.091, 0.01);
        TEST_NEAR(census[-2] / nx, 0.091, 0.01);
        TEST_NEAR(census[-1] / nx, 0.091, 0.01);
        TEST_NEAR(census[0] / nx, 0.091, 0.01);
        TEST_NEAR(census[1] / nx, 0.091, 0.01);
        TEST_NEAR(census[2] / nx, 0.091, 0.01);
        TEST_NEAR(census[3] / nx, 0.091, 0.01);
        TEST_NEAR(census[4] / nx, 0.091, 0.01);
        TEST_NEAR(census[5] / nx, 0.091, 0.01);

    }

    {

        Pcg rng(42);
        UniformInteger<int> dist(1, 100);

        TEST_EQUAL(dist.min(), 1);
        TEST_EQUAL(dist.max(), 100);
        TEST_EQUAL(dist.mean(), 50.5);
        TEST_NEAR(dist.sd(), 28.866070, 1e-6);

        auto tolerance = static_cast<double>(dist.max() - dist.min()) / std::sqrt(nx);
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

        TEST_NEAR(mean, dist.mean(), tolerance);
        TEST_NEAR(sd, dist.sd(), tolerance);

    }

    {

        Pcg rng(42);
        UniformInteger<int> dist(1000);

        TEST_EQUAL(dist.min(), 0);
        TEST_EQUAL(dist.max(), 999);
        TEST_EQUAL(dist.mean(), 499.5);
        TEST_NEAR(dist.sd(), 288.674990, 1e-6);

        auto tolerance = static_cast<double>(dist.max() - dist.min()) / std::sqrt(nx);
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

        TEST_NEAR(mean, dist.mean(), tolerance);
        TEST_NEAR(sd, dist.sd(), tolerance);

    }

    {

        Pcg rng(42);
        UniformInteger<std::int16_t> dist;

        TEST_EQUAL(dist.min(), 0);
        TEST_EQUAL(dist.max(), 32767);
        TEST_EQUAL(dist.mean(), 16383.5);
        TEST_NEAR(dist.sd(), 9459.306806, 1e-6);

        auto tolerance = static_cast<double>(dist.max() - dist.min()) / std::sqrt(nx);
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

        TEST_NEAR(mean, dist.mean(), tolerance);
        TEST_NEAR(sd, dist.sd(), tolerance);

    }

    {

        Pcg rng(42);
        UniformInteger<std::uint16_t> dist;

        TEST_EQUAL(dist.min(), 0u);
        TEST_EQUAL(dist.max(), 65535u);
        TEST_EQUAL(dist.mean(), 32767.5);
        TEST_NEAR(dist.sd(), 18918.613619, 1e-6);

        auto tolerance = static_cast<double>(dist.max() - dist.min()) / std::sqrt(nx);
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

        TEST_NEAR(mean, dist.mean(), tolerance);
        TEST_NEAR(sd, dist.sd(), tolerance);

    }

    {

        Pcg rng(42);
        UniformInteger<std::uint64_t> dist;

        TEST_EQUAL(dist.min(), 0u);
        TEST_EQUAL(dist.max(), 0xffff'ffff'ffff'ffffull);
        TEST_NEAR(dist.mean(), 9.22337e18, 1e13);
        TEST_NEAR(dist.sd(), 5.32512e18, 1e13);

        auto tolerance = static_cast<double>(dist.max() - dist.min()) / std::sqrt(nx);
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

        TEST_NEAR(mean, dist.mean(), tolerance);
        TEST_NEAR(sd, dist.sd(), tolerance);

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
        TEST_EQUAL(dist.mean(), 50.5);
        TEST_NEAR(dist.sd(), 28.866070, 1e-6);

        auto tolerance = static_cast<double>(dist.max() - dist.min()) / std::sqrt(nx);
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

        TEST_NEAR(mean, dist.mean(), tolerance);
        TEST_NEAR(sd, dist.sd(), tolerance);

    }

}
