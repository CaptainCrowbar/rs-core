#pragma once

#include "rs-core/global.hpp"
#include "rs-core/iterator.hpp"
#include <cerrno>
#include <compare>
#include <cstddef>
#include <cstdio>
#include <filesystem>
#include <ranges>
#include <string>
#include <string_view>
#include <system_error>
#include <utility>

namespace RS {

    class Cstdio {

    public:

        class iterator:
        public InputIterator<iterator, const std::string> {
        public:
            iterator() {}
            explicit iterator(Cstdio& io);
            const std::string& operator*() const noexcept { return line_; }
            iterator& operator++();
            bool operator==(const iterator& i) const noexcept { return io_ == i.io_; }
        private:
            Cstdio* io_{};
            std::string line_;
        };

        using line_range = std::ranges::subrange<iterator>;

        Cstdio() = default;
        explicit Cstdio(const std::filesystem::path& path, const char* mode = "rb");
        explicit Cstdio(std::FILE* stream) noexcept: stream_(stream) {}
        Cstdio(Cstdio&& io) noexcept: stream_(std::exchange(io.stream_, nullptr)) {}
        Cstdio& operator=(Cstdio&& io) noexcept;
        Cstdio(const Cstdio&) = delete;
        Cstdio& operator=(const Cstdio&) = delete;
        ~Cstdio() noexcept { close_stream(false); }

        void close() { close_stream(true); }
        void flush();
        bool get(char& c);
        std::FILE* handle() const noexcept { return stream_; }
        line_range lines();
        void put(char c);
        std::size_t read(void* ptr, std::size_t len);
        std::size_t read_into(std::string& buf, std::size_t pos = 0);
        std::string read_line();
        std::string read_str(std::size_t len);
        void seek(std::ptrdiff_t offset = 0, int from = SEEK_CUR);
        std::ptrdiff_t tell() const;
        std::size_t write(const void* ptr, std::size_t len);
        std::size_t write_str(std::string_view str) { return write(str.data(), str.size()); }

        static std::string read_file(const std::filesystem::path& path);
        static void write_file(std::string_view str, const std::filesystem::path& path);

    private:

        std::FILE* stream_{nullptr};

        void check(int err) const;
        void close_stream(bool checked);

    };

        inline Cstdio::iterator::iterator(Cstdio& io):
        io_(&io),
        line_() {
            ++*this;
        }

        inline Cstdio::iterator& Cstdio::iterator::operator++() {
            line_ = io_->read_line();
            if (line_.empty()) {
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
                close_stream(false);
                stream_ = std::exchange(io.stream_, nullptr);
            }
            return *this;
        }

        inline void Cstdio::flush() {
            if (stream_ != nullptr) {
                errno = 0;
                std::fflush(stream_);
                check(errno);
            }
        }

        inline bool Cstdio::get(char& c) {
            errno = 0;
            auto x = std::fgetc(stream_);
            check(errno);
            if (x == EOF) {
                return false;
            }
            c = static_cast<char>(static_cast<unsigned char>(x));
            return true;
        }

        inline Cstdio::line_range Cstdio::lines() {
            return {iterator{*this}, {}};
        }

        inline void Cstdio::put(char c) {
            auto x = static_cast<int>(static_cast<unsigned char>(c));
            errno = 0;
            std::fputc(x, stream_);
            check(errno);
        }

        inline std::size_t Cstdio::read(void* ptr, std::size_t len) {
            errno = 0;
            auto n = std::fread(ptr, 1, len, stream_);
            check(errno);
            return n;
        }

        inline std::size_t Cstdio::read_into(std::string& buf, std::size_t pos) {
            if (pos < buf.size()) {
                return read(buf.data() + pos, buf.size() - pos);
            } else {
                return 0;
            }
        }

        inline std::string Cstdio::read_line() {

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

            return buf;

        }

        inline std::string Cstdio::read_str(std::size_t len) {
            std::string str(len, '\0');
            auto n = read_into(str);
            str.resize(n);
            return str;
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
                io.write_str(str);
            } else {
                Cstdio io(path, "wb");
                io.write_str(str);
            }
        }

        inline void Cstdio::check(int err) const {
            if (err != 0) {
                throw std::system_error(std::error_code(err, std::system_category()));
            } else if (stream_ != nullptr && std::ferror(stream_)) {
                throw std::system_error(std::make_error_code(std::errc::io_error));
            }
        }

        inline void Cstdio::close_stream(bool checked) {
            if (stream_ == stdin || stream_ == stdout || stream_ == stderr) {
                stream_ = nullptr;
            } else if (stream_ != nullptr) {
                errno = 0;
                std::fclose(stream_);
                int err = errno;
                stream_ = nullptr;
                if (checked) {
                    check(err);
                }
            }
        }

}
