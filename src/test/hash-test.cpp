#include "rs-core/hash.hpp"
#include "rs-core/unit-test.hpp"
#include <cstddef>
#include <functional>
#include <string>

using namespace RS;

namespace MyNamespace {

    struct Foo {
        unsigned num = 0;
        std::size_t hash() const noexcept { return num * num; }
    };

    void rs_core_hash(Foo);

}

void test_rs_core_hash_kernighan() {

    std::string s;

    s = "";                    TEST_EQUAL(kernighan_hash(s.data(), s.size()), 0x0000'0000_u32);
    s = "Hello world";         TEST_EQUAL(kernighan_hash(s.data(), s.size()), 0xce59'8aa4_u32);
    s = "Goodnight moon";      TEST_EQUAL(kernighan_hash(s.data(), s.size()), 0x6758'daa6_u32);
    s = "Here comes the sun";  TEST_EQUAL(kernighan_hash(s.data(), s.size()), 0xdda4'f4dc_u32);

}

void test_rs_core_hash_mix() {

    auto h = 0uz;

    TRY(h = hash_mix());                                 TEST_EQUAL(h, 0uz);
    TRY(h = hash_mix(42uz));                             TEST_EQUAL(h, 42uz);
    TRY(h = hash_mix(42uz, 86uz));                       TEST_EQUAL(h, 0x9e37'84b3uz);
    TRY(h = hash_mix(42uz, 86uz, 99uz));                 TEST_EQUAL(h, 0x28'cd91'0cbbuz);
    TRY(h = hash_mix(42uz, 86uz, 99uz, 666uz));          TEST_EQUAL(h, 0xa16'f84f'e2fauz);
    TRY(h = hash_mix(42uz, 86uz, 99uz, 666uz, 2501uz));  TEST_EQUAL(h, 0x2'8252'880b'd846uz);

}

void test_rs_core_hash_standard() {

    MyNamespace::Foo f;
    std::hash<MyNamespace::Foo> h;

    f.num = 86;  TEST_EQUAL(h(f), 7396uz);
    f.num = 99;  TEST_EQUAL(h(f), 9801uz);

}
