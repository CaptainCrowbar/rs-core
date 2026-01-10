#include "rs-core/global.hpp"
#include "rs-core/unit-test.hpp"
#include <algorithm>
#include <concepts>
#include <cstdint>
#include <format>
#include <functional>
#include <iterator>
#include <list>
#include <map>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

using namespace RS;

namespace {

    template <SignedIntegral T>        std::string_view select(T) { return "SignedIntegral"; }
    template <UnsignedIntegral T>      std::string_view select(T) { return "UnsignedIntegral"; }
    template <Integral T>              std::string_view select(T) { return "Integral"; }
    template <FloatingPoint T>         std::string_view select(T) { return "FloatingPoint"; }
    template <FixedPointArithmetic T>  std::string_view select(T) { return "FixedPointArithmetic"; }
    template <RationalArithmetic T>    std::string_view select(T) { return "RationalArithmetic"; }
    template <Arithmetic T>            std::string_view select(T) { return "Arithmetic"; }

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

void test_rs_core_global_arithmetic_concepts() {

    TEST(SignedIntegral<int>);
    TEST(! SignedIntegral<unsigned>);
    TEST(SignedIntegral<std::int64_t>);
    TEST(! SignedIntegral<std::uint64_t>);
    TEST(! SignedIntegral<double>);
    TEST(! SignedIntegral<bool>);
    TEST(! SignedIntegral<int*>);
    TEST(! SignedIntegral<std::string>);
    TEST(! UnsignedIntegral<int>);
    TEST(UnsignedIntegral<unsigned>);
    TEST(! UnsignedIntegral<std::int64_t>);
    TEST(UnsignedIntegral<std::uint64_t>);
    TEST(! UnsignedIntegral<double>);
    TEST(! UnsignedIntegral<bool>);
    TEST(! UnsignedIntegral<int*>);
    TEST(! UnsignedIntegral<std::string>);
    TEST(Integral<int>);
    TEST(Integral<unsigned>);
    TEST(Integral<std::int64_t>);
    TEST(Integral<std::uint64_t>);
    TEST(! Integral<double>);
    TEST(! Integral<bool>);
    TEST(! Integral<int*>);
    TEST(! Integral<std::string>);
    TEST(! FloatingPoint<int>);
    TEST(! FloatingPoint<unsigned>);
    TEST(! FloatingPoint<std::int64_t>);
    TEST(! FloatingPoint<std::uint64_t>);
    TEST(FloatingPoint<double>);
    TEST(! FloatingPoint<bool>);
    TEST(! FloatingPoint<int*>);
    TEST(! FloatingPoint<std::string>);
    TEST(! FixedPointArithmetic<int>);
    TEST(! FixedPointArithmetic<unsigned>);
    TEST(! FixedPointArithmetic<std::int64_t>);
    TEST(! FixedPointArithmetic<std::uint64_t>);
    TEST(! FixedPointArithmetic<double>);
    TEST(! FixedPointArithmetic<bool>);
    TEST(! FixedPointArithmetic<int*>);
    TEST(! FixedPointArithmetic<std::string>);
    TEST(! RationalArithmetic<int>);
    TEST(! RationalArithmetic<unsigned>);
    TEST(! RationalArithmetic<std::int64_t>);
    TEST(! RationalArithmetic<std::uint64_t>);
    TEST(! RationalArithmetic<double>);
    TEST(! RationalArithmetic<bool>);
    TEST(! RationalArithmetic<int*>);
    TEST(! RationalArithmetic<std::string>);
    TEST(Arithmetic<int>);
    TEST(Arithmetic<unsigned>);
    TEST(Arithmetic<std::int64_t>);
    TEST(Arithmetic<std::uint64_t>);
    TEST(Arithmetic<double>);
    TEST(! Arithmetic<bool>);
    TEST(! Arithmetic<int*>);
    TEST(! Arithmetic<std::string>);

    TEST_EQUAL(select(86),     "SignedIntegral");
    TEST_EQUAL(select(99u),    "UnsignedIntegral");
    TEST_EQUAL(select(12.34),  "FloatingPoint");

}

void test_rs_core_global_range_concepts() {

    static_assert(ReadableRange<std::string, char>);
    static_assert(ReadableRange<std::string_view, char>);
    static_assert(ReadableRange<std::list<int>, int>);
    static_assert(ReadableRange<std::vector<int>, int>);
    static_assert(ReadableRange<std::vector<std::string>, std::string>);
    static_assert(ReadableRange<std::vector<std::string>, std::string_view>);
    static_assert(! ReadableRange<std::vector<std::string>, const char*>);
    static_assert(ReadableRange<const std::string, char>);
    static_assert(ReadableRange<const std::string_view, char>);
    static_assert(ReadableRange<const std::list<int>, int>);
    static_assert(ReadableRange<const std::vector<int>, int>);
    static_assert(ReadableRange<const std::vector<std::string>, std::string>);
    static_assert(ReadableRange<const std::vector<std::string>, std::string_view>);
    static_assert(! ReadableRange<const std::vector<std::string>, const char*>);
    static_assert(! ReadableRange<std::string, int*>);
    static_assert(! ReadableRange<std::string_view, int*>);
    static_assert(! ReadableRange<std::vector<int>, int*>);

    static_assert(WritableRange<std::string, char>);
    static_assert(! WritableRange<std::string_view, char>);
    static_assert(WritableRange<std::list<int>, int>);
    static_assert(WritableRange<std::vector<int>, int>);
    static_assert(WritableRange<std::vector<std::string>, std::string>);
    static_assert(WritableRange<std::vector<std::string>, std::string_view>);
    static_assert(WritableRange<std::vector<std::string>, const char*>);
    static_assert(! WritableRange<const std::string, char>);
    static_assert(! WritableRange<const std::string_view, char>);
    static_assert(! WritableRange<const std::list<int>, int>);
    static_assert(! WritableRange<const std::vector<int>, int>);
    static_assert(! WritableRange<const std::vector<std::string>, std::string>);
    static_assert(! WritableRange<const std::vector<std::string>, std::string_view>);
    static_assert(! WritableRange<const std::vector<std::string>, const char*>);
    static_assert(! WritableRange<std::string, int*>);
    static_assert(! WritableRange<std::string_view, int*>);
    static_assert(! WritableRange<std::vector<int>, int*>);

    static_assert(ReadWriteRange<std::string, char>);
    static_assert(! ReadWriteRange<std::string_view, char>);
    static_assert(ReadWriteRange<std::list<int>, int>);
    static_assert(ReadWriteRange<std::vector<int>, int>);
    static_assert(ReadWriteRange<std::vector<std::string>, std::string>);
    static_assert(ReadWriteRange<std::vector<std::string>, std::string_view>);
    static_assert(! ReadWriteRange<std::vector<std::string>, const char*>);
    static_assert(! ReadWriteRange<const std::string, char>);
    static_assert(! ReadWriteRange<const std::string_view, char>);
    static_assert(! ReadWriteRange<const std::list<int>, int>);
    static_assert(! ReadWriteRange<const std::vector<int>, int>);
    static_assert(! ReadWriteRange<const std::vector<std::string>, std::string>);
    static_assert(! ReadWriteRange<const std::vector<std::string>, std::string_view>);
    static_assert(! ReadWriteRange<const std::vector<std::string>, const char*>);
    static_assert(! ReadWriteRange<std::string, int*>);
    static_assert(! ReadWriteRange<std::string_view, int*>);
    static_assert(! ReadWriteRange<std::vector<int>, int*>);

    static_assert(ReadableForwardRange<std::string, char>);
    static_assert(ReadableForwardRange<std::list<int>, int>);
    static_assert(ReadableForwardRange<std::vector<int>, int>);
    static_assert(ReadableForwardRange<const std::string, char>);
    static_assert(ReadableForwardRange<const std::list<int>, int>);
    static_assert(ReadableForwardRange<const std::vector<int>, int>);

    static_assert(WritableForwardRange<std::string, char>);
    static_assert(WritableForwardRange<std::list<int>, int>);
    static_assert(WritableForwardRange<std::vector<int>, int>);
    static_assert(! WritableForwardRange<const std::string, char>);
    static_assert(! WritableForwardRange<const std::list<int>, int>);
    static_assert(! WritableForwardRange<const std::vector<int>, int>);

    static_assert(ReadWriteForwardRange<std::string, char>);
    static_assert(ReadWriteForwardRange<std::list<int>, int>);
    static_assert(ReadWriteForwardRange<std::vector<int>, int>);
    static_assert(! ReadWriteForwardRange<const std::string, char>);
    static_assert(! ReadWriteForwardRange<const std::list<int>, int>);
    static_assert(! ReadWriteForwardRange<const std::vector<int>, int>);

    static_assert(ReadableBidirectionalRange<std::string, char>);
    static_assert(ReadableBidirectionalRange<std::list<int>, int>);
    static_assert(ReadableBidirectionalRange<std::vector<int>, int>);
    static_assert(ReadableBidirectionalRange<const std::string, char>);
    static_assert(ReadableBidirectionalRange<const std::list<int>, int>);
    static_assert(ReadableBidirectionalRange<const std::vector<int>, int>);

    static_assert(WritableBidirectionalRange<std::string, char>);
    static_assert(WritableBidirectionalRange<std::list<int>, int>);
    static_assert(WritableBidirectionalRange<std::vector<int>, int>);
    static_assert(! WritableBidirectionalRange<const std::string, char>);
    static_assert(! WritableBidirectionalRange<const std::list<int>, int>);
    static_assert(! WritableBidirectionalRange<const std::vector<int>, int>);

    static_assert(ReadWriteBidirectionalRange<std::string, char>);
    static_assert(ReadWriteBidirectionalRange<std::list<int>, int>);
    static_assert(ReadWriteBidirectionalRange<std::vector<int>, int>);
    static_assert(! ReadWriteBidirectionalRange<const std::string, char>);
    static_assert(! ReadWriteBidirectionalRange<const std::list<int>, int>);
    static_assert(! ReadWriteBidirectionalRange<const std::vector<int>, int>);

    static_assert(ReadableRandomAccessRange<std::string, char>);
    static_assert(! ReadableRandomAccessRange<std::list<int>, int>);
    static_assert(ReadableRandomAccessRange<std::vector<int>, int>);
    static_assert(ReadableRandomAccessRange<const std::string, char>);
    static_assert(! ReadableRandomAccessRange<const std::list<int>, int>);
    static_assert(ReadableRandomAccessRange<const std::vector<int>, int>);

    static_assert(WritableRandomAccessRange<std::string, char>);
    static_assert(! WritableRandomAccessRange<std::list<int>, int>);
    static_assert(WritableRandomAccessRange<std::vector<int>, int>);
    static_assert(! WritableRandomAccessRange<const std::string, char>);
    static_assert(! WritableRandomAccessRange<const std::list<int>, int>);
    static_assert(! WritableRandomAccessRange<const std::vector<int>, int>);

    static_assert(ReadWriteRandomAccessRange<std::string, char>);
    static_assert(! ReadWriteRandomAccessRange<std::list<int>, int>);
    static_assert(ReadWriteRandomAccessRange<std::vector<int>, int>);
    static_assert(! ReadWriteRandomAccessRange<const std::string, char>);
    static_assert(! ReadWriteRandomAccessRange<const std::list<int>, int>);
    static_assert(! ReadWriteRandomAccessRange<const std::vector<int>, int>);

    static_assert(ReadableContiguousRange<std::string, char>);
    static_assert(! ReadableContiguousRange<std::list<int>, int>);
    static_assert(ReadableContiguousRange<std::vector<int>, int>);
    static_assert(ReadableContiguousRange<const std::string, char>);
    static_assert(! ReadableContiguousRange<const std::list<int>, int>);
    static_assert(ReadableContiguousRange<const std::vector<int>, int>);

    static_assert(WritableContiguousRange<std::string, char>);
    static_assert(! WritableContiguousRange<std::list<int>, int>);
    static_assert(WritableContiguousRange<std::vector<int>, int>);
    static_assert(! WritableContiguousRange<const std::string, char>);
    static_assert(! WritableContiguousRange<const std::list<int>, int>);
    static_assert(! WritableContiguousRange<const std::vector<int>, int>);

    static_assert(ReadWriteContiguousRange<std::string, char>);
    static_assert(! ReadWriteContiguousRange<std::list<int>, int>);
    static_assert(ReadWriteContiguousRange<std::vector<int>, int>);
    static_assert(! ReadWriteContiguousRange<const std::string, char>);
    static_assert(! ReadWriteContiguousRange<const std::list<int>, int>);
    static_assert(! ReadWriteContiguousRange<const std::vector<int>, int>);

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

void test_rs_core_global_as_range() {

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

void test_rs_core_global_sorted_range() {

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
