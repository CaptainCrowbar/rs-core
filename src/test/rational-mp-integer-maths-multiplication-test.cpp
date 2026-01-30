#include "rs-core/rational.hpp"
#include "rs-core/mp-integer.hpp"
#include "rs-core/unit-test.hpp"

using namespace RS;
using namespace RS::Literals;

void test_rs_core_rational_mp_integer_multiplication() {

    MPRational x, y, z;

    TRY((x = {5, 6}));   TRY((y = {9, 10}));   TRY(x *= y);     TEST_EQUAL(x, (MPRational{3, 4}));
    TRY((x = {-5, 6}));  TRY((y = {9, 10}));   TRY(x *= y);     TEST_EQUAL(x, (MPRational{-3, 4}));
    TRY((x = {5, 6}));   TRY((y = {-9, 10}));  TRY(x *= y);     TEST_EQUAL(x, (MPRational{-3, 4}));
    TRY((x = {-5, 6}));  TRY((y = {-9, 10}));  TRY(x *= y);     TEST_EQUAL(x, (MPRational{3, 4}));
    TRY((x = {5, 6}));   TRY((y = {9, 10}));   TRY(z = x * y);  TEST_EQUAL(z, (MPRational{3, 4}));
    TRY((x = {-5, 6}));  TRY((y = {9, 10}));   TRY(z = x * y);  TEST_EQUAL(z, (MPRational{-3, 4}));
    TRY((x = {5, 6}));   TRY((y = {-9, 10}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{-3, 4}));
    TRY((x = {-5, 6}));  TRY((y = {-9, 10}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{3, 4}));
    TRY((x = {0, 6}));   TRY((y = {0, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (MPRational{0, 1}));
    TRY((x = {0, 6}));   TRY((y = {1, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (MPRational{0, 1}));
    TRY((x = {0, 6}));   TRY((y = {2, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (MPRational{0, 1}));
    TRY((x = {0, 6}));   TRY((y = {3, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (MPRational{0, 1}));
    TRY((x = {0, 6}));   TRY((y = {4, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (MPRational{0, 1}));
    TRY((x = {0, 6}));   TRY((y = {5, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (MPRational{0, 1}));
    TRY((x = {0, 6}));   TRY((y = {6, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (MPRational{0, 1}));
    TRY((x = {1, 6}));   TRY((y = {0, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (MPRational{0, 1}));
    TRY((x = {1, 6}));   TRY((y = {1, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (MPRational{1, 36}));
    TRY((x = {1, 6}));   TRY((y = {2, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (MPRational{1, 18}));
    TRY((x = {1, 6}));   TRY((y = {3, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (MPRational{1, 12}));
    TRY((x = {1, 6}));   TRY((y = {4, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (MPRational{1, 9}));
    TRY((x = {1, 6}));   TRY((y = {5, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (MPRational{5, 36}));
    TRY((x = {1, 6}));   TRY((y = {6, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (MPRational{1, 6}));
    TRY((x = {2, 6}));   TRY((y = {0, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (MPRational{0, 1}));
    TRY((x = {2, 6}));   TRY((y = {1, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (MPRational{1, 18}));
    TRY((x = {2, 6}));   TRY((y = {2, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (MPRational{1, 9}));
    TRY((x = {2, 6}));   TRY((y = {3, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (MPRational{1, 6}));
    TRY((x = {2, 6}));   TRY((y = {4, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (MPRational{2, 9}));
    TRY((x = {2, 6}));   TRY((y = {5, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (MPRational{5, 18}));
    TRY((x = {2, 6}));   TRY((y = {6, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (MPRational{1, 3}));
    TRY((x = {3, 6}));   TRY((y = {0, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (MPRational{0, 1}));
    TRY((x = {3, 6}));   TRY((y = {1, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (MPRational{1, 12}));
    TRY((x = {3, 6}));   TRY((y = {2, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (MPRational{1, 6}));
    TRY((x = {3, 6}));   TRY((y = {3, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (MPRational{1, 4}));
    TRY((x = {3, 6}));   TRY((y = {4, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (MPRational{1, 3}));
    TRY((x = {3, 6}));   TRY((y = {5, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (MPRational{5, 12}));
    TRY((x = {3, 6}));   TRY((y = {6, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (MPRational{1, 2}));
    TRY((x = {4, 6}));   TRY((y = {0, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (MPRational{0, 1}));
    TRY((x = {4, 6}));   TRY((y = {1, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (MPRational{1, 9}));
    TRY((x = {4, 6}));   TRY((y = {2, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (MPRational{2, 9}));
    TRY((x = {4, 6}));   TRY((y = {3, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (MPRational{1, 3}));
    TRY((x = {4, 6}));   TRY((y = {4, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (MPRational{4, 9}));
    TRY((x = {4, 6}));   TRY((y = {5, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (MPRational{5, 9}));
    TRY((x = {4, 6}));   TRY((y = {6, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (MPRational{2, 3}));
    TRY((x = {5, 6}));   TRY((y = {0, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (MPRational{0, 1}));
    TRY((x = {5, 6}));   TRY((y = {1, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (MPRational{5, 36}));
    TRY((x = {5, 6}));   TRY((y = {2, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (MPRational{5, 18}));
    TRY((x = {5, 6}));   TRY((y = {3, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (MPRational{5, 12}));
    TRY((x = {5, 6}));   TRY((y = {4, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (MPRational{5, 9}));
    TRY((x = {5, 6}));   TRY((y = {5, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (MPRational{25, 36}));
    TRY((x = {5, 6}));   TRY((y = {6, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (MPRational{5, 6}));
    TRY((x = {6, 6}));   TRY((y = {0, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (MPRational{0, 1}));
    TRY((x = {6, 6}));   TRY((y = {1, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (MPRational{1, 6}));
    TRY((x = {6, 6}));   TRY((y = {2, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (MPRational{1, 3}));
    TRY((x = {6, 6}));   TRY((y = {3, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (MPRational{1, 2}));
    TRY((x = {6, 6}));   TRY((y = {4, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (MPRational{2, 3}));
    TRY((x = {6, 6}));   TRY((y = {5, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (MPRational{5, 6}));
    TRY((x = {6, 6}));   TRY((y = {6, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (MPRational{1, 1}));

}
