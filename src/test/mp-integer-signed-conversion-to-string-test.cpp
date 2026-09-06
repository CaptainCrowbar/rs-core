#include "rs-core/mp-integer.hpp"
#include "rs-core/unit-test.hpp"
#include <string>

using namespace RS;

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

    TRY(x = -123'456'789l);
    TEST_EQUAL(x.sign(), -1);

    TRY(s = x.to_string());        TEST_EQUAL(s, "-123456789");
    TRY(s = x.to_string(10, 15));  TEST_EQUAL(s, "-000000123456789");
    TRY(s = x.to_string(16));      TEST_EQUAL(s, "-75bcd15");

    TRY(x = 123'456'789'123'456'789ll);
    TEST_EQUAL(x.sign(), 1);

    TRY(s = x.to_string());        TEST_EQUAL(s, "123456789123456789");
    TRY(s = x.to_string(10, 15));  TEST_EQUAL(s, "123456789123456789");
    TRY(s = x.to_string(16));      TEST_EQUAL(s, "1b69b4bacd05f15");

    TRY(x = -123'456'789'123'456'789ll);
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
