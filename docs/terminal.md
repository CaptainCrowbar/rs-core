# Terminal control

_[Core utility library by Ross Smith](index.html)_

```c++
#include "rs-core/terminal.hpp"
namespace RS;
```

## Contents

* TOC
{:toc}

## Xterm class

```c++
class Xterm;
```

This class contains functions that generate terminal control escape sequences,
or query properties of the terminal. All of these assume a compatible
terminal emulator and may not be reliable on some systems. The colour flag
(see below) is the class's only internal state.

```c++
Xterm::Xterm() noexcept;
explicit Xterm::Xterm(bool use_colour) noexcept;
```

The constructor determines whether to generate colour control codes, and
related codes such as font control. The default constructor will set colour
mode only if `is_tty(stdout)` (see below) is true.

```c++
Xterm::Xterm(const Xterm& xt) noexcept;
Xterm::Xterm(Xterm&& xt) noexcept;
Xterm::~Xterm() noexcept;
Xterm& Xterm::operator=(const Xterm& xt) noexcept;
Xterm& Xterm::operator=(Xterm&& xt) noexcept;
```

Other life cycle operations.

### Terminal properties

```c++
enum class XtermMode: int {
    unknown,
    light,
    dark,
};
```

The dark or light mode indicator returned from `guess_mode().` This is
imported into the `Xterm` class (`using enum XtermMode`).

```c++
bool Xterm::is_colour() const noexcept;
```

Returns the colour flag supplied to the constructor.

```c++
static std::size_t Xterm::columns() noexcept;
static std::size_t Xterm::lines() noexcept;
```

Query the number of columns and lines in the output terminal. These are
obtained from the `COLUMNS` and `LINES` environment variables; if these are
not available, default values of 80 columns and 25 lines will be assumed.

```c++
static XtermMode Xterm::guess_mode() noexcept;
```

Attempts to determine whether the output terminal is in light or dark mode.
This checks the `COLORFGBG` environment variable, which is available on most
Unix terminals but probably not reliable on Windows. It will return `unknown`
if `is_tty(stdout)` is false, or if the variable is not available or its
format is not recognized.

```c++
static bool Xterm::is_tty(FILE* stream = stdout) noexcept;
static bool Xterm::is_tty(int fd) noexcept;
```

Query whether the standard I/O streams (`stdin,stdout,stderr`) are connected
to a terminal. The first version will always return false if the argument is
not one of the three standard streams.

### Cursor control sequences

```c++
static std::string_view left() noexcept           // esc [D
static std::string_view right() noexcept          // esc [C
static std::string_view up() noexcept             // esc [A
static std::string_view down() noexcept           // esc [B
static std::string left(int n)                    // esc [ <n> D
static std::string right(int n)                   // esc [ <n> C
static std::string up(int n)                      // esc [ <n> A
static std::string down(int n)                    // esc [ <n> B
static std::string move_to(int x, int y)          // esc [ <y> ; <x> H
static std::string_view save_position() noexcept  // esc [s
static std::string_view load_position() noexcept  // esc [u
static std::string_view erase_left() noexcept     // esc [1K
static std::string_view erase_right() noexcept    // esc [K
static std::string_view erase_above() noexcept    // esc [1J
static std::string_view erase_below() noexcept    // esc [J
static std::string_view erase_line() noexcept     // esc [2K
static std::string_view clear_screen() noexcept   // esc [2J
```

Standard escape sequences.

### Format control sequences

All of these functions will return an empty string if `is_colour()` is false.

```c++
std::string_view Xterm::reset() const noexcept;       // esc [0m
std::string_view Xterm::bold() const noexcept;        // esc [1m
std::string_view Xterm::under() const noexcept;       // esc [4m
std::string_view Xterm::bold_off() const noexcept;    // esc [22m
std::string_view Xterm::under_off() const noexcept;   // esc [24m
std::string_view Xterm::colour_off() const noexcept;  // esc [39m
std::string_view Xterm::black() const noexcept;       // esc [30m
std::string_view Xterm::red() const noexcept;         // esc [31m
std::string_view Xterm::green() const noexcept;       // esc [32m
std::string_view Xterm::yellow() const noexcept;      // esc [33m
std::string_view Xterm::blue() const noexcept;        // esc [34m
std::string_view Xterm::magenta() const noexcept;     // esc [35m
std::string_view Xterm::cyan() const noexcept;        // esc [36m
std::string_view Xterm::white() const noexcept;       // esc [37m
std::string_view Xterm::black_bg() const noexcept;    // esc [40m
std::string_view Xterm::red_bg() const noexcept;      // esc [41m
std::string_view Xterm::green_bg() const noexcept;    // esc [42m
std::string_view Xterm::yellow_bg() const noexcept;   // esc [43m
std::string_view Xterm::blue_bg() const noexcept;     // esc [44m
std::string_view Xterm::magenta_bg() const noexcept;  // esc [45m
std::string_view Xterm::cyan_bg() const noexcept;     // esc [46m
std::string_view Xterm::white_bg() const noexcept;    // esc [47m
```

Standard escape sequences.

```c++
std::string Xterm::grey(int y) const;
std::string Xterm::grey_bg(int y) const;
```

These return the escape codes for a greyscale foreground or background,
assuming at least a 256 colour terminal. The grey index will be clamped to
the range 0-23.

```c++
using Xterm::colour = std::array<int, 3>;
std::string Xterm::rgb(int r, int g, int b) const;
std::string Xterm::rgb(colour c) const;
std::string Xterm::rgb_bg(int r, int g, int b) const;
std::string Xterm::rgb_bg(colour c) const;
```

These return the escape codes for a coloured foreground or background,
assuming at least a 256 colour terminal. Each of the RGB indices will be
clamped to the range 0-5.
