#include "rs-core/iterator.hpp"
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
public Iterator<Output, int, std::output_iterator_tag> {
public:
    Output() = default;
    explicit Output(std::vector<int>& v): vec_(&v) {}
    void operator=(int x) { vec_->push_back(x); }
private:
    std::vector<int>* vec_;
};

class Input:
public Iterator<Input, const int, std::input_iterator_tag> {
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
public Iterator<Forward, const int, std::forward_iterator_tag> {
public:
    Forward() = default;
    explicit Forward(const std::vector<int>& v, std::size_t i): ptr_(v.data() + i) {}
    const int& operator*() const { return *ptr_; }
    Forward& operator++() { ++ptr_; return *this; }
    bool operator==(const Forward& i) const { return ptr_ == i.ptr_; }
private:
    const int* ptr_;
};

class ForwardMutable:
public Iterator<ForwardMutable, int, std::forward_iterator_tag> {
public:
    ForwardMutable() = default;
    explicit ForwardMutable(std::vector<int>& v, std::size_t i): ptr_(v.data() + i) {}
    int& operator*() const { return *ptr_; }
    ForwardMutable& operator++() { ++ptr_; return *this; }
    bool operator==(const ForwardMutable& i) const { return ptr_ == i.ptr_; }
private:
    int* ptr_;
};

class Bidirectional:
public Iterator<Bidirectional, const int, std::bidirectional_iterator_tag> {
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

class BidirectionalMutable:
public Iterator<BidirectionalMutable, int, std::bidirectional_iterator_tag> {
public:
    BidirectionalMutable() = default;
    explicit BidirectionalMutable(std::vector<int>& v, std::size_t i): ptr_(v.data() + i) {}
    int& operator*() const { return *ptr_; }
    BidirectionalMutable& operator++() { ++ptr_; return *this; }
    BidirectionalMutable& operator--() { --ptr_; return *this; }
    bool operator==(const BidirectionalMutable& i) const { return ptr_ == i.ptr_; }
private:
    int* ptr_;
};

class RandomAccess:
public Iterator<RandomAccess, const int, std::random_access_iterator_tag> {
public:
    RandomAccess() = default;
    explicit RandomAccess(const std::vector<int>& v, std::size_t i): ptr_(v.data() + i) {}
    const int& operator*() const { return *ptr_; }
    RandomAccess& operator+=(std::ptrdiff_t n) { ptr_ += n; return *this; }
    std::ptrdiff_t operator-(const RandomAccess& i) const { return ptr_ - i.ptr_; }
private:
    const int* ptr_;
};

class RandomAccessMutable:
public Iterator<RandomAccessMutable, int, std::random_access_iterator_tag> {
public:
    RandomAccessMutable() = default;
    explicit RandomAccessMutable(std::vector<int>& v, std::size_t i): ptr_(v.data() + i) {}
    int& operator*() const { return *ptr_; }
    RandomAccessMutable& operator+=(std::ptrdiff_t n) { ptr_ += n; return *this; }
    std::ptrdiff_t operator-(const RandomAccessMutable& i) const { return ptr_ - i.ptr_; }
private:
    int* ptr_;
};

class Contiguous:
public Iterator<Contiguous, const int, std::contiguous_iterator_tag> {
public:
    Contiguous() = default;
    explicit Contiguous(const std::vector<int>& v, std::size_t i): ptr_(v.data() + i) {}
    const int& operator*() const { return *ptr_; }
    Contiguous& operator+=(std::ptrdiff_t n) { ptr_ += n; return *this; }
    std::ptrdiff_t operator-(const Contiguous& i) const { return ptr_ - i.ptr_; }
private:
    const int* ptr_;
};

class ContiguousMutable:
public Iterator<ContiguousMutable, int, std::contiguous_iterator_tag> {
public:
    ContiguousMutable() = default;
    explicit ContiguousMutable(std::vector<int>& v, std::size_t i): ptr_(v.data() + i) {}
    int& operator*() const { return *ptr_; }
    ContiguousMutable& operator+=(std::ptrdiff_t n) { ptr_ += n; return *this; }
    std::ptrdiff_t operator-(const ContiguousMutable& i) const { return ptr_ - i.ptr_; }
private:
    int* ptr_;
};

void test_rs_core_iterator_tags() {

    static_assert(std::same_as<std::iterator_traits<Output>::iterator_category,         std::output_iterator_tag>);
    static_assert(std::same_as<std::iterator_traits<Input>::iterator_category,          std::input_iterator_tag>);
    static_assert(std::same_as<std::iterator_traits<Forward>::iterator_category,        std::forward_iterator_tag>);
    static_assert(std::same_as<std::iterator_traits<Bidirectional>::iterator_category,  std::bidirectional_iterator_tag>);
    static_assert(std::same_as<std::iterator_traits<RandomAccess>::iterator_category,         std::random_access_iterator_tag>);
    static_assert(std::same_as<std::iterator_traits<Contiguous>::iterator_category,     std::contiguous_iterator_tag>);

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

    auto rmut = rs::subrange(ForwardMutable(v, 0), ForwardMutable(v, v.size()));
    for (auto& x: rmut) {
        x *= 10;
    }
    TEST_EQUAL(std::format("{}", v), "[10, 20, 30, 40, 50]");

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

    auto rmut = rs::subrange(BidirectionalMutable(v, 0), BidirectionalMutable(v, v.size()));
    for (auto& x: rmut) {
        x *= 10;
    }
    TEST_EQUAL(std::format("{}", v), "[10, 20, 30, 40, 50]");

}

void test_rs_core_iterator_random_access_iterators() {

    std::vector<int> v {1, 2, 3, 4, 5};
    auto r = rs::subrange(RandomAccess(v, 0), RandomAccess(v, v.size()));
    TEST_EQUAL(std::format("{}", r), "[1, 2, 3, 4, 5]");
    RandomAccess i, j, k;
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

    auto rmut = rs::subrange(RandomAccessMutable(v, 0), RandomAccessMutable(v, v.size()));
    for (auto& x: rmut) {
        x *= 10;
    }
    TEST_EQUAL(std::format("{}", v), "[10, 20, 30, 40, 50]");

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

    auto rmut = rs::subrange(ContiguousMutable(v, 0), ContiguousMutable(v, v.size()));
    for (auto& x: rmut) {
        x *= 10;
    }
    TEST_EQUAL(std::format("{}", v), "[10, 20, 30, 40, 50]");

}
