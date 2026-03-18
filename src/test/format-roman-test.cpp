#include "rs-core/format.hpp"
#include "rs-core/unit-test.hpp"

using namespace RS;

void test_rs_core_format_roman() {

    TEST_EQUAL(roman(1),     "I");
    TEST_EQUAL(roman(42),    "XLII");
    TEST_EQUAL(roman(1111),  "MCXI");
    TEST_EQUAL(roman(2222),  "MMCCXXII");
    TEST_EQUAL(roman(3333),  "MMMCCCXXXIII");
    TEST_EQUAL(roman(4444),  "MMMMCDXLIV");
    TEST_EQUAL(roman(5555),  "MMMMMDLV");
    TEST_EQUAL(roman(6666),  "MMMMMMDCLXVI");
    TEST_EQUAL(roman(7777),  "MMMMMMMDCCLXXVII");
    TEST_EQUAL(roman(8888),  "MMMMMMMMDCCCLXXXVIII");
    TEST_EQUAL(roman(9999),  "MMMMMMMMMCMXCIX");
    TEST_EQUAL(roman(0),     "");
    TEST_EQUAL(roman(-1),    "");

}

void test_rs_core_format_parse_roman() {

    TEST_EQUAL(parse_roman("I"),                     1);
    TEST_EQUAL(parse_roman("II"),                    2);
    TEST_EQUAL(parse_roman("III"),                   3);
    TEST_EQUAL(parse_roman("IV"),                    4);
    TEST_EQUAL(parse_roman("IIII"),                  4);
    TEST_EQUAL(parse_roman("V"),                     5);
    TEST_EQUAL(parse_roman("VI"),                    6);
    TEST_EQUAL(parse_roman("VII"),                   7);
    TEST_EQUAL(parse_roman("VIII"),                  8);
    TEST_EQUAL(parse_roman("IX"),                    9);
    TEST_EQUAL(parse_roman("X"),                     10);
    TEST_EQUAL(parse_roman("XI"),                    11);
    TEST_EQUAL(parse_roman("XII"),                   12);
    TEST_EQUAL(parse_roman("XIII"),                  13);
    TEST_EQUAL(parse_roman("XIV"),                   14);
    TEST_EQUAL(parse_roman("XV"),                    15);
    TEST_EQUAL(parse_roman("XVI"),                   16);
    TEST_EQUAL(parse_roman("XVII"),                  17);
    TEST_EQUAL(parse_roman("XVIII"),                 18);
    TEST_EQUAL(parse_roman("XIX"),                   19);
    TEST_EQUAL(parse_roman("XX"),                    20);
    TEST_EQUAL(parse_roman("XLII"),                  42);
    TEST_EQUAL(parse_roman("MCXI"),                  1111);
    TEST_EQUAL(parse_roman("MMCCXXII"),              2222);
    TEST_EQUAL(parse_roman("MMMCCCXXXIII"),          3333);
    TEST_EQUAL(parse_roman("MMMMCDXLIV"),            4444);
    TEST_EQUAL(parse_roman("MMMMMDLV"),              5555);
    TEST_EQUAL(parse_roman("MMMMMMDCLXVI"),          6666);
    TEST_EQUAL(parse_roman("MMMMMMMDCCLXXVII"),      7777);
    TEST_EQUAL(parse_roman("MMMMMMMMDCCCLXXXVIII"),  8888);
    TEST_EQUAL(parse_roman("MMMMMMMMMCMXCIX"),       9999);
    TEST_EQUAL(parse_roman(""),                      -1);
    TEST_EQUAL(parse_roman("XYZ"),                   -1);

}
