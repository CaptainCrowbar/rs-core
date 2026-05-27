#pragma once

#include "rs-core/global.hpp"
#include <algorithm>
#include <concepts>
#include <cstddef>
#include <cstring>
#include <format>
#include <iterator>
#include <new>
#include <ranges>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>
#include <zlib.h>

namespace RS {

    class Zlib {

    public:

        class error:
        public std::runtime_error {
        public:
            explicit error(int code, std::string_view details = {});
            int code() const noexcept { return code_; }
        private:
            int code_ = 0;
            static std::string expand_error(int code, std::string_view details);
        };

        struct result {
            std::size_t bytes_in;
            std::size_t bytes_out;
        };

        Zlib() = default;
        explicit Zlib(int level) { set_level(level); }

        int level() const noexcept { return level_; }
        void set_level(int level);

        template <InputSpan IS, OutputBuffer OB>
            result encode(const IS& in, OB& out) const;
        template <InputSpan IS, OutputBuffer OB>
            result encode(const IS& in, OB& out, int level) const;
        template <InputSpan IS, OutputBuffer OB>
            result decode(const IS& in, OB& out) const;

    private:

        int level_ = -1;

        template <InputSpan IS, OutputBuffer OB, std::invocable<z_streamp> Init,
            std::invocable<z_streamp, int> Call, std::invocable<z_streamp> End>
        result encode_or_decode(const IS& in, OB& out, Init zlib_init, Call zlib_call, End zlib_end,
            bool encoding) const;

        static int check_result(int rc);

    };

        inline Zlib::error::error(int code, std::string_view details):
        std::runtime_error{expand_error(code, details)}, code_{code} {}

        inline std::string Zlib::error::expand_error(int code, std::string_view details) {

            static const std::unordered_map<int, const char*> table {

                { Z_OK,             "Z_OK: Success"                            },  // 0
                { Z_STREAM_END,     "Z_STREAM_END: End of stream"              },  // 1
                { Z_NEED_DICT,      "Z_NEED_DICT: Preset dictionary expected"  },  // 2
                { Z_ERRNO,          "Z_ERRNO: I/O error"                       },  // -1
                { Z_STREAM_ERROR,   "Z_STREAM_ERROR: Invalid zlib API call"    },  // -2
                { Z_DATA_ERROR,     "Z_DATA_ERROR: Input data is corrupt"      },  // -3
                { Z_MEM_ERROR,      "Z_MEM_ERROR: Out of memory"               },  // -4
                { Z_BUF_ERROR,      "Z_BUF_ERROR: Output buffer is too short"  },  // -5
                { Z_VERSION_ERROR,  "Z_VERSION_ERROR: Zlib version mismatch"   },  // -6

            };

            auto message = std::format("Zlib error {}: ", code);
            auto it = table.find(code);

            if (it == table.end()) {
                message += "Unknown error";
            } else {
                message += it->second;
            }

            if (! details.empty()) {
                message += ": ";
                message += details;
            }

            return message;

        }

        inline void Zlib::set_level(int level) {
            if (level >= -1 && level <= 9) {
                level_ = level;
            } else {
                throw error(Z_STREAM_ERROR, "Invalid compression level");
            }
        }

        template <InputSpan IS, OutputBuffer OB>
        Zlib::result Zlib::encode(const IS& in, OB& out) const {
            return encode(in, out, level_);
        }

        template <InputSpan IS, OutputBuffer OB>
        Zlib::result Zlib::encode(const IS& in, OB& out, int level) const {
            return encode_or_decode(in, out,
                [level] (z_streamp zsp) { return deflateInit(zsp, level); },
                [] (z_streamp zsp, int flush) { return deflate(zsp, flush); },
                [] (z_streamp zsp) { return deflateEnd(zsp); },
                true);
        }

        template <InputSpan IS, OutputBuffer OB>
        Zlib::result Zlib::decode(const IS& in, OB& out) const {
            return encode_or_decode(in, out,
                [] (z_streamp zsp) { return inflateInit(zsp); },
                [] (z_streamp zsp, int flush) { return inflate(zsp, flush); },
                [] (z_streamp zsp) { return inflateEnd(zsp); },
                false);
        }

        template <InputSpan IS, OutputBuffer OB, std::invocable<z_streamp> Init,
            std::invocable<z_streamp, int> Call, std::invocable<z_streamp> End>
        Zlib::result Zlib::encode_or_decode(const IS& in, OB& out, Init zlib_init, Call zlib_call, End zlib_end,
                bool encoding) const {

            // Call this with lambdas instead of raw Zlib functions to guard
            // against macros in Zlib.

            namespace rs = std::ranges;
            using Byte = rs::range_value_t<OB>;

            static constexpr auto min_io_block = 16uz;
            static constexpr auto max_io_block = 1uz << 20;
            static constexpr auto guess_factor = 4uz;

            z_stream zs;
            std::memset(&zs, 0, sizeof(zs));
            check_result(zlib_init(&zs));
            auto flush = Z_NO_FLUSH;
            auto guess_out_block = rs::size(in);

            if (encoding) {
                guess_out_block /= guess_factor;
            } else {
                guess_out_block *= guess_factor;
            }

            auto out_block = std::clamp(guess_out_block, min_io_block, max_io_block);
            auto in_offset = 0uz;
            auto out_offset = out.size();
            auto initial_out_offset = out_offset;
            out.resize(out_offset + out_block, Byte{});

            for (;;) {

                auto in_ptr = &*rs::begin(in) + in_offset;
                auto in_remaining = rs::size(in) - in_offset;
                auto in_available = std::min(in_remaining, max_io_block);
                auto out_ptr = &*rs::begin(out) + out_offset;
                auto out_remaining = rs::size(out) - out_offset;
                auto out_available = std::min(out_remaining, out_block);

                zs.next_in = const_cast<Bytef*>(reinterpret_cast<const Bytef*>(in_ptr)); // Zlib brain damage
                zs.avail_in = static_cast<uInt>(in_available);
                zs.next_out = reinterpret_cast<Bytef*>(out_ptr);
                zs.avail_out = static_cast<uInt>(out_available);

                auto rc = check_result(zlib_call(&zs, flush));

                in_offset += in_available - zs.avail_in;
                out_offset += out_available - zs.avail_out;

                if (rc == Z_STREAM_END) {
                    break;
                } else if (rc == Z_BUF_ERROR) {
                    out.resize(out_offset + out_block, Byte{});
                } else if (encoding && in_offset == rs::size(in)) {
                    flush = Z_FINISH;
                }

            }

            out.resize(out_offset, Byte{});
            check_result(zlib_end(&zs));

            return {in_offset, out_offset - initial_out_offset};

        }

        inline int Zlib::check_result(int rc) {
            if (rc == Z_OK || rc == Z_BUF_ERROR || rc == Z_STREAM_END) {
                return rc;
            } else if (rc == Z_MEM_ERROR) {
                throw std::bad_alloc{};
            } else {
                throw error{rc};
            }
        }

}
