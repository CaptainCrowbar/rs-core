#include "rs-core/core.hpp"
#include "rs-core/unit-test.hpp"
#include <stdexcept>

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
        throw std::runtime_error("failed");
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
        throw std::runtime_error("failed");
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
        throw std::runtime_error("failed");
    }
    catch (const std::runtime_error&) {}

    TEST_EQUAL(n, 2);

}
