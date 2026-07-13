#pragma once

#include "rs-core/global.hpp"
#include <algorithm>
#include <atomic>
#include <chrono>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <functional>
#include <mutex>
#include <random>
#include <thread>
#include <utility>
#include <vector>

namespace RS {

    class ThreadPool {

    public:

        using clock = std::chrono::steady_clock;

        ThreadPool(): ThreadPool{0} {}
        explicit ThreadPool(std::size_t threads);
        ~ThreadPool() noexcept;

        ThreadPool(const ThreadPool&) = delete;
        ThreadPool(ThreadPool&&) = delete;
        ThreadPool& operator=(const ThreadPool&) = delete;
        ThreadPool& operator=(ThreadPool&&) = delete;

        void clear() noexcept;
        template <std::invocable<> F> void insert(F&& f);
        template <std::invocable<> F> void operator()(F&& f) { insert(std::forward<F>(f)); }
        bool poll() { return ! unfinished_jobs_; }
        std::size_t threads() const noexcept { return workers_.size(); }
        void wait();
        template <typename R, typename P> bool wait_for(std::chrono::duration<R, P> dt);
        bool wait_until(clock::time_point tp);

    private:

        static constexpr std::chrono::microseconds poll_interval {100};

        struct worker {
            std::mutex mutex;
            std::deque<std::function<void()>> queue;
            std::thread thread;
        };

        std::atomic<std::size_t> clear_count_ {0};
        std::atomic<std::size_t> next_worker_ {0};
        std::atomic<std::size_t> unfinished_jobs_ {0};
        std::atomic<bool> shutting_down_ {false};
        std::vector<worker> workers_;

        void thread_payload(worker* wptr) noexcept;

        static std::size_t actual_threads(std::size_t threads) noexcept;
        template <std::invocable<> F> static bool callback_is_null(F&&) { return false; }
        static bool callback_is_null(void (*f)()) { return f == nullptr; }
        static bool callback_is_null(std::function<void()> f) { return ! f; }

    };

    inline ThreadPool::ThreadPool(std::size_t threads):
    workers_{actual_threads(threads)} {
        for (auto& w: workers_) {
            w.thread = std::thread{&ThreadPool::thread_payload, this, &w};
        }
    }

    inline ThreadPool::~ThreadPool() noexcept {

        clear();
        shutting_down_ = true;

        for (auto& w: workers_) {
            w.thread.join();
        }

    }

    inline void ThreadPool::clear() noexcept {

        ++clear_count_;

        for (auto& w: workers_) {
            std::unique_lock lock{w.mutex};
            w.queue.clear();
        }

        unfinished_jobs_ = 0;
        wait();
        --clear_count_;

    }

    template <std::invocable<> F>
    void ThreadPool::insert(F&& f) {

        if (clear_count_ || callback_is_null(std::forward<F>(f))) {
            return;
        }

        auto index = next_worker_++ % threads();
        auto& w = workers_[index];
        ++unfinished_jobs_;
        std::unique_lock lock{w.mutex};
        w.queue.emplace_back(std::forward<F>(f));

    }

    inline void ThreadPool::wait() {
        while (unfinished_jobs_) {
            std::this_thread::sleep_for(poll_interval);
        }
    }

    template <typename R, typename P>
    bool ThreadPool::wait_for(std::chrono::duration<R, P> dt) {
        return wait_until(clock::now() + dt);
    }

    inline bool ThreadPool::wait_until(clock::time_point tp) {

        for (;;) {

            if (! unfinished_jobs_) {
                return true;
            } else if (clock::now() >= tp) {
                return false;
            }

            std::this_thread::sleep_for(poll_interval);

        }

    }

    inline void ThreadPool::thread_payload(worker* wptr) noexcept {

        auto seed = static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(wptr));
        std::minstd_rand rng{seed};
        std::function<void()> call;
        worker* alt_worker;

        while (! shutting_down_) {

            call = {};

            {
                std::unique_lock lock{wptr->mutex};
                if (! wptr->queue.empty()) {
                    call = std::move(wptr->queue.back());
                    wptr->queue.pop_back();
                }
            }

            if (! call && workers_.size() >= 2) {
                do {
                    auto index = rng() % threads();
                    alt_worker = &workers_[index];
                } while (alt_worker != wptr);
                std::unique_lock lock{alt_worker->mutex};
                if (! alt_worker->queue.empty()) {
                    call = std::move(alt_worker->queue.front());
                    alt_worker->queue.pop_front();
                }
            }

            if (call) {
                call();
                --unfinished_jobs_;
            } else {
                std::this_thread::sleep_for(poll_interval);
            }

        }

    }

    inline std::size_t ThreadPool::actual_threads(std::size_t threads) noexcept {
        if (threads == 0) {
            threads = std::thread::hardware_concurrency();
        }
        return std::max(threads, 2uz);
    }

}
