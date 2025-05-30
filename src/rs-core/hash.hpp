#pragma once

#include "rs-core/global.hpp"
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <ranges>
#include <type_traits>

namespace RS {

    // Hash concepts

    template <typename T>
    concept Hashable = requires (T t) {
        { std::hash<std::remove_cvref_t<T>>()(t) } -> std::convertible_to<std::size_t>;
    };

    // Hash mixing functions

    constexpr std::size_t hash_mix() noexcept {
        return 0;
    }

    constexpr std::size_t hash_mix(std::size_t x) noexcept {
        return x;
    }

    constexpr std::size_t hash_mix(std::size_t x, std::size_t y) noexcept {
        return x ^ ((x << 6) + (x >> 2) + y + 0x9e37'79b9uz);
    }

    template <std::convertible_to<std::size_t>... TS>
    constexpr std::size_t hash_mix(std::size_t x, std::size_t y, TS... ts) noexcept {
        return hash_mix(hash_mix(x, y), ts...);
    }

    template <std::ranges::range Range>
    requires (std::convertible_to<std::ranges::range_value_t<Range>, std::size_t>)
    std::size_t hash_mix(const Range& range, std::size_t init = 0) {
        for (auto x: range) {
            init = hash_mix(init, x);
        }
        return init;
    }

    // Hash function by Brian Kernighan

    constexpr std::uint32_t kernighan_hash(const void* ptr, std::size_t len, std::uint32_t seed = 0) noexcept {
        auto bytes = static_cast<const std::uint8_t*>(ptr);
        for (auto i = 0uz; i < len; ++i) {
            seed = 31 * seed + bytes[i];
        }
        return seed;
    }

}
