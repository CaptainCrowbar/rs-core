#include "rs-core/dice.hpp"
#include "rs-core/unit-test.hpp"
#include <format>
#include <stdexcept>
#include <vector>

using namespace RS;
using State = DiceState<int, double>;

void test_rs_core_dice_state_construction() {

    State state;
    std::vector<int> vec;

    TEST_EQUAL(state.number(), 0);
    TEST_EQUAL(state.faces(), 6);
    TEST_EQUAL(std::format("{}", state), "[]");

    TRY((state = State {3}));
    TEST_EQUAL(state.number(), 3);
    TEST_EQUAL(state.faces(), 6);
    TEST_EQUAL(std::format("{}", state), "[1,1,1]");

    TRY((state = State {3, 10}));
    TEST_EQUAL(state.number(), 3);
    TEST_EQUAL(state.faces(), 10);
    TEST_EQUAL(std::format("{}", state), "[1,1,1]");

    TRY((state = State {3, 10, 5}));
    TEST_EQUAL(state.number(), 3);
    TEST_EQUAL(state.faces(), 10);
    TEST_EQUAL(std::format("{}", state), "[5,5,5]");

    TRY((state = State::from_list(6, {6, 4, 2})));
    TEST_EQUAL(state.number(), 3);
    TEST_EQUAL(state.faces(), 6);
    TEST_EQUAL(std::format("{}", state), "[2,4,6]");

    vec = {5, 4, 3, 2};
    TRY((state = State::from_range(6, vec)));
    TEST_EQUAL(state.number(), 4);
    TEST_EQUAL(state.faces(), 6);
    TEST_EQUAL(std::format("{}", state), "[2,3,4,5]");

    vec = {6, 7};
    TEST_THROW_EXACT((state = State {1, 0}),                 std::length_error,  "Number of faces must be at least 1");
    TEST_THROW_EXACT((state = State {3, 10, 0}),             std::out_of_range,  "Dice value (0) is out of range (1-10)");
    TEST_THROW_EXACT((state = State {3, 10, 11}),            std::out_of_range,  "Dice value (11) is out of range (1-10)");
    TEST_THROW_EXACT((state = State::from_list(6, {6, 7})),  std::out_of_range,  "Dice value (7) is out of range (1-6)");
    TEST_THROW_EXACT((state = State::from_range(6, vec)),    std::out_of_range,  "Dice value (7) is out of range (1-6)");

}
