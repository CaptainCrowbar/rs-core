#include "rs-core/dice.hpp"
#include "rs-core/unit-test.hpp"
#include <cstddef>
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

void test_rs_core_dice_state_formatting() {

    State state;
    std::vector<int> vec;

    TEST_EQUAL(std::format("{}", state.asc()), "[]");
    TEST_EQUAL(std::format("{}", state.desc()), "[]");
    TEST_EQUAL(std::format("{}", state.asc_groups()), "[]");
    TEST_EQUAL(std::format("{}", state.desc_groups()), "[]");
    TEST_EQUAL(std::format("{}", state), "[]");
    TEST_EQUAL(std::format("{:d}", state), "[]");
    TEST_EQUAL(std::format("{:c}", state), "[]");
    TEST_EQUAL(std::format("{:cd}", state), "[]");

    TRY((state = State {3, 10, 5}));
    TEST_EQUAL(state.number(), 3);
    TEST_EQUAL(state.faces(), 10);
    TEST_EQUAL(std::format("{}", state.asc()), "[5, 5, 5]");
    TEST_EQUAL(std::format("{}", state.desc()), "[5, 5, 5]");
    TEST_EQUAL(std::format("{}", state.asc_groups()), "[5:3]");
    TEST_EQUAL(std::format("{}", state.desc_groups()), "[5:3]");
    TEST_EQUAL(std::format("{}", state), "[5,5,5]");
    TEST_EQUAL(std::format("{:d}", state), "[5,5,5]");
    TEST_EQUAL(std::format("{:c}", state), "[5:3]");
    TEST_EQUAL(std::format("{:cd}", state), "[5:3]");

    for (auto i = 6; i >= 1; --i) {
        vec.insert(vec.end(), static_cast<std::size_t>(i), i);
    }

    TRY((state = State::from_range(6, vec)));
    TEST_EQUAL(state.number(), 21);
    TEST_EQUAL(state.faces(), 6);
    TEST_EQUAL(std::format("{}", state.asc()), "[1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6]");
    TEST_EQUAL(std::format("{}", state.desc()), "[6, 6, 6, 6, 6, 6, 5, 5, 5, 5, 5, 4, 4, 4, 4, 3, 3, 3, 2, 2, 1]");
    TEST_EQUAL(std::format("{}", state.asc_groups()), "[1:1, 2:2, 3:3, 4:4, 5:5, 6:6]");
    TEST_EQUAL(std::format("{}", state.desc_groups()), "[6:6, 5:5, 4:4, 3:3, 2:2, 1:1]");
    TEST_EQUAL(std::format("{}", state), "[1,2,2,3,3,3,4,4,4,4,5,5,5,5,5,6,6,6,6,6,6]");
    TEST_EQUAL(std::format("{:d}", state), "[6,6,6,6,6,6,5,5,5,5,5,4,4,4,4,3,3,3,2,2,1]");
    TEST_EQUAL(std::format("{:c}", state), "[1:1,2:2,3:3,4:4,5:5,6:6]");
    TEST_EQUAL(std::format("{:cd}", state), "[6:6,5:5,4:4,3:3,2:2,1:1]");

}

void test_rs_core_dice_state_enumeration() {

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

    state = State {3};

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

void test_rs_core_dice_state_iteration() {

    Dice<> dice;
    Dice<>::state_range states;
    Dice<>::state_iterator it;

    dice = Dice<> {2};
    states = dice.states();
    it = states.begin();

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

    dice = Dice<> {3};
    states = dice.states();
    it = states.begin();

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

void test_rs_core_dice_state_probability() {

    State state;

    TRY((state = State::from_list(6, {1})));  TEST_NEAR(state.probability(), 0.166'666'666'7, 1e-10);
    TRY((state = State::from_list(6, {2})));  TEST_NEAR(state.probability(), 0.166'666'666'7, 1e-10);
    TRY((state = State::from_list(6, {3})));  TEST_NEAR(state.probability(), 0.166'666'666'7, 1e-10);
    TRY((state = State::from_list(6, {4})));  TEST_NEAR(state.probability(), 0.166'666'666'7, 1e-10);
    TRY((state = State::from_list(6, {5})));  TEST_NEAR(state.probability(), 0.166'666'666'7, 1e-10);
    TRY((state = State::from_list(6, {6})));  TEST_NEAR(state.probability(), 0.166'666'666'7, 1e-10);

    TRY((state = State::from_list(6, {1, 1})));  TEST_NEAR(state.probability(), 0.027'777'777'8, 1e-10);
    TRY((state = State::from_list(6, {1, 2})));  TEST_NEAR(state.probability(), 0.055'555'555'6, 1e-10);
    TRY((state = State::from_list(6, {1, 3})));  TEST_NEAR(state.probability(), 0.055'555'555'6, 1e-10);
    TRY((state = State::from_list(6, {1, 4})));  TEST_NEAR(state.probability(), 0.055'555'555'6, 1e-10);
    TRY((state = State::from_list(6, {1, 5})));  TEST_NEAR(state.probability(), 0.055'555'555'6, 1e-10);
    TRY((state = State::from_list(6, {1, 6})));  TEST_NEAR(state.probability(), 0.055'555'555'6, 1e-10);
    TRY((state = State::from_list(6, {2, 2})));  TEST_NEAR(state.probability(), 0.027'777'777'8, 1e-10);
    TRY((state = State::from_list(6, {2, 3})));  TEST_NEAR(state.probability(), 0.055'555'555'6, 1e-10);
    TRY((state = State::from_list(6, {2, 4})));  TEST_NEAR(state.probability(), 0.055'555'555'6, 1e-10);
    TRY((state = State::from_list(6, {2, 5})));  TEST_NEAR(state.probability(), 0.055'555'555'6, 1e-10);
    TRY((state = State::from_list(6, {2, 6})));  TEST_NEAR(state.probability(), 0.055'555'555'6, 1e-10);
    TRY((state = State::from_list(6, {3, 3})));  TEST_NEAR(state.probability(), 0.027'777'777'8, 1e-10);
    TRY((state = State::from_list(6, {3, 4})));  TEST_NEAR(state.probability(), 0.055'555'555'6, 1e-10);
    TRY((state = State::from_list(6, {3, 5})));  TEST_NEAR(state.probability(), 0.055'555'555'6, 1e-10);
    TRY((state = State::from_list(6, {3, 6})));  TEST_NEAR(state.probability(), 0.055'555'555'6, 1e-10);
    TRY((state = State::from_list(6, {4, 4})));  TEST_NEAR(state.probability(), 0.027'777'777'8, 1e-10);
    TRY((state = State::from_list(6, {4, 5})));  TEST_NEAR(state.probability(), 0.055'555'555'6, 1e-10);
    TRY((state = State::from_list(6, {4, 6})));  TEST_NEAR(state.probability(), 0.055'555'555'6, 1e-10);
    TRY((state = State::from_list(6, {5, 5})));  TEST_NEAR(state.probability(), 0.027'777'777'8, 1e-10);
    TRY((state = State::from_list(6, {5, 6})));  TEST_NEAR(state.probability(), 0.055'555'555'6, 1e-10);
    TRY((state = State::from_list(6, {6, 6})));  TEST_NEAR(state.probability(), 0.027'777'777'8, 1e-10);

    TRY((state = State::from_list(6, {1, 1, 1})));  TEST_NEAR(state.probability(), 0.004'629'629'6, 1e-10);
    TRY((state = State::from_list(6, {1, 1, 2})));  TEST_NEAR(state.probability(), 0.013'888'888'9, 1e-10);
    TRY((state = State::from_list(6, {1, 1, 3})));  TEST_NEAR(state.probability(), 0.013'888'888'9, 1e-10);
    TRY((state = State::from_list(6, {1, 1, 4})));  TEST_NEAR(state.probability(), 0.013'888'888'9, 1e-10);
    TRY((state = State::from_list(6, {1, 1, 5})));  TEST_NEAR(state.probability(), 0.013'888'888'9, 1e-10);
    TRY((state = State::from_list(6, {1, 1, 6})));  TEST_NEAR(state.probability(), 0.013'888'888'9, 1e-10);
    TRY((state = State::from_list(6, {1, 2, 2})));  TEST_NEAR(state.probability(), 0.013'888'888'9, 1e-10);
    TRY((state = State::from_list(6, {1, 2, 3})));  TEST_NEAR(state.probability(), 0.027'777'777'8, 1e-10);
    TRY((state = State::from_list(6, {1, 2, 4})));  TEST_NEAR(state.probability(), 0.027'777'777'8, 1e-10);
    TRY((state = State::from_list(6, {1, 2, 5})));  TEST_NEAR(state.probability(), 0.027'777'777'8, 1e-10);
    TRY((state = State::from_list(6, {1, 2, 6})));  TEST_NEAR(state.probability(), 0.027'777'777'8, 1e-10);
    TRY((state = State::from_list(6, {1, 3, 3})));  TEST_NEAR(state.probability(), 0.013'888'888'9, 1e-10);
    TRY((state = State::from_list(6, {1, 3, 4})));  TEST_NEAR(state.probability(), 0.027'777'777'8, 1e-10);
    TRY((state = State::from_list(6, {1, 3, 5})));  TEST_NEAR(state.probability(), 0.027'777'777'8, 1e-10);
    TRY((state = State::from_list(6, {1, 3, 6})));  TEST_NEAR(state.probability(), 0.027'777'777'8, 1e-10);
    TRY((state = State::from_list(6, {1, 4, 4})));  TEST_NEAR(state.probability(), 0.013'888'888'9, 1e-10);
    TRY((state = State::from_list(6, {1, 4, 5})));  TEST_NEAR(state.probability(), 0.027'777'777'8, 1e-10);
    TRY((state = State::from_list(6, {1, 4, 6})));  TEST_NEAR(state.probability(), 0.027'777'777'8, 1e-10);
    TRY((state = State::from_list(6, {1, 5, 5})));  TEST_NEAR(state.probability(), 0.013'888'888'9, 1e-10);
    TRY((state = State::from_list(6, {1, 5, 6})));  TEST_NEAR(state.probability(), 0.027'777'777'8, 1e-10);
    TRY((state = State::from_list(6, {1, 6, 6})));  TEST_NEAR(state.probability(), 0.013'888'888'9, 1e-10);
    TRY((state = State::from_list(6, {2, 2, 2})));  TEST_NEAR(state.probability(), 0.004'629'629'6, 1e-10);
    TRY((state = State::from_list(6, {2, 2, 3})));  TEST_NEAR(state.probability(), 0.013'888'888'9, 1e-10);
    TRY((state = State::from_list(6, {2, 2, 4})));  TEST_NEAR(state.probability(), 0.013'888'888'9, 1e-10);
    TRY((state = State::from_list(6, {2, 2, 5})));  TEST_NEAR(state.probability(), 0.013'888'888'9, 1e-10);
    TRY((state = State::from_list(6, {2, 2, 6})));  TEST_NEAR(state.probability(), 0.013'888'888'9, 1e-10);
    TRY((state = State::from_list(6, {2, 3, 3})));  TEST_NEAR(state.probability(), 0.013'888'888'9, 1e-10);
    TRY((state = State::from_list(6, {2, 3, 4})));  TEST_NEAR(state.probability(), 0.027'777'777'8, 1e-10);
    TRY((state = State::from_list(6, {2, 3, 5})));  TEST_NEAR(state.probability(), 0.027'777'777'8, 1e-10);
    TRY((state = State::from_list(6, {2, 3, 6})));  TEST_NEAR(state.probability(), 0.027'777'777'8, 1e-10);
    TRY((state = State::from_list(6, {2, 4, 4})));  TEST_NEAR(state.probability(), 0.013'888'888'9, 1e-10);
    TRY((state = State::from_list(6, {2, 4, 5})));  TEST_NEAR(state.probability(), 0.027'777'777'8, 1e-10);
    TRY((state = State::from_list(6, {2, 4, 6})));  TEST_NEAR(state.probability(), 0.027'777'777'8, 1e-10);
    TRY((state = State::from_list(6, {2, 5, 5})));  TEST_NEAR(state.probability(), 0.013'888'888'9, 1e-10);
    TRY((state = State::from_list(6, {2, 5, 6})));  TEST_NEAR(state.probability(), 0.027'777'777'8, 1e-10);
    TRY((state = State::from_list(6, {2, 6, 6})));  TEST_NEAR(state.probability(), 0.013'888'888'9, 1e-10);
    TRY((state = State::from_list(6, {3, 3, 3})));  TEST_NEAR(state.probability(), 0.004'629'629'6, 1e-10);
    TRY((state = State::from_list(6, {3, 3, 4})));  TEST_NEAR(state.probability(), 0.013'888'888'9, 1e-10);
    TRY((state = State::from_list(6, {3, 3, 5})));  TEST_NEAR(state.probability(), 0.013'888'888'9, 1e-10);
    TRY((state = State::from_list(6, {3, 3, 6})));  TEST_NEAR(state.probability(), 0.013'888'888'9, 1e-10);
    TRY((state = State::from_list(6, {3, 4, 4})));  TEST_NEAR(state.probability(), 0.013'888'888'9, 1e-10);
    TRY((state = State::from_list(6, {3, 4, 5})));  TEST_NEAR(state.probability(), 0.027'777'777'8, 1e-10);
    TRY((state = State::from_list(6, {3, 4, 6})));  TEST_NEAR(state.probability(), 0.027'777'777'8, 1e-10);
    TRY((state = State::from_list(6, {3, 5, 5})));  TEST_NEAR(state.probability(), 0.013'888'888'9, 1e-10);
    TRY((state = State::from_list(6, {3, 5, 6})));  TEST_NEAR(state.probability(), 0.027'777'777'8, 1e-10);
    TRY((state = State::from_list(6, {3, 6, 6})));  TEST_NEAR(state.probability(), 0.013'888'888'9, 1e-10);
    TRY((state = State::from_list(6, {4, 4, 4})));  TEST_NEAR(state.probability(), 0.004'629'629'6, 1e-10);
    TRY((state = State::from_list(6, {4, 4, 5})));  TEST_NEAR(state.probability(), 0.013'888'888'9, 1e-10);
    TRY((state = State::from_list(6, {4, 4, 6})));  TEST_NEAR(state.probability(), 0.013'888'888'9, 1e-10);
    TRY((state = State::from_list(6, {4, 5, 5})));  TEST_NEAR(state.probability(), 0.013'888'888'9, 1e-10);
    TRY((state = State::from_list(6, {4, 5, 6})));  TEST_NEAR(state.probability(), 0.027'777'777'8, 1e-10);
    TRY((state = State::from_list(6, {4, 6, 6})));  TEST_NEAR(state.probability(), 0.013'888'888'9, 1e-10);
    TRY((state = State::from_list(6, {5, 5, 5})));  TEST_NEAR(state.probability(), 0.004'629'629'6, 1e-10);
    TRY((state = State::from_list(6, {5, 5, 6})));  TEST_NEAR(state.probability(), 0.013'888'888'9, 1e-10);
    TRY((state = State::from_list(6, {5, 6, 6})));  TEST_NEAR(state.probability(), 0.013'888'888'9, 1e-10);
    TRY((state = State::from_list(6, {6, 6, 6})));  TEST_NEAR(state.probability(), 0.004'629'629'6, 1e-10);

}
