#include "rs-core/format.hpp"
#include "rs-core/unit-test.hpp"
#include <cstddef>
#include <format>
#include <string_view>

using namespace RS;

namespace MyNamespace {

    struct Alpha {
        int num = 0;
        auto rs_core_format() const { return std::format("A({})", num); }
    };

    struct Bravo {
        int num = 0;
        auto rs_core_format(std::string_view f = {}) const { return std::format("B({},{})", num, f); }
    };

    struct Charlie {
        int num = 0;
        auto rs_core_format(std::size_t z = 0) const { return std::format("C({},{})", num, z); }
    };

    struct Delta {
        int num = 0;
        auto rs_core_format(std::string_view f = {}, std::size_t z = 0) const { return std::format("D({},{},{})", num, f, z); }
    };

    struct Echo {
        int num = 0;
    };
    inline auto rs_core_format(const Echo& x) { return std::format("E({})", x.num); }

    struct Foxtrot {
        int num = 0;
    };
    inline auto rs_core_format(const Foxtrot& x, std::string_view f = {}) { return std::format("F({},{})", x.num, f); }

    struct Golf {
        int num = 0;
    };
    inline auto rs_core_format(const Golf& x, std::size_t z = 0) { return std::format("G({},{})", x.num, z); }

    struct Hotel {
        int num = 0;
    };
    inline auto rs_core_format(const Hotel& x, std::string_view f = {}, std::size_t z = 0) { return std::format("H({},{},{})", x.num, f, z); }

}

void test_rs_core_format_concepts() {

    using namespace Detail;

    static_assert(FormatByMemberFunction<MyNamespace::Alpha>);
    static_assert(FormatByMemberFunction<MyNamespace::Bravo>);
    static_assert(FormatByMemberFunction<MyNamespace::Charlie>);
    static_assert(FormatByMemberFunction<MyNamespace::Delta>);
    static_assert(! FormatByMemberFunctionWithFlags<MyNamespace::Alpha>);
    static_assert(FormatByMemberFunctionWithFlags<MyNamespace::Bravo>);
    static_assert(! FormatByMemberFunctionWithFlags<MyNamespace::Charlie>);
    static_assert(FormatByMemberFunctionWithFlags<MyNamespace::Delta>);
    static_assert(! FormatByMemberFunctionWithSize<MyNamespace::Alpha>);
    static_assert(! FormatByMemberFunctionWithSize<MyNamespace::Bravo>);
    static_assert(FormatByMemberFunctionWithSize<MyNamespace::Charlie>);
    static_assert(! FormatByMemberFunctionWithSize<MyNamespace::Delta>);
    static_assert(! FormatByMemberFunctionWithBoth<MyNamespace::Alpha>);
    static_assert(! FormatByMemberFunctionWithBoth<MyNamespace::Bravo>);
    static_assert(! FormatByMemberFunctionWithBoth<MyNamespace::Charlie>);
    static_assert(FormatByMemberFunctionWithBoth<MyNamespace::Delta>);
    static_assert(FormatByFreeFunction<MyNamespace::Echo>);
    static_assert(FormatByFreeFunction<MyNamespace::Foxtrot>);
    static_assert(FormatByFreeFunction<MyNamespace::Golf>);
    static_assert(FormatByFreeFunction<MyNamespace::Hotel>);
    static_assert(! FormatByFreeFunctionWithFlags<MyNamespace::Echo>);
    static_assert(FormatByFreeFunctionWithFlags<MyNamespace::Foxtrot>);
    static_assert(! FormatByFreeFunctionWithFlags<MyNamespace::Golf>);
    static_assert(FormatByFreeFunctionWithFlags<MyNamespace::Hotel>);
    static_assert(! FormatByFreeFunctionWithSize<MyNamespace::Echo>);
    static_assert(! FormatByFreeFunctionWithSize<MyNamespace::Foxtrot>);
    static_assert(FormatByFreeFunctionWithSize<MyNamespace::Golf>);
    static_assert(! FormatByFreeFunctionWithSize<MyNamespace::Hotel>);
    static_assert(! FormatByFreeFunctionWithBoth<MyNamespace::Echo>);
    static_assert(! FormatByFreeFunctionWithBoth<MyNamespace::Foxtrot>);
    static_assert(! FormatByFreeFunctionWithBoth<MyNamespace::Golf>);
    static_assert(FormatByFreeFunctionWithBoth<MyNamespace::Hotel>);
    static_assert(AutoFormat<MyNamespace::Alpha>);
    static_assert(AutoFormat<MyNamespace::Bravo>);
    static_assert(AutoFormat<MyNamespace::Charlie>);
    static_assert(AutoFormat<MyNamespace::Delta>);
    static_assert(AutoFormat<MyNamespace::Echo>);
    static_assert(AutoFormat<MyNamespace::Foxtrot>);
    static_assert(AutoFormat<MyNamespace::Golf>);
    static_assert(AutoFormat<MyNamespace::Hotel>);

}

void test_rs_core_format_automation() {

    MyNamespace::Alpha a{10};
    MyNamespace::Bravo b{20};
    MyNamespace::Charlie c{30};
    MyNamespace::Delta d{40};
    MyNamespace::Echo e{50};
    MyNamespace::Foxtrot f{60};
    MyNamespace::Golf g{70};
    MyNamespace::Hotel h{80};

    TEST_EQUAL(std::format("{}", a),            "A(10)");
    TEST_EQUAL(std::format("{:beta}", b),       "B(20,beta)");
    TEST_EQUAL(std::format("{:86}", c),         "C(30,86)");
    TEST_EQUAL(std::format("{:gamma99}", d),    "D(40,gamma,99)");
    TEST_EQUAL(std::format("{}", e),            "E(50)");
    TEST_EQUAL(std::format("{:delta}", f),      "F(60,delta)");
    TEST_EQUAL(std::format("{:86}", g),         "G(70,86)");
    TEST_EQUAL(std::format("{:epsilon99}", h),  "H(80,epsilon,99)");

}
