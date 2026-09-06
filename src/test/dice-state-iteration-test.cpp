#include "rs-core/dice.hpp"
#include "rs-core/unit-test.hpp"
#include <format>

using namespace RS;

void test_rs_core_dice_state_iteration_1() {

    Dice<> dice {1};
    auto states = dice.states();
    auto it = states.begin();

    TEST_EQUAL(std::format("{}", *it), "[1]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[2]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[3]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[4]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[5]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[6]");  TRY(++it);

    TEST(it == states.end());

}

void test_rs_core_dice_state_iteration_2() {

    Dice<> dice {2};
    auto states = dice.states();
    auto it = states.begin();

    TEST_EQUAL(std::format("{}", *it), "[1,1]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[1,2]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[1,3]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[1,4]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[1,5]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[1,6]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[2,2]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[2,3]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[2,4]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[2,5]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[2,6]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[3,3]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[3,4]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[3,5]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[3,6]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[4,4]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[4,5]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[4,6]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[5,5]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[5,6]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[6,6]");  TRY(++it);

    TEST(it == states.end());

}

void test_rs_core_dice_state_iteration_3() {

    Dice<> dice {3};
    auto states = dice.states();
    auto it = states.begin();

    TEST_EQUAL(std::format("{}", *it), "[1,1,1]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[1,1,2]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[1,1,3]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[1,1,4]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[1,1,5]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[1,1,6]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[1,2,2]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[1,2,3]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[1,2,4]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[1,2,5]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[1,2,6]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[1,3,3]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[1,3,4]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[1,3,5]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[1,3,6]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[1,4,4]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[1,4,5]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[1,4,6]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[1,5,5]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[1,5,6]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[1,6,6]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[2,2,2]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[2,2,3]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[2,2,4]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[2,2,5]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[2,2,6]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[2,3,3]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[2,3,4]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[2,3,5]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[2,3,6]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[2,4,4]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[2,4,5]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[2,4,6]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[2,5,5]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[2,5,6]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[2,6,6]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[3,3,3]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[3,3,4]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[3,3,5]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[3,3,6]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[3,4,4]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[3,4,5]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[3,4,6]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[3,5,5]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[3,5,6]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[3,6,6]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[4,4,4]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[4,4,5]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[4,4,6]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[4,5,5]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[4,5,6]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[4,6,6]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[5,5,5]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[5,5,6]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[5,6,6]");  TRY(++it);
    TEST_EQUAL(std::format("{}", *it), "[6,6,6]");  TRY(++it);

    TEST(it == states.end());

}
