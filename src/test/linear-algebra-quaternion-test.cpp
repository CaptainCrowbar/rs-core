#include "rs-core/linear-algebra.hpp"
#include "rs-core/unit-test.hpp"
#include <cstdlib>
#include <format>

using namespace RS;

namespace {

    template <typename R>
    void fuzz(R& r) {
        for (auto& x: r) {
            if (std::abs(x) < 1e-6) {
                x = 0;
            }
        }
    }

}

void test_rs_linear_algebra_quaternion() {

    Qdouble q, r, s;

    TRY(q = 0);
    TEST_EQUAL(std::format("{}", q), "Q[0,0,0,0]");
    TRY(q = 42);
    TEST_EQUAL(std::format("{}", q), "Q[42,0,0,0]");
    TRY((q = {10.0,20.0,30.0,40.0}));
    TEST_EQUAL(std::format("{}", q), "Q[10,20,30,40]");
    TEST_EQUAL(std::format("{:.3f}", q), "Q[10.000,20.000,30.000,40.000]");
    TEST_EQUAL(std::format("{:.3e}", q), "Q[1.000e+01,2.000e+01,3.000e+01,4.000e+01]");

    TEST_EQUAL(q.a(), 10);
    TEST_EQUAL(q.b(), 20);
    TEST_EQUAL(q.c(), 30);
    TEST_EQUAL(q.d(), 40);
    TEST_EQUAL(q[0], 10);
    TEST_EQUAL(q[1], 20);
    TEST_EQUAL(q[2], 30);
    TEST_EQUAL(q[3], 40);

    TEST_EQUAL(q.scalar_part(), 10);
    TEST_EQUAL(std::format("{}", q.vector_part()), "[20,30,40]");
    TEST_EQUAL(q.norm2(), 3000);
    TEST_NEAR(q.norm(), 54.772256, 1e-6);
    TEST_EQUAL(std::format("{:.4f}", q.versor()), "Q[0.1826,0.3651,0.5477,0.7303]");
    TEST_EQUAL(std::format("{:.4f}", q.reciprocal()), "Q[0.0033,-0.0067,-0.0100,-0.0133]");

    TRY(q *= 2);
    TEST_EQUAL(std::format("{}", q), "Q[20,40,60,80]");
    TRY(q /= 4);
    TEST_EQUAL(std::format("{}", q), "Q[5,10,15,20]");
    TRY((q = {10.0,20.0,30.0,40.0}));
    TRY((r = {100.0,200.0,300.0,400.0}));
    TRY(s = q + r);
    TEST_EQUAL(std::format("{}", s), "Q[110,220,330,440]");
    TRY(s = q - r);
    TEST_EQUAL(std::format("{}", s), "Q[-90,-180,-270,-360]");
    TRY((q = {2.0,3.0,5.0,7.0}));
    TRY((r = {11.0,13.0,17.0,19.0}));
    TRY(s = q * r);
    TEST_EQUAL(std::format("{}", s), "Q[-235,35,123,101]");
    TRY((q = {10.0,20.0,30.0,40.0}));
    TRY(r = q * q.reciprocal());
    TRY(fuzz(r));
    TEST_EQUAL(std::format("{}", r), "Q[1,0,0,0]");
    TRY(r = q.reciprocal() * q);
    TRY(fuzz(r));
    TEST_EQUAL(std::format("{}", r), "Q[1,0,0,0]");

}
