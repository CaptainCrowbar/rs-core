#include "rs-core/rational.hpp"
#include "rs-core/unit-test.hpp"

using namespace RS;

void test_rs_core_rational_int_concepts() {

    TEST(! SignedIntegral<IntRational>);
    TEST(! UnsignedIntegral<IntRational>);
    TEST(! Integral<IntRational>);
    TEST(! FloatingPoint<IntRational>);
    TEST(! FixedPointArithmetic<IntRational>);
    TEST(RationalArithmetic<IntRational>);
    TEST(Arithmetic<IntRational>);

}

void test_rs_core_rational_int_construction() {

    IntRational r;

    /**/                    TEST_EQUAL(r.num(), 0);    TEST_EQUAL(r.den(), 1);
    TRY((r = 42));          TEST_EQUAL(r.num(), 42);   TEST_EQUAL(r.den(), 1);
    TRY((r = -42));         TEST_EQUAL(r.num(), -42);  TEST_EQUAL(r.den(), 1);
    TRY((r = 0));           TEST_EQUAL(r.num(), 0);    TEST_EQUAL(r.den(), 1);
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
