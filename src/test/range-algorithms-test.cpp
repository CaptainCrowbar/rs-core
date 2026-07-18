#include "rs-core/range.hpp"
#include "rs-core/unit-test.hpp"
#include <algorithm>
#include <format>
#include <iterator>
#include <string>
#include <vector>

using namespace RS;

void test_rs_core_range_cartesian_power() {

    std::string alpha = "abc";
    std::vector<std::string> vec;

    auto vec2str = [] (const std::vector<char>& v) { return std::string(v.data(), v.size()); };

    auto cp0 = cartesian_power(alpha, 0);
    auto cp1 = cartesian_power(alpha, 1);
    auto cp2 = cartesian_power(alpha, 2);
    auto cp3 = cartesian_power(alpha, 3);
    auto cp4 = cartesian_power(alpha, 4);

    TEST_EQUAL(std::distance(cp0.begin(), cp0.end()), 1);
    TEST_EQUAL(std::distance(cp1.begin(), cp1.end()), 3);
    TEST_EQUAL(std::distance(cp2.begin(), cp2.end()), 9);
    TEST_EQUAL(std::distance(cp3.begin(), cp3.end()), 27);
    TEST_EQUAL(std::distance(cp4.begin(), cp4.end()), 81);

    vec.clear();
    TRY(std::transform(cp0.begin(), cp0.end(), std::back_inserter(vec), vec2str));
    TEST_EQUAL(vec.size(), 1u);
    TEST_EQUAL(std::format("{}", vec), R"([""])");

    vec.clear();
    TRY(std::transform(cp1.begin(), cp1.end(), std::back_inserter(vec), vec2str));
    TEST_EQUAL(vec.size(), 3u);
    TEST_EQUAL(std::format("{}", vec), R"(["a", "b", "c"])");

    vec.clear();
    TRY(std::transform(cp2.begin(), cp2.end(), std::back_inserter(vec), vec2str));
    TEST_EQUAL(vec.size(), 9u);
    TEST_EQUAL(std::format("{}", vec), R"(["aa", "ab", "ac", "ba", "bb", "bc", "ca", "cb", "cc"])");

    vec.clear();
    TRY(std::transform(cp3.begin(), cp3.end(), std::back_inserter(vec), vec2str));
    TEST_EQUAL(vec.size(), 27u);
    TEST_EQUAL(std::format("{}", vec),
        R"(["aaa", "aab", "aac", "aba", "abb", "abc", "aca", "acb", "acc", )"
        R"("baa", "bab", "bac", "bba", "bbb", "bbc", "bca", "bcb", "bcc", )"
        R"("caa", "cab", "cac", "cba", "cbb", "cbc", "cca", "ccb", "ccc"])"
    );

    vec.clear();
    TRY(std::transform(cp4.begin(), cp4.end(), std::back_inserter(vec), vec2str));
    TEST_EQUAL(vec.size(), 81u);
    TEST_EQUAL(std::format("{}", vec),
        R"(["aaaa", "aaab", "aaac", "aaba", "aabb", "aabc", "aaca", "aacb", "aacc", )"
        R"("abaa", "abab", "abac", "abba", "abbb", "abbc", "abca", "abcb", "abcc", )"
        R"("acaa", "acab", "acac", "acba", "acbb", "acbc", "acca", "accb", "accc", )"
        R"("baaa", "baab", "baac", "baba", "babb", "babc", "baca", "bacb", "bacc", )"
        R"("bbaa", "bbab", "bbac", "bbba", "bbbb", "bbbc", "bbca", "bbcb", "bbcc", )"
        R"("bcaa", "bcab", "bcac", "bcba", "bcbb", "bcbc", "bcca", "bccb", "bccc", )"
        R"("caaa", "caab", "caac", "caba", "cabb", "cabc", "caca", "cacb", "cacc", )"
        R"("cbaa", "cbab", "cbac", "cbba", "cbbb", "cbbc", "cbca", "cbcb", "cbcc", )"
        R"("ccaa", "ccab", "ccac", "ccba", "ccbb", "ccbc", "ccca", "cccb", "cccc"])"
    );

}
