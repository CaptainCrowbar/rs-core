#include "rs-core/format.hpp"
#include "rs-core/unit-test.hpp"
#include <cstdint>
#include <stdexcept>

using namespace RS;

void test_rs_core_format_parse_integer_try() {

    std::int16_t i {};
    std::uint16_t u {};

    TRY(i = try_parse_number<std::int16_t>("0"));                            TEST_EQUAL(i, 0);
    TRY(i = try_parse_number<std::int16_t>("42"));                           TEST_EQUAL(i, 42);
    TRY(i = try_parse_number<std::int16_t>("+42"));                          TEST_EQUAL(i, 42);
    TRY(i = try_parse_number<std::int16_t>("32767"));                        TEST_EQUAL(i, 32767);
    TEST_THROW(i = try_parse_number<std::int16_t>("32768"),                  std::out_of_range, "Number is out of range:");
    TEST_THROW(i = try_parse_number<std::int16_t>("99999"),                  std::out_of_range, "Number is out of range:");
    TRY(i = try_parse_number<std::int16_t>("-42"));                          TEST_EQUAL(i, -42);
    TRY(i = try_parse_number<std::int16_t>("-32768"));                       TEST_EQUAL(i, -32768);
    TEST_THROW(i = try_parse_number<std::int16_t>("-32769"),                 std::out_of_range, "Number is out of range:");
    TEST_THROW(i = try_parse_number<std::int16_t>("-99999"),                 std::out_of_range, "Number is out of range:");
    TEST_THROW(i = try_parse_number<std::int16_t>(""),                       std::invalid_argument, "Invalid number:");
    TEST_THROW(i = try_parse_number<std::int16_t>("42a"),                    std::invalid_argument, "Invalid number:");
    TEST_THROW(i = try_parse_number<std::int16_t>("hello"),                  std::invalid_argument, "Invalid number:");
    TRY(i = try_parse_number<std::int16_t>("0", 0));                         TEST_EQUAL(i, 0);
    TRY(i = try_parse_number<std::int16_t>("42", 0));                        TEST_EQUAL(i, 42);
    TRY(i = try_parse_number<std::int16_t>("+42", 0));                       TEST_EQUAL(i, 42);
    TRY(i = try_parse_number<std::int16_t>("32767", 0));                     TEST_EQUAL(i, 32767);
    TEST_THROW(i = try_parse_number<std::int16_t>("32768", 0),               std::out_of_range, "Number is out of range:");
    TEST_THROW(i = try_parse_number<std::int16_t>("99999", 0),               std::out_of_range, "Number is out of range:");
    TRY(i = try_parse_number<std::int16_t>("-42", 0));                       TEST_EQUAL(i, -42);
    TRY(i = try_parse_number<std::int16_t>("-32768", 0));                    TEST_EQUAL(i, -32768);
    TEST_THROW(i = try_parse_number<std::int16_t>("-32769", 0),              std::out_of_range, "Number is out of range:");
    TEST_THROW(i = try_parse_number<std::int16_t>("-99999", 0),              std::out_of_range, "Number is out of range:");
    TEST_THROW(i = try_parse_number<std::int16_t>("", 0),                    std::invalid_argument, "Invalid number:");
    TEST_THROW(i = try_parse_number<std::int16_t>("42a", 0),                 std::invalid_argument, "Invalid number:");
    TEST_THROW(i = try_parse_number<std::int16_t>("hello", 0),               std::invalid_argument, "Invalid number:");
    TRY(i = try_parse_number<std::int16_t>("0", 16));                        TEST_EQUAL(i, 0);
    TRY(i = try_parse_number<std::int16_t>("2a", 16));                       TEST_EQUAL(i, 42);
    TRY(i = try_parse_number<std::int16_t>("+2a", 16));                      TEST_EQUAL(i, 42);
    TRY(i = try_parse_number<std::int16_t>("7fff", 16));                     TEST_EQUAL(i, 32767);
    TEST_THROW(i = try_parse_number<std::int16_t>("8000", 16),               std::out_of_range, "Number is out of range:");
    TEST_THROW(i = try_parse_number<std::int16_t>("10000", 16),              std::out_of_range, "Number is out of range:");
    TRY(i = try_parse_number<std::int16_t>("-2a", 16));                      TEST_EQUAL(i, -42);
    TRY(i = try_parse_number<std::int16_t>("-8000", 16));                    TEST_EQUAL(i, -32768);
    TEST_THROW(i = try_parse_number<std::int16_t>("-8001", 16),              std::out_of_range, "Number is out of range:");
    TEST_THROW(i = try_parse_number<std::int16_t>("-10000", 16),             std::out_of_range, "Number is out of range:");
    TEST_THROW(i = try_parse_number<std::int16_t>("", 16),                   std::invalid_argument, "Invalid number:");
    TEST_THROW(i = try_parse_number<std::int16_t>("2x", 16),                 std::invalid_argument, "Invalid number:");
    TEST_THROW(i = try_parse_number<std::int16_t>("hello", 16),              std::invalid_argument, "Invalid number:");
    TRY(i = try_parse_number<std::int16_t>("0x0", 0));                       TEST_EQUAL(i, 0);
    TRY(i = try_parse_number<std::int16_t>("0x2a", 0));                      TEST_EQUAL(i, 42);
    TRY(i = try_parse_number<std::int16_t>("+0x2a", 0));                     TEST_EQUAL(i, 42);
    TRY(i = try_parse_number<std::int16_t>("0x7fff", 0));                    TEST_EQUAL(i, 32767);
    TEST_THROW(i = try_parse_number<std::int16_t>("0x8000", 0),              std::out_of_range, "Number is out of range:");
    TEST_THROW(i = try_parse_number<std::int16_t>("0x10000", 0),             std::out_of_range, "Number is out of range:");
    TRY(i = try_parse_number<std::int16_t>("-0x2a", 0));                     TEST_EQUAL(i, -42);
    TRY(i = try_parse_number<std::int16_t>("-0x8000", 0));                   TEST_EQUAL(i, -32768);
    TEST_THROW(i = try_parse_number<std::int16_t>("-0x8001", 0),             std::out_of_range, "Number is out of range:");
    TEST_THROW(i = try_parse_number<std::int16_t>("-0x10000", 0),            std::out_of_range, "Number is out of range:");
    TEST_THROW(i = try_parse_number<std::int16_t>("0x2x", 0),                std::invalid_argument, "Invalid number:");
    TEST_THROW(i = try_parse_number<std::int16_t>("0xhello", 0),             std::invalid_argument, "Invalid number:");
    TRY(i = try_parse_number<std::int16_t>("0", 2));                         TEST_EQUAL(i, 0);
    TRY(i = try_parse_number<std::int16_t>("101010", 2));                    TEST_EQUAL(i, 42);
    TRY(i = try_parse_number<std::int16_t>("+101010", 2));                   TEST_EQUAL(i, 42);
    TRY(i = try_parse_number<std::int16_t>("111111111111111", 2));           TEST_EQUAL(i, 32767);
    TEST_THROW(i = try_parse_number<std::int16_t>("1000000000000000", 2),    std::out_of_range, "Number is out of range:");
    TEST_THROW(i = try_parse_number<std::int16_t>("10000000000000000", 2),   std::out_of_range, "Number is out of range:");
    TRY(i = try_parse_number<std::int16_t>("-101010", 2));                   TEST_EQUAL(i, -42);
    TRY(i = try_parse_number<std::int16_t>("-1000000000000000", 2));         TEST_EQUAL(i, -32768);
    TEST_THROW(i = try_parse_number<std::int16_t>("-1000000000000001", 2),   std::out_of_range, "Number is out of range:");
    TEST_THROW(i = try_parse_number<std::int16_t>("-10000000000000000", 2),  std::out_of_range, "Number is out of range:");
    TEST_THROW(i = try_parse_number<std::int16_t>("", 2),                    std::invalid_argument, "Invalid number:");
    TEST_THROW(i = try_parse_number<std::int16_t>("1x", 2),                  std::invalid_argument, "Invalid number:");
    TEST_THROW(i = try_parse_number<std::int16_t>("hello", 2),               std::invalid_argument, "Invalid number:");
    TRY(u = try_parse_number<std::uint16_t>("0"));                           TEST_EQUAL(u, 0);
    TRY(u = try_parse_number<std::uint16_t>("42"));                          TEST_EQUAL(u, 42);
    TRY(u = try_parse_number<std::uint16_t>("65535"));                       TEST_EQUAL(u, 65535);
    TEST_THROW(u = try_parse_number<std::uint16_t>("65536"),                 std::out_of_range, "Number is out of range:");
    TEST_THROW(u = try_parse_number<std::uint16_t>("99999"),                 std::out_of_range, "Number is out of range:");
    TEST_THROW(u = try_parse_number<std::uint16_t>(""),                      std::invalid_argument, "Invalid number:");
    TEST_THROW(u = try_parse_number<std::uint16_t>("+42"),                   std::invalid_argument, "Invalid number:");
    TEST_THROW(u = try_parse_number<std::uint16_t>("-42"),                   std::invalid_argument, "Invalid number:");
    TEST_THROW(u = try_parse_number<std::uint16_t>("42a"),                   std::invalid_argument, "Invalid number:");
    TEST_THROW(u = try_parse_number<std::uint16_t>("hello"),                 std::invalid_argument, "Invalid number:");
    TRY(u = try_parse_number<std::uint16_t>("0", 16));                       TEST_EQUAL(u, 0);
    TRY(u = try_parse_number<std::uint16_t>("2a", 16));                      TEST_EQUAL(u, 42);
    TRY(u = try_parse_number<std::uint16_t>("ffff", 16));                    TEST_EQUAL(u, 65535);
    TEST_THROW(u = try_parse_number<std::uint16_t>("10000", 16),             std::out_of_range, "Number is out of range:");
    TEST_THROW(u = try_parse_number<std::uint16_t>("", 16),                  std::invalid_argument, "Invalid number:");
    TEST_THROW(u = try_parse_number<std::uint16_t>("+2a", 16),               std::invalid_argument, "Invalid number:");
    TEST_THROW(u = try_parse_number<std::uint16_t>("-2a", 16),               std::invalid_argument, "Invalid number:");
    TEST_THROW(u = try_parse_number<std::uint16_t>("2x", 16),                std::invalid_argument, "Invalid number:");
    TEST_THROW(u = try_parse_number<std::uint16_t>("hello", 16),             std::invalid_argument, "Invalid number:");
    TRY(u = try_parse_number<std::uint16_t>("0x0", 0));                      TEST_EQUAL(u, 0);
    TRY(u = try_parse_number<std::uint16_t>("0x2a", 0));                     TEST_EQUAL(u, 42);
    TRY(u = try_parse_number<std::uint16_t>("0xffff", 0));                   TEST_EQUAL(u, 65535);
    TEST_THROW(u = try_parse_number<std::uint16_t>("0x10000", 0),            std::out_of_range, "Number is out of range:");
    TEST_THROW(u = try_parse_number<std::uint16_t>("+0x2a", 0),              std::invalid_argument, "Invalid number:");
    TEST_THROW(u = try_parse_number<std::uint16_t>("-0x2a", 0),              std::invalid_argument, "Invalid number:");
    TEST_THROW(u = try_parse_number<std::uint16_t>("0x2x", 0),               std::invalid_argument, "Invalid number:");
    TEST_THROW(u = try_parse_number<std::uint16_t>("0xhello", 0),            std::invalid_argument, "Invalid number:");
    TRY(u = try_parse_number<std::uint16_t>("0", 2));                        TEST_EQUAL(u, 0);
    TRY(u = try_parse_number<std::uint16_t>("101010", 2));                   TEST_EQUAL(u, 42);
    TRY(u = try_parse_number<std::uint16_t>("1111111111111111", 2));         TEST_EQUAL(u, 65535);
    TEST_THROW(u = try_parse_number<std::uint16_t>("10000000000000000", 2),  std::out_of_range, "Number is out of range:");
    TEST_THROW(u = try_parse_number<std::uint16_t>("", 2),                   std::invalid_argument, "Invalid number:");
    TEST_THROW(u = try_parse_number<std::uint16_t>("+101010", 2),            std::invalid_argument, "Invalid number:");
    TEST_THROW(u = try_parse_number<std::uint16_t>("-101010", 2),            std::invalid_argument, "Invalid number:");
    TEST_THROW(u = try_parse_number<std::uint16_t>("1x", 2),                 std::invalid_argument, "Invalid number:");
    TEST_THROW(u = try_parse_number<std::uint16_t>("hello", 2),              std::invalid_argument, "Invalid number:");

}
