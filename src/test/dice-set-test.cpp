#include "rs-core/dice.hpp"
#include "rs-core/random.hpp"
#include "rs-core/rational.hpp"
#include "rs-core/unit-test.hpp"
#include <algorithm>
#include <cmath>
#include <format>

using namespace RS;

void test_rs_core_dice_set_formatting() {

    DiceSet<> set;

    /**/                                               TEST_EQUAL(std::format("{}", set), "0");
    TRY((set = DiceSet<>{2, 10}));                     TEST_EQUAL(std::format("{}", set), "2d10");
    TRY((set += DiceSet<>{3, 8, IntRational{3, 2}}));  TEST_EQUAL(std::format("{}", set), "2d10+3d8*3/2");
    TRY((set -= DiceSet<>{4, 6, IntRational{5, 3}}));  TEST_EQUAL(std::format("{}", set), "2d10+3d8*3/2-4d6*5/3");
    TRY((set += DiceSet<>{1, 4, 10}));                 TEST_EQUAL(std::format("{}", set), "2d10+3d8*3/2-4d6*5/3+1d4*10");
    TRY((set += 20));                                  TEST_EQUAL(std::format("{}", set), "2d10+3d8*3/2-4d6*5/3+1d4*10+20");
    TRY((set += IntRational{5, 2}));                   TEST_EQUAL(std::format("{}", set), "2d10+3d8*3/2-4d6*5/3+1d4*10+45/2");
    TRY((set *= IntRational{3, 2}));                   TEST_EQUAL(std::format("{}", set), "2d10*3/2+3d8*9/4-4d6*5/2+1d4*15+135/4");
    TRY((set /= IntRational{5, 4}));                   TEST_EQUAL(std::format("{}", set), "2d10*6/5+3d8*9/5-4d6*2+1d4*12+27");
    /**/                                               TEST_EQUAL(std::format("{:D}", set), "2D10*6/5+3D8*9/5-4D6*2+1D4*12+27");
    /**/                                               TEST_EQUAL(std::format("{:p}", set), "2d10*6/5+3d8*9/5-4d6*2+d4*12+27");
    /**/                                               TEST_EQUAL(std::format("{:s}", set), "2d10*6/5+3d8*9/5-4d*2+1d4*12+27");
    /**/                                               TEST_EQUAL(std::format("{:x}", set), "2d10x6/5+3d8x9/5-4d6x2+1d4x12+27");

}

void test_rs_core_dice_set_parsing() {

    DiceSet<> set;

    TRY(set = DiceSet<>{""});                                                  TEST_EQUAL(std::format("{}", set), "0");
    TRY(set = DiceSet<>{"42"});                                                TEST_EQUAL(std::format("{}", set), "42");
    TRY(set = DiceSet<>{"2d10"});                                              TEST_EQUAL(std::format("{}", set), "2d10");
    TRY(set = DiceSet<>{"2d100 + 3d6"});                                       TEST_EQUAL(std::format("{}", set), "2d100+3d6");
    TRY(set = DiceSet<>{"2d100 - 3d6"});                                       TEST_EQUAL(std::format("{}", set), "2d100-3d6");
    TRY(set = DiceSet<>{"2d10 + 3d8 * 3/2"});                                  TEST_EQUAL(std::format("{}", set), "2d10+3d8*3/2");
    TRY(set = DiceSet<>{"3d8 * 3/2 + 2d10"});                                  TEST_EQUAL(std::format("{}", set), "2d10+3d8*3/2");
    TRY(set = DiceSet<>{"3d8 * 1/2 + 2d10"});                                  TEST_EQUAL(std::format("{}", set), "2d10+3d8/2");
    TRY(set = DiceSet<>{"3d8 / 2 + 2d10"});                                    TEST_EQUAL(std::format("{}", set), "2d10+3d8/2");
    TRY(set = DiceSet<>{"2d10 + 3d8 x 3/2 - 4d6 x 5/3"});                      TEST_EQUAL(std::format("{}", set), "2d10+3d8*3/2-4d6*5/3");
    TRY(set = DiceSet<>{"2d10 + 3d8 * 3/2 - 4d6 * 5/3 + 1d4 * 10 + 20"});      TEST_EQUAL(std::format("{}", set), "2d10+3d8*3/2-4d6*5/3+1d4*10+20");
    TRY(set = DiceSet<>{"2d10 + 3d8 x 3/2 - 4d6 x 5/3 + 1d4 x 10 + 225/10"});  TEST_EQUAL(std::format("{}", set), "2d10+3d8*3/2-4d6*5/3+1d4*10+45/2");
    TRY(set = DiceSet<>{"- 4d6 * 5/3 + 3d8 * 3/2 + 2d10"});                    TEST_EQUAL(std::format("{}", set), "2d10+3d8*3/2-4d6*5/3");
    TRY(set = DiceSet<>{"1d4 * 10 - 4d6 * 5/3 + 3d8 * 3/2 + 2d10"});           TEST_EQUAL(std::format("{}", set), "2d10+3d8*3/2-4d6*5/3+1d4*10");
    TRY(set = DiceSet<>{"20 + 1d4 * 10 - 4d6 * 5/3 + 3d8 * 3/2 + 2d10"});      TEST_EQUAL(std::format("{}", set), "2d10+3d8*3/2-4d6*5/3+1d4*10+20");
    TRY(set = DiceSet<>{"45/2 + 1d4 * 10 - 4d6 * 5/3 + 3d8 * 3/2 + 2d10"});    TEST_EQUAL(std::format("{}", set), "2d10+3d8*3/2-4d6*5/3+1d4*10+45/2");
    TRY(set = DiceSet<>{"2d6 + 2d10 + 3d6 + 3d10"});                           TEST_EQUAL(std::format("{}", set), "5d10+5d6");
    TRY(set = DiceSet<>{"2d6 * 2 + 2d10 + 2d6 * 3 + 3d10"});                   TEST_EQUAL(std::format("{}", set), "5d10+2d6*5");

}

void test_rs_core_dice_set_statistics() {

    DiceSet<> set;
    TEST_EQUAL(set.min(), 0);
    TEST_EQUAL(set.max(), 0);
    TEST_EQUAL(set.mean(), 0);
    TEST_EQUAL(set.sd(), 0);

    TRY(set = DiceSet<>{"d"});
    TEST_EQUAL(set.min(), 1);
    TEST_EQUAL(set.max(), 6);
    TEST_EQUAL(set.mean(), 3.5);
    TEST_NEAR(set.sd(), 1.707825, 1e-6);

    TRY(set = DiceSet<>{"3d"});
    TEST_EQUAL(set.min(), 3);
    TEST_EQUAL(set.max(), 18);
    TEST_EQUAL(set.mean(), 10.5);
    TEST_NEAR(set.sd(), 2.9580, 1e-4);

    TRY(set = DiceSet<>{"2d100"});
    TEST_EQUAL(set.min(), 2);
    TEST_EQUAL(set.max(), 200);
    TEST_EQUAL(set.mean(), 101);
    TEST_NEAR(set.sd(), 40.8228, 1e-4);

    TRY(set = DiceSet<>{"2d100-3d6"});
    TEST_EQUAL(set.min(), -16);
    TEST_EQUAL(set.max(), 197);
    TEST_EQUAL(set.mean(), 90.5);
    TEST_NEAR(set.sd(), 40.9298, 1e-4);

    TRY(set = DiceSet<>{"2d100*3/2-3d6/2"});
    TEST_EQUAL(set.min(), -6);
    TEST_EQUAL(set.max(), (IntRational{597, 2}));
    TEST_EQUAL(set.mean(), 146.25);
    TEST_NEAR(set.sd(), 61.2521, 1e-4);

}

void test_rs_core_dice_set_generation() {

    static constexpr auto n = 10'000;
    static constexpr auto dn = static_cast<double>(n);

    DiceSet<> set;
    Pcg rng;
    IntRational min, max, x;
    double mean, sd, sum, sum2;

    TRY(set = DiceSet<>{"3d"});
    rng.seed(42);
    min = 999'999;
    max = 0;
    sum = 0.0;
    sum2 = 0.0;

    for (auto i = 0; i < n; ++i) {
        TRY(x = set(rng));
        auto dx = x.to_floating<double>();
        min = std::min(min, x);
        max = std::max(max, x);
        sum += dx;
        sum2 += dx * dx;
    }

    mean = sum / dn;
    sd = std::sqrt((dn / (dn - 1.0)) * (sum2 / dn - mean * mean));
    TEST_EQUAL(min, set.min());
    TEST_EQUAL(max, set.max());
    TEST_NEAR(mean, set.mean(), 0.1);
    TEST_NEAR(sd, set.sd(), 0.1);

    TRY(set = DiceSet<>{"2d100"});
    rng.seed(42);
    min = 999'999;
    max = 0;
    sum = 0.0;
    sum2 = 0.0;

    for (auto i = 0; i < n; ++i) {
        TRY(x = set(rng));
        auto dx = x.to_floating<double>();
        min = std::min(min, x);
        max = std::max(max, x);
        sum += dx;
        sum2 += dx * dx;
    }

    mean = sum / dn;
    sd = std::sqrt((dn / (dn - 1.0)) * (sum2 / dn - mean * mean));
    TEST_EQUAL(min, set.min());
    TEST_EQUAL(max, set.max());
    TEST_NEAR(mean, set.mean(), 0.5);
    TEST_NEAR(sd, set.sd(), 0.5);

    TRY(set = DiceSet<>{"2d100-3d6"});
    rng.seed(42);
    min = 999'999;
    max = 0;
    sum = 0.0;
    sum2 = 0.0;

    for (auto i = 0; i < n; ++i) {
        TRY(x = set(rng));
        auto dx = x.to_floating<double>();
        min = std::min(min, x);
        max = std::max(max, x);
        sum += dx;
        sum2 += dx * dx;
    }

    mean = sum / dn;
    sd = std::sqrt((dn / (dn - 1.0)) * (sum2 / dn - mean * mean));
    TEST(min >= set.min());
    TEST(max <= set.max());
    TEST_NEAR(mean, set.mean(), 1);
    TEST_NEAR(sd, set.sd(), 1);

    TRY(set = DiceSet<>{"2d100*3/2-3d6/2"});
    rng.seed(42);
    min = 999'999;
    max = 0;
    sum = 0.0;
    sum2 = 0.0;

    for (auto i = 0; i < n; ++i) {
        TRY(x = set(rng));
        auto dx = x.to_floating<double>();
        min = std::min(min, x);
        max = std::max(max, x);
        sum += dx;
        sum2 += dx * dx;
    }

    mean = sum / dn;
    sd = std::sqrt((dn / (dn - 1.0)) * (sum2 / dn - mean * mean));
    TEST(min >= set.min());
    TEST(max <= set.max());
    TEST_NEAR(mean, set.mean(), 1);
    TEST_NEAR(sd, set.sd(), 1);

}
