#pragma once

#include "rs-core/global.hpp"
#include <compare>
#include <cstddef>
#include <iterator>
#include <type_traits>

namespace RS {

    template <typename I>
    class OutputIterator {
    public:
        using difference_type = void;
        using iterator_category = std::output_iterator_tag;
        using pointer = void;
        using reference = void;
        using value_type = void;
        I& operator*() { return self(); }
        friend I& operator++(I& t) { return t; }
        friend I operator++(I& t, int) { return t; }
    private:
        auto& self() { return *static_cast<I*>(this); }
    };

    template <typename I, typename CV>
    class InputIterator {
    public:
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::input_iterator_tag;
        using pointer = CV*;
        using reference = CV&;
        using value_type = std::remove_const_t<CV>;
        CV* operator->() const { return &*self(); }
        friend I operator++(I& i, int) { auto j = i; ++i; return j; }
    private:
        const auto& self() const { return *static_cast<const I*>(this); }
    };

    template <typename I, typename CV>
    class ForwardIterator:
    public InputIterator<I, CV> {
    public:
        using iterator_category = std::forward_iterator_tag;
    };

    template <typename I, typename CV>
    class BidirectionalIterator:
    public ForwardIterator<I, CV> {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        friend I operator--(I& i, int) { auto j = i; --i; return j; }
    };

    template <typename I, typename CV>
    class RandomAccessIterator:
    public BidirectionalIterator<I, CV> {
    public:
        using iterator_category = std::random_access_iterator_tag;
        CV& operator[](std::ptrdiff_t n) const { auto i = self(); i += n; return *i; }
        I& operator++() { self() += 1; return self(); }
        I& operator--() { self() += -1; return self(); }
        I& operator-=(std::ptrdiff_t n) { self() += - n; return self(); }
        friend I operator+(const I& a, std::ptrdiff_t b) { auto i = a; i += b; return i; }
        friend I operator+(std::ptrdiff_t a, const I& b) { auto i = b; i += a; return i; }
        friend I operator-(const I& a, std::ptrdiff_t b) { auto i = a; i -= b; return i; }
        friend bool operator==(const I& a, const I& b) { return a - b == 0; }
        friend std::strong_ordering operator<=>(const I& a, const I& b) {
            auto c = a - b;
            return c == 0 ? std::strong_ordering::equal :
                c < 0 ? std::strong_ordering::less : std::strong_ordering::greater;
        }
    private:
        auto& self() { return *static_cast<I*>(this); }
        const auto& self() const { return *static_cast<const I*>(this); }
    };

    template <typename I, typename CV>
    class ContiguousIterator:
    public RandomAccessIterator<I, CV> {
    public:
        using iterator_category = std::contiguous_iterator_tag;
    };

}
