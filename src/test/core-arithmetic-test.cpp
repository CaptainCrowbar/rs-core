#include "rs-core/core.hpp"
#include "rs-core/unit-test.hpp"

using namespace RS;

namespace {

    enum class MyBitmask: int {
        none     = 0,
        alpha    = 1,
        bravo    = 2,
        charlie  = 4,
        all      = 7,
    };

}

void test_rs_core_bitmask_functions() {

    int n;

    n = 0;  TEST(! has_bit(n, 0));  TEST(! has_bits(n, 0));
    n = 0;  TEST(! has_bit(n, 1));  TEST(! has_bits(n, 1));
    n = 6;  TEST(! has_bit(n, 1));  TEST(! has_bits(n, 1));
    n = 6;  TEST(has_bit(n, 2));    TEST(has_bits(n, 2));
    n = 6;  TEST(has_bit(n, 4));    TEST(has_bits(n, 4));
    n = 6;  TEST(has_bit(n, 7));    TEST(! has_bits(n, 7));

    unsigned u;

    u = 0;  TEST(! has_bit(u, 0));  TEST(! has_bits(u, 0));
    u = 0;  TEST(! has_bit(u, 1));  TEST(! has_bits(u, 1));
    u = 6;  TEST(! has_bit(u, 1));  TEST(! has_bits(u, 1));
    u = 6;  TEST(has_bit(u, 2));    TEST(has_bits(u, 2));
    u = 6;  TEST(has_bit(u, 4));    TEST(has_bits(u, 4));
    u = 6;  TEST(has_bit(u, 7));    TEST(! has_bits(u, 7));

    MyBitmask b;

    b = MyBitmask::none;   TEST(! has_bit(b, 0));  TEST(! has_bits(b, 0));
    b = MyBitmask::none;   TEST(! has_bit(b, 1));  TEST(! has_bits(b, 1));
    b = MyBitmask::bravo;  TEST(! has_bit(b, 1));  TEST(! has_bits(b, 1));
    b = MyBitmask::bravo;  TEST(has_bit(b, 2));    TEST(has_bits(b, 2));
    b = MyBitmask::bravo;  TEST(! has_bit(b, 4));  TEST(! has_bits(b, 4));
    b = MyBitmask::bravo;  TEST(has_bit(b, 7));    TEST(! has_bits(b, 7));

    b = MyBitmask::none;   TEST(! has_bit(b, MyBitmask::none));     TEST(! has_bits(b, MyBitmask::none));
    b = MyBitmask::none;   TEST(! has_bit(b, MyBitmask::alpha));    TEST(! has_bits(b, MyBitmask::alpha));
    b = MyBitmask::bravo;  TEST(! has_bit(b, MyBitmask::alpha));    TEST(! has_bits(b, MyBitmask::alpha));
    b = MyBitmask::bravo;  TEST(has_bit(b, MyBitmask::bravo));      TEST(has_bits(b, MyBitmask::bravo));
    b = MyBitmask::bravo;  TEST(! has_bit(b, MyBitmask::charlie));  TEST(! has_bits(b, MyBitmask::charlie));
    b = MyBitmask::bravo;  TEST(has_bit(b, MyBitmask::all));        TEST(! has_bits(b, MyBitmask::all));

}
