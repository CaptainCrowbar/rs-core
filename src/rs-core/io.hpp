#pragma once

#include "rs-core/enum.hpp"
#include "rs-core/global.hpp"
#include "rs-core/iterator.hpp"
#include <algorithm>
#include <cerrno>
#include <compare>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <format>
#include <iterator>
#include <ranges>
#include <stdexcept>
#include <string>
#include <string_view>
#include <system_error>
#include <utility>

#ifdef _WIN32

    extern "C" {
        _declspec(dllimport) void* __stdcall GetStdHandle(unsigned long nStdHandle);
        _declspec(dllimport) int __stdcall GetConsoleMode(void* hConsoleHandle, unsigned long* lpMode);
    }

#else

    #include <unistd.h>

#endif

namespace RS {

    RS_ENUM(IOMode, int,
        read_only,
        write_only,
        read_write,
        append,
    )

    RS_ENUM(IOSeek, int,
        current  = SEEK_CUR,
        end      = SEEK_END,
        set      = SEEK_SET,
    )

    class IO {

    public:

        using enum IOMode;
        using enum IOSeek;

        class iterator:
        public Iterator<iterator, const std::string, std::input_iterator_tag> {
        public:
            iterator() {}
            explicit iterator(IO& io);
            const std::string& operator*() const noexcept { return line_; }
            iterator& operator++();
            bool operator==(const iterator& i) const noexcept { return io_ == i.io_; }
            bool operator==(std::nullptr_t) const noexcept { return io_ == nullptr; }
        private:
            IO* io_{};
            std::string line_;
        };

        using line_range = std::ranges::subrange<iterator, std::nullptr_t>;

        IO() = default;
        IO(const IO&) = delete;
        IO(IO&&) = default;
        virtual ~IO() = default;
        IO& operator=(const IO&) = delete;
        IO& operator=(IO&&) = default;

        virtual bool can_seek() const noexcept = 0;
        virtual void close() = 0;
        virtual void flush() {}
        virtual bool get(char& c) { return read(&c, 1) == 1; }
        virtual void put(char c) { write(&c, 1); }
        virtual bool is_tty() const noexcept = 0;
        virtual std::size_t read(void* ptr, std::size_t len) = 0;
        virtual std::string read_all();
        virtual std::size_t read_into(std::string& buf, std::size_t pos = 0);
        virtual std::string read_line();
        virtual std::string read_str(std::size_t len);
        virtual void seek(std::ptrdiff_t offset = 0, IOSeek from = current) = 0;
        virtual std::ptrdiff_t tell() const = 0;
        virtual std::size_t write(const void* ptr, std::size_t len) = 0;
        virtual std::size_t write_str(std::string_view str) { return write(str.data(), str.size()); }

        line_range lines() { return {iterator{*this}, {}}; }

        template <typename... Args>
            std::size_t print(std::format_string<const Args&...> fmt, const Args&... args) {
                return write_str(std::format(fmt, args...));
            }

        template <typename... Args>
            std::size_t println(std::format_string<const Args&...> fmt, const Args&... args) {
                auto n = write_str(std::format(fmt, args...));
                put('\n');
                return n + 1;
            }

    protected:

        #ifdef _WIN32

            static std::wstring quick_wstring(const char* cptr) {
                std::wstring wstr;
                for (;*cptr != 0; ++cptr) {
                    wstr += static_cast<wchar_t>(*cptr);
                }
                return wstr;
            }

        #endif

    };

        inline IO::iterator::iterator(IO& io):
        io_(&io),
        line_() {
            ++*this;
        }

        inline IO::iterator& IO::iterator::operator++() {
            line_ = io_->read_line();
            if (line_.empty()) {
                io_ = nullptr;
            }
            return *this;
        }

        inline std::string IO::read_all() {

            static constexpr auto block_size = 4096uz;

            std::string buf;

            if (can_seek()) {

                auto start = tell();
                seek(0, end);
                auto signed_size = tell() - start;
                seek(- signed_size, current);
                auto size = static_cast<std::size_t>(signed_size);
                buf.resize(size);
                read(buf.data(), size);

            } else {

                auto count = 0uz;

                do {
                    auto offset = buf.size();
                    buf.resize(offset + block_size);
                    count = read(buf.data() + offset, block_size);
                    buf.resize(offset + count);
                } while (count > 0);

            }

            if (buf.size() < block_size / 2) {
                buf.shrink_to_fit();
            }

            return buf;

        }

        inline std::size_t IO::read_into(std::string& buf, std::size_t pos) {
            if (pos < buf.size()) {
                return read(buf.data() + pos, buf.size() - pos);
            } else {
                return 0;
            }
        }

        inline std::string IO::read_line() {
            std::string buf;
            char c{};
            while (get(c)) {
                buf += c;
                if (c == '\n') {
                    break;
                }
            }
            return buf;
        }

        inline std::string IO::read_str(std::size_t len) {
            std::string str(len, '\0');
            auto n = read_into(str);
            str.resize(n);
            return str;
        }

    class Cstdio:
    public IO {

    public:

        Cstdio() = default;
        explicit Cstdio(const std::filesystem::path& path, IOMode mode = read_only);
        explicit Cstdio(const std::filesystem::path& path, const char* mode);
        explicit Cstdio(std::FILE* stream) noexcept: stream_(stream), owner_(! file_is_stdio(stream)) {}
        explicit Cstdio(std::FILE* stream, bool own);
        Cstdio(Cstdio&& io) noexcept: stream_(std::exchange(io.stream_, nullptr)) {}
        Cstdio& operator=(Cstdio&& io) noexcept;
        Cstdio(const Cstdio&) = delete;
        Cstdio& operator=(const Cstdio&) = delete;
        ~Cstdio() noexcept override { close_stream(false); }

        bool can_seek() const noexcept override { return std::fseek(stream_, 0, SEEK_CUR) == 0; }
        void close() override { close_stream(true); }
        void flush() override;
        bool get(char& c) override;
        bool is_tty() const noexcept override { return file_is_tty(stream_); }
        void put(char c) override;
        std::size_t read(void* ptr, std::size_t len) override;
        std::string read_line() override;
        void seek(std::ptrdiff_t offset = 0, IOSeek from = current) override;
        std::ptrdiff_t tell() const override;
        std::size_t write(const void* ptr, std::size_t len) override;

        std::FILE* handle() const noexcept { return stream_; }
        std::FILE* release() noexcept;

    private:

        friend class Xterm;

        std::FILE* stream_ = nullptr;
        bool owner_ = false;

        void check(int err) const;
        void close_stream(bool checked);

        static bool file_is_stdio(std::FILE* stream) noexcept;
        static bool file_is_tty(std::FILE* stream) noexcept;
        static bool file_is_tty(int fd) noexcept;

        static const char* translate_mode(IOMode mode) noexcept;

    };

        inline Cstdio::Cstdio(const std::filesystem::path& path, IOMode mode):
        Cstdio(path, translate_mode(mode)) {}

        inline Cstdio::Cstdio(const std::filesystem::path& path, const char* mode) {
            if ((path.empty() || path == "-") && std::string_view{mode}.find('+') != npos) {
                if (mode[0] == 'r') {
                    stream_ = stdin;
                } else {
                    stream_ = stdout;
                }
            } else {
                errno = 0;
                #ifdef _WIN32
                    auto wmode = quick_wstring(mode);
                    stream_ = _wfopen(path.c_str(), wmode.data());
                #else
                    stream_ = std::fopen(path.c_str(), mode);
                #endif
                int err = errno;
                if (stream_ == nullptr) {
                    throw std::system_error(std::error_code(err, std::system_category()), path.string());
                }
                owner_ = true;
            }
        }

        inline Cstdio::Cstdio(std::FILE* stream, bool own):
        stream_(stream),
        owner_(own) {
            if (file_is_stdio(stream) && own) {
                throw std::invalid_argument("Can't take ownership of a standard stream");
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

        inline void Cstdio::seek(std::ptrdiff_t offset, IOSeek from) {
            errno = 0;
            std::fseek(stream_, static_cast<long>(offset), static_cast<int>(from));
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

        inline std::FILE* Cstdio::release() noexcept {
            owner_ = false;
            return std::exchange(stream_, nullptr);
        }

        inline void Cstdio::check(int err) const {
            if (err != 0) {
                throw std::system_error(std::error_code(err, std::system_category()));
            } else if (stream_ != nullptr && std::ferror(stream_)) {
                throw std::system_error(std::make_error_code(std::errc::io_error));
            }
        }

        inline void Cstdio::close_stream(bool checked) {
            if (owner_) {
                errno = 0;
                std::fclose(stream_);
                int err = errno;
                stream_ = nullptr;
                if (checked) {
                    check(err);
                }
            }
        }

        inline bool Cstdio::file_is_stdio(std::FILE* stream) noexcept {
            return stream == stdin || stream == stdout || stream == stderr;
        }

        inline bool Cstdio::file_is_tty(std::FILE* stream) noexcept {
            if (stream == stdin) {
                return file_is_tty(0);
            } else if (stream == stdout) {
                return file_is_tty(1);
            } else if (stream == stderr) {
                return file_is_tty(2);
            } else {
                return false;
            }
        }

        inline bool Cstdio::file_is_tty(int fd) noexcept {
            #ifdef _WIN32
                static constexpr auto std_input_handle = static_cast<unsigned long>(-10);
                auto handle = GetStdHandle(std_input_handle - fd);
                auto mode = 0ul;
                return GetConsoleMode(handle, &mode) != 0;
            #else
                return ::isatty(fd) != 0;
            #endif
        }

        inline const char* Cstdio::translate_mode(IOMode mode) noexcept {
            switch (mode) {
                case read_only:   return "rb";
                case write_only:  return "wb";
                case read_write:  return "rb+";
                case append:      return "ab";
                default:          std::unreachable();
            }
        }

    class StringBuffer:
    public IO {

    public:

        StringBuffer() noexcept { reset(); }
        explicit StringBuffer(std::string& str, IOMode mode = read_write) noexcept;
        StringBuffer(const StringBuffer&) = delete;
        StringBuffer(StringBuffer&& sb);
        StringBuffer& operator=(const StringBuffer&) = delete;
        StringBuffer& operator=(StringBuffer&& sb);

        bool can_seek() const noexcept override { return true; }
        void close() override { reset(); }
        bool is_tty() const noexcept override { return false; }
        std::size_t read(void* ptr, std::size_t len) override;
        std::string read_all() override;
        std::string read_line() override;
        std::string read_str(std::size_t len) override;
        void seek(std::ptrdiff_t offset, IOSeek from = current) override;
        std::ptrdiff_t tell() const override { return static_cast<std::ptrdiff_t>(pos_); }
        std::size_t write(const void* ptr, std::size_t len) override;

        void clear() noexcept;
        bool empty() const noexcept { return buf_ptr_->empty(); }
        std::size_t size() const noexcept { return buf_ptr_->size(); }
        std::string_view view() const noexcept { return *buf_ptr_; }

    private:

        std::string buf_str_;
        std::string* buf_ptr_;
        std::size_t pos_;
        bool owner_;

        void reset() noexcept;

    };

        inline StringBuffer::StringBuffer(std::string& str, IOMode mode) noexcept:
        buf_ptr_(&str),
        pos_(mode == append ? str.size() : 0uz),
        owner_(false) {}

        inline StringBuffer::StringBuffer(StringBuffer&& sb):
        buf_str_(std::move(sb.buf_str_)),
        buf_ptr_(sb.owner_ ? &buf_str_ : sb.buf_ptr_),
        pos_(sb.pos_),
        owner_(sb.owner_) {
            sb.reset();
        }

        inline StringBuffer& StringBuffer::operator=(StringBuffer&& sb) {
            buf_str_ = std::move(sb.buf_str_);
            buf_ptr_ = sb.owner_ ? &buf_str_ : sb.buf_ptr_;
            pos_ = sb.pos_;
            owner_ = sb.owner_;
            sb.reset();
            return *this;
        }

        inline std::size_t StringBuffer::read(void* ptr, std::size_t len) {
            auto n = std::min(len, buf_ptr_->size() - pos_);
            std::memcpy(ptr, buf_ptr_->data() + pos_, n);
            pos_ += n;
            return n;
        }

        inline std::string StringBuffer::read_all() {
            auto result = buf_ptr_->substr(pos_);
            pos_ = buf_ptr_->size();
            return result;
        }

        inline std::string StringBuffer::read_line() {
            auto next = buf_ptr_->find('\n', pos_);
            if (next == npos) {
                next = buf_ptr_->size();
            } else {
                ++next;
            }
            auto result = buf_ptr_->substr(pos_, next - pos_);
            pos_ = next;
            return result;
        }

        inline std::string StringBuffer::read_str(std::size_t len) {
            auto n = std::min(len, buf_ptr_->size() - pos_);
            auto result = buf_ptr_->substr(pos_, n);
            pos_ += n;
            return result;
        }

        inline void StringBuffer::seek(std::ptrdiff_t offset, IOSeek from) {
            auto signed_pos = static_cast<std::ptrdiff_t>(pos_);
            auto signed_size = static_cast<std::ptrdiff_t>(buf_ptr_->size());
            switch (from) {
                case set:  signed_pos = offset; break;
                case end:  signed_pos = signed_size - offset; break;
                default:   signed_pos += offset; break;
            }
            pos_ = static_cast<std::size_t>(std::clamp(signed_pos, 0z, signed_size));
        }

        inline std::size_t StringBuffer::write(const void* ptr, std::size_t len) {
            buf_ptr_->resize(pos_ + len);
            std::memcpy(buf_ptr_->data() + pos_, ptr, len);
            pos_ = buf_ptr_->size();
            return len;
        }

        inline void StringBuffer::clear() noexcept {
            buf_ptr_->clear();
            pos_ = 0;
        }

        inline void StringBuffer::reset() noexcept {
            buf_str_.clear();
            buf_ptr_ = &buf_str_;
            pos_ = 0;
            owner_ = true;
        }

}
