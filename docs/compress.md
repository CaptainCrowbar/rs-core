# Compression

_[Core utility library by Ross Smith](index.html)_

```c++
#include "rs-core/compress.hpp"
namespace RS;
```

## Contents

* TOC
{:toc}

## Notes

Using this module requires linking with [Zlib](https://zlib.net). Because the
`rs-core` library is header only, including this header necessarily also
includes `<zlib.h>.`

## Zlib class

```c++
class Zlib;
```

This class calls the Zlib library to perform compression and decompression.

The class stores a default value for the compression quality, which must be an
integer from -1 to 9 inclusive. Quality 0 generates no compression; the input
data is simply copied to the output (with the addition of some bookkeeping
information). Levels 1 to 9 represent increasing compression strength, at the
expense of increasing execution time. Quality -1 tells Zlib to use its
standard default compression level (this is currently level 6 but may change
in the future).

The compression level parameter is only relevant when compressing; it is
ignored when decompressing.

The maximum size of a file (before or after compression) is limited only by
the maximum size of a contiguous byte array, which is normally determined by
the maximum value of a `std::size_t.` The integer types used internally by
Zlib do not impose any narrower limits.

Preset dictionaries are not supported.

```c++
class error:
public std::runtime_error {
    explicit error(int code, std::string_view details = {});
    int code() const noexcept;
};
```

Exception thrown when an unexpected error occurs. This contains the Zlib error
code and a short error message.

The Zlib status codes are (not all of these can generate exceptions):

| Error code         | Value  | Description                 |
| ----------         | -----  | -----------                 |
| `Z_OK`             | 0      | Success                     |
| `Z_STREAM_END`     | 1      | End of stream               |
| `Z_NEED_DICT`      | 2      | Preset dictionary expected  |
| `Z_ERRNO`          | -1     | I/O error                   |
| `Z_STREAM_ERROR`   | -2     | Invalid zlib API call       |
| `Z_DATA_ERROR`     | -3     | Input data is corrupt       |
| `Z_MEM_ERROR`      | -4     | Out of memory               |
| `Z_BUF_ERROR`      | -5     | Output buffer is too short  |
| `Z_VERSION_ERROR`  | -6     | Zlib version mismatch       |

```c++
struct result {
    std::size_t bytes_in;
    std::size_t bytes_out;
};
```

Return type from the compression and decompression functions. This contains
the number of bytes read from the input buffer, and the number of bytes
written to the output buffer, after compression or decompression is
complete.

```c++
Zlib::Zlib();
explicit Zlib::Zlib(int level);
```

Constructors. The second constructor will throw `Zlib::error` if the
compression level is out of bounds.

```c++
Zlib::~Zlib() noexcept;
Zlib::Zlib(const Zlib& z);
Zlib::Zlib(Zlib&& z) noexcept;
Zlib& Zlib::operator=(const Zlib& z);
Zlib& Zlib::operator=(Zlib&& z) noexcept;
```

Other life cycle operations.

```c++
int Zlib::level() const noexcept;
void Zlib::set_level(int level);
```

Query or set the default compression level. The `set_level()` function will
throw `Zlib::error` (and leave the internal setting unchanged) if the
compression level is out of bounds.

```c++
template <InputSpan IS, OutputBuffer OB>
    Zlib::result Zlib::encode(const IS& in, OB& out) const;
template <InputSpan IS, OutputBuffer OB>
    Zlib::result Zlib::encode(const IS& in, OB& out, int level) const;
```

Compression functions. See [`rs-core/global`](global.md) for the definitions
of the I/O buffer concepts. The first version uses the `Zlib` object's
internal default compression level; the second version uses the specified
level, ignoring the preset default.

The entire input buffer will be consumed; the `bytes_in` field in the result
will always be equal to `in.size().` The compressed output is appended to the
output buffer, leaving its original contents intact.

If the input data is highly random or already compressed (or the compression
level is zero), it is possible for the output to be slightly larger than the
input, due to the added bookkeeping data.

The second function will throw `Zlib::error` if the compression level is out
of bounds.

```c++
template <InputSpan IS, OutputBuffer OB>
    Zlib::result Zlib::decode(const IS& in, OB& out) const;
```

Decompression function. This expects the input buffer to contain a compressed
data stream, possibly followed by unrelated data which will not be read. The
decompressed output is appended to the output buffer, leaving its original
contents intact.

This will throw `Zlib::error` if the input stream does not contain valid
compressed data.
