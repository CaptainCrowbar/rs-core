#include "rs-core/arithmetic.hpp"
#include "rs-core/unit-test.hpp"
#include <cmath>
#include <cstdint>
#include <optional>
#include <string>

using namespace RS;

namespace {

    enum class MyBitmask: int {
        none     = 0,
        alpha    = 1,
        bravo    = 2,
        charlie  = 4,
        all      = 7,
    };

}

void test_rs_core_arithmetic_bitmask_functions() {

    int n;

    n = 0;  TEST(! has_bit(n, 0));  TEST(! has_bits(n, 0));
    n = 0;  TEST(! has_bit(n, 1));  TEST(! has_bits(n, 1));
    n = 6;  TEST(! has_bit(n, 1));  TEST(! has_bits(n, 1));
    n = 6;  TEST(has_bit(n, 2));    TEST(has_bits(n, 2));
    n = 6;  TEST(has_bit(n, 4));    TEST(has_bits(n, 4));
    n = 6;  TEST(has_bit(n, 7));    TEST(! has_bits(n, 7));

    unsigned u;

    u = 0;  TEST(! has_bit(u, 0));  TEST(! has_bits(u, 0));
    u = 0;  TEST(! has_bit(u, 1));  TEST(! has_bits(u, 1));
    u = 6;  TEST(! has_bit(u, 1));  TEST(! has_bits(u, 1));
    u = 6;  TEST(has_bit(u, 2));    TEST(has_bits(u, 2));
    u = 6;  TEST(has_bit(u, 4));    TEST(has_bits(u, 4));
    u = 6;  TEST(has_bit(u, 7));    TEST(! has_bits(u, 7));

    MyBitmask b;

    b = MyBitmask::none;   TEST(! has_bit(b, 0));  TEST(! has_bits(b, 0));
    b = MyBitmask::none;   TEST(! has_bit(b, 1));  TEST(! has_bits(b, 1));
    b = MyBitmask::bravo;  TEST(! has_bit(b, 1));  TEST(! has_bits(b, 1));
    b = MyBitmask::bravo;  TEST(has_bit(b, 2));    TEST(has_bits(b, 2));
    b = MyBitmask::bravo;  TEST(! has_bit(b, 4));  TEST(! has_bits(b, 4));
    b = MyBitmask::bravo;  TEST(has_bit(b, 7));    TEST(! has_bits(b, 7));

    b = MyBitmask::none;   TEST(! has_bit(b, MyBitmask::none));     TEST(! has_bits(b, MyBitmask::none));
    b = MyBitmask::none;   TEST(! has_bit(b, MyBitmask::alpha));    TEST(! has_bits(b, MyBitmask::alpha));
    b = MyBitmask::bravo;  TEST(! has_bit(b, MyBitmask::alpha));    TEST(! has_bits(b, MyBitmask::alpha));
    b = MyBitmask::bravo;  TEST(has_bit(b, MyBitmask::bravo));      TEST(has_bits(b, MyBitmask::bravo));
    b = MyBitmask::bravo;  TEST(! has_bit(b, MyBitmask::charlie));  TEST(! has_bits(b, MyBitmask::charlie));
    b = MyBitmask::bravo;  TEST(has_bit(b, MyBitmask::all));        TEST(! has_bits(b, MyBitmask::all));

}

void test_rs_core_arithmetic_append_integers() {

    std::string s;

    s = "*";  TRY(append_number(s, 0));                      TEST_EQUAL(s, "*0");
    s = "*";  TRY(append_number(s, 42));                     TEST_EQUAL(s, "*42");
    s = "*";  TRY(append_number(s, -42));                    TEST_EQUAL(s, "*-42");
    s = "*";  TRY(append_number(s, 12345));                  TEST_EQUAL(s, "*12345");
    s = "*";  TRY(append_number(s, -12345));                 TEST_EQUAL(s, "*-12345");
    s = "*";  TRY(append_number(s, 0, 4));                   TEST_EQUAL(s, "*0000");
    s = "*";  TRY(append_number(s, 42, 4));                  TEST_EQUAL(s, "*0042");
    s = "*";  TRY(append_number(s, -42, 4));                 TEST_EQUAL(s, "*-0042");
    s = "*";  TRY(append_number(s, 12345, 4));               TEST_EQUAL(s, "*12345");
    s = "*";  TRY(append_number(s, -12345, 4));              TEST_EQUAL(s, "*-12345");
    s = "*";  TRY(append_number(s, 0, 6));                   TEST_EQUAL(s, "*000000");
    s = "*";  TRY(append_number(s, 42, 6));                  TEST_EQUAL(s, "*000042");
    s = "*";  TRY(append_number(s, -42, 6));                 TEST_EQUAL(s, "*-000042");
    s = "*";  TRY(append_number(s, 12345, 6));               TEST_EQUAL(s, "*012345");
    s = "*";  TRY(append_number(s, -12345, 6));              TEST_EQUAL(s, "*-012345");
    s = "*";  TRY(append_number(s, 0, 1, 16));               TEST_EQUAL(s, "*0");
    s = "*";  TRY(append_number(s, 42, 1, 16));              TEST_EQUAL(s, "*2a");
    s = "*";  TRY(append_number(s, -42, 1, 16));             TEST_EQUAL(s, "*-2a");
    s = "*";  TRY(append_number(s, 12345, 1, 16));           TEST_EQUAL(s, "*3039");
    s = "*";  TRY(append_number(s, -12345, 1, 16));          TEST_EQUAL(s, "*-3039");
    s = "*";  TRY(append_number(s, 0u));                     TEST_EQUAL(s, "*0");
    s = "*";  TRY(append_number(s, 42u));                    TEST_EQUAL(s, "*42");
    s = "*";  TRY(append_number(s, 12345u));                 TEST_EQUAL(s, "*12345");
    s = "*";  TRY(append_number(s, 0u, 4));                  TEST_EQUAL(s, "*0000");
    s = "*";  TRY(append_number(s, 42u, 4));                 TEST_EQUAL(s, "*0042");
    s = "*";  TRY(append_number(s, 12345u, 4));              TEST_EQUAL(s, "*12345");
    s = "*";  TRY(append_number(s, 0u, 1, 16));              TEST_EQUAL(s, "*0");
    s = "*";  TRY(append_number(s, 42u, 1, 16));             TEST_EQUAL(s, "*2a");
    s = "*";  TRY(append_number(s, 12345u, 1, 16));          TEST_EQUAL(s, "*3039");
    s = "*";  TRY(append_number(s, 32767_i16));              TEST_EQUAL(s, "*32767");
    s = "*";  TRY(append_number(s, -32767_i16));             TEST_EQUAL(s, "*-32767");
    s = "*";  TRY(append_number(s, -32767_i16 - 1));         TEST_EQUAL(s, "*-32768");
    s = "*";  TRY(append_number(s, 65535_u16));              TEST_EQUAL(s, "*65535");
    s = "*";  TRY(append_number(s, 32767_i16, 1, 16));       TEST_EQUAL(s, "*7fff");
    s = "*";  TRY(append_number(s, -32767_i16, 1, 16));      TEST_EQUAL(s, "*-7fff");
    s = "*";  TRY(append_number(s, -32767_i16 - 1, 1, 16));  TEST_EQUAL(s, "*-8000");
    s = "*";  TRY(append_number(s, 65535_u16, 1, 16));       TEST_EQUAL(s, "*ffff");

}

void test_rs_core_arithmetic_parse_integers() {

    ParseNumber rc {};
    std::int16_t i {};
    std::uint16_t u {};

    TRY(rc = parse_number("0", i));                      TEST_EQUAL(rc, ParseNumber::ok); TEST_EQUAL(i, 0);
    TRY(rc = parse_number("42", i));                     TEST_EQUAL(rc, ParseNumber::ok); TEST_EQUAL(i, 42);
    TRY(rc = parse_number("+42", i));                    TEST_EQUAL(rc, ParseNumber::ok); TEST_EQUAL(i, 42);
    TRY(rc = parse_number("32767", i));                  TEST_EQUAL(rc, ParseNumber::ok); TEST_EQUAL(i, 32767);
    TRY(rc = parse_number("32768", i));                  TEST_EQUAL(rc, ParseNumber::out_of_range);
    TRY(rc = parse_number("99999", i));                  TEST_EQUAL(rc, ParseNumber::out_of_range);
    TRY(rc = parse_number("-42", i));                    TEST_EQUAL(rc, ParseNumber::ok); TEST_EQUAL(i, -42);
    TRY(rc = parse_number("-32768", i));                 TEST_EQUAL(rc, ParseNumber::ok); TEST_EQUAL(i, -32768);
    TRY(rc = parse_number("-32769", i));                 TEST_EQUAL(rc, ParseNumber::out_of_range);
    TRY(rc = parse_number("-99999", i));                 TEST_EQUAL(rc, ParseNumber::out_of_range);
    TRY(rc = parse_number("", i));                       TEST_EQUAL(rc, ParseNumber::invalid_number);
    TRY(rc = parse_number("42a", i));                    TEST_EQUAL(rc, ParseNumber::invalid_number);
    TRY(rc = parse_number("hello", i));                  TEST_EQUAL(rc, ParseNumber::invalid_number);
    TRY(rc = parse_number("0", i, 16));                  TEST_EQUAL(rc, ParseNumber::ok); TEST_EQUAL(i, 0);
    TRY(rc = parse_number("2a", i, 16));                 TEST_EQUAL(rc, ParseNumber::ok); TEST_EQUAL(i, 42);
    TRY(rc = parse_number("+2a", i, 16));                TEST_EQUAL(rc, ParseNumber::ok); TEST_EQUAL(i, 42);
    TRY(rc = parse_number("7fff", i, 16));               TEST_EQUAL(rc, ParseNumber::ok); TEST_EQUAL(i, 32767);
    TRY(rc = parse_number("8000", i, 16));               TEST_EQUAL(rc, ParseNumber::out_of_range);
    TRY(rc = parse_number("10000", i, 16));              TEST_EQUAL(rc, ParseNumber::out_of_range);
    TRY(rc = parse_number("-2a", i, 16));                TEST_EQUAL(rc, ParseNumber::ok); TEST_EQUAL(i, -42);
    TRY(rc = parse_number("-8000", i, 16));              TEST_EQUAL(rc, ParseNumber::ok); TEST_EQUAL(i, -32768);
    TRY(rc = parse_number("-8001", i, 16));              TEST_EQUAL(rc, ParseNumber::out_of_range);
    TRY(rc = parse_number("-10000", i, 16));             TEST_EQUAL(rc, ParseNumber::out_of_range);
    TRY(rc = parse_number("", i, 16));                   TEST_EQUAL(rc, ParseNumber::invalid_number);
    TRY(rc = parse_number("2x", i, 16));                 TEST_EQUAL(rc, ParseNumber::invalid_number);
    TRY(rc = parse_number("hello", i, 16));              TEST_EQUAL(rc, ParseNumber::invalid_number);
    TRY(rc = parse_number("0x0", i, 0));                 TEST_EQUAL(rc, ParseNumber::ok); TEST_EQUAL(i, 0);
    TRY(rc = parse_number("0x2a", i, 0));                TEST_EQUAL(rc, ParseNumber::ok); TEST_EQUAL(i, 42);
    TRY(rc = parse_number("+0x2a", i, 0));               TEST_EQUAL(rc, ParseNumber::ok); TEST_EQUAL(i, 42);
    TRY(rc = parse_number("0x7fff", i, 0));              TEST_EQUAL(rc, ParseNumber::ok); TEST_EQUAL(i, 32767);
    TRY(rc = parse_number("0x8000", i, 0));              TEST_EQUAL(rc, ParseNumber::out_of_range);
    TRY(rc = parse_number("0x10000", i, 0));             TEST_EQUAL(rc, ParseNumber::out_of_range);
    TRY(rc = parse_number("-0x2a", i, 0));               TEST_EQUAL(rc, ParseNumber::ok); TEST_EQUAL(i, -42);
    TRY(rc = parse_number("-0x8000", i, 0));             TEST_EQUAL(rc, ParseNumber::ok); TEST_EQUAL(i, -32768);
    TRY(rc = parse_number("-0x8001", i, 0));             TEST_EQUAL(rc, ParseNumber::out_of_range);
    TRY(rc = parse_number("-0x10000", i, 0));            TEST_EQUAL(rc, ParseNumber::out_of_range);
    TRY(rc = parse_number("0x2x", i, 0));                TEST_EQUAL(rc, ParseNumber::invalid_number);
    TRY(rc = parse_number("0xhello", i, 0));             TEST_EQUAL(rc, ParseNumber::invalid_number);
    TRY(rc = parse_number("0", i, 2));                   TEST_EQUAL(rc, ParseNumber::ok); TEST_EQUAL(i, 0);
    TRY(rc = parse_number("101010", i, 2));              TEST_EQUAL(rc, ParseNumber::ok); TEST_EQUAL(i, 42);
    TRY(rc = parse_number("+101010", i, 2));             TEST_EQUAL(rc, ParseNumber::ok); TEST_EQUAL(i, 42);
    TRY(rc = parse_number("111111111111111", i, 2));     TEST_EQUAL(rc, ParseNumber::ok); TEST_EQUAL(i, 32767);
    TRY(rc = parse_number("1000000000000000", i, 2));    TEST_EQUAL(rc, ParseNumber::out_of_range);
    TRY(rc = parse_number("10000000000000000", i, 2));   TEST_EQUAL(rc, ParseNumber::out_of_range);
    TRY(rc = parse_number("-101010", i, 2));             TEST_EQUAL(rc, ParseNumber::ok); TEST_EQUAL(i, -42);
    TRY(rc = parse_number("-1000000000000000", i, 2));   TEST_EQUAL(rc, ParseNumber::ok); TEST_EQUAL(i, -32768);
    TRY(rc = parse_number("-1000000000000001", i, 2));   TEST_EQUAL(rc, ParseNumber::out_of_range);
    TRY(rc = parse_number("-10000000000000000", i, 2));  TEST_EQUAL(rc, ParseNumber::out_of_range);
    TRY(rc = parse_number("", i, 2));                    TEST_EQUAL(rc, ParseNumber::invalid_number);
    TRY(rc = parse_number("1x", i, 2));                  TEST_EQUAL(rc, ParseNumber::invalid_number);
    TRY(rc = parse_number("hello", i, 2));               TEST_EQUAL(rc, ParseNumber::invalid_number);
    TRY(rc = parse_number("0", u));                      TEST_EQUAL(rc, ParseNumber::ok); TEST_EQUAL(u, 0);
    TRY(rc = parse_number("42", u));                     TEST_EQUAL(rc, ParseNumber::ok); TEST_EQUAL(u, 42);
    TRY(rc = parse_number("65535", u));                  TEST_EQUAL(rc, ParseNumber::ok); TEST_EQUAL(u, 65535);
    TRY(rc = parse_number("65536", u));                  TEST_EQUAL(rc, ParseNumber::out_of_range);
    TRY(rc = parse_number("99999", u));                  TEST_EQUAL(rc, ParseNumber::out_of_range);
    TRY(rc = parse_number("", u));                       TEST_EQUAL(rc, ParseNumber::invalid_number);
    TRY(rc = parse_number("+42", u));                    TEST_EQUAL(rc, ParseNumber::invalid_number);
    TRY(rc = parse_number("-42", u));                    TEST_EQUAL(rc, ParseNumber::invalid_number);
    TRY(rc = parse_number("42a", u));                    TEST_EQUAL(rc, ParseNumber::invalid_number);
    TRY(rc = parse_number("hello", u));                  TEST_EQUAL(rc, ParseNumber::invalid_number);
    TRY(rc = parse_number("0", u, 16));                  TEST_EQUAL(rc, ParseNumber::ok); TEST_EQUAL(u, 0);
    TRY(rc = parse_number("2a", u, 16));                 TEST_EQUAL(rc, ParseNumber::ok); TEST_EQUAL(u, 42);
    TRY(rc = parse_number("ffff", u, 16));               TEST_EQUAL(rc, ParseNumber::ok); TEST_EQUAL(u, 65535);
    TRY(rc = parse_number("10000", u, 16));              TEST_EQUAL(rc, ParseNumber::out_of_range);
    TRY(rc = parse_number("", u, 16));                   TEST_EQUAL(rc, ParseNumber::invalid_number);
    TRY(rc = parse_number("+2a", u, 16));                TEST_EQUAL(rc, ParseNumber::invalid_number);
    TRY(rc = parse_number("-2a", u, 16));                TEST_EQUAL(rc, ParseNumber::invalid_number);
    TRY(rc = parse_number("2x", u, 16));                 TEST_EQUAL(rc, ParseNumber::invalid_number);
    TRY(rc = parse_number("hello", u, 16));              TEST_EQUAL(rc, ParseNumber::invalid_number);
    TRY(rc = parse_number("0x0", u, 0));                 TEST_EQUAL(rc, ParseNumber::ok); TEST_EQUAL(u, 0);
    TRY(rc = parse_number("0x2a", u, 0));                TEST_EQUAL(rc, ParseNumber::ok); TEST_EQUAL(u, 42);
    TRY(rc = parse_number("0xffff", u, 0));              TEST_EQUAL(rc, ParseNumber::ok); TEST_EQUAL(u, 65535);
    TRY(rc = parse_number("0x10000", u, 0));             TEST_EQUAL(rc, ParseNumber::out_of_range);
    TRY(rc = parse_number("+0x2a", u, 0));               TEST_EQUAL(rc, ParseNumber::invalid_number);
    TRY(rc = parse_number("-0x2a", u, 0));               TEST_EQUAL(rc, ParseNumber::invalid_number);
    TRY(rc = parse_number("0x2x", u, 0));                TEST_EQUAL(rc, ParseNumber::invalid_number);
    TRY(rc = parse_number("0xhello", u, 0));             TEST_EQUAL(rc, ParseNumber::invalid_number);
    TRY(rc = parse_number("0", u, 2));                   TEST_EQUAL(rc, ParseNumber::ok); TEST_EQUAL(u, 0);
    TRY(rc = parse_number("101010", u, 2));              TEST_EQUAL(rc, ParseNumber::ok); TEST_EQUAL(u, 42);
    TRY(rc = parse_number("1111111111111111", u, 2));    TEST_EQUAL(rc, ParseNumber::ok); TEST_EQUAL(u, 65535);
    TRY(rc = parse_number("10000000000000000", u, 2));   TEST_EQUAL(rc, ParseNumber::out_of_range);
    TRY(rc = parse_number("", u, 2));                    TEST_EQUAL(rc, ParseNumber::invalid_number);
    TRY(rc = parse_number("+101010", u, 2));             TEST_EQUAL(rc, ParseNumber::invalid_number);
    TRY(rc = parse_number("-101010", u, 2));             TEST_EQUAL(rc, ParseNumber::invalid_number);
    TRY(rc = parse_number("1x", u, 2));                  TEST_EQUAL(rc, ParseNumber::invalid_number);
    TRY(rc = parse_number("hello", u, 2));               TEST_EQUAL(rc, ParseNumber::invalid_number);

}

void test_rs_core_arithmetic_parse_integers_maybe() {

    std::optional<std::int16_t> i;
    std::optional<std::uint16_t> u;

    TRY(i = parse_number_maybe<std::int16_t>("0"));                      TEST(i.has_value()); TEST_EQUAL(i.value(), 0);
    TRY(i = parse_number_maybe<std::int16_t>("42"));                     TEST(i.has_value()); TEST_EQUAL(i.value(), 42);
    TRY(i = parse_number_maybe<std::int16_t>("+42"));                    TEST(i.has_value()); TEST_EQUAL(i.value(), 42);
    TRY(i = parse_number_maybe<std::int16_t>("32767"));                  TEST(i.has_value()); TEST_EQUAL(i.value(), 32767);
    TRY(i = parse_number_maybe<std::int16_t>("32768"));                  TEST(! i.has_value());
    TRY(i = parse_number_maybe<std::int16_t>("99999"));                  TEST(! i.has_value());
    TRY(i = parse_number_maybe<std::int16_t>("-42"));                    TEST(i.has_value()); TEST_EQUAL(i.value(), -42);
    TRY(i = parse_number_maybe<std::int16_t>("-32768"));                 TEST(i.has_value()); TEST_EQUAL(i.value(), -32768);
    TRY(i = parse_number_maybe<std::int16_t>("-32769"));                 TEST(! i.has_value());
    TRY(i = parse_number_maybe<std::int16_t>("-99999"));                 TEST(! i.has_value());
    TRY(i = parse_number_maybe<std::int16_t>(""));                       TEST(! i.has_value());
    TRY(i = parse_number_maybe<std::int16_t>("42a"));                    TEST(! i.has_value());
    TRY(i = parse_number_maybe<std::int16_t>("hello"));                  TEST(! i.has_value());
    TRY(i = parse_number_maybe<std::int16_t>("0", 16));                  TEST(i.has_value()); TEST_EQUAL(i.value(), 0);
    TRY(i = parse_number_maybe<std::int16_t>("2a", 16));                 TEST(i.has_value()); TEST_EQUAL(i.value(), 42);
    TRY(i = parse_number_maybe<std::int16_t>("+2a", 16));                TEST(i.has_value()); TEST_EQUAL(i.value(), 42);
    TRY(i = parse_number_maybe<std::int16_t>("7fff", 16));               TEST(i.has_value()); TEST_EQUAL(i.value(), 32767);
    TRY(i = parse_number_maybe<std::int16_t>("8000", 16));               TEST(! i.has_value());
    TRY(i = parse_number_maybe<std::int16_t>("10000", 16));              TEST(! i.has_value());
    TRY(i = parse_number_maybe<std::int16_t>("-2a", 16));                TEST(i.has_value()); TEST_EQUAL(i.value(), -42);
    TRY(i = parse_number_maybe<std::int16_t>("-8000", 16));              TEST(i.has_value()); TEST_EQUAL(i.value(), -32768);
    TRY(i = parse_number_maybe<std::int16_t>("-8001", 16));              TEST(! i.has_value());
    TRY(i = parse_number_maybe<std::int16_t>("-10000", 16));             TEST(! i.has_value());
    TRY(i = parse_number_maybe<std::int16_t>("", 16));                   TEST(! i.has_value());
    TRY(i = parse_number_maybe<std::int16_t>("2x", 16));                 TEST(! i.has_value());
    TRY(i = parse_number_maybe<std::int16_t>("hello", 16));              TEST(! i.has_value());
    TRY(i = parse_number_maybe<std::int16_t>("0x0", 0));                 TEST(i.has_value()); TEST_EQUAL(i.value(), 0);
    TRY(i = parse_number_maybe<std::int16_t>("0x2a", 0));                TEST(i.has_value()); TEST_EQUAL(i.value(), 42);
    TRY(i = parse_number_maybe<std::int16_t>("+0x2a", 0));               TEST(i.has_value()); TEST_EQUAL(i.value(), 42);
    TRY(i = parse_number_maybe<std::int16_t>("0x7fff", 0));              TEST(i.has_value()); TEST_EQUAL(i.value(), 32767);
    TRY(i = parse_number_maybe<std::int16_t>("0x8000", 0));              TEST(! i.has_value());
    TRY(i = parse_number_maybe<std::int16_t>("0x10000", 0));             TEST(! i.has_value());
    TRY(i = parse_number_maybe<std::int16_t>("-0x2a", 0));               TEST(i.has_value()); TEST_EQUAL(i.value(), -42);
    TRY(i = parse_number_maybe<std::int16_t>("-0x8000", 0));             TEST(i.has_value()); TEST_EQUAL(i.value(), -32768);
    TRY(i = parse_number_maybe<std::int16_t>("-0x8001", 0));             TEST(! i.has_value());
    TRY(i = parse_number_maybe<std::int16_t>("-0x10000", 0));            TEST(! i.has_value());
    TRY(i = parse_number_maybe<std::int16_t>("0x2x", 0));                TEST(! i.has_value());
    TRY(i = parse_number_maybe<std::int16_t>("0xhello", 0));             TEST(! i.has_value());
    TRY(i = parse_number_maybe<std::int16_t>("0", 2));                   TEST(i.has_value()); TEST_EQUAL(i.value(), 0);
    TRY(i = parse_number_maybe<std::int16_t>("101010", 2));              TEST(i.has_value()); TEST_EQUAL(i.value(), 42);
    TRY(i = parse_number_maybe<std::int16_t>("+101010", 2));             TEST(i.has_value()); TEST_EQUAL(i.value(), 42);
    TRY(i = parse_number_maybe<std::int16_t>("111111111111111", 2));     TEST(i.has_value()); TEST_EQUAL(i.value(), 32767);
    TRY(i = parse_number_maybe<std::int16_t>("1000000000000000", 2));    TEST(! i.has_value());
    TRY(i = parse_number_maybe<std::int16_t>("10000000000000000", 2));   TEST(! i.has_value());
    TRY(i = parse_number_maybe<std::int16_t>("-101010", 2));             TEST(i.has_value()); TEST_EQUAL(i.value(), -42);
    TRY(i = parse_number_maybe<std::int16_t>("-1000000000000000", 2));   TEST(i.has_value()); TEST_EQUAL(i.value(), -32768);
    TRY(i = parse_number_maybe<std::int16_t>("-1000000000000001", 2));   TEST(! i.has_value());
    TRY(i = parse_number_maybe<std::int16_t>("-10000000000000000", 2));  TEST(! i.has_value());
    TRY(i = parse_number_maybe<std::int16_t>("", 2));                    TEST(! i.has_value());
    TRY(i = parse_number_maybe<std::int16_t>("1x", 2));                  TEST(! i.has_value());
    TRY(i = parse_number_maybe<std::int16_t>("hello", 2));               TEST(! i.has_value());
    TRY(u = parse_number_maybe<std::uint16_t>("0"));                     TEST(u.has_value()); TEST_EQUAL(u.value(), 0);
    TRY(u = parse_number_maybe<std::uint16_t>("42"));                    TEST(u.has_value()); TEST_EQUAL(u.value(), 42);
    TRY(u = parse_number_maybe<std::uint16_t>("65535"));                 TEST(u.has_value()); TEST_EQUAL(u.value(), 65535);
    TRY(u = parse_number_maybe<std::uint16_t>("65536"));                 TEST(! u.has_value());
    TRY(u = parse_number_maybe<std::uint16_t>("99999"));                 TEST(! u.has_value());
    TRY(u = parse_number_maybe<std::uint16_t>(""));                      TEST(! u.has_value());
    TRY(u = parse_number_maybe<std::uint16_t>("+42"));                   TEST(! u.has_value());
    TRY(u = parse_number_maybe<std::uint16_t>("-42"));                   TEST(! u.has_value());
    TRY(u = parse_number_maybe<std::uint16_t>("42a"));                   TEST(! u.has_value());
    TRY(u = parse_number_maybe<std::uint16_t>("hello"));                 TEST(! u.has_value());
    TRY(u = parse_number_maybe<std::uint16_t>("0", 16));                 TEST(u.has_value()); TEST_EQUAL(u.value(), 0);
    TRY(u = parse_number_maybe<std::uint16_t>("2a", 16));                TEST(u.has_value()); TEST_EQUAL(u.value(), 42);
    TRY(u = parse_number_maybe<std::uint16_t>("ffff", 16));              TEST(u.has_value()); TEST_EQUAL(u.value(), 65535);
    TRY(u = parse_number_maybe<std::uint16_t>("10000", 16));             TEST(! u.has_value());
    TRY(u = parse_number_maybe<std::uint16_t>("", 16));                  TEST(! u.has_value());
    TRY(u = parse_number_maybe<std::uint16_t>("+2a", 16));               TEST(! u.has_value());
    TRY(u = parse_number_maybe<std::uint16_t>("-2a", 16));               TEST(! u.has_value());
    TRY(u = parse_number_maybe<std::uint16_t>("2x", 16));                TEST(! u.has_value());
    TRY(u = parse_number_maybe<std::uint16_t>("hello", 16));             TEST(! u.has_value());
    TRY(u = parse_number_maybe<std::uint16_t>("0x0", 0));                TEST(u.has_value()); TEST_EQUAL(u.value(), 0);
    TRY(u = parse_number_maybe<std::uint16_t>("0x2a", 0));               TEST(u.has_value()); TEST_EQUAL(u.value(), 42);
    TRY(u = parse_number_maybe<std::uint16_t>("0xffff", 0));             TEST(u.has_value()); TEST_EQUAL(u.value(), 65535);
    TRY(u = parse_number_maybe<std::uint16_t>("0x10000", 0));            TEST(! u.has_value());
    TRY(u = parse_number_maybe<std::uint16_t>("+0x2a", 0));              TEST(! u.has_value());
    TRY(u = parse_number_maybe<std::uint16_t>("-0x2a", 0));              TEST(! u.has_value());
    TRY(u = parse_number_maybe<std::uint16_t>("0x2x", 0));               TEST(! u.has_value());
    TRY(u = parse_number_maybe<std::uint16_t>("0xhello", 0));            TEST(! u.has_value());
    TRY(u = parse_number_maybe<std::uint16_t>("0", 2));                  TEST(u.has_value()); TEST_EQUAL(u.value(), 0);
    TRY(u = parse_number_maybe<std::uint16_t>("101010", 2));             TEST(u.has_value()); TEST_EQUAL(u.value(), 42);
    TRY(u = parse_number_maybe<std::uint16_t>("1111111111111111", 2));   TEST(u.has_value()); TEST_EQUAL(u.value(), 65535);
    TRY(u = parse_number_maybe<std::uint16_t>("10000000000000000", 2));  TEST(! u.has_value());
    TRY(u = parse_number_maybe<std::uint16_t>("", 2));                   TEST(! u.has_value());
    TRY(u = parse_number_maybe<std::uint16_t>("+101010", 2));            TEST(! u.has_value());
    TRY(u = parse_number_maybe<std::uint16_t>("-101010", 2));            TEST(! u.has_value());
    TRY(u = parse_number_maybe<std::uint16_t>("1x", 2));                 TEST(! u.has_value());
    TRY(u = parse_number_maybe<std::uint16_t>("hello", 2));              TEST(! u.has_value());

}

void test_rs_core_arithmetic_parse_floating_point() {

    ParseNumber rc {};
    double x {};

    TRY(rc = parse_number("0", x));         TEST_EQUAL(rc, ParseNumber::ok); TEST_EQUAL(x, 0);
    TRY(rc = parse_number("42", x));        TEST_EQUAL(rc, ParseNumber::ok); TEST_EQUAL(x, 42);
    TRY(rc = parse_number("+42", x));       TEST_EQUAL(rc, ParseNumber::ok); TEST_EQUAL(x, 42);
    TRY(rc = parse_number("-42", x));       TEST_EQUAL(rc, ParseNumber::ok); TEST_EQUAL(x, -42);
    TRY(rc = parse_number("1234.5", x));    TEST_EQUAL(rc, ParseNumber::ok); TEST_EQUAL(x, 1234.5);
    TRY(rc = parse_number("-1234.5", x));   TEST_EQUAL(rc, ParseNumber::ok); TEST_EQUAL(x, -1234.5);
    TRY(rc = parse_number("1e6", x));       TEST_EQUAL(rc, ParseNumber::ok); TEST_EQUAL(x, 1e6);
    TRY(rc = parse_number("-1e6", x));      TEST_EQUAL(rc, ParseNumber::ok); TEST_EQUAL(x, -1e6);
    TRY(rc = parse_number("5e-1", x));      TEST_EQUAL(rc, ParseNumber::ok); TEST_EQUAL(x, 0.5);
    TRY(rc = parse_number("-5e-1", x));     TEST_EQUAL(rc, ParseNumber::ok); TEST_EQUAL(x, -0.5);
    TRY(rc = parse_number("inf", x));       TEST_EQUAL(rc, ParseNumber::ok); TEST(std::isinf(x)); TEST(! std::signbit(x));
    TRY(rc = parse_number("+inf", x));      TEST_EQUAL(rc, ParseNumber::ok); TEST(std::isinf(x)); TEST(! std::signbit(x));
    TRY(rc = parse_number("-inf", x));      TEST_EQUAL(rc, ParseNumber::ok); TEST(std::isinf(x)); TEST(std::signbit(x));
    TRY(rc = parse_number("nan", x));       TEST_EQUAL(rc, ParseNumber::ok); TEST(std::isnan(x));
    TRY(rc = parse_number("", x));          TEST_EQUAL(rc, ParseNumber::invalid_number);
    TRY(rc = parse_number("42a", x));       TEST_EQUAL(rc, ParseNumber::invalid_number);
    TRY(rc = parse_number("hello", x));     TEST_EQUAL(rc, ParseNumber::invalid_number);
    TRY(rc = parse_number("1e9999", x));    TEST_EQUAL(rc, ParseNumber::out_of_range);
    TRY(rc = parse_number("-1e9999", x));   TEST_EQUAL(rc, ParseNumber::out_of_range);
    TRY(rc = parse_number("1e-9999", x));   TEST_EQUAL(rc, ParseNumber::out_of_range);
    TRY(rc = parse_number("-1e-9999", x));  TEST_EQUAL(rc, ParseNumber::out_of_range);

}

void test_rs_core_arithmetic_parse_floating_point_maybe() {

    std::optional<double> x {};

    TRY(x = parse_number_maybe<double>("0"));         TEST(x.has_value()); TEST_EQUAL(x.value(), 0);
    TRY(x = parse_number_maybe<double>("42"));        TEST(x.has_value()); TEST_EQUAL(x.value(), 42);
    TRY(x = parse_number_maybe<double>("+42"));       TEST(x.has_value()); TEST_EQUAL(x.value(), 42);
    TRY(x = parse_number_maybe<double>("-42"));       TEST(x.has_value()); TEST_EQUAL(x.value(), -42);
    TRY(x = parse_number_maybe<double>("1234.5"));    TEST(x.has_value()); TEST_EQUAL(x.value(), 1234.5);
    TRY(x = parse_number_maybe<double>("-1234.5"));   TEST(x.has_value()); TEST_EQUAL(x.value(), -1234.5);
    TRY(x = parse_number_maybe<double>("1e6"));       TEST(x.has_value()); TEST_EQUAL(x.value(), 1e6);
    TRY(x = parse_number_maybe<double>("-1e6"));      TEST(x.has_value()); TEST_EQUAL(x.value(), -1e6);
    TRY(x = parse_number_maybe<double>("5e-1"));      TEST(x.has_value()); TEST_EQUAL(x.value(), 0.5);
    TRY(x = parse_number_maybe<double>("-5e-1"));     TEST(x.has_value()); TEST_EQUAL(x.value(), -0.5);
    TRY(x = parse_number_maybe<double>("inf"));       TEST(x.has_value()); TEST(std::isinf(x.value())); TEST(! std::signbit(x.value()));
    TRY(x = parse_number_maybe<double>("+inf"));      TEST(x.has_value()); TEST(std::isinf(x.value())); TEST(! std::signbit(x.value()));
    TRY(x = parse_number_maybe<double>("-inf"));      TEST(x.has_value()); TEST(std::isinf(x.value())); TEST(std::signbit(x.value()));
    TRY(x = parse_number_maybe<double>("nan"));       TEST(x.has_value()); TEST(std::isnan(x.value()));
    TRY(x = parse_number_maybe<double>(""));          TEST(! x.has_value());
    TRY(x = parse_number_maybe<double>("42a"));       TEST(! x.has_value());
    TRY(x = parse_number_maybe<double>("hello"));     TEST(! x.has_value());
    TRY(x = parse_number_maybe<double>("1e9999"));    TEST(! x.has_value());
    TRY(x = parse_number_maybe<double>("-1e9999"));   TEST(! x.has_value());
    TRY(x = parse_number_maybe<double>("1e-9999"));   TEST(! x.has_value());
    TRY(x = parse_number_maybe<double>("-1e-9999"));  TEST(! x.has_value());

}
