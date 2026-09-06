#include "rs-core/rational.hpp"
#include "rs-core/unit-test.hpp"

using namespace RS;

void test_rs_core_rational_int_arithmetic_addition() {

    IntRational x, y, z;

    TRY((x = {5, 6}));   TRY((y = {9, 10}));   TRY(x += y);     TEST_EQUAL(x, (IntRational{26, 15}));
    TRY((x = {-5, 6}));  TRY((y = {9, 10}));   TRY(x += y);     TEST_EQUAL(x, (IntRational{1, 15}));
    TRY((x = {5, 6}));   TRY((y = {-9, 10}));  TRY(x += y);     TEST_EQUAL(x, (IntRational{-1, 15}));
    TRY((x = {-5, 6}));  TRY((y = {-9, 10}));  TRY(x += y);     TEST_EQUAL(x, (IntRational{-26, 15}));
    TRY((x = {5, 6}));   TRY((y = {9, 10}));   TRY(z = x + y);  TEST_EQUAL(z, (IntRational{26, 15}));
    TRY((x = {-5, 6}));  TRY((y = {9, 10}));   TRY(z = x + y);  TEST_EQUAL(z, (IntRational{1, 15}));
    TRY((x = {5, 6}));   TRY((y = {-9, 10}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{-1, 15}));
    TRY((x = {-5, 6}));  TRY((y = {-9, 10}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{-26, 15}));
    TRY((x = {0, 6}));   TRY((y = {0, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {0, 6}));   TRY((y = {1, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (IntRational{1, 6}));
    TRY((x = {0, 6}));   TRY((y = {2, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (IntRational{1, 3}));
    TRY((x = {0, 6}));   TRY((y = {3, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (IntRational{1, 2}));
    TRY((x = {0, 6}));   TRY((y = {4, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (IntRational{2, 3}));
    TRY((x = {0, 6}));   TRY((y = {5, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (IntRational{5, 6}));
    TRY((x = {0, 6}));   TRY((y = {6, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (IntRational{1, 1}));
    TRY((x = {1, 6}));   TRY((y = {0, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (IntRational{1, 6}));
    TRY((x = {1, 6}));   TRY((y = {1, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (IntRational{1, 3}));
    TRY((x = {1, 6}));   TRY((y = {2, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (IntRational{1, 2}));
    TRY((x = {1, 6}));   TRY((y = {3, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (IntRational{2, 3}));
    TRY((x = {1, 6}));   TRY((y = {4, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (IntRational{5, 6}));
    TRY((x = {1, 6}));   TRY((y = {5, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (IntRational{1, 1}));
    TRY((x = {1, 6}));   TRY((y = {6, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (IntRational{7, 6}));
    TRY((x = {2, 6}));   TRY((y = {0, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (IntRational{1, 3}));
    TRY((x = {2, 6}));   TRY((y = {1, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (IntRational{1, 2}));
    TRY((x = {2, 6}));   TRY((y = {2, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (IntRational{2, 3}));
    TRY((x = {2, 6}));   TRY((y = {3, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (IntRational{5, 6}));
    TRY((x = {2, 6}));   TRY((y = {4, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (IntRational{1, 1}));
    TRY((x = {2, 6}));   TRY((y = {5, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (IntRational{7, 6}));
    TRY((x = {2, 6}));   TRY((y = {6, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (IntRational{4, 3}));
    TRY((x = {3, 6}));   TRY((y = {0, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (IntRational{1, 2}));
    TRY((x = {3, 6}));   TRY((y = {1, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (IntRational{2, 3}));
    TRY((x = {3, 6}));   TRY((y = {2, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (IntRational{5, 6}));
    TRY((x = {3, 6}));   TRY((y = {3, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (IntRational{1, 1}));
    TRY((x = {3, 6}));   TRY((y = {4, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (IntRational{7, 6}));
    TRY((x = {3, 6}));   TRY((y = {5, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (IntRational{4, 3}));
    TRY((x = {3, 6}));   TRY((y = {6, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (IntRational{3, 2}));
    TRY((x = {4, 6}));   TRY((y = {0, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (IntRational{2, 3}));
    TRY((x = {4, 6}));   TRY((y = {1, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (IntRational{5, 6}));
    TRY((x = {4, 6}));   TRY((y = {2, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (IntRational{1, 1}));
    TRY((x = {4, 6}));   TRY((y = {3, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (IntRational{7, 6}));
    TRY((x = {4, 6}));   TRY((y = {4, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (IntRational{4, 3}));
    TRY((x = {4, 6}));   TRY((y = {5, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (IntRational{3, 2}));
    TRY((x = {4, 6}));   TRY((y = {6, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (IntRational{5, 3}));
    TRY((x = {5, 6}));   TRY((y = {0, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (IntRational{5, 6}));
    TRY((x = {5, 6}));   TRY((y = {1, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (IntRational{1, 1}));
    TRY((x = {5, 6}));   TRY((y = {2, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (IntRational{7, 6}));
    TRY((x = {5, 6}));   TRY((y = {3, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (IntRational{4, 3}));
    TRY((x = {5, 6}));   TRY((y = {4, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (IntRational{3, 2}));
    TRY((x = {5, 6}));   TRY((y = {5, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (IntRational{5, 3}));
    TRY((x = {5, 6}));   TRY((y = {6, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (IntRational{11, 6}));
    TRY((x = {6, 6}));   TRY((y = {0, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (IntRational{1, 1}));
    TRY((x = {6, 6}));   TRY((y = {1, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (IntRational{7, 6}));
    TRY((x = {6, 6}));   TRY((y = {2, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (IntRational{4, 3}));
    TRY((x = {6, 6}));   TRY((y = {3, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (IntRational{3, 2}));
    TRY((x = {6, 6}));   TRY((y = {4, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (IntRational{5, 3}));
    TRY((x = {6, 6}));   TRY((y = {5, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (IntRational{11, 6}));
    TRY((x = {6, 6}));   TRY((y = {6, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (IntRational{2, 1}));

}

void test_rs_core_rational_int_arithmetic_subtraction() {

    IntRational x, y, z;

    TRY((x = {5, 6}));   TRY((y = {9, 10}));   TRY(x -= y);     TEST_EQUAL(x, (IntRational{-1, 15}));
    TRY((x = {-5, 6}));  TRY((y = {9, 10}));   TRY(x -= y);     TEST_EQUAL(x, (IntRational{-26, 15}));
    TRY((x = {5, 6}));   TRY((y = {-9, 10}));  TRY(x -= y);     TEST_EQUAL(x, (IntRational{26, 15}));
    TRY((x = {-5, 6}));  TRY((y = {-9, 10}));  TRY(x -= y);     TEST_EQUAL(x, (IntRational{1, 15}));
    TRY((x = {5, 6}));   TRY((y = {9, 10}));   TRY(z = x - y);  TEST_EQUAL(z, (IntRational{-1, 15}));
    TRY((x = {-5, 6}));  TRY((y = {9, 10}));   TRY(z = x - y);  TEST_EQUAL(z, (IntRational{-26, 15}));
    TRY((x = {5, 6}));   TRY((y = {-9, 10}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{26, 15}));
    TRY((x = {-5, 6}));  TRY((y = {-9, 10}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{1, 15}));
    TRY((x = {0, 6}));   TRY((y = {0, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {0, 6}));   TRY((y = {1, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (IntRational{-1, 6}));
    TRY((x = {0, 6}));   TRY((y = {2, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (IntRational{-1, 3}));
    TRY((x = {0, 6}));   TRY((y = {3, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (IntRational{-1, 2}));
    TRY((x = {0, 6}));   TRY((y = {4, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (IntRational{-2, 3}));
    TRY((x = {0, 6}));   TRY((y = {5, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (IntRational{-5, 6}));
    TRY((x = {0, 6}));   TRY((y = {6, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (IntRational{-1, 1}));
    TRY((x = {1, 6}));   TRY((y = {0, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (IntRational{1, 6}));
    TRY((x = {1, 6}));   TRY((y = {1, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {1, 6}));   TRY((y = {2, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (IntRational{-1, 6}));
    TRY((x = {1, 6}));   TRY((y = {3, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (IntRational{-1, 3}));
    TRY((x = {1, 6}));   TRY((y = {4, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (IntRational{-1, 2}));
    TRY((x = {1, 6}));   TRY((y = {5, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (IntRational{-2, 3}));
    TRY((x = {1, 6}));   TRY((y = {6, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (IntRational{-5, 6}));
    TRY((x = {2, 6}));   TRY((y = {0, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (IntRational{1, 3}));
    TRY((x = {2, 6}));   TRY((y = {1, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (IntRational{1, 6}));
    TRY((x = {2, 6}));   TRY((y = {2, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {2, 6}));   TRY((y = {3, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (IntRational{-1, 6}));
    TRY((x = {2, 6}));   TRY((y = {4, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (IntRational{-1, 3}));
    TRY((x = {2, 6}));   TRY((y = {5, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (IntRational{-1, 2}));
    TRY((x = {2, 6}));   TRY((y = {6, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (IntRational{-2, 3}));
    TRY((x = {3, 6}));   TRY((y = {0, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (IntRational{1, 2}));
    TRY((x = {3, 6}));   TRY((y = {1, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (IntRational{1, 3}));
    TRY((x = {3, 6}));   TRY((y = {2, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (IntRational{1, 6}));
    TRY((x = {3, 6}));   TRY((y = {3, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {3, 6}));   TRY((y = {4, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (IntRational{-1, 6}));
    TRY((x = {3, 6}));   TRY((y = {5, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (IntRational{-1, 3}));
    TRY((x = {3, 6}));   TRY((y = {6, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (IntRational{-1, 2}));
    TRY((x = {4, 6}));   TRY((y = {0, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (IntRational{2, 3}));
    TRY((x = {4, 6}));   TRY((y = {1, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (IntRational{1, 2}));
    TRY((x = {4, 6}));   TRY((y = {2, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (IntRational{1, 3}));
    TRY((x = {4, 6}));   TRY((y = {3, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (IntRational{1, 6}));
    TRY((x = {4, 6}));   TRY((y = {4, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {4, 6}));   TRY((y = {5, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (IntRational{-1, 6}));
    TRY((x = {4, 6}));   TRY((y = {6, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (IntRational{-1, 3}));
    TRY((x = {5, 6}));   TRY((y = {0, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (IntRational{5, 6}));
    TRY((x = {5, 6}));   TRY((y = {1, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (IntRational{2, 3}));
    TRY((x = {5, 6}));   TRY((y = {2, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (IntRational{1, 2}));
    TRY((x = {5, 6}));   TRY((y = {3, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (IntRational{1, 3}));
    TRY((x = {5, 6}));   TRY((y = {4, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (IntRational{1, 6}));
    TRY((x = {5, 6}));   TRY((y = {5, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {5, 6}));   TRY((y = {6, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (IntRational{-1, 6}));
    TRY((x = {6, 6}));   TRY((y = {0, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (IntRational{1, 1}));
    TRY((x = {6, 6}));   TRY((y = {1, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (IntRational{5, 6}));
    TRY((x = {6, 6}));   TRY((y = {2, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (IntRational{2, 3}));
    TRY((x = {6, 6}));   TRY((y = {3, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (IntRational{1, 2}));
    TRY((x = {6, 6}));   TRY((y = {4, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (IntRational{1, 3}));
    TRY((x = {6, 6}));   TRY((y = {5, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (IntRational{1, 6}));
    TRY((x = {6, 6}));   TRY((y = {6, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (IntRational{0, 1}));

}

void test_rs_core_rational_int_arithmetic_multiplication() {

    IntRational x, y, z;

    TRY((x = {5, 6}));   TRY((y = {9, 10}));   TRY(x *= y);     TEST_EQUAL(x, (IntRational{3, 4}));
    TRY((x = {-5, 6}));  TRY((y = {9, 10}));   TRY(x *= y);     TEST_EQUAL(x, (IntRational{-3, 4}));
    TRY((x = {5, 6}));   TRY((y = {-9, 10}));  TRY(x *= y);     TEST_EQUAL(x, (IntRational{-3, 4}));
    TRY((x = {-5, 6}));  TRY((y = {-9, 10}));  TRY(x *= y);     TEST_EQUAL(x, (IntRational{3, 4}));
    TRY((x = {5, 6}));   TRY((y = {9, 10}));   TRY(z = x * y);  TEST_EQUAL(z, (IntRational{3, 4}));
    TRY((x = {-5, 6}));  TRY((y = {9, 10}));   TRY(z = x * y);  TEST_EQUAL(z, (IntRational{-3, 4}));
    TRY((x = {5, 6}));   TRY((y = {-9, 10}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{-3, 4}));
    TRY((x = {-5, 6}));  TRY((y = {-9, 10}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{3, 4}));
    TRY((x = {0, 6}));   TRY((y = {0, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {0, 6}));   TRY((y = {1, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {0, 6}));   TRY((y = {2, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {0, 6}));   TRY((y = {3, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {0, 6}));   TRY((y = {4, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {0, 6}));   TRY((y = {5, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {0, 6}));   TRY((y = {6, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {1, 6}));   TRY((y = {0, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {1, 6}));   TRY((y = {1, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (IntRational{1, 36}));
    TRY((x = {1, 6}));   TRY((y = {2, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (IntRational{1, 18}));
    TRY((x = {1, 6}));   TRY((y = {3, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (IntRational{1, 12}));
    TRY((x = {1, 6}));   TRY((y = {4, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (IntRational{1, 9}));
    TRY((x = {1, 6}));   TRY((y = {5, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (IntRational{5, 36}));
    TRY((x = {1, 6}));   TRY((y = {6, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (IntRational{1, 6}));
    TRY((x = {2, 6}));   TRY((y = {0, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {2, 6}));   TRY((y = {1, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (IntRational{1, 18}));
    TRY((x = {2, 6}));   TRY((y = {2, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (IntRational{1, 9}));
    TRY((x = {2, 6}));   TRY((y = {3, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (IntRational{1, 6}));
    TRY((x = {2, 6}));   TRY((y = {4, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (IntRational{2, 9}));
    TRY((x = {2, 6}));   TRY((y = {5, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (IntRational{5, 18}));
    TRY((x = {2, 6}));   TRY((y = {6, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (IntRational{1, 3}));
    TRY((x = {3, 6}));   TRY((y = {0, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {3, 6}));   TRY((y = {1, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (IntRational{1, 12}));
    TRY((x = {3, 6}));   TRY((y = {2, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (IntRational{1, 6}));
    TRY((x = {3, 6}));   TRY((y = {3, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (IntRational{1, 4}));
    TRY((x = {3, 6}));   TRY((y = {4, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (IntRational{1, 3}));
    TRY((x = {3, 6}));   TRY((y = {5, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (IntRational{5, 12}));
    TRY((x = {3, 6}));   TRY((y = {6, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (IntRational{1, 2}));
    TRY((x = {4, 6}));   TRY((y = {0, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {4, 6}));   TRY((y = {1, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (IntRational{1, 9}));
    TRY((x = {4, 6}));   TRY((y = {2, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (IntRational{2, 9}));
    TRY((x = {4, 6}));   TRY((y = {3, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (IntRational{1, 3}));
    TRY((x = {4, 6}));   TRY((y = {4, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (IntRational{4, 9}));
    TRY((x = {4, 6}));   TRY((y = {5, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (IntRational{5, 9}));
    TRY((x = {4, 6}));   TRY((y = {6, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (IntRational{2, 3}));
    TRY((x = {5, 6}));   TRY((y = {0, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {5, 6}));   TRY((y = {1, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (IntRational{5, 36}));
    TRY((x = {5, 6}));   TRY((y = {2, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (IntRational{5, 18}));
    TRY((x = {5, 6}));   TRY((y = {3, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (IntRational{5, 12}));
    TRY((x = {5, 6}));   TRY((y = {4, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (IntRational{5, 9}));
    TRY((x = {5, 6}));   TRY((y = {5, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (IntRational{25, 36}));
    TRY((x = {5, 6}));   TRY((y = {6, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (IntRational{5, 6}));
    TRY((x = {6, 6}));   TRY((y = {0, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {6, 6}));   TRY((y = {1, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (IntRational{1, 6}));
    TRY((x = {6, 6}));   TRY((y = {2, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (IntRational{1, 3}));
    TRY((x = {6, 6}));   TRY((y = {3, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (IntRational{1, 2}));
    TRY((x = {6, 6}));   TRY((y = {4, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (IntRational{2, 3}));
    TRY((x = {6, 6}));   TRY((y = {5, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (IntRational{5, 6}));
    TRY((x = {6, 6}));   TRY((y = {6, 6}));    TRY(z = x * y);  TEST_EQUAL(z, (IntRational{1, 1}));

}

void test_rs_core_rational_int_arithmetic_division() {

    IntRational x, y, z;

    TRY((x = {5, 6}));   TRY((y = {9, 10}));   TRY(x /= y);     TEST_EQUAL(x, (IntRational{25, 27}));
    TRY((x = {-5, 6}));  TRY((y = {9, 10}));   TRY(x /= y);     TEST_EQUAL(x, (IntRational{-25, 27}));
    TRY((x = {5, 6}));   TRY((y = {-9, 10}));  TRY(x /= y);     TEST_EQUAL(x, (IntRational{-25, 27}));
    TRY((x = {-5, 6}));  TRY((y = {-9, 10}));  TRY(x /= y);     TEST_EQUAL(x, (IntRational{25, 27}));
    TRY((x = {5, 6}));   TRY((y = {9, 10}));   TRY(z = x / y);  TEST_EQUAL(z, (IntRational{25, 27}));
    TRY((x = {-5, 6}));  TRY((y = {9, 10}));   TRY(z = x / y);  TEST_EQUAL(z, (IntRational{-25, 27}));
    TRY((x = {5, 6}));   TRY((y = {-9, 10}));  TRY(z = x / y);  TEST_EQUAL(z, (IntRational{-25, 27}));
    TRY((x = {-5, 6}));  TRY((y = {-9, 10}));  TRY(z = x / y);  TEST_EQUAL(z, (IntRational{25, 27}));
    TRY((x = {0, 6}));   TRY((y = {1, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {0, 6}));   TRY((y = {2, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {0, 6}));   TRY((y = {3, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {0, 6}));   TRY((y = {4, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {0, 6}));   TRY((y = {5, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {0, 6}));   TRY((y = {6, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {1, 6}));   TRY((y = {1, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (IntRational{1, 1}));
    TRY((x = {1, 6}));   TRY((y = {2, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (IntRational{1, 2}));
    TRY((x = {1, 6}));   TRY((y = {3, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (IntRational{1, 3}));
    TRY((x = {1, 6}));   TRY((y = {4, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (IntRational{1, 4}));
    TRY((x = {1, 6}));   TRY((y = {5, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (IntRational{1, 5}));
    TRY((x = {1, 6}));   TRY((y = {6, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (IntRational{1, 6}));
    TRY((x = {2, 6}));   TRY((y = {1, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (IntRational{2, 1}));
    TRY((x = {2, 6}));   TRY((y = {2, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (IntRational{1, 1}));
    TRY((x = {2, 6}));   TRY((y = {3, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (IntRational{2, 3}));
    TRY((x = {2, 6}));   TRY((y = {4, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (IntRational{1, 2}));
    TRY((x = {2, 6}));   TRY((y = {5, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (IntRational{2, 5}));
    TRY((x = {2, 6}));   TRY((y = {6, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (IntRational{1, 3}));
    TRY((x = {3, 6}));   TRY((y = {1, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (IntRational{3, 1}));
    TRY((x = {3, 6}));   TRY((y = {2, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (IntRational{3, 2}));
    TRY((x = {3, 6}));   TRY((y = {3, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (IntRational{1, 1}));
    TRY((x = {3, 6}));   TRY((y = {4, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (IntRational{3, 4}));
    TRY((x = {3, 6}));   TRY((y = {5, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (IntRational{3, 5}));
    TRY((x = {3, 6}));   TRY((y = {6, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (IntRational{1, 2}));
    TRY((x = {4, 6}));   TRY((y = {1, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (IntRational{4, 1}));
    TRY((x = {4, 6}));   TRY((y = {2, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (IntRational{2, 1}));
    TRY((x = {4, 6}));   TRY((y = {3, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (IntRational{4, 3}));
    TRY((x = {4, 6}));   TRY((y = {4, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (IntRational{1, 1}));
    TRY((x = {4, 6}));   TRY((y = {5, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (IntRational{4, 5}));
    TRY((x = {4, 6}));   TRY((y = {6, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (IntRational{2, 3}));
    TRY((x = {5, 6}));   TRY((y = {1, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (IntRational{5, 1}));
    TRY((x = {5, 6}));   TRY((y = {2, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (IntRational{5, 2}));
    TRY((x = {5, 6}));   TRY((y = {3, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (IntRational{5, 3}));
    TRY((x = {5, 6}));   TRY((y = {4, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (IntRational{5, 4}));
    TRY((x = {5, 6}));   TRY((y = {5, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (IntRational{1, 1}));
    TRY((x = {5, 6}));   TRY((y = {6, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (IntRational{5, 6}));
    TRY((x = {6, 6}));   TRY((y = {1, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (IntRational{6, 1}));
    TRY((x = {6, 6}));   TRY((y = {2, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (IntRational{3, 1}));
    TRY((x = {6, 6}));   TRY((y = {3, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (IntRational{2, 1}));
    TRY((x = {6, 6}));   TRY((y = {4, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (IntRational{3, 2}));
    TRY((x = {6, 6}));   TRY((y = {5, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (IntRational{6, 5}));
    TRY((x = {6, 6}));   TRY((y = {6, 6}));    TRY(z = x / y);  TEST_EQUAL(z, (IntRational{1, 1}));

}
