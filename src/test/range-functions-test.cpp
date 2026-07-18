#include "rs-core/range.hpp"
#include "rs-core/unit-test.hpp"
#include <concepts>
#include <format>
#include <functional>
#include <iterator>
#include <map>
#include <ranges>
#include <string>
#include <vector>

using namespace RS;

void test_rs_core_range_as_range() {

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

void test_rs_core_range_sorted() {

    std::vector<int> u, v;

    u = {};
    TRY(v = sorted(u));
    TEST_EQUAL(std::format("{}", v), "[]");

    u = {5, 4, 3, 2, 1};
    TRY(v = sorted(u));
    TEST_EQUAL(std::format("{}", v), "[1, 2, 3, 4, 5]");

    u = {1, 2, 3, 4, 5};
    TRY(v = sorted(u, std::greater<int>{}));
    TEST_EQUAL(std::format("{}", v), "[5, 4, 3, 2, 1]");

}
