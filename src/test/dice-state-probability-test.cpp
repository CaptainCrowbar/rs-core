#include "rs-core/dice.hpp"
#include "rs-core/unit-test.hpp"

using namespace RS;
using State = DiceState<int, double>;

void test_rs_core_dice_state_probability_1() {

    State state;

    TRY((state = State::from_list(6, {1})));  TEST_NEAR(state.probability(), 0.166'666'666'7, 1e-10);
    TRY((state = State::from_list(6, {2})));  TEST_NEAR(state.probability(), 0.166'666'666'7, 1e-10);
    TRY((state = State::from_list(6, {3})));  TEST_NEAR(state.probability(), 0.166'666'666'7, 1e-10);
    TRY((state = State::from_list(6, {4})));  TEST_NEAR(state.probability(), 0.166'666'666'7, 1e-10);
    TRY((state = State::from_list(6, {5})));  TEST_NEAR(state.probability(), 0.166'666'666'7, 1e-10);
    TRY((state = State::from_list(6, {6})));  TEST_NEAR(state.probability(), 0.166'666'666'7, 1e-10);

}

void test_rs_core_dice_state_probability_2() {

    State state;

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

}

void test_rs_core_dice_state_probability_3() {

    State state;

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
