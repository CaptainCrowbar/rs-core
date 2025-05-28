#include "rs-core/core.hpp"
#include "rs-core/unit-test.hpp"
#include <filesystem>
#include <string>
#include <system_error>

using namespace RS;

void test_rs_core_io_cstdio() {

    std::string s;
    std::filesystem::path p{"test-file"};
    auto n = 0uz;
    auto z = 0z;

    {
        Cstdio io(p, "wb");
        TRY(n = io.write("Hello world\n"));
        TEST_EQUAL(n, 12u);
        TRY(n = io.write("Goodnight moon\n"));
        TEST_EQUAL(n, 15u);
        TRY(n = io.write("Here comes the sun\n"));
        TEST_EQUAL(n, 19u);
    }

    TEST(std::filesystem::exists(p));

    {
        Cstdio io(p);
        TRY(z = io.tell());
        TEST_EQUAL(z, 0);
        TRY(io.seek(0, SEEK_END));
        TRY(z = io.tell());
        TEST_EQUAL(z, 46);
    }

    {
        Cstdio io(p);
        TRY(s = io.read(12));
        TEST_EQUAL(s, "Hello world\n");
        TRY(s = io.read(15));
        TEST_EQUAL(s, "Goodnight moon\n");
        TRY(s = io.read(19));
        TEST_EQUAL(s, "Here comes the sun\n");
        TRY(s = io.read(100));
        TEST_EQUAL(s, "");
        TEST(io.eof());
    }

    TRY(std::filesystem::remove(p));
    TEST(! std::filesystem::exists(p));
    TEST_THROW(Cstdio(p), std::system_error, "No such file");

}

void test_rs_core_io_line_iterator() {

    std::string s;
    std::filesystem::path p{"test-file"};
    Cstdio::line_range lines;
    Cstdio::iterator i;

    {
        Cstdio io(p, "wb");
        TRY(io.write("Hello world\n"));
        TRY(io.write("Goodnight moon\n"));
        TRY(io.write("Here comes the sun\n"));
    }

    TEST(std::filesystem::exists(p));

    {
        Cstdio io(p);
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

    {
        Cstdio io(p);
        TRY(lines = io.lines(true));
        TRY(i = lines.begin());
        TRY(s = *i);
        TEST_EQUAL(s, "Hello world");
        TRY(++i);
        TRY(s = *i);
        TEST_EQUAL(s, "Goodnight moon");
        TRY(++i);
        TRY(s = *i);
        TEST_EQUAL(s, "Here comes the sun");
        TRY(++i);
        TEST(i == lines.end());
    }

    TRY(std::filesystem::remove(p));
    TEST(! std::filesystem::exists(p));
    TEST_THROW(Cstdio(p), std::system_error, "No such file");

}

void test_rs_core_io_read_write_file() {

    std::string s;
    std::filesystem::path p{"test-file"};

    TRY(Cstdio::write_file("Hello world\n", p));
    TEST(std::filesystem::exists(p));
    TRY(s = Cstdio::read_file(p));
    TEST_EQUAL(s, "Hello world\n");
    TRY(std::filesystem::remove(p));
    TEST(! std::filesystem::exists(p));
    TEST_THROW(Cstdio::read_file(p), std::system_error, "No such file");

}
