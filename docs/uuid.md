# UUID Class

_[Core utility library by Ross Smith](index.html)_

```c++
#include "rs-core/uuid.hpp"
namespace RS;
```

## Contents

* TOC
{:toc}

## UUID class

```c++
class Uuid;
```

A class representing a 128-bit universally unique identifier.

```c++
constexpr Uuid::Uuid() noexcept;
```

The default constructor creates an all-zero UUID.

```c++
constexpr Uuid::Uuid
    (std::uint8_t a, std::uint8_t b, std::uint8_t c, std::uint8_t d,
    std::uint8_t e, std::uint8_t f, std::uint8_t g, std::uint8_t h,
    std::uint8_t i, std::uint8_t j, std::uint8_t k, std::uint8_t l,
    std::uint8_t m, std::uint8_t n, std::uint8_t o, std::uint8_t p) noexcept;
```

Constructor from an explicit list of bytes.

```c++
constexpr explicit Uuid::Uuid(Uint128 u,
    std::endian order = std::endian::big) noexcept;
```

Constructor from a 128-bit integer, in big or little endian byte order.

```c++
explicit Uuid::Uuid(std::string_view str);
```

Constructor from a string. The string must contain exactly 32 hex digits,
grouped in any way as long as each group contains an even number of digits.
Groups may be separated by any combination of ASCII punctuation, spaces, or
tabs; groups may be prefixed with `"0x"` (case insensitive). An empty string
is interpreted as a default constructed UUID. Otherwise, this will throw
`std::invalid_argument` if the string is not a valid UUID.

```c++
constexpr Uuid::~Uuid() noexcept;
constexpr Uuid::Uuid(const Uuid& u) noexcept;
constexpr Uuid::Uuid(Uuid&& u) noexcept;
constexpr Uuid& Uuid::operator=(const Uuid& u) noexcept;
constexpr Uuid& Uuid::operator=(Uuid&& u) noexcept;
```

Other life cycle functions.

```c++
constexpr std::uint8_t& Uuid::operator[](std::size_t i) noexcept;
constexpr const std::uint8_t& Uuid::operator[](std::size_t i)
    const noexcept;
```

Access to individual bytes. Behaviour is undefined if `i>=16.`

```c++
constexpr std::uint8_t* Uuid::begin() noexcept;
constexpr const std::uint8_t* Uuid::begin() const noexcept;
constexpr std::uint8_t* Uuid::end() noexcept;
constexpr const std::uint8_t* Uuid::end() const noexcept;
```

These allow iteration over the bytes in a UUID, starting with the most
significant.

```c++
constexpr Uint128 as_integer(std::endian order = std::endian::big) const noexcept;
```

Copies the UUID into a 128-bit integer, in big or little endian byte order.

```c++
constexpr std::size_t Uuid::hash() const noexcept;
struct std::hash<Uuid>;
```

Hash function.

```c++
std::string Uuid::to_string() const;
explicit Uuid::operator std::string() const;
struct std::formatter<Uuid>;
```

These convert the UUID to a string, in the standard format:
`"xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx".`

```c++
constexpr int Uuid::variant() const noexcept;
constexpr int Uuid::version() const noexcept;
constexpr void Uuid::set_variant(int v) noexcept;
constexpr void Uuid::set_version(int v) noexcept;
```

Query or set the UUID variant and version (type) fields. When setting either
field, bits beyond the 4 least significant are masked out. When querying or
setting the variant, the "don't care" bits of the variant field are masked
out.

```c++
static constexpr Uuid Uuid::max() noexcept;
```

Returns the maximum UUID (all bits 1).

```c++
static Uuid Uuid::read(const void* ptr) noexcept;
```

Copies the bytes of a UUID from a block of memory. Behaviour is undefined if
the pointer is null or does not point to a valid array of at least 16 bytes.

```c++
template <std::uniform_random_bit_generator RNG>
    static Uuid Uuid::random(RNG& rng, int type = 4);
```

Generates a random UUID. Only types 4 and 7 are supported; this will throw
`std::invalid_argument` if `type` has any other value.

```c++
constexpr bool operator==(const Uuid& u, const Uuid& v) noexcept;
constexpr bool operator!=(const Uuid& u, const Uuid& v) noexcept;
constexpr bool operator<(const Uuid& u, const Uuid& v) noexcept;
constexpr bool operator>(const Uuid& u, const Uuid& v) noexcept;
constexpr bool operator<=(const Uuid& u, const Uuid& v) noexcept;
constexpr bool operator>=(const Uuid& u, const Uuid& v) noexcept;
constexpr std::strong_ordering operator<=>
    (const Uuid& u, const Uuid& v) noexcept;
```

Comparison operators.
