#include "rs-core/random.hpp"
#include "rs-core/unit-test.hpp"
#include <algorithm>
#include <format>
#include <iterator>
#include <ranges>
#include <vector>

namespace rs = std::ranges;
namespace vs = std::views;
using namespace RS;

void test_rs_core_random_iterator() {

    UniformInteger<int> dist{1, 100};
    Pcg rng;
    std::vector<int> vec;
    int n;

    rng = {};
    vec.clear();
    RandomIterator<UniformInteger<int>, Pcg> i{dist, rng};
    TRY(std::copy_n(i, 10, std::back_inserter(vec)));
    TEST_EQUAL(vec.size(), 10u);
    TEST_EQUAL(std::format("{}", vec), "[67, 71, 54, 95, 72, 58, 86, 46, 48, 6]");
    TRY(n = dist(rng));
    TEST_EQUAL(n, 67);

    rng = {};
    vec.clear();
    auto range1 = random_range(dist, rng);
    TRY(rs::copy(range1 | vs::take(10), std::back_inserter(vec)));
    TEST_EQUAL(vec.size(), 10u);
    TEST_EQUAL(std::format("{}", vec), "[67, 71, 54, 95, 72, 58, 86, 46, 48, 6]");
    TRY(n = dist(rng));
    TEST_EQUAL(n, 67);

    rng = {};
    vec.clear();
    IndirectRandomIterator<UniformInteger<int>, Pcg> j{dist, rng};
    TRY(std::copy_n(j, 10, std::back_inserter(vec)));
    TEST_EQUAL(vec.size(), 10u);
    TEST_EQUAL(std::format("{}", vec), "[67, 71, 54, 95, 72, 58, 86, 46, 48, 6]");
    TRY(n = dist(rng));
    TEST_EQUAL(n, 73);

    rng = {};
    vec.clear();
    auto range2 = indirect_random_range(dist, rng);
    TRY(rs::copy(range2 | vs::take(10), std::back_inserter(vec)));
    TEST_EQUAL(vec.size(), 10u);
    TEST_EQUAL(std::format("{}", vec), "[67, 71, 54, 95, 72, 58, 86, 46, 48, 6]");
    TRY(n = dist(rng));
    TEST_EQUAL(n, 73);

}
