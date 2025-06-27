#include "rs-core/io.hpp"
#include "rs-core/unit-test.hpp"
#include <filesystem>
#include <string>
#include <system_error>

using namespace RS;

namespace fs = std::filesystem;

namespace {

    const inline fs::path file{"__test_file__"};

}

void test_rs_core_io_cstdio_class() {

    std::string s;
    auto n = 0uz;
    auto z = 0z;

    {
        Cstdio io(file, "wb");
        TRY(n = io.write_str("Hello world\n"));
        TEST_EQUAL(n, 12u);
        TRY(n = io.write_str("Goodnight moon\n"));
        TEST_EQUAL(n, 15u);
        TRY(n = io.write_str("Here comes the sun\n"));
        TEST_EQUAL(n, 19u);
    }

    TEST(fs::exists(file));

    {
        Cstdio io(file);
        TRY(z = io.tell());
        TEST_EQUAL(z, 0);
        TRY(io.seek(0, SEEK_END));
        TRY(z = io.tell());
        TEST_EQUAL(z, 46);
    }

    {
        Cstdio io(file);
        TRY(s = io.read_str(12));
        TEST_EQUAL(s, "Hello world\n");
        TRY(s = io.read_str(15));
        TEST_EQUAL(s, "Goodnight moon\n");
        TRY(s = io.read_str(19));
        TEST_EQUAL(s, "Here comes the sun\n");
        TRY(s = io.read_str(100));
        TEST_EQUAL(s, "");
    }

    {
        Cstdio io(file);
        TRY(s = io.read_all());
        TEST_EQUAL(s,
            "Hello world\n"
            "Goodnight moon\n"
            "Here comes the sun\n"
        );
    }

    TRY(fs::remove(file));
    TEST(! fs::exists(file));
    TEST_THROW(Cstdio(file), std::system_error, "No such file");

}

void test_rs_core_io_cstdio_byte_io() {

    std::string s;
    char c{};

    {
        Cstdio io(file, "wb");
        TRY(io.put('H'));
        TRY(io.put('e'));
        TRY(io.put('l'));
        TRY(io.put('l'));
        TRY(io.put('o'));
        TRY(io.put('\n'));
    }

    TEST(fs::exists(file));

    {
        Cstdio io(file);
        TEST(io.get(c));  TEST_EQUAL(c, 'H');
        TEST(io.get(c));  TEST_EQUAL(c, 'e');
        TEST(io.get(c));  TEST_EQUAL(c, 'l');
        TEST(io.get(c));  TEST_EQUAL(c, 'l');
        TEST(io.get(c));  TEST_EQUAL(c, 'o');
        TEST(io.get(c));  TEST_EQUAL(c, '\n');
        TEST(! io.get(c));
    }

    TRY(fs::remove(file));
    TEST(! fs::exists(file));
    TEST_THROW(Cstdio(file), std::system_error, "No such file");

}

void test_rs_core_io_cstdio_line_iterator() {

    std::string s;
    IO::line_range lines;
    IO::iterator i;

    {
        Cstdio io(file, "wb");
        TRY(io.write_str("Hello world\n"));
        TRY(io.write_str("Goodnight moon\n"));
        TRY(io.write_str("Here comes the sun\n"));
    }

    TEST(fs::exists(file));

    {
        Cstdio io(file);
        TRY(lines = io.lines());
        TRY(i = lines.begin());
        TRY(s = *i);
        TEST_EQUAL(s, "Hello world\n");
        TRY(++i);
        TRY(s = *i);
        TEST_EQUAL(s, "Goodnight moon\n");
        TRY(++i);
        TRY(s = *i);
        TEST_EQUAL(s, "Here comes the sun\n");
        TRY(++i);
        TEST(i == lines.end());
    }

    TRY(fs::remove(file));
    TEST(! fs::exists(file));
    TEST_THROW(Cstdio(file), std::system_error, "No such file");

}

void test_rs_core_io_string_buffer_class() {

    StringBuffer buf;
    std::string s;
    auto n = 0uz;
    auto z = 0z;

    TEST(buf.empty());
    TRY(n = buf.write_str("Hello world\n"));
    TEST_EQUAL(n, 12u);
    TRY(n = buf.write_str("Goodnight moon\n"));
    TEST_EQUAL(n, 15u);
    TRY(n = buf.write_str("Here comes the sun\n"));
    TEST_EQUAL(n, 19u);
    TRY(z = buf.tell());
    TEST_EQUAL(z, 46);

    TRY(buf.seek(0, SEEK_SET));
    TRY(z = buf.tell());
    TEST_EQUAL(z, 0);
    TRY(buf.seek(0, SEEK_END));
    TRY(z = buf.tell());
    TEST_EQUAL(z, 46);

    TRY(buf.seek(0, SEEK_SET));
    TRY(s = buf.read_str(12));
    TEST_EQUAL(s, "Hello world\n");
    TRY(s = buf.read_str(15));
    TEST_EQUAL(s, "Goodnight moon\n");
    TRY(s = buf.read_str(19));
    TEST_EQUAL(s, "Here comes the sun\n");
    TRY(s = buf.read_str(100));
    TEST_EQUAL(s, "");

    TRY(buf.seek(0, SEEK_SET));
    TRY(s = buf.read_all());
    TEST_EQUAL(s,
        "Hello world\n"
        "Goodnight moon\n"
        "Here comes the sun\n"
    );

}

void test_rs_core_io_string_buffer_byte_io() {

    StringBuffer buf;
    auto z = 0z;
    char c{};

    TRY(buf.put('H'));
    TRY(buf.put('e'));
    TRY(buf.put('l'));
    TRY(buf.put('l'));
    TRY(buf.put('o'));
    TRY(buf.put('\n'));
    TRY(z = buf.tell());
    TEST_EQUAL(z, 6);
    TRY(buf.seek(0, SEEK_SET));

    TEST(buf.get(c));  TEST_EQUAL(c, 'H');
    TEST(buf.get(c));  TEST_EQUAL(c, 'e');
    TEST(buf.get(c));  TEST_EQUAL(c, 'l');
    TEST(buf.get(c));  TEST_EQUAL(c, 'l');
    TEST(buf.get(c));  TEST_EQUAL(c, 'o');
    TEST(buf.get(c));  TEST_EQUAL(c, '\n');

    TEST(! buf.get(c));

}

void test_rs_core_io_string_buffer_line_iterator() {

    StringBuffer buf;
    std::string s;
    IO::line_range lines;
    IO::iterator i;

    TRY(buf.write_str("Hello world\n"));
    TRY(buf.write_str("Goodnight moon\n"));
    TRY(buf.write_str("Here comes the sun\n"));
    TRY(buf.seek(0, SEEK_SET));

    TRY(lines = buf.lines());
    TRY(i = lines.begin());
    TRY(s = *i);
    TEST_EQUAL(s, "Hello world\n");
    TRY(++i);
    TRY(s = *i);
    TEST_EQUAL(s, "Goodnight moon\n");
    TRY(++i);
    TRY(s = *i);
    TEST_EQUAL(s, "Here comes the sun\n");
    TRY(++i);
    TEST(i == lines.end());

}
