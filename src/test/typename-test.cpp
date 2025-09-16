#include "rs-core/typename.hpp"
#include "rs-core/unit-test.hpp"
#include <cstddef>
#include <string>
#include <vector>

using namespace RS;

namespace {

    class Alpha {
    public:
        virtual ~Alpha() = default;
        virtual void f() const = 0;
    };

    class Bravo:
    public Alpha {
    public:
        void f() const override {}
    };

}

void test_rs_core_typename_static() {

    TEST_EQUAL(type_name<int>(),                       "int");
    TEST_EQUAL(type_name<unsigned>(),                  "unsigned int");
    TEST_EQUAL(type_name<float>(),                     "float");
    TEST_MATCH(type_name<char*>(),                     R"(^char ?\*( _\w+)?)");
    TEST_MATCH(type_name<char const*>(),               R"(^char const ?\*( _\w+)?)");
    TEST_MATCH(type_name<std::byte>(),                 R"(^(enum )?std::byte$)");
    TEST_MATCH(type_name<std::string>(),               R"(^(class )?std(::\w+)?::basic_string<char,.+>$)");
    TEST_MATCH(type_name<std::vector<int>>(),          R"(^(class )?std(::\w+)?::vector<int,.+>$)");
    TEST_MATCH(type_name<std::vector<std::string>>(),  R"(^(class )?std(::\w+)?::vector<(class )?std(::\w+)?::basic_string<char,.+>,.+>$)");
    TEST_MATCH(type_name<Alpha>(),                     R"(^.+::Alpha$)");
    TEST_MATCH(type_name<Bravo>(),                     R"(^.+::Bravo$)");

}

void test_rs_core_typename_dynamic() {

    int i {};
    std::string s;
    Bravo b;
    const Alpha& a {b};

    TEST_EQUAL(type_name(i), type_name<int>());
    TEST_EQUAL(type_name(s), type_name<std::string>());
    TEST_EQUAL(type_name(a), type_name<Bravo>());
    TEST_EQUAL(type_name(b), type_name<Bravo>());

}
