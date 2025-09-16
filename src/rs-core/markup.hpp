#pragma once

#include "rs-core/character.hpp"
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
            write_ = [&out] (std::string_view s) { out.write_str(s); };
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
                auto tag_size = static_cast<std::size_t>(end_of_tag - element.begin());
                tag_.assign(element.data(), tag_size);
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
