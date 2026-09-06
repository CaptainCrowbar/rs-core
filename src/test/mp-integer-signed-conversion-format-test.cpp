#include "rs-core/mp-integer.hpp"
#include "rs-core/unit-test.hpp"
#include <format>
#include <string>

using namespace RS;

void test_rs_core_mp_integer_signed_format() {

    Integer a;
    Integer b {42};
    Integer c {123'456'789l};
    Integer d {-123'456'789l};
    Integer e {123'456'789'123'456'789ll};
    Integer f {-123'456'789'123'456'789ll};
    Integer g {"123456789123456789123456789123456789123456789", 10};
    Integer h {"-123456789123456789123456789123456789123456789", 10};
    Integer i {"123456789abcdef123456789abcdef123456789abcdef123456789abcdef", 16};
    Integer j {"-123456789abcdef123456789abcdef123456789abcdef123456789abcdef", 16};
    std::string s;

    TRY(s = std::format("{}", a));        TEST_EQUAL(s, "0");
    TRY(s = std::format("{:+}", a));      TEST_EQUAL(s, "+0");
    TRY(s = std::format("{:05d}", a));    TEST_EQUAL(s, "00000");
    TRY(s = std::format("{:+05d}", a));   TEST_EQUAL(s, "+00000");
    TRY(s = std::format("{:x}", a));      TEST_EQUAL(s, "0");
    TRY(s = std::format("{:+x}", a));     TEST_EQUAL(s, "+0");
    TRY(s = std::format("{:05x}", a));    TEST_EQUAL(s, "00000");
    TRY(s = std::format("{:+05x}", a));   TEST_EQUAL(s, "+00000");
    TRY(s = std::format("{}", b));        TEST_EQUAL(s, "42");
    TRY(s = std::format("{:+}", b));      TEST_EQUAL(s, "+42");
    TRY(s = std::format("{:05d}", b));    TEST_EQUAL(s, "00042");
    TRY(s = std::format("{:+05d}", b));   TEST_EQUAL(s, "+00042");
    TRY(s = std::format("{:x}", b));      TEST_EQUAL(s, "2a");
    TRY(s = std::format("{:+x}", b));     TEST_EQUAL(s, "+2a");
    TRY(s = std::format("{:05x}", b));    TEST_EQUAL(s, "0002a");
    TRY(s = std::format("{:+05x}", b));   TEST_EQUAL(s, "+0002a");
    TRY(s = std::format("{}", c));        TEST_EQUAL(s, "123456789");
    TRY(s = std::format("{:+}", c));      TEST_EQUAL(s, "+123456789");
    TRY(s = std::format("{:020d}", c));   TEST_EQUAL(s, "00000000000123456789");
    TRY(s = std::format("{:+020d}", c));  TEST_EQUAL(s, "+00000000000123456789");
    TRY(s = std::format("{:x}", c));      TEST_EQUAL(s, "75bcd15");
    TRY(s = std::format("{:+x}", c));     TEST_EQUAL(s, "+75bcd15");
    TRY(s = std::format("{:020x}", c));   TEST_EQUAL(s, "000000000000075bcd15");
    TRY(s = std::format("{:+020x}", c));  TEST_EQUAL(s, "+000000000000075bcd15");
    TRY(s = std::format("{}", d));        TEST_EQUAL(s, "-123456789");
    TRY(s = std::format("{:+}", d));      TEST_EQUAL(s, "-123456789");
    TRY(s = std::format("{:020d}", d));   TEST_EQUAL(s, "-00000000000123456789");
    TRY(s = std::format("{:+020d}", d));  TEST_EQUAL(s, "-00000000000123456789");
    TRY(s = std::format("{:x}", d));      TEST_EQUAL(s, "-75bcd15");
    TRY(s = std::format("{:+x}", d));     TEST_EQUAL(s, "-75bcd15");
    TRY(s = std::format("{:020x}", d));   TEST_EQUAL(s, "-000000000000075bcd15");
    TRY(s = std::format("{:+020x}", d));  TEST_EQUAL(s, "-000000000000075bcd15");
    TRY(s = std::format("{}", e));        TEST_EQUAL(s, "123456789123456789");
    TRY(s = std::format("{:+}", e));      TEST_EQUAL(s, "+123456789123456789");
    TRY(s = std::format("{:020d}", e));   TEST_EQUAL(s, "00123456789123456789");
    TRY(s = std::format("{:+020d}", e));  TEST_EQUAL(s, "+00123456789123456789");
    TRY(s = std::format("{:x}", e));      TEST_EQUAL(s, "1b69b4bacd05f15");
    TRY(s = std::format("{:+x}", e));     TEST_EQUAL(s, "+1b69b4bacd05f15");
    TRY(s = std::format("{:020x}", e));   TEST_EQUAL(s, "000001b69b4bacd05f15");
    TRY(s = std::format("{:+020x}", e));  TEST_EQUAL(s, "+000001b69b4bacd05f15");
    TRY(s = std::format("{}", f));        TEST_EQUAL(s, "-123456789123456789");
    TRY(s = std::format("{:+}", f));      TEST_EQUAL(s, "-123456789123456789");
    TRY(s = std::format("{:020d}", f));   TEST_EQUAL(s, "-00123456789123456789");
    TRY(s = std::format("{:+020d}", f));  TEST_EQUAL(s, "-00123456789123456789");
    TRY(s = std::format("{:x}", f));      TEST_EQUAL(s, "-1b69b4bacd05f15");
    TRY(s = std::format("{:+x}", f));     TEST_EQUAL(s, "-1b69b4bacd05f15");
    TRY(s = std::format("{:020x}", f));   TEST_EQUAL(s, "-000001b69b4bacd05f15");
    TRY(s = std::format("{:+020x}", f));  TEST_EQUAL(s, "-000001b69b4bacd05f15");
    TRY(s = std::format("{}", g));        TEST_EQUAL(s, "123456789123456789123456789123456789123456789");
    TRY(s = std::format("{:+}", g));      TEST_EQUAL(s, "+123456789123456789123456789123456789123456789");
    TRY(s = std::format("{:050d}", g));   TEST_EQUAL(s, "00000123456789123456789123456789123456789123456789");
    TRY(s = std::format("{:+050d}", g));  TEST_EQUAL(s, "+00000123456789123456789123456789123456789123456789");
    TRY(s = std::format("{:x}", g));      TEST_EQUAL(s, "58936e53d139afefabb2683f150b684045f15");
    TRY(s = std::format("{:+x}", g));     TEST_EQUAL(s, "+58936e53d139afefabb2683f150b684045f15");
    TRY(s = std::format("{:050x}", g));   TEST_EQUAL(s, "000000000000058936e53d139afefabb2683f150b684045f15");
    TRY(s = std::format("{:+050x}", g));  TEST_EQUAL(s, "+000000000000058936e53d139afefabb2683f150b684045f15");
    TRY(s = std::format("{}", h));        TEST_EQUAL(s, "-123456789123456789123456789123456789123456789");
    TRY(s = std::format("{:+}", h));      TEST_EQUAL(s, "-123456789123456789123456789123456789123456789");
    TRY(s = std::format("{:050d}", h));   TEST_EQUAL(s, "-00000123456789123456789123456789123456789123456789");
    TRY(s = std::format("{:+050d}", h));  TEST_EQUAL(s, "-00000123456789123456789123456789123456789123456789");
    TRY(s = std::format("{:x}", h));      TEST_EQUAL(s, "-58936e53d139afefabb2683f150b684045f15");
    TRY(s = std::format("{:+x}", h));     TEST_EQUAL(s, "-58936e53d139afefabb2683f150b684045f15");
    TRY(s = std::format("{:050x}", h));   TEST_EQUAL(s, "-000000000000058936e53d139afefabb2683f150b684045f15");
    TRY(s = std::format("{:+050x}", h));  TEST_EQUAL(s, "-000000000000058936e53d139afefabb2683f150b684045f15");
    TRY(s = std::format("{}", i));        TEST_EQUAL(s, "125642457939796217460094503631385345882379387509263401568735420576681455");
    TRY(s = std::format("{:+}", i));      TEST_EQUAL(s, "+125642457939796217460094503631385345882379387509263401568735420576681455");
    TRY(s = std::format("{:080d}", i));   TEST_EQUAL(s, "00000000125642457939796217460094503631385345882379387509263401568735420576681455");
    TRY(s = std::format("{:+080d}", i));  TEST_EQUAL(s, "+00000000125642457939796217460094503631385345882379387509263401568735420576681455");
    TRY(s = std::format("{:x}", i));      TEST_EQUAL(s, "123456789abcdef123456789abcdef123456789abcdef123456789abcdef");
    TRY(s = std::format("{:+x}", i));     TEST_EQUAL(s, "+123456789abcdef123456789abcdef123456789abcdef123456789abcdef");
    TRY(s = std::format("{:080x}", i));   TEST_EQUAL(s, "00000000000000000000123456789abcdef123456789abcdef123456789abcdef123456789abcdef");
    TRY(s = std::format("{:+080x}", i));  TEST_EQUAL(s, "+00000000000000000000123456789abcdef123456789abcdef123456789abcdef123456789abcdef");
    TRY(s = std::format("{}", j));        TEST_EQUAL(s, "-125642457939796217460094503631385345882379387509263401568735420576681455");
    TRY(s = std::format("{:+}", j));      TEST_EQUAL(s, "-125642457939796217460094503631385345882379387509263401568735420576681455");
    TRY(s = std::format("{:080d}", j));   TEST_EQUAL(s, "-00000000125642457939796217460094503631385345882379387509263401568735420576681455");
    TRY(s = std::format("{:+080d}", j));  TEST_EQUAL(s, "-00000000125642457939796217460094503631385345882379387509263401568735420576681455");
    TRY(s = std::format("{:x}", j));      TEST_EQUAL(s, "-123456789abcdef123456789abcdef123456789abcdef123456789abcdef");
    TRY(s = std::format("{:+x}", j));     TEST_EQUAL(s, "-123456789abcdef123456789abcdef123456789abcdef123456789abcdef");
    TRY(s = std::format("{:080x}", j));   TEST_EQUAL(s, "-00000000000000000000123456789abcdef123456789abcdef123456789abcdef123456789abcdef");
    TRY(s = std::format("{:+080x}", j));  TEST_EQUAL(s, "-00000000000000000000123456789abcdef123456789abcdef123456789abcdef123456789abcdef");

}
