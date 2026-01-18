#include "rs-core/mp-integer.hpp"
#include "rs-core/unit-test.hpp"
#include <string>

using namespace RS;

void test_rs_core_mp_integer_unsigned_arithmetic() {

    Natural x, y, z, q, r;
    std::string s;

    TRY(x = 0u);
    TEST_EQUAL(x.bits(), 0u);
    TRY(s = x.to_string());    TEST_EQUAL(s, "0");
    TRY(s = x.to_string(16));  TEST_EQUAL(s, "0");

    TRY(y = x + 15u);
    TEST_EQUAL(y.bits(), 4u);
    TRY(s = y.to_string());    TEST_EQUAL(s, "15");
    TRY(s = y.to_string(16));  TEST_EQUAL(s, "f");

    TRY(y = x - 15u);
    TEST_EQUAL(y.bits(), 0u);
    TRY(s = y.to_string());    TEST_EQUAL(s, "0");
    TRY(s = y.to_string(16));  TEST_EQUAL(s, "0");

    TRY(y = 15u - x);
    TEST_EQUAL(y.bits(), 4u);
    TRY(s = y.to_string());    TEST_EQUAL(s, "15");
    TRY(s = y.to_string(16));  TEST_EQUAL(s, "f");

    TRY(x = 0x1234'5678'9abc'def0ull);
    TRY(y = 0xffff'ffff'ffff'ffffull);
    TEST_EQUAL(x.bits(), 61u);
    TEST_EQUAL(y.bits(), 64u);
    TRY(s = x.to_string());  TEST_EQUAL(s, "1311768467463790320");
    TRY(s = y.to_string());  TEST_EQUAL(s, "18446744073709551615");

    TRY(z = x + 15u);
    TEST_EQUAL(z.bits(), 61u);
    TRY(s = z.to_string());    TEST_EQUAL(s, "1311768467463790335");
    TRY(s = z.to_string(16));  TEST_EQUAL(s, "123456789abcdeff");

    TRY(z = x + y);
    TEST_EQUAL(z.bits(), 65u);
    TRY(s = z.to_string());    TEST_EQUAL(s, "19758512541173341935");
    TRY(s = z.to_string(16));  TEST_EQUAL(s, "1123456789abcdeef");

    TRY(z = y - 15u);
    TEST_EQUAL(z.bits(), 64u);
    TRY(s = z.to_string());    TEST_EQUAL(s, "18446744073709551600");
    TRY(s = z.to_string(16));  TEST_EQUAL(s, "fffffffffffffff0");

    TRY(z = 15u - y);
    TEST_EQUAL(z.bits(), 0u);
    TRY(s = z.to_string());    TEST_EQUAL(s, "0");
    TRY(s = z.to_string(16));  TEST_EQUAL(s, "0");

    TRY(z = y - x);
    TEST_EQUAL(z.bits(), 64u);
    TRY(s = z.to_string());    TEST_EQUAL(s, "17134975606245761295");
    TRY(s = z.to_string(16));  TEST_EQUAL(s, "edcba9876543210f");

    TRY(z = x * y);
    TEST_EQUAL(z.bits(), 125u);
    TRY(s = z.to_string());    TEST_EQUAL(s, "24197857203266734862169780735577366800");
    TRY(s = z.to_string(16));  TEST_EQUAL(s, "123456789abcdeefedcba98765432110");

    TRY(x = Natural("123456789123456789123456789123456789123456789"));
    TRY(y = Natural("123456789123456789123456789123456789"));
    TRY(z = x - y);
    TEST_EQUAL(z, Natural("123456789000000000000000000000000000000000000"));
    TRY(y = Natural("123456789123456789123456789123456789000000000"));
    TRY(z = x - y);
    TEST_EQUAL(z, Natural("123456789"));
    TRY(x = Natural("123456789123456789123456789123456789123456789"));
    TRY(y = Natural("1357913579135791357913579"));
    TRY(z = x - y);
    TEST_EQUAL(z, Natural("123456789123456789122098875544320997765543210"));

    TRY(x = Natural("123456789123456789123456789123456789123456789"));
    TRY(y = Natural("123456789"));
    TRY(q = x / y);
    TRY(r = x % y);
    TEST_EQUAL(q, Natural("1000000001000000001000000001000000001"));
    TEST_EQUAL(r, Natural("0"));
    TRY(y = Natural("987654321"));
    TRY(q = x / y);
    TRY(r = x % y);
    TEST_EQUAL(q, Natural("124999998985937499000175780249997801"));
    TEST_EQUAL(r, Natural("725308668"));
    TRY(y = Natural("987654321987654321987654321987654321987654321"));
    TRY(q = x / y);
    TRY(r = x % y);
    TEST_EQUAL(q, Natural("0"));
    TEST_EQUAL(r, Natural("123456789123456789123456789123456789123456789"));
    TRY(y = {});

}

void test_rs_core_mp_integer_unsigned_bit_operations() {

    Natural x, y, z;
    std::string s;

    TEST_EQUAL(x.popcount(), 0u);

    TRY(x = 0x1234'5678'9abc'def0ull);
    TRY(y = 0xffff'ffff'ffff'ffffull);
    TEST_EQUAL(x.bits(), 61u);
    TEST_EQUAL(y.bits(), 64u);
    TEST_EQUAL(x.popcount(), 32u);
    TEST_EQUAL(y.popcount(), 64u);
    TRY(s = x.to_string());  TEST_EQUAL(s, "1311768467463790320");
    TRY(s = y.to_string());  TEST_EQUAL(s, "18446744073709551615");

    TRY(z = x & y);
    TEST_EQUAL(z.bits(), 61u);
    TRY(s = z.to_string());    TEST_EQUAL(s, "1311768467463790320");
    TRY(s = z.to_string(16));  TEST_EQUAL(s, "123456789abcdef0");

    TRY(z = x | y);
    TEST_EQUAL(z.bits(), 64u);
    TRY(s = z.to_string());    TEST_EQUAL(s, "18446744073709551615");
    TRY(s = z.to_string(16));  TEST_EQUAL(s, "ffffffffffffffff");

    TRY(z = x ^ y);
    TEST_EQUAL(z.bits(), 64u);
    TRY(s = z.to_string());    TEST_EQUAL(s, "17134975606245761295");
    TRY(s = z.to_string(16));  TEST_EQUAL(s, "edcba9876543210f");

    TRY(z = x >> 0);   TRY(s = z.to_string(16));  TEST_EQUAL(s, "123456789abcdef0");
    TRY(z = x >> 1);   TRY(s = z.to_string(16));  TEST_EQUAL(s, "91a2b3c4d5e6f78");
    TRY(z = x >> 2);   TRY(s = z.to_string(16));  TEST_EQUAL(s, "48d159e26af37bc");
    TRY(z = x >> 3);   TRY(s = z.to_string(16));  TEST_EQUAL(s, "2468acf13579bde");
    TRY(z = x >> 31);  TRY(s = z.to_string(16));  TEST_EQUAL(s, "2468acf1");
    TRY(z = x >> 32);  TRY(s = z.to_string(16));  TEST_EQUAL(s, "12345678");
    TRY(z = x >> 33);  TRY(s = z.to_string(16));  TEST_EQUAL(s, "91a2b3c");
    TRY(z = x >> 58);  TRY(s = z.to_string(16));  TEST_EQUAL(s, "4");
    TRY(z = x >> 59);  TRY(s = z.to_string(16));  TEST_EQUAL(s, "2");
    TRY(z = x >> 60);  TRY(s = z.to_string(16));  TEST_EQUAL(s, "1");
    TRY(z = x >> 61);  TRY(s = z.to_string(16));  TEST_EQUAL(s, "0");
    TRY(z = x >> 62);  TRY(s = z.to_string(16));  TEST_EQUAL(s, "0");
    TRY(z = x >> 63);  TRY(s = z.to_string(16));  TEST_EQUAL(s, "0");
    TRY(z = x >> 64);  TRY(s = z.to_string(16));  TEST_EQUAL(s, "0");
    TRY(z = x >> 65);  TRY(s = z.to_string(16));  TEST_EQUAL(s, "0");

    TRY(z = x << 0);   TRY(s = z.to_string(16));  TEST_EQUAL(s, "123456789abcdef0");
    TRY(z = x << 1);   TRY(s = z.to_string(16));  TEST_EQUAL(s, "2468acf13579bde0");
    TRY(z = x << 2);   TRY(s = z.to_string(16));  TEST_EQUAL(s, "48d159e26af37bc0");
    TRY(z = x << 3);   TRY(s = z.to_string(16));  TEST_EQUAL(s, "91a2b3c4d5e6f780");
    TRY(z = x << 4);   TRY(s = z.to_string(16));  TEST_EQUAL(s, "123456789abcdef00");
    TRY(z = x << 5);   TRY(s = z.to_string(16));  TEST_EQUAL(s, "2468acf13579bde00");
    TRY(z = x << 6);   TRY(s = z.to_string(16));  TEST_EQUAL(s, "48d159e26af37bc00");
    TRY(z = x << 7);   TRY(s = z.to_string(16));  TEST_EQUAL(s, "91a2b3c4d5e6f7800");
    TRY(z = x << 8);   TRY(s = z.to_string(16));  TEST_EQUAL(s, "123456789abcdef000");
    TRY(z = x << 9);   TRY(s = z.to_string(16));  TEST_EQUAL(s, "2468acf13579bde000");
    TRY(z = x << 10);  TRY(s = z.to_string(16));  TEST_EQUAL(s, "48d159e26af37bc000");
    TRY(z = x << 11);  TRY(s = z.to_string(16));  TEST_EQUAL(s, "91a2b3c4d5e6f78000");
    TRY(z = x << 12);  TRY(s = z.to_string(16));  TEST_EQUAL(s, "123456789abcdef0000");
    TRY(z = x << 13);  TRY(s = z.to_string(16));  TEST_EQUAL(s, "2468acf13579bde0000");
    TRY(z = x << 14);  TRY(s = z.to_string(16));  TEST_EQUAL(s, "48d159e26af37bc0000");
    TRY(z = x << 15);  TRY(s = z.to_string(16));  TEST_EQUAL(s, "91a2b3c4d5e6f780000");
    TRY(z = x << 16);  TRY(s = z.to_string(16));  TEST_EQUAL(s, "123456789abcdef00000");
    TRY(z = x << 17);  TRY(s = z.to_string(16));  TEST_EQUAL(s, "2468acf13579bde00000");
    TRY(z = x << 18);  TRY(s = z.to_string(16));  TEST_EQUAL(s, "48d159e26af37bc00000");
    TRY(z = x << 19);  TRY(s = z.to_string(16));  TEST_EQUAL(s, "91a2b3c4d5e6f7800000");
    TRY(z = x << 20);  TRY(s = z.to_string(16));  TEST_EQUAL(s, "123456789abcdef000000");

    TRY(x = {});
    TEST(! x.get_bit(0));
    TEST(! x.get_bit(100));

    TRY(x.set_bit(16));
    TEST_EQUAL(x, Natural("10000", 16));
    TEST(! x.get_bit(15));
    TEST(x.get_bit(16));
    TEST(! x.get_bit(17));

    TRY(x.set_bit(80));
    TEST_EQUAL(x, Natural("100000000000000010000", 16));
    TEST(! x.get_bit(79));
    TEST(x.get_bit(80));
    TEST(! x.get_bit(81));

    TRY(x.set_bit(80, false));
    TEST_EQUAL(x, Natural("10000", 16));
    TEST(! x.get_bit(80));

    TRY(x.flip_bit(80));
    TEST_EQUAL(x, Natural("100000000000000010000", 16));
    TEST(x.get_bit(80));

    TRY(x.flip_bit(80));
    TEST_EQUAL(x, Natural("10000", 16));
    TEST(! x.get_bit(80));

}
