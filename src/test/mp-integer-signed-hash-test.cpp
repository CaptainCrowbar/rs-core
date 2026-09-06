#include "rs-core/mp-integer.hpp"
#include "rs-core/unit-test.hpp"
#include <unordered_set>

using namespace RS;

void test_rs_core_mp_integer_signed_hash() {

    std::unordered_set<Integer> set;

    TEST(set.empty());

    for (int i = 1; i <= 10; ++i) {
        TRY(set.insert(i));
    }

    TEST_EQUAL(set.size(), 10u);

}
