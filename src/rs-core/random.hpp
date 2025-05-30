#pragma once

#include "rs-core/global.hpp"
#include <cstdint>

namespace RS {

    namespace Detail {

        struct Uint128 {

            std::uint64_t high {};
            std::uint64_t low {};

            constexpr Uint128() = default;
            constexpr Uint128(std::uint64_t lo) noexcept: low{lo} {}
            constexpr Uint128(std::uint64_t hi, std::uint64_t lo) noexcept: high{hi}, low{lo} {}

            constexpr Uint128 operator<<(int y) const noexcept {
                if (y >= 64) {
                    return {low << (y - 64), 0};
                } else if (y >= 1) {
                    return {(high << y) + (low >> (64 - y)), low << y};
                } else {
                    return *this;
                }
            }

            constexpr Uint128 operator>>(int y) const noexcept {
                if (y >= 64) {
                    return high >> (y - 64);
                } else if (y >= 1) {
                    return {high >> y, (low >> y) + (high << (64 - y))};
                } else {
                    return *this;
                }
            }

            constexpr Uint128 operator|(Uint128 y) const noexcept {
                return {high | y.high, low | y.low};
            }

            constexpr Uint128 operator+(Uint128 y) const noexcept {
                Uint128 z{high + y.high, low + y.low};
                if (z.low < low) {
                    ++z.high;
                }
                return z;
            }

            constexpr Uint128 operator*(Uint128 y) const noexcept {
                static constexpr std::uint64_t max32 = (1ull << 32) - 1;
                Uint128 z;
                for (auto a = 0; a < 128; a += 32) {
                    auto c = (*this >> a).low & max32;
                    for (auto b = 0; b < 128; b += 32) {
                        auto d = (y >> b).low & max32;
                        z = z + (Uint128{c * d} << (a + b));
                    }
                }
                return z;
            }

        };

    }

    // PCG64-DXSM algorithm
    // Based on code by Melissa O'Neill and Tony Finch
    // http://www.pcg-random.org/
    // https://dotat.at/@/2023-06-21-pcg64-dxsm.html

    class Pcg {

    public:

        using result_type = std::uint64_t;

        constexpr Pcg() noexcept { seed(default_seed); }
        constexpr explicit Pcg(std::uint64_t s) noexcept { seed(s); }
        constexpr explicit Pcg(std::uint64_t s0, std::uint64_t s1) noexcept { seed(s0, s1); }
        constexpr explicit Pcg(std::uint64_t s0, std::uint64_t s1, std::uint64_t s2, std::uint64_t s3) noexcept {
            seed(s0, s1, s2, s3);
        }

        constexpr std::uint64_t operator()() noexcept;
        constexpr void seed(std::uint64_t s) noexcept { seed(0, s, 0, 0); }
        constexpr void seed(std::uint64_t s0, std::uint64_t s1) noexcept { seed(s0, s1, 0, 0); }
        constexpr void seed(std::uint64_t s0, std::uint64_t s1, std::uint64_t s2, std::uint64_t s3) noexcept;

        constexpr static std::uint64_t min() noexcept { return 0; }
        constexpr static std::uint64_t max() noexcept { return ~ std::uint64_t{}; }

    private:

        static constexpr std::uint64_t default_seed = 0xcafe'f00d'd15e'a5e5ull;

        Detail::Uint128 state_;
        Detail::Uint128 delta_;

    };

        constexpr std::uint64_t Pcg::operator()() noexcept {
            static constexpr std::uint64_t k = 0xda94'2042'e4dd'58b5ull;
            auto u = state_;
            state_ = u * k + delta_;
            auto x = (u >> 64).low;
            auto y = (u | 1).low;
            x ^= x >> 32;
            x *= k;
            x ^= x >> 48;
            x *= y;
            return x;
        }

        constexpr void Pcg::seed(std::uint64_t s0, std::uint64_t s1, std::uint64_t s2, std::uint64_t s3) noexcept {
            state_ = {s0, s1};
            delta_ = {s2, s3};
            delta_ = (delta_ << 1) | 1;
            state_ = state_ + delta_;
            (*this)();
        }

}
