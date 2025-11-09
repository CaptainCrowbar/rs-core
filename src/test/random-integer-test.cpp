#include "rs-core/random.hpp"
#include "rs-core/mp-integer.hpp"
#include "rs-core/unit-test.hpp"
#include <cmath>
#include <cstdint>
#include <format>
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

void test_rs_core_random_dice() {

    static constexpr auto n = 10'000;
    static constexpr auto nx = static_cast<double>(n);

    {

        std::minstd_rand rng(42);
        Dice<int> dist;

        TEST_EQUAL(dist.min(), 1);
        TEST_EQUAL(dist.max(), 6);
        TEST_EQUAL(dist.number(), 1);
        TEST_EQUAL(dist.faces(), 6);
        TEST_EQUAL(dist.str(), "1d6");
        TEST_EQUAL(std::format("{}", dist), "1d6");

        TEST_EQUAL(dist.pdf(0), 0);
        TEST_NEAR(dist.pdf(1), 0.166'667, 1e-6);
        TEST_NEAR(dist.pdf(2), 0.166'667, 1e-6);
        TEST_NEAR(dist.pdf(3), 0.166'667, 1e-6);
        TEST_NEAR(dist.pdf(4), 0.166'667, 1e-6);
        TEST_NEAR(dist.pdf(5), 0.166'667, 1e-6);
        TEST_NEAR(dist.pdf(6), 0.166'667, 1e-6);
        TEST_EQUAL(dist.pdf(7), 0);

        TEST_EQUAL(dist.cdf(0), 0);
        TEST_NEAR(dist.cdf(1), 0.166'667, 1e-6);
        TEST_NEAR(dist.cdf(2), 0.333'333, 1e-6);
        TEST_NEAR(dist.cdf(3), 0.500'000, 1e-6);
        TEST_NEAR(dist.cdf(4), 0.666'667, 1e-6);
        TEST_NEAR(dist.cdf(5), 0.833'333, 1e-6);
        TEST_EQUAL(dist.cdf(6), 1);
        TEST_EQUAL(dist.cdf(7), 1);

        TEST_EQUAL(dist.ccdf(0), 1);
        TEST_EQUAL(dist.ccdf(1), 1);
        TEST_NEAR(dist.ccdf(2), 0.833'333, 1e-6);
        TEST_NEAR(dist.ccdf(3), 0.666'667, 1e-6);
        TEST_NEAR(dist.ccdf(4), 0.500'000, 1e-6);
        TEST_NEAR(dist.ccdf(5), 0.333'333, 1e-6);
        TEST_NEAR(dist.ccdf(6), 0.166'667, 1e-6);
        TEST_EQUAL(dist.ccdf(7), 0);

        std::unordered_map<int, int> census;
        int x{};

        for (auto i = 0; i < n; ++i) {
            TRY(x = dist(rng));
            TEST(x >= dist.min());
            TEST(x <= dist.max());
            ++census[x];
        }

        TEST_NEAR(census[1] / nx, 0.1667, 0.01);
        TEST_NEAR(census[2] / nx, 0.1667, 0.01);
        TEST_NEAR(census[3] / nx, 0.1667, 0.01);
        TEST_NEAR(census[4] / nx, 0.1667, 0.01);
        TEST_NEAR(census[5] / nx, 0.1667, 0.01);
        TEST_NEAR(census[6] / nx, 0.1667, 0.01);

    }

    {

        std::minstd_rand rng(42);
        Dice<int> dist{3};

        TEST_EQUAL(dist.min(), 3);
        TEST_EQUAL(dist.max(), 18);
        TEST_EQUAL(dist.number(), 3);
        TEST_EQUAL(dist.faces(), 6);
        TEST_EQUAL(dist.str(), "3d6");
        TEST_EQUAL(std::format("{}", dist), "3d6");

        TEST_EQUAL(dist.pdf(2), 0);
        TEST_NEAR(dist.pdf(3), 0.004'630, 1e-6);
        TEST_NEAR(dist.pdf(4), 0.013'889, 1e-6);
        TEST_NEAR(dist.pdf(5), 0.027'778, 1e-6);
        TEST_NEAR(dist.pdf(6), 0.046'296, 1e-6);
        TEST_NEAR(dist.pdf(7), 0.069'444, 1e-6);
        TEST_NEAR(dist.pdf(8), 0.097'222, 1e-6);
        TEST_NEAR(dist.pdf(9), 0.115'741, 1e-6);
        TEST_NEAR(dist.pdf(10), 0.125'000, 1e-6);
        TEST_NEAR(dist.pdf(11), 0.125'000, 1e-6);
        TEST_NEAR(dist.pdf(12), 0.115'741, 1e-6);
        TEST_NEAR(dist.pdf(13), 0.097'222, 1e-6);
        TEST_NEAR(dist.pdf(14), 0.069'444, 1e-6);
        TEST_NEAR(dist.pdf(15), 0.046'296, 1e-6);
        TEST_NEAR(dist.pdf(16), 0.027'778, 1e-6);
        TEST_NEAR(dist.pdf(17), 0.013'889, 1e-6);
        TEST_NEAR(dist.pdf(18), 0.004'630, 1e-6);
        TEST_EQUAL(dist.pdf(19), 0);

        TEST_EQUAL(dist.cdf(2), 0);
        TEST_NEAR(dist.cdf(3), 0.004'630, 1e-6);
        TEST_NEAR(dist.cdf(4), 0.018'519, 1e-6);
        TEST_NEAR(dist.cdf(5), 0.046'296, 1e-6);
        TEST_NEAR(dist.cdf(6), 0.092'593, 1e-6);
        TEST_NEAR(dist.cdf(7), 0.162'037, 1e-6);
        TEST_NEAR(dist.cdf(8), 0.259'259, 1e-6);
        TEST_NEAR(dist.cdf(9), 0.375'000, 1e-6);
        TEST_NEAR(dist.cdf(10), 0.500'000, 1e-6);
        TEST_NEAR(dist.cdf(11), 0.625'000, 1e-6);
        TEST_NEAR(dist.cdf(12), 0.740'741, 1e-6);
        TEST_NEAR(dist.cdf(13), 0.837'963, 1e-6);
        TEST_NEAR(dist.cdf(14), 0.907'407, 1e-6);
        TEST_NEAR(dist.cdf(15), 0.953'704, 1e-6);
        TEST_NEAR(dist.cdf(16), 0.981'481, 1e-6);
        TEST_NEAR(dist.cdf(17), 0.995'370, 1e-6);
        TEST_EQUAL(dist.cdf(18), 1);
        TEST_EQUAL(dist.cdf(19), 1);

        TEST_EQUAL(dist.ccdf(2), 1);
        TEST_EQUAL(dist.ccdf(3), 1);
        TEST_NEAR(dist.ccdf(4), 0.995'370, 1e-6);
        TEST_NEAR(dist.ccdf(5), 0.981'481, 1e-6);
        TEST_NEAR(dist.ccdf(6), 0.953'704, 1e-6);
        TEST_NEAR(dist.ccdf(7), 0.907'407, 1e-6);
        TEST_NEAR(dist.ccdf(8), 0.837'963, 1e-6);
        TEST_NEAR(dist.ccdf(9), 0.740'741, 1e-6);
        TEST_NEAR(dist.ccdf(10), 0.625'000, 1e-6);
        TEST_NEAR(dist.ccdf(11), 0.500'000, 1e-6);
        TEST_NEAR(dist.ccdf(12), 0.375'000, 1e-6);
        TEST_NEAR(dist.ccdf(13), 0.259'259, 1e-6);
        TEST_NEAR(dist.ccdf(14), 0.162'037, 1e-6);
        TEST_NEAR(dist.ccdf(15), 0.092'593, 1e-6);
        TEST_NEAR(dist.ccdf(16), 0.046'296, 1e-6);
        TEST_NEAR(dist.ccdf(17), 0.018'519, 1e-6);
        TEST_NEAR(dist.ccdf(18), 0.004'630, 1e-6);
        TEST_EQUAL(dist.ccdf(19), 0);

        int x{};
        double dx{};
        double sum{};
        double sum2{};

        for (auto i = 0; i < n; ++i) {
            TRY(x = dist(rng));
            TEST(x >= dist.min());
            TEST(x <= dist.max());
            dx = static_cast<double>(x);
            sum += dx;
            sum2 += dx * dx;
        }

        auto mean = sum / nx;
        auto sd = std::sqrt((nx / (nx - 1.0)) * (sum2 / nx - mean * mean));

        TEST_NEAR(mean, 10.5, 0.1);
        TEST_NEAR(sd, 2.9580, 0.1);

    }

    {

        std::minstd_rand rng(42);
        Dice<int> dist{2, 100};

        TEST_EQUAL(dist.min(), 2);
        TEST_EQUAL(dist.max(), 200);
        TEST_EQUAL(dist.number(), 2);
        TEST_EQUAL(dist.faces(), 100);
        TEST_EQUAL(dist.str(), "2d100");
        TEST_EQUAL(std::format("{}", dist), "2d100");

        int x{};
        double dx{};
        double sum{};
        double sum2{};

        for (auto i = 0; i < n; ++i) {
            TRY(x = dist(rng));
            TEST(x >= dist.min());
            TEST(x <= dist.max());
            dx = static_cast<double>(x);
            sum += dx;
            sum2 += dx * dx;
        }

        auto mean = sum / nx;
        auto sd = std::sqrt((nx / (nx - 1.0)) * (sum2 / nx - mean * mean));

        TEST_NEAR(mean, 101, 1);
        TEST_NEAR(sd, 40.8228, 1);

    }

}
