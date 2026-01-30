#include "rs-core/rational.hpp"
#include "rs-core/mp-integer.hpp"
#include "rs-core/unit-test.hpp"

using namespace RS;
using namespace RS::Literals;

void test_rs_core_rational_mp_integer_addition() {

    MPRational x, y, z;

    TRY((x = {5, 6}));   TRY((y = {9, 10}));   TRY(x += y);     TEST_EQUAL(x, (MPRational{26, 15}));
    TRY((x = {-5, 6}));  TRY((y = {9, 10}));   TRY(x += y);     TEST_EQUAL(x, (MPRational{1, 15}));
    TRY((x = {5, 6}));   TRY((y = {-9, 10}));  TRY(x += y);     TEST_EQUAL(x, (MPRational{-1, 15}));
    TRY((x = {-5, 6}));  TRY((y = {-9, 10}));  TRY(x += y);     TEST_EQUAL(x, (MPRational{-26, 15}));
    TRY((x = {5, 6}));   TRY((y = {9, 10}));   TRY(z = x + y);  TEST_EQUAL(z, (MPRational{26, 15}));
    TRY((x = {-5, 6}));  TRY((y = {9, 10}));   TRY(z = x + y);  TEST_EQUAL(z, (MPRational{1, 15}));
    TRY((x = {5, 6}));   TRY((y = {-9, 10}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{-1, 15}));
    TRY((x = {-5, 6}));  TRY((y = {-9, 10}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{-26, 15}));
    TRY((x = {0, 6}));   TRY((y = {0, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (MPRational{0, 1}));
    TRY((x = {0, 6}));   TRY((y = {1, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (MPRational{1, 6}));
    TRY((x = {0, 6}));   TRY((y = {2, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (MPRational{1, 3}));
    TRY((x = {0, 6}));   TRY((y = {3, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (MPRational{1, 2}));
    TRY((x = {0, 6}));   TRY((y = {4, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (MPRational{2, 3}));
    TRY((x = {0, 6}));   TRY((y = {5, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (MPRational{5, 6}));
    TRY((x = {0, 6}));   TRY((y = {6, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (MPRational{1, 1}));
    TRY((x = {1, 6}));   TRY((y = {0, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (MPRational{1, 6}));
    TRY((x = {1, 6}));   TRY((y = {1, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (MPRational{1, 3}));
    TRY((x = {1, 6}));   TRY((y = {2, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (MPRational{1, 2}));
    TRY((x = {1, 6}));   TRY((y = {3, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (MPRational{2, 3}));
    TRY((x = {1, 6}));   TRY((y = {4, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (MPRational{5, 6}));
    TRY((x = {1, 6}));   TRY((y = {5, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (MPRational{1, 1}));
    TRY((x = {1, 6}));   TRY((y = {6, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (MPRational{7, 6}));
    TRY((x = {2, 6}));   TRY((y = {0, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (MPRational{1, 3}));
    TRY((x = {2, 6}));   TRY((y = {1, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (MPRational{1, 2}));
    TRY((x = {2, 6}));   TRY((y = {2, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (MPRational{2, 3}));
    TRY((x = {2, 6}));   TRY((y = {3, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (MPRational{5, 6}));
    TRY((x = {2, 6}));   TRY((y = {4, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (MPRational{1, 1}));
    TRY((x = {2, 6}));   TRY((y = {5, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (MPRational{7, 6}));
    TRY((x = {2, 6}));   TRY((y = {6, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (MPRational{4, 3}));
    TRY((x = {3, 6}));   TRY((y = {0, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (MPRational{1, 2}));
    TRY((x = {3, 6}));   TRY((y = {1, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (MPRational{2, 3}));
    TRY((x = {3, 6}));   TRY((y = {2, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (MPRational{5, 6}));
    TRY((x = {3, 6}));   TRY((y = {3, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (MPRational{1, 1}));
    TRY((x = {3, 6}));   TRY((y = {4, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (MPRational{7, 6}));
    TRY((x = {3, 6}));   TRY((y = {5, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (MPRational{4, 3}));
    TRY((x = {3, 6}));   TRY((y = {6, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (MPRational{3, 2}));
    TRY((x = {4, 6}));   TRY((y = {0, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (MPRational{2, 3}));
    TRY((x = {4, 6}));   TRY((y = {1, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (MPRational{5, 6}));
    TRY((x = {4, 6}));   TRY((y = {2, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (MPRational{1, 1}));
    TRY((x = {4, 6}));   TRY((y = {3, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (MPRational{7, 6}));
    TRY((x = {4, 6}));   TRY((y = {4, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (MPRational{4, 3}));
    TRY((x = {4, 6}));   TRY((y = {5, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (MPRational{3, 2}));
    TRY((x = {4, 6}));   TRY((y = {6, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (MPRational{5, 3}));
    TRY((x = {5, 6}));   TRY((y = {0, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (MPRational{5, 6}));
    TRY((x = {5, 6}));   TRY((y = {1, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (MPRational{1, 1}));
    TRY((x = {5, 6}));   TRY((y = {2, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (MPRational{7, 6}));
    TRY((x = {5, 6}));   TRY((y = {3, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (MPRational{4, 3}));
    TRY((x = {5, 6}));   TRY((y = {4, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (MPRational{3, 2}));
    TRY((x = {5, 6}));   TRY((y = {5, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (MPRational{5, 3}));
    TRY((x = {5, 6}));   TRY((y = {6, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (MPRational{11, 6}));
    TRY((x = {6, 6}));   TRY((y = {0, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (MPRational{1, 1}));
    TRY((x = {6, 6}));   TRY((y = {1, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (MPRational{7, 6}));
    TRY((x = {6, 6}));   TRY((y = {2, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (MPRational{4, 3}));
    TRY((x = {6, 6}));   TRY((y = {3, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (MPRational{3, 2}));
    TRY((x = {6, 6}));   TRY((y = {4, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (MPRational{5, 3}));
    TRY((x = {6, 6}));   TRY((y = {5, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (MPRational{11, 6}));
    TRY((x = {6, 6}));   TRY((y = {6, 6}));    TRY(z = x + y);  TEST_EQUAL(z, (MPRational{2, 1}));

}

void test_rs_core_rational_mp_integer_subtraction() {

    MPRational x, y, z;

    TRY((x = {5, 6}));   TRY((y = {9, 10}));   TRY(x -= y);     TEST_EQUAL(x, (MPRational{-1, 15}));
    TRY((x = {-5, 6}));  TRY((y = {9, 10}));   TRY(x -= y);     TEST_EQUAL(x, (MPRational{-26, 15}));
    TRY((x = {5, 6}));   TRY((y = {-9, 10}));  TRY(x -= y);     TEST_EQUAL(x, (MPRational{26, 15}));
    TRY((x = {-5, 6}));  TRY((y = {-9, 10}));  TRY(x -= y);     TEST_EQUAL(x, (MPRational{1, 15}));
    TRY((x = {5, 6}));   TRY((y = {9, 10}));   TRY(z = x - y);  TEST_EQUAL(z, (MPRational{-1, 15}));
    TRY((x = {-5, 6}));  TRY((y = {9, 10}));   TRY(z = x - y);  TEST_EQUAL(z, (MPRational{-26, 15}));
    TRY((x = {5, 6}));   TRY((y = {-9, 10}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{26, 15}));
    TRY((x = {-5, 6}));  TRY((y = {-9, 10}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{1, 15}));
    TRY((x = {0, 6}));   TRY((y = {0, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (MPRational{0, 1}));
    TRY((x = {0, 6}));   TRY((y = {1, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (MPRational{-1, 6}));
    TRY((x = {0, 6}));   TRY((y = {2, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (MPRational{-1, 3}));
    TRY((x = {0, 6}));   TRY((y = {3, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (MPRational{-1, 2}));
    TRY((x = {0, 6}));   TRY((y = {4, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (MPRational{-2, 3}));
    TRY((x = {0, 6}));   TRY((y = {5, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (MPRational{-5, 6}));
    TRY((x = {0, 6}));   TRY((y = {6, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (MPRational{-1, 1}));
    TRY((x = {1, 6}));   TRY((y = {0, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (MPRational{1, 6}));
    TRY((x = {1, 6}));   TRY((y = {1, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (MPRational{0, 1}));
    TRY((x = {1, 6}));   TRY((y = {2, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (MPRational{-1, 6}));
    TRY((x = {1, 6}));   TRY((y = {3, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (MPRational{-1, 3}));
    TRY((x = {1, 6}));   TRY((y = {4, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (MPRational{-1, 2}));
    TRY((x = {1, 6}));   TRY((y = {5, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (MPRational{-2, 3}));
    TRY((x = {1, 6}));   TRY((y = {6, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (MPRational{-5, 6}));
    TRY((x = {2, 6}));   TRY((y = {0, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (MPRational{1, 3}));
    TRY((x = {2, 6}));   TRY((y = {1, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (MPRational{1, 6}));
    TRY((x = {2, 6}));   TRY((y = {2, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (MPRational{0, 1}));
    TRY((x = {2, 6}));   TRY((y = {3, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (MPRational{-1, 6}));
    TRY((x = {2, 6}));   TRY((y = {4, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (MPRational{-1, 3}));
    TRY((x = {2, 6}));   TRY((y = {5, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (MPRational{-1, 2}));
    TRY((x = {2, 6}));   TRY((y = {6, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (MPRational{-2, 3}));
    TRY((x = {3, 6}));   TRY((y = {0, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (MPRational{1, 2}));
    TRY((x = {3, 6}));   TRY((y = {1, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (MPRational{1, 3}));
    TRY((x = {3, 6}));   TRY((y = {2, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (MPRational{1, 6}));
    TRY((x = {3, 6}));   TRY((y = {3, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (MPRational{0, 1}));
    TRY((x = {3, 6}));   TRY((y = {4, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (MPRational{-1, 6}));
    TRY((x = {3, 6}));   TRY((y = {5, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (MPRational{-1, 3}));
    TRY((x = {3, 6}));   TRY((y = {6, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (MPRational{-1, 2}));
    TRY((x = {4, 6}));   TRY((y = {0, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (MPRational{2, 3}));
    TRY((x = {4, 6}));   TRY((y = {1, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (MPRational{1, 2}));
    TRY((x = {4, 6}));   TRY((y = {2, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (MPRational{1, 3}));
    TRY((x = {4, 6}));   TRY((y = {3, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (MPRational{1, 6}));
    TRY((x = {4, 6}));   TRY((y = {4, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (MPRational{0, 1}));
    TRY((x = {4, 6}));   TRY((y = {5, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (MPRational{-1, 6}));
    TRY((x = {4, 6}));   TRY((y = {6, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (MPRational{-1, 3}));
    TRY((x = {5, 6}));   TRY((y = {0, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (MPRational{5, 6}));
    TRY((x = {5, 6}));   TRY((y = {1, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (MPRational{2, 3}));
    TRY((x = {5, 6}));   TRY((y = {2, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (MPRational{1, 2}));
    TRY((x = {5, 6}));   TRY((y = {3, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (MPRational{1, 3}));
    TRY((x = {5, 6}));   TRY((y = {4, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (MPRational{1, 6}));
    TRY((x = {5, 6}));   TRY((y = {5, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (MPRational{0, 1}));
    TRY((x = {5, 6}));   TRY((y = {6, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (MPRational{-1, 6}));
    TRY((x = {6, 6}));   TRY((y = {0, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (MPRational{1, 1}));
    TRY((x = {6, 6}));   TRY((y = {1, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (MPRational{5, 6}));
    TRY((x = {6, 6}));   TRY((y = {2, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (MPRational{2, 3}));
    TRY((x = {6, 6}));   TRY((y = {3, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (MPRational{1, 2}));
    TRY((x = {6, 6}));   TRY((y = {4, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (MPRational{1, 3}));
    TRY((x = {6, 6}));   TRY((y = {5, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (MPRational{1, 6}));
    TRY((x = {6, 6}));   TRY((y = {6, 6}));    TRY(z = x - y);  TEST_EQUAL(z, (MPRational{0, 1}));

}
