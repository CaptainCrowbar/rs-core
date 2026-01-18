#include "rs-core/mp-integer.hpp"
#include "rs-core/unit-test.hpp"
#include <cstdint>
#include <optional>
#include <string>

using namespace RS;

void test_rs_core_mp_integer_signed_conversion_from_integer() {

    Integer x;
    std::string s;
    std::optional<std::int16_t> i;
    std::optional<std::uint16_t> u;
    std::optional<std::int32_t> j;
    std::optional<std::uint32_t> v;

    TEST_EQUAL(x.sign(), 0);
    TEST_EQUAL(static_cast<std::int64_t>(x), 0);
    TEST_EQUAL(static_cast<std::uint64_t>(x), 0u);
    TEST_EQUAL(static_cast<Natural>(x), 0u);

    TRY(x = 123'456'789l);
    TEST_EQUAL(x.sign(), 1);
    TEST_EQUAL(static_cast<std::int64_t>(x), 123'456'789l);
    TEST_EQUAL(static_cast<std::uint64_t>(x), 123'456'789ul);
    TEST_EQUAL(static_cast<Natural>(x), 123'456'789ul);

    TRY(x = -123'456'789l);
    TEST_EQUAL(x.sign(), -1);
    TEST_EQUAL(static_cast<std::int64_t>(x), -123'456'789l);
    TEST_EQUAL(static_cast<std::uint64_t>(x), 0u);
    TEST_EQUAL(static_cast<Natural>(x), 0u);

    TRY(x = 123'456'789'123'456'789ll);
    TEST_EQUAL(x.sign(), 1);
    TEST_EQUAL(static_cast<std::int64_t>(x), 123'456'789'123'456'789ll);
    TEST_EQUAL(static_cast<std::uint64_t>(x), 123'456'789'123'456'789ull);
    TEST_EQUAL(static_cast<Natural>(x), 123'456'789'123'456'789ull);

    TRY(x = -123'456'789'123'456'789ll);
    TEST_EQUAL(x.sign(), -1);
    TEST_EQUAL(static_cast<std::int64_t>(x), -123'456'789'123'456'789ll);
    TEST_EQUAL(static_cast<std::uint64_t>(x), 0u);
    TEST_EQUAL(static_cast<Natural>(x), 0u);

    TRY(x = 32'767l);
    TEST(x.in_range<std::int16_t>());   TRY(i = x.checked_cast<std::int16_t>());   TEST(i); TEST_EQUAL(*i, 32'767l);
    TEST(x.in_range<std::uint16_t>());  TRY(u = x.checked_cast<std::uint16_t>());  TEST(u); TEST_EQUAL(*u, 32'767ul);
    TEST(x.in_range<std::int32_t>());   TRY(j = x.checked_cast<std::int32_t>());   TEST(j); TEST_EQUAL(*j, 32'767l);
    TEST(x.in_range<std::uint32_t>());  TRY(v = x.checked_cast<std::uint32_t>());  TEST(v); TEST_EQUAL(*v, 32'767ul);

    TRY(x = 32'768l);
    TEST(! x.in_range<std::int16_t>());  TRY(i = x.checked_cast<std::int16_t>());   TEST(! i);
    TEST(x.in_range<std::uint16_t>());   TRY(u = x.checked_cast<std::uint16_t>());  TEST(u); TEST_EQUAL(*u, 32'768ul);
    TEST(x.in_range<std::int32_t>());    TRY(j = x.checked_cast<std::int32_t>());   TEST(j); TEST_EQUAL(*j, 32'768l);
    TEST(x.in_range<std::uint32_t>());   TRY(v = x.checked_cast<std::uint32_t>());  TEST(v); TEST_EQUAL(*v, 32'768ul);

    TRY(x = 65'535l);
    TEST(! x.in_range<std::int16_t>());  TRY(i = x.checked_cast<std::int16_t>());   TEST(! i);
    TEST(x.in_range<std::uint16_t>());   TRY(u = x.checked_cast<std::uint16_t>());  TEST(u); TEST_EQUAL(*u, 65'535ul);
    TEST(x.in_range<std::int32_t>());    TRY(j = x.checked_cast<std::int32_t>());   TEST(j); TEST_EQUAL(*j, 65'535l);
    TEST(x.in_range<std::uint32_t>());   TRY(v = x.checked_cast<std::uint32_t>());  TEST(v); TEST_EQUAL(*v, 65'535ul);

    TRY(x = 65'536l);
    TEST(! x.in_range<std::int16_t>());   TRY(i = x.checked_cast<std::int16_t>());   TEST(! i);
    TEST(! x.in_range<std::uint16_t>());  TRY(u = x.checked_cast<std::uint16_t>());  TEST(! u);
    TEST(x.in_range<std::int32_t>());     TRY(j = x.checked_cast<std::int32_t>());   TEST(j); TEST_EQUAL(*j, 65'536l);
    TEST(x.in_range<std::uint32_t>());    TRY(v = x.checked_cast<std::uint32_t>());  TEST(v); TEST_EQUAL(*v, 65'536ul);

    TRY(x = -32'767l);
    TEST(x.in_range<std::int16_t>());     TRY(i = x.checked_cast<std::int16_t>());   TEST(i); TEST_EQUAL(*i, -32'767l);
    TEST(! x.in_range<std::uint16_t>());  TRY(u = x.checked_cast<std::uint16_t>());  TEST(! u);
    TEST(x.in_range<std::int32_t>());     TRY(j = x.checked_cast<std::int32_t>());   TEST(j); TEST_EQUAL(*j, -32'767l);
    TEST(! x.in_range<std::uint32_t>());  TRY(v = x.checked_cast<std::uint32_t>());  TEST(! v);

    TRY(x = -32'768l);
    TEST(x.in_range<std::int16_t>());     TRY(i = x.checked_cast<std::int16_t>());   TEST(i); TEST_EQUAL(*i, -32'768l);
    TEST(! x.in_range<std::uint16_t>());  TRY(u = x.checked_cast<std::uint16_t>());  TEST(! u);
    TEST(x.in_range<std::int32_t>());     TRY(j = x.checked_cast<std::int32_t>());   TEST(j); TEST_EQUAL(*j, -32'768l);
    TEST(! x.in_range<std::uint32_t>());  TRY(v = x.checked_cast<std::uint32_t>());  TEST(! v);

    TRY(x = -32'769l);
    TEST(! x.in_range<std::int16_t>());   TRY(i = x.checked_cast<std::int16_t>());   TEST(! i);
    TEST(! x.in_range<std::uint16_t>());  TRY(u = x.checked_cast<std::uint16_t>());  TEST(! u);
    TEST(x.in_range<std::int32_t>());     TRY(j = x.checked_cast<std::int32_t>());   TEST(j); TEST_EQUAL(*j, -32'769l);
    TEST(! x.in_range<std::uint32_t>());  TRY(v = x.checked_cast<std::uint32_t>());  TEST(! v);

    TRY(x = -65'535l);
    TEST(! x.in_range<std::int16_t>());   TRY(i = x.checked_cast<std::int16_t>());   TEST(! i);
    TEST(! x.in_range<std::uint16_t>());  TRY(u = x.checked_cast<std::uint16_t>());  TEST(! u);
    TEST(x.in_range<std::int32_t>());     TRY(j = x.checked_cast<std::int32_t>());   TEST(j); TEST_EQUAL(*j, -65'535l);
    TEST(! x.in_range<std::uint32_t>());  TRY(v = x.checked_cast<std::uint32_t>());  TEST(! v);

    TRY(x = -65'536l);
    TEST(! x.in_range<std::int16_t>());   TRY(i = x.checked_cast<std::int16_t>());   TEST(! i);
    TEST(! x.in_range<std::uint16_t>());  TRY(u = x.checked_cast<std::uint16_t>());  TEST(! u);
    TEST(x.in_range<std::int32_t>());     TRY(j = x.checked_cast<std::int32_t>());   TEST(j); TEST_EQUAL(*j, -65'536l);
    TEST(! x.in_range<std::uint32_t>());  TRY(v = x.checked_cast<std::uint32_t>());  TEST(! v);

    TRY(x = -65'537l);
    TEST(! x.in_range<std::int16_t>());   TRY(i = x.checked_cast<std::int16_t>());   TEST(! i);
    TEST(! x.in_range<std::uint16_t>());  TRY(u = x.checked_cast<std::uint16_t>());  TEST(! u);
    TEST(x.in_range<std::int32_t>());     TRY(j = x.checked_cast<std::int32_t>());   TEST(j); TEST_EQUAL(*j, -65'537l);
    TEST(! x.in_range<std::uint32_t>());  TRY(v = x.checked_cast<std::uint32_t>());  TEST(! v);

}

void test_rs_core_mp_integer_signed_conversion_to_floating_point() {

    Integer x;
    Natural n{0xfedc'babc'defe'dcbaull, 0x9876'5432'1234'5678ull};
    double y{};

    TRY((x = 0));              TRY(y = x.as_double());  TEST_EQUAL(y, 0.0);
    TRY((x = 1));              TRY(y = x.as_double());  TEST_EQUAL(y, 1.0);
    TRY((x = -1));             TRY(y = x.as_double());  TEST_EQUAL(y, -1.0);
    TRY((x = 123'456'789l));   TRY(y = x.as_double());  TEST_EQUAL(y, 123'456'789.0);
    TRY((x = -123'456'789l));  TRY(y = x.as_double());  TEST_EQUAL(y, -123'456'789.0);
    TRY((x = n));              TRY(y = x.as_double());  TEST_NEAR(y, 3.387700037e38, 1e29);
    TRY((x = - x));            TRY(y = x.as_double());  TEST_NEAR(y, -3.387700037e38, 1e29);

}

void test_rs_core_mp_integer_signed_conversion_to_string() {

    Integer x;
    std::string s;

    TEST_EQUAL(x.sign(), 0);

    TRY(s = x.to_string());        TEST_EQUAL(s, "0");
    TRY(s = x.to_string(10, 15));  TEST_EQUAL(s, "000000000000000");
    TRY(s = x.to_string(16));      TEST_EQUAL(s, "0");

    TRY(x = 42);
    TEST_EQUAL(x.sign(), 1);

    TRY(s = x.to_string());        TEST_EQUAL(s, "42");
    TRY(s = x.to_string(10, 15));  TEST_EQUAL(s, "000000000000042");
    TRY(s = x.to_string(16));      TEST_EQUAL(s, "2a");

    TRY(x = 123'456'789l);
    TEST_EQUAL(x.sign(), 1);

    TRY(s = x.to_string());        TEST_EQUAL(s, "123456789");
    TRY(s = x.to_string(10, 15));  TEST_EQUAL(s, "000000123456789");
    TRY(s = x.to_string(16));      TEST_EQUAL(s, "75bcd15");

    TRY(x = - 123'456'789l);
    TEST_EQUAL(x.sign(), -1);

    TRY(s = x.to_string());        TEST_EQUAL(s, "-123456789");
    TRY(s = x.to_string(10, 15));  TEST_EQUAL(s, "-000000123456789");
    TRY(s = x.to_string(16));      TEST_EQUAL(s, "-75bcd15");

    TRY(x = 123'456'789'123'456'789ll);
    TEST_EQUAL(x.sign(), 1);

    TRY(s = x.to_string());        TEST_EQUAL(s, "123456789123456789");
    TRY(s = x.to_string(10, 15));  TEST_EQUAL(s, "123456789123456789");
    TRY(s = x.to_string(16));      TEST_EQUAL(s, "1b69b4bacd05f15");

    TRY(x = - 123'456'789'123'456'789ll);
    TEST_EQUAL(x.sign(), -1);

    TRY(s = x.to_string());        TEST_EQUAL(s, "-123456789123456789");
    TRY(s = x.to_string(10, 15));  TEST_EQUAL(s, "-123456789123456789");
    TRY(s = x.to_string(16));      TEST_EQUAL(s, "-1b69b4bacd05f15");

    TRY(x = Integer("123456789123456789123456789123456789123456789", 10));
    TEST_EQUAL(x.sign(), 1);

    TRY(s = x.to_string());        TEST_EQUAL(s, "123456789123456789123456789123456789123456789");
    TRY(s = x.to_string(10, 15));  TEST_EQUAL(s, "123456789123456789123456789123456789123456789");
    TRY(s = x.to_string(16));      TEST_EQUAL(s, "58936e53d139afefabb2683f150b684045f15");

    TRY(x = Integer("123456789abcdef123456789abcdef123456789abcdef123456789abcdef", 16));
    TEST_EQUAL(x.sign(), 1);

    TRY(s = x.to_string());        TEST_EQUAL(s, "125642457939796217460094503631385345882379387509263401568735420576681455");
    TRY(s = x.to_string(10, 15));  TEST_EQUAL(s, "125642457939796217460094503631385345882379387509263401568735420576681455");
    TRY(s = x.to_string(16));      TEST_EQUAL(s, "123456789abcdef123456789abcdef123456789abcdef123456789abcdef");

    TRY(x = Integer("-123456789123456789123456789123456789123456789", 10));
    TEST_EQUAL(x.sign(), -1);

    TRY(s = x.to_string());        TEST_EQUAL(s, "-123456789123456789123456789123456789123456789");
    TRY(s = x.to_string(10, 15));  TEST_EQUAL(s, "-123456789123456789123456789123456789123456789");
    TRY(s = x.to_string(16));      TEST_EQUAL(s, "-58936e53d139afefabb2683f150b684045f15");

    TRY(x = Integer("-123456789abcdef123456789abcdef123456789abcdef123456789abcdef", 16));
    TEST_EQUAL(x.sign(), -1);

    TRY(s = x.to_string());        TEST_EQUAL(s, "-125642457939796217460094503631385345882379387509263401568735420576681455");
    TRY(s = x.to_string(10, 15));  TEST_EQUAL(s, "-125642457939796217460094503631385345882379387509263401568735420576681455");
    TRY(s = x.to_string(16));      TEST_EQUAL(s, "-123456789abcdef123456789abcdef123456789abcdef123456789abcdef");

    TRY(x = Integer("123456789123456789123456789123456789123456789", 0));
    TEST_EQUAL(x.sign(), 1);

    TRY(s = x.to_string());        TEST_EQUAL(s, "123456789123456789123456789123456789123456789");
    TRY(s = x.to_string(10, 15));  TEST_EQUAL(s, "123456789123456789123456789123456789123456789");
    TRY(s = x.to_string(16));      TEST_EQUAL(s, "58936e53d139afefabb2683f150b684045f15");

    TRY(x = Integer("0x123456789abcdef123456789abcdef123456789abcdef123456789abcdef", 0));
    TEST_EQUAL(x.sign(), 1);

    TRY(s = x.to_string());        TEST_EQUAL(s, "125642457939796217460094503631385345882379387509263401568735420576681455");
    TRY(s = x.to_string(10, 15));  TEST_EQUAL(s, "125642457939796217460094503631385345882379387509263401568735420576681455");
    TRY(s = x.to_string(16));      TEST_EQUAL(s, "123456789abcdef123456789abcdef123456789abcdef123456789abcdef");

    TRY(x = Integer("-123456789123456789123456789123456789123456789", 0));
    TEST_EQUAL(x.sign(), -1);

    TRY(s = x.to_string());        TEST_EQUAL(s, "-123456789123456789123456789123456789123456789");
    TRY(s = x.to_string(10, 15));  TEST_EQUAL(s, "-123456789123456789123456789123456789123456789");
    TRY(s = x.to_string(16));      TEST_EQUAL(s, "-58936e53d139afefabb2683f150b684045f15");

    TRY(x = Integer("-0x123456789abcdef123456789abcdef123456789abcdef123456789abcdef", 0));
    TEST_EQUAL(x.sign(), -1);

    TRY(s = x.to_string());        TEST_EQUAL(s, "-125642457939796217460094503631385345882379387509263401568735420576681455");
    TRY(s = x.to_string(10, 15));  TEST_EQUAL(s, "-125642457939796217460094503631385345882379387509263401568735420576681455");
    TRY(s = x.to_string(16));      TEST_EQUAL(s, "-123456789abcdef123456789abcdef123456789abcdef123456789abcdef");

    TRY(x = Integer("123'456'789'123'456'789'123'456'789'123'456'789'123'456'789", 10));
    TEST_EQUAL(x.sign(), 1);

    TRY(s = x.to_string());        TEST_EQUAL(s, "123456789123456789123456789123456789123456789");
    TRY(s = x.to_string(10, 15));  TEST_EQUAL(s, "123456789123456789123456789123456789123456789");
    TRY(s = x.to_string(16));      TEST_EQUAL(s, "58936e53d139afefabb2683f150b684045f15");

    TRY(x = Integer("123_456_789_123_456_789_123_456_789_123_456_789_123_456_789", 10));
    TEST_EQUAL(x.sign(), 1);

    TRY(s = x.to_string());        TEST_EQUAL(s, "123456789123456789123456789123456789123456789");
    TRY(s = x.to_string(10, 15));  TEST_EQUAL(s, "123456789123456789123456789123456789123456789");
    TRY(s = x.to_string(16));      TEST_EQUAL(s, "58936e53d139afefabb2683f150b684045f15");

    TRY(x = Integer("-0x1234'5678'9abc'def1'2345'6789'abcd'ef12'3456'789a'bcde'f123'4567'89ab'cdef", 0));
    TEST_EQUAL(x.sign(), -1);

    TRY(s = x.to_string());        TEST_EQUAL(s, "-125642457939796217460094503631385345882379387509263401568735420576681455");
    TRY(s = x.to_string(10, 15));  TEST_EQUAL(s, "-125642457939796217460094503631385345882379387509263401568735420576681455");
    TRY(s = x.to_string(16));      TEST_EQUAL(s, "-123456789abcdef123456789abcdef123456789abcdef123456789abcdef");

    TRY(x = Integer("-0x1234_5678_9abc_def1_2345_6789_abcd_ef12_3456_789a_bcde_f123_4567_89ab_cdef", 0));
    TEST_EQUAL(x.sign(), -1);

    TRY(s = x.to_string());        TEST_EQUAL(s, "-125642457939796217460094503631385345882379387509263401568735420576681455");
    TRY(s = x.to_string(10, 15));  TEST_EQUAL(s, "-125642457939796217460094503631385345882379387509263401568735420576681455");
    TRY(s = x.to_string(16));      TEST_EQUAL(s, "-123456789abcdef123456789abcdef123456789abcdef123456789abcdef");

}

void test_rs_core_mp_integer_signed_conversion_from_string() {

    Integer x;
    std::optional<Integer> y;

    TRY(y = Integer::parse("0",                                            2));   TEST(y);  TEST_EQUAL(y.value().to_string(), "0");
    TRY(y = Integer::parse("101010",                                       2));   TEST(y);  TEST_EQUAL(y.value().to_string(), "42");
    TRY(y = Integer::parse("1011011111110111000001110000110100",           2));   TEST(y);  TEST_EQUAL(y.value().to_string(), "12345678900");
    TRY(y = Integer::parse("10'1010",                                      2));   TEST(y);  TEST_EQUAL(y.value().to_string(), "42");
    TRY(y = Integer::parse("10'1101'1111'1101'1100'0001'1100'0011'0100",   2));   TEST(y);  TEST_EQUAL(y.value().to_string(), "12345678900");
    TRY(y = Integer::parse("10_1010",                                      2));   TEST(y);  TEST_EQUAL(y.value().to_string(), "42");
    TRY(y = Integer::parse("10_1101_1111_1101_1100_0001_1100_0011_0100",   2));   TEST(y);  TEST_EQUAL(y.value().to_string(), "12345678900");
    TRY(y = Integer::parse("-0",                                           2));   TEST(y);  TEST_EQUAL(y.value().to_string(), "0");
    TRY(y = Integer::parse("+101010",                                      2));   TEST(y);  TEST_EQUAL(y.value().to_string(), "42");
    TRY(y = Integer::parse("-1011011111110111000001110000110100",          2));   TEST(y);  TEST_EQUAL(y.value().to_string(), "-12345678900");
    TRY(y = Integer::parse("-10'1010",                                     2));   TEST(y);  TEST_EQUAL(y.value().to_string(), "-42");
    TRY(y = Integer::parse("-10'1101'1111'1101'1100'0001'1100'0011'0100",  2));   TEST(y);  TEST_EQUAL(y.value().to_string(), "-12345678900");
    TRY(y = Integer::parse("-10_1010",                                     2));   TEST(y);  TEST_EQUAL(y.value().to_string(), "-42");
    TRY(y = Integer::parse("-10_1101_1111_1101_1100_0001_1100_0011_0100",  2));   TEST(y);  TEST_EQUAL(y.value().to_string(), "-12345678900");
    TRY(y = Integer::parse("0",                                            10));  TEST(y);  TEST_EQUAL(y.value().to_string(), "0");
    TRY(y = Integer::parse("42",                                           10));  TEST(y);  TEST_EQUAL(y.value().to_string(), "42");
    TRY(y = Integer::parse("123456789",                                    10));  TEST(y);  TEST_EQUAL(y.value().to_string(), "123456789");
    TRY(y = Integer::parse("123456789123456789",                           10));  TEST(y);  TEST_EQUAL(y.value().to_string(), "123456789123456789");
    TRY(y = Integer::parse("123456789123456789123456789",                  10));  TEST(y);  TEST_EQUAL(y.value().to_string(), "123456789123456789123456789");
    TRY(y = Integer::parse("123456789123456789123456789123456789",         10));  TEST(y);  TEST_EQUAL(y.value().to_string(), "123456789123456789123456789123456789");
    TRY(y = Integer::parse("123_456_789",                                  10));  TEST(y);  TEST_EQUAL(y.value().to_string(), "123456789");
    TRY(y = Integer::parse("123_456_789_123_456_789",                      10));  TEST(y);  TEST_EQUAL(y.value().to_string(), "123456789123456789");
    TRY(y = Integer::parse("123_456_789_123_456_789_123_456_789",          10));  TEST(y);  TEST_EQUAL(y.value().to_string(), "123456789123456789123456789");
    TRY(y = Integer::parse("123'456'789",                                  10));  TEST(y);  TEST_EQUAL(y.value().to_string(), "123456789");
    TRY(y = Integer::parse("123'456'789'123'456'789",                      10));  TEST(y);  TEST_EQUAL(y.value().to_string(), "123456789123456789");
    TRY(y = Integer::parse("123'456'789'123'456'789'123'456'789",          10));  TEST(y);  TEST_EQUAL(y.value().to_string(), "123456789123456789123456789");
    TRY(y = Integer::parse("-0",                                           10));  TEST(y);  TEST_EQUAL(y.value().to_string(), "0");
    TRY(y = Integer::parse("+123456789",                                   10));  TEST(y);  TEST_EQUAL(y.value().to_string(), "123456789");
    TRY(y = Integer::parse("-123456789123456789",                          10));  TEST(y);  TEST_EQUAL(y.value().to_string(), "-123456789123456789");
    TRY(y = Integer::parse("+123456789123456789123456789",                 10));  TEST(y);  TEST_EQUAL(y.value().to_string(), "123456789123456789123456789");
    TRY(y = Integer::parse("-123456789123456789123456789123456789",        10));  TEST(y);  TEST_EQUAL(y.value().to_string(), "-123456789123456789123456789123456789");
    TRY(y = Integer::parse("-123_456_789",                                 10));  TEST(y);  TEST_EQUAL(y.value().to_string(), "-123456789");
    TRY(y = Integer::parse("-123_456_789_123_456_789",                     10));  TEST(y);  TEST_EQUAL(y.value().to_string(), "-123456789123456789");
    TRY(y = Integer::parse("-123_456_789_123_456_789_123_456_789",         10));  TEST(y);  TEST_EQUAL(y.value().to_string(), "-123456789123456789123456789");
    TRY(y = Integer::parse("-123'456'789",                                 10));  TEST(y);  TEST_EQUAL(y.value().to_string(), "-123456789");
    TRY(y = Integer::parse("-123'456'789'123'456'789",                     10));  TEST(y);  TEST_EQUAL(y.value().to_string(), "-123456789123456789");
    TRY(y = Integer::parse("-123'456'789'123'456'789'123'456'789",         10));  TEST(y);  TEST_EQUAL(y.value().to_string(), "-123456789123456789123456789");
    TRY(y = Integer::parse("0",                                            16));  TEST(y);  TEST_EQUAL(y.value().to_string(), "0");
    TRY(y = Integer::parse("abcdef",                                       16));  TEST(y);  TEST_EQUAL(y.value().to_string(), "11259375");
    TRY(y = Integer::parse("abcdef123456789abcdef",                        16));  TEST(y);  TEST_EQUAL(y.value().to_string(), "12981175647918246886886895");
    TRY(y = Integer::parse("ab'cdef",                                      16));  TEST(y);  TEST_EQUAL(y.value().to_string(), "11259375");
    TRY(y = Integer::parse("a'bcde'f123'4567'89ab'cdef",                   16));  TEST(y);  TEST_EQUAL(y.value().to_string(), "12981175647918246886886895");
    TRY(y = Integer::parse("ab_cdef",                                      16));  TEST(y);  TEST_EQUAL(y.value().to_string(), "11259375");
    TRY(y = Integer::parse("a_bcde_f123_4567_89ab_cdef",                   16));  TEST(y);  TEST_EQUAL(y.value().to_string(), "12981175647918246886886895");
    TRY(y = Integer::parse("-0",                                           16));  TEST(y);  TEST_EQUAL(y.value().to_string(), "0");
    TRY(y = Integer::parse("+abcdef",                                      16));  TEST(y);  TEST_EQUAL(y.value().to_string(), "11259375");
    TRY(y = Integer::parse("-abcdef123456789abcdef",                       16));  TEST(y);  TEST_EQUAL(y.value().to_string(), "-12981175647918246886886895");
    TRY(y = Integer::parse("-ab'cdef",                                     16));  TEST(y);  TEST_EQUAL(y.value().to_string(), "-11259375");
    TRY(y = Integer::parse("-a'bcde'f123'4567'89ab'cdef",                  16));  TEST(y);  TEST_EQUAL(y.value().to_string(), "-12981175647918246886886895");
    TRY(y = Integer::parse("-ab_cdef",                                     16));  TEST(y);  TEST_EQUAL(y.value().to_string(), "-11259375");
    TRY(y = Integer::parse("-a_bcde_f123_4567_89ab_cdef",                  16));  TEST(y);  TEST_EQUAL(y.value().to_string(), "-12981175647918246886886895");
    TRY(y = Integer::parse("0",                                            0));   TEST(y);  TEST_EQUAL(y.value().to_string(), "0");
    TRY(y = Integer::parse("42",                                           0));   TEST(y);  TEST_EQUAL(y.value().to_string(), "42");
    TRY(y = Integer::parse("123456789",                                    0));   TEST(y);  TEST_EQUAL(y.value().to_string(), "123456789");
    TRY(y = Integer::parse("123456789123456789",                           0));   TEST(y);  TEST_EQUAL(y.value().to_string(), "123456789123456789");
    TRY(y = Integer::parse("123456789123456789123456789",                  0));   TEST(y);  TEST_EQUAL(y.value().to_string(), "123456789123456789123456789");
    TRY(y = Integer::parse("123456789123456789123456789123456789",         0));   TEST(y);  TEST_EQUAL(y.value().to_string(), "123456789123456789123456789123456789");
    TRY(y = Integer::parse("0b0",                                          0));   TEST(y);  TEST_EQUAL(y.value().to_string(), "0");
    TRY(y = Integer::parse("0b101010",                                     0));   TEST(y);  TEST_EQUAL(y.value().to_string(), "42");
    TRY(y = Integer::parse("0b1011011111110111000001110000110100",         0));   TEST(y);  TEST_EQUAL(y.value().to_string(), "12345678900");
    TRY(y = Integer::parse("0x0",                                          0));   TEST(y);  TEST_EQUAL(y.value().to_string(), "0");
    TRY(y = Integer::parse("0xabcdef",                                     0));   TEST(y);  TEST_EQUAL(y.value().to_string(), "11259375");
    TRY(y = Integer::parse("0xabcdef123456789abcdef",                      0));   TEST(y);  TEST_EQUAL(y.value().to_string(), "12981175647918246886886895");
    TRY(y = Integer::parse("-0",                                           0));   TEST(y);  TEST_EQUAL(y.value().to_string(), "0");
    TRY(y = Integer::parse("-42",                                          0));   TEST(y);  TEST_EQUAL(y.value().to_string(), "-42");
    TRY(y = Integer::parse("+123456789",                                   0));   TEST(y);  TEST_EQUAL(y.value().to_string(), "123456789");
    TRY(y = Integer::parse("-123456789123456789",                          0));   TEST(y);  TEST_EQUAL(y.value().to_string(), "-123456789123456789");
    TRY(y = Integer::parse("+123456789123456789123456789",                 0));   TEST(y);  TEST_EQUAL(y.value().to_string(), "123456789123456789123456789");
    TRY(y = Integer::parse("-123456789123456789123456789123456789",        0));   TEST(y);  TEST_EQUAL(y.value().to_string(), "-123456789123456789123456789123456789");
    TRY(y = Integer::parse("-0b0",                                         0));   TEST(y);  TEST_EQUAL(y.value().to_string(), "0");
    TRY(y = Integer::parse("+0b101010",                                    0));   TEST(y);  TEST_EQUAL(y.value().to_string(), "42");
    TRY(y = Integer::parse("-0b1011011111110111000001110000110100",        0));   TEST(y);  TEST_EQUAL(y.value().to_string(), "-12345678900");
    TRY(y = Integer::parse("-0x0",                                         0));   TEST(y);  TEST_EQUAL(y.value().to_string(), "0");
    TRY(y = Integer::parse("+0xabcdef",                                    0));   TEST(y);  TEST_EQUAL(y.value().to_string(), "11259375");
    TRY(y = Integer::parse("-0xabcdef123456789abcdef",                     0));   TEST(y);  TEST_EQUAL(y.value().to_string(), "-12981175647918246886886895");

    TRY(y = Integer::parse(""));           TEST(! y);
    TRY(y = Integer::parse("", 0));        TEST(! y);
    TRY(y = Integer::parse("abc"));        TEST(! y);
    TRY(y = Integer::parse("abc", 0));     TEST(! y);
    TRY(y = Integer::parse("123abc"));     TEST(! y);
    TRY(y = Integer::parse("123abc", 0));  TEST(! y);

    TRY(x = Integer("0",                                      10));  TEST_EQUAL(x.to_string(), "0");
    TRY(x = Integer("42",                                     10));  TEST_EQUAL(x.to_string(), "42");
    TRY(x = Integer("123456789",                              10));  TEST_EQUAL(x.to_string(), "123456789");
    TRY(x = Integer("123456789123456789",                     10));  TEST_EQUAL(x.to_string(), "123456789123456789");
    TRY(x = Integer("123456789123456789123456789",            10));  TEST_EQUAL(x.to_string(), "123456789123456789123456789");
    TRY(x = Integer("123456789123456789123456789123456789",   10));  TEST_EQUAL(x.to_string(), "123456789123456789123456789123456789");
    TRY(x = Integer("0",                                      2));   TEST_EQUAL(x.to_string(), "0");
    TRY(x = Integer("101010",                                 2));   TEST_EQUAL(x.to_string(), "42");
    TRY(x = Integer("1011011111110111000001110000110100",     2));   TEST_EQUAL(x.to_string(), "12345678900");
    TRY(x = Integer("0",                                      16));  TEST_EQUAL(x.to_string(), "0");
    TRY(x = Integer("abcdef",                                 16));  TEST_EQUAL(x.to_string(), "11259375");
    TRY(x = Integer("abcdef123456789abcdef",                  16));  TEST_EQUAL(x.to_string(), "12981175647918246886886895");
    TRY(x = Integer("0",                                      0));   TEST_EQUAL(x.to_string(), "0");
    TRY(x = Integer("42",                                     0));   TEST_EQUAL(x.to_string(), "42");
    TRY(x = Integer("123456789",                              0));   TEST_EQUAL(x.to_string(), "123456789");
    TRY(x = Integer("123456789123456789",                     0));   TEST_EQUAL(x.to_string(), "123456789123456789");
    TRY(x = Integer("123456789123456789123456789",            0));   TEST_EQUAL(x.to_string(), "123456789123456789123456789");
    TRY(x = Integer("123456789123456789123456789123456789",   0));   TEST_EQUAL(x.to_string(), "123456789123456789123456789123456789");
    TRY(x = Integer("0b0",                                    0));   TEST_EQUAL(x.to_string(), "0");
    TRY(x = Integer("0b101010",                               0));   TEST_EQUAL(x.to_string(), "42");
    TRY(x = Integer("0b1011011111110111000001110000110100",   0));   TEST_EQUAL(x.to_string(), "12345678900");
    TRY(x = Integer("0x0",                                    0));   TEST_EQUAL(x.to_string(), "0");
    TRY(x = Integer("0xabcdef",                               0));   TEST_EQUAL(x.to_string(), "11259375");
    TRY(x = Integer("0xabcdef123456789abcdef",                0));   TEST_EQUAL(x.to_string(), "12981175647918246886886895");
    TRY(x = Integer("+0",                                     10));  TEST_EQUAL(x.to_string(), "0");
    TRY(x = Integer("+42",                                    10));  TEST_EQUAL(x.to_string(), "42");
    TRY(x = Integer("+0",                                     2));   TEST_EQUAL(x.to_string(), "0");
    TRY(x = Integer("+101010",                                2));   TEST_EQUAL(x.to_string(), "42");
    TRY(x = Integer("+0",                                     16));  TEST_EQUAL(x.to_string(), "0");
    TRY(x = Integer("+abcdef",                                16));  TEST_EQUAL(x.to_string(), "11259375");
    TRY(x = Integer("+0",                                     0));   TEST_EQUAL(x.to_string(), "0");
    TRY(x = Integer("+42",                                    0));   TEST_EQUAL(x.to_string(), "42");
    TRY(x = Integer("+0b0",                                   0));   TEST_EQUAL(x.to_string(), "0");
    TRY(x = Integer("+0b101010",                              0));   TEST_EQUAL(x.to_string(), "42");
    TRY(x = Integer("+0x0",                                   0));   TEST_EQUAL(x.to_string(), "0");
    TRY(x = Integer("+0xabcdef",                              0));   TEST_EQUAL(x.to_string(), "11259375");
    TRY(x = Integer("-0",                                     10));  TEST_EQUAL(x.to_string(), "0");
    TRY(x = Integer("-42",                                    10));  TEST_EQUAL(x.to_string(), "-42");
    TRY(x = Integer("-123456789",                             10));  TEST_EQUAL(x.to_string(), "-123456789");
    TRY(x = Integer("-123456789123456789",                    10));  TEST_EQUAL(x.to_string(), "-123456789123456789");
    TRY(x = Integer("-123456789123456789123456789",           10));  TEST_EQUAL(x.to_string(), "-123456789123456789123456789");
    TRY(x = Integer("-123456789123456789123456789123456789",  10));  TEST_EQUAL(x.to_string(), "-123456789123456789123456789123456789");
    TRY(x = Integer("-0",                                     2));   TEST_EQUAL(x.to_string(), "0");
    TRY(x = Integer("-101010",                                2));   TEST_EQUAL(x.to_string(), "-42");
    TRY(x = Integer("-1011011111110111000001110000110100",    2));   TEST_EQUAL(x.to_string(), "-12345678900");
    TRY(x = Integer("-0",                                     16));  TEST_EQUAL(x.to_string(), "0");
    TRY(x = Integer("-abcdef",                                16));  TEST_EQUAL(x.to_string(), "-11259375");
    TRY(x = Integer("-abcdef123456789abcdef",                 16));  TEST_EQUAL(x.to_string(), "-12981175647918246886886895");
    TRY(x = Integer("-0",                                     0));   TEST_EQUAL(x.to_string(), "0");
    TRY(x = Integer("-42",                                    0));   TEST_EQUAL(x.to_string(), "-42");
    TRY(x = Integer("-123456789",                             0));   TEST_EQUAL(x.to_string(), "-123456789");
    TRY(x = Integer("-123456789123456789",                    0));   TEST_EQUAL(x.to_string(), "-123456789123456789");
    TRY(x = Integer("-123456789123456789123456789",           0));   TEST_EQUAL(x.to_string(), "-123456789123456789123456789");
    TRY(x = Integer("-123456789123456789123456789123456789",  0));   TEST_EQUAL(x.to_string(), "-123456789123456789123456789123456789");
    TRY(x = Integer("-0b0",                                   0));   TEST_EQUAL(x.to_string(), "0");
    TRY(x = Integer("-0b101010",                              0));   TEST_EQUAL(x.to_string(), "-42");
    TRY(x = Integer("-0b1011011111110111000001110000110100",  0));   TEST_EQUAL(x.to_string(), "-12345678900");
    TRY(x = Integer("-0x0",                                   0));   TEST_EQUAL(x.to_string(), "0");
    TRY(x = Integer("-0xabcdef",                              0));   TEST_EQUAL(x.to_string(), "-11259375");
    TRY(x = Integer("-0xabcdef123456789abcdef",               0));   TEST_EQUAL(x.to_string(), "-12981175647918246886886895");

}
