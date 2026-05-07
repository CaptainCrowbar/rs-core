#include "rs-core/arithmetic.hpp"
#include "rs-core/unit-test.hpp"
#include <cstdint>
#include <optional>
#include <stdexcept>

using namespace RS;

void test_rs_core_arithmetic_maybe_cast() {

    std::int8_t i8;
    std::int16_t i16;
    std::int32_t i32;
    std::uint8_t u8;
    std::uint16_t u16;
    std::uint32_t u32;
    std::optional<std::int16_t> oi;
    std::optional<std::uint16_t> ou;

    // Signed to signed

    i8 = 0;        TRY(oi = maybe_cast<std::int16_t>(i8));   TEST(oi); TEST_EQUAL(oi.value(), 0);
    i8 = 1;        TRY(oi = maybe_cast<std::int16_t>(i8));   TEST(oi); TEST_EQUAL(oi.value(), 1);
    i8 = 127;      TRY(oi = maybe_cast<std::int16_t>(i8));   TEST(oi); TEST_EQUAL(oi.value(), 127);
    i8 = -1;       TRY(oi = maybe_cast<std::int16_t>(i8));   TEST(oi); TEST_EQUAL(oi.value(), -1);
    i8 = -128;     TRY(oi = maybe_cast<std::int16_t>(i8));   TEST(oi); TEST_EQUAL(oi.value(), -128);
    i16 = 0;       TRY(oi = maybe_cast<std::int16_t>(i16));  TEST(oi); TEST_EQUAL(oi.value(), 0);
    i16 = 1;       TRY(oi = maybe_cast<std::int16_t>(i16));  TEST(oi); TEST_EQUAL(oi.value(), 1);
    i16 = 32767;   TRY(oi = maybe_cast<std::int16_t>(i16));  TEST(oi); TEST_EQUAL(oi.value(), 32767);
    i16 = -1;      TRY(oi = maybe_cast<std::int16_t>(i16));  TEST(oi); TEST_EQUAL(oi.value(), -1);
    i16 = -32768;  TRY(oi = maybe_cast<std::int16_t>(i16));  TEST(oi); TEST_EQUAL(oi.value(), -32768);
    i32 = 0;       TRY(oi = maybe_cast<std::int16_t>(i32));  TEST(oi); TEST_EQUAL(oi.value(), 0);
    i32 = 1;       TRY(oi = maybe_cast<std::int16_t>(i32));  TEST(oi); TEST_EQUAL(oi.value(), 1);
    i32 = 32767;   TRY(oi = maybe_cast<std::int16_t>(i32));  TEST(oi); TEST_EQUAL(oi.value(), 32767);
    i32 = 32768;   TRY(oi = maybe_cast<std::int16_t>(i32));  TEST(! oi);
    i32 = 65535;   TRY(oi = maybe_cast<std::int16_t>(i32));  TEST(! oi);
    i32 = 65536;   TRY(oi = maybe_cast<std::int16_t>(i32));  TEST(! oi);
    i32 = -1;      TRY(oi = maybe_cast<std::int16_t>(i32));  TEST(oi); TEST_EQUAL(oi.value(), -1);
    i32 = -32768;  TRY(oi = maybe_cast<std::int16_t>(i32));  TEST(oi); TEST_EQUAL(oi.value(), -32768);
    i32 = -32769;  TRY(oi = maybe_cast<std::int16_t>(i32));  TEST(! oi);
    i32 = -65535;  TRY(oi = maybe_cast<std::int16_t>(i32));  TEST(! oi);
    i32 = -65536;  TRY(oi = maybe_cast<std::int16_t>(i32));  TEST(! oi);

    // Unsigned to unsigned

    u8 = 0;       TRY(ou = maybe_cast<std::uint16_t>(u8));   TEST(ou); TEST_EQUAL(ou.value(), 0u);
    u8 = 1;       TRY(ou = maybe_cast<std::uint16_t>(u8));   TEST(ou); TEST_EQUAL(ou.value(), 1u);
    u8 = 255;     TRY(ou = maybe_cast<std::uint16_t>(u8));   TEST(ou); TEST_EQUAL(ou.value(), 255u);
    u16 = 0;      TRY(ou = maybe_cast<std::uint16_t>(u16));  TEST(ou); TEST_EQUAL(ou.value(), 0u);
    u16 = 1;      TRY(ou = maybe_cast<std::uint16_t>(u16));  TEST(ou); TEST_EQUAL(ou.value(), 1u);
    u16 = 32767;  TRY(ou = maybe_cast<std::uint16_t>(u16));  TEST(ou); TEST_EQUAL(ou.value(), 32767u);
    u16 = 32768;  TRY(ou = maybe_cast<std::uint16_t>(u16));  TEST(ou); TEST_EQUAL(ou.value(), 32768u);
    u16 = 65535;  TRY(ou = maybe_cast<std::uint16_t>(u16));  TEST(ou); TEST_EQUAL(ou.value(), 65535u);
    u32 = 0;      TRY(ou = maybe_cast<std::uint16_t>(u32));  TEST(ou); TEST_EQUAL(ou.value(), 0u);
    u32 = 1;      TRY(ou = maybe_cast<std::uint16_t>(u32));  TEST(ou); TEST_EQUAL(ou.value(), 1u);
    u32 = 32767;  TRY(ou = maybe_cast<std::uint16_t>(u32));  TEST(ou); TEST_EQUAL(ou.value(), 32767u);
    u32 = 32768;  TRY(ou = maybe_cast<std::uint16_t>(u32));  TEST(ou); TEST_EQUAL(ou.value(), 32768u);
    u32 = 65535;  TRY(ou = maybe_cast<std::uint16_t>(u32));  TEST(ou); TEST_EQUAL(ou.value(), 65535u);
    u32 = 65536;  TRY(ou = maybe_cast<std::uint16_t>(u32));  TEST(! ou);

    // Signed to unsigned

    i8 = 0;        TRY(ou = maybe_cast<std::uint16_t>(i8));   TEST(ou); TEST_EQUAL(ou.value(), 0u);
    i8 = 1;        TRY(ou = maybe_cast<std::uint16_t>(i8));   TEST(ou); TEST_EQUAL(ou.value(), 1u);
    i8 = 127;      TRY(ou = maybe_cast<std::uint16_t>(i8));   TEST(ou); TEST_EQUAL(ou.value(), 127u);
    i8 = -1;       TRY(ou = maybe_cast<std::uint16_t>(i8));   TEST(! ou);
    i8 = -128;     TRY(ou = maybe_cast<std::uint16_t>(i8));   TEST(! ou);
    i16 = 0;       TRY(ou = maybe_cast<std::uint16_t>(i16));  TEST(ou); TEST_EQUAL(ou.value(), 0u);
    i16 = 1;       TRY(ou = maybe_cast<std::uint16_t>(i16));  TEST(ou); TEST_EQUAL(ou.value(), 1u);
    i16 = 32767;   TRY(ou = maybe_cast<std::uint16_t>(i16));  TEST(ou); TEST_EQUAL(ou.value(), 32767u);
    i16 = -1;      TRY(ou = maybe_cast<std::uint16_t>(i16));  TEST(! ou);
    i16 = -32768;  TRY(ou = maybe_cast<std::uint16_t>(i16));  TEST(! ou);
    i32 = 0;       TRY(ou = maybe_cast<std::uint16_t>(i32));  TEST(ou); TEST_EQUAL(ou.value(), 0u);
    i32 = 1;       TRY(ou = maybe_cast<std::uint16_t>(i32));  TEST(ou); TEST_EQUAL(ou.value(), 1u);
    i32 = 32767;   TRY(ou = maybe_cast<std::uint16_t>(i32));  TEST(ou); TEST_EQUAL(ou.value(), 32767u);
    i32 = 32768;   TRY(ou = maybe_cast<std::uint16_t>(i32));  TEST(ou); TEST_EQUAL(ou.value(), 32768u);
    i32 = 65535;   TRY(ou = maybe_cast<std::uint16_t>(i32));  TEST(ou); TEST_EQUAL(ou.value(), 65535u);
    i32 = 65536;   TRY(ou = maybe_cast<std::uint16_t>(i32));  TEST(! ou);
    i32 = -1;      TRY(ou = maybe_cast<std::uint16_t>(i32));  TEST(! ou);
    i32 = -32768;  TRY(ou = maybe_cast<std::uint16_t>(i32));  TEST(! ou);
    i32 = -32769;  TRY(ou = maybe_cast<std::uint16_t>(i32));  TEST(! ou);
    i32 = -65535;  TRY(ou = maybe_cast<std::uint16_t>(i32));  TEST(! ou);
    i32 = -65536;  TRY(ou = maybe_cast<std::uint16_t>(i32));  TEST(! ou);

    // Unsigned to signed

    u8 = 0;       TRY(oi = maybe_cast<std::int16_t>(u8));   TEST(oi); TEST_EQUAL(oi.value(), 0);
    u8 = 1;       TRY(oi = maybe_cast<std::int16_t>(u8));   TEST(oi); TEST_EQUAL(oi.value(), 1);
    u8 = 255;     TRY(oi = maybe_cast<std::int16_t>(u8));   TEST(oi); TEST_EQUAL(oi.value(), 255);
    u16 = 0;      TRY(oi = maybe_cast<std::int16_t>(u16));  TEST(oi); TEST_EQUAL(oi.value(), 0);
    u16 = 1;      TRY(oi = maybe_cast<std::int16_t>(u16));  TEST(oi); TEST_EQUAL(oi.value(), 1);
    u16 = 32767;  TRY(oi = maybe_cast<std::int16_t>(u16));  TEST(oi); TEST_EQUAL(oi.value(), 32767);
    u16 = 32768;  TRY(oi = maybe_cast<std::int16_t>(u16));  TEST(! oi);
    u16 = 65535;  TRY(oi = maybe_cast<std::int16_t>(u16));  TEST(! oi);
    u32 = 0;      TRY(oi = maybe_cast<std::int16_t>(u32));  TEST(oi); TEST_EQUAL(oi.value(), 0);
    u32 = 1;      TRY(oi = maybe_cast<std::int16_t>(u32));  TEST(oi); TEST_EQUAL(oi.value(), 1);
    u32 = 32767;  TRY(oi = maybe_cast<std::int16_t>(u32));  TEST(oi); TEST_EQUAL(oi.value(), 32767);
    u32 = 32768;  TRY(oi = maybe_cast<std::int16_t>(u32));  TEST(! oi);
    u32 = 65535;  TRY(oi = maybe_cast<std::int16_t>(u32));  TEST(! oi);
    u32 = 65536;  TRY(oi = maybe_cast<std::int16_t>(u32));  TEST(! oi);

}

void test_rs_core_arithmetic_try_cast() {

    std::int8_t i8;
    std::int16_t i16, j16;
    std::int32_t i32;
    std::uint8_t u8;
    std::uint16_t u16, v16;
    std::uint32_t u32;

    // Signed to signed

    i8 = 0;        TRY(j16 = try_cast<std::int16_t>(i8));    TEST_EQUAL(j16, 0);
    i8 = 1;        TRY(j16 = try_cast<std::int16_t>(i8));    TEST_EQUAL(j16, 1);
    i8 = 127;      TRY(j16 = try_cast<std::int16_t>(i8));    TEST_EQUAL(j16, 127);
    i8 = -1;       TRY(j16 = try_cast<std::int16_t>(i8));    TEST_EQUAL(j16, -1);
    i8 = -128;     TRY(j16 = try_cast<std::int16_t>(i8));    TEST_EQUAL(j16, -128);
    i16 = 0;       TRY(j16 = try_cast<std::int16_t>(i16));   TEST_EQUAL(j16, 0);
    i16 = 1;       TRY(j16 = try_cast<std::int16_t>(i16));   TEST_EQUAL(j16, 1);
    i16 = 32767;   TRY(j16 = try_cast<std::int16_t>(i16));   TEST_EQUAL(j16, 32767);
    i16 = -1;      TRY(j16 = try_cast<std::int16_t>(i16));   TEST_EQUAL(j16, -1);
    i16 = -32768;  TRY(j16 = try_cast<std::int16_t>(i16));   TEST_EQUAL(j16, -32768);
    i32 = 0;       TRY(j16 = try_cast<std::int16_t>(i32));   TEST_EQUAL(j16, 0);
    i32 = 1;       TRY(j16 = try_cast<std::int16_t>(i32));   TEST_EQUAL(j16, 1);
    i32 = 32767;   TRY(j16 = try_cast<std::int16_t>(i32));   TEST_EQUAL(j16, 32767);
    i32 = -1;      TRY(j16 = try_cast<std::int16_t>(i32));   TEST_EQUAL(j16, -1);
    i32 = -32768;  TRY(j16 = try_cast<std::int16_t>(i32));   TEST_EQUAL(j16, -32768);
    i32 = 32768;   TEST_THROW(j16 = try_cast<std::int16_t>(i32), std::out_of_range, "out of range");
    i32 = 65535;   TEST_THROW(j16 = try_cast<std::int16_t>(i32), std::out_of_range, "out of range");
    i32 = 65536;   TEST_THROW(j16 = try_cast<std::int16_t>(i32), std::out_of_range, "out of range");
    i32 = -32769;  TEST_THROW(j16 = try_cast<std::int16_t>(i32), std::out_of_range, "out of range");
    i32 = -65535;  TEST_THROW(j16 = try_cast<std::int16_t>(i32), std::out_of_range, "out of range");
    i32 = -65536;  TEST_THROW(j16 = try_cast<std::int16_t>(i32), std::out_of_range, "out of range");

    // Unsigned to unsigned

    u8 = 0;       TRY(v16 = try_cast<std::uint16_t>(u8));    TEST_EQUAL(v16, 0u);
    u8 = 1;       TRY(v16 = try_cast<std::uint16_t>(u8));    TEST_EQUAL(v16, 1u);
    u8 = 255;     TRY(v16 = try_cast<std::uint16_t>(u8));    TEST_EQUAL(v16, 255u);
    u16 = 0;      TRY(v16 = try_cast<std::uint16_t>(u16));   TEST_EQUAL(v16, 0u);
    u16 = 1;      TRY(v16 = try_cast<std::uint16_t>(u16));   TEST_EQUAL(v16, 1u);
    u16 = 32767;  TRY(v16 = try_cast<std::uint16_t>(u16));   TEST_EQUAL(v16, 32767u);
    u16 = 32768;  TRY(v16 = try_cast<std::uint16_t>(u16));   TEST_EQUAL(v16, 32768u);
    u16 = 65535;  TRY(v16 = try_cast<std::uint16_t>(u16));   TEST_EQUAL(v16, 65535u);
    u32 = 0;      TRY(v16 = try_cast<std::uint16_t>(u32));   TEST_EQUAL(v16, 0u);
    u32 = 1;      TRY(v16 = try_cast<std::uint16_t>(u32));   TEST_EQUAL(v16, 1u);
    u32 = 32767;  TRY(v16 = try_cast<std::uint16_t>(u32));   TEST_EQUAL(v16, 32767u);
    u32 = 32768;  TRY(v16 = try_cast<std::uint16_t>(u32));   TEST_EQUAL(v16, 32768u);
    u32 = 65535;  TRY(v16 = try_cast<std::uint16_t>(u32));   TEST_EQUAL(v16, 65535u);
    u32 = 65536;  TEST_THROW(v16 = try_cast<std::uint16_t>(u32), std::out_of_range, "out of range");

    // Signed to unsigned

    i8 = 0;        TRY(v16 = try_cast<std::uint16_t>(i8));    TEST_EQUAL(v16, 0u);
    i8 = 1;        TRY(v16 = try_cast<std::uint16_t>(i8));    TEST_EQUAL(v16, 1u);
    i8 = 127;      TRY(v16 = try_cast<std::uint16_t>(i8));    TEST_EQUAL(v16, 127u);
    i16 = 0;       TRY(v16 = try_cast<std::uint16_t>(i16));   TEST_EQUAL(v16, 0u);
    i16 = 1;       TRY(v16 = try_cast<std::uint16_t>(i16));   TEST_EQUAL(v16, 1u);
    i16 = 32767;   TRY(v16 = try_cast<std::uint16_t>(i16));   TEST_EQUAL(v16, 32767u);
    i32 = 0;       TRY(v16 = try_cast<std::uint16_t>(i32));   TEST_EQUAL(v16, 0u);
    i32 = 1;       TRY(v16 = try_cast<std::uint16_t>(i32));   TEST_EQUAL(v16, 1u);
    i32 = 32767;   TRY(v16 = try_cast<std::uint16_t>(i32));   TEST_EQUAL(v16, 32767u);
    i32 = 32768;   TRY(v16 = try_cast<std::uint16_t>(i32));   TEST_EQUAL(v16, 32768u);
    i32 = 65535;   TRY(v16 = try_cast<std::uint16_t>(i32));   TEST_EQUAL(v16, 65535u);
    i8 = -1;       TEST_THROW(v16 = try_cast<std::uint16_t>(i8), std::out_of_range, "out of range");
    i8 = -128;     TEST_THROW(v16 = try_cast<std::uint16_t>(i8), std::out_of_range, "out of range");
    i16 = -1;      TEST_THROW(v16 = try_cast<std::uint16_t>(i16), std::out_of_range, "out of range");
    i16 = -32768;  TEST_THROW(v16 = try_cast<std::uint16_t>(i16), std::out_of_range, "out of range");
    i32 = 65536;   TEST_THROW(v16 = try_cast<std::uint16_t>(i32), std::out_of_range, "out of range");
    i32 = -1;      TEST_THROW(v16 = try_cast<std::uint16_t>(i32), std::out_of_range, "out of range");
    i32 = -32768;  TEST_THROW(v16 = try_cast<std::uint16_t>(i32), std::out_of_range, "out of range");
    i32 = -32769;  TEST_THROW(v16 = try_cast<std::uint16_t>(i32), std::out_of_range, "out of range");
    i32 = -65535;  TEST_THROW(v16 = try_cast<std::uint16_t>(i32), std::out_of_range, "out of range");
    i32 = -65536;  TEST_THROW(v16 = try_cast<std::uint16_t>(i32), std::out_of_range, "out of range");

    // Unsigned to signed

    u8 = 0;       TRY(j16 = try_cast<std::int16_t>(u8));    TEST_EQUAL(j16, 0);
    u8 = 1;       TRY(j16 = try_cast<std::int16_t>(u8));    TEST_EQUAL(j16, 1);
    u8 = 255;     TRY(j16 = try_cast<std::int16_t>(u8));    TEST_EQUAL(j16, 255);
    u16 = 0;      TRY(j16 = try_cast<std::int16_t>(u16));   TEST_EQUAL(j16, 0);
    u16 = 1;      TRY(j16 = try_cast<std::int16_t>(u16));   TEST_EQUAL(j16, 1);
    u16 = 32767;  TRY(j16 = try_cast<std::int16_t>(u16));   TEST_EQUAL(j16, 32767);
    u32 = 0;      TRY(j16 = try_cast<std::int16_t>(u32));   TEST_EQUAL(j16, 0);
    u32 = 1;      TRY(j16 = try_cast<std::int16_t>(u32));   TEST_EQUAL(j16, 1);
    u32 = 32767;  TRY(j16 = try_cast<std::int16_t>(u32));   TEST_EQUAL(j16, 32767);
    u16 = 32768;  TEST_THROW(j16 = try_cast<std::int16_t>(u16), std::out_of_range, "out of range");
    u16 = 65535;  TEST_THROW(j16 = try_cast<std::int16_t>(u16), std::out_of_range, "out of range");
    u32 = 32768;  TEST_THROW(j16 = try_cast<std::int16_t>(u32), std::out_of_range, "out of range");
    u32 = 65535;  TEST_THROW(j16 = try_cast<std::int16_t>(u32), std::out_of_range, "out of range");
    u32 = 65536;  TEST_THROW(j16 = try_cast<std::int16_t>(u32), std::out_of_range, "out of range");

}
