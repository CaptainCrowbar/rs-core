#pragma once

#include "rs-core/global.hpp"
#include <array>
#include <bit>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <functional>
#include <ranges>
#include <string_view>
#include <type_traits>

namespace RS {

    // Hash concepts

    template <typename T>
    concept Hashable = requires (T t) {
        { std::hash<std::remove_cvref_t<T>>()(t) } -> std::convertible_to<std::size_t>;
    };

    template <typename T>
    concept RegularHashable = Hashable<T> && std::regular<T>;

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

    constexpr std::uint32_t kernighan_hash(const void* ptr, std::size_t len) noexcept {
        auto bytes = static_cast<const std::uint8_t*>(ptr);
        std::uint32_t hash{};
        for (auto i = 0uz; i < len; ++i) {
            hash = 31 * hash + bytes[i];
        }
        return hash;
    }

    // Siphash-2-4-64 by Jean-Philippe Aumasson and Daniel J. Bernstein

    class SipHash {

    public:

        SipHash() noexcept { init(default_key0, default_key1); }
        explicit SipHash(std::uint64_t key0, std::uint64_t key1) noexcept { init(key0, key1); }
        explicit SipHash(const void* key) noexcept; // Key must be 16 bytes

        std::uint64_t operator()(const void* ptr, std::size_t len) const noexcept;
        std::uint64_t operator()(std::string_view view) const noexcept { return (*this)(view.data(), view.size()); }

    private:

        static constexpr std::uint64_t default_key0 = 0x0706'0504'0302'0100ull;
        static constexpr std::uint64_t default_key1 = 0x0f0e'0d0c'0b0a'0908ull;
        static constexpr std::uint64_t init_mask0 = 0x736f'6d65'7073'6575ull;
        static constexpr std::uint64_t init_mask1 = 0x646f'7261'6e64'6f6dull;
        static constexpr std::uint64_t init_mask2 = 0x6c79'6765'6e65'7261ull;
        static constexpr std::uint64_t init_mask3 = 0x7465'6462'7974'6573ull;

        std::array<std::uint64_t, 4> init_state_;

        void init(std::uint64_t key0, std::uint64_t key2);

    };

        inline SipHash::SipHash(const void* key) noexcept {
            std::array<std::uint64_t, 2> keys;
            std::memcpy(keys.data(), key, 16);
            init(keys[0], keys[1]);
        }

        inline std::uint64_t SipHash::operator()(const void* ptr, std::size_t len) const noexcept {

            auto state = init_state_;

            auto sipround = [&] {
                state[0] += state[1];
                state[1] = std::rotl(state[1], 13);
                state[1] ^= state[0];
                state[0] = std::rotl(state[0], 32);
                state[2] += state[3];
                state[3] = std::rotl(state[3], 16);
                state[3] ^= state[2];
                state[0] += state[3];
                state[3] = std::rotl(state[3], 21);
                state[3] ^= state[0];
                state[2] += state[1];
                state[1] = std::rotl(state[1], 17);
                state[1] ^= state[2];
                state[2] = std::rotl(state[2], 32);
            };

            auto byte_ptr = static_cast<const std::uint8_t*>(ptr);
            auto bytes_left = len % 8;
            auto end_ptr = byte_ptr + (len - bytes_left);
            std::uint64_t word;

            for (; byte_ptr != end_ptr; byte_ptr += 8) {
                std::memcpy(&word, byte_ptr, 8);
                state[3] ^= word;
                sipround();
                sipround();
                state[0] ^= word;
            }

            auto tail = static_cast<std::uint64_t>(len) << 56;
            std::memcpy(&tail, byte_ptr, bytes_left);
            state[3] ^= tail;
            sipround();
            sipround();
            state[0] ^= tail;
            state[2] ^= 0xff;
            sipround();
            sipround();
            sipround();
            sipround();

            return state[0] ^ state[1] ^ state[2] ^ state[3];

        }

        inline void SipHash::init(std::uint64_t key0, std::uint64_t key1) {
            init_state_[0] = key0 ^ init_mask0;
            init_state_[1] = key1 ^ init_mask1;
            init_state_[2] = key0 ^ init_mask2;
            init_state_[3] = key1 ^ init_mask3;
        }

}
