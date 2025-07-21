#include "rs-core/random.hpp"
#include "rs-core/unit-test.hpp"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <map>
#include <ranges>
#include <string>
#include <vector>

using namespace RS;

void test_rs_core_random_pcg_engine() {

    static const std::vector<std::uint64_t> expect = {
        0xa9b6'7185'2137'230bull,  0xb3cc'f402'a218'bf42ull,  0x8899'5fef'06e8'7299ull,  0xf297'6e1c'e9c8'fb39ull,
        0xb6ac'2dd4'b8b9'fc7full,  0x93e2'281f'6f03'230dull,  0xdbfd'17dc'c4ae'5577ull,  0x7422'bd2e'34b0'57d4ull,
        0x7a7c'fcf6'f879'80f2ull,  0x0f50'0975'3260'8022ull,  0xb988'c173'a88d'e4f0ull,  0x6fa9'dbc7'8193'9228ull,
        0xfcca'3e1f'd78f'db49ull,  0xf057'dd1c'fe29'cf46ull,  0x7e66'83c0'b4d7'125full,  0xbd9d'3f2d'ec76'80dcull,
        0x6706'6d0b'a710'6e90ull,  0xbfab'7e31'd261'7209ull,  0x30c9'8bb6'73a5'946dull,  0xc1f4'4b6d'660b'793dull,
        0x5456'030f'5eec'32d8ull,  0x9e15'd122'51a2'8be7ull,  0x8f45'a928'e8f3'4d0full,  0xcb14'bc52'8a16'5c25ull,
        0xb611'0438'5fcd'f646ull,  0xf912'e066'96dc'85c5ull,  0x57c5'112b'e759'5b98ull,  0x9a91'97a0'c3a3'aee9ull,
        0xd488'66ed'cca8'6cf7ull,  0x1857'32ad'174d'f42cull,  0xd675'1d3c'5708'07baull,  0xa056'25a6'ab29'71f3ull,
        0x8f60'3032'7a8d'10a1ull,  0x3e3c'3e5f'ecbc'dd1full,  0xb20e'8430'0c2d'c089ull,  0x570b'ec77'b7e5'6f00ull,
        0xb8a1'aa82'291b'f578ull,  0x4711'aa73'e274'd048ull,  0x6dd7'b147'1092'0764ull,  0x4662'f657'11cb'd5b5ull,
        0xc6af'd76c'bfd0'8e66ull,  0x62a8'23ad'4155'b3c5ull,  0x5435'd547'7150'f2edull,  0x6a94'45a0'bc2d'2f80ull,
        0x085d'cfb8'ad4f'a6dcull,  0xac49'def8'215a'59cdull,  0xce0d'12e5'4bf1'1d13ull,  0x3da0'd750'b62d'774eull,
        0xb009'de26'0e56'ce20ull,  0x1cc9'120b'b184'ebc2ull,  0xe3c9'd45b'1b73'bbd9ull,  0x6c48'6cb5'c9bb'fe68ull,
        0x67cc'26e6'7265'f44full,  0xde5f'f5de'4a74'4606ull,  0xe504'129b'f47b'034aull,  0xa3ec'e980'9f89'80a9ull,
        0x1b06'c26a'aa40'2c9aull,  0x5cd5'9ba4'19ba'd600ull,  0x0e06'199a'7610'7cbeull,  0xc40f'500f'5ef1'8cf7ull,
        0x6d64'86e6'1f00'9646ull,  0x3223'376c'4205'08c5ull,  0x4a31'5330'afd4'6867ull,  0x023c'72db'b1fe'94f1ull,
    };

    Pcg rng;
    std::uint64_t x = 0;

    for (auto y: expect) {
        TRY(x = rng());
        TEST_EQUAL(x, y);
    }

}

void test_rs_core_random_device_64_engine() {

    static constexpr auto n = 10'000;
    static constexpr auto nx = static_cast<double>(n);
    static const auto range = std::ldexp(1.0, 64);
    static const auto expect_mean = 0.5 * range;
    static const auto expect_sd = (range + 1.0) / std::sqrt(12.0);
    static const auto tolerance = range / std::sqrt(nx);

    RandomDevice64 rng;
    auto sum = 0.0;
    auto sum2 = 0.0;
    std::uint64_t x{};

    for (auto i = 0; i < n; ++i) {
        TRY(x = rng());
        auto y = static_cast<double>(x);
        sum += y;
        sum2 += y * y;
    }

    auto mean = sum / nx;
    auto sd = std::sqrt((nx / (nx - 1.0)) * (sum2 / nx - mean * mean));

    TEST_NEAR(mean, expect_mean, tolerance);
    TEST_NEAR(sd, expect_sd, tolerance);

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

void test_rs_core_random_choice() {

    static constexpr auto iterations = 10'000;
    static constexpr auto total = static_cast<double>(iterations);

    {

        RandomChoice<std::string> choice;
        Pcg rng(42);
        std::map<std::string, int> census;
        std::string s;

        TRY(choice.insert("Alpha"));
        TRY(choice.insert("Bravo"));
        TRY(choice.insert("Charlie"));
        TRY(choice.insert("Delta"));
        TRY(choice.insert("Echo"));

        for (auto i = 0; i < iterations; ++i) {
            TRY(s = choice(rng));
            TEST_MATCH(s, "^[A-E][a-z]+$");
            ++census[s];
        }

        TEST_NEAR(census["Alpha"] / total,    0.2, 0.01);
        TEST_NEAR(census["Bravo"] / total,    0.2, 0.01);
        TEST_NEAR(census["Charlie"] / total,  0.2, 0.01);
        TEST_NEAR(census["Delta"] / total,    0.2, 0.01);
        TEST_NEAR(census["Echo"] / total,     0.2, 0.01);

    }

    {

        std::vector<std::string> vec {
            "Alpha",
            "Bravo",
            "Charlie",
            "Delta",
            "Echo",
        };

        RandomChoice<std::string> choice{vec};
        Pcg rng(42);
        std::map<std::string, int> census;
        std::string s;

        for (auto i = 0; i < iterations; ++i) {
            TRY(s = choice(rng));
            TEST_MATCH(s, "^[A-E][a-z]+$");
            ++census[s];
        }

        TEST_NEAR(census["Alpha"] / total,    0.2, 0.01);
        TEST_NEAR(census["Bravo"] / total,    0.2, 0.01);
        TEST_NEAR(census["Charlie"] / total,  0.2, 0.01);
        TEST_NEAR(census["Delta"] / total,    0.2, 0.01);
        TEST_NEAR(census["Echo"] / total,     0.2, 0.01);

    }

    {

        RandomChoice<std::string> choice {
            "Alpha",
            "Bravo",
            "Charlie",
            "Delta",
            "Echo",
        };

        Pcg rng(42);
        std::map<std::string, int> census;
        std::string s;

        for (auto i = 0; i < iterations; ++i) {
            TRY(s = choice(rng));
            TEST_MATCH(s, "^[A-E][a-z]+$");
            ++census[s];
        }

        TEST_NEAR(census["Alpha"] / total,    0.2, 0.01);
        TEST_NEAR(census["Bravo"] / total,    0.2, 0.01);
        TEST_NEAR(census["Charlie"] / total,  0.2, 0.01);
        TEST_NEAR(census["Delta"] / total,    0.2, 0.01);
        TEST_NEAR(census["Echo"] / total,     0.2, 0.01);

    }

}

void test_rs_core_random_weighted_choice() {

    static constexpr auto iterations = 10'000;
    static constexpr auto total = static_cast<double>(iterations);

    {

        WeightedChoice<std::string> choice;
        Pcg rng(42);
        std::map<std::string, int> census;
        std::string s;

        TRY(choice.insert("Alpha",    10));
        TRY(choice.insert("Bravo",    20));
        TRY(choice.insert("Charlie",  30));
        TRY(choice.insert("Delta",    40));

        for (auto i = 0; i < iterations; ++i) {
            TRY(s = choice(rng));
            TEST_MATCH(s, "^[A-E][a-z]+$");
            ++census[s];
        }

        TEST_NEAR(census["Alpha"] / total,    0.1, 0.01);
        TEST_NEAR(census["Bravo"] / total,    0.2, 0.01);
        TEST_NEAR(census["Charlie"] / total,  0.3, 0.01);
        TEST_NEAR(census["Delta"] / total,    0.4, 0.01);

    }

    {

        WeightedChoice<std::string> choice {
            {"Alpha",    10},
            {"Bravo",    20},
            {"Charlie",  30},
            {"Delta",    40},
        };

        Pcg rng(42);
        std::map<std::string, int> census;
        std::string s;

        for (auto i = 0; i < iterations; ++i) {
            TRY(s = choice(rng));
            TEST_MATCH(s, "^[A-E][a-z]+$");
            ++census[s];
        }

        TEST_NEAR(census["Alpha"] / total,    0.1, 0.01);
        TEST_NEAR(census["Bravo"] / total,    0.2, 0.01);
        TEST_NEAR(census["Charlie"] / total,  0.3, 0.01);
        TEST_NEAR(census["Delta"] / total,    0.4, 0.01);

    }

    {

        WeightedChoice<std::string, double> choice;
        Pcg rng(42);
        std::map<std::string, int> census;
        std::string s;

        TRY(choice.insert("Alpha",    0.01));
        TRY(choice.insert("Bravo",    0.02));
        TRY(choice.insert("Charlie",  0.03));
        TRY(choice.insert("Delta",    0.04));

        for (auto i = 0; i < iterations; ++i) {
            TRY(s = choice(rng));
            TEST_MATCH(s, "^[A-E][a-z]+$");
            ++census[s];
        }

        TEST_NEAR(census["Alpha"] / total,    0.1, 0.01);
        TEST_NEAR(census["Bravo"] / total,    0.2, 0.01);
        TEST_NEAR(census["Charlie"] / total,  0.3, 0.01);
        TEST_NEAR(census["Delta"] / total,    0.4, 0.01);

    }

    {

        WeightedChoice<std::string, double> choice {
            {"Alpha",    0.01},
            {"Bravo",    0.02},
            {"Charlie",  0.03},
            {"Delta",    0.04},
        };

        Pcg rng(42);
        std::map<std::string, int> census;
        std::string s;

        for (auto i = 0; i < iterations; ++i) {
            TRY(s = choice(rng));
            TEST_MATCH(s, "^[A-E][a-z]+$");
            ++census[s];
        }

        TEST_NEAR(census["Alpha"] / total,    0.1, 0.01);
        TEST_NEAR(census["Bravo"] / total,    0.2, 0.01);
        TEST_NEAR(census["Charlie"] / total,  0.3, 0.01);
        TEST_NEAR(census["Delta"] / total,    0.4, 0.01);

    }

}

void test_rs_core_random_shuffle() {

    static constexpr auto iterations = 10'000;

    std::string s = "abcdefghij";
    Pcg rng(42);

    for (auto i = 0; i < iterations; ++i) {
        auto t = s;
        TRY(shuffle(t, rng));
        TEST(t != s);
        TEST_EQUAL(t.size(), s.size());
        std::ranges::sort(t);
        TEST_EQUAL(t, s);
    }

}
