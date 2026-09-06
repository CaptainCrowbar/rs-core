#include "rs-core/mp-integer.hpp"
#include "rs-core/unit-test.hpp"

using namespace RS;

void test_rs_core_mp_integer_unsigned_literals() {

    using namespace RS::Literals;

    Natural n;

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

}
