#include "rs-core/global.hpp"
#include "rs-core/unit-test.hpp"
#include <concepts>
#include <iterator>
#include <map>
#include <ranges>
#include <string>

using namespace RS;

namespace {

    enum class MyBitmask: int {
        none     = 0,
        alpha    = 1,
        bravo    = 2,
        charlie  = 4,
        all      = 7,
    };

}

void test_rs_core_global_bitmask_functions() {

    int n;

    n = 0;  TEST(! has_bit(n, 0));  TEST(! has_bits(n, 0));
    n = 0;  TEST(! has_bit(n, 1));  TEST(! has_bits(n, 1));
    n = 6;  TEST(! has_bit(n, 1));  TEST(! has_bits(n, 1));
    n = 6;  TEST(has_bit(n, 2));    TEST(has_bits(n, 2));
    n = 6;  TEST(has_bit(n, 4));    TEST(has_bits(n, 4));
    n = 6;  TEST(has_bit(n, 7));    TEST(! has_bits(n, 7));

    unsigned u;

    u = 0;  TEST(! has_bit(u, 0));  TEST(! has_bits(u, 0));
    u = 0;  TEST(! has_bit(u, 1));  TEST(! has_bits(u, 1));
    u = 6;  TEST(! has_bit(u, 1));  TEST(! has_bits(u, 1));
    u = 6;  TEST(has_bit(u, 2));    TEST(has_bits(u, 2));
    u = 6;  TEST(has_bit(u, 4));    TEST(has_bits(u, 4));
    u = 6;  TEST(has_bit(u, 7));    TEST(! has_bits(u, 7));

    MyBitmask b;

    b = MyBitmask::none;   TEST(! has_bit(b, 0));  TEST(! has_bits(b, 0));
    b = MyBitmask::none;   TEST(! has_bit(b, 1));  TEST(! has_bits(b, 1));
    b = MyBitmask::bravo;  TEST(! has_bit(b, 1));  TEST(! has_bits(b, 1));
    b = MyBitmask::bravo;  TEST(has_bit(b, 2));    TEST(has_bits(b, 2));
    b = MyBitmask::bravo;  TEST(! has_bit(b, 4));  TEST(! has_bits(b, 4));
    b = MyBitmask::bravo;  TEST(has_bit(b, 7));    TEST(! has_bits(b, 7));

    b = MyBitmask::none;   TEST(! has_bit(b, MyBitmask::none));     TEST(! has_bits(b, MyBitmask::none));
    b = MyBitmask::none;   TEST(! has_bit(b, MyBitmask::alpha));    TEST(! has_bits(b, MyBitmask::alpha));
    b = MyBitmask::bravo;  TEST(! has_bit(b, MyBitmask::alpha));    TEST(! has_bits(b, MyBitmask::alpha));
    b = MyBitmask::bravo;  TEST(has_bit(b, MyBitmask::bravo));      TEST(has_bits(b, MyBitmask::bravo));
    b = MyBitmask::bravo;  TEST(! has_bit(b, MyBitmask::charlie));  TEST(! has_bits(b, MyBitmask::charlie));
    b = MyBitmask::bravo;  TEST(has_bit(b, MyBitmask::all));        TEST(! has_bits(b, MyBitmask::all));

}

void test_rs_core_global_character_functions() {

    TEST(is_ascii('\0'));      TEST(ascii_iscntrl('\0'));      TEST(! ascii_isblank('\0'));    TEST(! ascii_isspace('\0'));
    TEST(is_ascii('\t'));      TEST(ascii_iscntrl('\t'));      TEST(ascii_isblank('\t'));      TEST(ascii_isspace('\t'));
    TEST(is_ascii('\r'));      TEST(ascii_iscntrl('\r'));      TEST(! ascii_isblank('\r'));    TEST(ascii_isspace('\r'));
    TEST(is_ascii('\x1f'));    TEST(ascii_iscntrl('\x1f'));    TEST(! ascii_isblank('\x1f'));  TEST(! ascii_isspace('\x1f'));
    TEST(is_ascii(' '));       TEST(! ascii_iscntrl(' '));     TEST(ascii_isblank(' '));       TEST(ascii_isspace(' '));
    TEST(is_ascii('!'));       TEST(! ascii_iscntrl('!'));     TEST(! ascii_isblank('!'));     TEST(! ascii_isspace('!'));
    TEST(is_ascii('/'));       TEST(! ascii_iscntrl('/'));     TEST(! ascii_isblank('/'));     TEST(! ascii_isspace('/'));
    TEST(is_ascii('0'));       TEST(! ascii_iscntrl('0'));     TEST(! ascii_isblank('0'));     TEST(! ascii_isspace('0'));
    TEST(is_ascii('9'));       TEST(! ascii_iscntrl('9'));     TEST(! ascii_isblank('9'));     TEST(! ascii_isspace('9'));
    TEST(is_ascii(':'));       TEST(! ascii_iscntrl(':'));     TEST(! ascii_isblank(':'));     TEST(! ascii_isspace(':'));
    TEST(is_ascii('@'));       TEST(! ascii_iscntrl('@'));     TEST(! ascii_isblank('@'));     TEST(! ascii_isspace('@'));
    TEST(is_ascii('A'));       TEST(! ascii_iscntrl('A'));     TEST(! ascii_isblank('A'));     TEST(! ascii_isspace('A'));
    TEST(is_ascii('F'));       TEST(! ascii_iscntrl('F'));     TEST(! ascii_isblank('F'));     TEST(! ascii_isspace('F'));
    TEST(is_ascii('Z'));       TEST(! ascii_iscntrl('Z'));     TEST(! ascii_isblank('Z'));     TEST(! ascii_isspace('Z'));
    TEST(is_ascii('['));       TEST(! ascii_iscntrl('['));     TEST(! ascii_isblank('['));     TEST(! ascii_isspace('['));
    TEST(is_ascii('`'));       TEST(! ascii_iscntrl('`'));     TEST(! ascii_isblank('`'));     TEST(! ascii_isspace('`'));
    TEST(is_ascii('a'));       TEST(! ascii_iscntrl('a'));     TEST(! ascii_isblank('a'));     TEST(! ascii_isspace('a'));
    TEST(is_ascii('f'));       TEST(! ascii_iscntrl('f'));     TEST(! ascii_isblank('f'));     TEST(! ascii_isspace('f'));
    TEST(is_ascii('z'));       TEST(! ascii_iscntrl('z'));     TEST(! ascii_isblank('z'));     TEST(! ascii_isspace('z'));
    TEST(is_ascii('{'));       TEST(! ascii_iscntrl('{'));     TEST(! ascii_isblank('{'));     TEST(! ascii_isspace('{'));
    TEST(is_ascii('~'));       TEST(! ascii_iscntrl('~'));     TEST(! ascii_isblank('~'));     TEST(! ascii_isspace('~'));
    TEST(is_ascii('\x7f'));    TEST(ascii_iscntrl('\x7f'));    TEST(! ascii_isblank('\x7f'));  TEST(! ascii_isspace('\x7f'));
    TEST(! is_ascii('\x80'));  TEST(! ascii_iscntrl('\x80'));  TEST(! ascii_isblank('\x80'));  TEST(! ascii_isspace('\x80'));
    TEST(! is_ascii('\xff'));  TEST(! ascii_iscntrl('\xff'));  TEST(! ascii_isblank('\xff'));  TEST(! ascii_isspace('\xff'));

    TEST(! ascii_isdigit('\0'));    TEST(! ascii_isxdigit('\0'));    TEST(! ascii_isalnum('\0'));
    TEST(! ascii_isdigit('\t'));    TEST(! ascii_isxdigit('\t'));    TEST(! ascii_isalnum('\t'));
    TEST(! ascii_isdigit('\r'));    TEST(! ascii_isxdigit('\r'));    TEST(! ascii_isalnum('\r'));
    TEST(! ascii_isdigit('\x1f'));  TEST(! ascii_isxdigit('\x1f'));  TEST(! ascii_isalnum('\x1f'));
    TEST(! ascii_isdigit(' '));     TEST(! ascii_isxdigit(' '));     TEST(! ascii_isalnum(' '));
    TEST(! ascii_isdigit('!'));     TEST(! ascii_isxdigit('!'));     TEST(! ascii_isalnum('!'));
    TEST(! ascii_isdigit('/'));     TEST(! ascii_isxdigit('/'));     TEST(! ascii_isalnum('/'));
    TEST(ascii_isdigit('0'));       TEST(ascii_isxdigit('0'));       TEST(ascii_isalnum('0'));
    TEST(ascii_isdigit('9'));       TEST(ascii_isxdigit('9'));       TEST(ascii_isalnum('9'));
    TEST(! ascii_isdigit(':'));     TEST(! ascii_isxdigit(':'));     TEST(! ascii_isalnum(':'));
    TEST(! ascii_isdigit('@'));     TEST(! ascii_isxdigit('@'));     TEST(! ascii_isalnum('@'));
    TEST(! ascii_isdigit('A'));     TEST(ascii_isxdigit('A'));       TEST(ascii_isalnum('A'));
    TEST(! ascii_isdigit('F'));     TEST(ascii_isxdigit('F'));       TEST(ascii_isalnum('F'));
    TEST(! ascii_isdigit('Z'));     TEST(! ascii_isxdigit('Z'));     TEST(ascii_isalnum('Z'));
    TEST(! ascii_isdigit('['));     TEST(! ascii_isxdigit('['));     TEST(! ascii_isalnum('['));
    TEST(! ascii_isdigit('`'));     TEST(! ascii_isxdigit('`'));     TEST(! ascii_isalnum('`'));
    TEST(! ascii_isdigit('a'));     TEST(ascii_isxdigit('a'));       TEST(ascii_isalnum('a'));
    TEST(! ascii_isdigit('f'));     TEST(ascii_isxdigit('f'));       TEST(ascii_isalnum('f'));
    TEST(! ascii_isdigit('z'));     TEST(! ascii_isxdigit('z'));     TEST(ascii_isalnum('z'));
    TEST(! ascii_isdigit('{'));     TEST(! ascii_isxdigit('{'));     TEST(! ascii_isalnum('{'));
    TEST(! ascii_isdigit('~'));     TEST(! ascii_isxdigit('~'));     TEST(! ascii_isalnum('~'));
    TEST(! ascii_isdigit('\x7f'));  TEST(! ascii_isxdigit('\x7f'));  TEST(! ascii_isalnum('\x7f'));
    TEST(! ascii_isdigit('\x80'));  TEST(! ascii_isxdigit('\x80'));  TEST(! ascii_isalnum('\x80'));
    TEST(! ascii_isdigit('\xff'));  TEST(! ascii_isxdigit('\xff'));  TEST(! ascii_isalnum('\xff'));

    TEST(! ascii_isupper('\0'));    TEST(! ascii_islower('\0'));    TEST(! ascii_isalpha('\0'));
    TEST(! ascii_isupper('\t'));    TEST(! ascii_islower('\t'));    TEST(! ascii_isalpha('\t'));
    TEST(! ascii_isupper('\r'));    TEST(! ascii_islower('\r'));    TEST(! ascii_isalpha('\r'));
    TEST(! ascii_isupper('\x1f'));  TEST(! ascii_islower('\x1f'));  TEST(! ascii_isalpha('\x1f'));
    TEST(! ascii_isupper(' '));     TEST(! ascii_islower(' '));     TEST(! ascii_isalpha(' '));
    TEST(! ascii_isupper('!'));     TEST(! ascii_islower('!'));     TEST(! ascii_isalpha('!'));
    TEST(! ascii_isupper('/'));     TEST(! ascii_islower('/'));     TEST(! ascii_isalpha('/'));
    TEST(! ascii_isupper('0'));     TEST(! ascii_islower('0'));     TEST(! ascii_isalpha('0'));
    TEST(! ascii_isupper('9'));     TEST(! ascii_islower('9'));     TEST(! ascii_isalpha('9'));
    TEST(! ascii_isupper(':'));     TEST(! ascii_islower(':'));     TEST(! ascii_isalpha(':'));
    TEST(! ascii_isupper('@'));     TEST(! ascii_islower('@'));     TEST(! ascii_isalpha('@'));
    TEST(ascii_isupper('A'));       TEST(! ascii_islower('A'));     TEST(ascii_isalpha('A'));
    TEST(ascii_isupper('F'));       TEST(! ascii_islower('F'));     TEST(ascii_isalpha('F'));
    TEST(ascii_isupper('Z'));       TEST(! ascii_islower('Z'));     TEST(ascii_isalpha('Z'));
    TEST(! ascii_isupper('['));     TEST(! ascii_islower('['));     TEST(! ascii_isalpha('['));
    TEST(! ascii_isupper('`'));     TEST(! ascii_islower('`'));     TEST(! ascii_isalpha('`'));
    TEST(! ascii_isupper('a'));     TEST(ascii_islower('a'));       TEST(ascii_isalpha('a'));
    TEST(! ascii_isupper('f'));     TEST(ascii_islower('f'));       TEST(ascii_isalpha('f'));
    TEST(! ascii_isupper('z'));     TEST(ascii_islower('z'));       TEST(ascii_isalpha('z'));
    TEST(! ascii_isupper('{'));     TEST(! ascii_islower('{'));     TEST(! ascii_isalpha('{'));
    TEST(! ascii_isupper('~'));     TEST(! ascii_islower('~'));     TEST(! ascii_isalpha('~'));
    TEST(! ascii_isupper('\x7f'));  TEST(! ascii_islower('\x7f'));  TEST(! ascii_isalpha('\x7f'));
    TEST(! ascii_isupper('\x80'));  TEST(! ascii_islower('\x80'));  TEST(! ascii_isalpha('\x80'));
    TEST(! ascii_isupper('\xff'));  TEST(! ascii_islower('\xff'));  TEST(! ascii_isalpha('\xff'));

    TEST(! ascii_isgraph('\0'));    TEST(! ascii_isprint('\0'));    TEST(! ascii_ispunct('\0'));
    TEST(! ascii_isgraph('\t'));    TEST(! ascii_isprint('\t'));    TEST(! ascii_ispunct('\t'));
    TEST(! ascii_isgraph('\r'));    TEST(! ascii_isprint('\r'));    TEST(! ascii_ispunct('\r'));
    TEST(! ascii_isgraph('\x1f'));  TEST(! ascii_isprint('\x1f'));  TEST(! ascii_ispunct('\x1f'));
    TEST(! ascii_isgraph(' '));     TEST(ascii_isprint(' '));       TEST(! ascii_ispunct(' '));
    TEST(ascii_isgraph('!'));       TEST(ascii_isprint('!'));       TEST(ascii_ispunct('!'));
    TEST(ascii_isgraph('/'));       TEST(ascii_isprint('/'));       TEST(ascii_ispunct('/'));
    TEST(ascii_isgraph('0'));       TEST(ascii_isprint('0'));       TEST(! ascii_ispunct('0'));
    TEST(ascii_isgraph('9'));       TEST(ascii_isprint('9'));       TEST(! ascii_ispunct('9'));
    TEST(ascii_isgraph(':'));       TEST(ascii_isprint(':'));       TEST(ascii_ispunct(':'));
    TEST(ascii_isgraph('@'));       TEST(ascii_isprint('@'));       TEST(ascii_ispunct('@'));
    TEST(ascii_isgraph('A'));       TEST(ascii_isprint('A'));       TEST(! ascii_ispunct('A'));
    TEST(ascii_isgraph('F'));       TEST(ascii_isprint('F'));       TEST(! ascii_ispunct('F'));
    TEST(ascii_isgraph('Z'));       TEST(ascii_isprint('Z'));       TEST(! ascii_ispunct('Z'));
    TEST(ascii_isgraph('['));       TEST(ascii_isprint('['));       TEST(ascii_ispunct('['));
    TEST(ascii_isgraph('`'));       TEST(ascii_isprint('`'));       TEST(ascii_ispunct('`'));
    TEST(ascii_isgraph('a'));       TEST(ascii_isprint('a'));       TEST(! ascii_ispunct('a'));
    TEST(ascii_isgraph('f'));       TEST(ascii_isprint('f'));       TEST(! ascii_ispunct('f'));
    TEST(ascii_isgraph('z'));       TEST(ascii_isprint('z'));       TEST(! ascii_ispunct('z'));
    TEST(ascii_isgraph('{'));       TEST(ascii_isprint('{'));       TEST(ascii_ispunct('{'));
    TEST(ascii_isgraph('~'));       TEST(ascii_isprint('~'));       TEST(ascii_ispunct('~'));
    TEST(! ascii_isgraph('\x7f'));  TEST(! ascii_isprint('\x7f'));  TEST(! ascii_ispunct('\x7f'));
    TEST(! ascii_isgraph('\x80'));  TEST(! ascii_isprint('\x80'));  TEST(! ascii_ispunct('\x80'));
    TEST(! ascii_isgraph('\xff'));  TEST(! ascii_isprint('\xff'));  TEST(! ascii_ispunct('\xff'));

    TEST_EQUAL(ascii_toupper('\0'),    '\0');    TEST_EQUAL(ascii_tolower('\0'),    '\0');
    TEST_EQUAL(ascii_toupper('\t'),    '\t');    TEST_EQUAL(ascii_tolower('\t'),    '\t');
    TEST_EQUAL(ascii_toupper('\r'),    '\r');    TEST_EQUAL(ascii_tolower('\r'),    '\r');
    TEST_EQUAL(ascii_toupper('\x1f'),  '\x1f');  TEST_EQUAL(ascii_tolower('\x1f'),  '\x1f');
    TEST_EQUAL(ascii_toupper(' '),     ' ');     TEST_EQUAL(ascii_tolower(' '),     ' ');
    TEST_EQUAL(ascii_toupper('!'),     '!');     TEST_EQUAL(ascii_tolower('!'),     '!');
    TEST_EQUAL(ascii_toupper('/'),     '/');     TEST_EQUAL(ascii_tolower('/'),     '/');
    TEST_EQUAL(ascii_toupper('0'),     '0');     TEST_EQUAL(ascii_tolower('0'),     '0');
    TEST_EQUAL(ascii_toupper('9'),     '9');     TEST_EQUAL(ascii_tolower('9'),     '9');
    TEST_EQUAL(ascii_toupper(':'),     ':');     TEST_EQUAL(ascii_tolower(':'),     ':');
    TEST_EQUAL(ascii_toupper('@'),     '@');     TEST_EQUAL(ascii_tolower('@'),     '@');
    TEST_EQUAL(ascii_toupper('A'),     'A');     TEST_EQUAL(ascii_tolower('A'),     'a');
    TEST_EQUAL(ascii_toupper('F'),     'F');     TEST_EQUAL(ascii_tolower('F'),     'f');
    TEST_EQUAL(ascii_toupper('Z'),     'Z');     TEST_EQUAL(ascii_tolower('Z'),     'z');
    TEST_EQUAL(ascii_toupper('['),     '[');     TEST_EQUAL(ascii_tolower('['),     '[');
    TEST_EQUAL(ascii_toupper('`'),     '`');     TEST_EQUAL(ascii_tolower('`'),     '`');
    TEST_EQUAL(ascii_toupper('a'),     'A');     TEST_EQUAL(ascii_tolower('a'),     'a');
    TEST_EQUAL(ascii_toupper('f'),     'F');     TEST_EQUAL(ascii_tolower('f'),     'f');
    TEST_EQUAL(ascii_toupper('z'),     'Z');     TEST_EQUAL(ascii_tolower('z'),     'z');
    TEST_EQUAL(ascii_toupper('{'),     '{');     TEST_EQUAL(ascii_tolower('{'),     '{');
    TEST_EQUAL(ascii_toupper('~'),     '~');     TEST_EQUAL(ascii_tolower('~'),     '~');
    TEST_EQUAL(ascii_toupper('\x7f'),  '\x7f');  TEST_EQUAL(ascii_tolower('\x7f'),  '\x7f');
    TEST_EQUAL(ascii_toupper('\x80'),  '\x80');  TEST_EQUAL(ascii_tolower('\x80'),  '\x80');
    TEST_EQUAL(ascii_toupper('\xff'),  '\xff');  TEST_EQUAL(ascii_tolower('\xff'),  '\xff');

}

void test_rs_core_global_range_functions() {

    std::multimap<int, std::string> map = {
        { 1, "alpha" },
        { 2, "bravo" },
        { 2, "charlie" },
        { 2, "delta" },
        { 3, "echo" },
    };

    auto eq_pair = map.equal_range(2);
    auto eq_range = as_range(eq_pair);

    static_assert(std::same_as<decltype(eq_range),
        std::ranges::subrange<
            std::multimap<int, std::string>::iterator,
            std::multimap<int, std::string>::iterator
        >>);

    auto i = eq_range.begin();
    auto j = eq_range.end();
    TEST_EQUAL(std::distance(i, j), 3);
    TEST_EQUAL(i->second, "bravo");
    ++i;
    TEST_EQUAL(i->second, "charlie");
    ++i;
    TEST_EQUAL(i->second, "delta");
    ++i;
    TEST(i == j);

}
