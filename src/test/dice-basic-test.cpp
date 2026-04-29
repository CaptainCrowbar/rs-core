#include "rs-core/dice.hpp"
#include "rs-core/random.hpp"
#include "rs-core/unit-test.hpp"
#include <cmath>
#include <format>
#include <stdexcept>
#include <unordered_map>

using namespace RS;

void test_rs_core_dice_basic_statistics() {

    Dice<> dice;

    TEST_EQUAL(dice.number(), 1);
    TEST_EQUAL(dice.faces(), 6);
    TEST_EQUAL(dice.min(), 1);
    TEST_EQUAL(dice.max(), 6);
    TEST_EQUAL(dice.mean(), 3.5);
    TEST_NEAR(dice.sd(), 1.707825, 1e-6);

    TEST_EQUAL(dice.pdf(0), 0);
    TEST_NEAR(dice.pdf(1), 0.166'667, 1e-6);
    TEST_NEAR(dice.pdf(2), 0.166'667, 1e-6);
    TEST_NEAR(dice.pdf(3), 0.166'667, 1e-6);
    TEST_NEAR(dice.pdf(4), 0.166'667, 1e-6);
    TEST_NEAR(dice.pdf(5), 0.166'667, 1e-6);
    TEST_NEAR(dice.pdf(6), 0.166'667, 1e-6);
    TEST_EQUAL(dice.pdf(7), 0);

    TEST_EQUAL(dice.cdf(0), 0);
    TEST_NEAR(dice.cdf(1), 0.166'667, 1e-6);
    TEST_NEAR(dice.cdf(2), 0.333'333, 1e-6);
    TEST_NEAR(dice.cdf(3), 0.500'000, 1e-6);
    TEST_NEAR(dice.cdf(4), 0.666'667, 1e-6);
    TEST_NEAR(dice.cdf(5), 0.833'333, 1e-6);
    TEST_EQUAL(dice.cdf(6), 1);
    TEST_EQUAL(dice.cdf(7), 1);

    TEST_EQUAL(dice.ccdf(0), 1);
    TEST_EQUAL(dice.ccdf(1), 1);
    TEST_NEAR(dice.ccdf(2), 0.833'333, 1e-6);
    TEST_NEAR(dice.ccdf(3), 0.666'667, 1e-6);
    TEST_NEAR(dice.ccdf(4), 0.500'000, 1e-6);
    TEST_NEAR(dice.ccdf(5), 0.333'333, 1e-6);
    TEST_NEAR(dice.ccdf(6), 0.166'667, 1e-6);
    TEST_EQUAL(dice.ccdf(7), 0);

    TRY(dice = Dice<> {3});

    TEST_EQUAL(dice.number(), 3);
    TEST_EQUAL(dice.faces(), 6);
    TEST_EQUAL(dice.min(), 3);
    TEST_EQUAL(dice.max(), 18);
    TEST_EQUAL(dice.mean(), 10.5);
    TEST_NEAR(dice.sd(), 2.9580, 1e-4);

    TEST_EQUAL(dice.pdf(2), 0);
    TEST_NEAR(dice.pdf(3), 0.004'630, 1e-6);
    TEST_NEAR(dice.pdf(4), 0.013'889, 1e-6);
    TEST_NEAR(dice.pdf(5), 0.027'778, 1e-6);
    TEST_NEAR(dice.pdf(6), 0.046'296, 1e-6);
    TEST_NEAR(dice.pdf(7), 0.069'444, 1e-6);
    TEST_NEAR(dice.pdf(8), 0.097'222, 1e-6);
    TEST_NEAR(dice.pdf(9), 0.115'741, 1e-6);
    TEST_NEAR(dice.pdf(10), 0.125'000, 1e-6);
    TEST_NEAR(dice.pdf(11), 0.125'000, 1e-6);
    TEST_NEAR(dice.pdf(12), 0.115'741, 1e-6);
    TEST_NEAR(dice.pdf(13), 0.097'222, 1e-6);
    TEST_NEAR(dice.pdf(14), 0.069'444, 1e-6);
    TEST_NEAR(dice.pdf(15), 0.046'296, 1e-6);
    TEST_NEAR(dice.pdf(16), 0.027'778, 1e-6);
    TEST_NEAR(dice.pdf(17), 0.013'889, 1e-6);
    TEST_NEAR(dice.pdf(18), 0.004'630, 1e-6);
    TEST_EQUAL(dice.pdf(19), 0);

    TEST_EQUAL(dice.cdf(2), 0);
    TEST_NEAR(dice.cdf(3), 0.004'630, 1e-6);
    TEST_NEAR(dice.cdf(4), 0.018'519, 1e-6);
    TEST_NEAR(dice.cdf(5), 0.046'296, 1e-6);
    TEST_NEAR(dice.cdf(6), 0.092'593, 1e-6);
    TEST_NEAR(dice.cdf(7), 0.162'037, 1e-6);
    TEST_NEAR(dice.cdf(8), 0.259'259, 1e-6);
    TEST_NEAR(dice.cdf(9), 0.375'000, 1e-6);
    TEST_NEAR(dice.cdf(10), 0.500'000, 1e-6);
    TEST_NEAR(dice.cdf(11), 0.625'000, 1e-6);
    TEST_NEAR(dice.cdf(12), 0.740'741, 1e-6);
    TEST_NEAR(dice.cdf(13), 0.837'963, 1e-6);
    TEST_NEAR(dice.cdf(14), 0.907'407, 1e-6);
    TEST_NEAR(dice.cdf(15), 0.953'704, 1e-6);
    TEST_NEAR(dice.cdf(16), 0.981'481, 1e-6);
    TEST_NEAR(dice.cdf(17), 0.995'370, 1e-6);
    TEST_EQUAL(dice.cdf(18), 1);
    TEST_EQUAL(dice.cdf(19), 1);

    TEST_EQUAL(dice.ccdf(2), 1);
    TEST_EQUAL(dice.ccdf(3), 1);
    TEST_NEAR(dice.ccdf(4), 0.995'370, 1e-6);
    TEST_NEAR(dice.ccdf(5), 0.981'481, 1e-6);
    TEST_NEAR(dice.ccdf(6), 0.953'704, 1e-6);
    TEST_NEAR(dice.ccdf(7), 0.907'407, 1e-6);
    TEST_NEAR(dice.ccdf(8), 0.837'963, 1e-6);
    TEST_NEAR(dice.ccdf(9), 0.740'741, 1e-6);
    TEST_NEAR(dice.ccdf(10), 0.625'000, 1e-6);
    TEST_NEAR(dice.ccdf(11), 0.500'000, 1e-6);
    TEST_NEAR(dice.ccdf(12), 0.375'000, 1e-6);
    TEST_NEAR(dice.ccdf(13), 0.259'259, 1e-6);
    TEST_NEAR(dice.ccdf(14), 0.162'037, 1e-6);
    TEST_NEAR(dice.ccdf(15), 0.092'593, 1e-6);
    TEST_NEAR(dice.ccdf(16), 0.046'296, 1e-6);
    TEST_NEAR(dice.ccdf(17), 0.018'519, 1e-6);
    TEST_NEAR(dice.ccdf(18), 0.004'630, 1e-6);
    TEST_EQUAL(dice.ccdf(19), 0);

    TRY((dice = Dice<> {2, 100}));

    TEST_EQUAL(dice.number(), 2);
    TEST_EQUAL(dice.faces(), 100);
    TEST_EQUAL(dice.min(), 2);
    TEST_EQUAL(dice.max(), 200);
    TEST_EQUAL(dice.mean(), 101);
    TEST_NEAR(dice.sd(), 40.8228, 1e-4);

}

void test_rs_core_dice_basic_formatting() {

    Dice<> dice;

    TEST_EQUAL(std::format("{}", dice),      "1d6");
    TEST_EQUAL(std::format("{:p}", dice),    "d6");
    TEST_EQUAL(std::format("{:s}", dice),    "1d");
    TEST_EQUAL(std::format("{:D}", dice),    "1D6");
    TEST_EQUAL(std::format("{:Dps}", dice),  "D");

    TRY(dice = Dice<> {3});

    TEST_EQUAL(std::format("{}", dice),      "3d6");
    TEST_EQUAL(std::format("{:p}", dice),    "3d6");
    TEST_EQUAL(std::format("{:s}", dice),    "3d");
    TEST_EQUAL(std::format("{:D}", dice),    "3D6");
    TEST_EQUAL(std::format("{:Dps}", dice),  "3D");

    TRY((dice = Dice<> {2, 100}));

    TEST_EQUAL(std::format("{}", dice),      "2d100");
    TEST_EQUAL(std::format("{:p}", dice),    "2d100");
    TEST_EQUAL(std::format("{:s}", dice),    "2d100");
    TEST_EQUAL(std::format("{:D}", dice),    "2D100");
    TEST_EQUAL(std::format("{:Dps}", dice),  "2D100");

}

void test_rs_core_dice_basic_parsing() {

    Dice<> dice;

    TRY(dice = Dice<>{});        TEST_EQUAL(std::format("{}", dice), "1d6");
    TRY(dice = Dice<>{"2d10"});  TEST_EQUAL(std::format("{}", dice), "2d10");
    TRY(dice = Dice<>{"3D20"});  TEST_EQUAL(std::format("{}", dice), "3d20");
    TRY(dice = Dice<>{"4d"});    TEST_EQUAL(std::format("{}", dice), "4d6");
    TRY(dice = Dice<>{"d20"});   TEST_EQUAL(std::format("{}", dice), "1d20");
    TRY(dice = Dice<>{"d"});     TEST_EQUAL(std::format("{}", dice), "1d6");

    TEST_THROW_EXACT(Dice<>{""},       std::invalid_argument,  R"(Invalid dice expression: "")");
    TEST_THROW_EXACT(Dice<>{"6"},      std::invalid_argument,  R"(Invalid dice expression: "6")");
    TEST_THROW_EXACT(Dice<>{"2d6+1"},  std::invalid_argument,  R"(Invalid dice expression: "2d6+1")");

}

void test_rs_core_dice_basic_generation() {

    static constexpr auto n = 10'000;
    static constexpr auto nx = static_cast<double>(n);

    Pcg rng {42};
    Dice<> dice;
    std::unordered_map<int, int> census;
    int x;
    double mean, sd;
    auto sum = 0.0;
    auto sum2 = 0.0;

    for (auto i = 0; i < n; ++i) {
        TRY(x = dice(rng));
        TEST(x >= dice.min());
        TEST(x <= dice.max());
        ++census[x];
    }

    TEST_NEAR(census[1] / nx, 0.1667, 0.01);
    TEST_NEAR(census[2] / nx, 0.1667, 0.01);
    TEST_NEAR(census[3] / nx, 0.1667, 0.01);
    TEST_NEAR(census[4] / nx, 0.1667, 0.01);
    TEST_NEAR(census[5] / nx, 0.1667, 0.01);
    TEST_NEAR(census[6] / nx, 0.1667, 0.01);

    rng.seed(42);
    TRY(dice = Dice<> {3});
    sum = 0.0;
    sum2 = 0.0;

    for (auto i = 0; i < n; ++i) {
        TRY(x = dice(rng));
        TEST(x >= dice.min());
        TEST(x <= dice.max());
        auto dx = static_cast<double>(x);
        sum += dx;
        sum2 += dx * dx;
    }

    mean = sum / nx;
    sd = std::sqrt((nx / (nx - 1.0)) * (sum2 / nx - mean * mean));
    TEST_NEAR(mean, dice.mean(), 0.05);
    TEST_NEAR(sd, dice.sd(), 0.05);

    rng.seed(42);
    TRY((dice = Dice<> {2, 100}));
    sum = 0.0;
    sum2 = 0.0;

    for (auto i = 0; i < n; ++i) {
        TRY(x = dice(rng));
        TEST(x >= dice.min());
        TEST(x <= dice.max());
        auto dx = static_cast<double>(x);
        sum += dx;
        sum2 += dx * dx;
    }

    mean = sum / nx;
    sd = std::sqrt((nx / (nx - 1.0)) * (sum2 / nx - mean * mean));
    TEST_NEAR(mean, dice.mean(), 0.5);
    TEST_NEAR(sd, dice.sd(), 0.5);

}
