#include "rs-core/rational.hpp"
#include "rs-core/unit-test.hpp"

using namespace RS;

void test_rs_core_rational_int_comparison() {

    IntRational x, y;
    short z;

    /**/                 /**/                   TEST(x == y);  TEST(x <= y);  TEST(x >= y);
    TRY((x = {5, 3}));   TRY((y = {-1}));       TEST(x != y);  TEST(x > y);   TEST(x >= y);
    TRY((x = {5, 3}));   TRY((y = {0}));        TEST(x != y);  TEST(x > y);   TEST(x >= y);
    TRY((x = {5, 3}));   TRY((y = {1}));        TEST(x != y);  TEST(x > y);   TEST(x >= y);
    TRY((x = {5, 3}));   TRY((y = {2}));        TEST(x != y);  TEST(x < y);   TEST(x <= y);
    TRY((x = {5, 3}));   TRY((y = {5, 3}));     TEST(x == y);  TEST(x <= y);  TEST(x >= y);
    TRY((x = {5, 3}));   TRY((y = {10, 6}));    TEST(x == y);  TEST(x <= y);  TEST(x >= y);
    TRY((x = {5, 3}));   TRY((y = {49, 30}));   TEST(x != y);  TEST(x > y);   TEST(x >= y);
    TRY((x = {5, 3}));   TRY((y = {51, 30}));   TEST(x != y);  TEST(x < y);   TEST(x <= y);
    TRY((x = {-5, 3}));  TRY((y = {1}));        TEST(x != y);  TEST(x < y);   TEST(x <= y);
    TRY((x = {-5, 3}));  TRY((y = {0}));        TEST(x != y);  TEST(x < y);   TEST(x <= y);
    TRY((x = {-5, 3}));  TRY((y = {-1}));       TEST(x != y);  TEST(x < y);   TEST(x <= y);
    TRY((x = {-5, 3}));  TRY((y = {-2}));       TEST(x != y);  TEST(x > y);   TEST(x >= y);
    TRY((x = {-5, 3}));  TRY((y = {-5, 3}));    TEST(x == y);  TEST(x >= y);  TEST(x <= y);
    TRY((x = {-5, 3}));  TRY((y = {-10, 6}));   TEST(x == y);  TEST(x >= y);  TEST(x <= y);
    TRY((x = {-5, 3}));  TRY((y = {-49, 30}));  TEST(x != y);  TEST(x < y);   TEST(x <= y);
    TRY((x = {-5, 3}));  TRY((y = {-51, 30}));  TEST(x != y);  TEST(x > y);   TEST(x >= y);
    TRY((x = {}));       z = 0;                 TEST(x == z);  TEST(x <= z);  TEST(x >= z);
    TRY((x = {5, 3}));   z = -1;                TEST(x != z);  TEST(x > z);   TEST(x >= z);
    TRY((x = {5, 3}));   z = 0;                 TEST(x != z);  TEST(x > z);   TEST(x >= z);
    TRY((x = {5, 3}));   z = 1;                 TEST(x != z);  TEST(x > z);   TEST(x >= z);
    TRY((x = {5, 3}));   z = 2;                 TEST(x != z);  TEST(x < z);   TEST(x <= z);
    TRY((x = {-5, 3}));  z = 1;                 TEST(x != z);  TEST(x < z);   TEST(x <= z);
    TRY((x = {-5, 3}));  z = 0;                 TEST(x != z);  TEST(x < z);   TEST(x <= z);
    TRY((x = {-5, 3}));  z = -1;                TEST(x != z);  TEST(x < z);   TEST(x <= z);
    TRY((x = {-5, 3}));  z = -2;                TEST(x != z);  TEST(x > z);   TEST(x >= z);

}
