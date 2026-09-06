#include "rs-core/rational.hpp"
#include "rs-core/unit-test.hpp"

using namespace RS;

void test_rs_core_rational_int_properties() {

    IntRational r;

    TEST_EQUAL(r.abs(),                  0);
    TEST_EQUAL(r.sign(),                 0);
    TEST_EQUAL(r.whole(),                0);
    TEST_EQUAL(r.fraction(),             0);
    TEST_EQUAL(r.truncate(),             0);
    TEST_EQUAL(r.signed_fraction(),      0);
    TEST_EQUAL(r.round_td(),             0);
    TEST_EQUAL(r.round_tt(),             0);
    TEST_EQUAL(r.round_tu(),             0);
    TEST_EQUAL(r.to_floating<double>(),  0);

    TRY(r = 42);
    TEST_EQUAL(r.abs(),                  IntRational{42});
    TEST_EQUAL(r.inverse(),              (IntRational{1, 42}));
    TEST_EQUAL(r.sign(),                 1);
    TEST_EQUAL(r.whole(),                42);
    TEST_EQUAL(r.fraction(),             0);
    TEST_EQUAL(r.truncate(),             42);
    TEST_EQUAL(r.signed_fraction(),      0);
    TEST_EQUAL(r.round_td(),             42);
    TEST_EQUAL(r.round_tt(),             42);
    TEST_EQUAL(r.round_tu(),             42);
    TEST_EQUAL(r.to_floating<double>(),  42);

    TRY((r = {3, 2}));
    TEST_EQUAL(r.abs(),                  (IntRational{3, 2}));
    TEST_EQUAL(r.inverse(),              (IntRational{2, 3}));
    TEST_EQUAL(r.sign(),                 1);
    TEST_EQUAL(r.whole(),                1);
    TEST_EQUAL(r.fraction(),             (IntRational{1, 2}));
    TEST_EQUAL(r.truncate(),             1);
    TEST_EQUAL(r.signed_fraction(),      (IntRational{1, 2}));
    TEST_EQUAL(r.round_td(),             1);
    TEST_EQUAL(r.round_tt(),             1);
    TEST_EQUAL(r.round_tu(),             2);
    TEST_EQUAL(r.to_floating<double>(),  1.5);

    TRY((r = {3, 4}));
    TEST_EQUAL(r.abs(),                  (IntRational{3, 4}));
    TEST_EQUAL(r.inverse(),              (IntRational{4, 3}));
    TEST_EQUAL(r.sign(),                 1);
    TEST_EQUAL(r.whole(),                0);
    TEST_EQUAL(r.fraction(),             (IntRational{3, 4}));
    TEST_EQUAL(r.truncate(),             0);
    TEST_EQUAL(r.signed_fraction(),      (IntRational{3, 4}));
    TEST_EQUAL(r.round_td(),             1);
    TEST_EQUAL(r.round_tt(),             1);
    TEST_EQUAL(r.round_tu(),             1);
    TEST_EQUAL(r.to_floating<double>(),  0.75);

    TRY((r = {9, 4}));
    TEST_EQUAL(r.abs(),                  (IntRational{9, 4}));
    TEST_EQUAL(r.inverse(),              (IntRational{4, 9}));
    TEST_EQUAL(r.sign(),                 1);
    TEST_EQUAL(r.whole(),                2);
    TEST_EQUAL(r.fraction(),             (IntRational{1, 4}));
    TEST_EQUAL(r.truncate(),             2);
    TEST_EQUAL(r.signed_fraction(),      (IntRational{1, 4}));
    TEST_EQUAL(r.round_td(),             2);
    TEST_EQUAL(r.round_tt(),             2);
    TEST_EQUAL(r.round_tu(),             2);
    TEST_EQUAL(r.to_floating<double>(),  2.25);

    TRY(r = -42);
    TEST_EQUAL(r.abs(),                  IntRational{42});
    TEST_EQUAL(r.inverse(),              (IntRational{-1, 42}));
    TEST_EQUAL(r.sign(),                 -1);
    TEST_EQUAL(r.whole(),                -42);
    TEST_EQUAL(r.fraction(),             0);
    TEST_EQUAL(r.truncate(),             -42);
    TEST_EQUAL(r.signed_fraction(),      0);
    TEST_EQUAL(r.round_td(),             -42);
    TEST_EQUAL(r.round_tt(),             -42);
    TEST_EQUAL(r.round_tu(),             -42);
    TEST_EQUAL(r.to_floating<double>(),  -42);

    TRY((r = {-3, 2}));
    TEST_EQUAL(r.abs(),                  (IntRational{3, 2}));
    TEST_EQUAL(r.inverse(),              (IntRational{-2, 3}));
    TEST_EQUAL(r.sign(),                 -1);
    TEST_EQUAL(r.whole(),                -2);
    TEST_EQUAL(r.fraction(),             (IntRational{1, 2}));
    TEST_EQUAL(r.truncate(),             -1);
    TEST_EQUAL(r.signed_fraction(),      (IntRational{-1, 2}));
    TEST_EQUAL(r.round_td(),             -2);
    TEST_EQUAL(r.round_tt(),             -1);
    TEST_EQUAL(r.round_tu(),             -1);
    TEST_EQUAL(r.to_floating<double>(),  -1.5);

    TRY((r = {-3, 4}));
    TEST_EQUAL(r.abs(),                  (IntRational{3, 4}));
    TEST_EQUAL(r.inverse(),              (IntRational{-4, 3}));
    TEST_EQUAL(r.sign(),                 -1);
    TEST_EQUAL(r.whole(),                -1);
    TEST_EQUAL(r.fraction(),             (IntRational{1, 4}));
    TEST_EQUAL(r.truncate(),             0);
    TEST_EQUAL(r.signed_fraction(),      (IntRational{-3, 4}));
    TEST_EQUAL(r.round_td(),             -1);
    TEST_EQUAL(r.round_tt(),             -1);
    TEST_EQUAL(r.round_tu(),             -1);
    TEST_EQUAL(r.to_floating<double>(),  -0.75);

    TRY((r = {-9, 4}));
    TEST_EQUAL(r.abs(),                  (IntRational{9, 4}));
    TEST_EQUAL(r.inverse(),              (IntRational{-4, 9}));
    TEST_EQUAL(r.sign(),                 -1);
    TEST_EQUAL(r.whole(),                -3);
    TEST_EQUAL(r.fraction(),             (IntRational{3, 4}));
    TEST_EQUAL(r.truncate(),             -2);
    TEST_EQUAL(r.signed_fraction(),      (IntRational{-1, 4}));
    TEST_EQUAL(r.round_td(),             -2);
    TEST_EQUAL(r.round_tt(),             -2);
    TEST_EQUAL(r.round_tu(),             -2);
    TEST_EQUAL(r.to_floating<double>(),  -2.25);

}
