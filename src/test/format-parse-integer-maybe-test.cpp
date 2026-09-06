#include "rs-core/format.hpp"
#include "rs-core/unit-test.hpp"
#include <cstdint>
#include <optional>

using namespace RS;

void test_rs_core_format_parse_integer_maybe() {

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
    TRY(i = parse_number_maybe<std::int16_t>("0", 0));                   TEST(i.has_value()); TEST_EQUAL(i.value(), 0);
    TRY(i = parse_number_maybe<std::int16_t>("42", 0));                  TEST(i.has_value()); TEST_EQUAL(i.value(), 42);
    TRY(i = parse_number_maybe<std::int16_t>("+42", 0));                 TEST(i.has_value()); TEST_EQUAL(i.value(), 42);
    TRY(i = parse_number_maybe<std::int16_t>("32767", 0));               TEST(i.has_value()); TEST_EQUAL(i.value(), 32767);
    TRY(i = parse_number_maybe<std::int16_t>("32768", 0));               TEST(! i.has_value());
    TRY(i = parse_number_maybe<std::int16_t>("99999", 0));               TEST(! i.has_value());
    TRY(i = parse_number_maybe<std::int16_t>("-42", 0));                 TEST(i.has_value()); TEST_EQUAL(i.value(), -42);
    TRY(i = parse_number_maybe<std::int16_t>("-32768", 0));              TEST(i.has_value()); TEST_EQUAL(i.value(), -32768);
    TRY(i = parse_number_maybe<std::int16_t>("-32769", 0));              TEST(! i.has_value());
    TRY(i = parse_number_maybe<std::int16_t>("-99999", 0));              TEST(! i.has_value());
    TRY(i = parse_number_maybe<std::int16_t>("", 0));                    TEST(! i.has_value());
    TRY(i = parse_number_maybe<std::int16_t>("42a", 0));                 TEST(! i.has_value());
    TRY(i = parse_number_maybe<std::int16_t>("hello", 0));               TEST(! i.has_value());
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
