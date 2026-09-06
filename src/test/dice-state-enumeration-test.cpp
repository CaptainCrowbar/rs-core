#include "rs-core/dice.hpp"
#include "rs-core/unit-test.hpp"
#include <format>

using namespace RS;
using State = DiceState<int, double>;

void test_rs_core_dice_state_enumeration_1() {

    State state {1};

    TEST_EQUAL(std::format("{}", state), "[1]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[2]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[3]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[4]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[5]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[6]");  TEST(! state.next());

}

void test_rs_core_dice_state_enumeration_2() {

    State state {2};

    TEST_EQUAL(std::format("{}", state), "[1,1]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[1,2]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[1,3]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[1,4]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[1,5]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[1,6]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[2,2]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[2,3]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[2,4]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[2,5]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[2,6]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[3,3]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[3,4]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[3,5]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[3,6]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[4,4]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[4,5]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[4,6]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[5,5]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[5,6]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[6,6]");  TEST(! state.next());

}

void test_rs_core_dice_state_enumeration_3() {

    State state {3};

    TEST_EQUAL(std::format("{}", state), "[1,1,1]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[1,1,2]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[1,1,3]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[1,1,4]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[1,1,5]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[1,1,6]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[1,2,2]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[1,2,3]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[1,2,4]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[1,2,5]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[1,2,6]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[1,3,3]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[1,3,4]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[1,3,5]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[1,3,6]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[1,4,4]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[1,4,5]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[1,4,6]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[1,5,5]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[1,5,6]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[1,6,6]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[2,2,2]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[2,2,3]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[2,2,4]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[2,2,5]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[2,2,6]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[2,3,3]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[2,3,4]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[2,3,5]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[2,3,6]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[2,4,4]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[2,4,5]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[2,4,6]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[2,5,5]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[2,5,6]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[2,6,6]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[3,3,3]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[3,3,4]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[3,3,5]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[3,3,6]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[3,4,4]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[3,4,5]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[3,4,6]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[3,5,5]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[3,5,6]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[3,6,6]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[4,4,4]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[4,4,5]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[4,4,6]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[4,5,5]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[4,5,6]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[4,6,6]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[5,5,5]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[5,5,6]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[5,6,6]");  TEST(state.next());
    TEST_EQUAL(std::format("{}", state), "[6,6,6]");  TEST(! state.next());

}
