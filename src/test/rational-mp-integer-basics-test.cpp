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
