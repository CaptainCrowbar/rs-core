#include "rs-core/global.hpp"
#include "rs-core/unit-test.hpp"
#include <algorithm>
#include <concepts>
#include <format>
#include <iterator>
#include <map>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

using namespace RS;

namespace {

    template <ReadableRange<char> R>
    std::string make_string(const R& r) {
        std::string s;
        std::ranges::copy(r, std::back_inserter(s));
        return s;
    }

    template <WritableRange<char> R>
    void copy_string(const std::string& s, R& r) {
        std::ranges::copy(s, std::ranges::begin(r));
    }

}

void test_rs_core_global_concepts() {

    static_assert(ReadableRange<std::string, char>);
    static_assert(ReadableRange<std::string_view, char>);
    static_assert(ReadableRange<std::vector<int>, int>);
    static_assert(ReadableRange<std::vector<std::string>, std::string>);
    static_assert(ReadableRange<std::vector<std::string>, std::string_view>);
    static_assert(! ReadableRange<std::vector<std::string>, const char*>);
    static_assert(ReadableRange<const std::string, char>);
    static_assert(ReadableRange<const std::string_view, char>);
    static_assert(ReadableRange<const std::vector<int>, int>);
    static_assert(ReadableRange<const std::vector<std::string>, std::string>);
    static_assert(ReadableRange<const std::vector<std::string>, std::string_view>);
    static_assert(! ReadableRange<const std::vector<std::string>, const char*>);
    static_assert(! ReadableRange<std::string, int*>);
    static_assert(! ReadableRange<std::string_view, int*>);
    static_assert(! ReadableRange<std::vector<int>, int*>);

    static_assert(WritableRange<std::string, char>);
    static_assert(! WritableRange<std::string_view, char>);
    static_assert(WritableRange<std::vector<int>, int>);
    static_assert(WritableRange<std::vector<std::string>, std::string>);
    static_assert(WritableRange<std::vector<std::string>, std::string_view>);
    static_assert(WritableRange<std::vector<std::string>, const char*>);
    static_assert(! WritableRange<const std::string, char>);
    static_assert(! WritableRange<const std::string_view, char>);
    static_assert(! WritableRange<const std::vector<int>, int>);
    static_assert(! WritableRange<const std::vector<std::string>, std::string>);
    static_assert(! WritableRange<const std::vector<std::string>, std::string_view>);
    static_assert(! WritableRange<const std::vector<std::string>, const char*>);
    static_assert(! WritableRange<std::string, int*>);
    static_assert(! WritableRange<std::string_view, int*>);
    static_assert(! WritableRange<std::vector<int>, int*>);

    static_assert(ReadWriteRange<std::string, char>);
    static_assert(! ReadWriteRange<std::string_view, char>);
    static_assert(ReadWriteRange<std::vector<int>, int>);
    static_assert(ReadWriteRange<std::vector<std::string>, std::string>);
    static_assert(ReadWriteRange<std::vector<std::string>, std::string_view>);
    static_assert(! ReadWriteRange<std::vector<std::string>, const char*>);
    static_assert(! ReadWriteRange<const std::string, char>);
    static_assert(! ReadWriteRange<const std::string_view, char>);
    static_assert(! ReadWriteRange<const std::vector<int>, int>);
    static_assert(! ReadWriteRange<const std::vector<std::string>, std::string>);
    static_assert(! ReadWriteRange<const std::vector<std::string>, std::string_view>);
    static_assert(! ReadWriteRange<const std::vector<std::string>, const char*>);
    static_assert(! ReadWriteRange<std::string, int*>);
    static_assert(! ReadWriteRange<std::string_view, int*>);
    static_assert(! ReadWriteRange<std::vector<int>, int*>);

    std::string s;
    std::vector<char> v;

    v = {'a', 'b', 'c', 'd', 'e'};
    TRY(s = make_string(v));
    TEST_EQUAL(s, "abcde");

    s = "xyz";
    v.clear();
    v.resize(s.size());
    TRY(copy_string(s, v));
    TEST_EQUAL(std::format("{}", v), "['x', 'y', 'z']");

}

void test_rs_core_global_range_functions() {

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
