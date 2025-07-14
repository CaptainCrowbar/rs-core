#include "rs-core/mp-integer.hpp"
#include "rs-core/unit-test.hpp"
#include <algorithm>
#include <tuple>
#include <unordered_set>

using namespace RS;

void test_rs_core_mp_integer_literals() {

    Natural n;
    Integer z;

    TRY(n = 0_N);                                                                                          TEST_EQUAL(n.str(), "0");
    TRY(n = 0x12345678_N);                                                                                 TEST_EQUAL(n.str(), "305419896");
    TRY(n = 0x123456789abcdef0_N);                                                                         TEST_EQUAL(n.str(), "1311768467463790320");
    TRY(n = 0b110011000011110111111011111001011100011101100011001111101111100000001000101111100010101_N);  TEST_EQUAL(n.str(), "123456789123456789123456789");
    TRY(n = 123456789123456789123456789_N);                                                                TEST_EQUAL(n.str(), "123456789123456789123456789");
    TRY(n = 0x661efdf2e3b19f7c045f15_N);                                                                   TEST_EQUAL(n.str(), "123456789123456789123456789");
    TRY(n = 0x12'345'678_N);                                                                               TEST_EQUAL(n.str(), "305419896");
    TRY(n = 0x1234'5678'9abc'def0_N);                                                                      TEST_EQUAL(n.str(), "1311768467463790320");
    TRY(n = 0b110011000011110111111011111001011100011101100011001111101111100000001000101111100010101_N);  TEST_EQUAL(n.str(), "123456789123456789123456789");
    TRY(n = 123'456'789'123'456'789'123'456'789_N);                                                        TEST_EQUAL(n.str(), "123456789123456789123456789");
    TRY(n = 0x66'1efd'f2e3'b19f'7c04'5f15_N);                                                              TEST_EQUAL(n.str(), "123456789123456789123456789");

    TRY(z = 0_Z);                                                                              TEST_EQUAL(z.str(), "0");
    TRY(z = 123456789_Z);                                                                      TEST_EQUAL(z.str(), "123456789");
    TRY(z = -123456789_Z);                                                                     TEST_EQUAL(z.str(), "-123456789");
    TRY(z = 123456789123456789_Z);                                                             TEST_EQUAL(z.str(), "123456789123456789");
    TRY(z = -123456789123456789_Z);                                                            TEST_EQUAL(z.str(), "-123456789123456789");
    TRY(z = 123456789123456789123456789123456789123456789_Z);                                  TEST_EQUAL(z.str(), "123456789123456789123456789123456789123456789");
    TRY(z = -123456789123456789123456789123456789123456789_Z);                                 TEST_EQUAL(z.str(), "-123456789123456789123456789123456789123456789");
    TRY(z = 0b10101010101010101010101010101010101010101010101010_Z);                           TEST_EQUAL(z.str(), "750599937895082");
    TRY(z = -0b10101010101010101010101010101010101010101010101010_Z);                          TEST_EQUAL(z.str(), "-750599937895082");
    TRY(z = 0x123456789abcdef123456789abcdef123456789abcdef123456789abcdef_Z);                 TEST_EQUAL(z.str(), "125642457939796217460094503631385345882379387509263401568735420576681455");
    TRY(z = -0x123456789abcdef123456789abcdef123456789abcdef123456789abcdef_Z);                TEST_EQUAL(z.str(), "-125642457939796217460094503631385345882379387509263401568735420576681455");
    TRY(z = 123'456'789_Z);                                                                    TEST_EQUAL(z.str(), "123456789");
    TRY(z = -123'456'789_Z);                                                                   TEST_EQUAL(z.str(), "-123456789");
    TRY(z = 123'456'789'123'456'789_Z);                                                        TEST_EQUAL(z.str(), "123456789123456789");
    TRY(z = -123'456'789'123'456'789_Z);                                                       TEST_EQUAL(z.str(), "-123456789123456789");
    TRY(z = 123'456'789'123'456'789'123'456'789'123'456'789'123'456'789_Z);                    TEST_EQUAL(z.str(), "123456789123456789123456789123456789123456789");
    TRY(z = -123'456'789'123'456'789'123'456'789'123'456'789'123'456'789_Z);                   TEST_EQUAL(z.str(), "-123456789123456789123456789123456789123456789");
    TRY(z = 0b10101'01010'10101'01010'10101'01010'10101'01010'10101'01010_Z);                  TEST_EQUAL(z.str(), "750599937895082");
    TRY(z = -0b10101'01010'10101'01010'10101'01010'10101'01010'10101'01010_Z);                 TEST_EQUAL(z.str(), "-750599937895082");
    TRY(z = 0x1234'5678'9abc'def1'2345'6789'abcd'ef12'3456'789a'bcde'f123'4567'89ab'cdef_Z);   TEST_EQUAL(z.str(), "125642457939796217460094503631385345882379387509263401568735420576681455");
    TRY(z = -0x1234'5678'9abc'def1'2345'6789'abcd'ef12'3456'789a'bcde'f123'4567'89ab'cdef_Z);  TEST_EQUAL(z.str(), "-125642457939796217460094503631385345882379387509263401568735420576681455");

}

void test_rs_core_mp_integer_core_functions() {

    Natural a = 42u;
    Natural b = 99u;
    Natural c;
    Natural d;
    Integer w = 42;
    Integer x = -99;
    Integer y;
    Integer z;

    TRY(c = std::clamp(a, Natural(0), Natural(10)));  TEST_EQUAL(c, 10u);
    TRY(y = std::clamp(w, Integer(0), Integer(10)));  TEST_EQUAL(y, 10);

    TRY(c = b / a);  TEST_EQUAL(c, 2u);  TRY(c = b % a);  TEST_EQUAL(c, 15u);
    TRY(y = x / w);  TEST_EQUAL(y, -3);  TRY(y = x % w);  TEST_EQUAL(y, 27);

    TRY(std::tie(c, d) = b.divide(a));  TEST_EQUAL(c, 2u);  TEST_EQUAL(d, 15u);
    TRY(std::tie(y, z) = x.divide(w));  TEST_EQUAL(y, -3);  TEST_EQUAL(z, 27);

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
