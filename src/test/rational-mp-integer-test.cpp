#include "rs-core/rational.hpp"
#include "rs-core/mp-integer.hpp"
#include "rs-core/unit-test.hpp"
#include <format>
#include <optional>
#include <stdexcept>
#include <string>

using namespace RS;
using namespace RS::Literals;

void test_rs_core_rational_mp_integer_construction() {

    MPRational r;

    /**/                          TEST_EQUAL(r.num(), 0_Z);    TEST_EQUAL(r.den(), 1_Z);
    TRY((r = 42_Z));              TEST_EQUAL(r.num(), 42_Z);   TEST_EQUAL(r.den(), 1_Z);
    TRY((r = -42_Z));             TEST_EQUAL(r.num(), -42_Z);  TEST_EQUAL(r.den(), 1_Z);
    TRY((r = 0_Z));               TEST_EQUAL(r.num(), 0_Z);    TEST_EQUAL(r.den(), 1_Z);
    TRY((r = {20_Z, 12_Z}));      TEST_EQUAL(r.num(), 5_Z);    TEST_EQUAL(r.den(), 3_Z);
    TRY((r = {-20_Z, 12_Z}));     TEST_EQUAL(r.num(), -5_Z);   TEST_EQUAL(r.den(), 3_Z);
    TRY((r = {20_Z, -12_Z}));     TEST_EQUAL(r.num(), -5_Z);   TEST_EQUAL(r.den(), 3_Z);
    TRY((r = {-20_Z, -12_Z}));    TEST_EQUAL(r.num(), 5_Z);    TEST_EQUAL(r.den(), 3_Z);
    TRY((r = {-12_Z, 6_Z}));      TEST_EQUAL(r.num(), -2_Z);   TEST_EQUAL(r.den(), 1_Z);
    TRY((r = {-11_Z, 6_Z}));      TEST_EQUAL(r.num(), -11_Z);  TEST_EQUAL(r.den(), 6_Z);
    TRY((r = {-10_Z, 6_Z}));      TEST_EQUAL(r.num(), -5_Z);   TEST_EQUAL(r.den(), 3_Z);
    TRY((r = {-9_Z, 6_Z}));       TEST_EQUAL(r.num(), -3_Z);   TEST_EQUAL(r.den(), 2_Z);
    TRY((r = {-8_Z, 6_Z}));       TEST_EQUAL(r.num(), -4_Z);   TEST_EQUAL(r.den(), 3_Z);
    TRY((r = {-7_Z, 6_Z}));       TEST_EQUAL(r.num(), -7_Z);   TEST_EQUAL(r.den(), 6_Z);
    TRY((r = {-6_Z, 6_Z}));       TEST_EQUAL(r.num(), -1_Z);   TEST_EQUAL(r.den(), 1_Z);
    TRY((r = {-5_Z, 6_Z}));       TEST_EQUAL(r.num(), -5_Z);   TEST_EQUAL(r.den(), 6_Z);
    TRY((r = {-4_Z, 6_Z}));       TEST_EQUAL(r.num(), -2_Z);   TEST_EQUAL(r.den(), 3_Z);
    TRY((r = {-3_Z, 6_Z}));       TEST_EQUAL(r.num(), -1_Z);   TEST_EQUAL(r.den(), 2_Z);
    TRY((r = {-2_Z, 6_Z}));       TEST_EQUAL(r.num(), -1_Z);   TEST_EQUAL(r.den(), 3_Z);
    TRY((r = {-1_Z, 6_Z}));       TEST_EQUAL(r.num(), -1_Z);   TEST_EQUAL(r.den(), 6_Z);
    TRY((r = {0_Z, 6_Z}));        TEST_EQUAL(r.num(), 0_Z);    TEST_EQUAL(r.den(), 1_Z);
    TRY((r = {1_Z, 6_Z}));        TEST_EQUAL(r.num(), 1_Z);    TEST_EQUAL(r.den(), 6_Z);
    TRY((r = {2_Z, 6_Z}));        TEST_EQUAL(r.num(), 1_Z);    TEST_EQUAL(r.den(), 3_Z);
    TRY((r = {3_Z, 6_Z}));        TEST_EQUAL(r.num(), 1_Z);    TEST_EQUAL(r.den(), 2_Z);
    TRY((r = {4_Z, 6_Z}));        TEST_EQUAL(r.num(), 2_Z);    TEST_EQUAL(r.den(), 3_Z);
    TRY((r = {5_Z, 6_Z}));        TEST_EQUAL(r.num(), 5_Z);    TEST_EQUAL(r.den(), 6_Z);
    TRY((r = {6_Z, 6_Z}));        TEST_EQUAL(r.num(), 1_Z);    TEST_EQUAL(r.den(), 1_Z);
    TRY((r = {7_Z, 6_Z}));        TEST_EQUAL(r.num(), 7_Z);    TEST_EQUAL(r.den(), 6_Z);
    TRY((r = {8_Z, 6_Z}));        TEST_EQUAL(r.num(), 4_Z);    TEST_EQUAL(r.den(), 3_Z);
    TRY((r = {9_Z, 6_Z}));        TEST_EQUAL(r.num(), 3_Z);    TEST_EQUAL(r.den(), 2_Z);
    TRY((r = {10_Z, 6_Z}));       TEST_EQUAL(r.num(), 5_Z);    TEST_EQUAL(r.den(), 3_Z);
    TRY((r = {11_Z, 6_Z}));       TEST_EQUAL(r.num(), 11_Z);   TEST_EQUAL(r.den(), 6_Z);
    TRY((r = {12_Z, 6_Z}));       TEST_EQUAL(r.num(), 2_Z);    TEST_EQUAL(r.den(), 1_Z);
    TRY((r = {2_Z, 0_Z, 4_Z}));   TEST_EQUAL(r.num(), 2_Z);    TEST_EQUAL(r.den(), 1_Z);
    TRY((r = {2_Z, 1_Z, 4_Z}));   TEST_EQUAL(r.num(), 9_Z);    TEST_EQUAL(r.den(), 4_Z);
    TRY((r = {2_Z, 2_Z, 4_Z}));   TEST_EQUAL(r.num(), 5_Z);    TEST_EQUAL(r.den(), 2_Z);
    TRY((r = {2_Z, 3_Z, 4_Z}));   TEST_EQUAL(r.num(), 11_Z);   TEST_EQUAL(r.den(), 4_Z);
    TRY((r = {2_Z, 4_Z, 4_Z}));   TEST_EQUAL(r.num(), 3_Z);    TEST_EQUAL(r.den(), 1_Z);
    TRY((r = {-2_Z, 0_Z, 4_Z}));  TEST_EQUAL(r.num(), -2_Z);   TEST_EQUAL(r.den(), 1_Z);
    TRY((r = {-2_Z, 1_Z, 4_Z}));  TEST_EQUAL(r.num(), -9_Z);   TEST_EQUAL(r.den(), 4_Z);
    TRY((r = {-2_Z, 2_Z, 4_Z}));  TEST_EQUAL(r.num(), -5_Z);   TEST_EQUAL(r.den(), 2_Z);
    TRY((r = {-2_Z, 3_Z, 4_Z}));  TEST_EQUAL(r.num(), -11_Z);  TEST_EQUAL(r.den(), 4_Z);
    TRY((r = {-2_Z, 4_Z, 4_Z}));  TEST_EQUAL(r.num(), -3_Z);   TEST_EQUAL(r.den(), 1_Z);

}

void test_rs_core_rational_mp_integer_properties() {

    MPRational r;

    TEST_EQUAL(r.abs(),              MPRational{});
    TEST_EQUAL(r.sign(),             0);
    TEST_EQUAL(r.whole(),            0_Z);
    TEST_EQUAL(r.fraction(),         MPRational{});
    TEST_EQUAL(r.truncate(),         0_Z);
    TEST_EQUAL(r.signed_fraction(),  MPRational{});

    TRY(r = 42_Z);
    TEST_EQUAL(r.abs(),              MPRational{42_Z});
    TEST_EQUAL(r.sign(),             1);
    TEST_EQUAL(r.whole(),            42_Z);
    TEST_EQUAL(r.fraction(),         MPRational{});
    TEST_EQUAL(r.truncate(),         42_Z);
    TEST_EQUAL(r.signed_fraction(),  MPRational{});

    TRY((r = {3_Z, 4_Z}));
    TEST_EQUAL(r.abs(),              (MPRational{3_Z, 4_Z}));
    TEST_EQUAL(r.sign(),             1);
    TEST_EQUAL(r.whole(),            0_Z);
    TEST_EQUAL(r.fraction(),         (MPRational{3_Z, 4_Z}));
    TEST_EQUAL(r.truncate(),         0_Z);
    TEST_EQUAL(r.signed_fraction(),  (MPRational{3_Z, 4_Z}));

    TRY((r = {9_Z, 4_Z}));
    TEST_EQUAL(r.abs(),              (MPRational{9_Z, 4_Z}));
    TEST_EQUAL(r.sign(),             1);
    TEST_EQUAL(r.whole(),            2_Z);
    TEST_EQUAL(r.fraction(),         (MPRational{1_Z, 4_Z}));
    TEST_EQUAL(r.truncate(),         2_Z);
    TEST_EQUAL(r.signed_fraction(),  (MPRational{1_Z, 4_Z}));

    TRY(r = -42_Z);
    TEST_EQUAL(r.abs(),              MPRational{42_Z});
    TEST_EQUAL(r.sign(),             -1);
    TEST_EQUAL(r.whole(),            -42_Z);
    TEST_EQUAL(r.fraction(),         MPRational{});
    TEST_EQUAL(r.truncate(),         -42_Z);
    TEST_EQUAL(r.signed_fraction(),  MPRational{});

    TRY((r = {-3_Z, 4_Z}));
    TEST_EQUAL(r.abs(),              (MPRational{3_Z, 4_Z}));
    TEST_EQUAL(r.sign(),             -1);
    TEST_EQUAL(r.whole(),            -1_Z);
    TEST_EQUAL(r.fraction(),         (MPRational{1_Z, 4_Z}));
    TEST_EQUAL(r.truncate(),         0_Z);
    TEST_EQUAL(r.signed_fraction(),  (MPRational{-3_Z, 4_Z}));

    TRY((r = {-9_Z, 4_Z}));
    TEST_EQUAL(r.abs(),              (MPRational{9_Z, 4_Z}));
    TEST_EQUAL(r.sign(),             -1);
    TEST_EQUAL(r.whole(),            -3_Z);
    TEST_EQUAL(r.fraction(),         (MPRational{3_Z, 4_Z}));
    TEST_EQUAL(r.truncate(),         -2_Z);
    TEST_EQUAL(r.signed_fraction(),  (MPRational{-1_Z, 4_Z}));

}

void test_rs_core_rational_mp_integer_arithmetic() {

    MPRational x, y, z;

    TRY((x = {5_Z, 6_Z}));   TRY((y = {9_Z, 10_Z}));   TRY(x += y);  TEST_EQUAL(x, (MPRational{26_Z, 15_Z}));
    TRY((x = {-5_Z, 6_Z}));  TRY((y = {9_Z, 10_Z}));   TRY(x += y);  TEST_EQUAL(x, (MPRational{1_Z, 15_Z}));
    TRY((x = {5_Z, 6_Z}));   TRY((y = {-9_Z, 10_Z}));  TRY(x += y);  TEST_EQUAL(x, (MPRational{-1_Z, 15_Z}));
    TRY((x = {-5_Z, 6_Z}));  TRY((y = {-9_Z, 10_Z}));  TRY(x += y);  TEST_EQUAL(x, (MPRational{-26_Z, 15_Z}));
    TRY((x = {5_Z, 6_Z}));   TRY((y = {9_Z, 10_Z}));   TRY(x -= y);  TEST_EQUAL(x, (MPRational{-1_Z, 15_Z}));
    TRY((x = {-5_Z, 6_Z}));  TRY((y = {9_Z, 10_Z}));   TRY(x -= y);  TEST_EQUAL(x, (MPRational{-26_Z, 15_Z}));
    TRY((x = {5_Z, 6_Z}));   TRY((y = {-9_Z, 10_Z}));  TRY(x -= y);  TEST_EQUAL(x, (MPRational{26_Z, 15_Z}));
    TRY((x = {-5_Z, 6_Z}));  TRY((y = {-9_Z, 10_Z}));  TRY(x -= y);  TEST_EQUAL(x, (MPRational{1_Z, 15_Z}));
    TRY((x = {5_Z, 6_Z}));   TRY((y = {9_Z, 10_Z}));   TRY(x *= y);  TEST_EQUAL(x, (MPRational{3_Z, 4_Z}));
    TRY((x = {-5_Z, 6_Z}));  TRY((y = {9_Z, 10_Z}));   TRY(x *= y);  TEST_EQUAL(x, (MPRational{-3_Z, 4_Z}));
    TRY((x = {5_Z, 6_Z}));   TRY((y = {-9_Z, 10_Z}));  TRY(x *= y);  TEST_EQUAL(x, (MPRational{-3_Z, 4_Z}));
    TRY((x = {-5_Z, 6_Z}));  TRY((y = {-9_Z, 10_Z}));  TRY(x *= y);  TEST_EQUAL(x, (MPRational{3_Z, 4_Z}));
    TRY((x = {5_Z, 6_Z}));   TRY((y = {9_Z, 10_Z}));   TRY(x /= y);  TEST_EQUAL(x, (MPRational{25_Z, 27_Z}));
    TRY((x = {-5_Z, 6_Z}));  TRY((y = {9_Z, 10_Z}));   TRY(x /= y);  TEST_EQUAL(x, (MPRational{-25_Z, 27_Z}));
    TRY((x = {5_Z, 6_Z}));   TRY((y = {-9_Z, 10_Z}));  TRY(x /= y);  TEST_EQUAL(x, (MPRational{-25_Z, 27_Z}));
    TRY((x = {-5_Z, 6_Z}));  TRY((y = {-9_Z, 10_Z}));  TRY(x /= y);  TEST_EQUAL(x, (MPRational{25_Z, 27_Z}));

    TRY((x = {5_Z, 6_Z}));   TRY((y = {9_Z, 10_Z}));   TRY(z = x + y);  TEST_EQUAL(z, (MPRational{26_Z, 15_Z}));
    TRY((x = {-5_Z, 6_Z}));  TRY((y = {9_Z, 10_Z}));   TRY(z = x + y);  TEST_EQUAL(z, (MPRational{1_Z, 15_Z}));
    TRY((x = {5_Z, 6_Z}));   TRY((y = {-9_Z, 10_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{-1_Z, 15_Z}));
    TRY((x = {-5_Z, 6_Z}));  TRY((y = {-9_Z, 10_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{-26_Z, 15_Z}));
    TRY((x = {5_Z, 6_Z}));   TRY((y = {9_Z, 10_Z}));   TRY(z = x - y);  TEST_EQUAL(z, (MPRational{-1_Z, 15_Z}));
    TRY((x = {-5_Z, 6_Z}));  TRY((y = {9_Z, 10_Z}));   TRY(z = x - y);  TEST_EQUAL(z, (MPRational{-26_Z, 15_Z}));
    TRY((x = {5_Z, 6_Z}));   TRY((y = {-9_Z, 10_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{26_Z, 15_Z}));
    TRY((x = {-5_Z, 6_Z}));  TRY((y = {-9_Z, 10_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{1_Z, 15_Z}));
    TRY((x = {5_Z, 6_Z}));   TRY((y = {9_Z, 10_Z}));   TRY(z = x * y);  TEST_EQUAL(z, (MPRational{3_Z, 4_Z}));
    TRY((x = {-5_Z, 6_Z}));  TRY((y = {9_Z, 10_Z}));   TRY(z = x * y);  TEST_EQUAL(z, (MPRational{-3_Z, 4_Z}));
    TRY((x = {5_Z, 6_Z}));   TRY((y = {-9_Z, 10_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{-3_Z, 4_Z}));
    TRY((x = {-5_Z, 6_Z}));  TRY((y = {-9_Z, 10_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{3_Z, 4_Z}));
    TRY((x = {5_Z, 6_Z}));   TRY((y = {9_Z, 10_Z}));   TRY(z = x / y);  TEST_EQUAL(z, (MPRational{25_Z, 27_Z}));
    TRY((x = {-5_Z, 6_Z}));  TRY((y = {9_Z, 10_Z}));   TRY(z = x / y);  TEST_EQUAL(z, (MPRational{-25_Z, 27_Z}));
    TRY((x = {5_Z, 6_Z}));   TRY((y = {-9_Z, 10_Z}));  TRY(z = x / y);  TEST_EQUAL(z, (MPRational{-25_Z, 27_Z}));
    TRY((x = {-5_Z, 6_Z}));  TRY((y = {-9_Z, 10_Z}));  TRY(z = x / y);  TEST_EQUAL(z, (MPRational{25_Z, 27_Z}));

    TRY((x = {0_Z, 6_Z}));   TRY((y = {0_Z, 6_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{0_Z, 1_Z}));
    TRY((x = {0_Z, 6_Z}));   TRY((y = {1_Z, 6_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{1_Z, 6_Z}));
    TRY((x = {0_Z, 6_Z}));   TRY((y = {2_Z, 6_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{1_Z, 3_Z}));
    TRY((x = {0_Z, 6_Z}));   TRY((y = {3_Z, 6_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{1_Z, 2_Z}));
    TRY((x = {0_Z, 6_Z}));   TRY((y = {4_Z, 6_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{2_Z, 3_Z}));
    TRY((x = {0_Z, 6_Z}));   TRY((y = {5_Z, 6_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{5_Z, 6_Z}));
    TRY((x = {0_Z, 6_Z}));   TRY((y = {6_Z, 6_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{1_Z, 1_Z}));
    TRY((x = {1_Z, 6_Z}));   TRY((y = {0_Z, 6_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{1_Z, 6_Z}));
    TRY((x = {1_Z, 6_Z}));   TRY((y = {1_Z, 6_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{1_Z, 3_Z}));
    TRY((x = {1_Z, 6_Z}));   TRY((y = {2_Z, 6_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{1_Z, 2_Z}));
    TRY((x = {1_Z, 6_Z}));   TRY((y = {3_Z, 6_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{2_Z, 3_Z}));
    TRY((x = {1_Z, 6_Z}));   TRY((y = {4_Z, 6_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{5_Z, 6_Z}));
    TRY((x = {1_Z, 6_Z}));   TRY((y = {5_Z, 6_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{1_Z, 1_Z}));
    TRY((x = {1_Z, 6_Z}));   TRY((y = {6_Z, 6_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{7_Z, 6_Z}));
    TRY((x = {2_Z, 6_Z}));   TRY((y = {0_Z, 6_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{1_Z, 3_Z}));
    TRY((x = {2_Z, 6_Z}));   TRY((y = {1_Z, 6_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{1_Z, 2_Z}));
    TRY((x = {2_Z, 6_Z}));   TRY((y = {2_Z, 6_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{2_Z, 3_Z}));
    TRY((x = {2_Z, 6_Z}));   TRY((y = {3_Z, 6_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{5_Z, 6_Z}));
    TRY((x = {2_Z, 6_Z}));   TRY((y = {4_Z, 6_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{1_Z, 1_Z}));
    TRY((x = {2_Z, 6_Z}));   TRY((y = {5_Z, 6_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{7_Z, 6_Z}));
    TRY((x = {2_Z, 6_Z}));   TRY((y = {6_Z, 6_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{4_Z, 3_Z}));
    TRY((x = {3_Z, 6_Z}));   TRY((y = {0_Z, 6_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{1_Z, 2_Z}));
    TRY((x = {3_Z, 6_Z}));   TRY((y = {1_Z, 6_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{2_Z, 3_Z}));
    TRY((x = {3_Z, 6_Z}));   TRY((y = {2_Z, 6_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{5_Z, 6_Z}));
    TRY((x = {3_Z, 6_Z}));   TRY((y = {3_Z, 6_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{1_Z, 1_Z}));
    TRY((x = {3_Z, 6_Z}));   TRY((y = {4_Z, 6_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{7_Z, 6_Z}));
    TRY((x = {3_Z, 6_Z}));   TRY((y = {5_Z, 6_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{4_Z, 3_Z}));
    TRY((x = {3_Z, 6_Z}));   TRY((y = {6_Z, 6_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{3_Z, 2_Z}));
    TRY((x = {4_Z, 6_Z}));   TRY((y = {0_Z, 6_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{2_Z, 3_Z}));
    TRY((x = {4_Z, 6_Z}));   TRY((y = {1_Z, 6_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{5_Z, 6_Z}));
    TRY((x = {4_Z, 6_Z}));   TRY((y = {2_Z, 6_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{1_Z, 1_Z}));
    TRY((x = {4_Z, 6_Z}));   TRY((y = {3_Z, 6_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{7_Z, 6_Z}));
    TRY((x = {4_Z, 6_Z}));   TRY((y = {4_Z, 6_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{4_Z, 3_Z}));
    TRY((x = {4_Z, 6_Z}));   TRY((y = {5_Z, 6_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{3_Z, 2_Z}));
    TRY((x = {4_Z, 6_Z}));   TRY((y = {6_Z, 6_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{5_Z, 3_Z}));
    TRY((x = {5_Z, 6_Z}));   TRY((y = {0_Z, 6_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{5_Z, 6_Z}));
    TRY((x = {5_Z, 6_Z}));   TRY((y = {1_Z, 6_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{1_Z, 1_Z}));
    TRY((x = {5_Z, 6_Z}));   TRY((y = {2_Z, 6_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{7_Z, 6_Z}));
    TRY((x = {5_Z, 6_Z}));   TRY((y = {3_Z, 6_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{4_Z, 3_Z}));
    TRY((x = {5_Z, 6_Z}));   TRY((y = {4_Z, 6_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{3_Z, 2_Z}));
    TRY((x = {5_Z, 6_Z}));   TRY((y = {5_Z, 6_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{5_Z, 3_Z}));
    TRY((x = {5_Z, 6_Z}));   TRY((y = {6_Z, 6_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{11_Z, 6_Z}));
    TRY((x = {6_Z, 6_Z}));   TRY((y = {0_Z, 6_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{1_Z, 1_Z}));
    TRY((x = {6_Z, 6_Z}));   TRY((y = {1_Z, 6_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{7_Z, 6_Z}));
    TRY((x = {6_Z, 6_Z}));   TRY((y = {2_Z, 6_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{4_Z, 3_Z}));
    TRY((x = {6_Z, 6_Z}));   TRY((y = {3_Z, 6_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{3_Z, 2_Z}));
    TRY((x = {6_Z, 6_Z}));   TRY((y = {4_Z, 6_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{5_Z, 3_Z}));
    TRY((x = {6_Z, 6_Z}));   TRY((y = {5_Z, 6_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{11_Z, 6_Z}));
    TRY((x = {6_Z, 6_Z}));   TRY((y = {6_Z, 6_Z}));  TRY(z = x + y);  TEST_EQUAL(z, (MPRational{2_Z, 1_Z}));

    TRY((x = {0_Z, 6_Z}));   TRY((y = {0_Z, 6_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{0_Z, 1_Z}));
    TRY((x = {0_Z, 6_Z}));   TRY((y = {1_Z, 6_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{-1_Z, 6_Z}));
    TRY((x = {0_Z, 6_Z}));   TRY((y = {2_Z, 6_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{-1_Z, 3_Z}));
    TRY((x = {0_Z, 6_Z}));   TRY((y = {3_Z, 6_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{-1_Z, 2_Z}));
    TRY((x = {0_Z, 6_Z}));   TRY((y = {4_Z, 6_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{-2_Z, 3_Z}));
    TRY((x = {0_Z, 6_Z}));   TRY((y = {5_Z, 6_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{-5_Z, 6_Z}));
    TRY((x = {0_Z, 6_Z}));   TRY((y = {6_Z, 6_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{-1_Z, 1_Z}));
    TRY((x = {1_Z, 6_Z}));   TRY((y = {0_Z, 6_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{1_Z, 6_Z}));
    TRY((x = {1_Z, 6_Z}));   TRY((y = {1_Z, 6_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{0_Z, 1_Z}));
    TRY((x = {1_Z, 6_Z}));   TRY((y = {2_Z, 6_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{-1_Z, 6_Z}));
    TRY((x = {1_Z, 6_Z}));   TRY((y = {3_Z, 6_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{-1_Z, 3_Z}));
    TRY((x = {1_Z, 6_Z}));   TRY((y = {4_Z, 6_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{-1_Z, 2_Z}));
    TRY((x = {1_Z, 6_Z}));   TRY((y = {5_Z, 6_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{-2_Z, 3_Z}));
    TRY((x = {1_Z, 6_Z}));   TRY((y = {6_Z, 6_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{-5_Z, 6_Z}));
    TRY((x = {2_Z, 6_Z}));   TRY((y = {0_Z, 6_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{1_Z, 3_Z}));
    TRY((x = {2_Z, 6_Z}));   TRY((y = {1_Z, 6_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{1_Z, 6_Z}));
    TRY((x = {2_Z, 6_Z}));   TRY((y = {2_Z, 6_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{0_Z, 1_Z}));
    TRY((x = {2_Z, 6_Z}));   TRY((y = {3_Z, 6_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{-1_Z, 6_Z}));
    TRY((x = {2_Z, 6_Z}));   TRY((y = {4_Z, 6_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{-1_Z, 3_Z}));
    TRY((x = {2_Z, 6_Z}));   TRY((y = {5_Z, 6_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{-1_Z, 2_Z}));
    TRY((x = {2_Z, 6_Z}));   TRY((y = {6_Z, 6_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{-2_Z, 3_Z}));
    TRY((x = {3_Z, 6_Z}));   TRY((y = {0_Z, 6_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{1_Z, 2_Z}));
    TRY((x = {3_Z, 6_Z}));   TRY((y = {1_Z, 6_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{1_Z, 3_Z}));
    TRY((x = {3_Z, 6_Z}));   TRY((y = {2_Z, 6_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{1_Z, 6_Z}));
    TRY((x = {3_Z, 6_Z}));   TRY((y = {3_Z, 6_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{0_Z, 1_Z}));
    TRY((x = {3_Z, 6_Z}));   TRY((y = {4_Z, 6_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{-1_Z, 6_Z}));
    TRY((x = {3_Z, 6_Z}));   TRY((y = {5_Z, 6_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{-1_Z, 3_Z}));
    TRY((x = {3_Z, 6_Z}));   TRY((y = {6_Z, 6_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{-1_Z, 2_Z}));
    TRY((x = {4_Z, 6_Z}));   TRY((y = {0_Z, 6_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{2_Z, 3_Z}));
    TRY((x = {4_Z, 6_Z}));   TRY((y = {1_Z, 6_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{1_Z, 2_Z}));
    TRY((x = {4_Z, 6_Z}));   TRY((y = {2_Z, 6_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{1_Z, 3_Z}));
    TRY((x = {4_Z, 6_Z}));   TRY((y = {3_Z, 6_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{1_Z, 6_Z}));
    TRY((x = {4_Z, 6_Z}));   TRY((y = {4_Z, 6_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{0_Z, 1_Z}));
    TRY((x = {4_Z, 6_Z}));   TRY((y = {5_Z, 6_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{-1_Z, 6_Z}));
    TRY((x = {4_Z, 6_Z}));   TRY((y = {6_Z, 6_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{-1_Z, 3_Z}));
    TRY((x = {5_Z, 6_Z}));   TRY((y = {0_Z, 6_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{5_Z, 6_Z}));
    TRY((x = {5_Z, 6_Z}));   TRY((y = {1_Z, 6_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{2_Z, 3_Z}));
    TRY((x = {5_Z, 6_Z}));   TRY((y = {2_Z, 6_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{1_Z, 2_Z}));
    TRY((x = {5_Z, 6_Z}));   TRY((y = {3_Z, 6_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{1_Z, 3_Z}));
    TRY((x = {5_Z, 6_Z}));   TRY((y = {4_Z, 6_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{1_Z, 6_Z}));
    TRY((x = {5_Z, 6_Z}));   TRY((y = {5_Z, 6_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{0_Z, 1_Z}));
    TRY((x = {5_Z, 6_Z}));   TRY((y = {6_Z, 6_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{-1_Z, 6_Z}));
    TRY((x = {6_Z, 6_Z}));   TRY((y = {0_Z, 6_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{1_Z, 1_Z}));
    TRY((x = {6_Z, 6_Z}));   TRY((y = {1_Z, 6_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{5_Z, 6_Z}));
    TRY((x = {6_Z, 6_Z}));   TRY((y = {2_Z, 6_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{2_Z, 3_Z}));
    TRY((x = {6_Z, 6_Z}));   TRY((y = {3_Z, 6_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{1_Z, 2_Z}));
    TRY((x = {6_Z, 6_Z}));   TRY((y = {4_Z, 6_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{1_Z, 3_Z}));
    TRY((x = {6_Z, 6_Z}));   TRY((y = {5_Z, 6_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{1_Z, 6_Z}));
    TRY((x = {6_Z, 6_Z}));   TRY((y = {6_Z, 6_Z}));  TRY(z = x - y);  TEST_EQUAL(z, (MPRational{0_Z, 1_Z}));

    TRY((x = {0_Z, 6_Z}));   TRY((y = {0_Z, 6_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{0_Z, 1_Z}));
    TRY((x = {0_Z, 6_Z}));   TRY((y = {1_Z, 6_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{0_Z, 1_Z}));
    TRY((x = {0_Z, 6_Z}));   TRY((y = {2_Z, 6_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{0_Z, 1_Z}));
    TRY((x = {0_Z, 6_Z}));   TRY((y = {3_Z, 6_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{0_Z, 1_Z}));
    TRY((x = {0_Z, 6_Z}));   TRY((y = {4_Z, 6_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{0_Z, 1_Z}));
    TRY((x = {0_Z, 6_Z}));   TRY((y = {5_Z, 6_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{0_Z, 1_Z}));
    TRY((x = {0_Z, 6_Z}));   TRY((y = {6_Z, 6_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{0_Z, 1_Z}));
    TRY((x = {1_Z, 6_Z}));   TRY((y = {0_Z, 6_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{0_Z, 1_Z}));
    TRY((x = {1_Z, 6_Z}));   TRY((y = {1_Z, 6_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{1_Z, 36_Z}));
    TRY((x = {1_Z, 6_Z}));   TRY((y = {2_Z, 6_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{1_Z, 18_Z}));
    TRY((x = {1_Z, 6_Z}));   TRY((y = {3_Z, 6_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{1_Z, 12_Z}));
    TRY((x = {1_Z, 6_Z}));   TRY((y = {4_Z, 6_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{1_Z, 9_Z}));
    TRY((x = {1_Z, 6_Z}));   TRY((y = {5_Z, 6_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{5_Z, 36_Z}));
    TRY((x = {1_Z, 6_Z}));   TRY((y = {6_Z, 6_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{1_Z, 6_Z}));
    TRY((x = {2_Z, 6_Z}));   TRY((y = {0_Z, 6_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{0_Z, 1_Z}));
    TRY((x = {2_Z, 6_Z}));   TRY((y = {1_Z, 6_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{1_Z, 18_Z}));
    TRY((x = {2_Z, 6_Z}));   TRY((y = {2_Z, 6_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{1_Z, 9_Z}));
    TRY((x = {2_Z, 6_Z}));   TRY((y = {3_Z, 6_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{1_Z, 6_Z}));
    TRY((x = {2_Z, 6_Z}));   TRY((y = {4_Z, 6_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{2_Z, 9_Z}));
    TRY((x = {2_Z, 6_Z}));   TRY((y = {5_Z, 6_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{5_Z, 18_Z}));
    TRY((x = {2_Z, 6_Z}));   TRY((y = {6_Z, 6_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{1_Z, 3_Z}));
    TRY((x = {3_Z, 6_Z}));   TRY((y = {0_Z, 6_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{0_Z, 1_Z}));
    TRY((x = {3_Z, 6_Z}));   TRY((y = {1_Z, 6_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{1_Z, 12_Z}));
    TRY((x = {3_Z, 6_Z}));   TRY((y = {2_Z, 6_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{1_Z, 6_Z}));
    TRY((x = {3_Z, 6_Z}));   TRY((y = {3_Z, 6_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{1_Z, 4_Z}));
    TRY((x = {3_Z, 6_Z}));   TRY((y = {4_Z, 6_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{1_Z, 3_Z}));
    TRY((x = {3_Z, 6_Z}));   TRY((y = {5_Z, 6_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{5_Z, 12_Z}));
    TRY((x = {3_Z, 6_Z}));   TRY((y = {6_Z, 6_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{1_Z, 2_Z}));
    TRY((x = {4_Z, 6_Z}));   TRY((y = {0_Z, 6_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{0_Z, 1_Z}));
    TRY((x = {4_Z, 6_Z}));   TRY((y = {1_Z, 6_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{1_Z, 9_Z}));
    TRY((x = {4_Z, 6_Z}));   TRY((y = {2_Z, 6_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{2_Z, 9_Z}));
    TRY((x = {4_Z, 6_Z}));   TRY((y = {3_Z, 6_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{1_Z, 3_Z}));
    TRY((x = {4_Z, 6_Z}));   TRY((y = {4_Z, 6_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{4_Z, 9_Z}));
    TRY((x = {4_Z, 6_Z}));   TRY((y = {5_Z, 6_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{5_Z, 9_Z}));
    TRY((x = {4_Z, 6_Z}));   TRY((y = {6_Z, 6_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{2_Z, 3_Z}));
    TRY((x = {5_Z, 6_Z}));   TRY((y = {0_Z, 6_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{0_Z, 1_Z}));
    TRY((x = {5_Z, 6_Z}));   TRY((y = {1_Z, 6_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{5_Z, 36_Z}));
    TRY((x = {5_Z, 6_Z}));   TRY((y = {2_Z, 6_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{5_Z, 18_Z}));
    TRY((x = {5_Z, 6_Z}));   TRY((y = {3_Z, 6_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{5_Z, 12_Z}));
    TRY((x = {5_Z, 6_Z}));   TRY((y = {4_Z, 6_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{5_Z, 9_Z}));
    TRY((x = {5_Z, 6_Z}));   TRY((y = {5_Z, 6_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{25_Z, 36_Z}));
    TRY((x = {5_Z, 6_Z}));   TRY((y = {6_Z, 6_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{5_Z, 6_Z}));
    TRY((x = {6_Z, 6_Z}));   TRY((y = {0_Z, 6_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{0_Z, 1_Z}));
    TRY((x = {6_Z, 6_Z}));   TRY((y = {1_Z, 6_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{1_Z, 6_Z}));
    TRY((x = {6_Z, 6_Z}));   TRY((y = {2_Z, 6_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{1_Z, 3_Z}));
    TRY((x = {6_Z, 6_Z}));   TRY((y = {3_Z, 6_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{1_Z, 2_Z}));
    TRY((x = {6_Z, 6_Z}));   TRY((y = {4_Z, 6_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{2_Z, 3_Z}));
    TRY((x = {6_Z, 6_Z}));   TRY((y = {5_Z, 6_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{5_Z, 6_Z}));
    TRY((x = {6_Z, 6_Z}));   TRY((y = {6_Z, 6_Z}));  TRY(z = x * y);  TEST_EQUAL(z, (MPRational{1_Z, 1_Z}));

    TRY((x = {0_Z, 6_Z}));   TRY((y = {1_Z, 6_Z}));  TRY(z = x / y);  TEST_EQUAL(z, (MPRational{0_Z, 1_Z}));
    TRY((x = {0_Z, 6_Z}));   TRY((y = {2_Z, 6_Z}));  TRY(z = x / y);  TEST_EQUAL(z, (MPRational{0_Z, 1_Z}));
    TRY((x = {0_Z, 6_Z}));   TRY((y = {3_Z, 6_Z}));  TRY(z = x / y);  TEST_EQUAL(z, (MPRational{0_Z, 1_Z}));
    TRY((x = {0_Z, 6_Z}));   TRY((y = {4_Z, 6_Z}));  TRY(z = x / y);  TEST_EQUAL(z, (MPRational{0_Z, 1_Z}));
    TRY((x = {0_Z, 6_Z}));   TRY((y = {5_Z, 6_Z}));  TRY(z = x / y);  TEST_EQUAL(z, (MPRational{0_Z, 1_Z}));
    TRY((x = {0_Z, 6_Z}));   TRY((y = {6_Z, 6_Z}));  TRY(z = x / y);  TEST_EQUAL(z, (MPRational{0_Z, 1_Z}));
    TRY((x = {1_Z, 6_Z}));   TRY((y = {1_Z, 6_Z}));  TRY(z = x / y);  TEST_EQUAL(z, (MPRational{1_Z, 1_Z}));
    TRY((x = {1_Z, 6_Z}));   TRY((y = {2_Z, 6_Z}));  TRY(z = x / y);  TEST_EQUAL(z, (MPRational{1_Z, 2_Z}));
    TRY((x = {1_Z, 6_Z}));   TRY((y = {3_Z, 6_Z}));  TRY(z = x / y);  TEST_EQUAL(z, (MPRational{1_Z, 3_Z}));
    TRY((x = {1_Z, 6_Z}));   TRY((y = {4_Z, 6_Z}));  TRY(z = x / y);  TEST_EQUAL(z, (MPRational{1_Z, 4_Z}));
    TRY((x = {1_Z, 6_Z}));   TRY((y = {5_Z, 6_Z}));  TRY(z = x / y);  TEST_EQUAL(z, (MPRational{1_Z, 5_Z}));
    TRY((x = {1_Z, 6_Z}));   TRY((y = {6_Z, 6_Z}));  TRY(z = x / y);  TEST_EQUAL(z, (MPRational{1_Z, 6_Z}));
    TRY((x = {2_Z, 6_Z}));   TRY((y = {1_Z, 6_Z}));  TRY(z = x / y);  TEST_EQUAL(z, (MPRational{2_Z, 1_Z}));
    TRY((x = {2_Z, 6_Z}));   TRY((y = {2_Z, 6_Z}));  TRY(z = x / y);  TEST_EQUAL(z, (MPRational{1_Z, 1_Z}));
    TRY((x = {2_Z, 6_Z}));   TRY((y = {3_Z, 6_Z}));  TRY(z = x / y);  TEST_EQUAL(z, (MPRational{2_Z, 3_Z}));
    TRY((x = {2_Z, 6_Z}));   TRY((y = {4_Z, 6_Z}));  TRY(z = x / y);  TEST_EQUAL(z, (MPRational{1_Z, 2_Z}));
    TRY((x = {2_Z, 6_Z}));   TRY((y = {5_Z, 6_Z}));  TRY(z = x / y);  TEST_EQUAL(z, (MPRational{2_Z, 5_Z}));
    TRY((x = {2_Z, 6_Z}));   TRY((y = {6_Z, 6_Z}));  TRY(z = x / y);  TEST_EQUAL(z, (MPRational{1_Z, 3_Z}));
    TRY((x = {3_Z, 6_Z}));   TRY((y = {1_Z, 6_Z}));  TRY(z = x / y);  TEST_EQUAL(z, (MPRational{3_Z, 1_Z}));
    TRY((x = {3_Z, 6_Z}));   TRY((y = {2_Z, 6_Z}));  TRY(z = x / y);  TEST_EQUAL(z, (MPRational{3_Z, 2_Z}));
    TRY((x = {3_Z, 6_Z}));   TRY((y = {3_Z, 6_Z}));  TRY(z = x / y);  TEST_EQUAL(z, (MPRational{1_Z, 1_Z}));
    TRY((x = {3_Z, 6_Z}));   TRY((y = {4_Z, 6_Z}));  TRY(z = x / y);  TEST_EQUAL(z, (MPRational{3_Z, 4_Z}));
    TRY((x = {3_Z, 6_Z}));   TRY((y = {5_Z, 6_Z}));  TRY(z = x / y);  TEST_EQUAL(z, (MPRational{3_Z, 5_Z}));
    TRY((x = {3_Z, 6_Z}));   TRY((y = {6_Z, 6_Z}));  TRY(z = x / y);  TEST_EQUAL(z, (MPRational{1_Z, 2_Z}));
    TRY((x = {4_Z, 6_Z}));   TRY((y = {1_Z, 6_Z}));  TRY(z = x / y);  TEST_EQUAL(z, (MPRational{4_Z, 1_Z}));
    TRY((x = {4_Z, 6_Z}));   TRY((y = {2_Z, 6_Z}));  TRY(z = x / y);  TEST_EQUAL(z, (MPRational{2_Z, 1_Z}));
    TRY((x = {4_Z, 6_Z}));   TRY((y = {3_Z, 6_Z}));  TRY(z = x / y);  TEST_EQUAL(z, (MPRational{4_Z, 3_Z}));
    TRY((x = {4_Z, 6_Z}));   TRY((y = {4_Z, 6_Z}));  TRY(z = x / y);  TEST_EQUAL(z, (MPRational{1_Z, 1_Z}));
    TRY((x = {4_Z, 6_Z}));   TRY((y = {5_Z, 6_Z}));  TRY(z = x / y);  TEST_EQUAL(z, (MPRational{4_Z, 5_Z}));
    TRY((x = {4_Z, 6_Z}));   TRY((y = {6_Z, 6_Z}));  TRY(z = x / y);  TEST_EQUAL(z, (MPRational{2_Z, 3_Z}));
    TRY((x = {5_Z, 6_Z}));   TRY((y = {1_Z, 6_Z}));  TRY(z = x / y);  TEST_EQUAL(z, (MPRational{5_Z, 1_Z}));
    TRY((x = {5_Z, 6_Z}));   TRY((y = {2_Z, 6_Z}));  TRY(z = x / y);  TEST_EQUAL(z, (MPRational{5_Z, 2_Z}));
    TRY((x = {5_Z, 6_Z}));   TRY((y = {3_Z, 6_Z}));  TRY(z = x / y);  TEST_EQUAL(z, (MPRational{5_Z, 3_Z}));
    TRY((x = {5_Z, 6_Z}));   TRY((y = {4_Z, 6_Z}));  TRY(z = x / y);  TEST_EQUAL(z, (MPRational{5_Z, 4_Z}));
    TRY((x = {5_Z, 6_Z}));   TRY((y = {5_Z, 6_Z}));  TRY(z = x / y);  TEST_EQUAL(z, (MPRational{1_Z, 1_Z}));
    TRY((x = {5_Z, 6_Z}));   TRY((y = {6_Z, 6_Z}));  TRY(z = x / y);  TEST_EQUAL(z, (MPRational{5_Z, 6_Z}));
    TRY((x = {6_Z, 6_Z}));   TRY((y = {1_Z, 6_Z}));  TRY(z = x / y);  TEST_EQUAL(z, (MPRational{6_Z, 1_Z}));
    TRY((x = {6_Z, 6_Z}));   TRY((y = {2_Z, 6_Z}));  TRY(z = x / y);  TEST_EQUAL(z, (MPRational{3_Z, 1_Z}));
    TRY((x = {6_Z, 6_Z}));   TRY((y = {3_Z, 6_Z}));  TRY(z = x / y);  TEST_EQUAL(z, (MPRational{2_Z, 1_Z}));
    TRY((x = {6_Z, 6_Z}));   TRY((y = {4_Z, 6_Z}));  TRY(z = x / y);  TEST_EQUAL(z, (MPRational{3_Z, 2_Z}));
    TRY((x = {6_Z, 6_Z}));   TRY((y = {5_Z, 6_Z}));  TRY(z = x / y);  TEST_EQUAL(z, (MPRational{6_Z, 5_Z}));
    TRY((x = {6_Z, 6_Z}));   TRY((y = {6_Z, 6_Z}));  TRY(z = x / y);  TEST_EQUAL(z, (MPRational{1_Z, 1_Z}));

}

void test_rs_core_rational_mp_integer_comparison() {

    MPRational x, y;

    /**/                     /**/                       TEST(x == y);  TEST(x <= y);  TEST(x >= y);
    TRY((x = {5_Z, 3_Z}));   TRY((y = {-1_Z}));         TEST(x != y);  TEST(x > y);   TEST(x >= y);
    TRY((x = {5_Z, 3_Z}));   TRY((y = {0_Z}));          TEST(x != y);  TEST(x > y);   TEST(x >= y);
    TRY((x = {5_Z, 3_Z}));   TRY((y = {1_Z}));          TEST(x != y);  TEST(x > y);   TEST(x >= y);
    TRY((x = {5_Z, 3_Z}));   TRY((y = {2_Z}));          TEST(x != y);  TEST(x < y);   TEST(x <= y);
    TRY((x = {5_Z, 3_Z}));   TRY((y = {5_Z, 3_Z}));     TEST(x == y);  TEST(x <= y);  TEST(x >= y);
    TRY((x = {5_Z, 3_Z}));   TRY((y = {10_Z, 6_Z}));    TEST(x == y);  TEST(x <= y);  TEST(x >= y);
    TRY((x = {5_Z, 3_Z}));   TRY((y = {49_Z, 30_Z}));   TEST(x != y);  TEST(x > y);   TEST(x >= y);
    TRY((x = {5_Z, 3_Z}));   TRY((y = {51_Z, 30_Z}));   TEST(x != y);  TEST(x < y);   TEST(x <= y);
    TRY((x = {-5_Z, 3_Z}));  TRY((y = {1_Z}));          TEST(x != y);  TEST(x < y);   TEST(x <= y);
    TRY((x = {-5_Z, 3_Z}));  TRY((y = {0_Z}));          TEST(x != y);  TEST(x < y);   TEST(x <= y);
    TRY((x = {-5_Z, 3_Z}));  TRY((y = {-1_Z}));         TEST(x != y);  TEST(x < y);   TEST(x <= y);
    TRY((x = {-5_Z, 3_Z}));  TRY((y = {-2_Z}));         TEST(x != y);  TEST(x > y);   TEST(x >= y);
    TRY((x = {-5_Z, 3_Z}));  TRY((y = {-5_Z, 3_Z}));    TEST(x == y);  TEST(x >= y);  TEST(x <= y);
    TRY((x = {-5_Z, 3_Z}));  TRY((y = {-10_Z, 6_Z}));   TEST(x == y);  TEST(x >= y);  TEST(x <= y);
    TRY((x = {-5_Z, 3_Z}));  TRY((y = {-49_Z, 30_Z}));  TEST(x != y);  TEST(x < y);   TEST(x <= y);
    TRY((x = {-5_Z, 3_Z}));  TRY((y = {-51_Z, 30_Z}));  TEST(x != y);  TEST(x > y);   TEST(x >= y);

}

void test_rs_core_rational_mp_integer_formatting() {

    MPRational r;
    std::string s;

    TRY((r = {}));              TRY(s = r.str());  TEST_EQUAL(s, "0");      TRY(s = r.mixed());  TEST_EQUAL(s, "0");
    TRY((r = {42_Z}));          TRY(s = r.str());  TEST_EQUAL(s, "42");     TRY(s = r.mixed());  TEST_EQUAL(s, "42");
    TRY((r = {-42_Z}));         TRY(s = r.str());  TEST_EQUAL(s, "-42");    TRY(s = r.mixed());  TEST_EQUAL(s, "-42");
    TRY((r = {2_Z, 3_Z}));      TRY(s = r.str());  TEST_EQUAL(s, "2/3");    TRY(s = r.mixed());  TEST_EQUAL(s, "2/3");
    TRY((r = {-2_Z, 3_Z}));     TRY(s = r.str());  TEST_EQUAL(s, "-2/3");   TRY(s = r.mixed());  TEST_EQUAL(s, "-2/3");
    TRY((r = {5_Z, 3_Z}));      TRY(s = r.str());  TEST_EQUAL(s, "5/3");    TRY(s = r.mixed());  TEST_EQUAL(s, "1 2/3");
    TRY((r = {-5_Z, 3_Z}));     TRY(s = r.str());  TEST_EQUAL(s, "-5/3");   TRY(s = r.mixed());  TEST_EQUAL(s, "-1 2/3");
    TRY((r = {100_Z, 30_Z}));   TRY(s = r.str());  TEST_EQUAL(s, "10/3");   TRY(s = r.mixed());  TEST_EQUAL(s, "3 1/3");
    TRY((r = {-100_Z, 30_Z}));  TRY(s = r.str());  TEST_EQUAL(s, "-10/3");  TRY(s = r.mixed());  TEST_EQUAL(s, "-3 1/3");

    TRY((r = {}));              TRY(s = std::format("{}", r));  TEST_EQUAL(s, "0");      TRY(s = std::format("{:m}", r));  TEST_EQUAL(s, "0");
    TRY((r = {42_Z}));          TRY(s = std::format("{}", r));  TEST_EQUAL(s, "42");     TRY(s = std::format("{:m}", r));  TEST_EQUAL(s, "42");
    TRY((r = {-42_Z}));         TRY(s = std::format("{}", r));  TEST_EQUAL(s, "-42");    TRY(s = std::format("{:m}", r));  TEST_EQUAL(s, "-42");
    TRY((r = {2_Z, 3_Z}));      TRY(s = std::format("{}", r));  TEST_EQUAL(s, "2/3");    TRY(s = std::format("{:m}", r));  TEST_EQUAL(s, "2/3");
    TRY((r = {-2_Z, 3_Z}));     TRY(s = std::format("{}", r));  TEST_EQUAL(s, "-2/3");   TRY(s = std::format("{:m}", r));  TEST_EQUAL(s, "-2/3");
    TRY((r = {5_Z, 3_Z}));      TRY(s = std::format("{}", r));  TEST_EQUAL(s, "5/3");    TRY(s = std::format("{:m}", r));  TEST_EQUAL(s, "1 2/3");
    TRY((r = {-5_Z, 3_Z}));     TRY(s = std::format("{}", r));  TEST_EQUAL(s, "-5/3");   TRY(s = std::format("{:m}", r));  TEST_EQUAL(s, "-1 2/3");
    TRY((r = {100_Z, 30_Z}));   TRY(s = std::format("{}", r));  TEST_EQUAL(s, "10/3");   TRY(s = std::format("{:m}", r));  TEST_EQUAL(s, "3 1/3");
    TRY((r = {-100_Z, 30_Z}));  TRY(s = std::format("{}", r));  TEST_EQUAL(s, "-10/3");  TRY(s = std::format("{:m}", r));  TEST_EQUAL(s, "-3 1/3");

}

void test_rs_core_rational_mp_integer_parsing() {

    MPRational r;
    std::optional<MPRational> opt;

    TRY(r = MPRational("0"));       TEST_EQUAL(r.num(), 0_Z);    TEST_EQUAL(r.den(), 1_Z);
    TRY(r = MPRational("42"));      TEST_EQUAL(r.num(), 42_Z);   TEST_EQUAL(r.den(), 1_Z);
    TRY(r = MPRational("-42"));     TEST_EQUAL(r.num(), -42_Z);  TEST_EQUAL(r.den(), 1_Z);
    TRY(r = MPRational("1/2"));     TEST_EQUAL(r.num(), 1_Z);    TEST_EQUAL(r.den(), 2_Z);
    TRY(r = MPRational("-1/2"));    TEST_EQUAL(r.num(), -1_Z);   TEST_EQUAL(r.den(), 2_Z);
    TRY(r = MPRational("30/12"));   TEST_EQUAL(r.num(), 5_Z);    TEST_EQUAL(r.den(), 2_Z);
    TRY(r = MPRational("-30/12"));  TEST_EQUAL(r.num(), -5_Z);   TEST_EQUAL(r.den(), 2_Z);
    TRY(r = MPRational("2 3/4"));   TEST_EQUAL(r.num(), 11_Z);   TEST_EQUAL(r.den(), 4_Z);
    TRY(r = MPRational("-2 3/4"));  TEST_EQUAL(r.num(), -11_Z);  TEST_EQUAL(r.den(), 4_Z);
    TRY(r = MPRational("4 6/8"));   TEST_EQUAL(r.num(), 19_Z);   TEST_EQUAL(r.den(), 4_Z);
    TRY(r = MPRational("-4 6/8"));  TEST_EQUAL(r.num(), -19_Z);  TEST_EQUAL(r.den(), 4_Z);

    TEST_THROW(MPRational("1 2"),    std::invalid_argument, "Invalid rational");
    TEST_THROW(MPRational("/1"),     std::invalid_argument, "Invalid rational");
    TEST_THROW(MPRational("1/"),     std::invalid_argument, "Invalid rational");
    TEST_THROW(MPRational("1/2/3"),  std::invalid_argument, "Invalid rational");
    TEST_THROW(MPRational("1.5"),    std::invalid_argument, "Invalid rational");

    TRY(opt = MPRational::parse("0"));       TEST(opt.has_value());  TEST_EQUAL(opt.value().num(), 0_Z);    TEST_EQUAL(opt.value().den(), 1_Z);
    TRY(opt = MPRational::parse("42"));      TEST(opt.has_value());  TEST_EQUAL(opt.value().num(), 42_Z);   TEST_EQUAL(opt.value().den(), 1_Z);
    TRY(opt = MPRational::parse("-42"));     TEST(opt.has_value());  TEST_EQUAL(opt.value().num(), -42_Z);  TEST_EQUAL(opt.value().den(), 1_Z);
    TRY(opt = MPRational::parse("1/2"));     TEST(opt.has_value());  TEST_EQUAL(opt.value().num(), 1_Z);    TEST_EQUAL(opt.value().den(), 2_Z);
    TRY(opt = MPRational::parse("-1/2"));    TEST(opt.has_value());  TEST_EQUAL(opt.value().num(), -1_Z);   TEST_EQUAL(opt.value().den(), 2_Z);
    TRY(opt = MPRational::parse("30/12"));   TEST(opt.has_value());  TEST_EQUAL(opt.value().num(), 5_Z);    TEST_EQUAL(opt.value().den(), 2_Z);
    TRY(opt = MPRational::parse("-30/12"));  TEST(opt.has_value());  TEST_EQUAL(opt.value().num(), -5_Z);   TEST_EQUAL(opt.value().den(), 2_Z);
    TRY(opt = MPRational::parse("2 3/4"));   TEST(opt.has_value());  TEST_EQUAL(opt.value().num(), 11_Z);   TEST_EQUAL(opt.value().den(), 4_Z);
    TRY(opt = MPRational::parse("-2 3/4"));  TEST(opt.has_value());  TEST_EQUAL(opt.value().num(), -11_Z);  TEST_EQUAL(opt.value().den(), 4_Z);
    TRY(opt = MPRational::parse("4 6/8"));   TEST(opt.has_value());  TEST_EQUAL(opt.value().num(), 19_Z);   TEST_EQUAL(opt.value().den(), 4_Z);
    TRY(opt = MPRational::parse("-4 6/8"));  TEST(opt.has_value());  TEST_EQUAL(opt.value().num(), -19_Z);  TEST_EQUAL(opt.value().den(), 4_Z);

    TRY(opt = MPRational::parse("1 2"));    TEST(! opt.has_value());
    TRY(opt = MPRational::parse("/1"));     TEST(! opt.has_value());
    TRY(opt = MPRational::parse("1/"));     TEST(! opt.has_value());
    TRY(opt = MPRational::parse("1/2/3"));  TEST(! opt.has_value());
    TRY(opt = MPRational::parse("1.5"));    TEST(! opt.has_value());

}
