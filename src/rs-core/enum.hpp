#pragma once

#include "rs-core/character.hpp"
#include "rs-core/format.hpp"
#include "rs-core/global.hpp"
#include <algorithm>
#include <concepts>
#include <format>
#include <ranges>
#include <set>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

#define RS_ENUM(EnumType, IntType, ...) \
    enum class EnumType: IntType { \
        __VA_ARGS__ \
    }; \
    [[maybe_unused]] inline void rs_core_enum_signature(EnumType) {} \
    [[maybe_unused]] inline const std::set<EnumType>& enum_values(EnumType) { \
        static const auto static_set = [] { \
            std::set<EnumType> temp_set; \
            if constexpr (std::signed_integral<IntType>) { \
                auto table = RS::Detail::signed_enum_table(# __VA_ARGS__); \
                for (auto& [k,v]: table) { \
                    temp_set.insert(static_cast<EnumType>(k)); \
                } \
            } else { \
                auto table = RS::Detail::unsigned_enum_table(# __VA_ARGS__); \
                for (auto& [k,v]: table) { \
                    temp_set.insert(static_cast<EnumType>(k)); \
                } \
            } \
            return temp_set; \
        }(); \
        return static_set; \
    } \
    [[maybe_unused]] inline std::string to_string(EnumType t) { \
        static const auto static_table = [] { \
            if constexpr (std::signed_integral<IntType>) { \
                return RS::Detail::signed_enum_table(# __VA_ARGS__); \
            } else { \
                return RS::Detail::unsigned_enum_table(# __VA_ARGS__); \
            } \
        }(); \
        auto index = static_cast<IntType>(t); \
        auto it = static_table.find(index); \
        if (it == static_table.end()) { \
            return std::to_string(index); \
        } else { \
            return it->second; \
        } \
    }

#define RS_BITMASK(BitmaskType, IntType, ...) \
    enum class BitmaskType: IntType { \
        __VA_ARGS__ \
    }; \
    [[maybe_unused]] inline void rs_core_bitmask_signature(BitmaskType) {} \
    [[maybe_unused]] inline const std::set<BitmaskType>& enum_values(BitmaskType) { \
        static const auto static_set = [] { \
            std::set<BitmaskType> temp_set {}; \
            auto table = RS::Detail::unsigned_enum_table(# __VA_ARGS__); \
            for (auto& [k,v]: table) { \
                temp_set.insert(static_cast<BitmaskType>(k)); \
            } \
            return temp_set; \
        }(); \
        return static_set; \
    } \
    [[maybe_unused]] inline std::string to_string(BitmaskType t) { \
        static_assert(std::unsigned_integral<IntType>); \
        static const auto static_table = RS::Detail::linear_enum_table(# __VA_ARGS__); \
        auto index = static_cast<unsigned long long>(t); \
        if (index == 0) { \
            return "none"; \
        } \
        auto residue = index; \
        std::string str; \
        for (const auto& [number,name]: static_table) { \
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
    [[maybe_unused]] constexpr bool operator!(BitmaskType t) noexcept { \
        return ! static_cast<bool>(t); \
    } \
    [[maybe_unused]] constexpr BitmaskType operator~(BitmaskType t) noexcept { \
        return static_cast<BitmaskType>(~ static_cast<IntType>(t)); \
    } \
    [[maybe_unused]] constexpr BitmaskType operator&(BitmaskType t, BitmaskType u) noexcept { \
        return static_cast<BitmaskType>(static_cast<IntType>(t) & static_cast<IntType>(u)); \
    } \
    [[maybe_unused]] constexpr BitmaskType operator|(BitmaskType t, BitmaskType u) noexcept { \
        return static_cast<BitmaskType>(static_cast<IntType>(t) | static_cast<IntType>(u)); \
    } \
    [[maybe_unused]] constexpr BitmaskType operator^(BitmaskType t, BitmaskType u) noexcept { \
        return static_cast<BitmaskType>(static_cast<IntType>(t) ^ static_cast<IntType>(u)); \
    } \
    [[maybe_unused]] constexpr BitmaskType& operator&=(BitmaskType& t, BitmaskType u) noexcept { \
        return t = t & u; \
    } \
    [[maybe_unused]] constexpr BitmaskType& operator|=(BitmaskType& t, BitmaskType u) noexcept { \
        return t = t | u; \
    } \
    [[maybe_unused]] constexpr BitmaskType& operator^=(BitmaskType& t, BitmaskType u) noexcept { \
        return t = t ^ u; \
    }

namespace RS {

    template <typename T>
    concept AutoBitmask = requires (const T t) {
        { rs_core_bitmask_signature(t) };
    };

    template <typename T>
    concept AutoEnum = AutoBitmask<T>
        || requires (const T t) {
            { rs_core_enum_signature(t) };
        };

    namespace Detail {

        enum class EnumCase: int {
            none,
            integer,
            sentence,
            title,
        };

        constexpr bool is_enum_delimiter_char(char c) noexcept {
            return c == ' '
                || (ascii_ispunct(c)
                    && c != '(' && c != ')' && c != '[' && c != ']' && c != '{' && c != '}' && c != '_');
        }

        inline void reformat_enum(std::string& str, EnumCase casing, char delimiter) {

            if (casing == EnumCase::sentence) {

                auto any_alpha = false;

                for (auto& c: str) {
                    if (ascii_isalpha(c)) {
                        c = any_alpha ? ascii_tolower(c) : ascii_toupper(c);
                        any_alpha = true;
                    }
                }

            } else if (casing == EnumCase::title) {

                auto was_alpha = false;

                for (auto& c: str) {
                    auto is_alpha = ascii_isalpha(c);
                    if (is_alpha) {
                        c = was_alpha ? ascii_tolower(c) : ascii_toupper(c);
                    }
                    was_alpha = is_alpha;
                }

            }

            if (delimiter != '_') {
                std::ranges::replace(str, '_', delimiter);
            }

        }

        template <std::integral T>
        T parse_enum_index(std::string_view str) {

            auto fail = [str] [[noreturn]] {
                throw std::invalid_argument(std::format("Invalid enumeration index: {:?}", str));
            };

            if (str.empty()) {

                fail();

            } else if (str.size() == 3 && str[0] == '\'' && str[2] == '\'') {

                return static_cast<T>(str[1]);

            } else if (str.size() == 4 && str[0] == '\'' && str[1] == '\\' && str[3] == '\'') {

                char c;

                switch (str[2]) {
                    case 'a':  c = '\a'; break;
                    case 'b':  c = '\b'; break;
                    case 'f':  c = '\f'; break;
                    case 'n':  c = '\n'; break;
                    case 'r':  c = '\r'; break;
                    case 't':  c = '\t'; break;
                    case 'v':  c = '\v'; break;
                    default:   fail();
                }

                return static_cast<T>(c);

            } else if (ascii_isdigit(str[0]) || str[0] == '+' || str[0] == '-') {

                auto maybe_index = parse_number_maybe<T>(str, 0);

                if (! maybe_index) {
                    fail();
                }

                return *maybe_index;

            } else {

                fail();

            }

        }

        inline std::string_view ascii_trim(std::string_view str) noexcept {
            auto i = str.find_first_not_of(ascii_whitespace);
            if (i == npos) {
                return str.substr(0, 0);
            }
            auto j = str.find_last_not_of(ascii_whitespace);
            return str.substr(i, j - i + 1);
        }

        template <std::integral T>
        std::vector<std::pair<T, std::string>> make_enum_list(const char* va_args) {

            std::string_view va_view = va_args;
            std::vector<std::pair<T, std::string>> list;
            auto field_pos = 0uz;
            T index = 0;

            for (;;) {

                auto comma_pos = va_view.find(',', field_pos);
                auto field = ascii_trim(va_view.substr(field_pos, comma_pos - field_pos));

                if (! field.empty()) {

                    auto eq_pos = field.find('=');

                    if (eq_pos != npos) {
                        auto index_str = ascii_trim(field.substr(eq_pos + 1));
                        index = parse_enum_index<T>(index_str);
                    }

                    auto name = ascii_trim(field.substr(0, eq_pos));
                    list.push_back({index, std::string{name}});
                    ++index;

                }

                if (comma_pos >= va_view.size()) {
                    break;
                }

                field_pos = comma_pos + 1;

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

}

template <RS::AutoEnum T>
struct std::formatter<T>:
RS::CommonFormatter {

    RS::Detail::EnumCase mode = RS::Detail::EnumCase::none;
    char delimiter = '_';

    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {

        using namespace RS::Detail;

        auto it = ctx.begin();

        for (; it != ctx.end() && *it != '}'; ++it) {
            if (*it == 'i' && mode == EnumCase::none && delimiter == '_') {
                mode = EnumCase::integer;
            } else if (*it == 's' && mode == EnumCase::none) {
                mode = EnumCase::sentence;
            } else if (*it == 't' && mode == EnumCase::none) {
                mode = EnumCase::title;
            } else if (is_enum_delimiter_char(*it) && mode != EnumCase::integer && delimiter == '_') {
                delimiter = *it;
            } else {
                throw std::format_error{"Invalid format"};
            }
        }

        return it;

    }

    template <typename FormatContext>
    auto format(const T& t, FormatContext& ctx) const {

        using namespace RS::Detail;
        using U = std::underlying_type_t<T>;

        std::string str;

        if (mode == EnumCase::integer) {
            str = std::to_string(static_cast<U>(t));
        } else {
            str = to_string(t);
            reformat_enum(str, mode, delimiter);
        }

        return write_out(str, ctx.out());

    }

};
