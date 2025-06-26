#pragma once

#include "rs-core/global.hpp"
#include "rs-core/io.hpp"
#include <algorithm>
#include <cerrno>
#include <cstddef>
#include <cstdio>
#include <functional>
#include <ranges>
#include <string>
#include <string_view>
#include <system_error>
#include <unordered_set>
#include <utility>

namespace RS {

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
    constexpr bool ascii_isalpha_w(char c) noexcept { return ascii_isalpha(c) || c == '_'; }
    constexpr bool ascii_isalnum(char c) noexcept { return ascii_isdigit(c) || ascii_isalpha(c); }
    constexpr bool ascii_isalnum_w(char c) noexcept { return ascii_isalnum(c) || c == '_'; }
    constexpr bool ascii_isgraph(char c) noexcept { return c >= '!' && c <= '~'; }
    constexpr bool ascii_isprint(char c) noexcept { return c >= ' ' && c <= '~'; }
    constexpr bool ascii_ispunct(char c) noexcept { return ascii_isgraph(c) && ! ascii_isalnum(c); }
    constexpr bool ascii_ispunct_w(char c) noexcept { return ascii_ispunct(c) && c != '_'; }
    constexpr char ascii_tolower(char c) noexcept { return static_cast<char>(ascii_isupper(c) ? c + 0x20 : c); }
    constexpr char ascii_toupper(char c) noexcept { return static_cast<char>(ascii_islower(c) ? c - 0x20 : c); }

    // String manipulation functions

    inline std::string ascii_lowercase(std::string_view str) {
        std::string out(str);
        std::transform(out.begin(), out.end(), out.begin(), ascii_tolower);
        return out;
    }

    inline std::string ascii_uppercase(std::string_view str) {
        std::string out(str);
        std::transform(out.begin(), out.end(), out.begin(), ascii_toupper);
        return out;
    }

    // XML/HTML Markup

    class Xtag {

    public:

        Xtag() = default;

        explicit Xtag(std::string_view element):
            Xtag(element, stdout) {}

        explicit Xtag(std::string_view element, std::string& out) {
            write_ = [&out] (std::string_view s) { out += s; };
            start(element);
        }

        explicit Xtag(std::string_view element, std::FILE* out) {
            write_ = [out] (std::string_view s) {
                errno = 0;
                std::fwrite(s.data(), 1, s.size(), out);
                auto err = errno;
                if (err != 0) {
                    throw std::system_error(std::error_code(err, std::system_category()));
                }
            };
            start(element);
        }

        explicit Xtag(std::string_view element, Cstdio& out) {
            write_ = [&out] (std::string_view s) { out.write(s); };
            start(element);
        }

        virtual ~Xtag() noexcept {
            try {
                stop();
            }
            catch (...) {}
        }

        Xtag(Xtag&& t) noexcept:
            tag_(std::exchange(t.tag_, std::string())),
            write_(std::move(t.write_)),
            n_lines_(std::exchange(t.n_lines_, false)) {}

        Xtag& operator=(Xtag&& t) noexcept {
            if (&t != this) {
                stop();
                tag_ = std::exchange(t.tag_, std::string());
                write_ = std::move(t.write_);
                n_lines_ = std::exchange(t.n_lines_, false);
            }
            return *this;
        }

        Xtag(const Xtag&) = delete;
        Xtag& operator=(const Xtag&) = delete;

    protected:

        void clear() noexcept {
            tag_.clear();
            write_ = {};
            n_lines_ = 0;
        }

        void start(std::string_view element) {

            auto lf_pos = element.find_last_not_of('\n') + 1;

            if (lf_pos == 0) {
                return;
            }

            n_lines_ = element.size() - lf_pos;
            element = element.substr(0, lf_pos);

            if (element.front() == '<' && element.back() == '>') {
                element = element.substr(1, lf_pos - 2);
            }

            std::string opening{'<'};
            opening += element;
            opening += '>';
            write_(opening);

            if (n_lines_ >= 2) {
                write_("\n");
            }

            if (element.back() == '/') {
                stop();
            } else {
                auto end_of_tag = std::ranges::find_if_not(element, ascii_isalnum_w);
                tag_.assign(element.data(), end_of_tag);
            }

        }

        void stop() {
            if (write_) {
                if (! tag_.empty()) {
                    write_("</" + tag_ + ">");
                }
                if (n_lines_ > 0) {
                    write_("\n");
                }
            }
            clear();
        }

        std::string tag() const {
            return tag_;
        }

    private:

        std::string tag_;
        std::function<void(std::string_view)> write_;
        std::size_t n_lines_{};

    };

    class Htag:
    public Xtag {

    public:

        Htag() = default;
        explicit Htag(std::string_view element): Htag(element, stdout) {}
        explicit Htag(std::string_view element, std::string& out): Xtag(element, out) { init(); }
        explicit Htag(std::string_view element, std::FILE* out): Xtag(element, out) { init(); }
        explicit Htag(std::string_view element, Cstdio& out): Xtag(element, out) { init(); }
        Htag(const Htag&) = delete;
        Htag(Htag&& t) = default;
        Htag& operator=(const Htag&) = delete;
        Htag& operator=(Htag&& t) = default;

    private:

        void init() {
            // https://www.w3.org/TR/html5/syntax.html#void-elements
            static const std::unordered_set<std::string> void_tags {
                "area", "base", "br", "col", "embed", "hr", "img", "input", "link", "meta", "param", "source", "track", "wbr"
            };
            if (void_tags.contains(ascii_lowercase(tag()))) {
                clear();
            }
        }

    };

}
