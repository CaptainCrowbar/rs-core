#include "rs-core/format.hpp"
#include "rs-core/unit-test.hpp"
#include <format>
#include <string>

using namespace RS;

namespace {

    struct Foo {
        int num = 0;
        auto to_string() const { return "Foo:" + std::to_string(num); }
    };

    struct Bar {
        int num = 0;
    };

    auto to_string(const Bar& b) { return "Bar:" + std::to_string(b.num); }

}

template <>
struct std::formatter<Foo>:
BasicFormatter<Foo> {};

template <>
struct std::formatter<Bar>:
BasicFormatter<Bar> {};

void test_rs_core_format() {

    Foo f{86};
    Bar b{99};

    TEST_EQUAL(std::format("{}", f), "Foo:86");
    TEST_EQUAL(std::format("{}", b), "Bar:99");

}
