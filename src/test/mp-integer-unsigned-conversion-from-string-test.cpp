#include "rs-core/mp-integer.hpp"
#include "rs-core/unit-test.hpp"
#include <optional>

using namespace RS;

void test_rs_core_mp_integer_unsigned_conversion_parse_from_string() {

    std::optional<Natural> n;

    TRY(n = Natural::parse("0",                                           2));   TEST(n);  TEST_EQUAL(n.value().to_string(), "0");
    TRY(n = Natural::parse("101010",                                      2));   TEST(n);  TEST_EQUAL(n.value().to_string(), "42");
    TRY(n = Natural::parse("1011011111110111000001110000110100",          2));   TEST(n);  TEST_EQUAL(n.value().to_string(), "12345678900");
    TRY(n = Natural::parse("10'1010",                                     2));   TEST(n);  TEST_EQUAL(n.value().to_string(), "42");
    TRY(n = Natural::parse("10'1101'1111'1101'1100'0001'1100'0011'0100",  2));   TEST(n);  TEST_EQUAL(n.value().to_string(), "12345678900");
    TRY(n = Natural::parse("10_1010",                                     2));   TEST(n);  TEST_EQUAL(n.value().to_string(), "42");
    TRY(n = Natural::parse("10_1101_1111_1101_1100_0001_1100_0011_0100",  2));   TEST(n);  TEST_EQUAL(n.value().to_string(), "12345678900");
    TRY(n = Natural::parse("0",                                           10));  TEST(n);  TEST_EQUAL(n.value().to_string(), "0");
    TRY(n = Natural::parse("42",                                          10));  TEST(n);  TEST_EQUAL(n.value().to_string(), "42");
    TRY(n = Natural::parse("123456789",                                   10));  TEST(n);  TEST_EQUAL(n.value().to_string(), "123456789");
    TRY(n = Natural::parse("123456789123456789",                          10));  TEST(n);  TEST_EQUAL(n.value().to_string(), "123456789123456789");
    TRY(n = Natural::parse("123456789123456789123456789",                 10));  TEST(n);  TEST_EQUAL(n.value().to_string(), "123456789123456789123456789");
    TRY(n = Natural::parse("123456789123456789123456789123456789",        10));  TEST(n);  TEST_EQUAL(n.value().to_string(), "123456789123456789123456789123456789");
    TRY(n = Natural::parse("123_456_789",                                 10));  TEST(n);  TEST_EQUAL(n.value().to_string(), "123456789");
    TRY(n = Natural::parse("123_456_789_123_456_789",                     10));  TEST(n);  TEST_EQUAL(n.value().to_string(), "123456789123456789");
    TRY(n = Natural::parse("123_456_789_123_456_789_123_456_789",         10));  TEST(n);  TEST_EQUAL(n.value().to_string(), "123456789123456789123456789");
    TRY(n = Natural::parse("123'456'789",                                 10));  TEST(n);  TEST_EQUAL(n.value().to_string(), "123456789");
    TRY(n = Natural::parse("123'456'789'123'456'789",                     10));  TEST(n);  TEST_EQUAL(n.value().to_string(), "123456789123456789");
    TRY(n = Natural::parse("123'456'789'123'456'789'123'456'789",         10));  TEST(n);  TEST_EQUAL(n.value().to_string(), "123456789123456789123456789");
    TRY(n = Natural::parse("0",                                           16));  TEST(n);  TEST_EQUAL(n.value().to_string(), "0");
    TRY(n = Natural::parse("abcdef",                                      16));  TEST(n);  TEST_EQUAL(n.value().to_string(), "11259375");
    TRY(n = Natural::parse("abcdef123456789abcdef",                       16));  TEST(n);  TEST_EQUAL(n.value().to_string(), "12981175647918246886886895");
    TRY(n = Natural::parse("ab'cdef",                                     16));  TEST(n);  TEST_EQUAL(n.value().to_string(), "11259375");
    TRY(n = Natural::parse("a'bcde'f123'4567'89ab'cdef",                  16));  TEST(n);  TEST_EQUAL(n.value().to_string(), "12981175647918246886886895");
    TRY(n = Natural::parse("ab_cdef",                                     16));  TEST(n);  TEST_EQUAL(n.value().to_string(), "11259375");
    TRY(n = Natural::parse("a_bcde_f123_4567_89ab_cdef",                  16));  TEST(n);  TEST_EQUAL(n.value().to_string(), "12981175647918246886886895");
    TRY(n = Natural::parse("0",                                           0));   TEST(n);  TEST_EQUAL(n.value().to_string(), "0");
    TRY(n = Natural::parse("42",                                          0));   TEST(n);  TEST_EQUAL(n.value().to_string(), "42");
    TRY(n = Natural::parse("123456789",                                   0));   TEST(n);  TEST_EQUAL(n.value().to_string(), "123456789");
    TRY(n = Natural::parse("123456789123456789",                          0));   TEST(n);  TEST_EQUAL(n.value().to_string(), "123456789123456789");
    TRY(n = Natural::parse("123456789123456789123456789",                 0));   TEST(n);  TEST_EQUAL(n.value().to_string(), "123456789123456789123456789");
    TRY(n = Natural::parse("123456789123456789123456789123456789",        0));   TEST(n);  TEST_EQUAL(n.value().to_string(), "123456789123456789123456789123456789");
    TRY(n = Natural::parse("0b0",                                         0));   TEST(n);  TEST_EQUAL(n.value().to_string(), "0");
    TRY(n = Natural::parse("0b101010",                                    0));   TEST(n);  TEST_EQUAL(n.value().to_string(), "42");
    TRY(n = Natural::parse("0b1011011111110111000001110000110100",        0));   TEST(n);  TEST_EQUAL(n.value().to_string(), "12345678900");
    TRY(n = Natural::parse("0x0",                                         0));   TEST(n);  TEST_EQUAL(n.value().to_string(), "0");
    TRY(n = Natural::parse("0xabcdef",                                    0));   TEST(n);  TEST_EQUAL(n.value().to_string(), "11259375");
    TRY(n = Natural::parse("0xabcdef123456789abcdef",                     0));   TEST(n);  TEST_EQUAL(n.value().to_string(), "12981175647918246886886895");

    TRY(n = Natural::parse(""));           TEST(! n);
    TRY(n = Natural::parse("", 0));        TEST(! n);
    TRY(n = Natural::parse("abc"));        TEST(! n);
    TRY(n = Natural::parse("abc", 0));     TEST(! n);
    TRY(n = Natural::parse("123abc"));     TEST(! n);
    TRY(n = Natural::parse("123abc", 0));  TEST(! n);

}

void test_rs_core_mp_integer_unsigned_conversion_construction_from_string() {

    Natural n;

    TRY(n = Natural("0"));                                        TEST_EQUAL(n.to_string(), "0");
    TRY(n = Natural("42"));                                       TEST_EQUAL(n.to_string(), "42");
    TRY(n = Natural("123456789"));                                TEST_EQUAL(n.to_string(), "123456789");
    TRY(n = Natural("123456789123456789"));                       TEST_EQUAL(n.to_string(), "123456789123456789");
    TRY(n = Natural("123456789123456789123456789"));              TEST_EQUAL(n.to_string(), "123456789123456789123456789");
    TRY(n = Natural("123456789123456789123456789123456789"));     TEST_EQUAL(n.to_string(), "123456789123456789123456789123456789");
    TRY(n = Natural("0", 2));                                     TEST_EQUAL(n.to_string(), "0");
    TRY(n = Natural("101010", 2));                                TEST_EQUAL(n.to_string(), "42");
    TRY(n = Natural("1011011111110111000001110000110100", 2));    TEST_EQUAL(n.to_string(), "12345678900");
    TRY(n = Natural("0", 16));                                    TEST_EQUAL(n.to_string(), "0");
    TRY(n = Natural("abcdef", 16));                               TEST_EQUAL(n.to_string(), "11259375");
    TRY(n = Natural("abcdef123456789abcdef", 16));                TEST_EQUAL(n.to_string(), "12981175647918246886886895");
    TRY(n = Natural("0", 0));                                     TEST_EQUAL(n.to_string(), "0");
    TRY(n = Natural("42", 0));                                    TEST_EQUAL(n.to_string(), "42");
    TRY(n = Natural("123456789", 0));                             TEST_EQUAL(n.to_string(), "123456789");
    TRY(n = Natural("123456789123456789", 0));                    TEST_EQUAL(n.to_string(), "123456789123456789");
    TRY(n = Natural("123456789123456789123456789", 0));           TEST_EQUAL(n.to_string(), "123456789123456789123456789");
    TRY(n = Natural("123456789123456789123456789123456789", 0));  TEST_EQUAL(n.to_string(), "123456789123456789123456789123456789");
    TRY(n = Natural("0b0", 0));                                   TEST_EQUAL(n.to_string(), "0");
    TRY(n = Natural("0b101010", 0));                              TEST_EQUAL(n.to_string(), "42");
    TRY(n = Natural("0b1011011111110111000001110000110100", 0));  TEST_EQUAL(n.to_string(), "12345678900");
    TRY(n = Natural("0x0", 0));                                   TEST_EQUAL(n.to_string(), "0");
    TRY(n = Natural("0xabcdef", 0));                              TEST_EQUAL(n.to_string(), "11259375");
    TRY(n = Natural("0xabcdef123456789abcdef", 0));               TEST_EQUAL(n.to_string(), "12981175647918246886886895");

}
