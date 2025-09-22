#pragma once

#include "rs-core/global.hpp"
#include <compare>
#include <concepts>
#include <cstddef>
#include <iterator>
#include <ranges>
#include <type_traits>

namespace RS {

    template <typename I, typename CV, typename Guide>
    class Iterator {

    public:

        using iterator_category =
            std::conditional_t<std::same_as<Guide, std::contiguous_iterator_tag>
                    || std::same_as<Guide, std::random_access_iterator_tag>
                    || std::same_as<Guide, std::bidirectional_iterator_tag>
                    || std::same_as<Guide, std::forward_iterator_tag>
                    || std::same_as<Guide, std::input_iterator_tag>
                    || std::same_as<Guide, std::output_iterator_tag>,
                Guide,
            std::conditional_t<std::contiguous_iterator<Guide> || std::ranges::contiguous_range<Guide>,
                std::contiguous_iterator_tag,
            std::conditional_t<std::random_access_iterator<Guide> || std::ranges::random_access_range<Guide>,
                std::random_access_iterator_tag,
            std::conditional_t<std::bidirectional_iterator<Guide> || std::ranges::bidirectional_range<Guide>,
                std::bidirectional_iterator_tag,
            std::conditional_t<std::forward_iterator<Guide> || std::ranges::forward_range<Guide>,
                std::forward_iterator_tag,
            std::conditional_t<std::input_iterator<Guide> || std::ranges::input_range<Guide>,
                std::input_iterator_tag,
            std::conditional_t<std::output_iterator<Guide, std::remove_const_t<CV>>
                    || std::ranges::output_range<Guide, std::remove_const_t<CV>>,
                std::output_iterator_tag,
            void>>>>>>>;

        static_assert(! std::is_void_v<iterator_category>, "Could not deduce iterator category from guide type");

    private:

        static constexpr bool is_exactly_contiguous = std::same_as<iterator_category, std::contiguous_iterator_tag>;
        static constexpr bool is_exactly_random_access = std::same_as<iterator_category, std::random_access_iterator_tag>;
        static constexpr bool is_exactly_bidirectional = std::same_as<iterator_category, std::bidirectional_iterator_tag>;
        static constexpr bool is_exactly_forward = std::same_as<iterator_category, std::forward_iterator_tag>;
        static constexpr bool is_exactly_input = std::same_as<iterator_category, std::input_iterator_tag>;
        static constexpr bool is_exactly_output = std::same_as<iterator_category, std::output_iterator_tag>;

        static constexpr bool is_at_least_contiguous = is_exactly_contiguous;
        static constexpr bool is_at_least_random_access = is_exactly_random_access || is_at_least_contiguous;
        static constexpr bool is_at_least_bidirectional = is_exactly_bidirectional || is_at_least_random_access;
        static constexpr bool is_at_least_forward = is_exactly_forward || is_at_least_bidirectional;
        static constexpr bool is_at_least_input = is_exactly_input || is_at_least_forward;
        static constexpr bool is_at_least_output = is_exactly_output || is_at_least_forward;

    public:

        using difference_type = std::conditional_t<is_exactly_output, void, std::ptrdiff_t>;
        using pointer = std::conditional_t<is_exactly_output, void, CV*>;
        using reference = std::conditional_t<is_exactly_output, void, CV&>;
        using value_type = std::conditional_t<is_exactly_output, void, std::remove_const_t<CV>>;

        I& operator*()                  requires is_exactly_output  { return self(); }
        friend I& operator++(I& t)      requires is_exactly_output  { return t; }
        friend I operator++(I& t, int)  requires is_exactly_output  { return t; }

        CV* operator->() const          requires is_at_least_input  { return &*self(); }
        friend I operator++(I& i, int)  requires is_at_least_input  { auto j = i; ++i; return j; }

        friend I operator--(I& i, int)  requires is_at_least_bidirectional  { auto j = i; --i; return j; }

        CV& operator[](std::ptrdiff_t n) const            requires is_at_least_random_access  { auto i = self(); i += n; return *i; }
        I& operator++()                                   requires is_at_least_random_access  { self() += 1; return self(); }
        I& operator--()                                   requires is_at_least_random_access  { self() += -1; return self(); }
        I& operator-=(std::ptrdiff_t n)                   requires is_at_least_random_access  { self() += - n; return self(); }
        friend I operator+(const I& a, std::ptrdiff_t b)  requires is_at_least_random_access  { auto i = a; i += b; return i; }
        friend I operator+(std::ptrdiff_t a, const I& b)  requires is_at_least_random_access  { auto i = b; i += a; return i; }
        friend I operator-(const I& a, std::ptrdiff_t b)  requires is_at_least_random_access  { auto i = a; i -= b; return i; }
        friend bool operator==(const I& a, const I& b)    requires is_at_least_random_access  { return a - b == 0; }

        friend std::strong_ordering operator<=>(const I& a, const I& b)
        requires is_at_least_random_access {
            auto c = a - b;
            return c == 0 ? std::strong_ordering::equal :
                c < 0 ? std::strong_ordering::less : std::strong_ordering::greater;
        }

    private:

        auto& self() { return *static_cast<I*>(this); }
        const auto& self() const { return *static_cast<const I*>(this); }

    };

}
