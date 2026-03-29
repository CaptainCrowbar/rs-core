#include "rs-core/range.hpp"
#include "rs-core/unit-test.hpp"
#include <algorithm>
#include <concepts>
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

void test_rs_core_range_concepts() {

    TEST((ReadableRange                  <std::string,                     char>));
    TEST((ReadableRange                  <std::string_view,                char>));
    TEST((ReadableRange                  <std::list<int>,                  int>));
    TEST((ReadableRange                  <std::vector<int>,                int>));
    TEST((ReadableRange                  <std::vector<std::string>,        std::string>));
    TEST((ReadableRange                  <std::vector<std::string>,        std::string_view>));
    TEST((! ReadableRange                <std::vector<std::string>,        const char*>));
    TEST((ReadableRange                  <const std::string,               char>));
    TEST((ReadableRange                  <const std::string_view,          char>));
    TEST((ReadableRange                  <const std::list<int>,            int>));
    TEST((ReadableRange                  <const std::vector<int>,          int>));
    TEST((ReadableRange                  <const std::vector<std::string>,  std::string>));
    TEST((ReadableRange                  <const std::vector<std::string>,  std::string_view>));
    TEST((! ReadableRange                <const std::vector<std::string>,  const char*>));
    TEST((! ReadableRange                <std::string,                     int*>));
    TEST((! ReadableRange                <std::string_view,                int*>));
    TEST((! ReadableRange                <std::vector<int>,                int*>));

    TEST((WritableRange                  <std::string,                     char>));
    TEST((! WritableRange                <std::string_view,                char>));
    TEST((WritableRange                  <std::list<int>,                  int>));
    TEST((WritableRange                  <std::vector<int>,                int>));
    TEST((WritableRange                  <std::vector<std::string>,        std::string>));
    TEST((WritableRange                  <std::vector<std::string>,        std::string_view>));
    TEST((WritableRange                  <std::vector<std::string>,        const char*>));
    TEST((! WritableRange                <const std::string,               char>));
    TEST((! WritableRange                <const std::string_view,          char>));
    TEST((! WritableRange                <const std::list<int>,            int>));
    TEST((! WritableRange                <const std::vector<int>,          int>));
    TEST((! WritableRange                <const std::vector<std::string>,  std::string>));
    TEST((! WritableRange                <const std::vector<std::string>,  std::string_view>));
    TEST((! WritableRange                <const std::vector<std::string>,  const char*>));
    TEST((! WritableRange                <std::string,                     int*>));
    TEST((! WritableRange                <std::string_view,                int*>));
    TEST((! WritableRange                <std::vector<int>,                int*>));

    TEST((ReadWriteRange                 <std::string,                     char>));
    TEST((! ReadWriteRange               <std::string_view,                char>));
    TEST((ReadWriteRange                 <std::list<int>,                  int>));
    TEST((ReadWriteRange                 <std::vector<int>,                int>));
    TEST((ReadWriteRange                 <std::vector<std::string>,        std::string>));
    TEST((ReadWriteRange                 <std::vector<std::string>,        std::string_view>));
    TEST((! ReadWriteRange               <std::vector<std::string>,        const char*>));
    TEST((! ReadWriteRange               <const std::string,               char>));
    TEST((! ReadWriteRange               <const std::string_view,          char>));
    TEST((! ReadWriteRange               <const std::list<int>,            int>));
    TEST((! ReadWriteRange               <const std::vector<int>,          int>));
    TEST((! ReadWriteRange               <const std::vector<std::string>,  std::string>));
    TEST((! ReadWriteRange               <const std::vector<std::string>,  std::string_view>));
    TEST((! ReadWriteRange               <const std::vector<std::string>,  const char*>));
    TEST((! ReadWriteRange               <std::string,                     int*>));
    TEST((! ReadWriteRange               <std::string_view,                int*>));
    TEST((! ReadWriteRange               <std::vector<int>,                int*>));

    TEST((ReadableForwardRange           <std::string,                     char>));
    TEST((ReadableForwardRange           <std::list<int>,                  int>));
    TEST((ReadableForwardRange           <std::vector<int>,                int>));
    TEST((ReadableForwardRange           <const std::string,               char>));
    TEST((ReadableForwardRange           <const std::list<int>,            int>));
    TEST((ReadableForwardRange           <const std::vector<int>,          int>));

    TEST((WritableForwardRange           <std::string,                     char>));
    TEST((WritableForwardRange           <std::list<int>,                  int>));
    TEST((WritableForwardRange           <std::vector<int>,                int>));
    TEST((! WritableForwardRange         <const std::string,               char>));
    TEST((! WritableForwardRange         <const std::list<int>,            int>));
    TEST((! WritableForwardRange         <const std::vector<int>,          int>));

    TEST((ReadWriteForwardRange          <std::string,                     char>));
    TEST((ReadWriteForwardRange          <std::list<int>,                  int>));
    TEST((ReadWriteForwardRange          <std::vector<int>,                int>));
    TEST((! ReadWriteForwardRange        <const std::string,               char>));
    TEST((! ReadWriteForwardRange        <const std::list<int>,            int>));
    TEST((! ReadWriteForwardRange        <const std::vector<int>,          int>));

    TEST((ReadableBidirectionalRange     <std::string,                     char>));
    TEST((ReadableBidirectionalRange     <std::list<int>,                  int>));
    TEST((ReadableBidirectionalRange     <std::vector<int>,                int>));
    TEST((ReadableBidirectionalRange     <const std::string,               char>));
    TEST((ReadableBidirectionalRange     <const std::list<int>,            int>));
    TEST((ReadableBidirectionalRange     <const std::vector<int>,          int>));

    TEST((WritableBidirectionalRange     <std::string,                     char>));
    TEST((WritableBidirectionalRange     <std::list<int>,                  int>));
    TEST((WritableBidirectionalRange     <std::vector<int>,                int>));
    TEST((! WritableBidirectionalRange   <const std::string,               char>));
    TEST((! WritableBidirectionalRange   <const std::list<int>,            int>));
    TEST((! WritableBidirectionalRange   <const std::vector<int>,          int>));

    TEST((ReadWriteBidirectionalRange    <std::string,                     char>));
    TEST((ReadWriteBidirectionalRange    <std::list<int>,                  int>));
    TEST((ReadWriteBidirectionalRange    <std::vector<int>,                int>));
    TEST((! ReadWriteBidirectionalRange  <const std::string,               char>));
    TEST((! ReadWriteBidirectionalRange  <const std::list<int>,            int>));
    TEST((! ReadWriteBidirectionalRange  <const std::vector<int>,          int>));

    TEST((ReadableRandomAccessRange      <std::string,                     char>));
    TEST((! ReadableRandomAccessRange    <std::list<int>,                  int>));
    TEST((ReadableRandomAccessRange      <std::vector<int>,                int>));
    TEST((ReadableRandomAccessRange      <const std::string,               char>));
    TEST((! ReadableRandomAccessRange    <const std::list<int>,            int>));
    TEST((ReadableRandomAccessRange      <const std::vector<int>,          int>));

    TEST((WritableRandomAccessRange      <std::string,                     char>));
    TEST((! WritableRandomAccessRange    <std::list<int>,                  int>));
    TEST((WritableRandomAccessRange      <std::vector<int>,                int>));
    TEST((! WritableRandomAccessRange    <const std::string,               char>));
    TEST((! WritableRandomAccessRange    <const std::list<int>,            int>));
    TEST((! WritableRandomAccessRange    <const std::vector<int>,          int>));

    TEST((ReadWriteRandomAccessRange     <std::string,                     char>));
    TEST((! ReadWriteRandomAccessRange   <std::list<int>,                  int>));
    TEST((ReadWriteRandomAccessRange     <std::vector<int>,                int>));
    TEST((! ReadWriteRandomAccessRange   <const std::string,               char>));
    TEST((! ReadWriteRandomAccessRange   <const std::list<int>,            int>));
    TEST((! ReadWriteRandomAccessRange   <const std::vector<int>,          int>));

    TEST((ReadableContiguousRange        <std::string,                     char>));
    TEST((! ReadableContiguousRange      <std::list<int>,                  int>));
    TEST((ReadableContiguousRange        <std::vector<int>,                int>));
    TEST((ReadableContiguousRange        <const std::string,               char>));
    TEST((! ReadableContiguousRange      <const std::list<int>,            int>));
    TEST((ReadableContiguousRange        <const std::vector<int>,          int>));

    TEST((WritableContiguousRange        <std::string,                     char>));
    TEST((! WritableContiguousRange      <std::list<int>,                  int>));
    TEST((WritableContiguousRange        <std::vector<int>,                int>));
    TEST((! WritableContiguousRange      <const std::string,               char>));
    TEST((! WritableContiguousRange      <const std::list<int>,            int>));
    TEST((! WritableContiguousRange      <const std::vector<int>,          int>));

    TEST((ReadWriteContiguousRange       <std::string,                     char>));
    TEST((! ReadWriteContiguousRange     <std::list<int>,                  int>));
    TEST((ReadWriteContiguousRange       <std::vector<int>,                int>));
    TEST((! ReadWriteContiguousRange     <const std::string,               char>));
    TEST((! ReadWriteContiguousRange     <const std::list<int>,            int>));
    TEST((! ReadWriteContiguousRange     <const std::vector<int>,          int>));

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
