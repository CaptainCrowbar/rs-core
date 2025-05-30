#pragma once

#include <algorithm>
#include <array>
#include <cerrno>
#include <compare>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <filesystem>
#include <format>
#include <functional>
#include <iterator>
#include <limits>
#include <optional>
#include <random>
#include <ranges>
#include <set>
#include <stdexcept>
#include <string>
#include <string_view>
#include <system_error>
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

    // Number parsing

    RS_ENUM(ParseNumber, int,
        ok,
        invalid_base,
        invalid_number,
        out_of_range,
    )

    namespace Detail {

        template <std::unsigned_integral T>
        ParseNumber parse_unsigned_integer(std::string_view str, T& t, int base) {

            using limits = std::numeric_limits<T>;

            if (str.empty()) {
                return ParseNumber::invalid_number;
            }

            if (base == 0 && str.size() >= 3 && str[0] == '0') {
                if (str[1] == 'B' || str[1] == 'b') {
                    return parse_unsigned_integer(str.substr(2), t, 2);
                } else if (str[1] == 'X' || str[1] == 'x') {
                    return parse_unsigned_integer(str.substr(2), t, 16);
                }
            }

            auto t_base = static_cast<T>(base);
            auto max_before_multiply = limits::max() / t_base;
            T digit {};
            T value {};

            for (auto c: str) {

                if (ascii_isdigit(c)) {
                    digit = static_cast<T>(c - '0');
                } else if (base >= 11 && ascii_isupper(c)) {
                    digit = static_cast<T>(c - 'A' + 10);
                } else if (base >= 11 && ascii_islower(c)) {
                    digit = static_cast<T>(c - 'a' + 10);
                } else {
                    return ParseNumber::invalid_number;
                }

                if (digit >= t_base) {
                    return ParseNumber::invalid_number;
                } else if (value > max_before_multiply) {
                    return ParseNumber::out_of_range;
                }

                value = t_base * value + digit;

                if (value < digit) {
                    return ParseNumber::out_of_range;
                }

            }

            t = value;

            return ParseNumber::ok;

        }

        template <std::signed_integral T>
        ParseNumber parse_signed_integer(std::string_view str, T& t, int base) {

            using U = std::make_unsigned_t<T>;
            using limits = std::numeric_limits<T>;

            static constexpr auto max_value = static_cast<U>(limits::max());

            auto negative = false;

            if (! str.empty()) {
                negative = str[0] == '-';
                if (negative || str[0] == '+') {
                    str = str.substr(1);
                }
            }

            U u {};
            auto rc = parse_unsigned_integer<U>(str, u, base);

            if (rc != ParseNumber::ok) {
                return rc;
            } else if (u > max_value + static_cast<T>(negative)) {
                return ParseNumber::out_of_range;
            }

            if (negative && u != 0) {
                t = T{-1} - static_cast<T>(u - 1);
            } else {
                t = static_cast<T>(u);
            }

            return ParseNumber::ok;

        }

    }

    template <std::integral T>
    ParseNumber parse_number(std::string_view str, T& t, int base = 10) {
        if (base < 0 || base == 1 || base > 36) {
            return ParseNumber::invalid_base;
        }
        if constexpr (std::signed_integral<T>) {
            return Detail::parse_signed_integer<T>(str, t, base);
        } else {
            return Detail::parse_unsigned_integer<T>(str, t, base);
        }
    }

    template <std::floating_point T>
    ParseNumber parse_number(std::string_view str, T& t) {

        if (str.empty() || ! ascii_isgraph(str[0])) {
            return ParseNumber::invalid_number;
        }

        T rc;
        std::string str_copy {str};
        char* endptr {nullptr};
        errno = 0;

        if constexpr (sizeof(T) <= sizeof(float)) {
            rc = static_cast<T>(std::strtof(str_copy.data(), &endptr));
        } else if constexpr (sizeof(T) <= sizeof(double)) {
            rc = static_cast<T>(std::strtod(str_copy.data(), &endptr));
        } else {
            rc = static_cast<T>(std::strtold(str_copy.data(), &endptr));
        }

        int err = errno;

        if (err == 0) {
            t = rc;
            if (endptr == str_copy.data() + str_copy.size()) {
                return ParseNumber::ok;
            } else {
                return ParseNumber::invalid_number;
            }
        } else if (err == ERANGE) {
            return ParseNumber::out_of_range;
        } else {
            return ParseNumber::invalid_number;
        }

    }

    template <std::integral T>
    std::optional<T> parse_number_maybe(std::string_view str, int base = 10) {
        T t {};
        if (parse_number(str, t, base) == ParseNumber::ok) {
            return t;
        } else {
            return {};
        }
    }

    template <std::floating_point T>
    std::optional<T> parse_number_maybe(std::string_view str) {
        T t {};
        if (parse_number(str, t) == ParseNumber::ok) {
            return t;
        } else {
            return {};
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

    // I/O utilities

    class Cstdio {

    public:

        class iterator:
        public InputIterator<iterator, const std::string> {
        public:
            iterator() {}
            explicit iterator(Cstdio& io, bool trim_crlf = false);
            const std::string& operator*() const noexcept { return line_; }
            iterator& operator++();
            bool operator==(const iterator& i) const noexcept { return io_ == i.io_; }
        private:
            Cstdio* io_{};
            std::string line_;
            bool trim_{};
        };

        using line_range = std::ranges::subrange<iterator>;

        Cstdio() = default;
        explicit Cstdio(const std::filesystem::path& path, const char* mode = "rb");
        explicit Cstdio(std::FILE* stream) noexcept: stream_(stream) {}
        Cstdio(Cstdio&& io) noexcept: stream_(std::exchange(io.stream_, nullptr)) {}
        Cstdio& operator=(Cstdio&& io) noexcept;
        Cstdio(const Cstdio&) = delete;
        Cstdio& operator=(const Cstdio&) = delete;
        ~Cstdio() noexcept { close(); }

        bool eof() const noexcept { return stream_ != nullptr && std::feof(stream_) != 0; }
        std::FILE* handle() const noexcept { return stream_; }
        line_range lines(bool trim_crlf = false);
        std::size_t read(void* ptr, std::size_t len);
        std::size_t read(std::string& buf, std::size_t pos = 0);
        std::string read(std::size_t len);
        std::string read_line(bool trim_crlf = false);
        void seek(std::ptrdiff_t offset = 0, int from = SEEK_CUR);
        std::ptrdiff_t tell() const;
        std::size_t write(const void* ptr, std::size_t len);
        std::size_t write(std::string_view str) { return write(str.data(), str.size()); }

        static std::string read_file(const std::filesystem::path& path);
        static void write_file(std::string_view str, const std::filesystem::path& path);

    private:

        std::FILE* stream_{nullptr};

        void check(int err) const;
        void close() noexcept;

    };

        inline Cstdio::iterator::iterator(Cstdio& io, bool trim_crlf):
        io_(&io),
        line_(),
        trim_(trim_crlf) {
            ++*this;
        }

        inline Cstdio::iterator& Cstdio::iterator::operator++() {
            line_ = io_->read_line(trim_);
            if (line_.empty() && io_->eof()) {
                io_ = nullptr;
            }
            return *this;
        }

        inline Cstdio::Cstdio(const std::filesystem::path& path, const char* mode) {
            errno = 0;
            stream_ = std::fopen(path.c_str(), mode);
            int err = errno;
            if (stream_ == nullptr) {
                throw std::system_error(std::error_code(err, std::system_category()), path.string());
            }
        }

        inline Cstdio& Cstdio::operator=(Cstdio&& io) noexcept {
            if (&io != this) {
                close();
                stream_ = std::exchange(io.stream_, nullptr);
            }
            return *this;
        }

        inline Cstdio::line_range Cstdio::lines(bool trim_crlf) {
            iterator i(*this, trim_crlf);
            return {i, {}};
        }

        inline std::size_t Cstdio::read(void* ptr, std::size_t len) {
            errno = 0;
            auto n = std::fread(ptr, 1, len, stream_);
            check(errno);
            return n;
        }

        inline std::size_t Cstdio::read(std::string& buf, std::size_t pos) {
            if (pos < buf.size()) {
                return read(buf.data() + pos, buf.size() - pos);
            } else {
                return 0;
            }
        }

        inline std::string Cstdio::read(std::size_t len) {
            std::string str(len, '\0');
            auto n = read(str);
            str.resize(n);
            return str;
        }

        inline std::string Cstdio::read_line(bool trim_crlf) {

            static constexpr auto block_size = 256uz;

            std::string buf;

            for (;;) {

                auto offset = buf.size();
                buf.resize(offset + block_size);
                errno = 0;
                auto rc = std::fgets(&buf[0] + offset, block_size, stream_);
                check(errno);

                if (rc == nullptr) {
                    return buf.substr(0, offset);
                }

                auto endpos = buf.find('\n', offset);

                if (endpos != npos) {
                    buf.resize(endpos + 1);
                    break;
                }

                endpos = buf.find_last_not_of('\0') + 1;

                if (endpos < buf.size() - 1) {
                    buf.resize(endpos);
                    break;
                }

                buf.pop_back();

            }

            if (trim_crlf && ! buf.empty() && buf.back() == '\n') {
                buf.pop_back();
                if (! buf.empty() && buf.back() == '\r') {
                    buf.pop_back();
                }
            }

            return buf;

        }

        inline void Cstdio::seek(std::ptrdiff_t offset, int from) {
            errno = 0;
            std::fseek(stream_, offset, from);
            check(errno);
        }

        inline std::ptrdiff_t Cstdio::tell() const {
            errno = 0;
            auto pos = std::ftell(stream_);
            check(errno);
            return pos;
        }

        inline std::size_t Cstdio::write(const void* ptr, std::size_t len) {
            errno = 0;
            auto n = std::fwrite(ptr, 1, len, stream_);
            check(errno);
            return n;
        }

        inline std::string Cstdio::read_file(const std::filesystem::path& path) {

            static constexpr auto block_size = 4096uz;

            std::string buf;

            if (path.empty() || path == "-") {

                Cstdio io(stdin);
                auto count = 0uz;

                do {
                    auto offset = buf.size();
                    buf.resize(offset + block_size);
                    auto count = io.read(buf.data() + offset, block_size);
                    buf.resize(offset + count);
                } while (count > 0);

            } else {

                Cstdio io(path, "rb");
                io.seek(0, SEEK_END);
                auto size = static_cast<std::size_t>(io.tell());
                io.seek(0, SEEK_SET);
                buf.resize(size);
                io.read(buf.data(), size);

            }

            if (buf.size() < block_size / 2) {
                buf.shrink_to_fit();
            }

            return buf;

        }

        inline void Cstdio::write_file(std::string_view str, const std::filesystem::path& path) {
            if (path.empty() || path == "-") {
                Cstdio io(stdout);
                io.write(str);
            } else {
                Cstdio io(path, "wb");
                io.write(str);
            }
        }

        inline void Cstdio::check(int err) const {
            if (err != 0) {
                throw std::system_error(std::error_code(err, std::system_category()));
            } else if (stream_ != nullptr && std::ferror(stream_)) {
                throw std::system_error(std::make_error_code(std::errc::io_error));
            }
        }

        inline void Cstdio::close() noexcept {
            if (stream_ != nullptr && stream_ != stdin && stream_ != stdout && stream_ != stderr) {
                std::fclose(stream_);
            }
            stream_ = nullptr;
        }

    // Metaprogramming utilities

    template <typename> constexpr bool dependent_false = false;

    // Random number generators

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
                static constexpr std::uint64_t max32 = ~ 0_u32;
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
        constexpr static std::uint64_t max() noexcept { return ~ 0_u64; }

    private:

        static constexpr auto default_seed = 0xcafe'f00d'd15e'a5e5_u64;

        Detail::Uint128 state_;
        Detail::Uint128 delta_;

    };

    constexpr std::uint64_t Pcg::operator()() noexcept {
        static constexpr auto k = 0xda94'2042'e4dd'58b5_u64;
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
