#include "rs-core/io.hpp"
#include "rs-core/unit-test.hpp"
#include <filesystem>
#include <string>
#include <system_error>

using namespace RS;

namespace fs = std::filesystem;

namespace {

    const inline fs::path test_file{"__test_file__"};

}

void test_rs_core_io_cstdio_class() {

    std::string s;
    auto n = 0uz;
    auto z = 0z;

    {
        Cstdio io(test_file, IO::write_only);
        TRY(n = io.write_str("Hello world\n"));
        TEST_EQUAL(n, 12u);
        TRY(n = io.write_str("Goodnight moon\n"));
        TEST_EQUAL(n, 15u);
        TRY(n = io.write_str("Here comes the sun\n"));
        TEST_EQUAL(n, 19u);
    }

    TEST(fs::exists(test_file));

    {
        Cstdio io(test_file);
        TRY(z = io.tell());
        TEST_EQUAL(z, 0);
        TRY(io.seek(0, IO::end));
        TRY(z = io.tell());
        TEST_EQUAL(z, 46);
    }

    {
        Cstdio io(test_file);
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
        Cstdio io(test_file);
        TRY(s = io.read_all());
        TEST_EQUAL(s,
            "Hello world\n"
            "Goodnight moon\n"
            "Here comes the sun\n"
        );
    }

    TRY(fs::remove(test_file));
    TEST(! fs::exists(test_file));
    TEST_THROW(Cstdio(test_file), std::system_error, test_file.string());

}

void test_rs_core_io_cstdio_byte_io() {

    std::string s;
    char c{};

    {
        Cstdio io(test_file, IO::write_only);
        TRY(io.put('H'));
        TRY(io.put('e'));
        TRY(io.put('l'));
        TRY(io.put('l'));
        TRY(io.put('o'));
        TRY(io.put('\n'));
    }

    TEST(fs::exists(test_file));

    {
        Cstdio io(test_file);
        TEST(io.get(c));  TEST_EQUAL(c, 'H');
        TEST(io.get(c));  TEST_EQUAL(c, 'e');
        TEST(io.get(c));  TEST_EQUAL(c, 'l');
        TEST(io.get(c));  TEST_EQUAL(c, 'l');
        TEST(io.get(c));  TEST_EQUAL(c, 'o');
        TEST(io.get(c));  TEST_EQUAL(c, '\n');
        TEST(! io.get(c));
    }

    TRY(fs::remove(test_file));
    TEST(! fs::exists(test_file));
    TEST_THROW(Cstdio(test_file), std::system_error, test_file.string());

}

void test_rs_core_io_cstdio_formatting() {

    std::string s;
    auto n = 0uz;

    {
        Cstdio io(test_file, IO::write_only);
        TRY(n = io.print("Hello world\n"));
        TEST_EQUAL(n, 12u);
        TRY(n = io.print("Answer {}\n", 42));
        TEST_EQUAL(n, 10u);
        TRY(n = io.print("Agent {} ❤️ {}\n", 86, 99));
        TEST_EQUAL(n, 19u);
    }

    TEST(fs::exists(test_file));

    {
        Cstdio io(test_file);
        TRY(s = io.read_all());
        TEST_EQUAL(s,
            "Hello world\n"
            "Answer 42\n"
            "Agent 86 ❤️ 99\n"
        );
    }

    {
        Cstdio io(test_file, IO::write_only);
        TRY(n = io.println("Hello world"));
        TEST_EQUAL(n, 12u);
        TRY(n = io.println("Answer {}", 42));
        TEST_EQUAL(n, 10u);
        TRY(n = io.println("Agent {} ❤️ {}", 86, 99));
        TEST_EQUAL(n, 19u);
    }

    TEST(fs::exists(test_file));

    {
        Cstdio io(test_file);
        TRY(s = io.read_all());
        TEST_EQUAL(s,
            "Hello world\n"
            "Answer 42\n"
            "Agent 86 ❤️ 99\n"
        );
    }

    TRY(fs::remove(test_file));
    TEST(! fs::exists(test_file));
    TEST_THROW(Cstdio(test_file), std::system_error, test_file.string());

}

void test_rs_core_io_cstdio_line_iterator() {

    std::string s;
    IO::line_range lines;
    IO::iterator i;

    {
        Cstdio io(test_file, IO::write_only);
        TRY(io.write_str("Hello world\n"));
        TRY(io.write_str("Goodnight moon\n"));
        TRY(io.write_str("Here comes the sun\n"));
    }

    TEST(fs::exists(test_file));

    {
        Cstdio io(test_file);
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

    TRY(fs::remove(test_file));
    TEST(! fs::exists(test_file));
    TEST_THROW(Cstdio(test_file), std::system_error, test_file.string());

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

    TRY(buf.seek(0, IO::set));
    TRY(z = buf.tell());
    TEST_EQUAL(z, 0);
    TRY(buf.seek(0, IO::end));
    TRY(z = buf.tell());
    TEST_EQUAL(z, 46);

    TRY(buf.seek(0, IO::set));
    TRY(s = buf.read_str(12));
    TEST_EQUAL(s, "Hello world\n");
    TRY(s = buf.read_str(15));
    TEST_EQUAL(s, "Goodnight moon\n");
    TRY(s = buf.read_str(19));
    TEST_EQUAL(s, "Here comes the sun\n");
    TRY(s = buf.read_str(100));
    TEST_EQUAL(s, "");

    TRY(buf.seek(0, IO::set));
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
    TRY(buf.seek(0, IO::set));

    TEST(buf.get(c));  TEST_EQUAL(c, 'H');
    TEST(buf.get(c));  TEST_EQUAL(c, 'e');
    TEST(buf.get(c));  TEST_EQUAL(c, 'l');
    TEST(buf.get(c));  TEST_EQUAL(c, 'l');
    TEST(buf.get(c));  TEST_EQUAL(c, 'o');
    TEST(buf.get(c));  TEST_EQUAL(c, '\n');

    TEST(! buf.get(c));

}

void test_rs_core_io_string_buffer_formatting() {

    StringBuffer buf;
    std::string s;
    auto n = 0uz;
    auto z = 0z;

    TRY(n = buf.print("Hello world\n"));
    TEST_EQUAL(n, 12u);
    TRY(n = buf.print("Answer {}\n", 42));
    TEST_EQUAL(n, 10u);
    TRY(n = buf.print("Agent {} ❤️ {}\n", 86, 99));
    TEST_EQUAL(n, 19u);
    TRY(z = buf.tell());
    TEST_EQUAL(z, 41);

    TRY(buf.seek(0, IO::set));
    TRY(s = buf.read_all());
    TEST_EQUAL(s,
        "Hello world\n"
        "Answer 42\n"
        "Agent 86 ❤️ 99\n"
    );

    TRY(buf.clear());
    TEST(buf.empty());
    TRY(n = buf.println("Hello world"));
    TEST_EQUAL(n, 12u);
    TRY(n = buf.println("Answer {}", 42));
    TEST_EQUAL(n, 10u);
    TRY(n = buf.println("Agent {} ❤️ {}", 86, 99));
    TEST_EQUAL(n, 19u);
    TRY(z = buf.tell());
    TEST_EQUAL(z, 41);

    TRY(buf.seek(0, IO::set));
    TRY(s = buf.read_all());
    TEST_EQUAL(s,
        "Hello world\n"
        "Answer 42\n"
        "Agent 86 ❤️ 99\n"
    );

}

void test_rs_core_io_string_buffer_line_iterator() {

    StringBuffer buf;
    std::string s;
    IO::line_range lines;
    IO::iterator i;

    TRY(buf.write_str("Hello world\n"));
    TRY(buf.write_str("Goodnight moon\n"));
    TRY(buf.write_str("Here comes the sun\n"));
    TRY(buf.seek(0, IO::set));

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
