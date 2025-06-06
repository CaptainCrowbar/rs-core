# Logging

_[Core utility library by Ross Smith](index.html)_

```c++
#include "rs-core/log.hpp"
namespace RS;
```

## Contents

* TOC
{:toc}

## Supporting types

```c++
enum class LogFlags: std::uint32_t {
    none = 0,
    // Context flags
    all,       // Mask containing all context flags
    date,      // Show date and time (UTC)
    time,      // Show time
    process,   // Show process ID
    thread,    // Show thread ID
    path,      // Show source file (full path)
    file,      // Show source file (name only)
    pretty,    // Show calling function (fully qualified)
    function,  // Show calling function (name only)
    line,      // Show source line number
    // Other flags
    append,    // Append to existing file
    colour,    // Colour console output by thread
    enabled,   // Enable logging immediately
};
```

Bitmask flags controlling logging options.

## Log class

```c++
class Log;
```

This is a simple utility for logging to a file or the console. The formatted
text passed in a call to a `Log` object will be prefixed with context
information, according to the flags supplied when the `Log` was constructed.

The arguments to the function call operator (the format string and its
arguments) must be enclosed in an extra pair of braces; this is necessary to
make automatic recording of the source location work with a variadic function
call.

The formatting arguments are passed to a separate thread to perform the actual
formatting and output, to minimise the performance impact on the calling
thread.

If output is going directly to the terminal (`stdout` or `stderr`), and the
`colour` flag has been selected, the output will be printed in pseudo-random
colours to distinguish which thread each log line came from. The `colour`
flag is ignored if the output is going to a file.

Example:

```c++
Log my_log("my-log-file.txt", Log::file | Log::function | Log::line);
my_log.enable();
my_log({"answer={}", 42});
my_log({"foo={}, bar={}", foo, bar});
```

```c++
using enum LogFlags;
```

Imported bitmask flags.

```c++
static constexpr LogFlags Log::defaults = file | line | colour;
```

Default logging flags.

```c++
struct Log::message {
    template <typename... Args>
        message(std::format_string<const Args&...> fmt, const Args&... args);
};
```

This is used in the formatting call, to make automatic recording of the source
location work with a variadic function call.

```c++
Log::Log();
```

Default constructor. This is equivalent to `Log(stderr, Log::defaults).`

```c++
explicit Log::Log(const std::filesystem::path& path,
    LogFlags flags = defaults);
```

Constructor from a file name. Log entries will be written to the specified
file. Any existing file will be overwritten unless the `append` flag was
supplied. By default, logging is disabled until `enable()` is called. This
will throw `std::system_error` if the file can't be opened for writing.

```c++
explicit Log::Log(std::FILE* out, LogFlags flags = defaults);
```

Constructor from an existing file stream handle. The `append` flag has no
effect. Usually this will be used with `stdout` or `stderr.`

```c++
Log::~Log() noexcept;
```

Destructor. If logging is currently enabled, this will wait until any log
entries already queued have been written.

```c++
void Log::enable(bool flag = true);
```

Enable or disable logging. Logging starts out disabled unless the `enabled`
flag was passed to the constructor. Calling `enable(false)` will block until
any log entries queued but not yet written have been completed.

```c++
void Log::operator()(const message& msg,
    const std::source_location loc = std::source_location::current());
```

Writes a log entry. A format string and its arguments must be passed in
braces, as described above. This queues the log entry details into an
internal queue, returning immediately without waiting for the logging to
complete. A mutex is used to ensure that this can safely be called from
multiple threads.
