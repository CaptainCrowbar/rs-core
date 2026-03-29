#include "rs-core/iterator.hpp"
#include "rs-core/unit-test.hpp"
#include <algorithm>
#include <compare>
#include <concepts>
#include <cstddef>
#include <format>
#include <iterator>
#include <list>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

namespace rs = std::ranges;
using namespace RS;

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

class Output:
public Iterator<Output, int, std::output_iterator_tag> {
public:
    Output() = default;
    explicit Output(std::vector<int>& v): vec_(&v) {}
    void operator=(int x) { vec_->push_back(x); }
private:
    std::vector<int>* vec_;
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

void test_rs_core_iterator_concepts() {

    TEST((ReadableIterator                  <std::string::iterator,                     char>));
    TEST((ReadableIterator                  <std::string_view::iterator,                char>));
    TEST((ReadableIterator                  <std::list<int>::iterator,                  int>));
    TEST((ReadableIterator                  <std::vector<int>::iterator,                int>));
    TEST((ReadableIterator                  <std::vector<std::string>::iterator,        std::string>));
    TEST((ReadableIterator                  <std::vector<std::string>::iterator,        std::string_view>));
    TEST((! ReadableIterator                <std::vector<std::string>::iterator,        const char*>));
    TEST((ReadableIterator                  <std::string::const_iterator,               char>));
    TEST((ReadableIterator                  <std::string_view::const_iterator,          char>));
    TEST((ReadableIterator                  <std::list<int>::const_iterator,            int>));
    TEST((ReadableIterator                  <std::vector<int>::const_iterator,          int>));
    TEST((ReadableIterator                  <std::vector<std::string>::const_iterator,  std::string>));
    TEST((ReadableIterator                  <std::vector<std::string>::const_iterator,  std::string_view>));
    TEST((! ReadableIterator                <std::vector<std::string>::const_iterator,  const char*>));
    TEST((! ReadableIterator                <std::string::iterator,                     int*>));
    TEST((! ReadableIterator                <std::string_view::iterator,                int*>));
    TEST((! ReadableIterator                <std::vector<int>::iterator,                int*>));

    TEST((WritableIterator                  <std::string::iterator,                     char>));
    TEST((! WritableIterator                <std::string_view::iterator,                char>));
    TEST((WritableIterator                  <std::list<int>::iterator,                  int>));
    TEST((WritableIterator                  <std::vector<int>::iterator,                int>));
    TEST((WritableIterator                  <std::vector<std::string>::iterator,        std::string>));
    TEST((WritableIterator                  <std::vector<std::string>::iterator,        std::string_view>));
    TEST((WritableIterator                  <std::vector<std::string>::iterator,        const char*>));
    TEST((! WritableIterator                <std::string::const_iterator,               char>));
    TEST((! WritableIterator                <std::string_view::const_iterator,          char>));
    TEST((! WritableIterator                <std::list<int>::const_iterator,            int>));
    TEST((! WritableIterator                <std::vector<int>::const_iterator,          int>));
    TEST((! WritableIterator                <std::vector<std::string>::const_iterator,  std::string>));
    TEST((! WritableIterator                <std::vector<std::string>::const_iterator,  std::string_view>));
    TEST((! WritableIterator                <std::vector<std::string>::const_iterator,  const char*>));
    TEST((! WritableIterator                <std::string::iterator,                     int*>));
    TEST((! WritableIterator                <std::string_view::iterator,                int*>));
    TEST((! WritableIterator                <std::vector<int>::iterator,                int*>));

    TEST((ReadWriteIterator                 <std::string::iterator,                     char>));
    TEST((! ReadWriteIterator               <std::string_view::iterator,                char>));
    TEST((ReadWriteIterator                 <std::list<int>::iterator,                  int>));
    TEST((ReadWriteIterator                 <std::vector<int>::iterator,                int>));
    TEST((ReadWriteIterator                 <std::vector<std::string>::iterator,        std::string>));
    TEST((ReadWriteIterator                 <std::vector<std::string>::iterator,        std::string_view>));
    TEST((! ReadWriteIterator               <std::vector<std::string>::iterator,        const char*>));
    TEST((! ReadWriteIterator               <std::string::const_iterator,               char>));
    TEST((! ReadWriteIterator               <std::string_view::const_iterator,          char>));
    TEST((! ReadWriteIterator               <std::list<int>::const_iterator,            int>));
    TEST((! ReadWriteIterator               <std::vector<int>::const_iterator,          int>));
    TEST((! ReadWriteIterator               <std::vector<std::string>::const_iterator,  std::string>));
    TEST((! ReadWriteIterator               <std::vector<std::string>::const_iterator,  std::string_view>));
    TEST((! ReadWriteIterator               <std::vector<std::string>::const_iterator,  const char*>));
    TEST((! ReadWriteIterator               <std::string::iterator,                     int*>));
    TEST((! ReadWriteIterator               <std::string_view::iterator,                int*>));
    TEST((! ReadWriteIterator               <std::vector<int>::iterator,                int*>));

    TEST((ReadableForwardIterator           <std::string::iterator,                     char>));
    TEST((ReadableForwardIterator           <std::list<int>::iterator,                  int>));
    TEST((ReadableForwardIterator           <std::vector<int>::iterator,                int>));
    TEST((ReadableForwardIterator           <std::string::const_iterator,               char>));
    TEST((ReadableForwardIterator           <std::list<int>::const_iterator,            int>));
    TEST((ReadableForwardIterator           <std::vector<int>::const_iterator,          int>));

    TEST((WritableForwardIterator           <std::string::iterator,                     char>));
    TEST((WritableForwardIterator           <std::list<int>::iterator,                  int>));
    TEST((WritableForwardIterator           <std::vector<int>::iterator,                int>));
    TEST((! WritableForwardIterator         <std::string::const_iterator,               char>));
    TEST((! WritableForwardIterator         <std::list<int>::const_iterator,            int>));
    TEST((! WritableForwardIterator         <std::vector<int>::const_iterator,          int>));

    TEST((ReadWriteForwardIterator          <std::string::iterator,                     char>));
    TEST((ReadWriteForwardIterator          <std::list<int>::iterator,                  int>));
    TEST((ReadWriteForwardIterator          <std::vector<int>::iterator,                int>));
    TEST((! ReadWriteForwardIterator        <std::string::const_iterator,               char>));
    TEST((! ReadWriteForwardIterator        <std::list<int>::const_iterator,            int>));
    TEST((! ReadWriteForwardIterator        <std::vector<int>::const_iterator,          int>));

    TEST((ReadableBidirectionalIterator     <std::string::iterator,                     char>));
    TEST((ReadableBidirectionalIterator     <std::list<int>::iterator,                  int>));
    TEST((ReadableBidirectionalIterator     <std::vector<int>::iterator,                int>));
    TEST((ReadableBidirectionalIterator     <std::string::const_iterator,               char>));
    TEST((ReadableBidirectionalIterator     <std::list<int>::const_iterator,            int>));
    TEST((ReadableBidirectionalIterator     <std::vector<int>::const_iterator,          int>));

    TEST((WritableBidirectionalIterator     <std::string::iterator,                     char>));
    TEST((WritableBidirectionalIterator     <std::list<int>::iterator,                  int>));
    TEST((WritableBidirectionalIterator     <std::vector<int>::iterator,                int>));
    TEST((! WritableBidirectionalIterator   <std::string::const_iterator,               char>));
    TEST((! WritableBidirectionalIterator   <std::list<int>::const_iterator,            int>));
    TEST((! WritableBidirectionalIterator   <std::vector<int>::const_iterator,          int>));

    TEST((ReadWriteBidirectionalIterator    <std::string::iterator,                     char>));
    TEST((ReadWriteBidirectionalIterator    <std::list<int>::iterator,                  int>));
    TEST((ReadWriteBidirectionalIterator    <std::vector<int>::iterator,                int>));
    TEST((! ReadWriteBidirectionalIterator  <std::string::const_iterator,               char>));
    TEST((! ReadWriteBidirectionalIterator  <std::list<int>::const_iterator,            int>));
    TEST((! ReadWriteBidirectionalIterator  <std::vector<int>::const_iterator,          int>));

    TEST((ReadableRandomAccessIterator      <std::string::iterator,                     char>));
    TEST((! ReadableRandomAccessIterator    <std::list<int>::iterator,                  int>));
    TEST((ReadableRandomAccessIterator      <std::vector<int>::iterator,                int>));
    TEST((ReadableRandomAccessIterator      <std::string::const_iterator,               char>));
    TEST((! ReadableRandomAccessIterator    <std::list<int>::const_iterator,            int>));
    TEST((ReadableRandomAccessIterator      <std::vector<int>::const_iterator,          int>));

    TEST((WritableRandomAccessIterator      <std::string::iterator,                     char>));
    TEST((! WritableRandomAccessIterator    <std::list<int>::iterator,                  int>));
    TEST((WritableRandomAccessIterator      <std::vector<int>::iterator,                int>));
    TEST((! WritableRandomAccessIterator    <std::string::const_iterator,               char>));
    TEST((! WritableRandomAccessIterator    <std::list<int>::const_iterator,            int>));
    TEST((! WritableRandomAccessIterator    <std::vector<int>::const_iterator,          int>));

    TEST((ReadWriteRandomAccessIterator     <std::string::iterator,                     char>));
    TEST((! ReadWriteRandomAccessIterator   <std::list<int>::iterator,                  int>));
    TEST((ReadWriteRandomAccessIterator     <std::vector<int>::iterator,                int>));
    TEST((! ReadWriteRandomAccessIterator   <std::string::const_iterator,               char>));
    TEST((! ReadWriteRandomAccessIterator   <std::list<int>::const_iterator,            int>));
    TEST((! ReadWriteRandomAccessIterator   <std::vector<int>::const_iterator,          int>));

    TEST((ReadableContiguousIterator        <std::string::iterator,                     char>));
    TEST((! ReadableContiguousIterator      <std::list<int>::iterator,                  int>));
    TEST((ReadableContiguousIterator        <std::vector<int>::iterator,                int>));
    TEST((ReadableContiguousIterator        <std::string::const_iterator,               char>));
    TEST((! ReadableContiguousIterator      <std::list<int>::const_iterator,            int>));
    TEST((ReadableContiguousIterator        <std::vector<int>::const_iterator,          int>));

    TEST((WritableContiguousIterator        <std::string::iterator,                     char>));
    TEST((! WritableContiguousIterator      <std::list<int>::iterator,                  int>));
    TEST((WritableContiguousIterator        <std::vector<int>::iterator,                int>));
    TEST((! WritableContiguousIterator      <std::string::const_iterator,               char>));
    TEST((! WritableContiguousIterator      <std::list<int>::const_iterator,            int>));
    TEST((! WritableContiguousIterator      <std::vector<int>::const_iterator,          int>));

    TEST((ReadWriteContiguousIterator       <std::string::iterator,                     char>));
    TEST((! ReadWriteContiguousIterator     <std::list<int>::iterator,                  int>));
    TEST((ReadWriteContiguousIterator       <std::vector<int>::iterator,                int>));
    TEST((! ReadWriteContiguousIterator     <std::string::const_iterator,               char>));
    TEST((! ReadWriteContiguousIterator     <std::list<int>::const_iterator,            int>));
    TEST((! ReadWriteContiguousIterator     <std::vector<int>::const_iterator,          int>));

    TEST((ReadableIterator                  <Input,                                     int>));
    TEST((ReadableIterator                  <Forward,                                   int>));
    TEST((ReadableIterator                  <Bidirectional,                             int>));
    TEST((ReadableIterator                  <RandomAccess,                              int>));
    TEST((ReadableIterator                  <Contiguous,                                int>));
    TEST((! ReadableIterator                <Output,                                    int>));
    TEST((ReadableIterator                  <ForwardMutable,                            int>));
    TEST((ReadableIterator                  <BidirectionalMutable,                      int>));
    TEST((ReadableIterator                  <RandomAccessMutable,                       int>));
    TEST((ReadableIterator                  <ContiguousMutable,                         int>));

    TEST((! ReadableForwardIterator         <Input,                                     int>));
    TEST((ReadableForwardIterator           <Forward,                                   int>));
    TEST((ReadableForwardIterator           <Bidirectional,                             int>));
    TEST((ReadableForwardIterator           <RandomAccess,                              int>));
    TEST((ReadableForwardIterator           <Contiguous,                                int>));
    TEST((! ReadableForwardIterator         <Output,                                    int>));
    TEST((ReadableForwardIterator           <ForwardMutable,                            int>));
    TEST((ReadableForwardIterator           <BidirectionalMutable,                      int>));
    TEST((ReadableForwardIterator           <RandomAccessMutable,                       int>));
    TEST((ReadableForwardIterator           <ContiguousMutable,                         int>));

    TEST((! ReadableBidirectionalIterator   <Input,                                     int>));
    TEST((! ReadableBidirectionalIterator   <Forward,                                   int>));
    TEST((ReadableBidirectionalIterator     <Bidirectional,                             int>));
    TEST((ReadableBidirectionalIterator     <RandomAccess,                              int>));
    TEST((ReadableBidirectionalIterator     <Contiguous,                                int>));
    TEST((! ReadableBidirectionalIterator   <Output,                                    int>));
    TEST((! ReadableBidirectionalIterator   <ForwardMutable,                            int>));
    TEST((ReadableBidirectionalIterator     <BidirectionalMutable,                      int>));
    TEST((ReadableBidirectionalIterator     <RandomAccessMutable,                       int>));
    TEST((ReadableBidirectionalIterator     <ContiguousMutable,                         int>));

    TEST((! ReadableRandomAccessIterator    <Input,                                     int>));
    TEST((! ReadableRandomAccessIterator    <Forward,                                   int>));
    TEST((! ReadableRandomAccessIterator    <Bidirectional,                             int>));
    TEST((ReadableRandomAccessIterator      <RandomAccess,                              int>));
    TEST((ReadableRandomAccessIterator      <Contiguous,                                int>));
    TEST((! ReadableRandomAccessIterator    <Output,                                    int>));
    TEST((! ReadableRandomAccessIterator    <ForwardMutable,                            int>));
    TEST((! ReadableRandomAccessIterator    <BidirectionalMutable,                      int>));
    TEST((ReadableRandomAccessIterator      <RandomAccessMutable,                       int>));
    TEST((ReadableRandomAccessIterator      <ContiguousMutable,                         int>));

    TEST((! ReadableContiguousIterator      <Input,                                     int>));
    TEST((! ReadableContiguousIterator      <Forward,                                   int>));
    TEST((! ReadableContiguousIterator      <Bidirectional,                             int>));
    TEST((! ReadableContiguousIterator      <RandomAccess,                              int>));
    TEST((ReadableContiguousIterator        <Contiguous,                                int>));
    TEST((! ReadableContiguousIterator      <Output,                                    int>));
    TEST((! ReadableContiguousIterator      <ForwardMutable,                            int>));
    TEST((! ReadableContiguousIterator      <BidirectionalMutable,                      int>));
    TEST((! ReadableContiguousIterator      <RandomAccessMutable,                       int>));
    TEST((ReadableContiguousIterator        <ContiguousMutable,                         int>));

    TEST((! WritableIterator                <Input,                                     int>));
    TEST((! WritableIterator                <Forward,                                   int>));
    TEST((! WritableIterator                <Bidirectional,                             int>));
    TEST((! WritableIterator                <RandomAccess,                              int>));
    TEST((! WritableIterator                <Contiguous,                                int>));
    TEST((WritableIterator                  <Output,                                    int>));
    TEST((WritableIterator                  <ForwardMutable,                            int>));
    TEST((WritableIterator                  <BidirectionalMutable,                      int>));
    TEST((WritableIterator                  <RandomAccessMutable,                       int>));
    TEST((WritableIterator                  <ContiguousMutable,                         int>));

    TEST((! WritableForwardIterator         <Input,                                     int>));
    TEST((! WritableForwardIterator         <Forward,                                   int>));
    TEST((! WritableForwardIterator         <Bidirectional,                             int>));
    TEST((! WritableForwardIterator         <RandomAccess,                              int>));
    TEST((! WritableForwardIterator         <Contiguous,                                int>));
    TEST((! WritableForwardIterator         <Output,                                    int>));
    TEST((WritableForwardIterator           <ForwardMutable,                            int>));
    TEST((WritableForwardIterator           <BidirectionalMutable,                      int>));
    TEST((WritableForwardIterator           <RandomAccessMutable,                       int>));
    TEST((WritableForwardIterator           <ContiguousMutable,                         int>));

    TEST((! WritableBidirectionalIterator   <Input,                                     int>));
    TEST((! WritableBidirectionalIterator   <Forward,                                   int>));
    TEST((! WritableBidirectionalIterator   <Bidirectional,                             int>));
    TEST((! WritableBidirectionalIterator   <RandomAccess,                              int>));
    TEST((! WritableBidirectionalIterator   <Contiguous,                                int>));
    TEST((! WritableBidirectionalIterator   <Output,                                    int>));
    TEST((! WritableBidirectionalIterator   <ForwardMutable,                            int>));
    TEST((WritableBidirectionalIterator     <BidirectionalMutable,                      int>));
    TEST((WritableBidirectionalIterator     <RandomAccessMutable,                       int>));
    TEST((WritableBidirectionalIterator     <ContiguousMutable,                         int>));

    TEST((! WritableRandomAccessIterator    <Input,                                     int>));
    TEST((! WritableRandomAccessIterator    <Forward,                                   int>));
    TEST((! WritableRandomAccessIterator    <Bidirectional,                             int>));
    TEST((! WritableRandomAccessIterator    <RandomAccess,                              int>));
    TEST((! WritableRandomAccessIterator    <Contiguous,                                int>));
    TEST((! WritableRandomAccessIterator    <Output,                                    int>));
    TEST((! WritableRandomAccessIterator    <ForwardMutable,                            int>));
    TEST((! WritableRandomAccessIterator    <BidirectionalMutable,                      int>));
    TEST((WritableRandomAccessIterator      <RandomAccessMutable,                       int>));
    TEST((WritableRandomAccessIterator      <ContiguousMutable,                         int>));

    TEST((! WritableContiguousIterator      <Input,                                     int>));
    TEST((! WritableContiguousIterator      <Forward,                                   int>));
    TEST((! WritableContiguousIterator      <Bidirectional,                             int>));
    TEST((! WritableContiguousIterator      <RandomAccess,                              int>));
    TEST((! WritableContiguousIterator      <Contiguous,                                int>));
    TEST((! WritableContiguousIterator      <Output,                                    int>));
    TEST((! WritableContiguousIterator      <ForwardMutable,                            int>));
    TEST((! WritableContiguousIterator      <BidirectionalMutable,                      int>));
    TEST((! WritableContiguousIterator      <RandomAccessMutable,                       int>));
    TEST((WritableContiguousIterator        <ContiguousMutable,                         int>));

    TEST((! ReadWriteIterator               <Input,                                     int>));
    TEST((! ReadWriteIterator               <Forward,                                   int>));
    TEST((! ReadWriteIterator               <Bidirectional,                             int>));
    TEST((! ReadWriteIterator               <RandomAccess,                              int>));
    TEST((! ReadWriteIterator               <Contiguous,                                int>));
    TEST((! ReadWriteIterator               <Output,                                    int>));
    TEST((ReadWriteIterator                 <ForwardMutable,                            int>));
    TEST((ReadWriteIterator                 <BidirectionalMutable,                      int>));
    TEST((ReadWriteIterator                 <RandomAccessMutable,                       int>));
    TEST((ReadWriteIterator                 <ContiguousMutable,                         int>));

    TEST((! ReadWriteForwardIterator        <Input,                                     int>));
    TEST((! ReadWriteForwardIterator        <Forward,                                   int>));
    TEST((! ReadWriteForwardIterator        <Bidirectional,                             int>));
    TEST((! ReadWriteForwardIterator        <RandomAccess,                              int>));
    TEST((! ReadWriteForwardIterator        <Contiguous,                                int>));
    TEST((! ReadWriteForwardIterator        <Output,                                    int>));
    TEST((ReadWriteForwardIterator          <ForwardMutable,                            int>));
    TEST((ReadWriteForwardIterator          <BidirectionalMutable,                      int>));
    TEST((ReadWriteForwardIterator          <RandomAccessMutable,                       int>));
    TEST((ReadWriteForwardIterator          <ContiguousMutable,                         int>));

    TEST((! ReadWriteBidirectionalIterator  <Input,                                     int>));
    TEST((! ReadWriteBidirectionalIterator  <Forward,                                   int>));
    TEST((! ReadWriteBidirectionalIterator  <Bidirectional,                             int>));
    TEST((! ReadWriteBidirectionalIterator  <RandomAccess,                              int>));
    TEST((! ReadWriteBidirectionalIterator  <Contiguous,                                int>));
    TEST((! ReadWriteBidirectionalIterator  <Output,                                    int>));
    TEST((! ReadWriteBidirectionalIterator  <ForwardMutable,                            int>));
    TEST((ReadWriteBidirectionalIterator    <BidirectionalMutable,                      int>));
    TEST((ReadWriteBidirectionalIterator    <RandomAccessMutable,                       int>));
    TEST((ReadWriteBidirectionalIterator    <ContiguousMutable,                         int>));

    TEST((! ReadWriteRandomAccessIterator   <Input,                                     int>));
    TEST((! ReadWriteRandomAccessIterator   <Forward,                                   int>));
    TEST((! ReadWriteRandomAccessIterator   <Bidirectional,                             int>));
    TEST((! ReadWriteRandomAccessIterator   <RandomAccess,                              int>));
    TEST((! ReadWriteRandomAccessIterator   <Contiguous,                                int>));
    TEST((! ReadWriteRandomAccessIterator   <Output,                                    int>));
    TEST((! ReadWriteRandomAccessIterator   <ForwardMutable,                            int>));
    TEST((! ReadWriteRandomAccessIterator   <BidirectionalMutable,                      int>));
    TEST((ReadWriteRandomAccessIterator     <RandomAccessMutable,                       int>));
    TEST((ReadWriteRandomAccessIterator     <ContiguousMutable,                         int>));

    TEST((! ReadWriteContiguousIterator     <Input,                                     int>));
    TEST((! ReadWriteContiguousIterator     <Forward,                                   int>));
    TEST((! ReadWriteContiguousIterator     <Bidirectional,                             int>));
    TEST((! ReadWriteContiguousIterator     <RandomAccess,                              int>));
    TEST((! ReadWriteContiguousIterator     <Contiguous,                                int>));
    TEST((! ReadWriteContiguousIterator     <Output,                                    int>));
    TEST((! ReadWriteContiguousIterator     <ForwardMutable,                            int>));
    TEST((! ReadWriteContiguousIterator     <BidirectionalMutable,                      int>));
    TEST((! ReadWriteContiguousIterator     <RandomAccessMutable,                       int>));
    TEST((ReadWriteContiguousIterator       <ContiguousMutable,                         int>));

}

void test_rs_core_iterator_tags() {

    TEST((std::same_as<std::iterator_traits<Output>::iterator_category,         std::output_iterator_tag>));
    TEST((std::same_as<std::iterator_traits<Input>::iterator_category,          std::input_iterator_tag>));
    TEST((std::same_as<std::iterator_traits<Forward>::iterator_category,        std::forward_iterator_tag>));
    TEST((std::same_as<std::iterator_traits<Bidirectional>::iterator_category,  std::bidirectional_iterator_tag>));
    TEST((std::same_as<std::iterator_traits<RandomAccess>::iterator_category,   std::random_access_iterator_tag>));
    TEST((std::same_as<std::iterator_traits<Contiguous>::iterator_category,     std::contiguous_iterator_tag>));

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
