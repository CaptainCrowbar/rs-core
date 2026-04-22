#include "rs-core/scope.hpp"
#include "rs-core/unit-test.hpp"
#include <format>
#include <stdexcept>
#include <vector>

using namespace RS;

void test_rs_core_scope_guard() {

    int n = 0;

    {
        n = 1;
        auto guard = on_exit([&] { n = 2; });
        TEST_EQUAL(n, 1);
    }

    TEST_EQUAL(n, 2);
    n = 0;

    try {
        n = 1;
        auto guard = on_exit([&] { n = 2; });
        TEST_EQUAL(n, 1);
        throw std::runtime_error("Failed");
    }
    catch (const std::runtime_error&) {}

    TEST_EQUAL(n, 2);
    n = 0;

    {
        n = 1;
        auto guard = on_success([&] { n = 2; });
        TEST_EQUAL(n, 1);
    }

    TEST_EQUAL(n, 2);
    n = 0;

    try {
        n = 1;
        auto guard = on_success([&] { n = 2; });
        TEST_EQUAL(n, 1);
        throw std::runtime_error("Failed");
    }
    catch (const std::runtime_error&) {}

    TEST_EQUAL(n, 1);
    n = 0;

    {
        n = 1;
        auto guard = on_failure([&] { n = 2; });
        TEST_EQUAL(n, 1);
    }

    TEST_EQUAL(n, 1);
    n = 0;

    try {
        n = 1;
        auto guard = on_failure([&] { n = 2; });
        TEST_EQUAL(n, 1);
        throw std::runtime_error("Failed");
    }
    catch (const std::runtime_error&) {}

    TEST_EQUAL(n, 2);

}

void test_rs_core_scope_guard_saved_container_size() {

    std::vector<int> v = {1, 2, 3};
    {
        auto guard = guard_size(v);
        v.push_back(4);
        v.push_back(5);
    }

    TEST_EQUAL(v.size(), 5u);
    TEST_EQUAL(std::format("{}", v), "[1, 2, 3, 4, 5]");

    v = {1, 2, 3};

    try {
        auto guard = guard_size(v);
        v.push_back(4);
        v.push_back(5);
        throw std::runtime_error("Failed");
    }
    catch (...) {}

    TEST_EQUAL(v.size(), 3u);
    TEST_EQUAL(std::format("{}", v), "[1, 2, 3]");

}

void test_rs_core_scope_guard_saved_value() {

    int n = 1;

    {
        auto guard = guard_value(n);
        n = 2;
        TEST_EQUAL(n, 2);
    }

    TEST_EQUAL(n, 2);

    n = 1;

    try {
        auto guard = guard_value(n);
        n = 2;
        TEST_EQUAL(n, 2);
        throw std::runtime_error("Failed");
    }
    catch (...) {}

    TEST_EQUAL(n, 1);

}
