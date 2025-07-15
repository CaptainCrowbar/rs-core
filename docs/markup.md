# Text Markup

_[Core utility library by Ross Smith](index.html)_

```c++
#include "rs-core/markup.hpp"
namespace RS;
```

## Contents

* TOC
{:toc}

## XML/HTML Markup

The `Htag` and `Xtag` classes write an HTML or XML tag in the constructor,
then write the corresponding closing tag in the destructor. Output can go to
a string or an output file, defaulting to standard output. A default
constructed object will do nothing on construction or destruction.

The opening tag can be supplied with or without enclosing angle brackets. The
constructor does not attempt any validation of the tag's format; the output
will be nonsense if the element argument is not a valid HTML/XML tag.

If the opening tag is standalone, the text will simply be written as is, and
no closing tag will be written. Standalone tags can be identified by a
closing slash.

The `Htag` class is also aware of the
[standard HTML5 list of self closing tags](https://www.w3.org/TR/html5/syntax.html#void-elements).
This is the only difference between `Htag` and `Xtag`.

If the element string ends with one line feed, a line feed will be written
after the closing tag, but not the opening one; if it ends with two line
feeds, one will be written after both tags.

The constructors that take a file stream will throw `std::system_error` if the
stream is not open for output, or if any other I/O error occurs. Errors while
writing the closing tag are ignored.

Behaviour is undefined if the output destination (string or file stream) is
destroyed or closed while any tag attached to it still exists.

### XML element class

```c++
class Xtag {
    Xtag();
    explicit Xtag(const std::string& element);
    explicit Xtag(const std::string& element, std::string& out);
    explicit Xtag(const std::string& element, std::FILE* out);
    explicit Xtag(const std::string& element, RS::Cstdio& out);
    Xtag(Xtag&& t) noexcept;
    virtual ~Xtag() noexcept;
    Xtag& operator=(Xtag&& t) noexcept;
};
```

### HTML element class

```c++
class Htag: public Xtag {
    Htag();
    explicit Htag(const std::string& element);
    explicit Htag(const std::string& element, std::string& out);
    explicit Htag(const std::string& element, std::FILE* out);
    explicit Htag(const std::string& element, RS::Cstdio& out);
    Htag(Htag&& t) noexcept;
    virtual ~Htag() noexcept;
    Htag& operator=(Htag&& t) noexcept;
};
```
