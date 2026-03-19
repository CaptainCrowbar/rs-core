#include "rs-core/format.hpp"
#include "rs-core/unit-test.hpp"
#include <string>

using namespace RS;

void test_rs_core_format_append_integer() {

    std::string s;

    s = "@";  TRY(append_integer(s, 0));              TEST_EQUAL(s, "@0");
    s = "@";  TRY(append_integer(s, 42));             TEST_EQUAL(s, "@42");
    s = "@";  TRY(append_integer(s, 23456));          TEST_EQUAL(s, "@23456");
    s = "@";  TRY(append_integer(s, -42));            TEST_EQUAL(s, "@-42");
    s = "@";  TRY(append_integer(s, -23456));         TEST_EQUAL(s, "@-23456");
    s = "@";  TRY(append_integer(s, 0u));             TEST_EQUAL(s, "@0");
    s = "@";  TRY(append_integer(s, 42u));            TEST_EQUAL(s, "@42");
    s = "@";  TRY(append_integer(s, 23456u));         TEST_EQUAL(s, "@23456");
    s = "@";  TRY(append_integer(s, 0, 2));           TEST_EQUAL(s, "@0");
    s = "@";  TRY(append_integer(s, 42, 2));          TEST_EQUAL(s, "@101010");
    s = "@";  TRY(append_integer(s, 23456, 2));       TEST_EQUAL(s, "@101101110100000");
    s = "@";  TRY(append_integer(s, 0, 16));          TEST_EQUAL(s, "@0");
    s = "@";  TRY(append_integer(s, 42, 16));         TEST_EQUAL(s, "@2a");
    s = "@";  TRY(append_integer(s, 23456, 16));      TEST_EQUAL(s, "@5ba0");
    s = "@";  TRY(append_integer(s, 0, 10, 4));       TEST_EQUAL(s, "@0000");
    s = "@";  TRY(append_integer(s, 42, 10, 4));      TEST_EQUAL(s, "@0042");
    s = "@";  TRY(append_integer(s, 23456, 10, 4));   TEST_EQUAL(s, "@23456");
    s = "@";  TRY(append_integer(s, -42, 10, 4));     TEST_EQUAL(s, "@-0042");
    s = "@";  TRY(append_integer(s, -23456, 10, 4));  TEST_EQUAL(s, "@-23456");
    s = "@";  TRY(append_integer(s, 0, 2, 10));       TEST_EQUAL(s, "@0000000000");
    s = "@";  TRY(append_integer(s, 42, 2, 10));      TEST_EQUAL(s, "@0000101010");
    s = "@";  TRY(append_integer(s, 23456, 2, 10));   TEST_EQUAL(s, "@101101110100000");
    s = "@";  TRY(append_integer(s, 0, 16, 3));       TEST_EQUAL(s, "@000");
    s = "@";  TRY(append_integer(s, 42, 16, 3));      TEST_EQUAL(s, "@02a");
    s = "@";  TRY(append_integer(s, 23456, 16, 3));   TEST_EQUAL(s, "@5ba0");

}
