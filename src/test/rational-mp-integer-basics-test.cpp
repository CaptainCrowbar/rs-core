#include "rs-core/rational.hpp"
#include "rs-core/mp-integer.hpp"
#include "rs-core/unit-test.hpp"

using namespace RS;
using namespace RS::Literals;

void test_rs_core_rational_mp_integer_concepts() {

    TEST(! SignedIntegral<MPRational>);
    TEST(! UnsignedIntegral<MPRational>);
    TEST(! Integral<MPRational>);
    TEST(! FloatingPoint<MPRational>);
    TEST(! FixedPointArithmetic<MPRational>);
    TEST(RationalArithmetic<MPRational>);
    TEST(Arithmetic<MPRational>);

}

void test_rs_core_rational_mp_integer_construction() {

    MPRational r;

    /**/                    TEST_EQUAL(r.num(), 0);    TEST_EQUAL(r.den(), 1);
    TRY((r = 0));           TEST_EQUAL(r.num(), 0);    TEST_EQUAL(r.den(), 1);
    TRY((r = 42));          TEST_EQUAL(r.num(), 42);   TEST_EQUAL(r.den(), 1);
    TRY((r = -42));         TEST_EQUAL(r.num(), -42);  TEST_EQUAL(r.den(), 1);
    TRY((r = 0_Z));         TEST_EQUAL(r.num(), 0);    TEST_EQUAL(r.den(), 1);
    TRY((r = 42_Z));        TEST_EQUAL(r.num(), 42);   TEST_EQUAL(r.den(), 1);
    TRY((r = -42_Z));       TEST_EQUAL(r.num(), -42);  TEST_EQUAL(r.den(), 1);
    TRY((r = {20, 12}));    TEST_EQUAL(r.num(), 5);    TEST_EQUAL(r.den(), 3);
    TRY((r = {-20, 12}));   TEST_EQUAL(r.num(), -5);   TEST_EQUAL(r.den(), 3);
    TRY((r = {20, -12}));   TEST_EQUAL(r.num(), -5);   TEST_EQUAL(r.den(), 3);
    TRY((r = {-20, -12}));  TEST_EQUAL(r.num(), 5);    TEST_EQUAL(r.den(), 3);
    TRY((r = {-12, 6}));    TEST_EQUAL(r.num(), -2);   TEST_EQUAL(r.den(), 1);
    TRY((r = {-11, 6}));    TEST_EQUAL(r.num(), -11);  TEST_EQUAL(r.den(), 6);
    TRY((r = {-10, 6}));    TEST_EQUAL(r.num(), -5);   TEST_EQUAL(r.den(), 3);
    TRY((r = {-9, 6}));     TEST_EQUAL(r.num(), -3);   TEST_EQUAL(r.den(), 2);
    TRY((r = {-8, 6}));     TEST_EQUAL(r.num(), -4);   TEST_EQUAL(r.den(), 3);
    TRY((r = {-7, 6}));     TEST_EQUAL(r.num(), -7);   TEST_EQUAL(r.den(), 6);
    TRY((r = {-6, 6}));     TEST_EQUAL(r.num(), -1);   TEST_EQUAL(r.den(), 1);
    TRY((r = {-5, 6}));     TEST_EQUAL(r.num(), -5);   TEST_EQUAL(r.den(), 6);
    TRY((r = {-4, 6}));     TEST_EQUAL(r.num(), -2);   TEST_EQUAL(r.den(), 3);
    TRY((r = {-3, 6}));     TEST_EQUAL(r.num(), -1);   TEST_EQUAL(r.den(), 2);
    TRY((r = {-2, 6}));     TEST_EQUAL(r.num(), -1);   TEST_EQUAL(r.den(), 3);
    TRY((r = {-1, 6}));     TEST_EQUAL(r.num(), -1);   TEST_EQUAL(r.den(), 6);
    TRY((r = {0, 6}));      TEST_EQUAL(r.num(), 0);    TEST_EQUAL(r.den(), 1);
    TRY((r = {1, 6}));      TEST_EQUAL(r.num(), 1);    TEST_EQUAL(r.den(), 6);
    TRY((r = {2, 6}));      TEST_EQUAL(r.num(), 1);    TEST_EQUAL(r.den(), 3);
    TRY((r = {3, 6}));      TEST_EQUAL(r.num(), 1);    TEST_EQUAL(r.den(), 2);
    TRY((r = {4, 6}));      TEST_EQUAL(r.num(), 2);    TEST_EQUAL(r.den(), 3);
    TRY((r = {5, 6}));      TEST_EQUAL(r.num(), 5);    TEST_EQUAL(r.den(), 6);
    TRY((r = {6, 6}));      TEST_EQUAL(r.num(), 1);    TEST_EQUAL(r.den(), 1);
    TRY((r = {7, 6}));      TEST_EQUAL(r.num(), 7);    TEST_EQUAL(r.den(), 6);
    TRY((r = {8, 6}));      TEST_EQUAL(r.num(), 4);    TEST_EQUAL(r.den(), 3);
    TRY((r = {9, 6}));      TEST_EQUAL(r.num(), 3);    TEST_EQUAL(r.den(), 2);
    TRY((r = {10, 6}));     TEST_EQUAL(r.num(), 5);    TEST_EQUAL(r.den(), 3);
    TRY((r = {11, 6}));     TEST_EQUAL(r.num(), 11);   TEST_EQUAL(r.den(), 6);
    TRY((r = {12, 6}));     TEST_EQUAL(r.num(), 2);    TEST_EQUAL(r.den(), 1);
    TRY((r = {2, 0, 4}));   TEST_EQUAL(r.num(), 2);    TEST_EQUAL(r.den(), 1);
    TRY((r = {2, 1, 4}));   TEST_EQUAL(r.num(), 9);    TEST_EQUAL(r.den(), 4);
    TRY((r = {2, 2, 4}));   TEST_EQUAL(r.num(), 5);    TEST_EQUAL(r.den(), 2);
    TRY((r = {2, 3, 4}));   TEST_EQUAL(r.num(), 11);   TEST_EQUAL(r.den(), 4);
    TRY((r = {2, 4, 4}));   TEST_EQUAL(r.num(), 3);    TEST_EQUAL(r.den(), 1);
    TRY((r = {-2, 0, 4}));  TEST_EQUAL(r.num(), -2);   TEST_EQUAL(r.den(), 1);
    TRY((r = {-2, 1, 4}));  TEST_EQUAL(r.num(), -9);   TEST_EQUAL(r.den(), 4);
    TRY((r = {-2, 2, 4}));  TEST_EQUAL(r.num(), -5);   TEST_EQUAL(r.den(), 2);
    TRY((r = {-2, 3, 4}));  TEST_EQUAL(r.num(), -11);  TEST_EQUAL(r.den(), 4);
    TRY((r = {-2, 4, 4}));  TEST_EQUAL(r.num(), -3);   TEST_EQUAL(r.den(), 1);

}

void test_rs_core_rational_mp_integer_properties() {

    MPRational r;

    TEST_EQUAL(r.abs(),              MPRational{});
    TEST_EQUAL(r.sign(),             0);
    TEST_EQUAL(r.whole(),            0);
    TEST_EQUAL(r.fraction(),         MPRational{});
    TEST_EQUAL(r.truncate(),         0);
    TEST_EQUAL(r.signed_fraction(),  MPRational{});

    TRY(r = 42);
    TEST_EQUAL(r.abs(),              MPRational{42});
    TEST_EQUAL(r.sign(),             1);
    TEST_EQUAL(r.whole(),            42);
    TEST_EQUAL(r.fraction(),         MPRational{});
    TEST_EQUAL(r.truncate(),         42);
    TEST_EQUAL(r.signed_fraction(),  MPRational{});

    TRY((r = {3, 4}));
    TEST_EQUAL(r.abs(),              (MPRational{3, 4}));
    TEST_EQUAL(r.sign(),             1);
    TEST_EQUAL(r.whole(),            0);
    TEST_EQUAL(r.fraction(),         (MPRational{3, 4}));
    TEST_EQUAL(r.truncate(),         0);
    TEST_EQUAL(r.signed_fraction(),  (MPRational{3, 4}));

    TRY((r = {9, 4}));
    TEST_EQUAL(r.abs(),              (MPRational{9, 4}));
    TEST_EQUAL(r.sign(),             1);
    TEST_EQUAL(r.whole(),            2);
    TEST_EQUAL(r.fraction(),         (MPRational{1, 4}));
    TEST_EQUAL(r.truncate(),         2);
    TEST_EQUAL(r.signed_fraction(),  (MPRational{1, 4}));

    TRY(r = -42);
    TEST_EQUAL(r.abs(),              MPRational{42});
    TEST_EQUAL(r.sign(),             -1);
    TEST_EQUAL(r.whole(),            -42);
    TEST_EQUAL(r.fraction(),         MPRational{});
    TEST_EQUAL(r.truncate(),         -42);
    TEST_EQUAL(r.signed_fraction(),  MPRational{});

    TRY((r = {-3, 4}));
    TEST_EQUAL(r.abs(),              (MPRational{3, 4}));
    TEST_EQUAL(r.sign(),             -1);
    TEST_EQUAL(r.whole(),            -1);
    TEST_EQUAL(r.fraction(),         (MPRational{1, 4}));
    TEST_EQUAL(r.truncate(),         0);
    TEST_EQUAL(r.signed_fraction(),  (MPRational{-3, 4}));

    TRY((r = {-9, 4}));
    TEST_EQUAL(r.abs(),              (MPRational{9, 4}));
    TEST_EQUAL(r.sign(),             -1);
    TEST_EQUAL(r.whole(),            -3);
    TEST_EQUAL(r.fraction(),         (MPRational{3, 4}));
    TEST_EQUAL(r.truncate(),         -2);
    TEST_EQUAL(r.signed_fraction(),  (MPRational{-1, 4}));

}

void test_rs_core_rational_mp_integer_comparison() {

    MPRational x, y;
    short z;

    /**/                 /**/                   TEST(x == y);  TEST(x <= y);  TEST(x >= y);
    TRY((x = {5, 3}));   TRY((y = {-1}));       TEST(x != y);  TEST(x > y);   TEST(x >= y);
    TRY((x = {5, 3}));   TRY((y = {}));         TEST(x != y);  TEST(x > y);   TEST(x >= y);
    TRY((x = {5, 3}));   TRY((y = {1}));        TEST(x != y);  TEST(x > y);   TEST(x >= y);
    TRY((x = {5, 3}));   TRY((y = {2}));        TEST(x != y);  TEST(x < y);   TEST(x <= y);
    TRY((x = {5, 3}));   TRY((y = {5, 3}));     TEST(x == y);  TEST(x <= y);  TEST(x >= y);
    TRY((x = {5, 3}));   TRY((y = {10, 6}));    TEST(x == y);  TEST(x <= y);  TEST(x >= y);
    TRY((x = {5, 3}));   TRY((y = {49, 30}));   TEST(x != y);  TEST(x > y);   TEST(x >= y);
    TRY((x = {5, 3}));   TRY((y = {51, 30}));   TEST(x != y);  TEST(x < y);   TEST(x <= y);
    TRY((x = {-5, 3}));  TRY((y = {1}));        TEST(x != y);  TEST(x < y);   TEST(x <= y);
    TRY((x = {-5, 3}));  TRY((y = {}));         TEST(x != y);  TEST(x < y);   TEST(x <= y);
    TRY((x = {-5, 3}));  TRY((y = {-1}));       TEST(x != y);  TEST(x < y);   TEST(x <= y);
    TRY((x = {-5, 3}));  TRY((y = {-2}));       TEST(x != y);  TEST(x > y);   TEST(x >= y);
    TRY((x = {-5, 3}));  TRY((y = {-5, 3}));    TEST(x == y);  TEST(x >= y);  TEST(x <= y);
    TRY((x = {-5, 3}));  TRY((y = {-10, 6}));   TEST(x == y);  TEST(x >= y);  TEST(x <= y);
    TRY((x = {-5, 3}));  TRY((y = {-49, 30}));  TEST(x != y);  TEST(x < y);   TEST(x <= y);
    TRY((x = {-5, 3}));  TRY((y = {-51, 30}));  TEST(x != y);  TEST(x > y);   TEST(x >= y);
    TRY((x = {}));       z = 0;                 TEST(x == z);  TEST(x <= z);  TEST(x >= z);
    TRY((x = {5, 3}));   z = -1;                TEST(x != z);  TEST(x > z);   TEST(x >= z);
    TRY((x = {5, 3}));   z = 0;                 TEST(x != z);  TEST(x > z);   TEST(x >= z);
    TRY((x = {5, 3}));   z = 1;                 TEST(x != z);  TEST(x > z);   TEST(x >= z);
    TRY((x = {5, 3}));   z = 2;                 TEST(x != z);  TEST(x < z);   TEST(x <= z);
    TRY((x = {-5, 3}));  z = 1;                 TEST(x != z);  TEST(x < z);   TEST(x <= z);
    TRY((x = {-5, 3}));  z = 0;                 TEST(x != z);  TEST(x < z);   TEST(x <= z);
    TRY((x = {-5, 3}));  z = -1;                TEST(x != z);  TEST(x < z);   TEST(x <= z);
    TRY((x = {-5, 3}));  z = -2;                TEST(x != z);  TEST(x > z);   TEST(x >= z);

}
