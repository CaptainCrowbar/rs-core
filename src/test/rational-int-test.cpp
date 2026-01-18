#include "rs-core/rational.hpp"
#include "rs-core/unit-test.hpp"
#include <format>
#include <optional>
#include <stdexcept>
#include <string>

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

void test_rs_core_rational_int_properties() {

    IntRational r;

    TEST_EQUAL(r.abs(),              IntRational{});
    TEST_EQUAL(r.sign(),             0);
    TEST_EQUAL(r.whole(),            0);
    TEST_EQUAL(r.fraction(),         IntRational{});
    TEST_EQUAL(r.truncate(),         0);
    TEST_EQUAL(r.signed_fraction(),  IntRational{});

    TRY(r = 42);
    TEST_EQUAL(r.abs(),              IntRational{42});
    TEST_EQUAL(r.sign(),             1);
    TEST_EQUAL(r.whole(),            42);
    TEST_EQUAL(r.fraction(),         IntRational{});
    TEST_EQUAL(r.truncate(),         42);
    TEST_EQUAL(r.signed_fraction(),  IntRational{});

    TRY((r = {3, 4}));
    TEST_EQUAL(r.abs(),              (IntRational{3, 4}));
    TEST_EQUAL(r.sign(),             1);
    TEST_EQUAL(r.whole(),            0);
    TEST_EQUAL(r.fraction(),         (IntRational{3, 4}));
    TEST_EQUAL(r.truncate(),         0);
    TEST_EQUAL(r.signed_fraction(),  (IntRational{3, 4}));

    TRY((r = {9, 4}));
    TEST_EQUAL(r.abs(),              (IntRational{9, 4}));
    TEST_EQUAL(r.sign(),             1);
    TEST_EQUAL(r.whole(),            2);
    TEST_EQUAL(r.fraction(),         (IntRational{1, 4}));
    TEST_EQUAL(r.truncate(),         2);
    TEST_EQUAL(r.signed_fraction(),  (IntRational{1, 4}));

    TRY(r = -42);
    TEST_EQUAL(r.abs(),              IntRational{42});
    TEST_EQUAL(r.sign(),             -1);
    TEST_EQUAL(r.whole(),            -42);
    TEST_EQUAL(r.fraction(),         IntRational{});
    TEST_EQUAL(r.truncate(),         -42);
    TEST_EQUAL(r.signed_fraction(),  IntRational{});

    TRY((r = {-3, 4}));
    TEST_EQUAL(r.abs(),              (IntRational{3, 4}));
    TEST_EQUAL(r.sign(),             -1);
    TEST_EQUAL(r.whole(),            -1);
    TEST_EQUAL(r.fraction(),         (IntRational{1, 4}));
    TEST_EQUAL(r.truncate(),         0);
    TEST_EQUAL(r.signed_fraction(),  (IntRational{-3, 4}));

    TRY((r = {-9, 4}));
    TEST_EQUAL(r.abs(),              (IntRational{9, 4}));
    TEST_EQUAL(r.sign(),             -1);
    TEST_EQUAL(r.whole(),            -3);
    TEST_EQUAL(r.fraction(),         (IntRational{3, 4}));
    TEST_EQUAL(r.truncate(),         -2);
    TEST_EQUAL(r.signed_fraction(),  (IntRational{-1, 4}));

}

void test_rs_core_rational_int_arithmetic() {

    IntRational x, y, z;

    TRY((x = {5, 6}));   TRY((y = {9, 10}));   TRY(x += y);  TEST_EQUAL(x, (IntRational{26, 15}));
    TRY((x = {-5, 6}));  TRY((y = {9, 10}));   TRY(x += y);  TEST_EQUAL(x, (IntRational{1, 15}));
    TRY((x = {5, 6}));   TRY((y = {-9, 10}));  TRY(x += y);  TEST_EQUAL(x, (IntRational{-1, 15}));
    TRY((x = {-5, 6}));  TRY((y = {-9, 10}));  TRY(x += y);  TEST_EQUAL(x, (IntRational{-26, 15}));
    TRY((x = {5, 6}));   TRY((y = {9, 10}));   TRY(x -= y);  TEST_EQUAL(x, (IntRational{-1, 15}));
    TRY((x = {-5, 6}));  TRY((y = {9, 10}));   TRY(x -= y);  TEST_EQUAL(x, (IntRational{-26, 15}));
    TRY((x = {5, 6}));   TRY((y = {-9, 10}));  TRY(x -= y);  TEST_EQUAL(x, (IntRational{26, 15}));
    TRY((x = {-5, 6}));  TRY((y = {-9, 10}));  TRY(x -= y);  TEST_EQUAL(x, (IntRational{1, 15}));
    TRY((x = {5, 6}));   TRY((y = {9, 10}));   TRY(x *= y);  TEST_EQUAL(x, (IntRational{3, 4}));
    TRY((x = {-5, 6}));  TRY((y = {9, 10}));   TRY(x *= y);  TEST_EQUAL(x, (IntRational{-3, 4}));
    TRY((x = {5, 6}));   TRY((y = {-9, 10}));  TRY(x *= y);  TEST_EQUAL(x, (IntRational{-3, 4}));
    TRY((x = {-5, 6}));  TRY((y = {-9, 10}));  TRY(x *= y);  TEST_EQUAL(x, (IntRational{3, 4}));
    TRY((x = {5, 6}));   TRY((y = {9, 10}));   TRY(x /= y);  TEST_EQUAL(x, (IntRational{25, 27}));
    TRY((x = {-5, 6}));  TRY((y = {9, 10}));   TRY(x /= y);  TEST_EQUAL(x, (IntRational{-25, 27}));
    TRY((x = {5, 6}));   TRY((y = {-9, 10}));  TRY(x /= y);  TEST_EQUAL(x, (IntRational{-25, 27}));
    TRY((x = {-5, 6}));  TRY((y = {-9, 10}));  TRY(x /= y);  TEST_EQUAL(x, (IntRational{25, 27}));

    TRY((x = {5, 6}));   TRY((y = {9, 10}));   TRY(z = x + y);  TEST_EQUAL(z, (IntRational{26, 15}));
    TRY((x = {-5, 6}));  TRY((y = {9, 10}));   TRY(z = x + y);  TEST_EQUAL(z, (IntRational{1, 15}));
    TRY((x = {5, 6}));   TRY((y = {-9, 10}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{-1, 15}));
    TRY((x = {-5, 6}));  TRY((y = {-9, 10}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{-26, 15}));
    TRY((x = {5, 6}));   TRY((y = {9, 10}));   TRY(z = x - y);  TEST_EQUAL(z, (IntRational{-1, 15}));
    TRY((x = {-5, 6}));  TRY((y = {9, 10}));   TRY(z = x - y);  TEST_EQUAL(z, (IntRational{-26, 15}));
    TRY((x = {5, 6}));   TRY((y = {-9, 10}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{26, 15}));
    TRY((x = {-5, 6}));  TRY((y = {-9, 10}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{1, 15}));
    TRY((x = {5, 6}));   TRY((y = {9, 10}));   TRY(z = x * y);  TEST_EQUAL(z, (IntRational{3, 4}));
    TRY((x = {-5, 6}));  TRY((y = {9, 10}));   TRY(z = x * y);  TEST_EQUAL(z, (IntRational{-3, 4}));
    TRY((x = {5, 6}));   TRY((y = {-9, 10}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{-3, 4}));
    TRY((x = {-5, 6}));  TRY((y = {-9, 10}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{3, 4}));
    TRY((x = {5, 6}));   TRY((y = {9, 10}));   TRY(z = x / y);  TEST_EQUAL(z, (IntRational{25, 27}));
    TRY((x = {-5, 6}));  TRY((y = {9, 10}));   TRY(z = x / y);  TEST_EQUAL(z, (IntRational{-25, 27}));
    TRY((x = {5, 6}));   TRY((y = {-9, 10}));  TRY(z = x / y);  TEST_EQUAL(z, (IntRational{-25, 27}));
    TRY((x = {-5, 6}));  TRY((y = {-9, 10}));  TRY(z = x / y);  TEST_EQUAL(z, (IntRational{25, 27}));

    TRY((x = {0, 6}));   TRY((y = {0, 6}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {0, 6}));   TRY((y = {1, 6}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{1, 6}));
    TRY((x = {0, 6}));   TRY((y = {2, 6}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{1, 3}));
    TRY((x = {0, 6}));   TRY((y = {3, 6}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{1, 2}));
    TRY((x = {0, 6}));   TRY((y = {4, 6}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{2, 3}));
    TRY((x = {0, 6}));   TRY((y = {5, 6}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{5, 6}));
    TRY((x = {0, 6}));   TRY((y = {6, 6}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{1, 1}));
    TRY((x = {1, 6}));   TRY((y = {0, 6}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{1, 6}));
    TRY((x = {1, 6}));   TRY((y = {1, 6}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{1, 3}));
    TRY((x = {1, 6}));   TRY((y = {2, 6}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{1, 2}));
    TRY((x = {1, 6}));   TRY((y = {3, 6}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{2, 3}));
    TRY((x = {1, 6}));   TRY((y = {4, 6}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{5, 6}));
    TRY((x = {1, 6}));   TRY((y = {5, 6}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{1, 1}));
    TRY((x = {1, 6}));   TRY((y = {6, 6}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{7, 6}));
    TRY((x = {2, 6}));   TRY((y = {0, 6}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{1, 3}));
    TRY((x = {2, 6}));   TRY((y = {1, 6}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{1, 2}));
    TRY((x = {2, 6}));   TRY((y = {2, 6}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{2, 3}));
    TRY((x = {2, 6}));   TRY((y = {3, 6}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{5, 6}));
    TRY((x = {2, 6}));   TRY((y = {4, 6}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{1, 1}));
    TRY((x = {2, 6}));   TRY((y = {5, 6}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{7, 6}));
    TRY((x = {2, 6}));   TRY((y = {6, 6}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{4, 3}));
    TRY((x = {3, 6}));   TRY((y = {0, 6}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{1, 2}));
    TRY((x = {3, 6}));   TRY((y = {1, 6}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{2, 3}));
    TRY((x = {3, 6}));   TRY((y = {2, 6}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{5, 6}));
    TRY((x = {3, 6}));   TRY((y = {3, 6}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{1, 1}));
    TRY((x = {3, 6}));   TRY((y = {4, 6}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{7, 6}));
    TRY((x = {3, 6}));   TRY((y = {5, 6}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{4, 3}));
    TRY((x = {3, 6}));   TRY((y = {6, 6}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{3, 2}));
    TRY((x = {4, 6}));   TRY((y = {0, 6}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{2, 3}));
    TRY((x = {4, 6}));   TRY((y = {1, 6}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{5, 6}));
    TRY((x = {4, 6}));   TRY((y = {2, 6}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{1, 1}));
    TRY((x = {4, 6}));   TRY((y = {3, 6}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{7, 6}));
    TRY((x = {4, 6}));   TRY((y = {4, 6}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{4, 3}));
    TRY((x = {4, 6}));   TRY((y = {5, 6}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{3, 2}));
    TRY((x = {4, 6}));   TRY((y = {6, 6}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{5, 3}));
    TRY((x = {5, 6}));   TRY((y = {0, 6}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{5, 6}));
    TRY((x = {5, 6}));   TRY((y = {1, 6}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{1, 1}));
    TRY((x = {5, 6}));   TRY((y = {2, 6}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{7, 6}));
    TRY((x = {5, 6}));   TRY((y = {3, 6}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{4, 3}));
    TRY((x = {5, 6}));   TRY((y = {4, 6}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{3, 2}));
    TRY((x = {5, 6}));   TRY((y = {5, 6}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{5, 3}));
    TRY((x = {5, 6}));   TRY((y = {6, 6}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{11, 6}));
    TRY((x = {6, 6}));   TRY((y = {0, 6}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{1, 1}));
    TRY((x = {6, 6}));   TRY((y = {1, 6}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{7, 6}));
    TRY((x = {6, 6}));   TRY((y = {2, 6}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{4, 3}));
    TRY((x = {6, 6}));   TRY((y = {3, 6}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{3, 2}));
    TRY((x = {6, 6}));   TRY((y = {4, 6}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{5, 3}));
    TRY((x = {6, 6}));   TRY((y = {5, 6}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{11, 6}));
    TRY((x = {6, 6}));   TRY((y = {6, 6}));  TRY(z = x + y);  TEST_EQUAL(z, (IntRational{2, 1}));

    TRY((x = {0, 6}));   TRY((y = {0, 6}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {0, 6}));   TRY((y = {1, 6}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{-1, 6}));
    TRY((x = {0, 6}));   TRY((y = {2, 6}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{-1, 3}));
    TRY((x = {0, 6}));   TRY((y = {3, 6}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{-1, 2}));
    TRY((x = {0, 6}));   TRY((y = {4, 6}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{-2, 3}));
    TRY((x = {0, 6}));   TRY((y = {5, 6}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{-5, 6}));
    TRY((x = {0, 6}));   TRY((y = {6, 6}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{-1, 1}));
    TRY((x = {1, 6}));   TRY((y = {0, 6}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{1, 6}));
    TRY((x = {1, 6}));   TRY((y = {1, 6}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {1, 6}));   TRY((y = {2, 6}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{-1, 6}));
    TRY((x = {1, 6}));   TRY((y = {3, 6}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{-1, 3}));
    TRY((x = {1, 6}));   TRY((y = {4, 6}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{-1, 2}));
    TRY((x = {1, 6}));   TRY((y = {5, 6}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{-2, 3}));
    TRY((x = {1, 6}));   TRY((y = {6, 6}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{-5, 6}));
    TRY((x = {2, 6}));   TRY((y = {0, 6}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{1, 3}));
    TRY((x = {2, 6}));   TRY((y = {1, 6}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{1, 6}));
    TRY((x = {2, 6}));   TRY((y = {2, 6}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {2, 6}));   TRY((y = {3, 6}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{-1, 6}));
    TRY((x = {2, 6}));   TRY((y = {4, 6}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{-1, 3}));
    TRY((x = {2, 6}));   TRY((y = {5, 6}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{-1, 2}));
    TRY((x = {2, 6}));   TRY((y = {6, 6}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{-2, 3}));
    TRY((x = {3, 6}));   TRY((y = {0, 6}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{1, 2}));
    TRY((x = {3, 6}));   TRY((y = {1, 6}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{1, 3}));
    TRY((x = {3, 6}));   TRY((y = {2, 6}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{1, 6}));
    TRY((x = {3, 6}));   TRY((y = {3, 6}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {3, 6}));   TRY((y = {4, 6}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{-1, 6}));
    TRY((x = {3, 6}));   TRY((y = {5, 6}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{-1, 3}));
    TRY((x = {3, 6}));   TRY((y = {6, 6}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{-1, 2}));
    TRY((x = {4, 6}));   TRY((y = {0, 6}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{2, 3}));
    TRY((x = {4, 6}));   TRY((y = {1, 6}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{1, 2}));
    TRY((x = {4, 6}));   TRY((y = {2, 6}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{1, 3}));
    TRY((x = {4, 6}));   TRY((y = {3, 6}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{1, 6}));
    TRY((x = {4, 6}));   TRY((y = {4, 6}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {4, 6}));   TRY((y = {5, 6}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{-1, 6}));
    TRY((x = {4, 6}));   TRY((y = {6, 6}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{-1, 3}));
    TRY((x = {5, 6}));   TRY((y = {0, 6}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{5, 6}));
    TRY((x = {5, 6}));   TRY((y = {1, 6}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{2, 3}));
    TRY((x = {5, 6}));   TRY((y = {2, 6}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{1, 2}));
    TRY((x = {5, 6}));   TRY((y = {3, 6}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{1, 3}));
    TRY((x = {5, 6}));   TRY((y = {4, 6}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{1, 6}));
    TRY((x = {5, 6}));   TRY((y = {5, 6}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {5, 6}));   TRY((y = {6, 6}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{-1, 6}));
    TRY((x = {6, 6}));   TRY((y = {0, 6}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{1, 1}));
    TRY((x = {6, 6}));   TRY((y = {1, 6}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{5, 6}));
    TRY((x = {6, 6}));   TRY((y = {2, 6}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{2, 3}));
    TRY((x = {6, 6}));   TRY((y = {3, 6}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{1, 2}));
    TRY((x = {6, 6}));   TRY((y = {4, 6}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{1, 3}));
    TRY((x = {6, 6}));   TRY((y = {5, 6}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{1, 6}));
    TRY((x = {6, 6}));   TRY((y = {6, 6}));  TRY(z = x - y);  TEST_EQUAL(z, (IntRational{0, 1}));

    TRY((x = {0, 6}));   TRY((y = {0, 6}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {0, 6}));   TRY((y = {1, 6}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {0, 6}));   TRY((y = {2, 6}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {0, 6}));   TRY((y = {3, 6}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {0, 6}));   TRY((y = {4, 6}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {0, 6}));   TRY((y = {5, 6}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {0, 6}));   TRY((y = {6, 6}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {1, 6}));   TRY((y = {0, 6}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {1, 6}));   TRY((y = {1, 6}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{1, 36}));
    TRY((x = {1, 6}));   TRY((y = {2, 6}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{1, 18}));
    TRY((x = {1, 6}));   TRY((y = {3, 6}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{1, 12}));
    TRY((x = {1, 6}));   TRY((y = {4, 6}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{1, 9}));
    TRY((x = {1, 6}));   TRY((y = {5, 6}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{5, 36}));
    TRY((x = {1, 6}));   TRY((y = {6, 6}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{1, 6}));
    TRY((x = {2, 6}));   TRY((y = {0, 6}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {2, 6}));   TRY((y = {1, 6}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{1, 18}));
    TRY((x = {2, 6}));   TRY((y = {2, 6}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{1, 9}));
    TRY((x = {2, 6}));   TRY((y = {3, 6}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{1, 6}));
    TRY((x = {2, 6}));   TRY((y = {4, 6}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{2, 9}));
    TRY((x = {2, 6}));   TRY((y = {5, 6}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{5, 18}));
    TRY((x = {2, 6}));   TRY((y = {6, 6}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{1, 3}));
    TRY((x = {3, 6}));   TRY((y = {0, 6}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {3, 6}));   TRY((y = {1, 6}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{1, 12}));
    TRY((x = {3, 6}));   TRY((y = {2, 6}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{1, 6}));
    TRY((x = {3, 6}));   TRY((y = {3, 6}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{1, 4}));
    TRY((x = {3, 6}));   TRY((y = {4, 6}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{1, 3}));
    TRY((x = {3, 6}));   TRY((y = {5, 6}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{5, 12}));
    TRY((x = {3, 6}));   TRY((y = {6, 6}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{1, 2}));
    TRY((x = {4, 6}));   TRY((y = {0, 6}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {4, 6}));   TRY((y = {1, 6}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{1, 9}));
    TRY((x = {4, 6}));   TRY((y = {2, 6}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{2, 9}));
    TRY((x = {4, 6}));   TRY((y = {3, 6}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{1, 3}));
    TRY((x = {4, 6}));   TRY((y = {4, 6}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{4, 9}));
    TRY((x = {4, 6}));   TRY((y = {5, 6}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{5, 9}));
    TRY((x = {4, 6}));   TRY((y = {6, 6}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{2, 3}));
    TRY((x = {5, 6}));   TRY((y = {0, 6}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {5, 6}));   TRY((y = {1, 6}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{5, 36}));
    TRY((x = {5, 6}));   TRY((y = {2, 6}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{5, 18}));
    TRY((x = {5, 6}));   TRY((y = {3, 6}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{5, 12}));
    TRY((x = {5, 6}));   TRY((y = {4, 6}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{5, 9}));
    TRY((x = {5, 6}));   TRY((y = {5, 6}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{25, 36}));
    TRY((x = {5, 6}));   TRY((y = {6, 6}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{5, 6}));
    TRY((x = {6, 6}));   TRY((y = {0, 6}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {6, 6}));   TRY((y = {1, 6}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{1, 6}));
    TRY((x = {6, 6}));   TRY((y = {2, 6}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{1, 3}));
    TRY((x = {6, 6}));   TRY((y = {3, 6}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{1, 2}));
    TRY((x = {6, 6}));   TRY((y = {4, 6}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{2, 3}));
    TRY((x = {6, 6}));   TRY((y = {5, 6}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{5, 6}));
    TRY((x = {6, 6}));   TRY((y = {6, 6}));  TRY(z = x * y);  TEST_EQUAL(z, (IntRational{1, 1}));

    TRY((x = {0, 6}));   TRY((y = {1, 6}));  TRY(z = x / y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {0, 6}));   TRY((y = {2, 6}));  TRY(z = x / y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {0, 6}));   TRY((y = {3, 6}));  TRY(z = x / y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {0, 6}));   TRY((y = {4, 6}));  TRY(z = x / y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {0, 6}));   TRY((y = {5, 6}));  TRY(z = x / y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {0, 6}));   TRY((y = {6, 6}));  TRY(z = x / y);  TEST_EQUAL(z, (IntRational{0, 1}));
    TRY((x = {1, 6}));   TRY((y = {1, 6}));  TRY(z = x / y);  TEST_EQUAL(z, (IntRational{1, 1}));
    TRY((x = {1, 6}));   TRY((y = {2, 6}));  TRY(z = x / y);  TEST_EQUAL(z, (IntRational{1, 2}));
    TRY((x = {1, 6}));   TRY((y = {3, 6}));  TRY(z = x / y);  TEST_EQUAL(z, (IntRational{1, 3}));
    TRY((x = {1, 6}));   TRY((y = {4, 6}));  TRY(z = x / y);  TEST_EQUAL(z, (IntRational{1, 4}));
    TRY((x = {1, 6}));   TRY((y = {5, 6}));  TRY(z = x / y);  TEST_EQUAL(z, (IntRational{1, 5}));
    TRY((x = {1, 6}));   TRY((y = {6, 6}));  TRY(z = x / y);  TEST_EQUAL(z, (IntRational{1, 6}));
    TRY((x = {2, 6}));   TRY((y = {1, 6}));  TRY(z = x / y);  TEST_EQUAL(z, (IntRational{2, 1}));
    TRY((x = {2, 6}));   TRY((y = {2, 6}));  TRY(z = x / y);  TEST_EQUAL(z, (IntRational{1, 1}));
    TRY((x = {2, 6}));   TRY((y = {3, 6}));  TRY(z = x / y);  TEST_EQUAL(z, (IntRational{2, 3}));
    TRY((x = {2, 6}));   TRY((y = {4, 6}));  TRY(z = x / y);  TEST_EQUAL(z, (IntRational{1, 2}));
    TRY((x = {2, 6}));   TRY((y = {5, 6}));  TRY(z = x / y);  TEST_EQUAL(z, (IntRational{2, 5}));
    TRY((x = {2, 6}));   TRY((y = {6, 6}));  TRY(z = x / y);  TEST_EQUAL(z, (IntRational{1, 3}));
    TRY((x = {3, 6}));   TRY((y = {1, 6}));  TRY(z = x / y);  TEST_EQUAL(z, (IntRational{3, 1}));
    TRY((x = {3, 6}));   TRY((y = {2, 6}));  TRY(z = x / y);  TEST_EQUAL(z, (IntRational{3, 2}));
    TRY((x = {3, 6}));   TRY((y = {3, 6}));  TRY(z = x / y);  TEST_EQUAL(z, (IntRational{1, 1}));
    TRY((x = {3, 6}));   TRY((y = {4, 6}));  TRY(z = x / y);  TEST_EQUAL(z, (IntRational{3, 4}));
    TRY((x = {3, 6}));   TRY((y = {5, 6}));  TRY(z = x / y);  TEST_EQUAL(z, (IntRational{3, 5}));
    TRY((x = {3, 6}));   TRY((y = {6, 6}));  TRY(z = x / y);  TEST_EQUAL(z, (IntRational{1, 2}));
    TRY((x = {4, 6}));   TRY((y = {1, 6}));  TRY(z = x / y);  TEST_EQUAL(z, (IntRational{4, 1}));
    TRY((x = {4, 6}));   TRY((y = {2, 6}));  TRY(z = x / y);  TEST_EQUAL(z, (IntRational{2, 1}));
    TRY((x = {4, 6}));   TRY((y = {3, 6}));  TRY(z = x / y);  TEST_EQUAL(z, (IntRational{4, 3}));
    TRY((x = {4, 6}));   TRY((y = {4, 6}));  TRY(z = x / y);  TEST_EQUAL(z, (IntRational{1, 1}));
    TRY((x = {4, 6}));   TRY((y = {5, 6}));  TRY(z = x / y);  TEST_EQUAL(z, (IntRational{4, 5}));
    TRY((x = {4, 6}));   TRY((y = {6, 6}));  TRY(z = x / y);  TEST_EQUAL(z, (IntRational{2, 3}));
    TRY((x = {5, 6}));   TRY((y = {1, 6}));  TRY(z = x / y);  TEST_EQUAL(z, (IntRational{5, 1}));
    TRY((x = {5, 6}));   TRY((y = {2, 6}));  TRY(z = x / y);  TEST_EQUAL(z, (IntRational{5, 2}));
    TRY((x = {5, 6}));   TRY((y = {3, 6}));  TRY(z = x / y);  TEST_EQUAL(z, (IntRational{5, 3}));
    TRY((x = {5, 6}));   TRY((y = {4, 6}));  TRY(z = x / y);  TEST_EQUAL(z, (IntRational{5, 4}));
    TRY((x = {5, 6}));   TRY((y = {5, 6}));  TRY(z = x / y);  TEST_EQUAL(z, (IntRational{1, 1}));
    TRY((x = {5, 6}));   TRY((y = {6, 6}));  TRY(z = x / y);  TEST_EQUAL(z, (IntRational{5, 6}));
    TRY((x = {6, 6}));   TRY((y = {1, 6}));  TRY(z = x / y);  TEST_EQUAL(z, (IntRational{6, 1}));
    TRY((x = {6, 6}));   TRY((y = {2, 6}));  TRY(z = x / y);  TEST_EQUAL(z, (IntRational{3, 1}));
    TRY((x = {6, 6}));   TRY((y = {3, 6}));  TRY(z = x / y);  TEST_EQUAL(z, (IntRational{2, 1}));
    TRY((x = {6, 6}));   TRY((y = {4, 6}));  TRY(z = x / y);  TEST_EQUAL(z, (IntRational{3, 2}));
    TRY((x = {6, 6}));   TRY((y = {5, 6}));  TRY(z = x / y);  TEST_EQUAL(z, (IntRational{6, 5}));
    TRY((x = {6, 6}));   TRY((y = {6, 6}));  TRY(z = x / y);  TEST_EQUAL(z, (IntRational{1, 1}));

}

void test_rs_core_rational_int_comparison() {

    IntRational x, y;

    /**/                 /**/                   TEST(x == y);  TEST(x <= y);  TEST(x >= y);
    TRY((x = {5, 3}));   TRY((y = {-1}));       TEST(x != y);  TEST(x > y);   TEST(x >= y);
    TRY((x = {5, 3}));   TRY((y = {0}));        TEST(x != y);  TEST(x > y);   TEST(x >= y);
    TRY((x = {5, 3}));   TRY((y = {1}));        TEST(x != y);  TEST(x > y);   TEST(x >= y);
    TRY((x = {5, 3}));   TRY((y = {2}));        TEST(x != y);  TEST(x < y);   TEST(x <= y);
    TRY((x = {5, 3}));   TRY((y = {5, 3}));     TEST(x == y);  TEST(x <= y);  TEST(x >= y);
    TRY((x = {5, 3}));   TRY((y = {10, 6}));    TEST(x == y);  TEST(x <= y);  TEST(x >= y);
    TRY((x = {5, 3}));   TRY((y = {49, 30}));   TEST(x != y);  TEST(x > y);   TEST(x >= y);
    TRY((x = {5, 3}));   TRY((y = {51, 30}));   TEST(x != y);  TEST(x < y);   TEST(x <= y);
    TRY((x = {-5, 3}));  TRY((y = {1}));        TEST(x != y);  TEST(x < y);   TEST(x <= y);
    TRY((x = {-5, 3}));  TRY((y = {0}));        TEST(x != y);  TEST(x < y);   TEST(x <= y);
    TRY((x = {-5, 3}));  TRY((y = {-1}));       TEST(x != y);  TEST(x < y);   TEST(x <= y);
    TRY((x = {-5, 3}));  TRY((y = {-2}));       TEST(x != y);  TEST(x > y);   TEST(x >= y);
    TRY((x = {-5, 3}));  TRY((y = {-5, 3}));    TEST(x == y);  TEST(x >= y);  TEST(x <= y);
    TRY((x = {-5, 3}));  TRY((y = {-10, 6}));   TEST(x == y);  TEST(x >= y);  TEST(x <= y);
    TRY((x = {-5, 3}));  TRY((y = {-49, 30}));  TEST(x != y);  TEST(x < y);   TEST(x <= y);
    TRY((x = {-5, 3}));  TRY((y = {-51, 30}));  TEST(x != y);  TEST(x > y);   TEST(x >= y);

}

void test_rs_core_rational_int_formatting() {

    IntRational r;
    std::string s;

    TRY((r = {}));          TRY(s = r.to_string());  TEST_EQUAL(s, "0");      TRY(s = r.mixed());  TEST_EQUAL(s, "0");
    TRY((r = {42}));        TRY(s = r.to_string());  TEST_EQUAL(s, "42");     TRY(s = r.mixed());  TEST_EQUAL(s, "42");
    TRY((r = {-42}));       TRY(s = r.to_string());  TEST_EQUAL(s, "-42");    TRY(s = r.mixed());  TEST_EQUAL(s, "-42");
    TRY((r = {2, 3}));      TRY(s = r.to_string());  TEST_EQUAL(s, "2/3");    TRY(s = r.mixed());  TEST_EQUAL(s, "2/3");
    TRY((r = {-2, 3}));     TRY(s = r.to_string());  TEST_EQUAL(s, "-2/3");   TRY(s = r.mixed());  TEST_EQUAL(s, "-2/3");
    TRY((r = {5, 3}));      TRY(s = r.to_string());  TEST_EQUAL(s, "5/3");    TRY(s = r.mixed());  TEST_EQUAL(s, "1 2/3");
    TRY((r = {-5, 3}));     TRY(s = r.to_string());  TEST_EQUAL(s, "-5/3");   TRY(s = r.mixed());  TEST_EQUAL(s, "-1 2/3");
    TRY((r = {100, 30}));   TRY(s = r.to_string());  TEST_EQUAL(s, "10/3");   TRY(s = r.mixed());  TEST_EQUAL(s, "3 1/3");
    TRY((r = {-100, 30}));  TRY(s = r.to_string());  TEST_EQUAL(s, "-10/3");  TRY(s = r.mixed());  TEST_EQUAL(s, "-3 1/3");

    TRY((r = {}));          TRY(s = std::format("{}", r));  TEST_EQUAL(s, "0");      TRY(s = std::format("{:m}", r));  TEST_EQUAL(s, "0");
    TRY((r = {42}));        TRY(s = std::format("{}", r));  TEST_EQUAL(s, "42");     TRY(s = std::format("{:m}", r));  TEST_EQUAL(s, "42");
    TRY((r = {-42}));       TRY(s = std::format("{}", r));  TEST_EQUAL(s, "-42");    TRY(s = std::format("{:m}", r));  TEST_EQUAL(s, "-42");
    TRY((r = {2, 3}));      TRY(s = std::format("{}", r));  TEST_EQUAL(s, "2/3");    TRY(s = std::format("{:m}", r));  TEST_EQUAL(s, "2/3");
    TRY((r = {-2, 3}));     TRY(s = std::format("{}", r));  TEST_EQUAL(s, "-2/3");   TRY(s = std::format("{:m}", r));  TEST_EQUAL(s, "-2/3");
    TRY((r = {5, 3}));      TRY(s = std::format("{}", r));  TEST_EQUAL(s, "5/3");    TRY(s = std::format("{:m}", r));  TEST_EQUAL(s, "1 2/3");
    TRY((r = {-5, 3}));     TRY(s = std::format("{}", r));  TEST_EQUAL(s, "-5/3");   TRY(s = std::format("{:m}", r));  TEST_EQUAL(s, "-1 2/3");
    TRY((r = {100, 30}));   TRY(s = std::format("{}", r));  TEST_EQUAL(s, "10/3");   TRY(s = std::format("{:m}", r));  TEST_EQUAL(s, "3 1/3");
    TRY((r = {-100, 30}));  TRY(s = std::format("{}", r));  TEST_EQUAL(s, "-10/3");  TRY(s = std::format("{:m}", r));  TEST_EQUAL(s, "-3 1/3");

}

void test_rs_core_rational_int_parsing() {

    IntRational r;
    std::optional<IntRational> opt;

    TRY(r = IntRational("0"));       TEST_EQUAL(r.num(), 0);    TEST_EQUAL(r.den(), 1);
    TRY(r = IntRational("42"));      TEST_EQUAL(r.num(), 42);   TEST_EQUAL(r.den(), 1);
    TRY(r = IntRational("-42"));     TEST_EQUAL(r.num(), -42);  TEST_EQUAL(r.den(), 1);
    TRY(r = IntRational("1/2"));     TEST_EQUAL(r.num(), 1);    TEST_EQUAL(r.den(), 2);
    TRY(r = IntRational("-1/2"));    TEST_EQUAL(r.num(), -1);   TEST_EQUAL(r.den(), 2);
    TRY(r = IntRational("30/12"));   TEST_EQUAL(r.num(), 5);    TEST_EQUAL(r.den(), 2);
    TRY(r = IntRational("-30/12"));  TEST_EQUAL(r.num(), -5);   TEST_EQUAL(r.den(), 2);
    TRY(r = IntRational("2 3/4"));   TEST_EQUAL(r.num(), 11);   TEST_EQUAL(r.den(), 4);
    TRY(r = IntRational("-2 3/4"));  TEST_EQUAL(r.num(), -11);  TEST_EQUAL(r.den(), 4);
    TRY(r = IntRational("4 6/8"));   TEST_EQUAL(r.num(), 19);   TEST_EQUAL(r.den(), 4);
    TRY(r = IntRational("-4 6/8"));  TEST_EQUAL(r.num(), -19);  TEST_EQUAL(r.den(), 4);

    TEST_THROW(IntRational("1 2"),    std::invalid_argument, "Invalid rational");
    TEST_THROW(IntRational("/1"),     std::invalid_argument, "Invalid rational");
    TEST_THROW(IntRational("1/"),     std::invalid_argument, "Invalid rational");
    TEST_THROW(IntRational("1/2/3"),  std::invalid_argument, "Invalid rational");
    TEST_THROW(IntRational("1.5"),    std::invalid_argument, "Invalid rational");

    TRY(opt = IntRational::parse("0"));       TEST(opt.has_value());  TEST_EQUAL(opt.value().num(), 0);    TEST_EQUAL(opt.value().den(), 1);
    TRY(opt = IntRational::parse("42"));      TEST(opt.has_value());  TEST_EQUAL(opt.value().num(), 42);   TEST_EQUAL(opt.value().den(), 1);
    TRY(opt = IntRational::parse("-42"));     TEST(opt.has_value());  TEST_EQUAL(opt.value().num(), -42);  TEST_EQUAL(opt.value().den(), 1);
    TRY(opt = IntRational::parse("1/2"));     TEST(opt.has_value());  TEST_EQUAL(opt.value().num(), 1);    TEST_EQUAL(opt.value().den(), 2);
    TRY(opt = IntRational::parse("-1/2"));    TEST(opt.has_value());  TEST_EQUAL(opt.value().num(), -1);   TEST_EQUAL(opt.value().den(), 2);
    TRY(opt = IntRational::parse("30/12"));   TEST(opt.has_value());  TEST_EQUAL(opt.value().num(), 5);    TEST_EQUAL(opt.value().den(), 2);
    TRY(opt = IntRational::parse("-30/12"));  TEST(opt.has_value());  TEST_EQUAL(opt.value().num(), -5);   TEST_EQUAL(opt.value().den(), 2);
    TRY(opt = IntRational::parse("2 3/4"));   TEST(opt.has_value());  TEST_EQUAL(opt.value().num(), 11);   TEST_EQUAL(opt.value().den(), 4);
    TRY(opt = IntRational::parse("-2 3/4"));  TEST(opt.has_value());  TEST_EQUAL(opt.value().num(), -11);  TEST_EQUAL(opt.value().den(), 4);
    TRY(opt = IntRational::parse("4 6/8"));   TEST(opt.has_value());  TEST_EQUAL(opt.value().num(), 19);   TEST_EQUAL(opt.value().den(), 4);
    TRY(opt = IntRational::parse("-4 6/8"));  TEST(opt.has_value());  TEST_EQUAL(opt.value().num(), -19);  TEST_EQUAL(opt.value().den(), 4);

    TRY(opt = IntRational::parse("1 2"));    TEST(! opt.has_value());
    TRY(opt = IntRational::parse("/1"));     TEST(! opt.has_value());
    TRY(opt = IntRational::parse("1/"));     TEST(! opt.has_value());
    TRY(opt = IntRational::parse("1/2/3"));  TEST(! opt.has_value());
    TRY(opt = IntRational::parse("1.5"));    TEST(! opt.has_value());

}
