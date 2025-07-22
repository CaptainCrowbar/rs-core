#include "rs-core/rational.hpp"
#include "rs-core/mp-integer.hpp"
#include "rs-core/unit-test.hpp"

using namespace RS;
using namespace RS::Literals;

void test_rs_core_rational_mp_integer_division() {

    MPRational x, y, z;

    TRY((x = {5_Z, 6_Z}));   TRY((y = {9_Z, 10_Z}));   TRY(x /= y);     TEST_EQUAL(x, (MPRational{25_Z, 27_Z}));
    TRY((x = {-5_Z, 6_Z}));  TRY((y = {9_Z, 10_Z}));   TRY(x /= y);     TEST_EQUAL(x, (MPRational{-25_Z, 27_Z}));
    TRY((x = {5_Z, 6_Z}));   TRY((y = {-9_Z, 10_Z}));  TRY(x /= y);     TEST_EQUAL(x, (MPRational{-25_Z, 27_Z}));
    TRY((x = {-5_Z, 6_Z}));  TRY((y = {-9_Z, 10_Z}));  TRY(x /= y);     TEST_EQUAL(x, (MPRational{25_Z, 27_Z}));
    TRY((x = {5_Z, 6_Z}));   TRY((y = {9_Z, 10_Z}));   TRY(z = x / y);  TEST_EQUAL(z, (MPRational{25_Z, 27_Z}));
    TRY((x = {-5_Z, 6_Z}));  TRY((y = {9_Z, 10_Z}));   TRY(z = x / y);  TEST_EQUAL(z, (MPRational{-25_Z, 27_Z}));
    TRY((x = {5_Z, 6_Z}));   TRY((y = {-9_Z, 10_Z}));  TRY(z = x / y);  TEST_EQUAL(z, (MPRational{-25_Z, 27_Z}));
    TRY((x = {-5_Z, 6_Z}));  TRY((y = {-9_Z, 10_Z}));  TRY(z = x / y);  TEST_EQUAL(z, (MPRational{25_Z, 27_Z}));
    TRY((x = {0_Z, 6_Z}));   TRY((y = {1_Z, 6_Z}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{0_Z, 1_Z}));
    TRY((x = {0_Z, 6_Z}));   TRY((y = {2_Z, 6_Z}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{0_Z, 1_Z}));
    TRY((x = {0_Z, 6_Z}));   TRY((y = {3_Z, 6_Z}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{0_Z, 1_Z}));
    TRY((x = {0_Z, 6_Z}));   TRY((y = {4_Z, 6_Z}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{0_Z, 1_Z}));
    TRY((x = {0_Z, 6_Z}));   TRY((y = {5_Z, 6_Z}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{0_Z, 1_Z}));
    TRY((x = {0_Z, 6_Z}));   TRY((y = {6_Z, 6_Z}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{0_Z, 1_Z}));
    TRY((x = {1_Z, 6_Z}));   TRY((y = {1_Z, 6_Z}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{1_Z, 1_Z}));
    TRY((x = {1_Z, 6_Z}));   TRY((y = {2_Z, 6_Z}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{1_Z, 2_Z}));
    TRY((x = {1_Z, 6_Z}));   TRY((y = {3_Z, 6_Z}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{1_Z, 3_Z}));
    TRY((x = {1_Z, 6_Z}));   TRY((y = {4_Z, 6_Z}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{1_Z, 4_Z}));
    TRY((x = {1_Z, 6_Z}));   TRY((y = {5_Z, 6_Z}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{1_Z, 5_Z}));
    TRY((x = {1_Z, 6_Z}));   TRY((y = {6_Z, 6_Z}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{1_Z, 6_Z}));
    TRY((x = {2_Z, 6_Z}));   TRY((y = {1_Z, 6_Z}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{2_Z, 1_Z}));
    TRY((x = {2_Z, 6_Z}));   TRY((y = {2_Z, 6_Z}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{1_Z, 1_Z}));
    TRY((x = {2_Z, 6_Z}));   TRY((y = {3_Z, 6_Z}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{2_Z, 3_Z}));
    TRY((x = {2_Z, 6_Z}));   TRY((y = {4_Z, 6_Z}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{1_Z, 2_Z}));
    TRY((x = {2_Z, 6_Z}));   TRY((y = {5_Z, 6_Z}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{2_Z, 5_Z}));
    TRY((x = {2_Z, 6_Z}));   TRY((y = {6_Z, 6_Z}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{1_Z, 3_Z}));
    TRY((x = {3_Z, 6_Z}));   TRY((y = {1_Z, 6_Z}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{3_Z, 1_Z}));
    TRY((x = {3_Z, 6_Z}));   TRY((y = {2_Z, 6_Z}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{3_Z, 2_Z}));
    TRY((x = {3_Z, 6_Z}));   TRY((y = {3_Z, 6_Z}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{1_Z, 1_Z}));
    TRY((x = {3_Z, 6_Z}));   TRY((y = {4_Z, 6_Z}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{3_Z, 4_Z}));
    TRY((x = {3_Z, 6_Z}));   TRY((y = {5_Z, 6_Z}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{3_Z, 5_Z}));
    TRY((x = {3_Z, 6_Z}));   TRY((y = {6_Z, 6_Z}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{1_Z, 2_Z}));
    TRY((x = {4_Z, 6_Z}));   TRY((y = {1_Z, 6_Z}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{4_Z, 1_Z}));
    TRY((x = {4_Z, 6_Z}));   TRY((y = {2_Z, 6_Z}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{2_Z, 1_Z}));
    TRY((x = {4_Z, 6_Z}));   TRY((y = {3_Z, 6_Z}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{4_Z, 3_Z}));
    TRY((x = {4_Z, 6_Z}));   TRY((y = {4_Z, 6_Z}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{1_Z, 1_Z}));
    TRY((x = {4_Z, 6_Z}));   TRY((y = {5_Z, 6_Z}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{4_Z, 5_Z}));
    TRY((x = {4_Z, 6_Z}));   TRY((y = {6_Z, 6_Z}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{2_Z, 3_Z}));
    TRY((x = {5_Z, 6_Z}));   TRY((y = {1_Z, 6_Z}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{5_Z, 1_Z}));
    TRY((x = {5_Z, 6_Z}));   TRY((y = {2_Z, 6_Z}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{5_Z, 2_Z}));
    TRY((x = {5_Z, 6_Z}));   TRY((y = {3_Z, 6_Z}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{5_Z, 3_Z}));
    TRY((x = {5_Z, 6_Z}));   TRY((y = {4_Z, 6_Z}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{5_Z, 4_Z}));
    TRY((x = {5_Z, 6_Z}));   TRY((y = {5_Z, 6_Z}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{1_Z, 1_Z}));
    TRY((x = {5_Z, 6_Z}));   TRY((y = {6_Z, 6_Z}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{5_Z, 6_Z}));
    TRY((x = {6_Z, 6_Z}));   TRY((y = {1_Z, 6_Z}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{6_Z, 1_Z}));
    TRY((x = {6_Z, 6_Z}));   TRY((y = {2_Z, 6_Z}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{3_Z, 1_Z}));
    TRY((x = {6_Z, 6_Z}));   TRY((y = {3_Z, 6_Z}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{2_Z, 1_Z}));
    TRY((x = {6_Z, 6_Z}));   TRY((y = {4_Z, 6_Z}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{3_Z, 2_Z}));
    TRY((x = {6_Z, 6_Z}));   TRY((y = {5_Z, 6_Z}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{6_Z, 5_Z}));
    TRY((x = {6_Z, 6_Z}));   TRY((y = {6_Z, 6_Z}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{1_Z, 1_Z}));

}
