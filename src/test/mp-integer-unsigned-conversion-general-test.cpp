#include "rs-core/mp-integer.hpp"
#include "rs-core/unit-test.hpp"
#include <cstdint>
#include <optional>
#include <string>

using namespace RS;

void test_rs_core_mp_integer_unsigned_construction_from_list() {

    Natural x;

    TEST_EQUAL(x.to_string(16), "0");
    TRY(x = 1ull);
    TEST_EQUAL(x.to_string(16), "1");
    TRY(x = 0xab'cdef0ull);
    TEST_EQUAL(x.to_string(16), "abcdef0");
    TRY(x = 0x1234'5678ull);
    TEST_EQUAL(x.to_string(16), "12345678");
    TRY(x = 0x1234'5678'9abc'def0ull);
    TEST_EQUAL(x.to_string(16), "123456789abcdef0");
    TRY((x = {0xfedc'babc'defe'dcbaull, 0x9876'5432'1234'5678ull}));
    TEST_EQUAL(x.to_string(16), "fedcbabcdefedcba9876543212345678");
    TRY((x = {0xfedc'babc'defe'dcbaull, 0x9876'5432'1234'5678ull, 0x1f2e'3d4c'5b6a'7891ull}));
    TEST_EQUAL(x.to_string(16), "fedcbabcdefedcba98765432123456781f2e3d4c5b6a7891");
    TRY((x = {0xfedc'babc'defe'dcbaull, 0x9876'5432'1234'5678ull, 0x1f2e'3d4c'5b6a'7891ull, 0x0fed'cba9'8765'4321ull}));
    TEST_EQUAL(x.to_string(16), "fedcbabcdefedcba98765432123456781f2e3d4c5b6a78910fedcba987654321");

}

void test_rs_core_mp_integer_unsigned_conversion_from_integer() {

    Natural x;
    std::string s;
    std::optional<std::int16_t> i;
    std::optional<std::uint16_t> u;
    std::optional<std::int32_t> j;
    std::optional<std::uint32_t> v;

    TEST_EQUAL(static_cast<std::uint64_t>(x), 0u);

    TRY(x = 0x1234'5678ul);
    TEST_EQUAL(x.bits(), 29u);
    TEST_EQUAL(static_cast<std::uint64_t>(x), 0x1234'5678ul);

    TRY(x = 0x1234'5678'9abc'def0ull);
    TEST_EQUAL(x.bits(), 61u);
    TEST_EQUAL(static_cast<std::uint64_t>(x), 0x1234'5678'9abc'def0ull);

    TRY(x = 32'767ul);
    TEST(x.in_range<std::int16_t>());   TRY(i = x.maybe_cast<std::int16_t>());   TEST(i); TEST_EQUAL(*i, 32'767l);
    TEST(x.in_range<std::uint16_t>());  TRY(u = x.maybe_cast<std::uint16_t>());  TEST(u); TEST_EQUAL(*u, 32'767ul);
    TEST(x.in_range<std::int32_t>());   TRY(j = x.maybe_cast<std::int32_t>());   TEST(j); TEST_EQUAL(*j, 32'767l);
    TEST(x.in_range<std::uint32_t>());  TRY(v = x.maybe_cast<std::uint32_t>());  TEST(v); TEST_EQUAL(*v, 32'767ul);

    TRY(x = 32'768ul);
    TEST(! x.in_range<std::int16_t>());  TRY(i = x.maybe_cast<std::int16_t>());   TEST(! i);
    TEST(x.in_range<std::uint16_t>());   TRY(u = x.maybe_cast<std::uint16_t>());  TEST(u); TEST_EQUAL(*u, 32'768ul);
    TEST(x.in_range<std::int32_t>());    TRY(j = x.maybe_cast<std::int32_t>());   TEST(j); TEST_EQUAL(*j, 32'768l);
    TEST(x.in_range<std::uint32_t>());   TRY(v = x.maybe_cast<std::uint32_t>());  TEST(v); TEST_EQUAL(*v, 32'768ul);

    TRY(x = 65'535ul);
    TEST(! x.in_range<std::int16_t>());  TRY(i = x.maybe_cast<std::int16_t>());   TEST(! i);
    TEST(x.in_range<std::uint16_t>());   TRY(u = x.maybe_cast<std::uint16_t>());  TEST(u); TEST_EQUAL(*u, 65'535ul);
    TEST(x.in_range<std::int32_t>());    TRY(j = x.maybe_cast<std::int32_t>());   TEST(j); TEST_EQUAL(*j, 65'535l);
    TEST(x.in_range<std::uint32_t>());   TRY(v = x.maybe_cast<std::uint32_t>());  TEST(v); TEST_EQUAL(*v, 65'535ul);

    TRY(x = 65'536ul);
    TEST(! x.in_range<std::int16_t>());   TRY(i = x.maybe_cast<std::int16_t>());   TEST(! i);
    TEST(! x.in_range<std::uint16_t>());  TRY(u = x.maybe_cast<std::uint16_t>());  TEST(! u);
    TEST(x.in_range<std::int32_t>());     TRY(j = x.maybe_cast<std::int32_t>());   TEST(j); TEST_EQUAL(*j, 65'536l);
    TEST(x.in_range<std::uint32_t>());    TRY(v = x.maybe_cast<std::uint32_t>());  TEST(v); TEST_EQUAL(*v, 65'536ul);

}

void test_rs_core_mp_integer_unsigned_conversion_to_floating_point() {

    Natural x;
    double y{};

    TRY((x = 0u));                                                    TRY(y = x.as_double());  TEST_EQUAL(y, 0.0);
    TRY((x = 1u));                                                    TRY(y = x.as_double());  TEST_EQUAL(y, 1.0);
    TRY((x = 123'456'789ul));                                         TRY(y = x.as_double());  TEST_EQUAL(y, 123'456'789.0);
    TRY((x = {0xfedc'babc'defe'dcbaull, 0x9876'5432'1234'5678ull}));  TRY(y = x.as_double());  TEST_NEAR(y, 3.387700037e38, 1e29);

}
