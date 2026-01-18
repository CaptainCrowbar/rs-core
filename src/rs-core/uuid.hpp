#pragma once

#include "rs-core/arithmetic.hpp"
#include "rs-core/format.hpp"
#include "rs-core/global.hpp"
#include "rs-core/hash.hpp"
#include "rs-core/random.hpp"
#include "rs-core/uint128.hpp"
#include <array>
#include <bit>
#include <chrono>
#include <compare>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <format>
#include <functional>
#include <random>
#include <stdexcept>
#include <string>
#include <string_view>

namespace RS {

    class Uuid {

    public:

        constexpr Uuid() = default;
        constexpr Uuid(std::uint8_t a, std::uint8_t b, std::uint8_t c, std::uint8_t d,
            std::uint8_t e, std::uint8_t f, std::uint8_t g, std::uint8_t h,
            std::uint8_t i, std::uint8_t j, std::uint8_t k, std::uint8_t l,
            std::uint8_t m, std::uint8_t n, std::uint8_t o, std::uint8_t p) noexcept:
            bytes_{a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p} {}
        constexpr explicit Uuid(Uint128 u, std::endian order = std::endian::big) noexcept;
        explicit Uuid(std::string_view str);

        constexpr std::uint8_t& operator[](std::size_t i) noexcept { return bytes_[i]; }
        constexpr const std::uint8_t& operator[](std::size_t i) const noexcept { return bytes_[i]; }
        constexpr std::uint8_t* begin() noexcept { return bytes_.data(); }
        constexpr const std::uint8_t* begin() const noexcept { return bytes_.data(); }
        constexpr std::uint8_t* end() noexcept { return begin() + 16; }
        constexpr const std::uint8_t* end() const noexcept { return begin() + 16; }

        constexpr Uint128 as_integer(std::endian order = std::endian::big) const noexcept;
        constexpr std::size_t hash() const noexcept { return kernighan_hash(begin(), 16); }
        constexpr int variant() const noexcept;
        constexpr int version() const noexcept { return static_cast<int>(bytes_[6] >> 4); }
        constexpr void set_variant(int v) noexcept;
        constexpr void set_version(int v) noexcept;
        std::string to_string() const;
        explicit operator std::string() const { return to_string(); }

        static constexpr Uuid max() noexcept;
        template <std::uniform_random_bit_generator RNG> static Uuid random(RNG& rng, int type = 4);
        static Uuid read(const void* ptr) noexcept;

        friend constexpr bool operator==(const Uuid& u, const Uuid& v) noexcept = default;
        friend constexpr auto operator<=>(const Uuid& u, const Uuid& v) noexcept = default;

    private:

        std::array<std::uint8_t, 16> bytes_ {0};

        template <std::uniform_random_bit_generator RNG> void fill_random(RNG& rng, std::size_t start_byte) noexcept;
        template <std::uniform_random_bit_generator RNG> void generate_v4(RNG& rng) noexcept { fill_random(rng, 0); }
        template <std::uniform_random_bit_generator RNG> void generate_v7(RNG& rng) noexcept;

    };

        constexpr Uuid::Uuid(Uint128 u, std::endian order) noexcept {

            int start, stop, delta;

            if (order == std::endian::big) {
                start = 15;
                stop = -1;
                delta = -1;
            } else {
                start = 0;
                stop = 16;
                delta = 1;
            }

            for (auto i = start; i != stop; i += delta, u >>= 8) {
                auto j = static_cast<unsigned>(i);
                bytes_[j] = static_cast<std::uint8_t>(u);
            }

        }

        inline Uuid::Uuid(std::string_view str) {

            if (str.empty()) {
                return;
            }

            static constexpr auto is_separator = [] (char c) {
                return ascii_isblank(c) || ascii_ispunct(c);
            };

            auto i = 0uz;
            auto j = 0uz;
            auto last_pos = str.size() - 1;

            while (i < last_pos && j < 16) {
                if (is_separator(str[i])) {
                    ++i;
                } else if (str[i] == '0' && (str[i + 1] == 'X' || str[i + 1] == 'x')) {
                    i += 2;
                } else if (ascii_isxdigit(str[i]) && ascii_isxdigit(str[i + 1])) {
                    parse_number(str.substr(i, 2), bytes_[j++], 16);
                    i += 2;
                } else {
                    break;
                }
            }

            while (i < str.size() && is_separator(str[i])) {
                ++i;
            }

            if (i < str.size() || j < 16) {
                throw std::invalid_argument(std::format("Invalid UUID: {:?}", str));
            }

        }

        constexpr Uint128 Uuid::as_integer(std::endian order) const noexcept {

            Uint128 u;
            int start, stop, delta;

            if (order == std::endian::big) {
                start = 0;
                stop = 16;
                delta = 1;
            } else {
                start = 15;
                stop = -1;
                delta = -1;
            }

            for (auto i = start; i != stop; i += delta) {
                auto j = static_cast<unsigned>(i);
                u = (u << 8) + bytes_[j];
            }

            return u;

        }

        constexpr int Uuid::variant() const noexcept {
            auto v = static_cast<int>(bytes_[8] >> 4);
            return v < 8 ? v & 8 : v < 12 ? v & 12 : v & 14;
        }

        constexpr void Uuid::set_variant(int v) noexcept {
            auto u = static_cast<std::uint8_t>(v & 15);
            std::uint8_t mask;
            if (u < 8) {
                mask = 8;
            } else if (u < 12) {
                mask = 12;
            } else {
                mask = 14;
            }
            bytes_[8] &= ((15 - mask) << 4) + 15;
            bytes_[8] |= (u & mask) << 4;
        }

        constexpr void Uuid::set_version(int v) noexcept {
            bytes_[6] &= 15;
            bytes_[6] |= static_cast<std::uint8_t>(v) << 4;
        }

        inline std::string Uuid::to_string() const {
            return std::format
                ("{:02x}{:02x}{:02x}{:02x}-{:02x}{:02x}-{:02x}{:02x}-{:02x}{:02x}-{:02x}{:02x}{:02x}{:02x}{:02x}{:02x}",
                bytes_[0], bytes_[1], bytes_[2], bytes_[3], bytes_[4], bytes_[5], bytes_[6], bytes_[7],
                bytes_[8], bytes_[9], bytes_[10], bytes_[11], bytes_[12], bytes_[13], bytes_[14], bytes_[15]);
        }

        constexpr Uuid Uuid::max() noexcept {
            Uuid u;
            std::memset(u.bytes_.data(), '\xff', u.bytes_.size());
            return u;
        }

        template <std::uniform_random_bit_generator RNG>
        inline Uuid Uuid::random(RNG& rng, int type) {
            Uuid u;
            switch (type) {
                case 4:  u.generate_v4(rng); break;
                case 7:  u.generate_v7(rng); break;
                default:  throw std::invalid_argument(std::format("Unsupported UUUID type ({})", type));
            }
            u.set_variant(8);
            u.set_version(type);
            return u;
        }

        inline Uuid Uuid::read(const void* ptr) noexcept {
            Uuid u;
            std::memcpy(u.bytes_.data(), ptr, 16);
            return u;
        }

        template <std::uniform_random_bit_generator RNG>
        void Uuid::fill_random(RNG& rng, std::size_t start_byte) noexcept {

            UniformInteger<std::uint64_t> dist;
            auto n_bytes = 16uz - start_byte;
            std::uint64_t x;

            for (auto i = 0uz; i < n_bytes; ++i, x >>= 8) {
                if (i % 8 == 0) {
                    x = dist(rng);
                }
                bytes_[start_byte + i] = static_cast<std::uint8_t>(x);
            }

        }

        template <std::uniform_random_bit_generator RNG>
        void Uuid::generate_v7(RNG& rng) noexcept {

            using namespace std::chrono;

            auto timestamp = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

            for (auto i = 5uz, j = 0uz; j < 6; --i, ++j) {
                bytes_[j] = static_cast<std::uint8_t>(timestamp >> i);
            }

            fill_random(rng, 6);

        }

}

template <>
struct std::formatter<RS::Uuid>:
RS::BasicFormatter<RS::Uuid> {};

template <>
struct std::hash<RS::Uuid> {
    std::size_t operator()(const RS::Uuid& u) const noexcept { return u.hash(); }
};
