#include "rs-core/mp-integer.hpp"
#include "rs-core/unit-test.hpp"
#include <cstdint>
#include <format>
#include <optional>
#include <string>

using namespace RS;

void test_rs_core_mp_integer_unsigned_construction_from_list() {

    Natural x;

    TEST_EQUAL(x.str(16), "0");
    TRY(x = 1ull);
    TEST_EQUAL(x.str(16), "1");
    TRY(x = 0xab'cdef0ull);
    TEST_EQUAL(x.str(16), "abcdef0");
    TRY(x = 0x1234'5678ull);
    TEST_EQUAL(x.str(16), "12345678");
    TRY(x = 0x1234'5678'9abc'def0ull);
    TEST_EQUAL(x.str(16), "123456789abcdef0");
    TRY((x = {0xfedc'babc'defe'dcbaull, 0x9876'5432'1234'5678ull}));
    TEST_EQUAL(x.str(16), "fedcbabcdefedcba9876543212345678");
    TRY((x = {0xfedc'babc'defe'dcbaull, 0x9876'5432'1234'5678ull, 0x1f2e'3d4c'5b6a'7891ull}));
    TEST_EQUAL(x.str(16), "fedcbabcdefedcba98765432123456781f2e3d4c5b6a7891");
    TRY((x = {0xfedc'babc'defe'dcbaull, 0x9876'5432'1234'5678ull, 0x1f2e'3d4c'5b6a'7891ull, 0x0fed'cba9'8765'4321ull}));
    TEST_EQUAL(x.str(16), "fedcbabcdefedcba98765432123456781f2e3d4c5b6a78910fedcba987654321");

}

void test_rs_core_mp_integer_unsigned_conversion_from_integer() {

    Natural x;
    std::string s;
    std::optional<std::int16_t> i;
    std::optional<std::uint16_t> u;
    std::optional<std::int32_t> j;
    std::optional<std::uint32_t> v;

    TEST_EQUAL(static_cast<std::uint64_t>(x), 0u);

    TRY(x = 0x1234'5678ul);
    TEST_EQUAL(x.bits(), 29u);
    TEST_EQUAL(static_cast<std::uint64_t>(x), 0x1234'5678ul);

    TRY(x = 0x1234'5678'9abc'def0ull);
    TEST_EQUAL(x.bits(), 61u);
    TEST_EQUAL(static_cast<std::uint64_t>(x), 0x1234'5678'9abc'def0ull);

    TRY(x = 32'767ul);
    TEST(x.in_range<std::int16_t>());   TRY(i = x.checked_cast<std::int16_t>());   TEST(i); TEST_EQUAL(*i, 32'767l);
    TEST(x.in_range<std::uint16_t>());  TRY(u = x.checked_cast<std::uint16_t>());  TEST(u); TEST_EQUAL(*u, 32'767ul);
    TEST(x.in_range<std::int32_t>());   TRY(j = x.checked_cast<std::int32_t>());   TEST(j); TEST_EQUAL(*j, 32'767l);
    TEST(x.in_range<std::uint32_t>());  TRY(v = x.checked_cast<std::uint32_t>());  TEST(v); TEST_EQUAL(*v, 32'767ul);

    TRY(x = 32'768ul);
    TEST(! x.in_range<std::int16_t>());  TRY(i = x.checked_cast<std::int16_t>());   TEST(! i);
    TEST(x.in_range<std::uint16_t>());   TRY(u = x.checked_cast<std::uint16_t>());  TEST(u); TEST_EQUAL(*u, 32'768ul);
    TEST(x.in_range<std::int32_t>());    TRY(j = x.checked_cast<std::int32_t>());   TEST(j); TEST_EQUAL(*j, 32'768l);
    TEST(x.in_range<std::uint32_t>());   TRY(v = x.checked_cast<std::uint32_t>());  TEST(v); TEST_EQUAL(*v, 32'768ul);

    TRY(x = 65'535ul);
    TEST(! x.in_range<std::int16_t>());  TRY(i = x.checked_cast<std::int16_t>());   TEST(! i);
    TEST(x.in_range<std::uint16_t>());   TRY(u = x.checked_cast<std::uint16_t>());  TEST(u); TEST_EQUAL(*u, 65'535ul);
    TEST(x.in_range<std::int32_t>());    TRY(j = x.checked_cast<std::int32_t>());   TEST(j); TEST_EQUAL(*j, 65'535l);
    TEST(x.in_range<std::uint32_t>());   TRY(v = x.checked_cast<std::uint32_t>());  TEST(v); TEST_EQUAL(*v, 65'535ul);

    TRY(x = 65'536ul);
    TEST(! x.in_range<std::int16_t>());   TRY(i = x.checked_cast<std::int16_t>());   TEST(! i);
    TEST(! x.in_range<std::uint16_t>());  TRY(u = x.checked_cast<std::uint16_t>());  TEST(! u);
    TEST(x.in_range<std::int32_t>());     TRY(j = x.checked_cast<std::int32_t>());   TEST(j); TEST_EQUAL(*j, 65'536l);
    TEST(x.in_range<std::uint32_t>());    TRY(v = x.checked_cast<std::uint32_t>());  TEST(v); TEST_EQUAL(*v, 65'536ul);

}

void test_rs_core_mp_integer_unsigned_conversion_to_string() {

    Natural x;
    std::string s;

    TRY(s = x.str());                   TEST_EQUAL(s, "0");
    TRY(s = x.str(10, 15));             TEST_EQUAL(s, "000000000000000");
    TRY(s = x.str(2));                  TEST_EQUAL(s, "0");
    TRY(s = x.str(16));                 TEST_EQUAL(s, "0");
    TRY(s = std::format("{0}", x));     TEST_EQUAL(s, "0");
    TRY(s = std::format("{0:15}", x));  TEST_EQUAL(s, "000000000000000");
    TRY(s = std::format("{0:b}", x));   TEST_EQUAL(s, "0");
    TRY(s = std::format("{0:x}", x));   TEST_EQUAL(s, "0");

    TRY(x = 42u);

    TRY(s = x.str());                   TEST_EQUAL(s, "42");
    TRY(s = x.str(10, 15));             TEST_EQUAL(s, "000000000000042");
    TRY(s = x.str(2));                  TEST_EQUAL(s, "101010");
    TRY(s = x.str(16));                 TEST_EQUAL(s, "2a");
    TRY(s = std::format("{0}", x));     TEST_EQUAL(s, "42");
    TRY(s = std::format("{0:15}", x));  TEST_EQUAL(s, "000000000000042");
    TRY(s = std::format("{0:b}", x));   TEST_EQUAL(s, "101010");
    TRY(s = std::format("{0:x}", x));   TEST_EQUAL(s, "2a");

    TRY(x = 0x1234'5678ul);

    TRY(s = x.str());                   TEST_EQUAL(s, "305419896");
    TRY(s = x.str(10, 15));             TEST_EQUAL(s, "000000305419896");
    TRY(s = x.str(2));                  TEST_EQUAL(s, "10010001101000101011001111000");
    TRY(s = x.str(16));                 TEST_EQUAL(s, "12345678");
    TRY(s = std::format("{0}", x));     TEST_EQUAL(s, "305419896");
    TRY(s = std::format("{0:15}", x));  TEST_EQUAL(s, "000000305419896");
    TRY(s = std::format("{0:b}", x));   TEST_EQUAL(s, "10010001101000101011001111000");
    TRY(s = std::format("{0:x}", x));   TEST_EQUAL(s, "12345678");

    TRY(x = 0x1234'5678'9abc'def0ull);

    TRY(s = x.str());                   TEST_EQUAL(s, "1311768467463790320");
    TRY(s = x.str(10, 15));             TEST_EQUAL(s, "1311768467463790320");
    TRY(s = x.str(2));                  TEST_EQUAL(s, "1001000110100010101100111100010011010101111001101111011110000");
    TRY(s = x.str(16));                 TEST_EQUAL(s, "123456789abcdef0");
    TRY(s = std::format("{0}", x));     TEST_EQUAL(s, "1311768467463790320");
    TRY(s = std::format("{0:15}", x));  TEST_EQUAL(s, "1311768467463790320");
    TRY(s = std::format("{0:b}", x));   TEST_EQUAL(s, "1001000110100010101100111100010011010101111001101111011110000");
    TRY(s = std::format("{0:x}", x));   TEST_EQUAL(s, "123456789abcdef0");

    TRY(x = Natural("110011000011110111111011111001011100011101100011001111101111100000001000101111100010101", 2));

    TRY(s = x.str());                   TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = x.str(10, 15));             TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = x.str(2));                  TEST_EQUAL(s, "110011000011110111111011111001011100011101100011001111101111100000001000101111100010101");
    TRY(s = x.str(16));                 TEST_EQUAL(s, "661efdf2e3b19f7c045f15");
    TRY(s = std::format("{0}", x));     TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = std::format("{0:15}", x));  TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = std::format("{0:b}", x));   TEST_EQUAL(s, "110011000011110111111011111001011100011101100011001111101111100000001000101111100010101");
    TRY(s = std::format("{0:x}", x));   TEST_EQUAL(s, "661efdf2e3b19f7c045f15");

    TRY(x = Natural("123456789123456789123456789", 10));

    TRY(s = x.str());                   TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = x.str(10, 15));             TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = x.str(2));                  TEST_EQUAL(s, "110011000011110111111011111001011100011101100011001111101111100000001000101111100010101");
    TRY(s = x.str(16));                 TEST_EQUAL(s, "661efdf2e3b19f7c045f15");
    TRY(s = std::format("{0}", x));     TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = std::format("{0:15}", x));  TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = std::format("{0:b}", x));   TEST_EQUAL(s, "110011000011110111111011111001011100011101100011001111101111100000001000101111100010101");
    TRY(s = std::format("{0:x}", x));   TEST_EQUAL(s, "661efdf2e3b19f7c045f15");

    TRY(x = Natural("661efdf2e3b19f7c045f15", 16));

    TRY(s = x.str());                   TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = x.str(10, 15));             TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = x.str(2));                  TEST_EQUAL(s, "110011000011110111111011111001011100011101100011001111101111100000001000101111100010101");
    TRY(s = x.str(16));                 TEST_EQUAL(s, "661efdf2e3b19f7c045f15");
    TRY(s = std::format("{0}", x));     TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = std::format("{0:15}", x));  TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = std::format("{0:b}", x));   TEST_EQUAL(s, "110011000011110111111011111001011100011101100011001111101111100000001000101111100010101");
    TRY(s = std::format("{0:x}", x));   TEST_EQUAL(s, "661efdf2e3b19f7c045f15");

    TRY(x = Natural("123456789123456789123456789", 0));

    TRY(s = x.str());                   TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = x.str(10, 15));             TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = x.str(2));                  TEST_EQUAL(s, "110011000011110111111011111001011100011101100011001111101111100000001000101111100010101");
    TRY(s = x.str(16));                 TEST_EQUAL(s, "661efdf2e3b19f7c045f15");
    TRY(s = std::format("{0}", x));     TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = std::format("{0:15}", x));  TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = std::format("{0:b}", x));   TEST_EQUAL(s, "110011000011110111111011111001011100011101100011001111101111100000001000101111100010101");
    TRY(s = std::format("{0:x}", x));   TEST_EQUAL(s, "661efdf2e3b19f7c045f15");

    TRY(x = Natural("0x661efdf2e3b19f7c045f15", 0));

    TRY(s = x.str());                   TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = x.str(10, 15));             TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = x.str(2));                  TEST_EQUAL(s, "110011000011110111111011111001011100011101100011001111101111100000001000101111100010101");
    TRY(s = x.str(16));                 TEST_EQUAL(s, "661efdf2e3b19f7c045f15");
    TRY(s = std::format("{0}", x));     TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = std::format("{0:15}", x));  TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = std::format("{0:b}", x));   TEST_EQUAL(s, "110011000011110111111011111001011100011101100011001111101111100000001000101111100010101");
    TRY(s = std::format("{0:x}", x));   TEST_EQUAL(s, "661efdf2e3b19f7c045f15");

    TRY(x = Natural("123'456'789'123'456'789'123'456'789", 10));

    TRY(s = x.str());                   TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = x.str(10, 15));             TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = x.str(2));                  TEST_EQUAL(s, "110011000011110111111011111001011100011101100011001111101111100000001000101111100010101");
    TRY(s = x.str(16));                 TEST_EQUAL(s, "661efdf2e3b19f7c045f15");
    TRY(s = std::format("{0}", x));     TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = std::format("{0:15}", x));  TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = std::format("{0:b}", x));   TEST_EQUAL(s, "110011000011110111111011111001011100011101100011001111101111100000001000101111100010101");
    TRY(s = std::format("{0:x}", x));   TEST_EQUAL(s, "661efdf2e3b19f7c045f15");

    TRY(x = Natural("123_456_789_123_456_789_123_456_789", 10));

    TRY(s = x.str());                   TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = x.str(10, 15));             TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = x.str(2));                  TEST_EQUAL(s, "110011000011110111111011111001011100011101100011001111101111100000001000101111100010101");
    TRY(s = x.str(16));                 TEST_EQUAL(s, "661efdf2e3b19f7c045f15");
    TRY(s = std::format("{0}", x));     TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = std::format("{0:15}", x));  TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = std::format("{0:b}", x));   TEST_EQUAL(s, "110011000011110111111011111001011100011101100011001111101111100000001000101111100010101");
    TRY(s = std::format("{0:x}", x));   TEST_EQUAL(s, "661efdf2e3b19f7c045f15");

    TRY(x = Natural("0x66'1efd'f2e3'b19f'7c04'5f15", 0));

    TRY(s = x.str());                   TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = x.str(10, 15));             TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = x.str(2));                  TEST_EQUAL(s, "110011000011110111111011111001011100011101100011001111101111100000001000101111100010101");
    TRY(s = x.str(16));                 TEST_EQUAL(s, "661efdf2e3b19f7c045f15");
    TRY(s = std::format("{0}", x));     TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = std::format("{0:15}", x));  TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = std::format("{0:b}", x));   TEST_EQUAL(s, "110011000011110111111011111001011100011101100011001111101111100000001000101111100010101");
    TRY(s = std::format("{0:x}", x));   TEST_EQUAL(s, "661efdf2e3b19f7c045f15");

    TRY(x = Natural("0x66_1efd_f2e3_b19f_7c04_5f15", 0));

    TRY(s = x.str());                   TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = x.str(10, 15));             TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = x.str(2));                  TEST_EQUAL(s, "110011000011110111111011111001011100011101100011001111101111100000001000101111100010101");
    TRY(s = x.str(16));                 TEST_EQUAL(s, "661efdf2e3b19f7c045f15");
    TRY(s = std::format("{0}", x));     TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = std::format("{0:15}", x));  TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = std::format("{0:b}", x));   TEST_EQUAL(s, "110011000011110111111011111001011100011101100011001111101111100000001000101111100010101");
    TRY(s = std::format("{0:x}", x));   TEST_EQUAL(s, "661efdf2e3b19f7c045f15");

}

void test_rs_core_mp_integer_unsigned_conversion_from_string() {

    Natural x;
    std::optional<Natural> y;

    TRY(y = Natural::parse("0",                                           2));   TEST(y);  TEST_EQUAL(y.value().str(), "0");
    TRY(y = Natural::parse("101010",                                      2));   TEST(y);  TEST_EQUAL(y.value().str(), "42");
    TRY(y = Natural::parse("1011011111110111000001110000110100",          2));   TEST(y);  TEST_EQUAL(y.value().str(), "12345678900");
    TRY(y = Natural::parse("10'1010",                                     2));   TEST(y);  TEST_EQUAL(y.value().str(), "42");
    TRY(y = Natural::parse("10'1101'1111'1101'1100'0001'1100'0011'0100",  2));   TEST(y);  TEST_EQUAL(y.value().str(), "12345678900");
    TRY(y = Natural::parse("10_1010",                                     2));   TEST(y);  TEST_EQUAL(y.value().str(), "42");
    TRY(y = Natural::parse("10_1101_1111_1101_1100_0001_1100_0011_0100",  2));   TEST(y);  TEST_EQUAL(y.value().str(), "12345678900");
    TRY(y = Natural::parse("0",                                           10));  TEST(y);  TEST_EQUAL(y.value().str(), "0");
    TRY(y = Natural::parse("42",                                          10));  TEST(y);  TEST_EQUAL(y.value().str(), "42");
    TRY(y = Natural::parse("123456789",                                   10));  TEST(y);  TEST_EQUAL(y.value().str(), "123456789");
    TRY(y = Natural::parse("123456789123456789",                          10));  TEST(y);  TEST_EQUAL(y.value().str(), "123456789123456789");
    TRY(y = Natural::parse("123456789123456789123456789",                 10));  TEST(y);  TEST_EQUAL(y.value().str(), "123456789123456789123456789");
    TRY(y = Natural::parse("123456789123456789123456789123456789",        10));  TEST(y);  TEST_EQUAL(y.value().str(), "123456789123456789123456789123456789");
    TRY(y = Natural::parse("123_456_789",                                 10));  TEST(y);  TEST_EQUAL(y.value().str(), "123456789");
    TRY(y = Natural::parse("123_456_789_123_456_789",                     10));  TEST(y);  TEST_EQUAL(y.value().str(), "123456789123456789");
    TRY(y = Natural::parse("123_456_789_123_456_789_123_456_789",         10));  TEST(y);  TEST_EQUAL(y.value().str(), "123456789123456789123456789");
    TRY(y = Natural::parse("123'456'789",                                 10));  TEST(y);  TEST_EQUAL(y.value().str(), "123456789");
    TRY(y = Natural::parse("123'456'789'123'456'789",                     10));  TEST(y);  TEST_EQUAL(y.value().str(), "123456789123456789");
    TRY(y = Natural::parse("123'456'789'123'456'789'123'456'789",         10));  TEST(y);  TEST_EQUAL(y.value().str(), "123456789123456789123456789");
    TRY(y = Natural::parse("0",                                           16));  TEST(y);  TEST_EQUAL(y.value().str(), "0");
    TRY(y = Natural::parse("abcdef",                                      16));  TEST(y);  TEST_EQUAL(y.value().str(), "11259375");
    TRY(y = Natural::parse("abcdef123456789abcdef",                       16));  TEST(y);  TEST_EQUAL(y.value().str(), "12981175647918246886886895");
    TRY(y = Natural::parse("ab'cdef",                                     16));  TEST(y);  TEST_EQUAL(y.value().str(), "11259375");
    TRY(y = Natural::parse("a'bcde'f123'4567'89ab'cdef",                  16));  TEST(y);  TEST_EQUAL(y.value().str(), "12981175647918246886886895");
    TRY(y = Natural::parse("ab_cdef",                                     16));  TEST(y);  TEST_EQUAL(y.value().str(), "11259375");
    TRY(y = Natural::parse("a_bcde_f123_4567_89ab_cdef",                  16));  TEST(y);  TEST_EQUAL(y.value().str(), "12981175647918246886886895");
    TRY(y = Natural::parse("0",                                           0));   TEST(y);  TEST_EQUAL(y.value().str(), "0");
    TRY(y = Natural::parse("42",                                          0));   TEST(y);  TEST_EQUAL(y.value().str(), "42");
    TRY(y = Natural::parse("123456789",                                   0));   TEST(y);  TEST_EQUAL(y.value().str(), "123456789");
    TRY(y = Natural::parse("123456789123456789",                          0));   TEST(y);  TEST_EQUAL(y.value().str(), "123456789123456789");
    TRY(y = Natural::parse("123456789123456789123456789",                 0));   TEST(y);  TEST_EQUAL(y.value().str(), "123456789123456789123456789");
    TRY(y = Natural::parse("123456789123456789123456789123456789",        0));   TEST(y);  TEST_EQUAL(y.value().str(), "123456789123456789123456789123456789");
    TRY(y = Natural::parse("0b0",                                         0));   TEST(y);  TEST_EQUAL(y.value().str(), "0");
    TRY(y = Natural::parse("0b101010",                                    0));   TEST(y);  TEST_EQUAL(y.value().str(), "42");
    TRY(y = Natural::parse("0b1011011111110111000001110000110100",        0));   TEST(y);  TEST_EQUAL(y.value().str(), "12345678900");
    TRY(y = Natural::parse("0x0",                                         0));   TEST(y);  TEST_EQUAL(y.value().str(), "0");
    TRY(y = Natural::parse("0xabcdef",                                    0));   TEST(y);  TEST_EQUAL(y.value().str(), "11259375");
    TRY(y = Natural::parse("0xabcdef123456789abcdef",                     0));   TEST(y);  TEST_EQUAL(y.value().str(), "12981175647918246886886895");

    TRY(y = Natural::parse(""));           TEST(! y);
    TRY(y = Natural::parse("", 0));        TEST(! y);
    TRY(y = Natural::parse("abc"));        TEST(! y);
    TRY(y = Natural::parse("abc", 0));     TEST(! y);
    TRY(y = Natural::parse("123abc"));     TEST(! y);
    TRY(y = Natural::parse("123abc", 0));  TEST(! y);

    TRY(x = Natural("0"));                                        TEST_EQUAL(x.str(), "0");
    TRY(x = Natural("42"));                                       TEST_EQUAL(x.str(), "42");
    TRY(x = Natural("123456789"));                                TEST_EQUAL(x.str(), "123456789");
    TRY(x = Natural("123456789123456789"));                       TEST_EQUAL(x.str(), "123456789123456789");
    TRY(x = Natural("123456789123456789123456789"));              TEST_EQUAL(x.str(), "123456789123456789123456789");
    TRY(x = Natural("123456789123456789123456789123456789"));     TEST_EQUAL(x.str(), "123456789123456789123456789123456789");
    TRY(x = Natural("0", 2));                                     TEST_EQUAL(x.str(), "0");
    TRY(x = Natural("101010", 2));                                TEST_EQUAL(x.str(), "42");
    TRY(x = Natural("1011011111110111000001110000110100", 2));    TEST_EQUAL(x.str(), "12345678900");
    TRY(x = Natural("0", 16));                                    TEST_EQUAL(x.str(), "0");
    TRY(x = Natural("abcdef", 16));                               TEST_EQUAL(x.str(), "11259375");
    TRY(x = Natural("abcdef123456789abcdef", 16));                TEST_EQUAL(x.str(), "12981175647918246886886895");
    TRY(x = Natural("0", 0));                                     TEST_EQUAL(x.str(), "0");
    TRY(x = Natural("42", 0));                                    TEST_EQUAL(x.str(), "42");
    TRY(x = Natural("123456789", 0));                             TEST_EQUAL(x.str(), "123456789");
    TRY(x = Natural("123456789123456789", 0));                    TEST_EQUAL(x.str(), "123456789123456789");
    TRY(x = Natural("123456789123456789123456789", 0));           TEST_EQUAL(x.str(), "123456789123456789123456789");
    TRY(x = Natural("123456789123456789123456789123456789", 0));  TEST_EQUAL(x.str(), "123456789123456789123456789123456789");
    TRY(x = Natural("0b0", 0));                                   TEST_EQUAL(x.str(), "0");
    TRY(x = Natural("0b101010", 0));                              TEST_EQUAL(x.str(), "42");
    TRY(x = Natural("0b1011011111110111000001110000110100", 0));  TEST_EQUAL(x.str(), "12345678900");
    TRY(x = Natural("0x0", 0));                                   TEST_EQUAL(x.str(), "0");
    TRY(x = Natural("0xabcdef", 0));                              TEST_EQUAL(x.str(), "11259375");
    TRY(x = Natural("0xabcdef123456789abcdef", 0));               TEST_EQUAL(x.str(), "12981175647918246886886895");

}
