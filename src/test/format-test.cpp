#include "rs-core/format.hpp"
#include "rs-core/unit-test.hpp"
#include <format>
#include <string>

using namespace RS;

namespace {

    struct Alpha {
        int number = 0;
        auto to_string() const { return "A:" + std::to_string(number); }
    };

    struct Bravo {
        int number = 0;
    };

    auto to_string(const Bravo& b) { return "B:" + std::to_string(b.number); }

    struct Charlie {
        int number = 0;
    };

}

template <>
struct std::formatter<Alpha>:
BasicFormatter<Alpha> {};

template <>
struct std::formatter<Bravo>:
BasicFormatter<Bravo> {};

template <>
struct std::formatter<Charlie>:
CommonFormatter {

    std::string flags;
    unsigned another_number = 1;

    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return parse_helper(ctx, "abcdef", &flags, &another_number);
    }

    template <typename FormatContext>
    auto format(Charlie c, FormatContext& ctx) const {
        write_out("C:", ctx.out());
        write_out(flags, ctx.out());
        *ctx.out() = ':';
        write_out(std::to_string(another_number), ctx.out());
        *ctx.out() = ':';
        write_out(std::to_string(c.number), ctx.out());
        return ctx.out();
    }

};

void test_rs_core_format() {

    Alpha f{86};
    Bravo b{99};
    Charlie c{2501};

    TEST_EQUAL(std::format("{}", f),         "A:86");
    TEST_EQUAL(std::format("{}", b),         "B:99");
    TEST_EQUAL(std::format("{}", c),         "C::1:2501");
    TEST_EQUAL(std::format("{0:42}", c),     "C::42:2501");
    TEST_EQUAL(std::format("{0:abc}", c),    "C:abc:1:2501");
    TEST_EQUAL(std::format("{0:abc42}", c),  "C:abc:42:2501");

}
