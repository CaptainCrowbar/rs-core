#pragma once

#include "rs-core/arithmetic.hpp"
#include "rs-core/format.hpp"
#include "rs-core/global.hpp"
#include "rs-core/hash.hpp"
#include <array>
#include <compare>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <format>
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
        explicit Uuid(std::string_view str);

        constexpr std::uint8_t& operator[](std::size_t i) noexcept { return bytes_[i]; }
        constexpr const std::uint8_t& operator[](std::size_t i) const noexcept { return bytes_[i]; }
        constexpr std::uint8_t* begin() noexcept { return bytes_.data(); }
        constexpr const std::uint8_t* begin() const noexcept { return bytes_.data(); }
        constexpr std::uint8_t* end() noexcept { return begin() + 16; }
        constexpr const std::uint8_t* end() const noexcept { return begin() + 16; }

        constexpr std::size_t hash() const noexcept { return kernighan_hash(begin(), 16); }
        constexpr int version() const noexcept { return static_cast<int>(bytes_[6] >> 4); }
        std::string str() const;
        std::string rs_core_format() const { return str(); }
        explicit operator std::string() const { return str(); }

        template <std::uniform_random_bit_generator RNG> static Uuid random(RNG& rng);
        static Uuid read(const void* ptr) noexcept;

        friend constexpr bool operator==(const Uuid& u, const Uuid& v) noexcept { return u.bytes_ == v.bytes_; }
        friend constexpr auto operator<=>(const Uuid& u, const Uuid& v) noexcept { return u.bytes_ <=> v.bytes_; }

    private:

        std::array<std::uint8_t, 16> bytes_ {0};

    };

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

        inline std::string Uuid::str() const {
            return std::format
                ("{:02x}{:02x}{:02x}{:02x}-{:02x}{:02x}-{:02x}{:02x}-{:02x}{:02x}-{:02x}{:02x}{:02x}{:02x}{:02x}{:02x}",
                bytes_[0], bytes_[1], bytes_[2], bytes_[3], bytes_[4], bytes_[5], bytes_[6], bytes_[7],
                bytes_[8], bytes_[9], bytes_[10], bytes_[11], bytes_[12], bytes_[13], bytes_[14], bytes_[15]);
        }

        template <std::uniform_random_bit_generator RNG>
        inline Uuid Uuid::random(RNG& rng) {

            std::uniform_int_distribution<std::uint32_t> dist;
            Uuid u;
            auto ptr = u.begin();

            for (auto i = 0; i < 4; ++i) {
                auto x = dist(rng);
                for (auto j = 0; j < 4; ++j, x >>= 8) {
                    *ptr++ = static_cast<std::uint8_t>(x);
                }
            }

            u[6] &= 0x0f;
            u[6] |= 0x40;
            u[8] &= 0x3f;
            u[8] |= 0x80;

            return u;

        }

        inline Uuid Uuid::read(const void* ptr) noexcept {
            Uuid u;
            std::memcpy(u.bytes_.data(), ptr, 16);
            return u;
        }

}

namespace std {

    template <>
    struct hash<::RS::Uuid> {
        std::size_t operator()(const ::RS::Uuid& u) const noexcept { return u.hash(); }
    };

}
