#include "rs-core/mp-integer.hpp"
#include "rs-core/unit-test.hpp"
#include <optional>

using namespace RS;

void test_rs_core_mp_integer_signed_conversion_parse_from_string() {

    std::optional<Integer> i;

    TRY(i = Integer::parse("0",                                            2));   TEST(i);  TEST_EQUAL(i.value().to_string(), "0");
    TRY(i = Integer::parse("101010",                                       2));   TEST(i);  TEST_EQUAL(i.value().to_string(), "42");
    TRY(i = Integer::parse("1011011111110111000001110000110100",           2));   TEST(i);  TEST_EQUAL(i.value().to_string(), "12345678900");
    TRY(i = Integer::parse("10'1010",                                      2));   TEST(i);  TEST_EQUAL(i.value().to_string(), "42");
    TRY(i = Integer::parse("10'1101'1111'1101'1100'0001'1100'0011'0100",   2));   TEST(i);  TEST_EQUAL(i.value().to_string(), "12345678900");
    TRY(i = Integer::parse("10_1010",                                      2));   TEST(i);  TEST_EQUAL(i.value().to_string(), "42");
    TRY(i = Integer::parse("10_1101_1111_1101_1100_0001_1100_0011_0100",   2));   TEST(i);  TEST_EQUAL(i.value().to_string(), "12345678900");
    TRY(i = Integer::parse("-0",                                           2));   TEST(i);  TEST_EQUAL(i.value().to_string(), "0");
    TRY(i = Integer::parse("+101010",                                      2));   TEST(i);  TEST_EQUAL(i.value().to_string(), "42");
    TRY(i = Integer::parse("-1011011111110111000001110000110100",          2));   TEST(i);  TEST_EQUAL(i.value().to_string(), "-12345678900");
    TRY(i = Integer::parse("-10'1010",                                     2));   TEST(i);  TEST_EQUAL(i.value().to_string(), "-42");
    TRY(i = Integer::parse("-10'1101'1111'1101'1100'0001'1100'0011'0100",  2));   TEST(i);  TEST_EQUAL(i.value().to_string(), "-12345678900");
    TRY(i = Integer::parse("-10_1010",                                     2));   TEST(i);  TEST_EQUAL(i.value().to_string(), "-42");
    TRY(i = Integer::parse("-10_1101_1111_1101_1100_0001_1100_0011_0100",  2));   TEST(i);  TEST_EQUAL(i.value().to_string(), "-12345678900");
    TRY(i = Integer::parse("0",                                            10));  TEST(i);  TEST_EQUAL(i.value().to_string(), "0");
    TRY(i = Integer::parse("42",                                           10));  TEST(i);  TEST_EQUAL(i.value().to_string(), "42");
    TRY(i = Integer::parse("123456789",                                    10));  TEST(i);  TEST_EQUAL(i.value().to_string(), "123456789");
    TRY(i = Integer::parse("123456789123456789",                           10));  TEST(i);  TEST_EQUAL(i.value().to_string(), "123456789123456789");
    TRY(i = Integer::parse("123456789123456789123456789",                  10));  TEST(i);  TEST_EQUAL(i.value().to_string(), "123456789123456789123456789");
    TRY(i = Integer::parse("123456789123456789123456789123456789",         10));  TEST(i);  TEST_EQUAL(i.value().to_string(), "123456789123456789123456789123456789");
    TRY(i = Integer::parse("123_456_789",                                  10));  TEST(i);  TEST_EQUAL(i.value().to_string(), "123456789");
    TRY(i = Integer::parse("123_456_789_123_456_789",                      10));  TEST(i);  TEST_EQUAL(i.value().to_string(), "123456789123456789");
    TRY(i = Integer::parse("123_456_789_123_456_789_123_456_789",          10));  TEST(i);  TEST_EQUAL(i.value().to_string(), "123456789123456789123456789");
    TRY(i = Integer::parse("123'456'789",                                  10));  TEST(i);  TEST_EQUAL(i.value().to_string(), "123456789");
    TRY(i = Integer::parse("123'456'789'123'456'789",                      10));  TEST(i);  TEST_EQUAL(i.value().to_string(), "123456789123456789");
    TRY(i = Integer::parse("123'456'789'123'456'789'123'456'789",          10));  TEST(i);  TEST_EQUAL(i.value().to_string(), "123456789123456789123456789");
    TRY(i = Integer::parse("-0",                                           10));  TEST(i);  TEST_EQUAL(i.value().to_string(), "0");
    TRY(i = Integer::parse("+123456789",                                   10));  TEST(i);  TEST_EQUAL(i.value().to_string(), "123456789");
    TRY(i = Integer::parse("-123456789123456789",                          10));  TEST(i);  TEST_EQUAL(i.value().to_string(), "-123456789123456789");
    TRY(i = Integer::parse("+123456789123456789123456789",                 10));  TEST(i);  TEST_EQUAL(i.value().to_string(), "123456789123456789123456789");
    TRY(i = Integer::parse("-123456789123456789123456789123456789",        10));  TEST(i);  TEST_EQUAL(i.value().to_string(), "-123456789123456789123456789123456789");
    TRY(i = Integer::parse("-123_456_789",                                 10));  TEST(i);  TEST_EQUAL(i.value().to_string(), "-123456789");
    TRY(i = Integer::parse("-123_456_789_123_456_789",                     10));  TEST(i);  TEST_EQUAL(i.value().to_string(), "-123456789123456789");
    TRY(i = Integer::parse("-123_456_789_123_456_789_123_456_789",         10));  TEST(i);  TEST_EQUAL(i.value().to_string(), "-123456789123456789123456789");
    TRY(i = Integer::parse("-123'456'789",                                 10));  TEST(i);  TEST_EQUAL(i.value().to_string(), "-123456789");
    TRY(i = Integer::parse("-123'456'789'123'456'789",                     10));  TEST(i);  TEST_EQUAL(i.value().to_string(), "-123456789123456789");
    TRY(i = Integer::parse("-123'456'789'123'456'789'123'456'789",         10));  TEST(i);  TEST_EQUAL(i.value().to_string(), "-123456789123456789123456789");
    TRY(i = Integer::parse("0",                                            16));  TEST(i);  TEST_EQUAL(i.value().to_string(), "0");
    TRY(i = Integer::parse("abcdef",                                       16));  TEST(i);  TEST_EQUAL(i.value().to_string(), "11259375");
    TRY(i = Integer::parse("abcdef123456789abcdef",                        16));  TEST(i);  TEST_EQUAL(i.value().to_string(), "12981175647918246886886895");
    TRY(i = Integer::parse("ab'cdef",                                      16));  TEST(i);  TEST_EQUAL(i.value().to_string(), "11259375");
    TRY(i = Integer::parse("a'bcde'f123'4567'89ab'cdef",                   16));  TEST(i);  TEST_EQUAL(i.value().to_string(), "12981175647918246886886895");
    TRY(i = Integer::parse("ab_cdef",                                      16));  TEST(i);  TEST_EQUAL(i.value().to_string(), "11259375");
    TRY(i = Integer::parse("a_bcde_f123_4567_89ab_cdef",                   16));  TEST(i);  TEST_EQUAL(i.value().to_string(), "12981175647918246886886895");
    TRY(i = Integer::parse("-0",                                           16));  TEST(i);  TEST_EQUAL(i.value().to_string(), "0");
    TRY(i = Integer::parse("+abcdef",                                      16));  TEST(i);  TEST_EQUAL(i.value().to_string(), "11259375");
    TRY(i = Integer::parse("-abcdef123456789abcdef",                       16));  TEST(i);  TEST_EQUAL(i.value().to_string(), "-12981175647918246886886895");
    TRY(i = Integer::parse("-ab'cdef",                                     16));  TEST(i);  TEST_EQUAL(i.value().to_string(), "-11259375");
    TRY(i = Integer::parse("-a'bcde'f123'4567'89ab'cdef",                  16));  TEST(i);  TEST_EQUAL(i.value().to_string(), "-12981175647918246886886895");
    TRY(i = Integer::parse("-ab_cdef",                                     16));  TEST(i);  TEST_EQUAL(i.value().to_string(), "-11259375");
    TRY(i = Integer::parse("-a_bcde_f123_4567_89ab_cdef",                  16));  TEST(i);  TEST_EQUAL(i.value().to_string(), "-12981175647918246886886895");
    TRY(i = Integer::parse("0",                                            0));   TEST(i);  TEST_EQUAL(i.value().to_string(), "0");
    TRY(i = Integer::parse("42",                                           0));   TEST(i);  TEST_EQUAL(i.value().to_string(), "42");
    TRY(i = Integer::parse("123456789",                                    0));   TEST(i);  TEST_EQUAL(i.value().to_string(), "123456789");
    TRY(i = Integer::parse("123456789123456789",                           0));   TEST(i);  TEST_EQUAL(i.value().to_string(), "123456789123456789");
    TRY(i = Integer::parse("123456789123456789123456789",                  0));   TEST(i);  TEST_EQUAL(i.value().to_string(), "123456789123456789123456789");
    TRY(i = Integer::parse("123456789123456789123456789123456789",         0));   TEST(i);  TEST_EQUAL(i.value().to_string(), "123456789123456789123456789123456789");
    TRY(i = Integer::parse("0b0",                                          0));   TEST(i);  TEST_EQUAL(i.value().to_string(), "0");
    TRY(i = Integer::parse("0b101010",                                     0));   TEST(i);  TEST_EQUAL(i.value().to_string(), "42");
    TRY(i = Integer::parse("0b1011011111110111000001110000110100",         0));   TEST(i);  TEST_EQUAL(i.value().to_string(), "12345678900");
    TRY(i = Integer::parse("0x0",                                          0));   TEST(i);  TEST_EQUAL(i.value().to_string(), "0");
    TRY(i = Integer::parse("0xabcdef",                                     0));   TEST(i);  TEST_EQUAL(i.value().to_string(), "11259375");
    TRY(i = Integer::parse("0xabcdef123456789abcdef",                      0));   TEST(i);  TEST_EQUAL(i.value().to_string(), "12981175647918246886886895");
    TRY(i = Integer::parse("-0",                                           0));   TEST(i);  TEST_EQUAL(i.value().to_string(), "0");
    TRY(i = Integer::parse("-42",                                          0));   TEST(i);  TEST_EQUAL(i.value().to_string(), "-42");
    TRY(i = Integer::parse("+123456789",                                   0));   TEST(i);  TEST_EQUAL(i.value().to_string(), "123456789");
    TRY(i = Integer::parse("-123456789123456789",                          0));   TEST(i);  TEST_EQUAL(i.value().to_string(), "-123456789123456789");
    TRY(i = Integer::parse("+123456789123456789123456789",                 0));   TEST(i);  TEST_EQUAL(i.value().to_string(), "123456789123456789123456789");
    TRY(i = Integer::parse("-123456789123456789123456789123456789",        0));   TEST(i);  TEST_EQUAL(i.value().to_string(), "-123456789123456789123456789123456789");
    TRY(i = Integer::parse("-0b0",                                         0));   TEST(i);  TEST_EQUAL(i.value().to_string(), "0");
    TRY(i = Integer::parse("+0b101010",                                    0));   TEST(i);  TEST_EQUAL(i.value().to_string(), "42");
    TRY(i = Integer::parse("-0b1011011111110111000001110000110100",        0));   TEST(i);  TEST_EQUAL(i.value().to_string(), "-12345678900");
    TRY(i = Integer::parse("-0x0",                                         0));   TEST(i);  TEST_EQUAL(i.value().to_string(), "0");
    TRY(i = Integer::parse("+0xabcdef",                                    0));   TEST(i);  TEST_EQUAL(i.value().to_string(), "11259375");
    TRY(i = Integer::parse("-0xabcdef123456789abcdef",                     0));   TEST(i);  TEST_EQUAL(i.value().to_string(), "-12981175647918246886886895");

    TRY(i = Integer::parse(""));           TEST(! i);
    TRY(i = Integer::parse("", 0));        TEST(! i);
    TRY(i = Integer::parse("abc"));        TEST(! i);
    TRY(i = Integer::parse("abc", 0));     TEST(! i);
    TRY(i = Integer::parse("123abc"));     TEST(! i);
    TRY(i = Integer::parse("123abc", 0));  TEST(! i);

}

void test_rs_core_mp_integer_signed_conversion_construction_from_string() {

    Integer i;

    TRY(i = Integer("0",                                      10));  TEST_EQUAL(i.to_string(), "0");
    TRY(i = Integer("42",                                     10));  TEST_EQUAL(i.to_string(), "42");
    TRY(i = Integer("123456789",                              10));  TEST_EQUAL(i.to_string(), "123456789");
    TRY(i = Integer("123456789123456789",                     10));  TEST_EQUAL(i.to_string(), "123456789123456789");
    TRY(i = Integer("123456789123456789123456789",            10));  TEST_EQUAL(i.to_string(), "123456789123456789123456789");
    TRY(i = Integer("123456789123456789123456789123456789",   10));  TEST_EQUAL(i.to_string(), "123456789123456789123456789123456789");
    TRY(i = Integer("0",                                      2));   TEST_EQUAL(i.to_string(), "0");
    TRY(i = Integer("101010",                                 2));   TEST_EQUAL(i.to_string(), "42");
    TRY(i = Integer("1011011111110111000001110000110100",     2));   TEST_EQUAL(i.to_string(), "12345678900");
    TRY(i = Integer("0",                                      16));  TEST_EQUAL(i.to_string(), "0");
    TRY(i = Integer("abcdef",                                 16));  TEST_EQUAL(i.to_string(), "11259375");
    TRY(i = Integer("abcdef123456789abcdef",                  16));  TEST_EQUAL(i.to_string(), "12981175647918246886886895");
    TRY(i = Integer("0",                                      0));   TEST_EQUAL(i.to_string(), "0");
    TRY(i = Integer("42",                                     0));   TEST_EQUAL(i.to_string(), "42");
    TRY(i = Integer("123456789",                              0));   TEST_EQUAL(i.to_string(), "123456789");
    TRY(i = Integer("123456789123456789",                     0));   TEST_EQUAL(i.to_string(), "123456789123456789");
    TRY(i = Integer("123456789123456789123456789",            0));   TEST_EQUAL(i.to_string(), "123456789123456789123456789");
    TRY(i = Integer("123456789123456789123456789123456789",   0));   TEST_EQUAL(i.to_string(), "123456789123456789123456789123456789");
    TRY(i = Integer("0b0",                                    0));   TEST_EQUAL(i.to_string(), "0");
    TRY(i = Integer("0b101010",                               0));   TEST_EQUAL(i.to_string(), "42");
    TRY(i = Integer("0b1011011111110111000001110000110100",   0));   TEST_EQUAL(i.to_string(), "12345678900");
    TRY(i = Integer("0x0",                                    0));   TEST_EQUAL(i.to_string(), "0");
    TRY(i = Integer("0xabcdef",                               0));   TEST_EQUAL(i.to_string(), "11259375");
    TRY(i = Integer("0xabcdef123456789abcdef",                0));   TEST_EQUAL(i.to_string(), "12981175647918246886886895");
    TRY(i = Integer("+0",                                     10));  TEST_EQUAL(i.to_string(), "0");
    TRY(i = Integer("+42",                                    10));  TEST_EQUAL(i.to_string(), "42");
    TRY(i = Integer("+0",                                     2));   TEST_EQUAL(i.to_string(), "0");
    TRY(i = Integer("+101010",                                2));   TEST_EQUAL(i.to_string(), "42");
    TRY(i = Integer("+0",                                     16));  TEST_EQUAL(i.to_string(), "0");
    TRY(i = Integer("+abcdef",                                16));  TEST_EQUAL(i.to_string(), "11259375");
    TRY(i = Integer("+0",                                     0));   TEST_EQUAL(i.to_string(), "0");
    TRY(i = Integer("+42",                                    0));   TEST_EQUAL(i.to_string(), "42");
    TRY(i = Integer("+0b0",                                   0));   TEST_EQUAL(i.to_string(), "0");
    TRY(i = Integer("+0b101010",                              0));   TEST_EQUAL(i.to_string(), "42");
    TRY(i = Integer("+0x0",                                   0));   TEST_EQUAL(i.to_string(), "0");
    TRY(i = Integer("+0xabcdef",                              0));   TEST_EQUAL(i.to_string(), "11259375");
    TRY(i = Integer("-0",                                     10));  TEST_EQUAL(i.to_string(), "0");
    TRY(i = Integer("-42",                                    10));  TEST_EQUAL(i.to_string(), "-42");
    TRY(i = Integer("-123456789",                             10));  TEST_EQUAL(i.to_string(), "-123456789");
    TRY(i = Integer("-123456789123456789",                    10));  TEST_EQUAL(i.to_string(), "-123456789123456789");
    TRY(i = Integer("-123456789123456789123456789",           10));  TEST_EQUAL(i.to_string(), "-123456789123456789123456789");
    TRY(i = Integer("-123456789123456789123456789123456789",  10));  TEST_EQUAL(i.to_string(), "-123456789123456789123456789123456789");
    TRY(i = Integer("-0",                                     2));   TEST_EQUAL(i.to_string(), "0");
    TRY(i = Integer("-101010",                                2));   TEST_EQUAL(i.to_string(), "-42");
    TRY(i = Integer("-1011011111110111000001110000110100",    2));   TEST_EQUAL(i.to_string(), "-12345678900");
    TRY(i = Integer("-0",                                     16));  TEST_EQUAL(i.to_string(), "0");
    TRY(i = Integer("-abcdef",                                16));  TEST_EQUAL(i.to_string(), "-11259375");
    TRY(i = Integer("-abcdef123456789abcdef",                 16));  TEST_EQUAL(i.to_string(), "-12981175647918246886886895");
    TRY(i = Integer("-0",                                     0));   TEST_EQUAL(i.to_string(), "0");
    TRY(i = Integer("-42",                                    0));   TEST_EQUAL(i.to_string(), "-42");
    TRY(i = Integer("-123456789",                             0));   TEST_EQUAL(i.to_string(), "-123456789");
    TRY(i = Integer("-123456789123456789",                    0));   TEST_EQUAL(i.to_string(), "-123456789123456789");
    TRY(i = Integer("-123456789123456789123456789",           0));   TEST_EQUAL(i.to_string(), "-123456789123456789123456789");
    TRY(i = Integer("-123456789123456789123456789123456789",  0));   TEST_EQUAL(i.to_string(), "-123456789123456789123456789123456789");
    TRY(i = Integer("-0b0",                                   0));   TEST_EQUAL(i.to_string(), "0");
    TRY(i = Integer("-0b101010",                              0));   TEST_EQUAL(i.to_string(), "-42");
    TRY(i = Integer("-0b1011011111110111000001110000110100",  0));   TEST_EQUAL(i.to_string(), "-12345678900");
    TRY(i = Integer("-0x0",                                   0));   TEST_EQUAL(i.to_string(), "0");
    TRY(i = Integer("-0xabcdef",                              0));   TEST_EQUAL(i.to_string(), "-11259375");
    TRY(i = Integer("-0xabcdef123456789abcdef",               0));   TEST_EQUAL(i.to_string(), "-12981175647918246886886895");

}
