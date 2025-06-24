#pragma once

#include "rs-core/global.hpp"
#include <cstdlib>
#include <memory>
#include <string>
#include <typeinfo>

#ifdef __GNUC__
    #include <cxxabi.h>
#endif

namespace RS {

    namespace Detail {

        inline std::string demangle_typename(std::string name) {

            #ifdef __GNUC__

                // https://gcc.gnu.org/onlinedocs/libstdc++/libstdc++-html-USERS-4.3/a01696.html

                auto status = 0;
                auto demangle_ptr = abi::__cxa_demangle(name.data(), nullptr, nullptr, &status);
                std::unique_ptr<char, decltype(&std::free)> name_ptr(demangle_ptr, &std::free);

                if (demangle_ptr != nullptr) {
                    return demangle_ptr;
                }

            #endif

            return name;

        }

    }

    template <typename T>
    std::string type_name() {
        using namespace Detail;
        return demangle_typename(typeid(T).name());
    }

    template <typename T>
    std::string type_name(T&& t) {
        using namespace Detail;
        return demangle_typename(typeid(t).name());
    }

}
