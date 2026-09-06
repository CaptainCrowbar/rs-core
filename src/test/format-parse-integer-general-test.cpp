#include "rs-core/format.hpp"
#include "rs-core/unit-test.hpp"
#include <cstdint>

using namespace RS;

void test_rs_core_format_parse_integer_general() {

    ParseNumber rc {};
    std::int16_t i {};
    std::uint16_t u {};

    TRY(rc = parse_number("0", i));                        TEST(rc == ParseNumber::ok); TEST_EQUAL(i, 0);
    TRY(rc = parse_number("42", i));                       TEST(rc == ParseNumber::ok); TEST_EQUAL(i, 42);
    TRY(rc = parse_number("+42", i));                      TEST(rc == ParseNumber::ok); TEST_EQUAL(i, 42);
    TRY(rc = parse_number("32767", i));                    TEST(rc == ParseNumber::ok); TEST_EQUAL(i, 32767);
    TRY(rc = parse_number("32768", i));                    TEST(rc == ParseNumber::out_of_range);
    TRY(rc = parse_number("99999", i));                    TEST(rc == ParseNumber::out_of_range);
    TRY(rc = parse_number("-42", i));                      TEST(rc == ParseNumber::ok); TEST_EQUAL(i, -42);
    TRY(rc = parse_number("-32768", i));                   TEST(rc == ParseNumber::ok); TEST_EQUAL(i, -32768);
    TRY(rc = parse_number("-32769", i));                   TEST(rc == ParseNumber::out_of_range);
    TRY(rc = parse_number("-99999", i));                   TEST(rc == ParseNumber::out_of_range);
    TRY(rc = parse_number("", i));                         TEST(rc == ParseNumber::invalid_number);
    TRY(rc = parse_number("42a", i));                      TEST(rc == ParseNumber::invalid_number);
    TRY(rc = parse_number("hello", i));                    TEST(rc == ParseNumber::invalid_number);
    TRY(rc = parse_number("0", i, 0));                     TEST(rc == ParseNumber::ok); TEST_EQUAL(i, 0);
    TRY(rc = parse_number("42", i, 0));                    TEST(rc == ParseNumber::ok); TEST_EQUAL(i, 42);
    TRY(rc = parse_number("+42", i, 0));                   TEST(rc == ParseNumber::ok); TEST_EQUAL(i, 42);
    TRY(rc = parse_number("32767", i, 0));                 TEST(rc == ParseNumber::ok); TEST_EQUAL(i, 32767);
    TRY(rc = parse_number("32768", i, 0));                 TEST(rc == ParseNumber::out_of_range);
    TRY(rc = parse_number("99999", i, 0));                 TEST(rc == ParseNumber::out_of_range);
    TRY(rc = parse_number("-42", i, 0));                   TEST(rc == ParseNumber::ok); TEST_EQUAL(i, -42);
    TRY(rc = parse_number("-32768", i, 0));                TEST(rc == ParseNumber::ok); TEST_EQUAL(i, -32768);
    TRY(rc = parse_number("-32769", i, 0));                TEST(rc == ParseNumber::out_of_range);
    TRY(rc = parse_number("-99999", i, 0));                TEST(rc == ParseNumber::out_of_range);
    TRY(rc = parse_number("", i, 0));                      TEST(rc == ParseNumber::invalid_number);
    TRY(rc = parse_number("42a", i, 0));                   TEST(rc == ParseNumber::invalid_number);
    TRY(rc = parse_number("hello", i, 0));                 TEST(rc == ParseNumber::invalid_number);
    TRY(rc = parse_number("0", i, 16));                    TEST(rc == ParseNumber::ok); TEST_EQUAL(i, 0);
    TRY(rc = parse_number("2a", i, 16));                   TEST(rc == ParseNumber::ok); TEST_EQUAL(i, 42);
    TRY(rc = parse_number("+2a", i, 16));                  TEST(rc == ParseNumber::ok); TEST_EQUAL(i, 42);
    TRY(rc = parse_number("7fff", i, 16));                 TEST(rc == ParseNumber::ok); TEST_EQUAL(i, 32767);
    TRY(rc = parse_number("8000", i, 16));                 TEST(rc == ParseNumber::out_of_range);
    TRY(rc = parse_number("10000", i, 16));                TEST(rc == ParseNumber::out_of_range);
    TRY(rc = parse_number("-2a", i, 16));                  TEST(rc == ParseNumber::ok); TEST_EQUAL(i, -42);
    TRY(rc = parse_number("-8000", i, 16));                TEST(rc == ParseNumber::ok); TEST_EQUAL(i, -32768);
    TRY(rc = parse_number("-8001", i, 16));                TEST(rc == ParseNumber::out_of_range);
    TRY(rc = parse_number("-10000", i, 16));               TEST(rc == ParseNumber::out_of_range);
    TRY(rc = parse_number("", i, 16));                     TEST(rc == ParseNumber::invalid_number);
    TRY(rc = parse_number("2x", i, 16));                   TEST(rc == ParseNumber::invalid_number);
    TRY(rc = parse_number("hello", i, 16));                TEST(rc == ParseNumber::invalid_number);

    TRY(rc = parse_number("0b0", i, 0));                   TEST(rc == ParseNumber::ok); TEST_EQUAL(i, 0);
    TRY(rc = parse_number("0b101010", i, 0));              TEST(rc == ParseNumber::ok); TEST_EQUAL(i, 42);
    TRY(rc = parse_number("+0b101010", i, 0));             TEST(rc == ParseNumber::ok); TEST_EQUAL(i, 42);
    TRY(rc = parse_number("0b111111111111111", i, 0));     TEST(rc == ParseNumber::ok); TEST_EQUAL(i, 32767);
    TRY(rc = parse_number("0b1000000000000000", i, 0));    TEST(rc == ParseNumber::out_of_range);
    TRY(rc = parse_number("0b10000000000000000", i, 0));   TEST(rc == ParseNumber::out_of_range);
    TRY(rc = parse_number("-0b101010", i, 0));             TEST(rc == ParseNumber::ok); TEST_EQUAL(i, -42);
    TRY(rc = parse_number("-0b1000000000000000", i, 0));   TEST(rc == ParseNumber::ok); TEST_EQUAL(i, -32768);
    TRY(rc = parse_number("-0b1000000000000001", i, 0));   TEST(rc == ParseNumber::out_of_range);
    TRY(rc = parse_number("-0b10000000000000000", i, 0));  TEST(rc == ParseNumber::out_of_range);
    TRY(rc = parse_number("0b12", i, 0));                  TEST(rc == ParseNumber::invalid_number);
    TRY(rc = parse_number("0bhello", i, 0));               TEST(rc == ParseNumber::invalid_number);

    TRY(rc = parse_number("0o0", i, 0));                   TEST(rc == ParseNumber::ok); TEST_EQUAL(i, 0);
    TRY(rc = parse_number("0o52", i, 0));                  TEST(rc == ParseNumber::ok); TEST_EQUAL(i, 42);
    TRY(rc = parse_number("+0o52", i, 0));                 TEST(rc == ParseNumber::ok); TEST_EQUAL(i, 42);
    TRY(rc = parse_number("0o77777", i, 0));               TEST(rc == ParseNumber::ok); TEST_EQUAL(i, 32767);
    TRY(rc = parse_number("0o100000", i, 0));              TEST(rc == ParseNumber::out_of_range);
    TRY(rc = parse_number("0o1000000", i, 0));             TEST(rc == ParseNumber::out_of_range);
    TRY(rc = parse_number("-0o52", i, 0));                 TEST(rc == ParseNumber::ok); TEST_EQUAL(i, -42);
    TRY(rc = parse_number("-0o100000", i, 0));             TEST(rc == ParseNumber::ok); TEST_EQUAL(i, -32768);
    TRY(rc = parse_number("-0o100001", i, 0));             TEST(rc == ParseNumber::out_of_range);
    TRY(rc = parse_number("-0o1000000", i, 0));            TEST(rc == ParseNumber::out_of_range);
    TRY(rc = parse_number("0o78", i, 0));                  TEST(rc == ParseNumber::invalid_number);
    TRY(rc = parse_number("0ohello", i, 0));               TEST(rc == ParseNumber::invalid_number);

    TRY(rc = parse_number("0x0", i, 0));                   TEST(rc == ParseNumber::ok); TEST_EQUAL(i, 0);
    TRY(rc = parse_number("0x2a", i, 0));                  TEST(rc == ParseNumber::ok); TEST_EQUAL(i, 42);
    TRY(rc = parse_number("+0x2a", i, 0));                 TEST(rc == ParseNumber::ok); TEST_EQUAL(i, 42);
    TRY(rc = parse_number("0x7fff", i, 0));                TEST(rc == ParseNumber::ok); TEST_EQUAL(i, 32767);
    TRY(rc = parse_number("0x8000", i, 0));                TEST(rc == ParseNumber::out_of_range);
    TRY(rc = parse_number("0x10000", i, 0));               TEST(rc == ParseNumber::out_of_range);
    TRY(rc = parse_number("-0x2a", i, 0));                 TEST(rc == ParseNumber::ok); TEST_EQUAL(i, -42);
    TRY(rc = parse_number("-0x8000", i, 0));               TEST(rc == ParseNumber::ok); TEST_EQUAL(i, -32768);
    TRY(rc = parse_number("-0x8001", i, 0));               TEST(rc == ParseNumber::out_of_range);
    TRY(rc = parse_number("-0x10000", i, 0));              TEST(rc == ParseNumber::out_of_range);
    TRY(rc = parse_number("0x2x", i, 0));                  TEST(rc == ParseNumber::invalid_number);
    TRY(rc = parse_number("0xhello", i, 0));               TEST(rc == ParseNumber::invalid_number);

    TRY(rc = parse_number("0", i, 2));                     TEST(rc == ParseNumber::ok); TEST_EQUAL(i, 0);
    TRY(rc = parse_number("101010", i, 2));                TEST(rc == ParseNumber::ok); TEST_EQUAL(i, 42);
    TRY(rc = parse_number("+101010", i, 2));               TEST(rc == ParseNumber::ok); TEST_EQUAL(i, 42);
    TRY(rc = parse_number("111111111111111", i, 2));       TEST(rc == ParseNumber::ok); TEST_EQUAL(i, 32767);
    TRY(rc = parse_number("1000000000000000", i, 2));      TEST(rc == ParseNumber::out_of_range);
    TRY(rc = parse_number("10000000000000000", i, 2));     TEST(rc == ParseNumber::out_of_range);
    TRY(rc = parse_number("-101010", i, 2));               TEST(rc == ParseNumber::ok); TEST_EQUAL(i, -42);
    TRY(rc = parse_number("-1000000000000000", i, 2));     TEST(rc == ParseNumber::ok); TEST_EQUAL(i, -32768);
    TRY(rc = parse_number("-1000000000000001", i, 2));     TEST(rc == ParseNumber::out_of_range);
    TRY(rc = parse_number("-10000000000000000", i, 2));    TEST(rc == ParseNumber::out_of_range);
    TRY(rc = parse_number("", i, 2));                      TEST(rc == ParseNumber::invalid_number);
    TRY(rc = parse_number("1x", i, 2));                    TEST(rc == ParseNumber::invalid_number);
    TRY(rc = parse_number("hello", i, 2));                 TEST(rc == ParseNumber::invalid_number);
    TRY(rc = parse_number("0", u));                        TEST(rc == ParseNumber::ok); TEST_EQUAL(u, 0);
    TRY(rc = parse_number("42", u));                       TEST(rc == ParseNumber::ok); TEST_EQUAL(u, 42);
    TRY(rc = parse_number("65535", u));                    TEST(rc == ParseNumber::ok); TEST_EQUAL(u, 65535);
    TRY(rc = parse_number("65536", u));                    TEST(rc == ParseNumber::out_of_range);
    TRY(rc = parse_number("99999", u));                    TEST(rc == ParseNumber::out_of_range);
    TRY(rc = parse_number("", u));                         TEST(rc == ParseNumber::invalid_number);
    TRY(rc = parse_number("+42", u));                      TEST(rc == ParseNumber::invalid_number);
    TRY(rc = parse_number("-42", u));                      TEST(rc == ParseNumber::invalid_number);
    TRY(rc = parse_number("42a", u));                      TEST(rc == ParseNumber::invalid_number);
    TRY(rc = parse_number("hello", u));                    TEST(rc == ParseNumber::invalid_number);
    TRY(rc = parse_number("0", u, 16));                    TEST(rc == ParseNumber::ok); TEST_EQUAL(u, 0);
    TRY(rc = parse_number("2a", u, 16));                   TEST(rc == ParseNumber::ok); TEST_EQUAL(u, 42);
    TRY(rc = parse_number("ffff", u, 16));                 TEST(rc == ParseNumber::ok); TEST_EQUAL(u, 65535);
    TRY(rc = parse_number("10000", u, 16));                TEST(rc == ParseNumber::out_of_range);
    TRY(rc = parse_number("", u, 16));                     TEST(rc == ParseNumber::invalid_number);
    TRY(rc = parse_number("+2a", u, 16));                  TEST(rc == ParseNumber::invalid_number);
    TRY(rc = parse_number("-2a", u, 16));                  TEST(rc == ParseNumber::invalid_number);
    TRY(rc = parse_number("2x", u, 16));                   TEST(rc == ParseNumber::invalid_number);
    TRY(rc = parse_number("hello", u, 16));                TEST(rc == ParseNumber::invalid_number);

    TRY(rc = parse_number("0b0", u, 0));                   TEST(rc == ParseNumber::ok); TEST_EQUAL(u, 0);
    TRY(rc = parse_number("0b101010", u, 0));              TEST(rc == ParseNumber::ok); TEST_EQUAL(u, 42);
    TRY(rc = parse_number("0b1111111111111111", u, 0));    TEST(rc == ParseNumber::ok); TEST_EQUAL(u, 65535);
    TRY(rc = parse_number("0b10000000000000000", u, 0));   TEST(rc == ParseNumber::out_of_range);
    TRY(rc = parse_number("+0b101010", u, 0));             TEST(rc == ParseNumber::invalid_number);
    TRY(rc = parse_number("-0b101010", u, 0));             TEST(rc == ParseNumber::invalid_number);
    TRY(rc = parse_number("0b12", u, 0));                  TEST(rc == ParseNumber::invalid_number);
    TRY(rc = parse_number("0bhello", u, 0));               TEST(rc == ParseNumber::invalid_number);

    TRY(rc = parse_number("0o0", u, 0));                   TEST(rc == ParseNumber::ok); TEST_EQUAL(u, 0);
    TRY(rc = parse_number("0o52", u, 0));                  TEST(rc == ParseNumber::ok); TEST_EQUAL(u, 42);
    TRY(rc = parse_number("0o177777", u, 0));              TEST(rc == ParseNumber::ok); TEST_EQUAL(u, 65535);
    TRY(rc = parse_number("0o200000", u, 0));              TEST(rc == ParseNumber::out_of_range);
    TRY(rc = parse_number("+0o52", u, 0));                 TEST(rc == ParseNumber::invalid_number);
    TRY(rc = parse_number("-0o52", u, 0));                 TEST(rc == ParseNumber::invalid_number);
    TRY(rc = parse_number("0o78", u, 0));                  TEST(rc == ParseNumber::invalid_number);
    TRY(rc = parse_number("0ohello", u, 0));               TEST(rc == ParseNumber::invalid_number);

    TRY(rc = parse_number("0x0", u, 0));                   TEST(rc == ParseNumber::ok); TEST_EQUAL(u, 0);
    TRY(rc = parse_number("0x2a", u, 0));                  TEST(rc == ParseNumber::ok); TEST_EQUAL(u, 42);
    TRY(rc = parse_number("0xffff", u, 0));                TEST(rc == ParseNumber::ok); TEST_EQUAL(u, 65535);
    TRY(rc = parse_number("0x10000", u, 0));               TEST(rc == ParseNumber::out_of_range);
    TRY(rc = parse_number("+0x2a", u, 0));                 TEST(rc == ParseNumber::invalid_number);
    TRY(rc = parse_number("-0x2a", u, 0));                 TEST(rc == ParseNumber::invalid_number);
    TRY(rc = parse_number("0x2x", u, 0));                  TEST(rc == ParseNumber::invalid_number);
    TRY(rc = parse_number("0xhello", u, 0));               TEST(rc == ParseNumber::invalid_number);

    TRY(rc = parse_number("0", u, 2));                     TEST(rc == ParseNumber::ok); TEST_EQUAL(u, 0);
    TRY(rc = parse_number("101010", u, 2));                TEST(rc == ParseNumber::ok); TEST_EQUAL(u, 42);
    TRY(rc = parse_number("1111111111111111", u, 2));      TEST(rc == ParseNumber::ok); TEST_EQUAL(u, 65535);
    TRY(rc = parse_number("10000000000000000", u, 2));     TEST(rc == ParseNumber::out_of_range);
    TRY(rc = parse_number("", u, 2));                      TEST(rc == ParseNumber::invalid_number);
    TRY(rc = parse_number("+101010", u, 2));               TEST(rc == ParseNumber::invalid_number);
    TRY(rc = parse_number("-101010", u, 2));               TEST(rc == ParseNumber::invalid_number);
    TRY(rc = parse_number("1x", u, 2));                    TEST(rc == ParseNumber::invalid_number);
    TRY(rc = parse_number("hello", u, 2));                 TEST(rc == ParseNumber::invalid_number);

}
