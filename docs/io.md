# I/O Utilities

_[Core utility library by Ross Smith](index.html)_

```c++
#include "rs-core/io.hpp"
namespace RS;
```

## Contents

* TOC
{:toc}

## Supporting types

```c++
enum class IOMode: int {
    read_only,
    write_only,
    read_write,
    append,
};
```

Used in I/O class constructors to indicate the read/write mode. Some classes
may also allow other modes specific to that class.

```c++
enum class IOSeek: int {
    current  = SEEK_CUR,  // Relative to the current position
    end      = SEEK_END,  // Relative to the beginning of the stream
    set      = SEEK_SET,  // Relative to the end of the stream
};
```

Used in `IO:seek()` to indicate where to seek from.

## IO class

```c++
class IO;
```

This is the abstract base class for other I/O classes. Each derived class is
basically a thin wrapper providing a common API for I/O channels.

For `IO` and all derived classes, any member function not marked `noexcept`
may throw `std::bad_alloc` or `std::system_error` if an underlying system
call fails.

In derived classes, functions overriding base class virtual functions are
documented only where they add significant behavioural details.

```c++
using enum IOMode;
using enum IOSeek;
```

Imported for convenience.

```c++
class IO::iterator;
```

Iterator over the lines in an input stream. This is an input iterator that
dereferences to a `const std::string&.` The iterator calls `read_line()` when
it is constructed or incremented.

```c++
using IO::line_range = std::ranges::subrange<iterator, [see below]>;
```

A range of line iterators. Depending on the implementation, this may be either
a pair of iterators or an iterator-sentinel pair.

```c++
IO::IO() noexcept;
IO::IO(IO&&) noexcept;
virtual IO::~IO() noexcept;
IO& IO::operator=(IO&&) noexcept;
```

Life cycle operations.

```c++
virtual bool IO::can_seek() const noexcept;
```

Indicates whether or not the stream is seekable. This does not guarantee that
any particular call to `seek()` will work.

```c++
virtual void IO::close();
```

Closes the stream. The detailed semantics depend on the particular I/O channel
being handled.

```c++
virtual void IO::flush();
```

Flushes the stream. For some I/O channel types this will do nothing.

```c++
virtual bool IO::get(char& c);
```

Reads one byte from the file, returning true on a successful read. If the read
fails the argument will be left unchanged.

```c++
IO::line_range IO::lines();
```

Returns an iterator range over the lines in an input stream, starting at the
current read position.

```c++
template <typename... Args>
    std::size_t IO::print(std::format_string<const Args&...> fmt,
        const Args&... args);
template <typename... Args>
    std::size_t IO::println(std::format_string<const Args&...> fmt,
        const Args&... args);
```

Write formatted data to the stream. The return value is the number of bytes
written.

```c++
virtual void IO::put(char c);
```

Writes one byte to the stream.

```c++
virtual std::size_t IO::read(void* ptr, std::size_t len);
```

Reads up to `len` bytes, writing it into the supplied buffer, and returns the
number of bytes actually read (which may be zero if we are at the end of the
stream).

```c++
virtual std::string IO::read_all();
```

Read all data from the current read position to the end of the stream.

```c++
virtual std::size_t IO::read_into(std::string& buf, std::size_t pos = 0);
```

Reads from the stream into a buffer supplied as a string, with data written
into the string starting at the given position. This will do nothing and
return zero if `pos>=buf.size().`

```c++
virtual std::string IO::read_line();
```

Reads one line from the stream, starting at the current read position and
ending after the next line feed or at the end of the stream, whichever comes
first. If the stream actually contains binary data, not text, this may read a
large amount of data looking for a line feed.

```c++
std::string IO::read_str(std::size_t len);
```

Reads up to `len` bytes and returns the data as a string.

```c++
virtual void IO::seek(std::ptrdiff_t offset = 0, IOSeek from = current);
```

Seeks to a different position in the stream, if possible.

```c++
virtual std::ptrdiff_t IO::tell() const;
```

Report the current stream position, if possible.

```c++
virtual std::size_t IO::write(const void* ptr, std::size_t len);
```

Writes a block of data to the stream. The return value is the number of bytes
written (this is not guaranteed to be equal to `len`).

```c++
std::size_t IO::write_str(std::string_view str);
```

Writes a block of data to the stream. The return value is the number of bytes
written (this is not guaranteed to be equal to `str.size()`).

## Cstdio class

```c++
class Cstdio: public IO;
```

This is a simple wrapper around a standard `FILE*` stream handle. Operations
not covered by this class's interface can be invoked by calling the standard
`<cstdio>` functions on the stream handle from the `handle()` method.

```c++
Cstdio::Cstdio() noexcept;
```

The default constructor sets the internal stream to a null pointer.

```c++
explicit Cstdio::Cstdio(const std::filesystem::path& path,
    IOMode mode = read_only);
explicit Cstdio::Cstdio(const std::filesystem::path& path,
    const char* mode);
```

Constructor from a file path and I/O mode. For the second version, behaviour
is undefined if `mode` is a null pointer or an invalid mode string. If the
path is `"-"` or an empty string, and the mode is not a read-write mode,
instead of opening a file this will attach the `Cstdio` object to standard
input or output.

```c++
explicit Cstdio::Cstdio(std::FILE* stream) noexcept;
explicit Cstdio::Cstdio(std::FILE* stream, bool own) noexcept;
```

Constructor from an existing stream handle. This is mainly intended to be used
with the standard handles (`stdin,stdout,stderr`). If the `own` flag is set,
the `Cstdio` object will take ownership of the stream and will close it on
destruction. By default, ownership is taken if the handle is not standard
input, standard output, or standard error. This will throw
`std::invalid_argument` if the second version is called with one of the
standard streams but with the ownership flag set to true.

```c++
Cstdio::Cstdio(Cstdio&& io) noexcept;
Cstdio& Cstdio::operator=(Cstdio&& io) noexcept;
```

Move constructor and assignment operator.

```c++
Cstdio::~Cstdio() noexcept override;
```

The destructor will close the stream handle, unless the handle is null or one
of the three standard streams.

```c++
void Cstdio::close() override;
```

Closes the stream and resets the internal `FILE*` pointer to null. This will
do nothing if the stream was already null; if it is one of the three standard
streams, the pointer will be reset but the stream will not be affected. This
can throw if something goes wrong while closing the stream, but the pointer
will be reset regardless. Other operations (destructor and assignment
operator) that close the stream will ignore errors while closing.

```c++
std::FILE* Cstdio::handle() const noexcept;
std::FILE* Cstdio::release() noexcept;
```

These return the underlying `<cstdio>` stream handle. The `release()` function
relinquishes ownership of the handle (if it was owned) and sets the internal
handle to null.

## StringBuffer class

```c++
class StringBuffer: public IO;
```

This class manages an internal string buffer, manipulating it using an I/O
like interface.

```c++
StringBuffer::StringBuffer();
```

The default constructor initializes the buffer to an empty string. A
`StringBuffer` is always opened in read-write mode.

```c++
StringBuffer::StringBuffer(StringBuffer&& sb);
StringBuffer::~StringBuffer() noexcept override;
StringBuffer& StringBuffer::operator=(StringBuffer&& sb);
```

Other life cycle operations.

```c++
void StringBuffer::close() override;
```

A string buffer has no concept of open vs closed; the `close()` function does
nothing.

```c++
void StringBuffer::clear() noexcept;
```

Resets the buffer to an empty string.

```c++
bool StringBuffer::empty() const noexcept;
std::size_t StringBuffer::size() const noexcept;
```

Query the buffer's current size.

```c++
std::string_view StringBuffer::view() const noexcept;
```

Returns a view over the internal buffer.
