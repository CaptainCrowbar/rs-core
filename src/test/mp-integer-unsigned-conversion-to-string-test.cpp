#include "rs-core/mp-integer.hpp"
#include "rs-core/unit-test.hpp"
#include <format>
#include <string>

using namespace RS;

void test_rs_core_mp_integer_unsigned_conversion_to_string() {

    Natural x;
    std::string s;

    TRY(s = x.to_string());        TEST_EQUAL(s, "0");
    TRY(s = x.to_string(10, 15));  TEST_EQUAL(s, "000000000000000");
    TRY(s = x.to_string(2));       TEST_EQUAL(s, "0");
    TRY(s = x.to_string(16));      TEST_EQUAL(s, "0");

    TRY(x = 42u);

    TRY(s = x.to_string());        TEST_EQUAL(s, "42");
    TRY(s = x.to_string(10, 15));  TEST_EQUAL(s, "000000000000042");
    TRY(s = x.to_string(2));       TEST_EQUAL(s, "101010");
    TRY(s = x.to_string(16));      TEST_EQUAL(s, "2a");

    TRY(x = 0x1234'5678ul);

    TRY(s = x.to_string());        TEST_EQUAL(s, "305419896");
    TRY(s = x.to_string(10, 15));  TEST_EQUAL(s, "000000305419896");
    TRY(s = x.to_string(2));       TEST_EQUAL(s, "10010001101000101011001111000");
    TRY(s = x.to_string(16));      TEST_EQUAL(s, "12345678");

    TRY(x = 0x1234'5678'9abc'def0ull);

    TRY(s = x.to_string());        TEST_EQUAL(s, "1311768467463790320");
    TRY(s = x.to_string(10, 15));  TEST_EQUAL(s, "1311768467463790320");
    TRY(s = x.to_string(2));       TEST_EQUAL(s, "1001000110100010101100111100010011010101111001101111011110000");
    TRY(s = x.to_string(16));      TEST_EQUAL(s, "123456789abcdef0");

    TRY(x = Natural("110011000011110111111011111001011100011101100011001111101111100000001000101111100010101", 2));

    TRY(s = x.to_string());        TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = x.to_string(10, 15));  TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = x.to_string(2));       TEST_EQUAL(s, "110011000011110111111011111001011100011101100011001111101111100000001000101111100010101");
    TRY(s = x.to_string(16));      TEST_EQUAL(s, "661efdf2e3b19f7c045f15");

    TRY(x = Natural("123456789123456789123456789", 10));

    TRY(s = x.to_string());        TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = x.to_string(10, 15));  TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = x.to_string(2));       TEST_EQUAL(s, "110011000011110111111011111001011100011101100011001111101111100000001000101111100010101");
    TRY(s = x.to_string(16));      TEST_EQUAL(s, "661efdf2e3b19f7c045f15");

    TRY(x = Natural("661efdf2e3b19f7c045f15", 16));

    TRY(s = x.to_string());        TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = x.to_string(10, 15));  TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = x.to_string(2));       TEST_EQUAL(s, "110011000011110111111011111001011100011101100011001111101111100000001000101111100010101");
    TRY(s = x.to_string(16));      TEST_EQUAL(s, "661efdf2e3b19f7c045f15");

    TRY(x = Natural("123456789123456789123456789", 0));

    TRY(s = x.to_string());        TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = x.to_string(10, 15));  TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = x.to_string(2));       TEST_EQUAL(s, "110011000011110111111011111001011100011101100011001111101111100000001000101111100010101");
    TRY(s = x.to_string(16));      TEST_EQUAL(s, "661efdf2e3b19f7c045f15");

    TRY(x = Natural("0x661efdf2e3b19f7c045f15", 0));

    TRY(s = x.to_string());        TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = x.to_string(10, 15));  TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = x.to_string(2));       TEST_EQUAL(s, "110011000011110111111011111001011100011101100011001111101111100000001000101111100010101");
    TRY(s = x.to_string(16));      TEST_EQUAL(s, "661efdf2e3b19f7c045f15");

    TRY(x = Natural("123'456'789'123'456'789'123'456'789", 10));

    TRY(s = x.to_string());        TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = x.to_string(10, 15));  TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = x.to_string(2));       TEST_EQUAL(s, "110011000011110111111011111001011100011101100011001111101111100000001000101111100010101");
    TRY(s = x.to_string(16));      TEST_EQUAL(s, "661efdf2e3b19f7c045f15");

    TRY(x = Natural("123_456_789_123_456_789_123_456_789", 10));

    TRY(s = x.to_string());        TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = x.to_string(10, 15));  TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = x.to_string(2));       TEST_EQUAL(s, "110011000011110111111011111001011100011101100011001111101111100000001000101111100010101");
    TRY(s = x.to_string(16));      TEST_EQUAL(s, "661efdf2e3b19f7c045f15");

    TRY(x = Natural("0x66'1efd'f2e3'b19f'7c04'5f15", 0));

    TRY(s = x.to_string());        TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = x.to_string(10, 15));  TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = x.to_string(2));       TEST_EQUAL(s, "110011000011110111111011111001011100011101100011001111101111100000001000101111100010101");
    TRY(s = x.to_string(16));      TEST_EQUAL(s, "661efdf2e3b19f7c045f15");

    TRY(x = Natural("0x66_1efd_f2e3_b19f_7c04_5f15", 0));

    TRY(s = x.to_string());        TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = x.to_string(10, 15));  TEST_EQUAL(s, "123456789123456789123456789");
    TRY(s = x.to_string(2));       TEST_EQUAL(s, "110011000011110111111011111001011100011101100011001111101111100000001000101111100010101");
    TRY(s = x.to_string(16));      TEST_EQUAL(s, "661efdf2e3b19f7c045f15");

}

void test_rs_core_mp_integer_unsigned_format() {

    Natural a;
    Natural b {42};
    Natural c {123'456'789l};
    Natural d {123'456'789'123'456'789ll};
    Natural e {"123456789123456789123456789123456789123456789", 10};
    Natural f {"123456789abcdef123456789abcdef123456789abcdef123456789abcdef", 16};
    std::string s;

    TRY(s = std::format("{}", a));       TEST_EQUAL(s, "0");
    TRY(s = std::format("{:05d}", a));   TEST_EQUAL(s, "00000");
    TRY(s = std::format("{:x}", a));     TEST_EQUAL(s, "0");
    TRY(s = std::format("{:05x}", a));   TEST_EQUAL(s, "00000");
    TRY(s = std::format("{}", b));       TEST_EQUAL(s, "42");
    TRY(s = std::format("{:05d}", b));   TEST_EQUAL(s, "00042");
    TRY(s = std::format("{:x}", b));     TEST_EQUAL(s, "2a");
    TRY(s = std::format("{:05x}", b));   TEST_EQUAL(s, "0002a");
    TRY(s = std::format("{}", c));       TEST_EQUAL(s, "123456789");
    TRY(s = std::format("{:020d}", c));  TEST_EQUAL(s, "00000000000123456789");
    TRY(s = std::format("{:x}", c));     TEST_EQUAL(s, "75bcd15");
    TRY(s = std::format("{:020x}", c));  TEST_EQUAL(s, "000000000000075bcd15");
    TRY(s = std::format("{}", d));       TEST_EQUAL(s, "123456789123456789");
    TRY(s = std::format("{:020d}", d));  TEST_EQUAL(s, "00123456789123456789");
    TRY(s = std::format("{:x}", d));     TEST_EQUAL(s, "1b69b4bacd05f15");
    TRY(s = std::format("{:020x}", d));  TEST_EQUAL(s, "000001b69b4bacd05f15");
    TRY(s = std::format("{}", e));       TEST_EQUAL(s, "123456789123456789123456789123456789123456789");
    TRY(s = std::format("{:050d}", e));  TEST_EQUAL(s, "00000123456789123456789123456789123456789123456789");
    TRY(s = std::format("{:x}", e));     TEST_EQUAL(s, "58936e53d139afefabb2683f150b684045f15");
    TRY(s = std::format("{:050x}", e));  TEST_EQUAL(s, "000000000000058936e53d139afefabb2683f150b684045f15");
    TRY(s = std::format("{}", f));       TEST_EQUAL(s, "125642457939796217460094503631385345882379387509263401568735420576681455");
    TRY(s = std::format("{:080d}", f));  TEST_EQUAL(s, "00000000125642457939796217460094503631385345882379387509263401568735420576681455");
    TRY(s = std::format("{:x}", f));     TEST_EQUAL(s, "123456789abcdef123456789abcdef123456789abcdef123456789abcdef");
    TRY(s = std::format("{:080x}", f));  TEST_EQUAL(s, "00000000000000000000123456789abcdef123456789abcdef123456789abcdef123456789abcdef");

}
