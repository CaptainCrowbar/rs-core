#include "rs-core/rational.hpp"
#include "rs-core/mp-integer.hpp"
#include "rs-core/unit-test.hpp"

using namespace RS;
using namespace RS::Literals;

void test_rs_core_rational_mp_integer_division() {

    MPRational x, y, z;

    TRY((x = {5, 6}));   TRY((y = {9, 10}));   TRY(x /= y);     TEST_EQUAL(x, (MPRational{25, 27}));
    TRY((x = {-5, 6}));  TRY((y = {9, 10}));   TRY(x /= y);     TEST_EQUAL(x, (MPRational{-25, 27}));
    TRY((x = {5, 6}));   TRY((y = {-9, 10}));  TRY(x /= y);     TEST_EQUAL(x, (MPRational{-25, 27}));
    TRY((x = {-5, 6}));  TRY((y = {-9, 10}));  TRY(x /= y);     TEST_EQUAL(x, (MPRational{25, 27}));
    TRY((x = {5, 6}));   TRY((y = {9, 10}));   TRY(z = x / y);  TEST_EQUAL(z, (MPRational{25, 27}));
    TRY((x = {-5, 6}));  TRY((y = {9, 10}));   TRY(z = x / y);  TEST_EQUAL(z, (MPRational{-25, 27}));
    TRY((x = {5, 6}));   TRY((y = {-9, 10}));  TRY(z = x / y);  TEST_EQUAL(z, (MPRational{-25, 27}));
    TRY((x = {-5, 6}));  TRY((y = {-9, 10}));  TRY(z = x / y);  TEST_EQUAL(z, (MPRational{25, 27}));
    TRY((x = {0, 6}));   TRY((y = {1, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{0, 1}));
    TRY((x = {0, 6}));   TRY((y = {2, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{0, 1}));
    TRY((x = {0, 6}));   TRY((y = {3, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{0, 1}));
    TRY((x = {0, 6}));   TRY((y = {4, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{0, 1}));
    TRY((x = {0, 6}));   TRY((y = {5, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{0, 1}));
    TRY((x = {0, 6}));   TRY((y = {6, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{0, 1}));
    TRY((x = {1, 6}));   TRY((y = {1, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{1, 1}));
    TRY((x = {1, 6}));   TRY((y = {2, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{1, 2}));
    TRY((x = {1, 6}));   TRY((y = {3, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{1, 3}));
    TRY((x = {1, 6}));   TRY((y = {4, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{1, 4}));
    TRY((x = {1, 6}));   TRY((y = {5, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{1, 5}));
    TRY((x = {1, 6}));   TRY((y = {6, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{1, 6}));
    TRY((x = {2, 6}));   TRY((y = {1, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{2, 1}));
    TRY((x = {2, 6}));   TRY((y = {2, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{1, 1}));
    TRY((x = {2, 6}));   TRY((y = {3, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{2, 3}));
    TRY((x = {2, 6}));   TRY((y = {4, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{1, 2}));
    TRY((x = {2, 6}));   TRY((y = {5, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{2, 5}));
    TRY((x = {2, 6}));   TRY((y = {6, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{1, 3}));
    TRY((x = {3, 6}));   TRY((y = {1, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{3, 1}));
    TRY((x = {3, 6}));   TRY((y = {2, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{3, 2}));
    TRY((x = {3, 6}));   TRY((y = {3, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{1, 1}));
    TRY((x = {3, 6}));   TRY((y = {4, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{3, 4}));
    TRY((x = {3, 6}));   TRY((y = {5, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{3, 5}));
    TRY((x = {3, 6}));   TRY((y = {6, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{1, 2}));
    TRY((x = {4, 6}));   TRY((y = {1, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{4, 1}));
    TRY((x = {4, 6}));   TRY((y = {2, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{2, 1}));
    TRY((x = {4, 6}));   TRY((y = {3, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{4, 3}));
    TRY((x = {4, 6}));   TRY((y = {4, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{1, 1}));
    TRY((x = {4, 6}));   TRY((y = {5, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{4, 5}));
    TRY((x = {4, 6}));   TRY((y = {6, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{2, 3}));
    TRY((x = {5, 6}));   TRY((y = {1, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{5, 1}));
    TRY((x = {5, 6}));   TRY((y = {2, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{5, 2}));
    TRY((x = {5, 6}));   TRY((y = {3, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{5, 3}));
    TRY((x = {5, 6}));   TRY((y = {4, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{5, 4}));
    TRY((x = {5, 6}));   TRY((y = {5, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{1, 1}));
    TRY((x = {5, 6}));   TRY((y = {6, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{5, 6}));
    TRY((x = {6, 6}));   TRY((y = {1, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{6, 1}));
    TRY((x = {6, 6}));   TRY((y = {2, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{3, 1}));
    TRY((x = {6, 6}));   TRY((y = {3, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{2, 1}));
    TRY((x = {6, 6}));   TRY((y = {4, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{3, 2}));
    TRY((x = {6, 6}));   TRY((y = {5, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{6, 5}));
    TRY((x = {6, 6}));   TRY((y = {6, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (MPRational{1, 1}));

}
