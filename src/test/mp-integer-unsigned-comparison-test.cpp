#include "rs-core/mp-integer.hpp"
#include "rs-core/unit-test.hpp"
#include <compare>

using namespace RS;

void test_rs_core_mp_integer_unsigned_comparison() {

    TEST(Natural{0} == Natural{0});    TEST(Natural{0} <= Natural{0});    TEST(Natural{0} >= Natural{0});
    TEST(Natural{42} == Natural{42});  TEST(Natural{42} <= Natural{42});  TEST(Natural{42} >= Natural{42});
    TEST(Natural{86} != Natural{99});  TEST(Natural{86} < Natural{99});   TEST(Natural{86} <= Natural{99});
    TEST(Natural{99} != Natural{86});  TEST(Natural{99} > Natural{86});   TEST(Natural{99} >= Natural{86});
    TEST(Natural{0} == 0);             TEST(Natural{0} <= 0);             TEST(Natural{0} >= 0);
    TEST(Natural{42} == 42);           TEST(Natural{42} <= 42);           TEST(Natural{42} >= 42);
    TEST(Natural{86} != 99);           TEST(Natural{86} < 99);            TEST(Natural{86} <= 99);
    TEST(Natural{99} != 86);           TEST(Natural{99} > 86);            TEST(Natural{99} >= 86);
    TEST(Natural{0} != -42);           TEST(Natural{0} > -42);            TEST(Natural{0} >= -42);
    TEST(Natural{0} == 0u);            TEST(Natural{0} <= 0u);            TEST(Natural{0} >= 0u);
    TEST(Natural{42} == 42u);          TEST(Natural{42} <= 42u);          TEST(Natural{42} >= 42u);
    TEST(Natural{86} != 99u);          TEST(Natural{86} < 99u);           TEST(Natural{86} <= 99u);
    TEST(Natural{99} != 86u);          TEST(Natural{99} > 86u);           TEST(Natural{99} >= 86u);
    TEST(0 == Natural{0});             TEST(0 <= Natural{0});             TEST(0 >= Natural{0});
    TEST(42 == Natural{42});           TEST(42 <= Natural{42});           TEST(42 >= Natural{42});
    TEST(86 != Natural{99});           TEST(86 < Natural{99});            TEST(86 <= Natural{99});
    TEST(99 != Natural{86});           TEST(99 > Natural{86});            TEST(99 >= Natural{86});
    TEST(-42 != Natural{0});           TEST(-42 < Natural{0});            TEST(-42 <= Natural{0});
    TEST(0u == Natural{0});            TEST(0u <= Natural{0});            TEST(0u >= Natural{0});
    TEST(42u == Natural{42});          TEST(42u <= Natural{42});          TEST(42u >= Natural{42});
    TEST(86u != Natural{99});          TEST(86u < Natural{99});           TEST(86u <= Natural{99});
    TEST(99u != Natural{86});          TEST(99u > Natural{86});           TEST(99u >= Natural{86});

    TEST((Natural{0} <=> Natural{0})    == std::strong_ordering::equal);
    TEST((Natural{42} <=> Natural{42})  == std::strong_ordering::equal);
    TEST((Natural{86} <=> Natural{99})  == std::strong_ordering::less);
    TEST((Natural{99} <=> Natural{86})  == std::strong_ordering::greater);
    TEST((Natural{0} <=> 0)             == std::strong_ordering::equal);
    TEST((Natural{42} <=> 42)           == std::strong_ordering::equal);
    TEST((Natural{86} <=> 99)           == std::strong_ordering::less);
    TEST((Natural{99} <=> 86)           == std::strong_ordering::greater);
    TEST((Natural{0} <=> -42)           == std::strong_ordering::greater);
    TEST((Natural{0} <=> 0u)            == std::strong_ordering::equal);
    TEST((Natural{42} <=> 42u)          == std::strong_ordering::equal);
    TEST((Natural{86} <=> 99u)          == std::strong_ordering::less);
    TEST((Natural{99} <=> 86u)          == std::strong_ordering::greater);
    TEST((0 <=> Natural{0})             == std::strong_ordering::equal);
    TEST((42 <=> Natural{42})           == std::strong_ordering::equal);
    TEST((86 <=> Natural{99})           == std::strong_ordering::less);
    TEST((99 <=> Natural{86})           == std::strong_ordering::greater);
    TEST((-42 <=> Natural{0})           == std::strong_ordering::less);
    TEST((0u <=> Natural{0})            == std::strong_ordering::equal);
    TEST((42u <=> Natural{42})          == std::strong_ordering::equal);
    TEST((86u <=> Natural{99})          == std::strong_ordering::less);
    TEST((99u <=> Natural{86})          == std::strong_ordering::greater);

}
