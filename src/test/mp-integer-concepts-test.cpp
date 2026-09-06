#include "rs-core/mp-integer.hpp"
#include "rs-core/unit-test.hpp"

using namespace RS;

void test_rs_core_mp_integer_concepts() {

    TEST(! SignedIntegral<Natural>);
    TEST(UnsignedIntegral<Natural>);
    TEST(Integral<Natural>);
    TEST(! FloatingPoint<Natural>);
    TEST(! FixedPointArithmetic<Natural>);
    TEST(! RationalArithmetic<Natural>);
    TEST(Arithmetic<Natural>);
    TEST(Mpitype<Natural>);

    TEST(SignedIntegral<Integer>);
    TEST(! UnsignedIntegral<Integer>);
    TEST(Integral<Integer>);
    TEST(! FloatingPoint<Integer>);
    TEST(! FixedPointArithmetic<Integer>);
    TEST(! RationalArithmetic<Integer>);
    TEST(Arithmetic<Integer>);
    TEST(Mpitype<Integer>);

}
