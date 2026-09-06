#include "rs-core/mp-integer.hpp"
#include "rs-core/unit-test.hpp"

using namespace RS;

void test_rs_core_mp_integer_signed_conversion_to_floating_point() {

    Integer i;
    Natural n {0xfedc'babc'defe'dcbaull, 0x9876'5432'1234'5678ull};
    double d {};

    TRY((i = 0));              TRY(d = i.as_double());  TEST_EQUAL(d, 0.0);
    TRY((i = 1));              TRY(d = i.as_double());  TEST_EQUAL(d, 1.0);
    TRY((i = -1));             TRY(d = i.as_double());  TEST_EQUAL(d, -1.0);
    TRY((i = 123'456'789l));   TRY(d = i.as_double());  TEST_EQUAL(d, 123'456'789.0);
    TRY((i = -123'456'789l));  TRY(d = i.as_double());  TEST_EQUAL(d, -123'456'789.0);
    TRY((i = n));              TRY(d = i.as_double());  TEST_NEAR(d, 3.387700037e38, 1e29);
    TRY((i = - i));            TRY(d = i.as_double());  TEST_NEAR(d, -3.387700037e38, 1e29);

}
