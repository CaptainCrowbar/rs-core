#include "rs-core/rational.hpp"
#include "rs-core/unit-test.hpp"
#include <format>
#include <optional>
#include <stdexcept>
#include <string>

using namespace RS;

void test_rs_core_rational_int_formatting() {

    IntRational r;
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

    TRY((r = {}));          TRY(s = std::format("{}", r));     TEST_EQUAL(s, "0");
    /**/                    TRY(s = std::format("{:+}", r));   TEST_EQUAL(s, "+0");
    /**/                    TRY(s = std::format("{:V}", r));   TEST_EQUAL(s, "0/1");
    /**/                    TRY(s = std::format("{:+V}", r));  TEST_EQUAL(s, "+0/1");
    /**/                    TRY(s = std::format("{:m}", r));   TEST_EQUAL(s, "0");
    /**/                    TRY(s = std::format("{:+m}", r));  TEST_EQUAL(s, "+0");
    TRY((r = {42}));        TRY(s = std::format("{}", r));     TEST_EQUAL(s, "42");
    /**/                    TRY(s = std::format("{:+}", r));   TEST_EQUAL(s, "+42");
    /**/                    TRY(s = std::format("{:V}", r));   TEST_EQUAL(s, "42/1");
    /**/                    TRY(s = std::format("{:+V}", r));  TEST_EQUAL(s, "+42/1");
    /**/                    TRY(s = std::format("{:m}", r));   TEST_EQUAL(s, "42");
    /**/                    TRY(s = std::format("{:+m}", r));  TEST_EQUAL(s, "+42");
    TRY((r = {-42}));       TRY(s = std::format("{}", r));     TEST_EQUAL(s, "-42");
    /**/                    TRY(s = std::format("{:+}", r));   TEST_EQUAL(s, "-42");
    /**/                    TRY(s = std::format("{:V}", r));   TEST_EQUAL(s, "-42/1");
    /**/                    TRY(s = std::format("{:+V}", r));  TEST_EQUAL(s, "-42/1");
    /**/                    TRY(s = std::format("{:m}", r));   TEST_EQUAL(s, "-42");
    /**/                    TRY(s = std::format("{:+m}", r));  TEST_EQUAL(s, "-42");
    TRY((r = {2, 3}));      TRY(s = std::format("{}", r));     TEST_EQUAL(s, "2/3");
    /**/                    TRY(s = std::format("{:+}", r));   TEST_EQUAL(s, "+2/3");
    /**/                    TRY(s = std::format("{:V}", r));   TEST_EQUAL(s, "2/3");
    /**/                    TRY(s = std::format("{:+V}", r));  TEST_EQUAL(s, "+2/3");
    /**/                    TRY(s = std::format("{:m}", r));   TEST_EQUAL(s, "2/3");
    /**/                    TRY(s = std::format("{:+m}", r));  TEST_EQUAL(s, "+2/3");
    TRY((r = {-2, 3}));     TRY(s = std::format("{}", r));     TEST_EQUAL(s, "-2/3");
    /**/                    TRY(s = std::format("{:+}", r));   TEST_EQUAL(s, "-2/3");
    /**/                    TRY(s = std::format("{:V}", r));   TEST_EQUAL(s, "-2/3");
    /**/                    TRY(s = std::format("{:+V}", r));  TEST_EQUAL(s, "-2/3");
    /**/                    TRY(s = std::format("{:m}", r));   TEST_EQUAL(s, "-2/3");
    /**/                    TRY(s = std::format("{:+m}", r));  TEST_EQUAL(s, "-2/3");
    TRY((r = {5, 3}));      TRY(s = std::format("{}", r));     TEST_EQUAL(s, "5/3");
    /**/                    TRY(s = std::format("{:+}", r));   TEST_EQUAL(s, "+5/3");
    /**/                    TRY(s = std::format("{:V}", r));   TEST_EQUAL(s, "5/3");
    /**/                    TRY(s = std::format("{:+V}", r));  TEST_EQUAL(s, "+5/3");
    /**/                    TRY(s = std::format("{:m}", r));   TEST_EQUAL(s, "1 2/3");
    /**/                    TRY(s = std::format("{:+m}", r));  TEST_EQUAL(s, "+1 2/3");
    TRY((r = {-5, 3}));     TRY(s = std::format("{}", r));     TEST_EQUAL(s, "-5/3");
    /**/                    TRY(s = std::format("{:+}", r));   TEST_EQUAL(s, "-5/3");
    /**/                    TRY(s = std::format("{:V}", r));   TEST_EQUAL(s, "-5/3");
    /**/                    TRY(s = std::format("{:+V}", r));  TEST_EQUAL(s, "-5/3");
    /**/                    TRY(s = std::format("{:m}", r));   TEST_EQUAL(s, "-1 2/3");
    /**/                    TRY(s = std::format("{:+m}", r));  TEST_EQUAL(s, "-1 2/3");
    TRY((r = {100, 30}));   TRY(s = std::format("{}", r));     TEST_EQUAL(s, "10/3");
    /**/                    TRY(s = std::format("{:+}", r));   TEST_EQUAL(s, "+10/3");
    /**/                    TRY(s = std::format("{:V}", r));   TEST_EQUAL(s, "10/3");
    /**/                    TRY(s = std::format("{:+V}", r));  TEST_EQUAL(s, "+10/3");
    /**/                    TRY(s = std::format("{:m}", r));   TEST_EQUAL(s, "3 1/3");
    /**/                    TRY(s = std::format("{:+m}", r));  TEST_EQUAL(s, "+3 1/3");
    TRY((r = {-100, 30}));  TRY(s = std::format("{}", r));     TEST_EQUAL(s, "-10/3");
    /**/                    TRY(s = std::format("{:+}", r));   TEST_EQUAL(s, "-10/3");
    /**/                    TRY(s = std::format("{:V}", r));   TEST_EQUAL(s, "-10/3");
    /**/                    TRY(s = std::format("{:+V}", r));  TEST_EQUAL(s, "-10/3");
    /**/                    TRY(s = std::format("{:m}", r));   TEST_EQUAL(s, "-3 1/3");
    /**/                    TRY(s = std::format("{:+m}", r));  TEST_EQUAL(s, "-3 1/3");

}

void test_rs_core_rational_int_parsing() {

    IntRational r;
    std::optional<IntRational> opt;

    TRY(r = IntRational("0"));       TEST_EQUAL(r.num(), 0);    TEST_EQUAL(r.den(), 1);
    TRY(r = IntRational("42"));      TEST_EQUAL(r.num(), 42);   TEST_EQUAL(r.den(), 1);
    TRY(r = IntRational("-42"));     TEST_EQUAL(r.num(), -42);  TEST_EQUAL(r.den(), 1);
    TRY(r = IntRational("1/2"));     TEST_EQUAL(r.num(), 1);    TEST_EQUAL(r.den(), 2);
    TRY(r = IntRational("-1/2"));    TEST_EQUAL(r.num(), -1);   TEST_EQUAL(r.den(), 2);
    TRY(r = IntRational("30/12"));   TEST_EQUAL(r.num(), 5);    TEST_EQUAL(r.den(), 2);
    TRY(r = IntRational("-30/12"));  TEST_EQUAL(r.num(), -5);   TEST_EQUAL(r.den(), 2);
    TRY(r = IntRational("2 3/4"));   TEST_EQUAL(r.num(), 11);   TEST_EQUAL(r.den(), 4);
    TRY(r = IntRational("-2 3/4"));  TEST_EQUAL(r.num(), -11);  TEST_EQUAL(r.den(), 4);
    TRY(r = IntRational("4 6/8"));   TEST_EQUAL(r.num(), 19);   TEST_EQUAL(r.den(), 4);
    TRY(r = IntRational("-4 6/8"));  TEST_EQUAL(r.num(), -19);  TEST_EQUAL(r.den(), 4);

    TEST_THROW(IntRational("1 2"),    std::invalid_argument, "Invalid rational");
    TEST_THROW(IntRational("/1"),     std::invalid_argument, "Invalid rational");
    TEST_THROW(IntRational("1/"),     std::invalid_argument, "Invalid rational");
    TEST_THROW(IntRational("1/2/3"),  std::invalid_argument, "Invalid rational");
    TEST_THROW(IntRational("1.5"),    std::invalid_argument, "Invalid rational");

    TRY(opt = IntRational::parse("0"));       TEST(opt.has_value());  TEST_EQUAL(opt.value().num(), 0);    TEST_EQUAL(opt.value().den(), 1);
    TRY(opt = IntRational::parse("42"));      TEST(opt.has_value());  TEST_EQUAL(opt.value().num(), 42);   TEST_EQUAL(opt.value().den(), 1);
    TRY(opt = IntRational::parse("-42"));     TEST(opt.has_value());  TEST_EQUAL(opt.value().num(), -42);  TEST_EQUAL(opt.value().den(), 1);
    TRY(opt = IntRational::parse("1/2"));     TEST(opt.has_value());  TEST_EQUAL(opt.value().num(), 1);    TEST_EQUAL(opt.value().den(), 2);
    TRY(opt = IntRational::parse("-1/2"));    TEST(opt.has_value());  TEST_EQUAL(opt.value().num(), -1);   TEST_EQUAL(opt.value().den(), 2);
    TRY(opt = IntRational::parse("30/12"));   TEST(opt.has_value());  TEST_EQUAL(opt.value().num(), 5);    TEST_EQUAL(opt.value().den(), 2);
    TRY(opt = IntRational::parse("-30/12"));  TEST(opt.has_value());  TEST_EQUAL(opt.value().num(), -5);   TEST_EQUAL(opt.value().den(), 2);
    TRY(opt = IntRational::parse("2 3/4"));   TEST(opt.has_value());  TEST_EQUAL(opt.value().num(), 11);   TEST_EQUAL(opt.value().den(), 4);
    TRY(opt = IntRational::parse("-2 3/4"));  TEST(opt.has_value());  TEST_EQUAL(opt.value().num(), -11);  TEST_EQUAL(opt.value().den(), 4);
    TRY(opt = IntRational::parse("4 6/8"));   TEST(opt.has_value());  TEST_EQUAL(opt.value().num(), 19);   TEST_EQUAL(opt.value().den(), 4);
    TRY(opt = IntRational::parse("-4 6/8"));  TEST(opt.has_value());  TEST_EQUAL(opt.value().num(), -19);  TEST_EQUAL(opt.value().den(), 4);

    TRY(opt = IntRational::parse("1 2"));    TEST(! opt.has_value());
    TRY(opt = IntRational::parse("/1"));     TEST(! opt.has_value());
    TRY(opt = IntRational::parse("1/"));     TEST(! opt.has_value());
    TRY(opt = IntRational::parse("1/2/3"));  TEST(! opt.has_value());
    TRY(opt = IntRational::parse("1.5"));    TEST(! opt.has_value());

}
