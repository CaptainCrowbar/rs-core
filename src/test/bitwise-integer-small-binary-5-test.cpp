#include "rs-core/bitwise-integer.hpp"
#include "rs-core/unit-test.hpp"

using namespace RS;

void test_rs_core_bitwise_integer_small_uint_5() {

    using U = SmallUint<5>;

    static const U c{42};
    U x, y, z;

    TEST_EQUAL(static_cast<int>(U::max()), 31);

    TEST(c.fits_in<int>());  TEST_EQUAL(static_cast<int>(c), 10);  TEST(c);
    TEST(x.fits_in<int>());  TEST_EQUAL(static_cast<int>(x), 0);   TEST(! x);

    TRY(x = U{25});
    TRY(y = U{10});

    TEST_EQUAL(static_cast<int>(x), 25);
    TEST_EQUAL(static_cast<int>(y), 10);
    TEST_EQUAL(static_cast<int>(z), 0);

    TEST_EQUAL(x.bin(), "11001");
    TEST_EQUAL(y.bin(), "01010");
    TEST_EQUAL(z.bin(), "00000");
    TEST_EQUAL(x.dec(), "25");
    TEST_EQUAL(y.dec(), "10");
    TEST_EQUAL(z.dec(), "0");
    TEST_EQUAL(x.hex(), "19");
    TEST_EQUAL(y.hex(), "0a");
    TEST_EQUAL(z.hex(), "00");
    TEST_EQUAL(static_cast<double>(x), 25.0);
    TEST_EQUAL(static_cast<double>(y), 10.0);
    TEST_EQUAL(static_cast<double>(z), 0.0);
    TEST_EQUAL(x.significant_bits(), 5u);
    TEST_EQUAL(y.significant_bits(), 4u);
    TEST_EQUAL(z.significant_bits(), 0u);

    TRY(z = - z);  TEST_EQUAL(static_cast<int>(z), 0);
    TRY(z = - x);  TEST_EQUAL(static_cast<int>(z), 7);
    TRY(z = - y);  TEST_EQUAL(static_cast<int>(z), 22);

    TRY(z.clear());
    TEST(! z);
    TEST_EQUAL(z, U{0});

    TRY(z = ~ z);  TEST_EQUAL(static_cast<int>(z), 31);
    TRY(z = ~ x);  TEST_EQUAL(static_cast<int>(z), 6);
    TRY(z = ~ y);  TEST_EQUAL(static_cast<int>(z), 21);

    TRY(z = x + y);  TEST_EQUAL(static_cast<int>(z), 3);
    TRY(z = x - y);  TEST_EQUAL(static_cast<int>(z), 15);
    TRY(z = y - x);  TEST_EQUAL(static_cast<int>(z), 17);
    TRY(z = x * y);  TEST_EQUAL(static_cast<int>(z), 26);
    TRY(z = x / y);  TEST_EQUAL(static_cast<int>(z), 2);
    TRY(z = x % y);  TEST_EQUAL(static_cast<int>(z), 5);
    TRY(z = y / x);  TEST_EQUAL(static_cast<int>(z), 0);
    TRY(z = y % x);  TEST_EQUAL(static_cast<int>(z), 10);
    TRY(z = x & y);  TEST_EQUAL(static_cast<int>(z), 8);
    TRY(z = x | y);  TEST_EQUAL(static_cast<int>(z), 27);
    TRY(z = x ^ y);  TEST_EQUAL(static_cast<int>(z), 19);

    TRY(z = x << 0);   TEST_EQUAL(static_cast<int>(z), 25);  TRY(z = x >> 0);   TEST_EQUAL(static_cast<int>(z), 25);
    TRY(z = x << 1);   TEST_EQUAL(static_cast<int>(z), 18);  TRY(z = x >> 1);   TEST_EQUAL(static_cast<int>(z), 12);
    TRY(z = x << 2);   TEST_EQUAL(static_cast<int>(z), 4);   TRY(z = x >> 2);   TEST_EQUAL(static_cast<int>(z), 6);
    TRY(z = x << 3);   TEST_EQUAL(static_cast<int>(z), 8);   TRY(z = x >> 3);   TEST_EQUAL(static_cast<int>(z), 3);
    TRY(z = x << 4);   TEST_EQUAL(static_cast<int>(z), 16);  TRY(z = x >> 4);   TEST_EQUAL(static_cast<int>(z), 1);
    TRY(z = x << 5);   TEST_EQUAL(static_cast<int>(z), 0);   TRY(z = x >> 5);   TEST_EQUAL(static_cast<int>(z), 0);

    TEST(++x);    TEST_EQUAL(static_cast<int>(x), 26);
    TEST(--x);    TEST_EQUAL(static_cast<int>(x), 25);
    TEST(x--);    TEST_EQUAL(static_cast<int>(x), 24);
    TEST(x++);    TEST_EQUAL(static_cast<int>(x), 25);
    TEST(++y);    TEST_EQUAL(static_cast<int>(y), 11);
    TEST(--y);    TEST_EQUAL(static_cast<int>(y), 10);
    TEST(y--);    TEST_EQUAL(static_cast<int>(y), 9);
    TEST(y++);    TEST_EQUAL(static_cast<int>(y), 10);
    TEST(++z);    TEST_EQUAL(static_cast<int>(z), 1);
    TEST(! --z);  TEST_EQUAL(static_cast<int>(z), 0);
    TEST(! z--);  TEST_EQUAL(static_cast<int>(z), 31);
    TEST(z++);    TEST_EQUAL(static_cast<int>(z), 0);

    TEST(x != y);
    TEST(x > y);
    TEST(x >= y);
    TEST(y != x);
    TEST(y < x);
    TEST(y <= x);

    TRY(x = rotl(y, 0));   TEST_EQUAL(static_cast<int>(x), 10);
    TRY(x = rotl(y, 1));   TEST_EQUAL(static_cast<int>(x), 20);
    TRY(x = rotl(y, 2));   TEST_EQUAL(static_cast<int>(x), 9);
    TRY(x = rotl(y, 3));   TEST_EQUAL(static_cast<int>(x), 18);
    TRY(x = rotl(y, 4));   TEST_EQUAL(static_cast<int>(x), 5);
    TRY(x = rotl(y, 5));   TEST_EQUAL(static_cast<int>(x), 10);
    TRY(x = rotl(y, 6));   TEST_EQUAL(static_cast<int>(x), 20);
    TRY(x = rotl(y, 7));   TEST_EQUAL(static_cast<int>(x), 9);
    TRY(x = rotl(y, 8));   TEST_EQUAL(static_cast<int>(x), 18);
    TRY(x = rotl(y, 9));   TEST_EQUAL(static_cast<int>(x), 5);
    TRY(x = rotl(y, 10));  TEST_EQUAL(static_cast<int>(x), 10);

    TRY(x = rotr(y, 0));   TEST_EQUAL(static_cast<int>(x), 10);
    TRY(x = rotr(y, 1));   TEST_EQUAL(static_cast<int>(x), 5);
    TRY(x = rotr(y, 2));   TEST_EQUAL(static_cast<int>(x), 18);
    TRY(x = rotr(y, 3));   TEST_EQUAL(static_cast<int>(x), 9);
    TRY(x = rotr(y, 4));   TEST_EQUAL(static_cast<int>(x), 20);
    TRY(x = rotr(y, 5));   TEST_EQUAL(static_cast<int>(x), 10);
    TRY(x = rotr(y, 6));   TEST_EQUAL(static_cast<int>(x), 5);
    TRY(x = rotr(y, 7));   TEST_EQUAL(static_cast<int>(x), 18);
    TRY(x = rotr(y, 8));   TEST_EQUAL(static_cast<int>(x), 9);
    TRY(x = rotr(y, 9));   TEST_EQUAL(static_cast<int>(x), 20);
    TRY(x = rotr(y, 10));  TEST_EQUAL(static_cast<int>(x), 10);

    TRY(x = U::from_double(25.0));
    TEST_EQUAL(x.dec(), "25");
    TEST_EQUAL(static_cast<double>(x), 25.0);
    TEST_EQUAL(static_cast<int>(x), 25);

}
