#include "rs-core/mp-integer.hpp"
#include "rs-core/unit-test.hpp"
#include <cstdint>
#include <optional>
#include <string>

using namespace RS;

void test_rs_core_mp_integer_signed_conversion_assignment_from_integer() {

    Integer i;

    TEST_EQUAL(i.sign(), 0);
    TEST_EQUAL(static_cast<std::int64_t>(i), 0);
    TEST_EQUAL(static_cast<std::uint64_t>(i), 0u);
    TEST_EQUAL(static_cast<Natural>(i), 0u);

    TRY(i = 123'456'789l);
    TEST_EQUAL(i.sign(), 1);
    TEST_EQUAL(static_cast<std::int64_t>(i), 123'456'789l);
    TEST_EQUAL(static_cast<std::uint64_t>(i), 123'456'789ul);
    TEST_EQUAL(static_cast<Natural>(i), 123'456'789ul);

    TRY(i = -123'456'789l);
    TEST_EQUAL(i.sign(), -1);
    TEST_EQUAL(static_cast<std::int64_t>(i), -123'456'789l);
    TEST_EQUAL(static_cast<std::uint64_t>(i), 0u);
    TEST_EQUAL(static_cast<Natural>(i), 0u);

    TRY(i = 123'456'789'123'456'789ll);
    TEST_EQUAL(i.sign(), 1);
    TEST_EQUAL(static_cast<std::int64_t>(i), 123'456'789'123'456'789ll);
    TEST_EQUAL(static_cast<std::uint64_t>(i), 123'456'789'123'456'789ull);
    TEST_EQUAL(static_cast<Natural>(i), 123'456'789'123'456'789ull);

    TRY(i = -123'456'789'123'456'789ll);
    TEST_EQUAL(i.sign(), -1);
    TEST_EQUAL(static_cast<std::int64_t>(i), -123'456'789'123'456'789ll);
    TEST_EQUAL(static_cast<std::uint64_t>(i), 0u);
    TEST_EQUAL(static_cast<Natural>(i), 0u);

}

void test_rs_core_mp_integer_signed_conversion_maybe_cast_from_integer() {

    Integer i;
    std::optional<std::int16_t> a;
    std::optional<std::uint16_t> b;
    std::optional<std::int32_t> c;
    std::optional<std::uint32_t> d;

    TRY(i = 32'767l);
    TEST(i.in_range<std::int16_t>());   TRY(a = i.maybe_cast<std::int16_t>());   TEST(a); TEST_EQUAL(*a, 32'767l);
    TEST(i.in_range<std::uint16_t>());  TRY(b = i.maybe_cast<std::uint16_t>());  TEST(b); TEST_EQUAL(*b, 32'767ul);
    TEST(i.in_range<std::int32_t>());   TRY(c = i.maybe_cast<std::int32_t>());   TEST(c); TEST_EQUAL(*c, 32'767l);
    TEST(i.in_range<std::uint32_t>());  TRY(d = i.maybe_cast<std::uint32_t>());  TEST(d); TEST_EQUAL(*d, 32'767ul);

    TRY(i = 32'768l);
    TEST(! i.in_range<std::int16_t>());  TRY(a = i.maybe_cast<std::int16_t>());   TEST(! a);
    TEST(i.in_range<std::uint16_t>());   TRY(b = i.maybe_cast<std::uint16_t>());  TEST(b); TEST_EQUAL(*b, 32'768ul);
    TEST(i.in_range<std::int32_t>());    TRY(c = i.maybe_cast<std::int32_t>());   TEST(c); TEST_EQUAL(*c, 32'768l);
    TEST(i.in_range<std::uint32_t>());   TRY(d = i.maybe_cast<std::uint32_t>());  TEST(d); TEST_EQUAL(*d, 32'768ul);

    TRY(i = 65'535l);
    TEST(! i.in_range<std::int16_t>());  TRY(a = i.maybe_cast<std::int16_t>());   TEST(! a);
    TEST(i.in_range<std::uint16_t>());   TRY(b = i.maybe_cast<std::uint16_t>());  TEST(b); TEST_EQUAL(*b, 65'535ul);
    TEST(i.in_range<std::int32_t>());    TRY(c = i.maybe_cast<std::int32_t>());   TEST(c); TEST_EQUAL(*c, 65'535l);
    TEST(i.in_range<std::uint32_t>());   TRY(d = i.maybe_cast<std::uint32_t>());  TEST(d); TEST_EQUAL(*d, 65'535ul);

    TRY(i = 65'536l);
    TEST(! i.in_range<std::int16_t>());   TRY(a = i.maybe_cast<std::int16_t>());   TEST(! a);
    TEST(! i.in_range<std::uint16_t>());  TRY(b = i.maybe_cast<std::uint16_t>());  TEST(! b);
    TEST(i.in_range<std::int32_t>());     TRY(c = i.maybe_cast<std::int32_t>());   TEST(c); TEST_EQUAL(*c, 65'536l);
    TEST(i.in_range<std::uint32_t>());    TRY(d = i.maybe_cast<std::uint32_t>());  TEST(d); TEST_EQUAL(*d, 65'536ul);

    TRY(i = -32'767l);
    TEST(i.in_range<std::int16_t>());     TRY(a = i.maybe_cast<std::int16_t>());   TEST(a); TEST_EQUAL(*a, -32'767l);
    TEST(! i.in_range<std::uint16_t>());  TRY(b = i.maybe_cast<std::uint16_t>());  TEST(! b);
    TEST(i.in_range<std::int32_t>());     TRY(c = i.maybe_cast<std::int32_t>());   TEST(c); TEST_EQUAL(*c, -32'767l);
    TEST(! i.in_range<std::uint32_t>());  TRY(d = i.maybe_cast<std::uint32_t>());  TEST(! d);

    TRY(i = -32'768l);
    TEST(i.in_range<std::int16_t>());     TRY(a = i.maybe_cast<std::int16_t>());   TEST(a); TEST_EQUAL(*a, -32'768l);
    TEST(! i.in_range<std::uint16_t>());  TRY(b = i.maybe_cast<std::uint16_t>());  TEST(! b);
    TEST(i.in_range<std::int32_t>());     TRY(c = i.maybe_cast<std::int32_t>());   TEST(c); TEST_EQUAL(*c, -32'768l);
    TEST(! i.in_range<std::uint32_t>());  TRY(d = i.maybe_cast<std::uint32_t>());  TEST(! d);

    TRY(i = -32'769l);
    TEST(! i.in_range<std::int16_t>());   TRY(a = i.maybe_cast<std::int16_t>());   TEST(! a);
    TEST(! i.in_range<std::uint16_t>());  TRY(b = i.maybe_cast<std::uint16_t>());  TEST(! b);
    TEST(i.in_range<std::int32_t>());     TRY(c = i.maybe_cast<std::int32_t>());   TEST(c); TEST_EQUAL(*c, -32'769l);
    TEST(! i.in_range<std::uint32_t>());  TRY(d = i.maybe_cast<std::uint32_t>());  TEST(! d);

    TRY(i = -65'535l);
    TEST(! i.in_range<std::int16_t>());   TRY(a = i.maybe_cast<std::int16_t>());   TEST(! a);
    TEST(! i.in_range<std::uint16_t>());  TRY(b = i.maybe_cast<std::uint16_t>());  TEST(! b);
    TEST(i.in_range<std::int32_t>());     TRY(c = i.maybe_cast<std::int32_t>());   TEST(c); TEST_EQUAL(*c, -65'535l);
    TEST(! i.in_range<std::uint32_t>());  TRY(d = i.maybe_cast<std::uint32_t>());  TEST(! d);

    TRY(i = -65'536l);
    TEST(! i.in_range<std::int16_t>());   TRY(a = i.maybe_cast<std::int16_t>());   TEST(! a);
    TEST(! i.in_range<std::uint16_t>());  TRY(b = i.maybe_cast<std::uint16_t>());  TEST(! b);
    TEST(i.in_range<std::int32_t>());     TRY(c = i.maybe_cast<std::int32_t>());   TEST(c); TEST_EQUAL(*c, -65'536l);
    TEST(! i.in_range<std::uint32_t>());  TRY(d = i.maybe_cast<std::uint32_t>());  TEST(! d);

    TRY(i = -65'537l);
    TEST(! i.in_range<std::int16_t>());   TRY(a = i.maybe_cast<std::int16_t>());   TEST(! a);
    TEST(! i.in_range<std::uint16_t>());  TRY(b = i.maybe_cast<std::uint16_t>());  TEST(! b);
    TEST(i.in_range<std::int32_t>());     TRY(c = i.maybe_cast<std::int32_t>());   TEST(c); TEST_EQUAL(*c, -65'537l);
    TEST(! i.in_range<std::uint32_t>());  TRY(d = i.maybe_cast<std::uint32_t>());  TEST(! d);

}
