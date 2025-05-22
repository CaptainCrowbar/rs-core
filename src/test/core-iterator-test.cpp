#include "rs-core/core.hpp"
#include "rs-core/unit-test.hpp"
#include <algorithm>
#include <compare>
#include <concepts>
#include <cstddef>
#include <format>
#include <iterator>
#include <ranges>
#include <vector>

namespace rs = std::ranges;
using namespace RS;

class Output:
public OutputIterator<Output> {
public:
    Output() = default;
    explicit Output(std::vector<int>& v): vec_(&v) {}
    void operator=(int x) { vec_->push_back(x); }
private:
    std::vector<int>* vec_;
};

class Input:
public InputIterator<Input, const int> {
public:
    Input() = default;
    explicit Input(const std::vector<int>& v, std::size_t i): ptr_(v.data() + i) {}
    const int& operator*() const { return *ptr_; }
    Input& operator++() { ++ptr_; return *this; }
    bool operator==(const Input& i) const { return ptr_ == i.ptr_; }
private:
    const int* ptr_;
};

class Forward:
public ForwardIterator<Forward, const int> {
public:
    Forward() = default;
    explicit Forward(const std::vector<int>& v, std::size_t i): ptr_(v.data() + i) {}
    const int& operator*() const { return *ptr_; }
    Forward& operator++() { ++ptr_; return *this; }
    bool operator==(const Forward& i) const { return ptr_ == i.ptr_; }
private:
    const int* ptr_;
};

class Bidirectional:
public BidirectionalIterator<Bidirectional, const int> {
public:
    Bidirectional() = default;
    explicit Bidirectional(const std::vector<int>& v, std::size_t i): ptr_(v.data() + i) {}
    const int& operator*() const { return *ptr_; }
    Bidirectional& operator++() { ++ptr_; return *this; }
    Bidirectional& operator--() { --ptr_; return *this; }
    bool operator==(const Bidirectional& i) const { return ptr_ == i.ptr_; }
private:
    const int* ptr_;
};

class Random:
public RandomAccessIterator<Random, const int> {
public:
    Random() = default;
    explicit Random(const std::vector<int>& v, std::size_t i): ptr_(v.data() + i) {}
    const int& operator*() const { return *ptr_; }
    Random& operator+=(std::ptrdiff_t n) { ptr_ += n; return *this; }
    std::ptrdiff_t operator-(const Random& i) const { return ptr_ - i.ptr_; }
private:
    const int* ptr_;
};

class Contiguous:
public ContiguousIterator<Contiguous, const int> {
public:
    Contiguous() = default;
    explicit Contiguous(const std::vector<int>& v, std::size_t i): ptr_(v.data() + i) {}
    const int& operator*() const { return *ptr_; }
    Contiguous& operator+=(std::ptrdiff_t n) { ptr_ += n; return *this; }
    std::ptrdiff_t operator-(const Contiguous& i) const { return ptr_ - i.ptr_; }
private:
    const int* ptr_;
};

void test_rs_core_iterator_tags() {

    static_assert(std::same_as<std::iterator_traits<Output>::iterator_category, std::output_iterator_tag>);
    static_assert(std::same_as<std::iterator_traits<Input>::iterator_category, std::input_iterator_tag>);
    static_assert(std::same_as<std::iterator_traits<Forward>::iterator_category, std::forward_iterator_tag>);
    static_assert(std::same_as<std::iterator_traits<Bidirectional>::iterator_category, std::bidirectional_iterator_tag>);
    static_assert(std::same_as<std::iterator_traits<Random>::iterator_category, std::random_access_iterator_tag>);
    static_assert(std::same_as<std::iterator_traits<Contiguous>::iterator_category, std::contiguous_iterator_tag>);

}

void test_rs_core_iterator_output_iterators() {

    std::vector<int> v;
    auto o = Output(v);

    TRY(*o = 1);  TRY(++o);  TEST_EQUAL(std::format("{}", v), "[1]");
    TRY(*o = 2);  TRY(++o);  TEST_EQUAL(std::format("{}", v), "[1, 2]");
    TRY(*o = 3);  TRY(++o);  TEST_EQUAL(std::format("{}", v), "[1, 2, 3]");
    TRY(*o = 4);  TRY(o++);  TEST_EQUAL(std::format("{}", v), "[1, 2, 3, 4]");
    TRY(*o = 5);  TRY(o++);  TEST_EQUAL(std::format("{}", v), "[1, 2, 3, 4, 5]");
    TRY(*o = 6);  TRY(o++);  TEST_EQUAL(std::format("{}", v), "[1, 2, 3, 4, 5, 6]");

}

void test_rs_core_iterator_input_iterators() {

    std::vector<int> v {1, 2, 3, 4, 5};
    auto r = rs::subrange(Input(v, 0), Input(v, v.size()));
    TEST_EQUAL(std::format("{}", r), "[1, 2, 3, 4, 5]");
    Input i, j;

    TRY(i = r.begin());  TEST_EQUAL(*i, 1);
    TRY(++i);            TEST_EQUAL(*i, 2);
    TRY(i++);            TEST_EQUAL(*i, 3);

    TRY(i = r.begin());  TRY(j = r.begin());
    TRY(j = i);          TEST(i == j);
    TRY(++j);            TEST(i != j);

}

void test_rs_core_iterator_forward_iterators() {

    std::vector<int> v {1, 2, 3, 4, 5};
    auto r = rs::subrange(Forward(v, 0), Forward(v, v.size()));
    TEST_EQUAL(std::format("{}", r), "[1, 2, 3, 4, 5]");
    Forward i, j;

    TRY(i = r.begin());  TEST_EQUAL(*i, 1);
    TRY(++i);            TEST_EQUAL(*i, 2);
    TRY(i++);            TEST_EQUAL(*i, 3);

    TRY(i = r.begin());  TRY(j = r.begin());
    TRY(j = i);          TEST(i == j);
    TRY(++j);            TEST(i != j);

}

void test_rs_core_iterator_bidirectional_iterators() {

    std::vector<int> v {1, 2, 3, 4, 5};
    auto r = rs::subrange(Bidirectional(v, 0), Bidirectional(v, v.size()));
    TEST_EQUAL(std::format("{}", r), "[1, 2, 3, 4, 5]");
    Bidirectional i, j;

    TRY(i = r.begin());  TEST_EQUAL(*i, 1);
    TRY(++i);            TEST_EQUAL(*i, 2);
    TRY(i++);            TEST_EQUAL(*i, 3);
    TRY(--i);            TEST_EQUAL(*i, 2);
    TRY(i--);            TEST_EQUAL(*i, 1);

    TRY(i = r.begin());  TRY(j = r.begin());
    TRY(j = i);          TEST(i == j);
    TRY(++j);            TEST(i != j);

}

void test_rs_core_iterator_random_access_iterators() {

    std::vector<int> v {1, 2, 3, 4, 5};
    auto r = rs::subrange(Random(v, 0), Random(v, v.size()));
    TEST_EQUAL(std::format("{}", r), "[1, 2, 3, 4, 5]");
    Random i, j, k;
    auto n = 0z;

    (void)j;
    (void)k;
    (void)n;

    TRY(i = r.begin());  TEST_EQUAL(*i, 1);
    TRY(++i);            TEST_EQUAL(*i, 2);
    TRY(i++);            TEST_EQUAL(*i, 3);
    TRY(--i);            TEST_EQUAL(*i, 2);
    TRY(i--);            TEST_EQUAL(*i, 1);
    TRY(i += 2);         TEST_EQUAL(*i, 3);
    TRY(i -= 2);         TEST_EQUAL(*i, 1);
    TRY(j = i + 2);      TEST_EQUAL(*j, 3);
    TRY(k = j - 2);      TEST_EQUAL(*k, 1);
    TRY(n = k - i);      TEST_EQUAL(n, 0);
    TRY(n = j - i);      TEST_EQUAL(n, 2);
    TRY(n = i - j);      TEST_EQUAL(n, -2);

    TRY(i = r.begin());
    TRY(j = r.begin());

    TRY(j = i);  TEST(i == j);  TEST(i <= j);  TEST(i >= j);
    TRY(++j);    TEST(i != j);  TEST(i < j);   TEST(j > i);

    TRY(i = r.begin());
    TEST_EQUAL(i[0], 1);
    TEST_EQUAL(i[1], 2);
    TEST_EQUAL(i[2], 3);
    TEST_EQUAL(i[3], 4);
    TEST_EQUAL(i[4], 5);

}

void test_rs_core_iterator_contiguous_iterators() {

    std::vector<int> v {1, 2, 3, 4, 5};
    auto r = rs::subrange(Contiguous(v, 0), Contiguous(v, v.size()));
    TEST_EQUAL(std::format("{}", r), "[1, 2, 3, 4, 5]");
    Contiguous i, j, k;
    auto n = 0z;

    (void)j;
    (void)k;
    (void)n;

    TRY(i = r.begin());  TEST_EQUAL(*i, 1);
    TRY(++i);            TEST_EQUAL(*i, 2);
    TRY(i++);            TEST_EQUAL(*i, 3);
    TRY(--i);            TEST_EQUAL(*i, 2);
    TRY(i--);            TEST_EQUAL(*i, 1);
    TRY(i += 2);         TEST_EQUAL(*i, 3);
    TRY(i -= 2);         TEST_EQUAL(*i, 1);
    TRY(j = i + 2);      TEST_EQUAL(*j, 3);
    TRY(k = j - 2);      TEST_EQUAL(*k, 1);
    TRY(n = k - i);      TEST_EQUAL(n, 0);
    TRY(n = j - i);      TEST_EQUAL(n, 2);
    TRY(n = i - j);      TEST_EQUAL(n, -2);

    TRY(i = r.begin());
    TRY(j = r.begin());

    TRY(j = i);  TEST(i == j);  TEST(i <= j);  TEST(i >= j);
    TRY(++j);    TEST(i != j);  TEST(i < j);   TEST(j > i);

    TRY(i = r.begin());
    TEST_EQUAL(i[0], 1);
    TEST_EQUAL(i[1], 2);
    TEST_EQUAL(i[2], 3);
    TEST_EQUAL(i[3], 4);
    TEST_EQUAL(i[4], 5);

}
