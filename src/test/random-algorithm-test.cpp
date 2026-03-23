#include "rs-core/random.hpp"
#include "rs-core/enum.hpp"
#include "rs-core/unit-test.hpp"
#include <algorithm>
#include <map>
#include <random>
#include <ranges>
#include <string>

using namespace RS;

namespace {

    RS_BITMASK(Mask, unsigned,
        alpha    = 1,
        bravo    = 2,
        charlie  = 4,
    )

}

void test_rs_core_random_bit() {

    static constexpr auto iterations = 10'000;
    static constexpr auto total = static_cast<double>(iterations);

    {

        std::minstd_rand rng(42);
        int n;

        for (auto i = 0; i < iterations; ++i) {
            TRY(n = random_bit(4, rng));
            TEST_EQUAL(n, 4);
        }

    }

    {

        std::minstd_rand rng(42);
        std::map<int, int> census;
        int n;

        for (auto i = 0; i < iterations; ++i) {
            TRY((n = random_bit(3, rng)));
            TEST(n == 1 || n == 2);
            ++census[n];
        }

        TEST_NEAR(census[1] / total, 0.5, 0.01);
        TEST_NEAR(census[2] / total, 0.5, 0.01);

    }

    {

        std::minstd_rand rng(42);
        std::map<int, int> census;
        int n;

        for (auto i = 0; i < iterations; ++i) {
            TRY((n = random_bit(7, rng)));
            TEST(n == 1 || n == 2 || n == 4);
            ++census[n];
        }

        TEST_NEAR(census[1] / total, 0.33, 0.01);
        TEST_NEAR(census[2] / total, 0.33, 0.01);
        TEST_NEAR(census[4] / total, 0.33, 0.01);

    }

    {

        std::minstd_rand rng(42);
        Mask m;

        for (auto i = 0; i < iterations; ++i) {
            TRY(m = random_bit(Mask::charlie, rng));
            TEST_EQUAL(m, Mask::charlie);
        }

    }

    {

        std::minstd_rand rng(42);
        std::map<Mask, int> census;
        Mask m;

        for (auto i = 0; i < iterations; ++i) {
            TRY((m = random_bit(Mask::alpha | Mask::bravo, rng)));
            TEST(m == Mask::alpha || m == Mask::bravo);
            ++census[m];
        }

        TEST_NEAR(census[Mask::alpha] / total, 0.5, 0.01);
        TEST_NEAR(census[Mask::bravo] / total, 0.5, 0.01);

    }

    {

        std::minstd_rand rng(42);
        std::map<Mask, int> census;
        Mask m;

        for (auto i = 0; i < iterations; ++i) {
            TRY((m = random_bit(Mask::alpha | Mask::bravo | Mask::charlie, rng)));
            TEST(m == Mask::alpha || m == Mask::bravo || m == Mask::charlie);
            ++census[m];
        }

        TEST_NEAR(census[Mask::alpha] / total,    0.33, 0.01);
        TEST_NEAR(census[Mask::bravo] / total,    0.33, 0.01);
        TEST_NEAR(census[Mask::charlie] / total,  0.33, 0.01);

    }

}

namespace {

    RS_ENUM(Foo, unsigned,
        alpha,
        bravo,
        charlie,
        delta,
    )

    RS_ENUM(Bar, int,
        alpha = -1,
        bravo,
        charlie,
        delta,
        echo = 10
    )

}

void test_rs_core_random_enum() {

    static constexpr auto iterations = 10'000;
    static constexpr auto total = static_cast<double>(iterations);

    {

        std::minstd_rand rng(42);
        std::map<Foo, int> census;
        Foo f;

        for (auto i = 0; i < iterations; ++i) {
            TRY((f = random_enum<Foo>(rng)));
            TEST(f >= Foo::alpha);
            TEST(f <= Foo::delta);
            ++census[f];
        }

        TEST_NEAR(census[Foo::alpha] / total,    0.25, 0.02);
        TEST_NEAR(census[Foo::bravo] / total,    0.25, 0.02);
        TEST_NEAR(census[Foo::charlie] / total,  0.25, 0.02);
        TEST_NEAR(census[Foo::delta] / total,    0.25, 0.02);

    }

    {

        std::minstd_rand rng(42);
        std::map<Foo, int> census;
        Foo f;

        for (auto i = 0; i < iterations; ++i) {
            TRY((f = random_enum<Foo, 1>(rng)));
            TEST(f >= Foo::bravo);
            TEST(f <= Foo::delta);
            ++census[f];
        }

        TEST_NEAR(census[Foo::bravo] / total,    0.33, 0.02);
        TEST_NEAR(census[Foo::charlie] / total,  0.33, 0.02);
        TEST_NEAR(census[Foo::delta] / total,    0.33, 0.02);

    }

    {

        std::minstd_rand rng(42);
        std::map<Bar, int> census;
        Bar b;

        for (auto i = 0; i < iterations; ++i) {
            TRY((b = random_enum<Bar>(rng)));
            TEST(b >= Bar::alpha);
            TEST(b <= Bar::echo);
            ++census[b];
        }

        TEST_NEAR(census[Bar::alpha] / total,    0.2, 0.02);
        TEST_NEAR(census[Bar::bravo] / total,    0.2, 0.02);
        TEST_NEAR(census[Bar::charlie] / total,  0.2, 0.02);
        TEST_NEAR(census[Bar::delta] / total,    0.2, 0.02);
        TEST_NEAR(census[Bar::echo] / total,     0.2, 0.02);

    }

    {

        std::minstd_rand rng(42);
        std::map<Bar, int> census;
        Bar b;

        for (auto i = 0; i < iterations; ++i) {
            TRY((b = random_enum<Bar, Bar::charlie>(rng)));
            TEST(b >= Bar::charlie);
            TEST(b <= Bar::echo);
            ++census[b];
        }

        TEST_NEAR(census[Bar::charlie] / total,  0.33, 0.02);
        TEST_NEAR(census[Bar::delta] / total,    0.33, 0.02);
        TEST_NEAR(census[Bar::echo] / total,     0.33, 0.02);

    }

}

void test_rs_core_random_shuffle() {

    static constexpr auto iterations = 10'000;

    std::string s = "abcdefghij";
    std::minstd_rand rng(42);

    for (auto i = 0; i < iterations; ++i) {
        auto t = s;
        TRY(shuffle(t, rng));
        TEST(t != s);
        TEST_EQUAL(t.size(), s.size());
        std::ranges::sort(t);
        TEST_EQUAL(t, s);
    }

}
