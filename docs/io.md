# I/O Utilities

_[Core utility library by Ross Smith](index.html)_

```c++
#include "rs-core/io.hpp"
namespace RS;
```

## Contents

* TOC
{:toc}

## Cstdio class

```c++
class Cstdio;
```

This is a simple wrapper around a standard `FILE*` stream handle. Operations
not covered by this class's interface can be invoked by calling the standard
`<cstdio>` functions on the stream handle from the `handle()` method.

Any member function not marked `noexcept` may throw `std::system_error` if the
underlying `<cstdio>` call fails.

```c++
class Cstdio::iterator;
```

Iterator over the lines in an input stream. This is a const input iterator
whose value type is `std::string.` The iterator calls `read_line()` when it
is constructed or incremented.

```c++
using Cstdio::line_range = std::ranges::subrange<iterator, [see below]>;
```

A range of line iterators. Depending on the implementation, this may be either
a pair of iterators or an iterator-sentinel pair.

```c++
Cstdio::Cstdio() noexcept;
```

The default constructor sets the internal stream to a null pointer.

```c++
explicit Cstdio::Cstdio(const std::filesystem::path& path,
    const char* mode = "rb");
```

Constructor from a file path and I/O mode.

```c++
explicit Cstdio::Cstdio(std::FILE* stream) noexcept;
```

Constructor from an existing stream handle. This is mainly intended to be used
with the standard handles (`stdin,stdout,stderr`). If the handle is not one
of these, the `Cstdio` object will take ownership of the stream and will
close it on destruction.

```c++
Cstdio::Cstdio(Cstdio&& io) noexcept;
Cstdio& Cstdio::operator=(Cstdio&& io) noexcept;
```

Move constructor and assignment operator.

```c++
Cstdio::~Cstdio() noexcept;
```

The destructor will close the stream handle, unless the handle is null or one
of the three standard streams.

```c++
void Cstdio::close();
```

Closes the stream and resets the internal `FILE*` pointer to null. This will
do nothing if the stream was already null; if it is one of the three standard
streams, the pointer will be reset but the stream will not be affected. This
can throw if something goes wrong while closing the stream, but the pointer
will be reset regardless. Other operations (destructor and assignment
operator) that close the stream will ignore errors while closing.

```c++
void Cstdio::flush();
```

Flushes the stream. This will do nothing if the stream is null.

```c++
bool Cstdio::get(char& c);
```

Reads one byte from the file, returning true on a successful read. If the read
fails the argument will be left unchanged.

```c++
std::FILE* Cstdio::handle() const noexcept;
```

Returns the underlying `<cstdio>` stream handle.

```c++
Cstdio::line_range Cstdio::lines();
```

Returns an iterator range over the lines in an input stream, starting at the
current read position.

```c++
void Cstdio::put(char c);
```

Writes one byte to the stream.

```c++
std::size_t Cstdio::read(void* ptr, std::size_t len);
```

Reads up to `len` bytes, writing it into the supplied buffer, and returns the
number of bytes actually read (which may be zero if you are at the end of the
stream).

```c++
std::size_t Cstdio::read_into(std::string& buf, std::size_t pos = 0);
```

Reads from the stream into a buffer supplied as a string, with data written
into the string starting at the given position. This will do nothing and
return zero if `pos>=buf.size().`

```c++
std::string Cstdio::read_line();
```

Reads one line from the stream, starting at the current read position and
ending after the next line feed or at the end of the stream, whichever comes
first. If the stream actually contains binary data, not text, this may read a
large amount of data looking for a line feed.

```c++
std::string Cstdio::read_str(std::size_t len);
```

Reads up to `len` bytes and returns the data as a string.

```c++
void Cstdio::seek(std::ptrdiff_t offset = 0, int from = SEEK_CUR);
```

Seek through the stream, if possible. The `from` argument must be one of the
standard seek start positions (`SEEK_CUR,SEEK_END,SEEK_SET`).

```c++
std::ptrdiff_t Cstdio::tell() const;
```

Report the current stream position, if possible.

```c++
std::size_t Cstdio::write(const void* ptr, std::size_t len);
```

Writes a block of data to the stream. The return value is the number of bytes
written (this is not guaranteed to be equal to `len`).

```c++
std::size_t Cstdio::write_str(std::string_view str);
```

Writes a block of data to the stream. The return value is the number of bytes
written (this is not guaranteed to be equal to `str.size()`).

```c++
static std::string Cstdio::read_file(const std::filesystem::path& path);
```

Reads the complete contents of a file into a string.

```c++
static void Cstdio::write_file(std::string_view str, const std::filesystem::path& path);
```

Writes the contents of a string into a file. Any existing file will be
overwritten.
