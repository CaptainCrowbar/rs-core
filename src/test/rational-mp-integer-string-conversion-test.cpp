#include "rs-core/rational.hpp"
#include "rs-core/mp-integer.hpp"
#include "rs-core/unit-test.hpp"
#include <format>
#include <optional>
#include <stdexcept>
#include <string>

using namespace RS;
using namespace RS::Literals;

void test_rs_core_rational_mp_integer_formatting() {

    MPRational r;
    std::string s;

    TRY((r = {}));          TRY(s = r.to_string());  TEST_EQUAL(s, "0");      TRY(s = r.mixed());  TEST_EQUAL(s, "0");
    TRY((r = {42}));        TRY(s = r.to_string());  TEST_EQUAL(s, "42");     TRY(s = r.mixed());  TEST_EQUAL(s, "42");
    TRY((r = {-42}));       TRY(s = r.to_string());  TEST_EQUAL(s, "-42");    TRY(s = r.mixed());  TEST_EQUAL(s, "-42");
    TRY((r = {2, 3}));      TRY(s = r.to_string());  TEST_EQUAL(s, "2/3");    TRY(s = r.mixed());  TEST_EQUAL(s, "2/3");
    TRY((r = {-2, 3}));     TRY(s = r.to_string());  TEST_EQUAL(s, "-2/3");   TRY(s = r.mixed());  TEST_EQUAL(s, "-2/3");
    TRY((r = {5, 3}));      TRY(s = r.to_string());  TEST_EQUAL(s, "5/3");    TRY(s = r.mixed());  TEST_EQUAL(s, "1 2/3");
    TRY((r = {-5, 3}));     TRY(s = r.to_string());  TEST_EQUAL(s, "-5/3");   TRY(s = r.mixed());  TEST_EQUAL(s, "-1 2/3");
    TRY((r = {100, 30}));   TRY(s = r.to_string());  TEST_EQUAL(s, "10/3");   TRY(s = r.mixed());  TEST_EQUAL(s, "3 1/3");
    TRY((r = {-100, 30}));  TRY(s = r.to_string());  TEST_EQUAL(s, "-10/3");  TRY(s = r.mixed());  TEST_EQUAL(s, "-3 1/3");

    TRY((r = {}));          TRY(s = std::format("{}", r));  TEST_EQUAL(s, "0");      TRY(s = std::format("{:m}", r));  TEST_EQUAL(s, "0");
    TRY((r = {42}));        TRY(s = std::format("{}", r));  TEST_EQUAL(s, "42");     TRY(s = std::format("{:m}", r));  TEST_EQUAL(s, "42");
    TRY((r = {-42}));       TRY(s = std::format("{}", r));  TEST_EQUAL(s, "-42");    TRY(s = std::format("{:m}", r));  TEST_EQUAL(s, "-42");
    TRY((r = {2, 3}));      TRY(s = std::format("{}", r));  TEST_EQUAL(s, "2/3");    TRY(s = std::format("{:m}", r));  TEST_EQUAL(s, "2/3");
    TRY((r = {-2, 3}));     TRY(s = std::format("{}", r));  TEST_EQUAL(s, "-2/3");   TRY(s = std::format("{:m}", r));  TEST_EQUAL(s, "-2/3");
    TRY((r = {5, 3}));      TRY(s = std::format("{}", r));  TEST_EQUAL(s, "5/3");    TRY(s = std::format("{:m}", r));  TEST_EQUAL(s, "1 2/3");
    TRY((r = {-5, 3}));     TRY(s = std::format("{}", r));  TEST_EQUAL(s, "-5/3");   TRY(s = std::format("{:m}", r));  TEST_EQUAL(s, "-1 2/3");
    TRY((r = {100, 30}));   TRY(s = std::format("{}", r));  TEST_EQUAL(s, "10/3");   TRY(s = std::format("{:m}", r));  TEST_EQUAL(s, "3 1/3");
    TRY((r = {-100, 30}));  TRY(s = std::format("{}", r));  TEST_EQUAL(s, "-10/3");  TRY(s = std::format("{:m}", r));  TEST_EQUAL(s, "-3 1/3");

}

void test_rs_core_rational_mp_integer_parsing() {

    MPRational r;
    std::optional<MPRational> opt;

    TRY(r = MPRational("0"));       TEST_EQUAL(r.num(), 0);    TEST_EQUAL(r.den(), 1);
    TRY(r = MPRational("42"));      TEST_EQUAL(r.num(), 42);   TEST_EQUAL(r.den(), 1);
    TRY(r = MPRational("-42"));     TEST_EQUAL(r.num(), -42);  TEST_EQUAL(r.den(), 1);
    TRY(r = MPRational("1/2"));     TEST_EQUAL(r.num(), 1);    TEST_EQUAL(r.den(), 2);
    TRY(r = MPRational("-1/2"));    TEST_EQUAL(r.num(), -1);   TEST_EQUAL(r.den(), 2);
    TRY(r = MPRational("30/12"));   TEST_EQUAL(r.num(), 5);    TEST_EQUAL(r.den(), 2);
    TRY(r = MPRational("-30/12"));  TEST_EQUAL(r.num(), -5);   TEST_EQUAL(r.den(), 2);
    TRY(r = MPRational("2 3/4"));   TEST_EQUAL(r.num(), 11);   TEST_EQUAL(r.den(), 4);
    TRY(r = MPRational("-2 3/4"));  TEST_EQUAL(r.num(), -11);  TEST_EQUAL(r.den(), 4);
    TRY(r = MPRational("4 6/8"));   TEST_EQUAL(r.num(), 19);   TEST_EQUAL(r.den(), 4);
    TRY(r = MPRational("-4 6/8"));  TEST_EQUAL(r.num(), -19);  TEST_EQUAL(r.den(), 4);

    TEST_THROW(MPRational("1 2"),    std::invalid_argument, "Invalid rational");
    TEST_THROW(MPRational("/1"),     std::invalid_argument, "Invalid rational");
    TEST_THROW(MPRational("1/"),     std::invalid_argument, "Invalid rational");
    TEST_THROW(MPRational("1/2/3"),  std::invalid_argument, "Invalid rational");
    TEST_THROW(MPRational("1.5"),    std::invalid_argument, "Invalid rational");

    TRY(opt = MPRational::parse("0"));       TEST(opt.has_value());  TEST_EQUAL(opt.value().num(), 0);    TEST_EQUAL(opt.value().den(), 1);
    TRY(opt = MPRational::parse("42"));      TEST(opt.has_value());  TEST_EQUAL(opt.value().num(), 42);   TEST_EQUAL(opt.value().den(), 1);
    TRY(opt = MPRational::parse("-42"));     TEST(opt.has_value());  TEST_EQUAL(opt.value().num(), -42);  TEST_EQUAL(opt.value().den(), 1);
    TRY(opt = MPRational::parse("1/2"));     TEST(opt.has_value());  TEST_EQUAL(opt.value().num(), 1);    TEST_EQUAL(opt.value().den(), 2);
    TRY(opt = MPRational::parse("-1/2"));    TEST(opt.has_value());  TEST_EQUAL(opt.value().num(), -1);   TEST_EQUAL(opt.value().den(), 2);
    TRY(opt = MPRational::parse("30/12"));   TEST(opt.has_value());  TEST_EQUAL(opt.value().num(), 5);    TEST_EQUAL(opt.value().den(), 2);
    TRY(opt = MPRational::parse("-30/12"));  TEST(opt.has_value());  TEST_EQUAL(opt.value().num(), -5);   TEST_EQUAL(opt.value().den(), 2);
    TRY(opt = MPRational::parse("2 3/4"));   TEST(opt.has_value());  TEST_EQUAL(opt.value().num(), 11);   TEST_EQUAL(opt.value().den(), 4);
    TRY(opt = MPRational::parse("-2 3/4"));  TEST(opt.has_value());  TEST_EQUAL(opt.value().num(), -11);  TEST_EQUAL(opt.value().den(), 4);
    TRY(opt = MPRational::parse("4 6/8"));   TEST(opt.has_value());  TEST_EQUAL(opt.value().num(), 19);   TEST_EQUAL(opt.value().den(), 4);
    TRY(opt = MPRational::parse("-4 6/8"));  TEST(opt.has_value());  TEST_EQUAL(opt.value().num(), -19);  TEST_EQUAL(opt.value().den(), 4);

    TRY(opt = MPRational::parse("1 2"));    TEST(! opt.has_value());
    TRY(opt = MPRational::parse("/1"));     TEST(! opt.has_value());
    TRY(opt = MPRational::parse("1/"));     TEST(! opt.has_value());
    TRY(opt = MPRational::parse("1/2/3"));  TEST(! opt.has_value());
    TRY(opt = MPRational::parse("1.5"));    TEST(! opt.has_value());

}
