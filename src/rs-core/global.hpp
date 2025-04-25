#pragma once

#include <limits>
#include <cstddef>

namespace RS {

    // Sanity check

    static_assert(std::numeric_limits<unsigned char>::digits == 8);

    // Constants

    constexpr auto npos = ~ 0uz;

}
