#include "rs-core/bitwise-integer.hpp"
#include "rs-core/unit-test.hpp"
#include <concepts>
#include <cstdint>
#include <unordered_set>

using namespace RS;
using namespace RS::Literals;

void test_rs_core_bitwise_integer_implementation_selection() {

    TEST((std::same_as<Uint<1>, SmallUint<1>>));
    TEST((std::same_as<Uint<5>, SmallUint<5>>));
    TEST((std::same_as<Uint<10>, SmallUint<10>>));
    TEST((std::same_as<Uint<20>, SmallUint<20>>));
    TEST((std::same_as<Uint<30>, SmallUint<30>>));
    TEST((std::same_as<Uint<40>, SmallUint<40>>));
    TEST((std::same_as<Uint<50>, SmallUint<50>>));
    TEST((std::same_as<Uint<60>, SmallUint<60>>));
    TEST((std::same_as<Uint<64>, SmallUint<64>>));
    TEST((std::same_as<Uint<65>, LargeUint<65>>));
    TEST((std::same_as<Uint<70>, LargeUint<70>>));
    TEST((std::same_as<Uint<80>, LargeUint<80>>));
    TEST((std::same_as<Uint<90>, LargeUint<90>>));
    TEST((std::same_as<Uint<100>, LargeUint<100>>));
    TEST((std::same_as<Uint<200>, LargeUint<200>>));
    TEST((std::same_as<Uint<500>, LargeUint<500>>));
    TEST((std::same_as<Uint<1000>, LargeUint<1000>>));

}

namespace {

    template <typename T1, typename T2>
    void do_conversion_tests() {

        const auto ca = 0x0123456789abcdefull;
        const auto cb = ~ ca;
        const auto mask1 = static_cast<std::uint64_t>(T1::max());
        const auto mask2 = static_cast<std::uint64_t>(T2::max());

        T1 x1, y1, z1;
        T2 x2, y2, z2;

        TRY(x1 = static_cast<T1>(ca));  TEST_EQUAL(static_cast<std::uint64_t>(x1), ca & mask1);
        TRY(y2 = static_cast<T2>(x1));  TEST_EQUAL(static_cast<std::uint64_t>(y2), ca & mask1 & mask2);
        TRY(z1 = static_cast<T1>(y2));  TEST_EQUAL(static_cast<std::uint64_t>(z1), std::uint64_t(y2));
        TRY(x2 = static_cast<T2>(ca));  TEST_EQUAL(static_cast<std::uint64_t>(x2), ca & mask2);
        TRY(y1 = static_cast<T1>(x2));  TEST_EQUAL(static_cast<std::uint64_t>(y1), ca & mask2 & mask1);
        TRY(z2 = static_cast<T2>(y1));  TEST_EQUAL(static_cast<std::uint64_t>(z2), std::uint64_t(y1));
        TRY(x1 = static_cast<T1>(cb));  TEST_EQUAL(static_cast<std::uint64_t>(x1), cb & mask1);
        TRY(y2 = static_cast<T2>(x1));  TEST_EQUAL(static_cast<std::uint64_t>(y2), cb & mask1 & mask2);
        TRY(z1 = static_cast<T1>(y2));  TEST_EQUAL(static_cast<std::uint64_t>(z1), std::uint64_t(y2));
        TRY(x2 = static_cast<T2>(cb));  TEST_EQUAL(static_cast<std::uint64_t>(x2), cb & mask2);
        TRY(y1 = static_cast<T1>(x2));  TEST_EQUAL(static_cast<std::uint64_t>(y1), cb & mask2 & mask1);
        TRY(z2 = static_cast<T2>(y1));  TEST_EQUAL(static_cast<std::uint64_t>(z2), std::uint64_t(y1));

    }

}

void test_rs_core_bitwise_integer_type_conversions() {

    do_conversion_tests<SmallUint<10>, SmallUint<31>>();
    do_conversion_tests<SmallUint<10>, SmallUint<32>>();
    do_conversion_tests<SmallUint<10>, SmallUint<33>>();
    do_conversion_tests<SmallUint<10>, SmallUint<63>>();
    do_conversion_tests<SmallUint<10>, SmallUint<64>>();
    do_conversion_tests<SmallUint<10>, LargeUint<31>>();
    do_conversion_tests<SmallUint<10>, LargeUint<32>>();
    do_conversion_tests<SmallUint<10>, LargeUint<33>>();
    do_conversion_tests<SmallUint<10>, LargeUint<63>>();
    do_conversion_tests<SmallUint<10>, LargeUint<64>>();
    do_conversion_tests<LargeUint<10>, SmallUint<31>>();
    do_conversion_tests<LargeUint<10>, SmallUint<32>>();
    do_conversion_tests<LargeUint<10>, SmallUint<33>>();
    do_conversion_tests<LargeUint<10>, SmallUint<63>>();
    do_conversion_tests<LargeUint<10>, SmallUint<64>>();
    do_conversion_tests<LargeUint<10>, LargeUint<31>>();
    do_conversion_tests<LargeUint<10>, LargeUint<32>>();
    do_conversion_tests<LargeUint<10>, LargeUint<33>>();
    do_conversion_tests<LargeUint<10>, LargeUint<63>>();
    do_conversion_tests<LargeUint<10>, LargeUint<64>>();

}

void test_rs_core_bitwise_integer_string_parsing() {

    SmallUint<35> x;
    LargeUint<35> y;

    TEST(! SmallUint<35>::try_parse("", x));
    TEST(! SmallUint<35>::try_parse("a", x));
    TEST(! SmallUint<35>::try_parse("123456789xyz", x, 16));

    TEST(SmallUint<35>::try_parse("0", x));                      TEST_EQUAL(static_cast<std::uint64_t>(x), 0u);
    TEST(SmallUint<35>::try_parse("42", x));                     TEST_EQUAL(static_cast<std::uint64_t>(x), 42u);
    TEST(SmallUint<35>::try_parse("1234567890", x));             TEST_EQUAL(static_cast<std::uint64_t>(x), 1234567890ull);
    TEST(SmallUint<35>::try_parse("123456789", x, 16));          TEST_EQUAL(static_cast<std::uint64_t>(x), 0x123456789ull);
    TEST(SmallUint<35>::try_parse("101010110011001100", x, 2));  TEST_EQUAL(static_cast<std::uint64_t>(x), 0x00002acccull);

    TEST(! LargeUint<35>::try_parse("", y));
    TEST(! LargeUint<35>::try_parse("a", y));
    TEST(! LargeUint<35>::try_parse("123456789xyz", y, 16));

    TEST(LargeUint<35>::try_parse("0", y));                      TEST_EQUAL(static_cast<std::uint64_t>(y), 0u);
    TEST(LargeUint<35>::try_parse("42", y));                     TEST_EQUAL(static_cast<std::uint64_t>(y), 42u);
    TEST(LargeUint<35>::try_parse("1234567890", y));             TEST_EQUAL(static_cast<std::uint64_t>(y), 1234567890ull);
    TEST(LargeUint<35>::try_parse("123456789", y, 16));          TEST_EQUAL(static_cast<std::uint64_t>(y), 0x123456789ull);
    TEST(LargeUint<35>::try_parse("101010110011001100", y, 2));  TEST_EQUAL(static_cast<std::uint64_t>(y), 0x00002acccull);

    Uint128 u;

    TRY(u = 123456789123456789123456789123456789_u128);
    TEST_EQUAL(u.dec(), "123456789123456789123456789123456789");
    TRY(u = 0x123456789abcdef123456789abcdef_u128);
    TEST_EQUAL(u.hex(), "00123456789abcdef123456789abcdef");
    TRY(u = 0b10101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010_u128);
    TEST_EQUAL(u.bin(), "10101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010");

    TRY(u = 123'456'789'123'456'789'123'456'789'123'456'789_u128);
    TEST_EQUAL(u.dec(), "123456789123456789123456789123456789");
    TRY(u = 0x12'3456'789a'bcde'f123'4567'89ab'cdef_u128);
    TEST_EQUAL(u.hex(), "00123456789abcdef123456789abcdef");
    TRY(u = 0b10101010'10101010'10101010'10101010'10101010'10101010'10101010'10101010'10101010'10101010'10101010'10101010'10101010'10101010'10101010'10101010_u128);
    TEST_EQUAL(u.bin(), "10101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010");

}

void test_rs_core_bitwise_integer_hash() {

    std::unordered_set<SmallUint<5>> set_s5;
    std::unordered_set<SmallUint<50>> set_s50;
    std::unordered_set<LargeUint<50>> set_l50;
    std::unordered_set<LargeUint<500>> set_l500;

    TEST(set_s5.empty());
    TEST(set_s50.empty());
    TEST(set_l50.empty());
    TEST(set_l500.empty());

    for (auto i = 1u; i <= 10; ++i) {
        TRY(set_s5.insert(SmallUint<5>(i)));
        TRY(set_s50.insert(SmallUint<50>(i)));
        TRY(set_l50.insert(LargeUint<50>(i)));
        TRY(set_l500.insert(LargeUint<500>(i)));
    }

    TEST_EQUAL(set_s5.size(), 10u);
    TEST_EQUAL(set_s50.size(), 10u);
    TEST_EQUAL(set_l50.size(), 10u);
    TEST_EQUAL(set_l500.size(), 10u);

}
