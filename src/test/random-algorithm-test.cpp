#include "rs-core/random.hpp"
#include "rs-core/unit-test.hpp"
#include <algorithm>
#include <map>
#include <random>
#include <ranges>
#include <string>
#include <vector>

using namespace RS;

void test_rs_core_random_choice() {

    static constexpr auto iterations = 10'000;
    static constexpr auto total = static_cast<double>(iterations);

    {

        RandomChoice<std::string> choice;
        std::minstd_rand rng(42);
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

        TEST_NEAR(census["Alpha"] / total,    0.2, 0.02);
        TEST_NEAR(census["Bravo"] / total,    0.2, 0.02);
        TEST_NEAR(census["Charlie"] / total,  0.2, 0.02);
        TEST_NEAR(census["Delta"] / total,    0.2, 0.02);
        TEST_NEAR(census["Echo"] / total,     0.2, 0.02);

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
        std::minstd_rand rng(42);
        std::map<std::string, int> census;
        std::string s;

        for (auto i = 0; i < iterations; ++i) {
            TRY(s = choice(rng));
            TEST_MATCH(s, "^[A-E][a-z]+$");
            ++census[s];
        }

        TEST_NEAR(census["Alpha"] / total,    0.2, 0.02);
        TEST_NEAR(census["Bravo"] / total,    0.2, 0.02);
        TEST_NEAR(census["Charlie"] / total,  0.2, 0.02);
        TEST_NEAR(census["Delta"] / total,    0.2, 0.02);
        TEST_NEAR(census["Echo"] / total,     0.2, 0.02);

    }

    {

        RandomChoice<std::string> choice {
            "Alpha",
            "Bravo",
            "Charlie",
            "Delta",
            "Echo",
        };

        std::minstd_rand rng(42);
        std::map<std::string, int> census;
        std::string s;

        for (auto i = 0; i < iterations; ++i) {
            TRY(s = choice(rng));
            TEST_MATCH(s, "^[A-E][a-z]+$");
            ++census[s];
        }

        TEST_NEAR(census["Alpha"] / total,    0.2, 0.02);
        TEST_NEAR(census["Bravo"] / total,    0.2, 0.02);
        TEST_NEAR(census["Charlie"] / total,  0.2, 0.02);
        TEST_NEAR(census["Delta"] / total,    0.2, 0.02);
        TEST_NEAR(census["Echo"] / total,     0.2, 0.02);

    }

}

void test_rs_core_random_choice_functions() {

    static constexpr auto iterations = 10'000;
    static constexpr auto total = static_cast<double>(iterations);

    static const std::vector<std::string> vec {
        "Alpha",
        "Bravo",
        "Charlie",
        "Delta",
        "Echo",
    };

    {

        std::minstd_rand rng(42);
        std::map<std::string, int> census;
        std::string s;

        for (auto i = 0; i < iterations; ++i) {
            TRY(s = random_choice(vec, rng));
            TEST_MATCH(s, "^[A-E][a-z]+$");
            ++census[s];
        }

        TEST_NEAR(census["Alpha"] / total,    0.2, 0.02);
        TEST_NEAR(census["Bravo"] / total,    0.2, 0.02);
        TEST_NEAR(census["Charlie"] / total,  0.2, 0.02);
        TEST_NEAR(census["Delta"] / total,    0.2, 0.02);
        TEST_NEAR(census["Echo"] / total,     0.2, 0.02);

    }

    {

        std::minstd_rand rng(42);
        std::map<std::string, int> census;
        std::string s;

        for (auto i = 0; i < iterations; ++i) {
            TRY(s = quick_choice(vec, rng));
            TEST_MATCH(s, "^[A-E][a-z]+$");
            ++census[s];
        }

        TEST_NEAR(census["Alpha"] / total,    0.2, 0.02);
        TEST_NEAR(census["Bravo"] / total,    0.2, 0.02);
        TEST_NEAR(census["Charlie"] / total,  0.2, 0.02);
        TEST_NEAR(census["Delta"] / total,    0.2, 0.02);
        TEST_NEAR(census["Echo"] / total,     0.2, 0.02);

    }

}

void test_rs_core_random_weighted_choice() {

    static constexpr auto iterations = 10'000;
    static constexpr auto total = static_cast<double>(iterations);

    {

        WeightedChoice<std::string> choice;
        std::minstd_rand rng(42);
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

        TEST_NEAR(census["Alpha"] / total,    0.1, 0.02);
        TEST_NEAR(census["Bravo"] / total,    0.2, 0.02);
        TEST_NEAR(census["Charlie"] / total,  0.3, 0.02);
        TEST_NEAR(census["Delta"] / total,    0.4, 0.02);

    }

    {

        WeightedChoice<std::string> choice {
            {"Alpha",    10},
            {"Bravo",    20},
            {"Charlie",  30},
            {"Delta",    40},
        };

        std::minstd_rand rng(42);
        std::map<std::string, int> census;
        std::string s;

        for (auto i = 0; i < iterations; ++i) {
            TRY(s = choice(rng));
            TEST_MATCH(s, "^[A-E][a-z]+$");
            ++census[s];
        }

        TEST_NEAR(census["Alpha"] / total,    0.1, 0.02);
        TEST_NEAR(census["Bravo"] / total,    0.2, 0.02);
        TEST_NEAR(census["Charlie"] / total,  0.3, 0.02);
        TEST_NEAR(census["Delta"] / total,    0.4, 0.02);

    }

}

void test_rs_core_random_weighted_choice_floating_point() {

    static constexpr auto iterations = 10'000;
    static constexpr auto total = static_cast<double>(iterations);

    {

        WeightedChoice<std::string, double> choice;
        std::minstd_rand rng(42);
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

        TEST_NEAR(census["Alpha"] / total,    0.1, 0.02);
        TEST_NEAR(census["Bravo"] / total,    0.2, 0.02);
        TEST_NEAR(census["Charlie"] / total,  0.3, 0.02);
        TEST_NEAR(census["Delta"] / total,    0.4, 0.02);

    }

    {

        WeightedChoice<std::string, double> choice {
            {"Alpha",    0.01},
            {"Bravo",    0.02},
            {"Charlie",  0.03},
            {"Delta",    0.04},
        };

        std::minstd_rand rng(42);
        std::map<std::string, int> census;
        std::string s;

        for (auto i = 0; i < iterations; ++i) {
            TRY(s = choice(rng));
            TEST_MATCH(s, "^[A-E][a-z]+$");
            ++census[s];
        }

        TEST_NEAR(census["Alpha"] / total,    0.1, 0.02);
        TEST_NEAR(census["Bravo"] / total,    0.2, 0.02);
        TEST_NEAR(census["Charlie"] / total,  0.3, 0.02);
        TEST_NEAR(census["Delta"] / total,    0.4, 0.02);

    }

}

void test_rs_core_random_weighted_choice_mp_integer() {

    static constexpr auto iterations = 1000;
    static constexpr auto total = static_cast<double>(iterations);

    {

        WeightedChoice<std::string, Integer> choice;
        std::minstd_rand rng(42);
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

        TEST_NEAR(census["Alpha"] / total,    0.1, 0.02);
        TEST_NEAR(census["Bravo"] / total,    0.2, 0.02);
        TEST_NEAR(census["Charlie"] / total,  0.3, 0.02);
        TEST_NEAR(census["Delta"] / total,    0.4, 0.02);

    }

    {

        WeightedChoice<std::string, Integer> choice {
            {"Alpha",    10},
            {"Bravo",    20},
            {"Charlie",  30},
            {"Delta",    40},
        };

        std::minstd_rand rng(42);
        std::map<std::string, int> census;
        std::string s;

        for (auto i = 0; i < iterations; ++i) {
            TRY(s = choice(rng));
            TEST_MATCH(s, "^[A-E][a-z]+$");
            ++census[s];
        }

        TEST_NEAR(census["Alpha"] / total,    0.1, 0.02);
        TEST_NEAR(census["Bravo"] / total,    0.2, 0.02);
        TEST_NEAR(census["Charlie"] / total,  0.3, 0.02);
        TEST_NEAR(census["Delta"] / total,    0.4, 0.02);

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
