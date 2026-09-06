#include "rs-core/format.hpp"
#include "rs-core/unit-test.hpp"
#include <cmath>
#include <optional>
#include <stdexcept>

using namespace RS;

void test_rs_core_format_parse_floating_point_general() {

    ParseNumber rc {};
    double x {};

    TRY(rc = parse_number("0", x));         TEST(rc == ParseNumber::ok); TEST_EQUAL(x, 0);
    TRY(rc = parse_number("42", x));        TEST(rc == ParseNumber::ok); TEST_EQUAL(x, 42);
    TRY(rc = parse_number("+42", x));       TEST(rc == ParseNumber::ok); TEST_EQUAL(x, 42);
    TRY(rc = parse_number("-42", x));       TEST(rc == ParseNumber::ok); TEST_EQUAL(x, -42);
    TRY(rc = parse_number("1234.5", x));    TEST(rc == ParseNumber::ok); TEST_EQUAL(x, 1234.5);
    TRY(rc = parse_number("-1234.5", x));   TEST(rc == ParseNumber::ok); TEST_EQUAL(x, -1234.5);
    TRY(rc = parse_number("1e6", x));       TEST(rc == ParseNumber::ok); TEST_EQUAL(x, 1e6);
    TRY(rc = parse_number("-1e6", x));      TEST(rc == ParseNumber::ok); TEST_EQUAL(x, -1e6);
    TRY(rc = parse_number("5e-1", x));      TEST(rc == ParseNumber::ok); TEST_EQUAL(x, 0.5);
    TRY(rc = parse_number("-5e-1", x));     TEST(rc == ParseNumber::ok); TEST_EQUAL(x, -0.5);
    TRY(rc = parse_number("inf", x));       TEST(rc == ParseNumber::ok); TEST(std::isinf(x)); TEST(! std::signbit(x));
    TRY(rc = parse_number("+inf", x));      TEST(rc == ParseNumber::ok); TEST(std::isinf(x)); TEST(! std::signbit(x));
    TRY(rc = parse_number("-inf", x));      TEST(rc == ParseNumber::ok); TEST(std::isinf(x)); TEST(std::signbit(x));
    TRY(rc = parse_number("nan", x));       TEST(rc == ParseNumber::ok); TEST(std::isnan(x));
    TRY(rc = parse_number("", x));          TEST(rc == ParseNumber::invalid_number);
    TRY(rc = parse_number("42a", x));       TEST(rc == ParseNumber::invalid_number);
    TRY(rc = parse_number("hello", x));     TEST(rc == ParseNumber::invalid_number);
    TRY(rc = parse_number("1e9999", x));    TEST(rc == ParseNumber::out_of_range);
    TRY(rc = parse_number("-1e9999", x));   TEST(rc == ParseNumber::out_of_range);
    TRY(rc = parse_number("1e-9999", x));   TEST(rc == ParseNumber::out_of_range);
    TRY(rc = parse_number("-1e-9999", x));  TEST(rc == ParseNumber::out_of_range);

}

void test_rs_core_format_parse_floating_point_maybe() {

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

void test_rs_core_format_parse_floating_point_try() {

    double x {};

    TRY(x = try_parse_number<double>("0"));               TEST_EQUAL(x, 0);
    TRY(x = try_parse_number<double>("42"));              TEST_EQUAL(x, 42);
    TRY(x = try_parse_number<double>("+42"));             TEST_EQUAL(x, 42);
    TRY(x = try_parse_number<double>("-42"));             TEST_EQUAL(x, -42);
    TRY(x = try_parse_number<double>("1234.5"));          TEST_EQUAL(x, 1234.5);
    TRY(x = try_parse_number<double>("-1234.5"));         TEST_EQUAL(x, -1234.5);
    TRY(x = try_parse_number<double>("1e6"));             TEST_EQUAL(x, 1e6);
    TRY(x = try_parse_number<double>("-1e6"));            TEST_EQUAL(x, -1e6);
    TRY(x = try_parse_number<double>("5e-1"));            TEST_EQUAL(x, 0.5);
    TRY(x = try_parse_number<double>("-5e-1"));           TEST_EQUAL(x, -0.5);
    TRY(x = try_parse_number<double>("inf"));             TEST(std::isinf(x)); TEST(! std::signbit(x));
    TRY(x = try_parse_number<double>("+inf"));            TEST(std::isinf(x)); TEST(! std::signbit(x));
    TRY(x = try_parse_number<double>("-inf"));            TEST(std::isinf(x)); TEST(std::signbit(x));
    TRY(x = try_parse_number<double>("nan"));             TEST(std::isnan(x));
    TEST_THROW(x = try_parse_number<double>(""),          std::invalid_argument, "Invalid number:");
    TEST_THROW(x = try_parse_number<double>("42a"),       std::invalid_argument, "Invalid number:");
    TEST_THROW(x = try_parse_number<double>("hello"),     std::invalid_argument, "Invalid number:");
    TEST_THROW(x = try_parse_number<double>("1e9999"),    std::out_of_range, "Number is out of range:");
    TEST_THROW(x = try_parse_number<double>("-1e9999"),   std::out_of_range, "Number is out of range:");
    TEST_THROW(x = try_parse_number<double>("1e-9999"),   std::out_of_range, "Number is out of range:");
    TEST_THROW(x = try_parse_number<double>("-1e-9999"),  std::out_of_range, "Number is out of range:");

}
