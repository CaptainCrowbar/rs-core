#pragma once

#include "rs-core/character.hpp"
#include "rs-core/format.hpp"
#include "rs-core/global.hpp"
#include <algorithm>
#include <concepts>
#include <cstdlib>
#include <format>
#include <ranges>
#include <set>
#include <string>
#include <string_view>
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
                auto table = ::RS::Detail::signed_enum_table(# __VA_ARGS__); \
                for (auto& [k,v]: table) { \
                    temp_set.insert(static_cast<EnumType>(k)); \
                } \
            } else { \
                auto table = ::RS::Detail::unsigned_enum_table(# __VA_ARGS__); \
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
                return ::RS::Detail::signed_enum_table(# __VA_ARGS__); \
            } else { \
                return ::RS::Detail::unsigned_enum_table(# __VA_ARGS__); \
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

#define RS_BITMASK(EnumType, IntType, ...) \
    enum class EnumType: IntType { \
        __VA_ARGS__ \
    }; \
    [[maybe_unused]] inline void rs_core_bitmask_signature(EnumType) {} \
    [[maybe_unused]] inline const std::set<EnumType>& enum_values(EnumType) { \
        static const auto static_set = [] { \
            std::set<EnumType> temp_set {}; \
            auto table = ::RS::Detail::unsigned_enum_table(# __VA_ARGS__); \
            for (auto& [k,v]: table) { \
                temp_set.insert(static_cast<EnumType>(k)); \
            } \
            return temp_set; \
        }(); \
        return static_set; \
    } \
    [[maybe_unused]] inline std::string to_string(EnumType t) { \
        static_assert(std::unsigned_integral<IntType>); \
        static const auto static_table = ::RS::Detail::linear_enum_table(# __VA_ARGS__); \
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
    }

namespace RS {

    namespace Detail {

        enum class EnumCase: int {
            none,
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
        std::vector<std::pair<T, std::string>> make_enum_list(const char* va_args) {

            static constexpr std::string_view whitespace = "\t\n\r ";

            std::string_view va_view = va_args;
            std::vector<std::pair<T, std::string>> list;
            T index = 0;
            auto begin_field = 0uz;

            for (;;) {

                auto comma_pos = va_view.find(',', begin_field);
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

                if (comma_pos >= va_view.size()) {
                    break;
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

    template <typename T>
    concept AutoBitmask = requires (T t) {
        { rs_core_bitmask_signature(t) };
    };

    template <typename T>
    concept AutoEnum = AutoBitmask<T>
        || requires (T t) {
            { rs_core_enum_signature(t) };
        };

}

template <::RS::AutoEnum T>
struct std::formatter<T> {

public:

    constexpr auto parse(std::format_parse_context& ctx) {
        using namespace ::RS::Detail;
        auto it = ctx.begin();
        for (; it != ctx.end() && *it != '}'; ++it) {
            if (*it == 's' && case_ == EnumCase::none) {
                case_ = EnumCase::sentence;
            } else if (*it == 't' && case_ == EnumCase::none) {
                case_ = EnumCase::title;
            } else if (is_enum_delimiter_char(*it) && delimiter_ == '_') {
                delimiter_ = *it;
            } else {
                throw std::format_error{std::format("Invalid format: {:?}", *it)};
            }
        }
        return it;
    }

    template <typename FormatContext>
    auto format(const T& t, FormatContext& ctx) const {
        using namespace ::RS::Detail;
        auto out = to_string(t);
        reformat_enum(out, case_, delimiter_);
        return std::ranges::copy(out, ctx.out()).out;
    }

private:

    ::RS::Detail::EnumCase case_ = ::RS::Detail::EnumCase::none;
    char delimiter_ = '_';

};
