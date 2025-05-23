#pragma once

#include <algorithm>
#include <array>
#include <compare>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <format>
#include <functional>
#include <iterator>
#include <limits>
#include <ranges>
#include <set>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

// Enumeration helpers

#define RS_ENUM(EnumType, IntType, ...) \
    enum class EnumType: IntType { \
        __VA_ARGS__ \
    }; \
    [[maybe_unused]] inline const std::set<EnumType>& enum_values(EnumType) { \
        static const auto set = [] { \
            std::set<EnumType> set; \
            if constexpr (std::signed_integral<IntType>) { \
                auto table = ::RS::Detail::signed_enum_table(# __VA_ARGS__); \
                for (auto& [k,v]: table) { \
                    set.insert(static_cast<EnumType>(k)); \
                } \
            } else { \
                auto table = ::RS::Detail::unsigned_enum_table(# __VA_ARGS__); \
                for (auto& [k,v]: table) { \
                    set.insert(static_cast<EnumType>(k)); \
                } \
            } \
            return set; \
        }(); \
        return set; \
    } \
    [[maybe_unused]] inline std::string to_string(EnumType t) { \
        static const auto table = [] { \
            if constexpr (std::signed_integral<IntType>) { \
                return ::RS::Detail::signed_enum_table(# __VA_ARGS__); \
            } else { \
                return ::RS::Detail::unsigned_enum_table(# __VA_ARGS__); \
            } \
        }(); \
        auto index = static_cast<IntType>(t); \
        auto it = table.find(index); \
        if (it == table.end()) { \
            return std::to_string(index); \
        } else { \
            return it->second; \
        } \
    } \
    [[maybe_unused]] inline std::string rs_core_format(EnumType t) { \
        return to_string(t); \
    } \
    [[maybe_unused]] void rs_core_enum(EnumType);

#define RS_BITMASK(EnumType, IntType, ...) \
    enum class EnumType: IntType { \
        __VA_ARGS__ \
    }; \
    [[maybe_unused]] inline const std::set<EnumType>& enum_values(EnumType) { \
        static const auto set = [] { \
            std::set<EnumType> set {}; \
            auto table = ::RS::Detail::unsigned_enum_table(# __VA_ARGS__); \
            for (auto& [k,v]: table) { \
                set.insert(static_cast<EnumType>(k)); \
            } \
            return set; \
        }(); \
        return set; \
    } \
    [[maybe_unused]] inline std::string to_string(EnumType t) { \
        static_assert(std::unsigned_integral<IntType>); \
        static const auto table = ::RS::Detail::linear_enum_table(# __VA_ARGS__); \
        auto index = static_cast<unsigned long long>(t); \
        if (index == 0) { \
            return "none"; \
        } \
        auto residue = index; \
        std::string str; \
        for (const auto& [number,name]: table) { \
            if ((number & residue) != 0) { \
                str += name + '|'; \
                residue &= ~ number; \
            } \
        } \
        if (residue == 0) { \
            str.pop_back(); \
            return str; \
        } else { \
            return std::format("0x{:x}", index); \
        } \
    } \
    [[maybe_unused]] inline std::string rs_core_format(EnumType t) { \
        return to_string(t); \
    } \
    [[maybe_unused]] constexpr bool operator!(EnumType t) noexcept { \
        return ! static_cast<bool>(t); \
    } \
    [[maybe_unused]] constexpr EnumType operator~(EnumType t) noexcept { \
        return static_cast<EnumType>(~ static_cast<IntType>(t)); \
    } \
    [[maybe_unused]] constexpr EnumType operator&(EnumType t, EnumType u) noexcept { \
        return static_cast<EnumType>(static_cast<IntType>(t) & static_cast<IntType>(u)); \
    } \
    [[maybe_unused]] constexpr EnumType operator|(EnumType t, EnumType u) noexcept { \
        return static_cast<EnumType>(static_cast<IntType>(t) | static_cast<IntType>(u)); \
    } \
    [[maybe_unused]] constexpr EnumType operator^(EnumType t, EnumType u) noexcept { \
        return static_cast<EnumType>(static_cast<IntType>(t) ^ static_cast<IntType>(u)); \
    } \
    [[maybe_unused]] constexpr EnumType& operator&=(EnumType& t, EnumType u) noexcept { \
        return t = t & u; \
    } \
    [[maybe_unused]] constexpr EnumType& operator|=(EnumType& t, EnumType u) noexcept { \
        return t = t | u; \
    } \
    [[maybe_unused]] constexpr EnumType& operator^=(EnumType& t, EnumType u) noexcept { \
        return t = t ^ u; \
    } \
    [[maybe_unused]] void rs_core_bitmask(EnumType); \
    [[maybe_unused]] void rs_core_enum(EnumType);

namespace RS {

    // Sanity check

    static_assert(std::numeric_limits<unsigned char>::digits == 8);

    // Constants

    constexpr std::string_view ascii_whitespace = "\t\n\r ";
    constexpr auto npos = ~ 0uz;

    // Bitmask functions

    namespace Detail {

        template <std::integral T>
        constexpr auto force_unsigned(T t) noexcept {
            return static_cast<std::make_unsigned_t<T>>(t);
        }

        template <typename T>
        requires std::is_enum_v<T>
        constexpr auto force_unsigned(T t) noexcept {
            return force_unsigned(static_cast<std::underlying_type_t<T>>(t));
        }

    }

    template <typename T1, typename T2>
    requires (std::integral<T1> || std::is_enum_v<T1>)
        && (std::integral<T2> || std::is_enum_v<T2>)
    constexpr bool has_bit(T1 x, T2 y) noexcept {
        using namespace Detail;
        auto u = force_unsigned(x);
        auto v = force_unsigned(y);
        return (u & v) != 0;
    }

    template <typename T1, typename T2>
    requires (std::integral<T1> || std::is_enum_v<T1>)
        && (std::integral<T2> || std::is_enum_v<T2>)
    constexpr bool has_bits(T1 x, T2 y) noexcept {
        using namespace Detail;
        auto u = force_unsigned(x);
        auto v = force_unsigned(y);
        return v != 0 && (u & v) == v;
    }

    // Integer literals

    constexpr std::int8_t operator""_i8(unsigned long long x) noexcept { return static_cast<std::int8_t>(x); }
    constexpr std::int16_t operator""_i16(unsigned long long x) noexcept { return static_cast<std::int16_t>(x); }
    constexpr std::int32_t operator""_i32(unsigned long long x) noexcept { return static_cast<std::int32_t>(x); }
    constexpr std::int64_t operator""_i64(unsigned long long x) noexcept { return static_cast<std::int64_t>(x); }
    constexpr std::uint8_t operator""_u8(unsigned long long x) noexcept { return static_cast<std::uint8_t>(x); }
    constexpr std::uint16_t operator""_u16(unsigned long long x) noexcept { return static_cast<std::uint16_t>(x); }
    constexpr std::uint32_t operator""_u32(unsigned long long x) noexcept { return static_cast<std::uint32_t>(x); }
    constexpr std::uint64_t operator""_u64(unsigned long long x) noexcept { return static_cast<std::uint64_t>(x); }

    // Character functions

    constexpr bool is_ascii(char c) noexcept { return static_cast<unsigned char>(c) <= 0x7f; }
    constexpr bool ascii_iscntrl(char c) noexcept { auto b = static_cast<unsigned char>(c); return b <= 0x1f || b == 0x7f; }
    constexpr bool ascii_isblank(char c) noexcept { return c == '\t' || c == ' '; }
    constexpr bool ascii_isspace(char c) noexcept { return (c >= '\t' && c <= '\r') || c == ' '; }
    constexpr bool ascii_isdigit(char c) noexcept { return c >= '0' && c <= '9'; }
    constexpr bool ascii_isxdigit(char c) noexcept { return ascii_isdigit(c) || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'); }
    constexpr bool ascii_isupper(char c) noexcept { return c >= 'A' && c <= 'Z'; }
    constexpr bool ascii_islower(char c) noexcept { return c >= 'a' && c <= 'z'; }
    constexpr bool ascii_isalpha(char c) noexcept { return ascii_isupper(c) || ascii_islower(c); }
    constexpr bool ascii_isalnum(char c) noexcept { return ascii_isdigit(c) || ascii_isalpha(c); }
    constexpr bool ascii_isgraph(char c) noexcept { return c >= '!' && c <= '~'; }
    constexpr bool ascii_isprint(char c) noexcept { return c >= ' ' && c <= '~'; }
    constexpr bool ascii_ispunct(char c) noexcept { return ascii_isgraph(c) && ! ascii_isalnum(c); }
    constexpr char ascii_tolower(char c) noexcept { return static_cast<char>(ascii_isupper(c) ? c + 0x20 : c); }
    constexpr char ascii_toupper(char c) noexcept { return static_cast<char>(ascii_islower(c) ? c - 0x20 : c); }

    // Enumeration helpers

    namespace Detail {

        template <typename T>
        concept ExtendedEnum = std::is_enum_v<T>
            && requires(T t) { rs_core_enum(t); };

        template <typename T>
        concept ExtendedBitmask = std::is_enum_v<T>
            && requires(T t) { rs_core_bitmask(t); };

        template <std::integral T>
        std::vector<std::pair<T, std::string>> make_enum_list(const char* va_args) {

            static constexpr std::string_view whitespace = "\t\n\r ";

            std::string_view va_view = va_args;
            std::vector<std::pair<T, std::string>> list;
            T index = 0;
            auto begin_field = 0uz;

            while (begin_field < va_view.size()) {

                auto comma_pos = va_view.find_first_of(",", begin_field);
                auto field = va_view.substr(begin_field, comma_pos - begin_field);
                auto begin_name = field.find_first_not_of(whitespace);

                if (begin_name != std::string::npos) {

                    field = field.substr(begin_name);
                    field = field.substr(0, field.find_last_not_of(whitespace) + 1);
                    auto eq_pos = field.find('=');

                    if (eq_pos != std::string::npos) {

                        auto index_str = field.substr(eq_pos + 1);
                        field = field.substr(0, eq_pos);
                        auto end_field = field.find_last_not_of(whitespace) + 1;

                        if (end_field != 0) {
                            field = field.substr(0, end_field);
                        }

                        if constexpr (std::signed_integral<T>) {
                            index = static_cast<T>(std::strtoll(index_str.data(), nullptr, 0));
                        } else {
                            index = static_cast<T>(std::strtoull(index_str.data(), nullptr, 0));
                        }

                    }

                    std::string name{field};
                    list.push_back({index, name});
                    ++index;

                }

                begin_field = comma_pos + 1;

            }

            return list;

        }

        inline std::unordered_map<long long, std::string> signed_enum_table(const char* va_args) {
            auto list = make_enum_list<long long>(va_args);
            std::unordered_map<long long, std::string> table(list.begin(), list.end());
            return table;
        }

        inline std::unordered_map<unsigned long long, std::string> unsigned_enum_table(const char* va_args) {
            auto list = make_enum_list<unsigned long long>(va_args);
            std::unordered_map<unsigned long long, std::string> table(list.begin(), list.end());
            return table;
        }

        inline std::vector<std::pair<unsigned long long, std::string>> linear_enum_table(const char* va_args) {
            return make_enum_list<unsigned long long>(va_args);
        }

    }

    // Formatters

    namespace Detail {

        template <typename T>
        concept StringOrView = std::convertible_to<T, std::string>
            || std::convertible_to<T, std::string_view>;

        template <typename T>
        concept FormatByMemberFunction = requires (const T& t) {
            { t.rs_core_format() } -> StringOrView;
        };

        template <typename T>
        concept FormatByMemberFunctionWithFlags = requires (const T& t, std::string_view s) {
            { t.rs_core_format(s) } -> StringOrView;
        };

        template <typename T>
        concept FormatByMemberFunctionWithSize = requires (const T& t, std::size_t n) {
            { t.rs_core_format(n) } -> StringOrView;
        };

        template <typename T>
        concept FormatByMemberFunctionWithBoth = requires (const T& t, std::string_view s, std::size_t n) {
            { t.rs_core_format(s, n) } -> StringOrView;
        };

        template <typename T>
        concept FormatByFreeFunction = requires (const T& t) {
            { rs_core_format(t) } -> StringOrView;
        };

        template <typename T>
        concept FormatByFreeFunctionWithFlags = requires (const T& t, std::string_view s) {
            { rs_core_format(t, s) } -> StringOrView;
        };

        template <typename T>
        concept FormatByFreeFunctionWithSize = requires (const T& t, std::size_t n) {
            { rs_core_format(t, n) } -> StringOrView;
        };

        template <typename T>
        concept FormatByFreeFunctionWithBoth = requires (const T& t, std::string_view s, std::size_t n) {
            { rs_core_format(t, s, n) } -> StringOrView;
        };

        template <typename T>
        concept AutoFormat =
            FormatByMemberFunction<T>
            || FormatByMemberFunctionWithFlags<T>
            || FormatByMemberFunctionWithSize<T>
            || FormatByMemberFunctionWithBoth<T>
            || FormatByFreeFunction<T>
            || FormatByFreeFunctionWithFlags<T>
            || FormatByFreeFunctionWithSize<T>
            || FormatByFreeFunctionWithBoth<T>;

    }

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

    // Iterator base classes

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

    // Metaprogramming utilities

    template <typename> constexpr bool dependent_false = false;

    // Random number generators

    namespace Detail {

        struct Uint128 {

            std::uint64_t high = 0;
            std::uint64_t low = 0;

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
                static constexpr std::uint64_t max32 = ~ std::uint32_t{};
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
        constexpr explicit Pcg(std::uint64_t s0, std::uint64_t s1, std::uint64_t s2, std::uint64_t s3) noexcept { seed(s0, s1, s2, s3); }

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
        static constexpr std::uint64_t factor = 0xda94'2042'e4dd'58b5ull;
        auto u = this->state_;
        this->state_ = u * factor + this->delta_;
        auto x = (u >> 64).low;
        auto y = (u | 1).low;
        x ^= x >> 32;
        x *= factor;
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

    // Range functions

    template <std::input_or_output_iterator I, std::sentinel_for<I> S>
    std::ranges::subrange<I, S> as_range(std::pair<I, S> pair) noexcept {
        return std::ranges::subrange(pair.first, pair.second);
    }

    // Scope guards

    RS_BITMASK(ScopeMode, unsigned char,
        success  = 1,  // Invoke callback on normal exit, but not when unwinding due to exception
        failure  = 2,  // Invoke callback when unwinding due to exception, but not on normal exit
        exit     = 3,  // Invoke callback unconditionally in destructor
    )

    template <std::invocable F, ScopeMode M>
    class BasicScopeGuard {

    public:

        BasicScopeGuard(F&& f):
            callback_(std::forward<F>(f)),
            inflight_(std::uncaught_exceptions()) {}

        ~BasicScopeGuard() noexcept {
            if (inflight_ >= 0) {
                auto uncaught = std::uncaught_exceptions();
                if ((!! (M & ScopeMode::success) && uncaught <= inflight_)
                        || (!! (M & ScopeMode::failure) && uncaught > inflight_)) {
                    callback_();
                }
            }
        }

        BasicScopeGuard(const BasicScopeGuard&) = delete;
        BasicScopeGuard(BasicScopeGuard&&) = delete;
        BasicScopeGuard& operator=(const BasicScopeGuard&) = delete;
        BasicScopeGuard& operator=(BasicScopeGuard&&) = delete;

        void release() noexcept {
            inflight_ = -1;
        }

    private:

        F callback_;
        int inflight_;

    };

    template <std::invocable F>
    auto on_success(F&& f) {
        return BasicScopeGuard<F, ScopeMode::success>(std::forward<F>(f));
    }

    template <std::invocable F>
    auto on_failure(F&& f) {
        return BasicScopeGuard<F, ScopeMode::failure>(std::forward<F>(f));
    }

    template <std::invocable F>
    auto on_exit(F&& f) {
        return BasicScopeGuard<F, ScopeMode::exit>(std::forward<F>(f));
    }

    // UUID

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
        std::string str() const;
        std::string rs_core_format() const { return str(); }
        explicit operator std::string() const { return str(); }

        constexpr static Uuid read(const void* ptr) noexcept {
            Uuid u;
            std::memcpy(u.bytes_.data(), ptr, 16);
            return u;
        }

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
            while (i < str.size() && j < 16) {
                auto len = str.size() - i;
                if (len >= 2 && str[i] == '0' && (str[i + 1] == 'X' || str[i + 1] == 'x')) {
                    i += 2;
                } else if (len >= 2 && ascii_isxdigit(str[i]) && ascii_isxdigit(str[i + 1])) {
                    for (auto k = 0; k < 2; ++k) {
                        bytes_[j] *= 16;
                        auto c = str[i + k];
                        if (ascii_isdigit(c)) {
                            bytes_[j] += static_cast<std::uint8_t>(c - '0');
                        } else if (ascii_isupper(c)) {
                            bytes_[j] += static_cast<std::uint8_t>(c - 'A' + 10);
                        } else {
                            bytes_[j] += static_cast<std::uint8_t>(c - 'a' + 10);
                        }
                    }
                    i += 2;
                    ++j;
                } else if (is_separator(str[i])) {
                    ++i;
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
            std::string s;
            s.reserve(37);
            const auto append_bytes = [this,&s] (std::size_t pos, std::size_t len) {
                static constexpr const char* xdigits = "0123456789abcdef";
                for (auto i = 0uz; i < len; ++i) {
                    s += xdigits[bytes_[pos + i] / 16];
                    s += xdigits[bytes_[pos + i] % 16];
                }
                s += '-';
            };
            append_bytes(0, 4);
            append_bytes(4, 2);
            append_bytes(6, 2);
            append_bytes(8, 2);
            append_bytes(10, 6);
            s.pop_back();
            return s;
        }

}

// Formatters

template <::RS::Detail::AutoFormat T>
struct std::formatter<T> {

private:

    static constexpr auto max_flags = 16uz;

    static constexpr auto with_flags =
        ::RS::Detail::FormatByMemberFunctionWithFlags<T>
        || ::RS::Detail::FormatByMemberFunctionWithBoth<T>
        || ::RS::Detail::FormatByFreeFunctionWithFlags<T>
        || ::RS::Detail::FormatByFreeFunctionWithBoth<T>;

    static constexpr auto with_size =
        ::RS::Detail::FormatByMemberFunctionWithSize<T>
        || ::RS::Detail::FormatByMemberFunctionWithBoth<T>
        || ::RS::Detail::FormatByFreeFunctionWithSize<T>
        || ::RS::Detail::FormatByFreeFunctionWithBoth<T>;

    template <int> class empty_type {};

    struct flags_base {
        std::array<char, max_flags> flags;
        std::size_t n_flags = 0;
    };

    struct size_base {
        std::size_t size = 0;
    };

    struct info_type:
    std::conditional_t<with_flags, flags_base, empty_type<1>>,
    std::conditional_t<with_size, size_base, empty_type<2>> {};

    info_type info_;

    constexpr std::string_view flags() const noexcept {
        if constexpr (with_flags) {
            return std::string_view(info_.flags.data(), info_.n_flags);
        } else {
            return {};
        }
    }

    static constexpr bool legit_flag(char c) noexcept {
        return c != 0 && c != '{' && c != '}'
            && (c < '0' || c > '9');
    }

public:

    constexpr auto parse(std::format_parse_context& ctx) {

        auto it = ctx.begin();

        for (; it != ctx.end() && *it != '}'; ++it) {

            if constexpr (with_flags) {
                if (legit_flag(*it) && info_.n_flags < max_flags) {
                    info_.flags[info_.n_flags++] = *it;
                    continue;
                }
            }

            if constexpr (with_size) {
                if (*it >= '0' && *it <= '9') {
                    info_.size = info_.size * 10uz + static_cast<std::size_t>(*it - '0');
                    continue;
                }
            }

            throw std::format_error{std::format("Invalid format: {:?}", *it)};

        }

        return it;

    }

    // The gratuitous template here is a workaround for a libc++ bug
    // https://github.com/llvm/llvm-project/issues/66466

    template <typename FormatContext>
    auto format(const T& t, FormatContext& ctx) const {

        using namespace ::RS::Detail;

        std::string out;

        if constexpr (FormatByMemberFunctionWithBoth<T>) {
            out = t.rs_core_format(flags(), info_.size);
        } else if constexpr (FormatByMemberFunctionWithFlags<T>) {
            out = t.rs_core_format(flags());
        } else if constexpr (FormatByMemberFunctionWithSize<T>) {
            out = t.rs_core_format(info_.size);
        } else if constexpr (FormatByMemberFunction<T>) {
            out = t.rs_core_format();
        } else if constexpr (FormatByFreeFunctionWithBoth<T>) {
            out = rs_core_format(t, flags(), info_.size);
        } else if constexpr (FormatByFreeFunctionWithFlags<T>) {
            out = rs_core_format(t, flags());
        } else if constexpr (FormatByFreeFunctionWithSize<T>) {
            out = rs_core_format(t, info_.size);
        } else if constexpr (FormatByFreeFunction<T>) {
            out = rs_core_format(t);
        } else {
            static_assert(::RS::dependent_false<T>);
        }

        return std::ranges::copy(out, ctx.out()).out;

    }

};

// Hash functions

namespace std {

    template <>
    struct hash<::RS::Uuid> {
        std::size_t operator()(const ::RS::Uuid& u) const noexcept { return u.hash(); }
    };

}
