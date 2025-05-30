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
    // const input iterator
    // value type is std::string
using Cstdio::line_range = std::ranges::subrange<iterator>;
```

Iterator over the lines in a text file. This calls `read_line()` when it is
constructed or incremented.

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
bool Cstdio::eof() const noexcept;
```

True if the stream's EOF flag has been set (and the stream is not null).

```c++
std::FILE* Cstdio::handle() const noexcept;
```

Returns the underlying `<cstdio>` stream handle.

```c++
Cstdio::line_range Cstdio::lines(bool trim_crlf = false);
```

Returns an iterator range over the lines in a text file, starting at the
current read position. See `read_line()` for the flag usage.

```c++
std::size_t Cstdio::read(void* ptr, std::size_t len);
std::size_t Cstdio::read(std::string& buf, std::size_t pos = 0);
std::string Cstdio::read(std::size_t len);
```

Read from the file. The first version reads up to `len` bytes, writing it into
the supplied buffer, and returns the number of bytes actually read (which may
be zero if you are at the end of the file).

The second version does the same thing, but the buffer is supplied as a
string, with data written into the string starting at the given position.
This will do nothing and return zero if `pos>=buf.size().`

The third version reads up to `len` bytes and returns the data as a string.

```c++
std::string Cstdio::read_line(bool trim_crlf = false);
```

Read one line from the file, starting at the current read position and ending
after the next line feed or at the end of the file, whichever comes first. If
the file is actually a binary file, this may read a large amount of data
looking for a line feed. If the `trim_crlf` flag is set, any trailing LF or
CR+LF will be removed from the returned string.

```c++
void Cstdio::seek(std::ptrdiff_t offset = 0, int from = SEEK_CUR);
```

Seek through the file, if possible. The `from` argument must be one of the
standard seek start positions (`SEEK_CUR,SEEK_END,SEEK_SET`).

```c++
std::ptrdiff_t Cstdio::tell() const;
```

Report the current stream position, if possible.

```c++
std::size_t Cstdio::write(const void* ptr, std::size_t len);
std::size_t Cstdio::write(std::string_view str);
```

Write a block of data to the file. The return value is the number of bytes
written; this is not guaranteed to be equal to `len` or `str.size().`

```c++
static std::string Cstdio::read_file(const std::filesystem::path& path);
```

Read the complete contents of a file into a string.

```c++
static void Cstdio::write_file(std::string_view str, const std::filesystem::path& path);
```

Write the contents of a string into a file. Any existing file will be
overwritten.
