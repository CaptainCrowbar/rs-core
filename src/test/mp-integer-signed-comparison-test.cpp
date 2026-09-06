#include "rs-core/mp-integer.hpp"
#include "rs-core/unit-test.hpp"
#include <compare>

using namespace RS;

void test_rs_core_mp_integer_signed_comparison() {

    TEST(Integer{0} == Integer{0});      TEST(Integer{0} <= Integer{0});      TEST(Integer{0} >= Integer{0});
    TEST(Integer{42} == Integer{42});    TEST(Integer{42} <= Integer{42});    TEST(Integer{42} >= Integer{42});
    TEST(Integer{86} != Integer{99});    TEST(Integer{86} < Integer{99});     TEST(Integer{86} <= Integer{99});
    TEST(Integer{99} != Integer{86});    TEST(Integer{99} > Integer{86});     TEST(Integer{99} >= Integer{86});
    TEST(Integer{-42} == Integer{-42});  TEST(Integer{-42} <= Integer{-42});  TEST(Integer{-42} >= Integer{-42});
    TEST(Integer{-86} != Integer{-99});  TEST(Integer{-86} > Integer{-99});   TEST(Integer{-86} >= Integer{-99});
    TEST(Integer{-99} != Integer{-86});  TEST(Integer{-99} < Integer{-86});   TEST(Integer{-99} <= Integer{-86});
    TEST(Integer{0} != Integer{42});     TEST(Integer{0} < Integer{42});      TEST(Integer{0} <= Integer{42});
    TEST(Integer{0} != Integer{-42});    TEST(Integer{0} > Integer{-42});     TEST(Integer{0} >= Integer{-42});
    TEST(Integer{42} != Integer{0});     TEST(Integer{42} > Integer{0});      TEST(Integer{42} >= Integer{0});
    TEST(Integer{-42} != Integer{0});    TEST(Integer{-42} < Integer{0});     TEST(Integer{-42} <= Integer{0});
    TEST(Integer{-42} != Integer{42});   TEST(Integer{-42} < Integer{42});    TEST(Integer{-42} <= Integer{42});
    TEST(Integer{42} != Integer{-42});   TEST(Integer{42} > Integer{-42});    TEST(Integer{42} >= Integer{-42});
    TEST(Integer{0} == 0);               TEST(Integer{0} <= 0);               TEST(Integer{0} >= 0);
    TEST(Integer{42} == 42);             TEST(Integer{42} <= 42);             TEST(Integer{42} >= 42);
    TEST(Integer{86} != 99);             TEST(Integer{86} < 99);              TEST(Integer{86} <= 99);
    TEST(Integer{99} != 86);             TEST(Integer{99} > 86);              TEST(Integer{99} >= 86);
    TEST(Integer{-42} == -42);           TEST(Integer{-42} <= -42);           TEST(Integer{-42} >= -42);
    TEST(Integer{-86} != -99);           TEST(Integer{-86} > -99);            TEST(Integer{-86} >= -99);
    TEST(Integer{-99} != -86);           TEST(Integer{-99} < -86);            TEST(Integer{-99} <= -86);
    TEST(Integer{0} != 42);              TEST(Integer{0} < 42);               TEST(Integer{0} <= 42);
    TEST(Integer{0} != -42);             TEST(Integer{0} > -42);              TEST(Integer{0} >= -42);
    TEST(Integer{42} != 0);              TEST(Integer{42} > 0);               TEST(Integer{42} >= 0);
    TEST(Integer{-42} != 0);             TEST(Integer{-42} < 0);              TEST(Integer{-42} <= 0);
    TEST(Integer{-42} != 42);            TEST(Integer{-42} < 42);             TEST(Integer{-42} <= 42);
    TEST(Integer{42} != -42);            TEST(Integer{42} > -42);             TEST(Integer{42} >= -42);
    TEST(0 == Integer{0});               TEST(0 <= Integer{0});               TEST(0 >= Integer{0});
    TEST(42 == Integer{42});             TEST(42 <= Integer{42});             TEST(42 >= Integer{42});
    TEST(86 != Integer{99});             TEST(86 < Integer{99});              TEST(86 <= Integer{99});
    TEST(99 != Integer{86});             TEST(99 > Integer{86});              TEST(99 >= Integer{86});
    TEST(-42 == Integer{-42});           TEST(-42 <= Integer{-42});           TEST(-42 >= Integer{-42});
    TEST(-86 != Integer{-99});           TEST(-86 > Integer{-99});            TEST(-86 >= Integer{-99});
    TEST(-99 != Integer{-86});           TEST(-99 < Integer{-86});            TEST(-99 <= Integer{-86});
    TEST(0 != Integer{42});              TEST(0 < Integer{42});               TEST(0 <= Integer{42});
    TEST(0 != Integer{-42});             TEST(0 > Integer{-42});              TEST(0 >= Integer{-42});
    TEST(42 != Integer{0});              TEST(42 > Integer{0});               TEST(42 >= Integer{0});
    TEST(-42 != Integer{0});             TEST(-42 < Integer{0});              TEST(-42 <= Integer{0});
    TEST(-42 != Integer{42});            TEST(-42 < Integer{42});             TEST(-42 <= Integer{42});
    TEST(42 != Integer{-42});            TEST(42 > Integer{-42});             TEST(42 >= Integer{-42});
    TEST(Integer{0} == 0u);              TEST(Integer{0} <= 0u);              TEST(Integer{0} >= 0u);
    TEST(Integer{42} == 42u);            TEST(Integer{42} <= 42u);            TEST(Integer{42} >= 42u);
    TEST(Integer{86} != 99u);            TEST(Integer{86} < 99u);             TEST(Integer{86} <= 99u);
    TEST(Integer{99} != 86u);            TEST(Integer{99} > 86u);             TEST(Integer{99} >= 86u);
    TEST(Integer{0} != 42u);             TEST(Integer{0} < 42u);              TEST(Integer{0} <= 42u);
    TEST(Integer{42} != 0u);             TEST(Integer{42} > 0u);              TEST(Integer{42} >= 0u);
    TEST(0u == Integer{0});              TEST(0u <= Integer{0});              TEST(0u >= Integer{0});
    TEST(42u == Integer{42});            TEST(42u <= Integer{42});            TEST(42u >= Integer{42});
    TEST(86u != Integer{99});            TEST(86u < Integer{99});             TEST(86u <= Integer{99});
    TEST(99u != Integer{86});            TEST(99u > Integer{86});             TEST(99u >= Integer{86});
    TEST(0u != Integer{42});             TEST(0u < Integer{42});              TEST(0u <= Integer{42});
    TEST(42u != Integer{0});             TEST(42u > Integer{0});              TEST(42u >= Integer{0});

    TEST((Integer{0} <=> Integer{0})      == std::strong_ordering::equal);
    TEST((Integer{42} <=> Integer{42})    == std::strong_ordering::equal);
    TEST((Integer{86} <=> Integer{99})    == std::strong_ordering::less);
    TEST((Integer{99} <=> Integer{86})    == std::strong_ordering::greater);
    TEST((Integer{-42} <=> Integer{-42})  == std::strong_ordering::equal);
    TEST((Integer{-86} <=> Integer{-99})  == std::strong_ordering::greater);
    TEST((Integer{-99} <=> Integer{-86})  == std::strong_ordering::less);
    TEST((Integer{0} <=> Integer{42})     == std::strong_ordering::less);
    TEST((Integer{0} <=> Integer{-42})    == std::strong_ordering::greater);
    TEST((Integer{42} <=> Integer{0})     == std::strong_ordering::greater);
    TEST((Integer{-42} <=> Integer{0})    == std::strong_ordering::less);
    TEST((Integer{-42} <=> Integer{42})   == std::strong_ordering::less);
    TEST((Integer{42} <=> Integer{-42})   == std::strong_ordering::greater);
    TEST((Integer{0} <=> 0)               == std::strong_ordering::equal);
    TEST((Integer{42} <=> 42)             == std::strong_ordering::equal);
    TEST((Integer{86} <=> 99)             == std::strong_ordering::less);
    TEST((Integer{99} <=> 86)             == std::strong_ordering::greater);
    TEST((Integer{-42} <=> -42)           == std::strong_ordering::equal);
    TEST((Integer{-86} <=> -99)           == std::strong_ordering::greater);
    TEST((Integer{-99} <=> -86)           == std::strong_ordering::less);
    TEST((Integer{0} <=> 42)              == std::strong_ordering::less);
    TEST((Integer{0} <=> -42)             == std::strong_ordering::greater);
    TEST((Integer{42} <=> 0)              == std::strong_ordering::greater);
    TEST((Integer{-42} <=> 0)             == std::strong_ordering::less);
    TEST((Integer{-42} <=> 42)            == std::strong_ordering::less);
    TEST((Integer{42} <=> -42)            == std::strong_ordering::greater);
    TEST((0 <=> Integer{0})               == std::strong_ordering::equal);
    TEST((42 <=> Integer{42})             == std::strong_ordering::equal);
    TEST((86 <=> Integer{99})             == std::strong_ordering::less);
    TEST((99 <=> Integer{86})             == std::strong_ordering::greater);
    TEST((-42 <=> Integer{-42})           == std::strong_ordering::equal);
    TEST((-86 <=> Integer{-99})           == std::strong_ordering::greater);
    TEST((-99 <=> Integer{-86})           == std::strong_ordering::less);
    TEST((0 <=> Integer{42})              == std::strong_ordering::less);
    TEST((0 <=> Integer{-42})             == std::strong_ordering::greater);
    TEST((42 <=> Integer{0})              == std::strong_ordering::greater);
    TEST((-42 <=> Integer{0})             == std::strong_ordering::less);
    TEST((-42 <=> Integer{42})            == std::strong_ordering::less);
    TEST((42 <=> Integer{-42})            == std::strong_ordering::greater);
    TEST((Integer{0} <=> 0u)              == std::strong_ordering::equal);
    TEST((Integer{42} <=> 42u)            == std::strong_ordering::equal);
    TEST((Integer{86} <=> 99u)            == std::strong_ordering::less);
    TEST((Integer{99} <=> 86u)            == std::strong_ordering::greater);
    TEST((Integer{0} <=> 42u)             == std::strong_ordering::less);
    TEST((Integer{42} <=> 0u)             == std::strong_ordering::greater);
    TEST((0u <=> Integer{0})              == std::strong_ordering::equal);
    TEST((42u <=> Integer{42})            == std::strong_ordering::equal);
    TEST((86u <=> Integer{99})            == std::strong_ordering::less);
    TEST((99u <=> Integer{86})            == std::strong_ordering::greater);
    TEST((0u <=> Integer{42})             == std::strong_ordering::less);
    TEST((42u <=> Integer{0})             == std::strong_ordering::greater);

}

void test_rs_core_mp_integer_mixed_comparison() {

    TEST(Integer{0} == Natural{0});    TEST(Integer{0} <= Natural{0});    TEST(Integer{0} >= Natural{0});
    TEST(Integer{42} == Natural{42});  TEST(Integer{42} <= Natural{42});  TEST(Integer{42} >= Natural{42});
    TEST(Integer{86} != Natural{99});  TEST(Integer{86} < Natural{99});   TEST(Integer{86} <= Natural{99});
    TEST(Integer{99} != Natural{86});  TEST(Integer{99} > Natural{86});   TEST(Integer{99} >= Natural{86});
    TEST(Integer{0} != Natural{42});   TEST(Integer{0} < Natural{42});    TEST(Integer{0} <= Natural{42});
    TEST(Integer{42} != Natural{0});   TEST(Integer{42} > Natural{0});    TEST(Integer{42} >= Natural{0});
    TEST(Natural{0} == Integer{0});    TEST(Natural{0} <= Integer{0});    TEST(Natural{0} >= Integer{0});
    TEST(Natural{42} == Integer{42});  TEST(Natural{42} <= Integer{42});  TEST(Natural{42} >= Integer{42});
    TEST(Natural{86} != Integer{99});  TEST(Natural{86} < Integer{99});   TEST(Natural{86} <= Integer{99});
    TEST(Natural{99} != Integer{86});  TEST(Natural{99} > Integer{86});   TEST(Natural{99} >= Integer{86});
    TEST(Natural{0} != Integer{42});   TEST(Natural{0} < Integer{42});    TEST(Natural{0} <= Integer{42});
    TEST(Natural{42} != Integer{0});   TEST(Natural{42} > Integer{0});    TEST(Natural{42} >= Integer{0});

    TEST((Integer{0} <=> Natural{0})    == std::strong_ordering::equal);
    TEST((Integer{42} <=> Natural{42})  == std::strong_ordering::equal);
    TEST((Integer{86} <=> Natural{99})  == std::strong_ordering::less);
    TEST((Integer{99} <=> Natural{86})  == std::strong_ordering::greater);
    TEST((Integer{0} <=> Natural{42})   == std::strong_ordering::less);
    TEST((Integer{42} <=> Natural{0})   == std::strong_ordering::greater);
    TEST((Natural{0} <=> Integer{0})    == std::strong_ordering::equal);
    TEST((Natural{42} <=> Integer{42})  == std::strong_ordering::equal);
    TEST((Natural{86} <=> Integer{99})  == std::strong_ordering::less);
    TEST((Natural{99} <=> Integer{86})  == std::strong_ordering::greater);
    TEST((Natural{0} <=> Integer{42})   == std::strong_ordering::less);
    TEST((Natural{42} <=> Integer{0})   == std::strong_ordering::greater);

}
