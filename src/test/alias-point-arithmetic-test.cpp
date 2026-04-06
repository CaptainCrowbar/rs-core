#include "rs-core/alias.hpp"
#include "rs-core/linear-algebra.hpp"
#include "rs-core/unit-test.hpp"
#include <format>

using namespace RS;

namespace {

    class TagP2;
    class TagV3;
    class TagP3;

    using V2 = Double2;
    using P2 = Alias<V2, TagP2, AliasFlags::point_arithmetic>;
    using V3 = Alias<Double3, TagV3>;
    using P3 = Alias<V3, TagP3, AliasFlags::point_arithmetic>;

}

void test_rs_core_alias_point_arithmetic() {

    V2 u {13, 87};
    V2 v {69, 46};
    V2 w;
    P2 p {49, 73};
    P2 q {81, 60};
    P2 r;

    TEST_EQUAL(std::format("{}", u), "[13,87]");
    TEST_EQUAL(std::format("{}", v), "[69,46]");
    TEST_EQUAL(std::format("{}", w), "[0,0]");
    TEST_EQUAL(std::format("{}", p), "[49,73]");
    TEST_EQUAL(std::format("{}", q), "[81,60]");
    TEST_EQUAL(std::format("{}", r), "[0,0]");

    TRY(w = u + v);           TEST_EQUAL(std::format("{}", w), "[82,133]");
    TRY(w = u - v);           TEST_EQUAL(std::format("{}", w), "[-56,41]");
    TRY(r = p + u);           TEST_EQUAL(std::format("{}", r), "[62,160]");
    TRY(r = q - v);           TEST_EQUAL(std::format("{}", r), "[12,14]");
    TRY(w = p - q);           TEST_EQUAL(std::format("{}", w), "[-32,13]");
    TRY(r = p); TRY(r += u);  TEST_EQUAL(std::format("{}", r), "[62,160]");
    TRY(r = q); TRY(r -= v);  TEST_EQUAL(std::format("{}", r), "[12,14]");

}

void test_rs_core_alias_point_arithmetic_nested() {

    V3 u {42, 74, 82};
    V3 v {71, 52, 96};
    V3 w;
    P3 p {55, 92, 16};
    P3 q {88, 50, 41};
    P3 r;

    TEST_EQUAL(std::format("{}", u), "[42,74,82]");
    TEST_EQUAL(std::format("{}", v), "[71,52,96]");
    TEST_EQUAL(std::format("{}", w), "[0,0,0]");
    TEST_EQUAL(std::format("{}", p), "[55,92,16]");
    TEST_EQUAL(std::format("{}", q), "[88,50,41]");
    TEST_EQUAL(std::format("{}", r), "[0,0,0]");

    TRY(w = u + v);           TEST_EQUAL(std::format("{}", w), "[113,126,178]");
    TRY(w = u - v);           TEST_EQUAL(std::format("{}", w), "[-29,22,-14]");
    TRY(r = p + u);           TEST_EQUAL(std::format("{}", r), "[97,166,98]");
    TRY(r = q - v);           TEST_EQUAL(std::format("{}", r), "[17,-2,-55]");
    TRY(w = p - q);           TEST_EQUAL(std::format("{}", w), "[-33,42,-25]");
    TRY(r = p); TRY(r += u);  TEST_EQUAL(std::format("{}", r), "[97,166,98]");
    TRY(r = q); TRY(r -= v);  TEST_EQUAL(std::format("{}", r), "[17,-2,-55]");

}
