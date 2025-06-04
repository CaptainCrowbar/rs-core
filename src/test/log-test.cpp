#include "rs-core/log.hpp"
#include "rs-core/io.hpp"
#include "rs-core/unit-test.hpp"
#include <filesystem>
#include <memory>
#include <string>

using namespace RS;

namespace {

    const inline std::filesystem::path logfile{"__log_test__"};

}

void test_rs_core_log_message() {

    REQUIRE(! std::filesystem::exists(logfile));

    {
        std::shared_ptr<Log> logptr;
        TRY(logptr = std::make_shared<Log>(logfile));
        TRY(logptr->enable());
        TRY((*logptr)({"Hello"}));
    }

    {
        Cstdio in(logfile);
        std::string line;
        TRY(line = in.read_line(true));
        TEST_EQUAL(line, "[log-test.cpp:24] Hello");
    }

    {
        std::shared_ptr<Log> logptr;
        TRY(logptr = std::make_shared<Log>(logfile));
        TRY(logptr->enable());
        TRY((*logptr)({"Answer {}", 42}));
        TRY((*logptr)({"Project {}", 2501}));
        TRY((*logptr)({"Agent {} ❤️ {}", 86, 99}));
    }

    {
        Cstdio in(logfile);
        std::string line;
        TRY(line = in.read_line(true));
        TEST_EQUAL(line, "[log-test.cpp:38] Answer 42");
        TRY(line = in.read_line(true));
        TEST_EQUAL(line, "[log-test.cpp:39] Project 2501");
        TRY(line = in.read_line(true));
        TEST_EQUAL(line, "[log-test.cpp:40] Agent 86 ❤️ 99");
    }

    TRY(std::filesystem::remove(logfile));
    REQUIRE(! std::filesystem::exists(logfile));

}

void test_rs_core_log_context() {

    REQUIRE(! std::filesystem::exists(logfile));

    {
        Log log(logfile, Log::enabled);
        TRY(log({"Hello"}));
        Cstdio in(logfile);
        std::string line;
        TRY(line = in.read_line(true));
        TEST_EQUAL(line, "Hello");
    }

    {
        Log log(logfile, Log::time | Log::enabled);
        TRY(log({"Hello"}));
        Cstdio in(logfile);
        std::string line;
        TRY(line = in.read_line(true));
        TEST_MATCH(line, R"(^\[\d{8}-\d{6}\.\d{6,9}\] Hello$)");
    }

    {
        Log log(logfile, Log::process | Log::enabled);
        TRY(log({"Hello"}));
        Cstdio in(logfile);
        std::string line;
        TRY(line = in.read_line(true));
        TEST_MATCH(line, R"(^\[P[0-9a-f]+\] Hello$)");
    }

    {
        Log log(logfile, Log::thread | Log::enabled);
        TRY(log({"Hello"}));
        Cstdio in(logfile);
        std::string line;
        TRY(line = in.read_line(true));
        TEST_MATCH(line, R"(^\[T[0-9a-f]+\] Hello$)");
    }

    {
        Log log(logfile, Log::path | Log::enabled);
        TRY(log({"Hello"}));
        Cstdio in(logfile);
        std::string line;
        TRY(line = in.read_line(true));
        #ifdef _WIN32
            // TODO
        #else
            TEST_MATCH(line, R"(^\[(/[^/]+)+/log-test\.cpp\] Hello$)");
        #endif
    }

    {
        Log log(logfile, Log::file | Log::enabled);
        TRY(log({"Hello"}));
        Cstdio in(logfile);
        std::string line;
        TRY(line = in.read_line(true));
        TEST_MATCH(line, R"(^\[log-test.cpp\] Hello$)");
    }

    {
        Log log(logfile, Log::pretty | Log::enabled);
        TRY(log({"Hello"}));
        Cstdio in(logfile);
        std::string line;
        TRY(line = in.read_line(true));
        TEST_MATCH(line, R"(^\[void test_rs_core_log_context\(\)\] Hello$)");
    }

    {
        Log log(logfile, Log::function | Log::enabled);
        TRY(log({"Hello"}));
        Cstdio in(logfile);
        std::string line;
        TRY(line = in.read_line(true));
        TEST_MATCH(line, R"(^\[test_rs_core_log_context\] Hello$)");
    }

    {
        Log log(logfile, Log::file | Log::line | Log::column | Log::enabled);
        TRY(log({"Hello"}));
        Cstdio in(logfile);
        std::string line;
        TRY(line = in.read_line(true));
        TEST_MATCH(line, R"(^\[log-test\.cpp:\d{3}:\d{2}\] Hello$)");
    }

    TRY(std::filesystem::remove(logfile));
    REQUIRE(! std::filesystem::exists(logfile));

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

    REQUIRE(! std::filesystem::exists(logfile));

    {
        Log log(logfile, Log::pretty | Log::enabled);
        TRY(foo(log, 42));
        Cstdio in(logfile);
        std::string line;
        TRY(line = in.read_line(true));
        TEST_MATCH(line, R"(^\[void .+::foo\(.+\) .+\] Hello 42$)");
    }

    {
        Log log(logfile, Log::function | Log::enabled);
        TRY(foo(log, 42));
        Cstdio in(logfile);
        std::string line;
        TRY(line = in.read_line(true));
        TEST_EQUAL(line, "[foo] Hello 42");
    }

    {
        Alpha a;
        Log log(logfile, Log::pretty | Log::enabled);
        TRY(a.f(log, 86));
        Cstdio in(logfile);
        std::string line;
        TRY(line = in.read_line(true));
        TEST_MATCH(line, R"(^\[void .+::Alpha::f\(.+\) .+\] Hello 86$)");
    }

    {
        Alpha a;
        Log log(logfile, Log::function | Log::enabled);
        TRY(a.f(log, 86));
        Cstdio in(logfile);
        std::string line;
        TRY(line = in.read_line(true));
        TEST_EQUAL(line, "[f] Hello 86");
    }

    {
        Bravo b;
        Log log(logfile, Log::pretty | Log::enabled);
        TRY(b.f(log, 99));
        Cstdio in(logfile);
        std::string line;
        TRY(line = in.read_line(true));
        TEST_MATCH(line, R"(^\[void .+::Bravo::f\(.+\) .+\] Hello 99$)");
    }

    {
        Bravo b;
        Log log(logfile, Log::function | Log::enabled);
        TRY(b.f(log, 99));
        Cstdio in(logfile);
        std::string line;
        TRY(line = in.read_line(true));
        TEST_EQUAL(line, "[f] Hello 99");
    }

    TRY(std::filesystem::remove(logfile));
    REQUIRE(! std::filesystem::exists(logfile));

}
