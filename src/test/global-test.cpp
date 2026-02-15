#include "rs-core/global.hpp"
#include "rs-core/unit-test.hpp"
#include <cstdint>
#include <string>
#include <string_view>

using namespace RS;

namespace {

    template <SignedIntegral T>        std::string_view select(T) { return "SignedIntegral"; }
    template <UnsignedIntegral T>      std::string_view select(T) { return "UnsignedIntegral"; }
    template <Integral T>              std::string_view select(T) { return "Integral"; }
    template <FloatingPoint T>         std::string_view select(T) { return "FloatingPoint"; }
    template <FixedPointArithmetic T>  std::string_view select(T) { return "FixedPointArithmetic"; }
    template <RationalArithmetic T>    std::string_view select(T) { return "RationalArithmetic"; }
    template <Arithmetic T>            std::string_view select(T) { return "Arithmetic"; }

}

void test_rs_core_global_primitive_concepts() {

    TEST(! Reference<int>);
    TEST(Reference<int&>);
    TEST(Reference<const int&>);
    TEST(! MutableReference<int>);
    TEST(MutableReference<int&>);
    TEST(! MutableReference<const int&>);
    TEST(! ConstReference<int>);
    TEST(! ConstReference<int&>);
    TEST(ConstReference<const int&>);
    TEST(NonReference<int>);
    TEST(! NonReference<int&>);
    TEST(! NonReference<const int&>);

}

void test_rs_core_global_arithmetic_concepts() {

    TEST(SignedIntegral<int>);
    TEST(! SignedIntegral<unsigned>);
    TEST(SignedIntegral<std::int64_t>);
    TEST(! SignedIntegral<std::uint64_t>);
    TEST(! SignedIntegral<double>);
    TEST(! SignedIntegral<bool>);
    TEST(! SignedIntegral<int*>);
    TEST(! SignedIntegral<std::string>);
    TEST(! UnsignedIntegral<int>);
    TEST(UnsignedIntegral<unsigned>);
    TEST(! UnsignedIntegral<std::int64_t>);
    TEST(UnsignedIntegral<std::uint64_t>);
    TEST(! UnsignedIntegral<double>);
    TEST(! UnsignedIntegral<bool>);
    TEST(! UnsignedIntegral<int*>);
    TEST(! UnsignedIntegral<std::string>);
    TEST(Integral<int>);
    TEST(Integral<unsigned>);
    TEST(Integral<std::int64_t>);
    TEST(Integral<std::uint64_t>);
    TEST(! Integral<double>);
    TEST(! Integral<bool>);
    TEST(! Integral<int*>);
    TEST(! Integral<std::string>);
    TEST(! FloatingPoint<int>);
    TEST(! FloatingPoint<unsigned>);
    TEST(! FloatingPoint<std::int64_t>);
    TEST(! FloatingPoint<std::uint64_t>);
    TEST(FloatingPoint<double>);
    TEST(! FloatingPoint<bool>);
    TEST(! FloatingPoint<int*>);
    TEST(! FloatingPoint<std::string>);
    TEST(! FixedPointArithmetic<int>);
    TEST(! FixedPointArithmetic<unsigned>);
    TEST(! FixedPointArithmetic<std::int64_t>);
    TEST(! FixedPointArithmetic<std::uint64_t>);
    TEST(! FixedPointArithmetic<double>);
    TEST(! FixedPointArithmetic<bool>);
    TEST(! FixedPointArithmetic<int*>);
    TEST(! FixedPointArithmetic<std::string>);
    TEST(! RationalArithmetic<int>);
    TEST(! RationalArithmetic<unsigned>);
    TEST(! RationalArithmetic<std::int64_t>);
    TEST(! RationalArithmetic<std::uint64_t>);
    TEST(! RationalArithmetic<double>);
    TEST(! RationalArithmetic<bool>);
    TEST(! RationalArithmetic<int*>);
    TEST(! RationalArithmetic<std::string>);
    TEST(Arithmetic<int>);
    TEST(Arithmetic<unsigned>);
    TEST(Arithmetic<std::int64_t>);
    TEST(Arithmetic<std::uint64_t>);
    TEST(Arithmetic<double>);
    TEST(! Arithmetic<bool>);
    TEST(! Arithmetic<int*>);
    TEST(! Arithmetic<std::string>);

    TEST_EQUAL(select(86),     "SignedIntegral");
    TEST_EQUAL(select(99u),    "UnsignedIntegral");
    TEST_EQUAL(select(12.34),  "FloatingPoint");

}
