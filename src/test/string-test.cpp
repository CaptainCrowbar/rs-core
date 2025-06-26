#include "rs-core/string.hpp"
#include "rs-core/unit-test.hpp"

using namespace RS;

void test_rs_core_string_character_functions() {

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
    TEST(is_ascii('_'));       TEST(! ascii_iscntrl('_'));     TEST(! ascii_isblank('_'));     TEST(! ascii_isspace('_'));
    TEST(is_ascii('`'));       TEST(! ascii_iscntrl('`'));     TEST(! ascii_isblank('`'));     TEST(! ascii_isspace('`'));
    TEST(is_ascii('a'));       TEST(! ascii_iscntrl('a'));     TEST(! ascii_isblank('a'));     TEST(! ascii_isspace('a'));
    TEST(is_ascii('f'));       TEST(! ascii_iscntrl('f'));     TEST(! ascii_isblank('f'));     TEST(! ascii_isspace('f'));
    TEST(is_ascii('z'));       TEST(! ascii_iscntrl('z'));     TEST(! ascii_isblank('z'));     TEST(! ascii_isspace('z'));
    TEST(is_ascii('{'));       TEST(! ascii_iscntrl('{'));     TEST(! ascii_isblank('{'));     TEST(! ascii_isspace('{'));
    TEST(is_ascii('~'));       TEST(! ascii_iscntrl('~'));     TEST(! ascii_isblank('~'));     TEST(! ascii_isspace('~'));
    TEST(is_ascii('\x7f'));    TEST(ascii_iscntrl('\x7f'));    TEST(! ascii_isblank('\x7f'));  TEST(! ascii_isspace('\x7f'));
    TEST(! is_ascii('\x80'));  TEST(! ascii_iscntrl('\x80'));  TEST(! ascii_isblank('\x80'));  TEST(! ascii_isspace('\x80'));
    TEST(! is_ascii('\xff'));  TEST(! ascii_iscntrl('\xff'));  TEST(! ascii_isblank('\xff'));  TEST(! ascii_isspace('\xff'));

    TEST(! ascii_isdigit('\0'));    TEST(! ascii_isxdigit('\0'));    TEST(! ascii_isalnum('\0'));    TEST(! ascii_isalnum_w('\0'));
    TEST(! ascii_isdigit('\t'));    TEST(! ascii_isxdigit('\t'));    TEST(! ascii_isalnum('\t'));    TEST(! ascii_isalnum_w('\t'));
    TEST(! ascii_isdigit('\r'));    TEST(! ascii_isxdigit('\r'));    TEST(! ascii_isalnum('\r'));    TEST(! ascii_isalnum_w('\r'));
    TEST(! ascii_isdigit('\x1f'));  TEST(! ascii_isxdigit('\x1f'));  TEST(! ascii_isalnum('\x1f'));  TEST(! ascii_isalnum_w('\x1f'));
    TEST(! ascii_isdigit(' '));     TEST(! ascii_isxdigit(' '));     TEST(! ascii_isalnum(' '));     TEST(! ascii_isalnum_w(' '));
    TEST(! ascii_isdigit('!'));     TEST(! ascii_isxdigit('!'));     TEST(! ascii_isalnum('!'));     TEST(! ascii_isalnum_w('!'));
    TEST(! ascii_isdigit('/'));     TEST(! ascii_isxdigit('/'));     TEST(! ascii_isalnum('/'));     TEST(! ascii_isalnum_w('/'));
    TEST(ascii_isdigit('0'));       TEST(ascii_isxdigit('0'));       TEST(ascii_isalnum('0'));       TEST(ascii_isalnum_w('0'));
    TEST(ascii_isdigit('9'));       TEST(ascii_isxdigit('9'));       TEST(ascii_isalnum('9'));       TEST(ascii_isalnum_w('9'));
    TEST(! ascii_isdigit(':'));     TEST(! ascii_isxdigit(':'));     TEST(! ascii_isalnum(':'));     TEST(! ascii_isalnum_w(':'));
    TEST(! ascii_isdigit('@'));     TEST(! ascii_isxdigit('@'));     TEST(! ascii_isalnum('@'));     TEST(! ascii_isalnum_w('@'));
    TEST(! ascii_isdigit('A'));     TEST(ascii_isxdigit('A'));       TEST(ascii_isalnum('A'));       TEST(ascii_isalnum_w('A'));
    TEST(! ascii_isdigit('F'));     TEST(ascii_isxdigit('F'));       TEST(ascii_isalnum('F'));       TEST(ascii_isalnum_w('F'));
    TEST(! ascii_isdigit('Z'));     TEST(! ascii_isxdigit('Z'));     TEST(ascii_isalnum('Z'));       TEST(ascii_isalnum_w('Z'));
    TEST(! ascii_isdigit('['));     TEST(! ascii_isxdigit('['));     TEST(! ascii_isalnum('['));     TEST(! ascii_isalnum_w('['));
    TEST(! ascii_isdigit('_'));     TEST(! ascii_isxdigit('_'));     TEST(! ascii_isalnum('_'));     TEST(ascii_isalnum_w('_'));
    TEST(! ascii_isdigit('`'));     TEST(! ascii_isxdigit('`'));     TEST(! ascii_isalnum('`'));     TEST(! ascii_isalnum_w('`'));
    TEST(! ascii_isdigit('a'));     TEST(ascii_isxdigit('a'));       TEST(ascii_isalnum('a'));       TEST(ascii_isalnum_w('a'));
    TEST(! ascii_isdigit('f'));     TEST(ascii_isxdigit('f'));       TEST(ascii_isalnum('f'));       TEST(ascii_isalnum_w('f'));
    TEST(! ascii_isdigit('z'));     TEST(! ascii_isxdigit('z'));     TEST(ascii_isalnum('z'));       TEST(ascii_isalnum_w('z'));
    TEST(! ascii_isdigit('{'));     TEST(! ascii_isxdigit('{'));     TEST(! ascii_isalnum('{'));     TEST(! ascii_isalnum_w('{'));
    TEST(! ascii_isdigit('~'));     TEST(! ascii_isxdigit('~'));     TEST(! ascii_isalnum('~'));     TEST(! ascii_isalnum_w('~'));
    TEST(! ascii_isdigit('\x7f'));  TEST(! ascii_isxdigit('\x7f'));  TEST(! ascii_isalnum('\x7f'));  TEST(! ascii_isalnum_w('\x7f'));
    TEST(! ascii_isdigit('\x80'));  TEST(! ascii_isxdigit('\x80'));  TEST(! ascii_isalnum('\x80'));  TEST(! ascii_isalnum_w('\x80'));
    TEST(! ascii_isdigit('\xff'));  TEST(! ascii_isxdigit('\xff'));  TEST(! ascii_isalnum('\xff'));  TEST(! ascii_isalnum_w('\xff'));

    TEST(! ascii_isupper('\0'));    TEST(! ascii_islower('\0'));    TEST(! ascii_isalpha('\0'));    TEST(! ascii_isalpha_w('\0'));
    TEST(! ascii_isupper('\t'));    TEST(! ascii_islower('\t'));    TEST(! ascii_isalpha('\t'));    TEST(! ascii_isalpha_w('\t'));
    TEST(! ascii_isupper('\r'));    TEST(! ascii_islower('\r'));    TEST(! ascii_isalpha('\r'));    TEST(! ascii_isalpha_w('\r'));
    TEST(! ascii_isupper('\x1f'));  TEST(! ascii_islower('\x1f'));  TEST(! ascii_isalpha('\x1f'));  TEST(! ascii_isalpha_w('\x1f'));
    TEST(! ascii_isupper(' '));     TEST(! ascii_islower(' '));     TEST(! ascii_isalpha(' '));     TEST(! ascii_isalpha_w(' '));
    TEST(! ascii_isupper('!'));     TEST(! ascii_islower('!'));     TEST(! ascii_isalpha('!'));     TEST(! ascii_isalpha_w('!'));
    TEST(! ascii_isupper('/'));     TEST(! ascii_islower('/'));     TEST(! ascii_isalpha('/'));     TEST(! ascii_isalpha_w('/'));
    TEST(! ascii_isupper('0'));     TEST(! ascii_islower('0'));     TEST(! ascii_isalpha('0'));     TEST(! ascii_isalpha_w('0'));
    TEST(! ascii_isupper('9'));     TEST(! ascii_islower('9'));     TEST(! ascii_isalpha('9'));     TEST(! ascii_isalpha_w('9'));
    TEST(! ascii_isupper(':'));     TEST(! ascii_islower(':'));     TEST(! ascii_isalpha(':'));     TEST(! ascii_isalpha_w(':'));
    TEST(! ascii_isupper('@'));     TEST(! ascii_islower('@'));     TEST(! ascii_isalpha('@'));     TEST(! ascii_isalpha_w('@'));
    TEST(ascii_isupper('A'));       TEST(! ascii_islower('A'));     TEST(ascii_isalpha('A'));       TEST(ascii_isalpha_w('A'));
    TEST(ascii_isupper('F'));       TEST(! ascii_islower('F'));     TEST(ascii_isalpha('F'));       TEST(ascii_isalpha_w('F'));
    TEST(ascii_isupper('Z'));       TEST(! ascii_islower('Z'));     TEST(ascii_isalpha('Z'));       TEST(ascii_isalpha_w('Z'));
    TEST(! ascii_isupper('['));     TEST(! ascii_islower('['));     TEST(! ascii_isalpha('['));     TEST(! ascii_isalpha_w('['));
    TEST(! ascii_isupper('_'));     TEST(! ascii_islower('_'));     TEST(! ascii_isalpha('_'));     TEST(ascii_isalpha_w('_'));
    TEST(! ascii_isupper('`'));     TEST(! ascii_islower('`'));     TEST(! ascii_isalpha('`'));     TEST(! ascii_isalpha_w('`'));
    TEST(! ascii_isupper('a'));     TEST(ascii_islower('a'));       TEST(ascii_isalpha('a'));       TEST(ascii_isalpha_w('a'));
    TEST(! ascii_isupper('f'));     TEST(ascii_islower('f'));       TEST(ascii_isalpha('f'));       TEST(ascii_isalpha_w('f'));
    TEST(! ascii_isupper('z'));     TEST(ascii_islower('z'));       TEST(ascii_isalpha('z'));       TEST(ascii_isalpha_w('z'));
    TEST(! ascii_isupper('{'));     TEST(! ascii_islower('{'));     TEST(! ascii_isalpha('{'));     TEST(! ascii_isalpha_w('{'));
    TEST(! ascii_isupper('~'));     TEST(! ascii_islower('~'));     TEST(! ascii_isalpha('~'));     TEST(! ascii_isalpha_w('~'));
    TEST(! ascii_isupper('\x7f'));  TEST(! ascii_islower('\x7f'));  TEST(! ascii_isalpha('\x7f'));  TEST(! ascii_isalpha_w('\x7f'));
    TEST(! ascii_isupper('\x80'));  TEST(! ascii_islower('\x80'));  TEST(! ascii_isalpha('\x80'));  TEST(! ascii_isalpha_w('\x80'));
    TEST(! ascii_isupper('\xff'));  TEST(! ascii_islower('\xff'));  TEST(! ascii_isalpha('\xff'));  TEST(! ascii_isalpha_w('\xff'));

    TEST(! ascii_isgraph('\0'));    TEST(! ascii_isprint('\0'));    TEST(! ascii_ispunct('\0'));    TEST(! ascii_ispunct_w('\0'));
    TEST(! ascii_isgraph('\t'));    TEST(! ascii_isprint('\t'));    TEST(! ascii_ispunct('\t'));    TEST(! ascii_ispunct_w('\t'));
    TEST(! ascii_isgraph('\r'));    TEST(! ascii_isprint('\r'));    TEST(! ascii_ispunct('\r'));    TEST(! ascii_ispunct_w('\r'));
    TEST(! ascii_isgraph('\x1f'));  TEST(! ascii_isprint('\x1f'));  TEST(! ascii_ispunct('\x1f'));  TEST(! ascii_ispunct_w('\x1f'));
    TEST(! ascii_isgraph(' '));     TEST(ascii_isprint(' '));       TEST(! ascii_ispunct(' '));     TEST(! ascii_ispunct_w(' '));
    TEST(ascii_isgraph('!'));       TEST(ascii_isprint('!'));       TEST(ascii_ispunct('!'));       TEST(ascii_ispunct_w('!'));
    TEST(ascii_isgraph('/'));       TEST(ascii_isprint('/'));       TEST(ascii_ispunct('/'));       TEST(ascii_ispunct_w('/'));
    TEST(ascii_isgraph('0'));       TEST(ascii_isprint('0'));       TEST(! ascii_ispunct('0'));     TEST(! ascii_ispunct_w('0'));
    TEST(ascii_isgraph('9'));       TEST(ascii_isprint('9'));       TEST(! ascii_ispunct('9'));     TEST(! ascii_ispunct_w('9'));
    TEST(ascii_isgraph(':'));       TEST(ascii_isprint(':'));       TEST(ascii_ispunct(':'));       TEST(ascii_ispunct_w(':'));
    TEST(ascii_isgraph('@'));       TEST(ascii_isprint('@'));       TEST(ascii_ispunct('@'));       TEST(ascii_ispunct_w('@'));
    TEST(ascii_isgraph('A'));       TEST(ascii_isprint('A'));       TEST(! ascii_ispunct('A'));     TEST(! ascii_ispunct_w('A'));
    TEST(ascii_isgraph('F'));       TEST(ascii_isprint('F'));       TEST(! ascii_ispunct('F'));     TEST(! ascii_ispunct_w('F'));
    TEST(ascii_isgraph('Z'));       TEST(ascii_isprint('Z'));       TEST(! ascii_ispunct('Z'));     TEST(! ascii_ispunct_w('Z'));
    TEST(ascii_isgraph('['));       TEST(ascii_isprint('['));       TEST(ascii_ispunct('['));       TEST(ascii_ispunct_w('['));
    TEST(ascii_isgraph('_'));       TEST(ascii_isprint('_'));       TEST(ascii_ispunct('_'));       TEST(! ascii_ispunct_w('_'));
    TEST(ascii_isgraph('`'));       TEST(ascii_isprint('`'));       TEST(ascii_ispunct('`'));       TEST(ascii_ispunct_w('`'));
    TEST(ascii_isgraph('a'));       TEST(ascii_isprint('a'));       TEST(! ascii_ispunct('a'));     TEST(! ascii_ispunct_w('a'));
    TEST(ascii_isgraph('f'));       TEST(ascii_isprint('f'));       TEST(! ascii_ispunct('f'));     TEST(! ascii_ispunct_w('f'));
    TEST(ascii_isgraph('z'));       TEST(ascii_isprint('z'));       TEST(! ascii_ispunct('z'));     TEST(! ascii_ispunct_w('z'));
    TEST(ascii_isgraph('{'));       TEST(ascii_isprint('{'));       TEST(ascii_ispunct('{'));       TEST(ascii_ispunct_w('{'));
    TEST(ascii_isgraph('~'));       TEST(ascii_isprint('~'));       TEST(ascii_ispunct('~'));       TEST(ascii_ispunct_w('~'));
    TEST(! ascii_isgraph('\x7f'));  TEST(! ascii_isprint('\x7f'));  TEST(! ascii_ispunct('\x7f'));  TEST(! ascii_ispunct_w('\x7f'));
    TEST(! ascii_isgraph('\x80'));  TEST(! ascii_isprint('\x80'));  TEST(! ascii_ispunct('\x80'));  TEST(! ascii_ispunct_w('\x80'));
    TEST(! ascii_isgraph('\xff'));  TEST(! ascii_isprint('\xff'));  TEST(! ascii_ispunct('\xff'));  TEST(! ascii_ispunct_w('\xff'));

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
    TEST_EQUAL(ascii_toupper('_'),     '_');     TEST_EQUAL(ascii_tolower('_'),     '_');
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

void test_rs_core_string_case_conversion() {

    TEST_EQUAL(ascii_lowercase("Hello World"),  "hello world");
    TEST_EQUAL(ascii_lowercase("hello world"),  "hello world");
    TEST_EQUAL(ascii_lowercase("HELLO WORLD"),  "hello world");
    TEST_EQUAL(ascii_uppercase("Hello World"),  "HELLO WORLD");
    TEST_EQUAL(ascii_uppercase("hello world"),  "HELLO WORLD");
    TEST_EQUAL(ascii_uppercase("HELLO WORLD"),  "HELLO WORLD");

}
