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

#define TEST_ALIAS_MATHS_FUNCTION_T_YIELDS_T(f, x) do { \
    AD ax{x}; \
    auto r = std::f(x); \
    auto ar = f(ax); \
    TEST_NEAR(*ar, r, 1e-10); \
} while (false)

#define TEST_ALIAS_MATHS_FUNCTION_T_YIELDS_RT(f, x, RT) do { \
    AD ax{x}; \
    auto r1 = std::f(x); \
    auto r2 = f(ax); \
    TEST_NEAR(r2, r1, 1e-10); \
} while (false)

#define TEST_ALIAS_MATHS_FUNCTION_T_T_YIELDS_T(f, x, y) do { \
    AD ax{x}; \
    AD ay{y}; \
    auto r = std::f(x, y); \
    auto ar = f(ax, ay); \
    TEST_NEAR(*ar, r, 1e-10); \
} while (false)

#define TEST_ALIAS_MATHS_FUNCTION_T_T_YIELDS_RT(f, x, y, RT) do { \
    AD ax{x}; \
    AD ay{y}; \
    auto r1 = std::f(x, y); \
    auto r2 = f(ax, ay); \
    TEST_NEAR(r2, r1, 1e-10); \
} while (false)

#define TEST_ALIAS_MATHS_FUNCTION_T_TPTR_YIELDS_T(f, x) do { \
    AD ax{x}; \
    AD ay{}; \
    double y{}; \
    auto r = std::f(x, &y); \
    auto ar = f(ax, &ay); \
    TEST_NEAR(*ar, r, 1e-10); \
    TEST_NEAR(*ay, y, 1e-10); \
} while (false)

#define TEST_ALIAS_MATHS_FUNCTION_T_U_YIELDS_T(f, x, y) do { \
    AD ax{x}; \
    auto r = std::f(x, y); \
    auto ar = f(ax, y); \
    TEST_NEAR(*ar, r, 1e-10); \
} while (false)

#define TEST_ALIAS_MATHS_FUNCTION_T_UPTR_YIELDS_T(f, x, U) do { \
    AD ax{x}; \
    U y1{}; \
    U y2{}; \
    auto r = std::f(x, &y1); \
    auto ar = f(ax, &y2); \
    TEST_NEAR(*ar, r, 1e-10); \
    TEST_EQUAL(y1, y2); \
} while (false)

#define TEST_ALIAS_MATHS_FUNCTION_U_T_YIELDS_T(f, x, y) do { \
    AD ay{y}; \
    auto r = std::f(x, y); \
    auto ar = f(x, ay); \
    TEST_NEAR(*ar, r, 1e-10); \
} while (false)

#define TEST_ALIAS_MATHS_FUNCTION_T_T_T_YIELDS_T(f, x, y, z) do { \
    AD ax{x}; \
    AD ay{y}; \
    AD az{z}; \
    auto r = std::f(x, y, z); \
    auto ar = f(ax, ay, az); \
    TEST_NEAR(*ar, r, 1e-10); \
} while (false)

#define TEST_ALIAS_MATHS_FUNCTION_T_T_UPTR_YIELDS_T(f, x, y, U) do { \
    AD ax{x}; \
    AD ay{y}; \
    U z1{}; \
    U z2{}; \
    auto r = std::f(x, y, &z1); \
    auto ar = f(ax, ay, &z2); \
    TEST_NEAR(*ar, r, 1e-10); \
    TEST_EQUAL(z1, z2); \
} while (false)

#define TEST_ALIAS_MATHS_FUNCTION_U_U_T_YIELDS_T(f, x, y, z) do { \
    AD az{z}; \
    auto r = std::f(x, y, z); \
    auto ar = f(x, y, az); \
    TEST_NEAR(*ar, r, 1e-10); \
} while (false)

void test_rs_core_alias_maths_functions() {

    TEST_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (acos,            0.5);
    TEST_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (acosh,           0.5);
    TEST_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (asin,            0.5);
    TEST_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (asinh,           0.5);
    TEST_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (atan,            0.5);
    TEST_ALIAS_MATHS_FUNCTION_T_T_YIELDS_T       (atan2,           0.5, 1.5);
    TEST_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (atanh,           0.5);
    TEST_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (cbrt,            0.5);
    TEST_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (ceil,            2.5);
    TEST_ALIAS_MATHS_FUNCTION_T_T_YIELDS_T       (copysign,        0.5, -1.5);
    TEST_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (cos,             0.5);
    TEST_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (cosh,            1.5);
    TEST_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (erf,             0.5);
    TEST_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (erfc,            0.5);
    TEST_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (exp,             0.5);
    TEST_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (exp2,            0.5);
    TEST_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (expm1,           0.5);
    TEST_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (fabs,            -1.5);
    TEST_ALIAS_MATHS_FUNCTION_T_T_YIELDS_T       (fdim,            2.5, 1.5);
    TEST_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (floor,           2.5);
    TEST_ALIAS_MATHS_FUNCTION_T_T_T_YIELDS_T     (fma,             0.5, 1.5, 2.5);
    TEST_ALIAS_MATHS_FUNCTION_T_T_YIELDS_T       (fmax,            0.5, 1.5);
    TEST_ALIAS_MATHS_FUNCTION_T_T_YIELDS_T       (fmin,            0.5, 1.5);
    TEST_ALIAS_MATHS_FUNCTION_T_T_YIELDS_T       (fmod,            2.5, 1.5);
    TEST_ALIAS_MATHS_FUNCTION_T_YIELDS_RT        (fpclassify,      0.5, int);
    TEST_ALIAS_MATHS_FUNCTION_T_UPTR_YIELDS_T    (frexp,           1.2345, int);
    TEST_ALIAS_MATHS_FUNCTION_T_T_YIELDS_T       (hypot,           0.5, 1.5);
    TEST_ALIAS_MATHS_FUNCTION_T_T_T_YIELDS_T     (hypot,           0.5, 1.5, 2.5);
    TEST_ALIAS_MATHS_FUNCTION_T_YIELDS_RT        (ilogb,           2.5, int);
    TEST_ALIAS_MATHS_FUNCTION_T_YIELDS_RT        (isfinite,        0.5, bool);
    TEST_ALIAS_MATHS_FUNCTION_T_T_YIELDS_RT      (isgreater,       0.5, 1.5, bool);
    TEST_ALIAS_MATHS_FUNCTION_T_T_YIELDS_RT      (isgreaterequal,  0.5, 1.5, bool);
    TEST_ALIAS_MATHS_FUNCTION_T_YIELDS_RT        (isinf,           0.5, bool);
    TEST_ALIAS_MATHS_FUNCTION_T_T_YIELDS_RT      (isless,          0.5, 1.5, bool);
    TEST_ALIAS_MATHS_FUNCTION_T_T_YIELDS_RT      (islessequal,     0.5, 1.5, bool);
    TEST_ALIAS_MATHS_FUNCTION_T_T_YIELDS_RT      (islessgreater,   0.5, 1.5, bool);
    TEST_ALIAS_MATHS_FUNCTION_T_YIELDS_RT        (isnan,           0.5, bool);
    TEST_ALIAS_MATHS_FUNCTION_T_YIELDS_RT        (isnormal,        0.5, bool);
    TEST_ALIAS_MATHS_FUNCTION_T_T_YIELDS_RT      (isunordered,     0.5, 1.5, bool);
    TEST_ALIAS_MATHS_FUNCTION_T_U_YIELDS_T       (ldexp,           0.5, 5);
    TEST_ALIAS_MATHS_FUNCTION_T_T_T_YIELDS_T     (lerp,            0.5, 1.5, 2.5);
    TEST_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (lgamma,          5.0);
    TEST_ALIAS_MATHS_FUNCTION_T_YIELDS_RT        (llrint,          2.5, long long);
    TEST_ALIAS_MATHS_FUNCTION_T_YIELDS_RT        (llround,         2.5, long long);
    TEST_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (log,             0.5);
    TEST_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (log10,           0.5);
    TEST_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (log1p,           0.5);
    TEST_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (log2,            0.5);
    TEST_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (logb,            2.5);
    TEST_ALIAS_MATHS_FUNCTION_T_YIELDS_RT        (lrint,           2.5, long);
    TEST_ALIAS_MATHS_FUNCTION_T_YIELDS_RT        (lround,          2.5, long);
    TEST_ALIAS_MATHS_FUNCTION_T_TPTR_YIELDS_T    (modf,            1.2345);
    TEST_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (nearbyint,       2.5);
    TEST_ALIAS_MATHS_FUNCTION_T_T_YIELDS_T       (nextafter,       0.5, 1.5);
    TEST_ALIAS_MATHS_FUNCTION_T_U_YIELDS_T       (nexttoward,      0.5, 1.5L);
    TEST_ALIAS_MATHS_FUNCTION_T_T_YIELDS_T       (pow,             0.5, 1.5);
    TEST_ALIAS_MATHS_FUNCTION_T_T_YIELDS_T       (remainder,       2.5, 1.5);
    TEST_ALIAS_MATHS_FUNCTION_T_T_UPTR_YIELDS_T  (remquo,          2.5, 1.5, int);
    TEST_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (rint,            2.5);
    TEST_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (round,           2.5);
    TEST_ALIAS_MATHS_FUNCTION_T_U_YIELDS_T       (scalbln,         0.5, 5L);
    TEST_ALIAS_MATHS_FUNCTION_T_U_YIELDS_T       (scalbn,          0.5, 5);
    TEST_ALIAS_MATHS_FUNCTION_T_YIELDS_RT        (signbit,         -0.5, bool);
    TEST_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (sin,             0.5);
    TEST_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (sinh,            0.5);
    TEST_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (sqrt,            0.5);
    TEST_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (tan,             0.5);
    TEST_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (tanh,            0.5);
    TEST_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (tgamma,          5.0);
    TEST_ALIAS_MATHS_FUNCTION_T_YIELDS_T         (trunc,           1.5);

    #if __cpp_lib_math_special_functions >= 201603L

        TEST_ALIAS_MATHS_FUNCTION_U_U_T_YIELDS_T  (assoc_laguerre,  2u, 10u, 0.5)
        TEST_ALIAS_MATHS_FUNCTION_U_U_T_YIELDS_T  (assoc_legendre,  2u, 1u, 0.5)
        TEST_ALIAS_MATHS_FUNCTION_T_T_YIELDS_T    (beta,            0.123, 0.877)
        TEST_ALIAS_MATHS_FUNCTION_T_YIELDS_T      (comp_ellint_1,   0.5)
        TEST_ALIAS_MATHS_FUNCTION_T_YIELDS_T      (comp_ellint_2,   0.0)
        TEST_ALIAS_MATHS_FUNCTION_T_T_YIELDS_T    (comp_ellint_3,   0.5, 0.0)
        TEST_ALIAS_MATHS_FUNCTION_T_T_YIELDS_T    (cyl_bessel_i,    0.0, 1.2345)
        TEST_ALIAS_MATHS_FUNCTION_T_T_YIELDS_T    (cyl_bessel_j,    0.0, 1.2345)
        TEST_ALIAS_MATHS_FUNCTION_T_T_YIELDS_T    (cyl_bessel_k,    0.5, 1.2345)
        TEST_ALIAS_MATHS_FUNCTION_T_T_YIELDS_T    (cyl_neumann,     0.5, 0.333)
        TEST_ALIAS_MATHS_FUNCTION_T_T_YIELDS_T    (ellint_1,        0.0, 1.5)
        TEST_ALIAS_MATHS_FUNCTION_T_T_YIELDS_T    (ellint_2,        0.0, 1.5)
        TEST_ALIAS_MATHS_FUNCTION_T_T_T_YIELDS_T  (ellint_3,        0.0, 0.0, 1.5)
        TEST_ALIAS_MATHS_FUNCTION_T_YIELDS_T      (expint,          1.0)
        TEST_ALIAS_MATHS_FUNCTION_U_T_YIELDS_T    (hermite,         3u, 10.0)
        TEST_ALIAS_MATHS_FUNCTION_U_T_YIELDS_T    (laguerre,        2u, 0.5)
        TEST_ALIAS_MATHS_FUNCTION_U_T_YIELDS_T    (legendre,        3u, 0.25)
        TEST_ALIAS_MATHS_FUNCTION_T_YIELDS_T      (riemann_zeta,    0.5)
        TEST_ALIAS_MATHS_FUNCTION_U_T_YIELDS_T    (sph_bessel,      1u, 1.2345)
        TEST_ALIAS_MATHS_FUNCTION_U_U_T_YIELDS_T  (sph_legendre,    3u, 0u, 1.2345)
        TEST_ALIAS_MATHS_FUNCTION_U_T_YIELDS_T    (sph_neumann,     1u, 1.2345)

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
