#include "rs-core/mp-integer.hpp"
#include "rs-core/unit-test.hpp"
#include <unordered_set>

using namespace RS;

void test_rs_core_mp_integer_unsigned_hash() {

    std::unordered_set<Natural> set;

    TEST(set.empty());

    for (int i = 1; i <= 10; ++i) {
        TRY(set.insert(static_cast<unsigned>(i)));
    }

    TEST_EQUAL(set.size(), 10u);

}
