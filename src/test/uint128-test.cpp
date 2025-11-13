#include "rs-core/uint128.hpp"
#include "rs-core/unit-test.hpp"
#include <cstdint>
#include <format>

using namespace RS;

void test_rs_core_uint128_conversion() {

    Uint128 u;

    TRY(u = 42u);
    TEST_EQUAL(u.high(), 0u);
    TEST_EQUAL(u.low(), 42u);
    TEST_EQUAL(static_cast<int>(u), 42);
    TEST_EQUAL(static_cast<unsigned>(u), 42u);

    TRY(u = static_cast<Uint128>(86));
    TEST_EQUAL(u.high(), 0u);
    TEST_EQUAL(u.low(), 86u);
    TEST_EQUAL(static_cast<int>(u), 86);
    TEST_EQUAL(static_cast<unsigned>(u), 86u);

    TRY(u = static_cast<Uint128>(-99));
    TEST_EQUAL(u.high(), 0xffff'ffff'ffff'ffffull);
    TEST_EQUAL(u.low(), 0xffff'ffff'ffff'ff9dull);
    TEST_EQUAL(static_cast<int>(u), -99);
    TEST_EQUAL(static_cast<std::uint16_t>(u), 0xff9du);

}

void test_rs_core_uint128_parsing() {

    Uint128 u;

    TRY((u = Uint128{"0"}));                                     TEST_EQUAL(u.high(), 0u);                        TEST_EQUAL(u.low(), 0u);
    TRY((u = Uint128{"42"}));                                    TEST_EQUAL(u.high(), 0u);                        TEST_EQUAL(u.low(), 0x2au);
    TRY((u = Uint128{"42", 16}));                                TEST_EQUAL(u.high(), 0u);                        TEST_EQUAL(u.low(), 0x42u);
    TRY((u = Uint128{"101010", 2}));                             TEST_EQUAL(u.high(), 0u);                        TEST_EQUAL(u.low(), 0x2au);
    TRY((u = Uint128{"12345678"}));                              TEST_EQUAL(u.high(), 0u);                        TEST_EQUAL(u.low(), 0xbc'614eull);
    TRY((u = Uint128{"12345678", 16}));                          TEST_EQUAL(u.high(), 0u);                        TEST_EQUAL(u.low(), 0x1234'5678ull);
    TRY((u = Uint128{"abcdefff", 16}));                          TEST_EQUAL(u.high(), 0u);                        TEST_EQUAL(u.low(), 0xabcd'efffull);
    TRY((u = Uint128{"123456789123456789123456789123456789"}));  TEST_EQUAL(u.high(), 0x17'c6e3'c032'f890ull);    TEST_EQUAL(u.low(), 0x45ad'7466'8404'5f15ull);
    TRY((u = Uint128{"123456789abcdef123456789abcdef12", 16}));  TEST_EQUAL(u.high(), 0x1234'5678'9abc'def1ull);  TEST_EQUAL(u.low(), 0x2345'6789'abcd'ef12ull);

}

void test_rs_core_uint128_formatting() {

    Uint128 u, v, w, x;

    TRY(v = 0x1234'5678ull);
    TRY(w = 0xabcd'efffull);
    TRY((x = {0x1234'5678'9abc'def1ull, 0x2345'6789'abcd'ef12ull}));

    TEST_EQUAL(u.str(),                   "0");
    TEST_EQUAL(v.str(),                   "305419896");
    TEST_EQUAL(w.str(),                   "2882400255");
    TEST_EQUAL(x.str(),                   "24197857203266734884469844682461802258");
    TEST_EQUAL(u.str(10, 15),             "000000000000000");
    TEST_EQUAL(v.str(10, 15),             "000000305419896");
    TEST_EQUAL(w.str(10, 15),             "000002882400255");
    TEST_EQUAL(x.str(10, 15),             "24197857203266734884469844682461802258");
    TEST_EQUAL(std::format("{}", u),      "0");
    TEST_EQUAL(std::format("{}", v),      "305419896");
    TEST_EQUAL(std::format("{}", w),      "2882400255");
    TEST_EQUAL(std::format("{}", x),      "24197857203266734884469844682461802258");
    TEST_EQUAL(std::format("{:15}", u),   "000000000000000");
    TEST_EQUAL(std::format("{:15}", v),   "000000305419896");
    TEST_EQUAL(std::format("{:15}", w),   "000002882400255");
    TEST_EQUAL(std::format("{:15}", x),   "24197857203266734884469844682461802258");
    TEST_EQUAL(u.str(16),                 "0");
    TEST_EQUAL(v.str(16),                 "12345678");
    TEST_EQUAL(w.str(16),                 "abcdefff");
    TEST_EQUAL(x.str(16),                 "123456789abcdef123456789abcdef12");
    TEST_EQUAL(u.str(16, 15),             "000000000000000");
    TEST_EQUAL(v.str(16, 15),             "000000012345678");
    TEST_EQUAL(w.str(16, 15),             "0000000abcdefff");
    TEST_EQUAL(x.str(16, 15),             "123456789abcdef123456789abcdef12");
    TEST_EQUAL(std::format("{:x}", u),    "0");
    TEST_EQUAL(std::format("{:x}", v),    "12345678");
    TEST_EQUAL(std::format("{:x}", w),    "abcdefff");
    TEST_EQUAL(std::format("{:x}", x),    "123456789abcdef123456789abcdef12");
    TEST_EQUAL(std::format("{:15x}", u),  "000000000000000");
    TEST_EQUAL(std::format("{:15x}", v),  "000000012345678");
    TEST_EQUAL(std::format("{:15x}", w),  "0000000abcdefff");
    TEST_EQUAL(std::format("{:15x}", x),  "123456789abcdef123456789abcdef12");
    TEST_EQUAL(u.str(2),                  "0");
    TEST_EQUAL(v.str(2),                  "10010001101000101011001111000");
    TEST_EQUAL(w.str(2),                  "10101011110011011110111111111111");
    TEST_EQUAL(x.str(2),                  "10010001101000101011001111000100110101011110011011110111100010010001101000101011001111000100110101011110011011110111100010010");
    TEST_EQUAL(u.str(2, 30),              "000000000000000000000000000000");
    TEST_EQUAL(v.str(2, 30),              "010010001101000101011001111000");
    TEST_EQUAL(w.str(2, 30),              "10101011110011011110111111111111");
    TEST_EQUAL(x.str(2, 30),              "10010001101000101011001111000100110101011110011011110111100010010001101000101011001111000100110101011110011011110111100010010");
    TEST_EQUAL(std::format("{:b}", u),    "0");
    TEST_EQUAL(std::format("{:b}", v),    "10010001101000101011001111000");
    TEST_EQUAL(std::format("{:b}", w),    "10101011110011011110111111111111");
    TEST_EQUAL(std::format("{:b}", x),    "10010001101000101011001111000100110101011110011011110111100010010001101000101011001111000100110101011110011011110111100010010");
    TEST_EQUAL(std::format("{:b30}", u),  "000000000000000000000000000000");
    TEST_EQUAL(std::format("{:b30}", v),  "010010001101000101011001111000");
    TEST_EQUAL(std::format("{:b30}", w),  "10101011110011011110111111111111");
    TEST_EQUAL(std::format("{:b30}", x),  "10010001101000101011001111000100110101011110011011110111100010010001101000101011001111000100110101011110011011110111100010010");
    TEST_EQUAL(u.hex(),                   "00000000000000000000000000000000");
    TEST_EQUAL(v.hex(),                   "00000000000000000000000012345678");
    TEST_EQUAL(w.hex(),                   "000000000000000000000000abcdefff");
    TEST_EQUAL(x.hex(),                   "123456789abcdef123456789abcdef12");

}

void test_rs_core_uint128_arithmetic() {

    Uint128 u, v, w, x;

    TRY((u = Uint128{0x1234'5678'9abcull, 0xdef1'2345'6789'abcdull}));
    TRY((v = Uint128{0x1234'5678ull, 0x9abc'def1'2345'6789ull}));
    TRY((w = Uint128{0x1234'5678ull, 0xfedc'ba98'7654'3210ull}));

    TRY(x = u + v);                         TEST_EQUAL(x.high(), 0x0000'1234'68ac'f135ull);  TEST_EQUAL(x.low(), 0x79ae'0236'8acf'1356ull);
    TRY(x = u - v);                         TEST_EQUAL(x.high(), 0x0000'1234'4444'4444ull);  TEST_EQUAL(x.low(), 0x4434'4454'4444'4444ull);
    TRY(x = u - w);                         TEST_EQUAL(x.high(), 0x0000'1234'4444'4443ull);  TEST_EQUAL(x.low(), 0xe014'68ac'f135'79bdull);
    TRY(x = w - v);                         TEST_EQUAL(x.high(), 0u);                        TEST_EQUAL(x.low(), 0x641f'dba7'530e'ca87ull);
    TRY(x = 0x123456789ull * 0xabcdefull);  TEST_EQUAL(x.high(), 0u);                        TEST_EQUAL(x.low(), 0x00c3'79aa'aa37'5de7ull);
    TRY(x = v * 0xabcdefull);               TEST_EQUAL(x.high(), 0x000c'379a'aaaa'aaaaull);  TEST_EQUAL(x.low(), 0x9fed'cbba'aa37'5de7ull);
    TRY(x = u * 0xabcdefull);               TEST_EQUAL(x.high(), 0x379a'aaaa'aaaa'9fedull);  TEST_EQUAL(x.low(), 0xcbba'aaaa'aa09'8d63ull);
    TRY(x = u * v);                         TEST_EQUAL(x.high(), 0xe417'6543'10ec'8042ull);  TEST_EQUAL(x.low(), 0xab3c'0962'220d'6bb5ull);
    TRY(x = u / v);                         TEST_EQUAL(x.high(), 0u);                        TEST_EQUAL(x.low(), 0x0000'0000'0001'0000ull);
    TRY(x = u % v);                         TEST_EQUAL(x.high(), 0u);                        TEST_EQUAL(x.low(), 0x0000'0000'0000'abcdull);
    TRY(x = v / u);                         TEST_EQUAL(x.high(), 0u);                        TEST_EQUAL(x.low(), 0u);
    TRY(x = v % u);                         TEST_EQUAL(x.high(), 0x0000'0000'1234'5678ull);  TEST_EQUAL(x.low(), 0x9abc'def1'2345'6789ull);

}

void test_rs_core_uint128_bitwise_operations() {

    Uint128 u, v, w, x;

    TRY((v = Uint128{0x1234'5678'9abcull, 0xdef1'2345'6789'abcdull}));
    TRY((w = Uint128{0x1234'5678ull, 0x9abc'def1'2345'6789ull}));

    TRY(x = ~ u);       TEST_EQUAL(x.high(), 0xffff'ffff'ffff'ffffull);  TEST_EQUAL(x.low(), 0xffff'ffff'ffff'ffffull);
    TRY(x = ~ x);       TEST_EQUAL(x.high(), 0x0000'0000'0000'0000ull);  TEST_EQUAL(x.low(), 0x0000'0000'0000'0000ull);
    TRY(x = ~ v);       TEST_EQUAL(x.high(), 0xffff'edcb'a987'6543ull);  TEST_EQUAL(x.low(), 0x210e'dcba'9876'5432ull);
    TRY(x = v & w);     TEST_EQUAL(x.high(), 0x0000'0000'1230'1238ull);  TEST_EQUAL(x.low(), 0x9ab0'0241'2301'2389ull);
    TRY(x = v | w);     TEST_EQUAL(x.high(), 0x0000'1234'567c'defcull);  TEST_EQUAL(x.low(), 0xdefd'fff5'67cd'efcdull);
    TRY(x = v ^ w);     TEST_EQUAL(x.high(), 0x0000'1234'444c'ccc4ull);  TEST_EQUAL(x.low(), 0x444d'fdb4'44cc'cc44ull);
    TRY(x = v << 0);    TEST_EQUAL(x.high(), 0x0000'1234'5678'9abcull);  TEST_EQUAL(x.low(), 0xdef1'2345'6789'abcdull);
    TRY(x = v << 32);   TEST_EQUAL(x.high(), 0x5678'9abc'def1'2345ull);  TEST_EQUAL(x.low(), 0x6789'abcd'0000'0000ull);
    TRY(x = v << 64);   TEST_EQUAL(x.high(), 0xdef1'2345'6789'abcdull);  TEST_EQUAL(x.low(), 0x0000'0000'0000'0000ull);
    TRY(x = v << 96);   TEST_EQUAL(x.high(), 0x6789'abcd'0000'0000ull);  TEST_EQUAL(x.low(), 0x0000'0000'0000'0000ull);
    TRY(x = v << 128);  TEST_EQUAL(x.high(), 0x0000'0000'0000'0000ull);  TEST_EQUAL(x.low(), 0x0000'0000'0000'0000ull);
    TRY(x = v >> 0);    TEST_EQUAL(x.high(), 0x0000'1234'5678'9abcull);  TEST_EQUAL(x.low(), 0xdef1'2345'6789'abcdull);
    TRY(x = v >> 32);   TEST_EQUAL(x.high(), 0x0000'0000'0000'1234ull);  TEST_EQUAL(x.low(), 0x5678'9abc'def1'2345ull);
    TRY(x = v >> 64);   TEST_EQUAL(x.high(), 0x0000'0000'0000'0000ull);  TEST_EQUAL(x.low(), 0x0000'1234'5678'9abcull);
    TRY(x = v >> 96);   TEST_EQUAL(x.high(), 0x0000'0000'0000'0000ull);  TEST_EQUAL(x.low(), 0x0000'0000'0000'1234ull);
    TRY(x = v >> 128);  TEST_EQUAL(x.high(), 0x0000'0000'0000'0000ull);  TEST_EQUAL(x.low(), 0x0000'0000'0000'0000ull);

}
