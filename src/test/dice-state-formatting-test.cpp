#include "rs-core/dice.hpp"
#include "rs-core/arithmetic.hpp"
#include "rs-core/unit-test.hpp"
#include <format>
#include <vector>

using namespace RS;
using State = DiceState<int, double>;

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
        vec.insert(vec.end(), to_unsigned(i), i);
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
