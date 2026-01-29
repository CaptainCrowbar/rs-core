#include "rs-core/mp-integer.hpp"
#include "rs-core/unit-test.hpp"
#include <compare>
#include <unordered_set>

using namespace RS;

void test_rs_core_mp_integer_concepts() {

    TEST(! SignedIntegral<Natural>);
    TEST(UnsignedIntegral<Natural>);
    TEST(Integral<Natural>);
    TEST(! FloatingPoint<Natural>);
    TEST(! FixedPointArithmetic<Natural>);
    TEST(! RationalArithmetic<Natural>);
    TEST(Arithmetic<Natural>);
    TEST(Mpitype<Natural>);

    TEST(SignedIntegral<Integer>);
    TEST(! UnsignedIntegral<Integer>);
    TEST(Integral<Integer>);
    TEST(! FloatingPoint<Integer>);
    TEST(! FixedPointArithmetic<Integer>);
    TEST(! RationalArithmetic<Integer>);
    TEST(Arithmetic<Integer>);
    TEST(Mpitype<Integer>);

}

void test_rs_core_mp_integer_literals() {

    using namespace RS::Literals;

    Natural n;
    Integer z;

    TRY(n = 0_N);                                                                                          TEST_EQUAL(n.to_string(), "0");
    TRY(n = 0x12345678_N);                                                                                 TEST_EQUAL(n.to_string(), "305419896");
    TRY(n = 0x123456789abcdef0_N);                                                                         TEST_EQUAL(n.to_string(), "1311768467463790320");
    TRY(n = 0b110011000011110111111011111001011100011101100011001111101111100000001000101111100010101_N);  TEST_EQUAL(n.to_string(), "123456789123456789123456789");
    TRY(n = 123456789123456789123456789_N);                                                                TEST_EQUAL(n.to_string(), "123456789123456789123456789");
    TRY(n = 0x661efdf2e3b19f7c045f15_N);                                                                   TEST_EQUAL(n.to_string(), "123456789123456789123456789");
    TRY(n = 0x12'345'678_N);                                                                               TEST_EQUAL(n.to_string(), "305419896");
    TRY(n = 0x1234'5678'9abc'def0_N);                                                                      TEST_EQUAL(n.to_string(), "1311768467463790320");
    TRY(n = 0b110011000011110111111011111001011100011101100011001111101111100000001000101111100010101_N);  TEST_EQUAL(n.to_string(), "123456789123456789123456789");
    TRY(n = 123'456'789'123'456'789'123'456'789_N);                                                        TEST_EQUAL(n.to_string(), "123456789123456789123456789");
    TRY(n = 0x66'1efd'f2e3'b19f'7c04'5f15_N);                                                              TEST_EQUAL(n.to_string(), "123456789123456789123456789");

    TRY(z = 0_Z);                                                                              TEST_EQUAL(z.to_string(), "0");
    TRY(z = 123456789_Z);                                                                      TEST_EQUAL(z.to_string(), "123456789");
    TRY(z = -123456789_Z);                                                                     TEST_EQUAL(z.to_string(), "-123456789");
    TRY(z = 123456789123456789_Z);                                                             TEST_EQUAL(z.to_string(), "123456789123456789");
    TRY(z = -123456789123456789_Z);                                                            TEST_EQUAL(z.to_string(), "-123456789123456789");
    TRY(z = 123456789123456789123456789123456789123456789_Z);                                  TEST_EQUAL(z.to_string(), "123456789123456789123456789123456789123456789");
    TRY(z = -123456789123456789123456789123456789123456789_Z);                                 TEST_EQUAL(z.to_string(), "-123456789123456789123456789123456789123456789");
    TRY(z = 0b10101010101010101010101010101010101010101010101010_Z);                           TEST_EQUAL(z.to_string(), "750599937895082");
    TRY(z = -0b10101010101010101010101010101010101010101010101010_Z);                          TEST_EQUAL(z.to_string(), "-750599937895082");
    TRY(z = 0x123456789abcdef123456789abcdef123456789abcdef123456789abcdef_Z);                 TEST_EQUAL(z.to_string(), "125642457939796217460094503631385345882379387509263401568735420576681455");
    TRY(z = -0x123456789abcdef123456789abcdef123456789abcdef123456789abcdef_Z);                TEST_EQUAL(z.to_string(), "-125642457939796217460094503631385345882379387509263401568735420576681455");
    TRY(z = 123'456'789_Z);                                                                    TEST_EQUAL(z.to_string(), "123456789");
    TRY(z = -123'456'789_Z);                                                                   TEST_EQUAL(z.to_string(), "-123456789");
    TRY(z = 123'456'789'123'456'789_Z);                                                        TEST_EQUAL(z.to_string(), "123456789123456789");
    TRY(z = -123'456'789'123'456'789_Z);                                                       TEST_EQUAL(z.to_string(), "-123456789123456789");
    TRY(z = 123'456'789'123'456'789'123'456'789'123'456'789'123'456'789_Z);                    TEST_EQUAL(z.to_string(), "123456789123456789123456789123456789123456789");
    TRY(z = -123'456'789'123'456'789'123'456'789'123'456'789'123'456'789_Z);                   TEST_EQUAL(z.to_string(), "-123456789123456789123456789123456789123456789");
    TRY(z = 0b10101'01010'10101'01010'10101'01010'10101'01010'10101'01010_Z);                  TEST_EQUAL(z.to_string(), "750599937895082");
    TRY(z = -0b10101'01010'10101'01010'10101'01010'10101'01010'10101'01010_Z);                 TEST_EQUAL(z.to_string(), "-750599937895082");
    TRY(z = 0x1234'5678'9abc'def1'2345'6789'abcd'ef12'3456'789a'bcde'f123'4567'89ab'cdef_Z);   TEST_EQUAL(z.to_string(), "125642457939796217460094503631385345882379387509263401568735420576681455");
    TRY(z = -0x1234'5678'9abc'def1'2345'6789'abcd'ef12'3456'789a'bcde'f123'4567'89ab'cdef_Z);  TEST_EQUAL(z.to_string(), "-125642457939796217460094503631385345882379387509263401568735420576681455");

}

void test_rs_core_mp_integer_comparison() {

    TEST(Natural{0} == Natural{0});      TEST(Natural{0} <= Natural{0});      TEST(Natural{0} >= Natural{0});
    TEST(Natural{42} == Natural{42});    TEST(Natural{42} <= Natural{42});    TEST(Natural{42} >= Natural{42});
    TEST(Natural{86} != Natural{99});    TEST(Natural{86} < Natural{99});     TEST(Natural{86} <= Natural{99});
    TEST(Natural{99} != Natural{86});    TEST(Natural{99} > Natural{86});     TEST(Natural{99} >= Natural{86});
    TEST(Natural{0} == 0);               TEST(Natural{0} <= 0);               TEST(Natural{0} >= 0);
    TEST(Natural{42} == 42);             TEST(Natural{42} <= 42);             TEST(Natural{42} >= 42);
    TEST(Natural{86} != 99);             TEST(Natural{86} < 99);              TEST(Natural{86} <= 99);
    TEST(Natural{99} != 86);             TEST(Natural{99} > 86);              TEST(Natural{99} >= 86);
    TEST(Natural{0} != -42);             TEST(Natural{0} > -42);              TEST(Natural{0} >= -42);
    TEST(Natural{0} == 0u);              TEST(Natural{0} <= 0u);              TEST(Natural{0} >= 0u);
    TEST(Natural{42} == 42u);            TEST(Natural{42} <= 42u);            TEST(Natural{42} >= 42u);
    TEST(Natural{86} != 99u);            TEST(Natural{86} < 99u);             TEST(Natural{86} <= 99u);
    TEST(Natural{99} != 86u);            TEST(Natural{99} > 86u);             TEST(Natural{99} >= 86u);
    TEST(0 == Natural{0});               TEST(0 <= Natural{0});               TEST(0 >= Natural{0});
    TEST(42 == Natural{42});             TEST(42 <= Natural{42});             TEST(42 >= Natural{42});
    TEST(86 != Natural{99});             TEST(86 < Natural{99});              TEST(86 <= Natural{99});
    TEST(99 != Natural{86});             TEST(99 > Natural{86});              TEST(99 >= Natural{86});
    TEST(-42 != Natural{0});             TEST(-42 < Natural{0});              TEST(-42 <= Natural{0});
    TEST(0u == Natural{0});              TEST(0u <= Natural{0});              TEST(0u >= Natural{0});
    TEST(42u == Natural{42});            TEST(42u <= Natural{42});            TEST(42u >= Natural{42});
    TEST(86u != Natural{99});            TEST(86u < Natural{99});             TEST(86u <= Natural{99});
    TEST(99u != Natural{86});            TEST(99u > Natural{86});             TEST(99u >= Natural{86});
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
    TEST(Integer{0} == Natural{0});      TEST(Integer{0} <= Natural{0});      TEST(Integer{0} >= Natural{0});
    TEST(Integer{42} == Natural{42});    TEST(Integer{42} <= Natural{42});    TEST(Integer{42} >= Natural{42});
    TEST(Integer{86} != Natural{99});    TEST(Integer{86} < Natural{99});     TEST(Integer{86} <= Natural{99});
    TEST(Integer{99} != Natural{86});    TEST(Integer{99} > Natural{86});     TEST(Integer{99} >= Natural{86});
    TEST(Integer{0} != Natural{42});     TEST(Integer{0} < Natural{42});      TEST(Integer{0} <= Natural{42});
    TEST(Integer{42} != Natural{0});     TEST(Integer{42} > Natural{0});      TEST(Integer{42} >= Natural{0});
    TEST(Natural{0} == Integer{0});      TEST(Natural{0} <= Integer{0});      TEST(Natural{0} >= Integer{0});
    TEST(Natural{42} == Integer{42});    TEST(Natural{42} <= Integer{42});    TEST(Natural{42} >= Integer{42});
    TEST(Natural{86} != Integer{99});    TEST(Natural{86} < Integer{99});     TEST(Natural{86} <= Integer{99});
    TEST(Natural{99} != Integer{86});    TEST(Natural{99} > Integer{86});     TEST(Natural{99} >= Integer{86});
    TEST(Natural{0} != Integer{42});     TEST(Natural{0} < Integer{42});      TEST(Natural{0} <= Integer{42});
    TEST(Natural{42} != Integer{0});     TEST(Natural{42} > Integer{0});      TEST(Natural{42} >= Integer{0});

    TEST((Natural{0} <=> Natural{0})      == std::strong_ordering::equal);
    TEST((Natural{42} <=> Natural{42})    == std::strong_ordering::equal);
    TEST((Natural{86} <=> Natural{99})    == std::strong_ordering::less);
    TEST((Natural{99} <=> Natural{86})    == std::strong_ordering::greater);
    TEST((Natural{0} <=> 0)               == std::strong_ordering::equal);
    TEST((Natural{42} <=> 42)             == std::strong_ordering::equal);
    TEST((Natural{86} <=> 99)             == std::strong_ordering::less);
    TEST((Natural{99} <=> 86)             == std::strong_ordering::greater);
    TEST((Natural{0} <=> -42)             == std::strong_ordering::greater);
    TEST((Natural{0} <=> 0u)              == std::strong_ordering::equal);
    TEST((Natural{42} <=> 42u)            == std::strong_ordering::equal);
    TEST((Natural{86} <=> 99u)            == std::strong_ordering::less);
    TEST((Natural{99} <=> 86u)            == std::strong_ordering::greater);
    TEST((0 <=> Natural{0})               == std::strong_ordering::equal);
    TEST((42 <=> Natural{42})             == std::strong_ordering::equal);
    TEST((86 <=> Natural{99})             == std::strong_ordering::less);
    TEST((99 <=> Natural{86})             == std::strong_ordering::greater);
    TEST((-42 <=> Natural{0})             == std::strong_ordering::less);
    TEST((0u <=> Natural{0})              == std::strong_ordering::equal);
    TEST((42u <=> Natural{42})            == std::strong_ordering::equal);
    TEST((86u <=> Natural{99})            == std::strong_ordering::less);
    TEST((99u <=> Natural{86})            == std::strong_ordering::greater);
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
    TEST((Integer{0} <=> Natural{0})      == std::strong_ordering::equal);
    TEST((Integer{42} <=> Natural{42})    == std::strong_ordering::equal);
    TEST((Integer{86} <=> Natural{99})    == std::strong_ordering::less);
    TEST((Integer{99} <=> Natural{86})    == std::strong_ordering::greater);
    TEST((Integer{0} <=> Natural{42})     == std::strong_ordering::less);
    TEST((Integer{42} <=> Natural{0})     == std::strong_ordering::greater);
    TEST((Natural{0} <=> Integer{0})      == std::strong_ordering::equal);
    TEST((Natural{42} <=> Integer{42})    == std::strong_ordering::equal);
    TEST((Natural{86} <=> Integer{99})    == std::strong_ordering::less);
    TEST((Natural{99} <=> Integer{86})    == std::strong_ordering::greater);
    TEST((Natural{0} <=> Integer{42})     == std::strong_ordering::less);
    TEST((Natural{42} <=> Integer{0})     == std::strong_ordering::greater);

}

void test_rs_core_mp_integer_hash_set() {

    std::unordered_set<Natural> uset;
    std::unordered_set<Integer> iset;

    TEST(uset.empty());
    TEST(iset.empty());

    for (int i = 1; i <= 10; ++i) {
        TRY(uset.insert(static_cast<unsigned>(i)));
        TRY(iset.insert(i));
    }

    TEST_EQUAL(uset.size(), 10u);
    TEST_EQUAL(iset.size(), 10u);

}
