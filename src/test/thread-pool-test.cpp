#include "rs-core/thread-pool.hpp"
#include "rs-core/character.hpp"
#include "rs-core/random.hpp"
#include "rs-core/unit-test.hpp"
#include <algorithm>
#include <chrono>
#include <cstdint>
#include <mutex>
#include <print>
#include <random>
#include <ranges>
#include <string>
#include <string_view>
#include <thread>

namespace rs = std::ranges;
using namespace RS;
using namespace std::chrono;

namespace {

    std::string_view alphabet() {

        static const auto str = [] {
            std::string s;
            for (char c = 'a'; c <= 'z'; ++c) {
                s += c;
            }
            return s;
        }();

        return str;

    }

}

void test_rs_core_thread_pool_class() {

    ThreadPool pool;
    std::string log;
    std::mutex mutex;
    std::mt19937 rng{42};
    std::uniform_int_distribution<int> dist{1, 100};
    TEST_EQUAL(pool.threads(), std::thread::hardware_concurrency());

    auto f = [&] (char c, int t) {
        std::this_thread::sleep_for(milliseconds{t});
        std::unique_lock lock{mutex};
        log += c;
    };

    for (char c = 'a'; c <= 'z'; ++c) {
        auto t = dist(rng);
        TRY(pool.insert([=] { f(c, t); }));
    }

    TRY(pool.wait());
    TEST_EQUAL(log.size(), alphabet().size());
    TEST(log != alphabet());
    rs::sort(log);
    TEST_EQUAL(log, alphabet());

    TRY(pool.clear());
    TEST_EQUAL(pool.threads(), std::thread::hardware_concurrency());
    log.clear();

    for (char c = 'a'; c <= 'z'; ++c) {
        auto t = dist(rng);
        TRY(pool([=] { f(c, t); }));
    }

    TEST(pool.wait_for(5s));
    TEST_EQUAL(log.size(), alphabet().size());
    TEST(log != alphabet());
    rs::sort(log);
    TEST_EQUAL(log, alphabet());

}

void test_rs_core_thread_pool_benchmark() {

    static constexpr int iterations = 1'000'000;

    ThreadPool pool;
    std::mutex mutex;
    auto counter = 0uz;

    auto task = [&] {
        std::unique_lock lock{mutex};
        ++counter;
    };

    auto start = system_clock::now();

    for (int i = 0; i < iterations; ++i) {
        TRY(pool.insert(task));
    }

    TRY(pool.wait());
    auto stop = system_clock::now();
    auto total = static_cast<double>(duration_cast<nanoseconds>(stop - start).count());
    auto each = total / static_cast<double>(iterations);
    auto rate = static_cast<std::uint64_t>(1e9 / each);
    std::println("... Calls per second = {}", rate);

    if (counter == 42) {
        std::println("... !!!!!");
    }

}
