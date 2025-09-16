#include "rs-core/log.hpp"
#include "rs-core/io.hpp"
#include "rs-core/unit-test.hpp"
#include <cstdio>
#include <filesystem>
#include <format>
#include <memory>
#include <string>

using namespace RS;

namespace {

    const inline std::filesystem::path logfile{"__log_test__"};

}

void test_rs_core_log_message() {

    TRY(std::filesystem::remove(logfile));
    TEST(! std::filesystem::exists(logfile));
    auto line_number{0};

    {
        std::shared_ptr<Log> logptr;
        TRY(logptr = std::make_shared<Log>(logfile));
        TRY(logptr->enable());
        line_number = __LINE__;
        TRY((*logptr)({"Hello"}));
    }

    {
        Cstdio in(logfile);
        std::string line;
        TRY(line = in.read_line());
        TEST_EQUAL(line, std::format("[log-test.cpp:{}] Hello\n", line_number + 1));
    }

    {
        std::shared_ptr<Log> logptr;
        TRY(logptr = std::make_shared<Log>(logfile));
        TRY(logptr->enable());
        line_number = __LINE__;
        TRY((*logptr)({"Answer {}", 42}));
        TRY((*logptr)({"Project {}", 2501}));
        TRY((*logptr)({"Agent {} ❤️ {}", 86, 99}));
    }

    {
        Cstdio in(logfile);
        std::string line;
        TRY(line = in.read_line());
        TEST_EQUAL(line, std::format("[log-test.cpp:{}] Answer 42\n", line_number + 1));
        TRY(line = in.read_line());
        TEST_EQUAL(line, std::format("[log-test.cpp:{}] Project 2501\n", line_number + 2));
        TRY(line = in.read_line());
        TEST_EQUAL(line, std::format("[log-test.cpp:{}] Agent 86 ❤️ 99\n", line_number + 3));
    }

    TRY(std::filesystem::remove(logfile));
    TEST(! std::filesystem::exists(logfile));

}

// void test_rs_core_log_terminal() {

//     Log log(stdout, Log::defaults | Log::date | Log::colour | Log::enabled);
//     TRY(log({"Answer {}", 42}));
//     TRY(log({"Project {}", 2501}));
//     TRY(log({"Agent {} ❤️ {}", 86, 99}));

// }

void test_rs_core_log_context() {

    TRY(std::filesystem::remove(logfile));
    TEST(! std::filesystem::exists(logfile));

    {
        Log log(logfile, Log::enabled);
        TRY(log({"Hello"}));
    }

    {
        Cstdio in(logfile);
        std::string line;
        TRY(line = in.read_line());
        TEST_EQUAL(line, "Hello\n");
    }

    {
        Log log(logfile, Log::date | Log::enabled);
        TRY(log({"Hello"}));
    }

    {
        Cstdio in(logfile);
        std::string line;
        TRY(line = in.read_line());
        TEST_MATCH(line, R"(^\[\d{8}-\d{6}\.\d{6,9}\] Hello\n$)");
    }

    {
        Log log(logfile, Log::time | Log::enabled);
        TRY(log({"Hello"}));
    }

    {
        Cstdio in(logfile);
        std::string line;
        TRY(line = in.read_line());
        TEST_MATCH(line, R"(^\[\d{6}\.\d{6,9}\] Hello\n$)");
    }

    {
        Log log(logfile, Log::process | Log::enabled);
        TRY(log({"Hello"}));
    }

    {
        Cstdio in(logfile);
        std::string line;
        TRY(line = in.read_line());
        TEST_MATCH(line, R"(^\[P[0-9a-f]+\] Hello\n$)");
    }

    {
        Log log(logfile, Log::thread | Log::enabled);
        TRY(log({"Hello"}));
    }

    {
        Cstdio in(logfile);
        std::string line;
        TRY(line = in.read_line());
        TEST_MATCH(line, R"(^\[T[0-9a-f]+\] Hello\n$)");
    }

    {
        Log log(logfile, Log::path | Log::enabled);
        TRY(log({"Hello"}));
    }

    {
        Cstdio in(logfile);
        std::string line;
        TRY(line = in.read_line());
        #ifdef _WIN32
            // TODO
        #else
            TEST_MATCH(line, R"(^\[(/[^/]+)+/log-test\.cpp\] Hello\n$)");
        #endif
    }

    {
        Log log(logfile, Log::file | Log::enabled);
        TRY(log({"Hello"}));
    }

    {
        Cstdio in(logfile);
        std::string line;
        TRY(line = in.read_line());
        TEST_MATCH(line, R"(^\[log-test.cpp\] Hello\n$)");
    }

    {
        Log log(logfile, Log::pretty | Log::enabled);
        TRY(log({"Hello"}));
    }

    {
        Cstdio in(logfile);
        std::string line;
        TRY(line = in.read_line());
        TEST_MATCH(line, R"(^\[void (\w+ )?test_rs_core_log_context\((void)?\)\] Hello\n$)");
    }

    {
        Log log(logfile, Log::function | Log::enabled);
        TRY(log({"Hello"}));
    }

    {
        Cstdio in(logfile);
        std::string line;
        TRY(line = in.read_line());
        TEST_MATCH(line, R"(^\[test_rs_core_log_context\] Hello\n$)");
    }

    {
        Log log(logfile, Log::file | Log::line | Log::enabled);
        TRY(log({"Hello"}));
    }

    {
        Cstdio in(logfile);
        std::string line;
        TRY(line = in.read_line());
        TEST_MATCH(line, R"(^\[log-test\.cpp:\d{3}\] Hello\n$)");
    }

    TRY(std::filesystem::remove(logfile));
    TEST(! std::filesystem::exists(logfile));

}

namespace {

    template <typename T>
    void foo(Log& log, T t) {
        TRY(log({"Hello {}", t}));
    }

    struct Alpha {
        void f(Log& log, int n) const {
            TRY(log({"Hello {}", n}));
        }
    };

    struct Bravo {
        template <typename T>
        void f(Log& log, T t) const {
            TRY(log({"Hello {}", t}));
        }
    };

}

void test_rs_core_log_function_context() {

    TRY(std::filesystem::remove(logfile));
    TEST(! std::filesystem::exists(logfile));

    {
        Log log(logfile, Log::pretty | Log::enabled);
        TRY(foo(log, 42));
    }

    {
        Cstdio in(logfile);
        std::string line;
        TRY(line = in.read_line());
        TEST_MATCH(line, R"(^\[void .+::foo(<.+>)?\(.+\).*\] Hello 42\n$)");
    }

    {
        Log log(logfile, Log::function | Log::enabled);
        TRY(foo(log, 42));
    }

    {
        Cstdio in(logfile);
        std::string line;
        TRY(line = in.read_line());
        TEST_EQUAL(line, "[foo] Hello 42\n");
    }

    {
        Alpha a;
        Log log(logfile, Log::pretty | Log::enabled);
        TRY(a.f(log, 86));
    }

    {
        Cstdio in(logfile);
        std::string line;
        TRY(line = in.read_line());
        TEST_MATCH(line, R"(^\[void .+::Alpha::f\(.+\) .+\] Hello 86\n$)");
    }

    {
        Alpha a;
        Log log(logfile, Log::function | Log::enabled);
        TRY(a.f(log, 86));
    }

    {
        Cstdio in(logfile);
        std::string line;
        TRY(line = in.read_line());
        TEST_EQUAL(line, "[f] Hello 86\n");
    }

    {
        Bravo b;
        Log log(logfile, Log::pretty | Log::enabled);
        TRY(b.f(log, 99));
    }

    {
        Cstdio in(logfile);
        std::string line;
        TRY(line = in.read_line());
        TEST_MATCH(line, R"(^\[void .+::Bravo::f(<.+>)?\(.+\) .+\] Hello 99\n$)");
    }

    {
        Bravo b;
        Log log(logfile, Log::function | Log::enabled);
        TRY(b.f(log, 99));
    }

    {
        Cstdio in(logfile);
        std::string line;
        TRY(line = in.read_line());
        TEST_EQUAL(line, "[f] Hello 99\n");
    }

    TRY(std::filesystem::remove(logfile));
    TEST(! std::filesystem::exists(logfile));

}
