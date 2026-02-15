#include "rs-core/alias.hpp"
#include "rs-core/unit-test.hpp"
#include <cmath>
#include <limits>
#include <numbers>

using namespace RS;

namespace {

    class MyTag;

    using AD = Alias<double, MyTag>;

}

#define TEST_ALIAS_MATHS_FUNCTION_T(f, x) do { \
    AD ax{x}; \
    auto r = std::f(x); \
    auto ar = f(ax); \
    TEST_NEAR(*ar, r, 1e-10); \
} while (false)

#define TEST_ALIAS_MATHS_FUNCTION_T_T(f, x, y) do { \
    AD ax{x}; \
    AD ay{y}; \
    auto r = std::f(x, y); \
    auto ar = f(ax, ay); \
    TEST_NEAR(*ar, r, 1e-10); \
} while (false)

#define TEST_ALIAS_MATHS_FUNCTION_T_TPTR(f, x) do { \
    AD ax{x}; \
    AD ay{}; \
    double y{}; \
    auto r = std::f(x, &y); \
    auto ar = f(ax, &ay); \
    TEST_NEAR(*ar, r, 1e-10); \
    TEST_NEAR(*ay, y, 1e-10); \
} while (false)

#define TEST_ALIAS_MATHS_FUNCTION_T_U(f, x, y) do { \
    AD ax{x}; \
    auto r = std::f(x, y); \
    auto ar = f(ax, y); \
    TEST_NEAR(*ar, r, 1e-10); \
} while (false)

#define TEST_ALIAS_MATHS_FUNCTION_T_UPTR(f, x, U) do { \
    AD ax{x}; \
    U y1{}; \
    U y2{}; \
    auto r = std::f(x, &y1); \
    auto ar = f(ax, &y2); \
    TEST_NEAR(*ar, r, 1e-10); \
    TEST_EQUAL(y1, y2); \
} while (false)

#define TEST_ALIAS_MATHS_FUNCTION_U_T(f, x, y) do { \
    AD ay{y}; \
    auto r = std::f(x, y); \
    auto ar = f(x, ay); \
    TEST_NEAR(*ar, r, 1e-10); \
} while (false)

#define TEST_ALIAS_MATHS_FUNCTION_T_T_T(f, x, y, z) do { \
    AD ax{x}; \
    AD ay{y}; \
    AD az{z}; \
    auto r = std::f(x, y, z); \
    auto ar = f(ax, ay, az); \
    TEST_NEAR(*ar, r, 1e-10); \
} while (false)

#define TEST_ALIAS_MATHS_FUNCTION_T_T_UPTR(f, x, y, U) do { \
    AD ax{x}; \
    AD ay{y}; \
    U z1{}; \
    U z2{}; \
    auto r = std::f(x, y, &z1); \
    auto ar = f(ax, ay, &z2); \
    TEST_NEAR(*ar, r, 1e-10); \
    TEST_EQUAL(z1, z2); \
} while (false)

#define TEST_ALIAS_MATHS_FUNCTION_U_U_T(f, x, y, z) do { \
    AD az{z}; \
    auto r = std::f(x, y, z); \
    auto ar = f(x, y, az); \
    TEST_NEAR(*ar, r, 1e-10); \
} while (false)


void test_rs_core_alias_maths_functions() {

    TEST_ALIAS_MATHS_FUNCTION_T         (acos,            0.5);
    TEST_ALIAS_MATHS_FUNCTION_T         (acosh,           0.5);
    TEST_ALIAS_MATHS_FUNCTION_T         (asin,            0.5);
    TEST_ALIAS_MATHS_FUNCTION_T         (asinh,           0.5);
    TEST_ALIAS_MATHS_FUNCTION_T         (atan,            0.5);
    TEST_ALIAS_MATHS_FUNCTION_T_T       (atan2,           0.5, 1.5);
    TEST_ALIAS_MATHS_FUNCTION_T         (atanh,           0.5);
    TEST_ALIAS_MATHS_FUNCTION_T         (cbrt,            0.5);
    TEST_ALIAS_MATHS_FUNCTION_T         (ceil,            2.5);
    TEST_ALIAS_MATHS_FUNCTION_T_T       (copysign,        0.5, -1.5);
    TEST_ALIAS_MATHS_FUNCTION_T         (cos,             0.5);
    TEST_ALIAS_MATHS_FUNCTION_T         (cosh,            1.5);
    TEST_ALIAS_MATHS_FUNCTION_T         (erf,             0.5);
    TEST_ALIAS_MATHS_FUNCTION_T         (erfc,            0.5);
    TEST_ALIAS_MATHS_FUNCTION_T         (exp,             0.5);
    TEST_ALIAS_MATHS_FUNCTION_T         (exp2,            0.5);
    TEST_ALIAS_MATHS_FUNCTION_T         (expm1,           0.5);
    TEST_ALIAS_MATHS_FUNCTION_T         (fabs,            -1.5);
    TEST_ALIAS_MATHS_FUNCTION_T_T       (fdim,            2.5, 1.5);
    TEST_ALIAS_MATHS_FUNCTION_T         (floor,           2.5);
    TEST_ALIAS_MATHS_FUNCTION_T_T_T     (fma,             0.5, 1.5, 2.5);
    TEST_ALIAS_MATHS_FUNCTION_T_T       (fmax,            0.5, 1.5);
    TEST_ALIAS_MATHS_FUNCTION_T_T       (fmin,            0.5, 1.5);
    TEST_ALIAS_MATHS_FUNCTION_T_T       (fmod,            2.5, 1.5);
    TEST_ALIAS_MATHS_FUNCTION_T         (fpclassify,      0.5);
    TEST_ALIAS_MATHS_FUNCTION_T_UPTR    (frexp,           123.456, int);
    TEST_ALIAS_MATHS_FUNCTION_T_T       (hypot,           0.5, 1.5);
    TEST_ALIAS_MATHS_FUNCTION_T_T_T     (hypot,           0.5, 1.5, 2.5);
    TEST_ALIAS_MATHS_FUNCTION_T         (ilogb,           2.5);
    TEST_ALIAS_MATHS_FUNCTION_T         (isfinite,        0.5);
    TEST_ALIAS_MATHS_FUNCTION_T_T       (isgreater,       0.5, 1.5);
    TEST_ALIAS_MATHS_FUNCTION_T_T       (isgreaterequal,  0.5, 1.5);
    TEST_ALIAS_MATHS_FUNCTION_T         (isinf,           0.5);
    TEST_ALIAS_MATHS_FUNCTION_T_T       (isless,          0.5, 1.5);
    TEST_ALIAS_MATHS_FUNCTION_T_T       (islessequal,     0.5, 1.5);
    TEST_ALIAS_MATHS_FUNCTION_T_T       (islessgreater,   0.5, 1.5);
    TEST_ALIAS_MATHS_FUNCTION_T         (isnan,           0.5);
    TEST_ALIAS_MATHS_FUNCTION_T         (isnormal,        0.5);
    TEST_ALIAS_MATHS_FUNCTION_T_T       (isunordered,     0.5, 1.5);
    TEST_ALIAS_MATHS_FUNCTION_T_U       (ldexp,           0.5, 5);
    TEST_ALIAS_MATHS_FUNCTION_T_T_T     (lerp,            0.5, 1.5, 2.5);
    TEST_ALIAS_MATHS_FUNCTION_T         (lgamma,          5.0);
    TEST_ALIAS_MATHS_FUNCTION_T         (llrint,          2.5);
    TEST_ALIAS_MATHS_FUNCTION_T         (llround,         2.5);
    TEST_ALIAS_MATHS_FUNCTION_T         (log,             0.5);
    TEST_ALIAS_MATHS_FUNCTION_T         (log10,           0.5);
    TEST_ALIAS_MATHS_FUNCTION_T         (log1p,           0.5);
    TEST_ALIAS_MATHS_FUNCTION_T         (log2,            0.5);
    TEST_ALIAS_MATHS_FUNCTION_T         (logb,            2.5);
    TEST_ALIAS_MATHS_FUNCTION_T         (lrint,           2.5);
    TEST_ALIAS_MATHS_FUNCTION_T         (lround,          2.5);
    TEST_ALIAS_MATHS_FUNCTION_T_TPTR    (modf,            123.456);
    TEST_ALIAS_MATHS_FUNCTION_T         (nearbyint,       2.5);
    TEST_ALIAS_MATHS_FUNCTION_T_T       (nextafter,       0.5, 1.5);
    TEST_ALIAS_MATHS_FUNCTION_T_U       (nexttoward,      0.5, 1.5L);
    TEST_ALIAS_MATHS_FUNCTION_T_T       (pow,             0.5, 1.5);
    TEST_ALIAS_MATHS_FUNCTION_T_T       (remainder,       2.5, 1.5);
    TEST_ALIAS_MATHS_FUNCTION_T_T_UPTR  (remquo,          2.5, 1.5, int);
    TEST_ALIAS_MATHS_FUNCTION_T         (rint,            2.5);
    TEST_ALIAS_MATHS_FUNCTION_T         (round,           2.5);
    TEST_ALIAS_MATHS_FUNCTION_T_U       (scalbln,         0.5, 5L);
    TEST_ALIAS_MATHS_FUNCTION_T_U       (scalbn,          0.5, 5);
    TEST_ALIAS_MATHS_FUNCTION_T         (signbit,         -0.5);
    TEST_ALIAS_MATHS_FUNCTION_T         (sin,             0.5);
    TEST_ALIAS_MATHS_FUNCTION_T         (sinh,            0.5);
    TEST_ALIAS_MATHS_FUNCTION_T         (sqrt,            0.5);
    TEST_ALIAS_MATHS_FUNCTION_T         (tan,             0.5);
    TEST_ALIAS_MATHS_FUNCTION_T         (tanh,            0.5);
    TEST_ALIAS_MATHS_FUNCTION_T         (tgamma,          5.0);
    TEST_ALIAS_MATHS_FUNCTION_T         (trunc,           1.5);

    #if __cpp_lib_math_special_functions >= 201603L

        TEST_ALIAS_MATHS_FUNCTION_U_U_T  (assoc_laguerre,  2u, 10u, 0.5)
        TEST_ALIAS_MATHS_FUNCTION_U_U_T  (assoc_legendre,  2u, 1u, 0.5)
        TEST_ALIAS_MATHS_FUNCTION_T_T    (beta,            0.123, 0.877)
        TEST_ALIAS_MATHS_FUNCTION_T      (comp_ellint_1,   0.5)
        TEST_ALIAS_MATHS_FUNCTION_T      (comp_ellint_2,   0.0)
        TEST_ALIAS_MATHS_FUNCTION_T_T    (comp_ellint_3,   0.5, 0.0)
        TEST_ALIAS_MATHS_FUNCTION_T_T    (cyl_bessel_i,    0.0, 1.2345)
        TEST_ALIAS_MATHS_FUNCTION_T_T    (cyl_bessel_j,    0.0, 1.2345)
        TEST_ALIAS_MATHS_FUNCTION_T_T    (cyl_bessel_k,    0.5, 1.2345)
        TEST_ALIAS_MATHS_FUNCTION_T_T    (cyl_neumann,     0.5, 0.333)
        TEST_ALIAS_MATHS_FUNCTION_T_T    (ellint_1,        0.0, 1.5)
        TEST_ALIAS_MATHS_FUNCTION_T_T    (ellint_2,        0.0, 1.5)
        TEST_ALIAS_MATHS_FUNCTION_T_T_T  (ellint_3,        0.0, 0.0, 1.5)
        TEST_ALIAS_MATHS_FUNCTION_T      (expint,          1.0)
        TEST_ALIAS_MATHS_FUNCTION_U_T    (hermite,         3u, 10.0)
        TEST_ALIAS_MATHS_FUNCTION_U_T    (laguerre,        2u, 0.5)
        TEST_ALIAS_MATHS_FUNCTION_U_T    (legendre,        3u, 0.25)
        TEST_ALIAS_MATHS_FUNCTION_T      (riemann_zeta,    0.5)
        TEST_ALIAS_MATHS_FUNCTION_U_T    (sph_bessel,      1u, 1.2345)
        TEST_ALIAS_MATHS_FUNCTION_U_U_T  (sph_legendre,    3u, 0u, 1.2345)
        TEST_ALIAS_MATHS_FUNCTION_U_T    (sph_neumann,     1u, 1.2345)

    #endif

}

void test_rs_core_alias_numnbers() {

    TEST_NEAR(*std::numbers::e_v<AD>,      std::numbers::e_v<double>,      1e-15);
    TEST_NEAR(*std::numbers::pi_v<AD>,     std::numbers::pi_v<double>,     1e-15);
    TEST_NEAR(*std::numbers::sqrt2_v<AD>,  std::numbers::sqrt2_v<double>,  1e-15);

}

void test_rs_core_alias_numeric_limits() {

    using AL = std::numeric_limits<AD>;
    using DL = std::numeric_limits<double>;

    TEST(AL::is_specialized);
    TEST_EQUAL(AL::is_iec559, DL::is_iec559);
    TEST_EQUAL(*AL::max(), DL::max());
    TEST_EQUAL(*AL::min(), DL::min());

}
