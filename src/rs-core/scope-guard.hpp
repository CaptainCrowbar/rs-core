#pragma once

#include "rs-core/enum.hpp"
#include "rs-core/global.hpp"
#include <concepts>
#include <exception>
#include <utility>

namespace RS {

    RS_BITMASK(ScopeMode, unsigned char,
        success  = 1,  // Invoke callback on normal exit, but not when unwinding due to exception
        failure  = 2,  // Invoke callback when unwinding due to exception, but not on normal exit
        exit     = 3,  // Invoke callback unconditionally in destructor
    )

    template <std::invocable F, ScopeMode M>
    class BasicScopeGuard {

    public:

        BasicScopeGuard(F&& f):
            callback_(std::forward<F>(f)),
            inflight_(std::uncaught_exceptions()) {}

        ~BasicScopeGuard() noexcept {
            if (inflight_ >= 0) {
                auto uncaught = std::uncaught_exceptions();
                if ((!! (M & ScopeMode::success) && uncaught <= inflight_)
                        || (!! (M & ScopeMode::failure) && uncaught > inflight_)) {
                    callback_();
                }
            }
        }

        BasicScopeGuard(const BasicScopeGuard&) = delete;
        BasicScopeGuard(BasicScopeGuard&&) = delete;
        BasicScopeGuard& operator=(const BasicScopeGuard&) = delete;
        BasicScopeGuard& operator=(BasicScopeGuard&&) = delete;

        void release() noexcept {
            inflight_ = -1;
        }

    private:

        F callback_;
        int inflight_;

    };

    template <std::invocable F>
    auto on_success(F&& f) {
        return BasicScopeGuard<F, ScopeMode::success>(std::forward<F>(f));
    }

    template <std::invocable F>
    auto on_failure(F&& f) {
        return BasicScopeGuard<F, ScopeMode::failure>(std::forward<F>(f));
    }

    template <std::invocable F>
    auto on_exit(F&& f) {
        return BasicScopeGuard<F, ScopeMode::exit>(std::forward<F>(f));
    }

}
