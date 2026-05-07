#include "rs-core/arithmetic.hpp"
#include "rs-core/unit-test.hpp"
#include <numbers>

using namespace RS;
using namespace RS::Literals;

void test_rs_core_arithmetic_binomial_coefficient() {

    TEST_EQUAL(binomial(0, -1),   0);
    TEST_EQUAL(binomial(0, 0),    1);
    TEST_EQUAL(binomial(0, 1),    0);
    TEST_EQUAL(binomial(1, -1),   0);
    TEST_EQUAL(binomial(1, 0),    1);
    TEST_EQUAL(binomial(1, 1),    1);
    TEST_EQUAL(binomial(1, 2),    0);
    TEST_EQUAL(binomial(2, -1),   0);
    TEST_EQUAL(binomial(2, 0),    1);
    TEST_EQUAL(binomial(2, 1),    2);
    TEST_EQUAL(binomial(2, 2),    1);
    TEST_EQUAL(binomial(2, 3),    0);
    TEST_EQUAL(binomial(3, -1),   0);
    TEST_EQUAL(binomial(3, 0),    1);
    TEST_EQUAL(binomial(3, 1),    3);
    TEST_EQUAL(binomial(3, 2),    3);
    TEST_EQUAL(binomial(3, 3),    1);
    TEST_EQUAL(binomial(3, 4),    0);
    TEST_EQUAL(binomial(4, -1),   0);
    TEST_EQUAL(binomial(4, 0),    1);
    TEST_EQUAL(binomial(4, 1),    4);
    TEST_EQUAL(binomial(4, 2),    6);
    TEST_EQUAL(binomial(4, 3),    4);
    TEST_EQUAL(binomial(4, 4),    1);
    TEST_EQUAL(binomial(4, 5),    0);
    TEST_EQUAL(binomial(5, -1),   0);
    TEST_EQUAL(binomial(5, 0),    1);
    TEST_EQUAL(binomial(5, 1),    5);
    TEST_EQUAL(binomial(5, 2),    10);
    TEST_EQUAL(binomial(5, 3),    10);
    TEST_EQUAL(binomial(5, 4),    5);
    TEST_EQUAL(binomial(5, 5),    1);
    TEST_EQUAL(binomial(5, 6),    0);
    TEST_EQUAL(binomial(20, 0),   1);
    TEST_EQUAL(binomial(20, 1),   20);
    TEST_EQUAL(binomial(20, 2),   190);
    TEST_EQUAL(binomial(20, 3),   1'140);
    TEST_EQUAL(binomial(20, 4),   4'845);
    TEST_EQUAL(binomial(20, 5),   15'504);
    TEST_EQUAL(binomial(20, 6),   38'760);
    TEST_EQUAL(binomial(20, 7),   77'520);
    TEST_EQUAL(binomial(20, 8),   125'970);
    TEST_EQUAL(binomial(20, 9),   167'960);
    TEST_EQUAL(binomial(20, 10),  184'756);
    TEST_EQUAL(binomial(20, 11),  167'960);
    TEST_EQUAL(binomial(20, 12),  125'970);
    TEST_EQUAL(binomial(20, 13),  77'520);
    TEST_EQUAL(binomial(20, 14),  38'760);
    TEST_EQUAL(binomial(20, 15),  15'504);
    TEST_EQUAL(binomial(20, 16),  4'845);
    TEST_EQUAL(binomial(20, 17),  1'140);
    TEST_EQUAL(binomial(20, 18),  190);
    TEST_EQUAL(binomial(20, 19),  20);
    TEST_EQUAL(binomial(20, 20),  1);
    TEST_EQUAL(binomial(97, 0),   1);
    TEST_EQUAL(binomial(97, 1),   97);
    TEST_EQUAL(binomial(97, 2),   4'656);
    TEST_EQUAL(binomial(97, 3),   147'440);
    TEST_EQUAL(binomial(97, 4),   3'464'840);
    TEST_EQUAL(binomial(97, 5),   64'446'024);
    TEST_EQUAL(binomial(97, 6),   988'172'368);
    TEST_NEAR(binomial(97, 7),    1.284'624'078e10, 1e1);
    TEST_NEAR(binomial(97, 8),    1.445'202'088e11, 1e2);
    TEST_NEAR(binomial(97, 9),    1.429'144'287e12, 1e3);
    TEST_NEAR(binomial(97, 10),   1.257'646'973e13, 1e4);
    TEST_NEAR(binomial(97, 11),   9.946'844'239e13, 1e4);
    TEST_NEAR(binomial(97, 12),   7.128'571'705e14, 1e5);
    TEST_NEAR(binomial(97, 13),   4.660'989'192e15, 1e6);
    TEST_NEAR(binomial(97, 14),   2.796'593'515e16, 1e7);
    TEST_NEAR(binomial(97, 15),   1.547'448'412e17, 1e8);
    TEST_NEAR(binomial(97, 16),   7.930'673'109e17, 1e8);
    TEST_NEAR(binomial(97, 17),   3.778'732'482e18, 1e9);
    TEST_NEAR(binomial(97, 18),   1.679'436'658e19, 1e10);
    TEST_NEAR(binomial(97, 19),   6.982'920'843e19, 1e10);
    TEST_NEAR(binomial(97, 20),   2.723'339'129e20, 1e11);

}

void test_rs_core_arithmetic_int_power() {

    int x{};
    int y{};
    int z{};

    x = 3;  y = 0;   TRY(z = int_power(x, y));  TEST_EQUAL(z, 1);
    x = 3;  y = 1;   TRY(z = int_power(x, y));  TEST_EQUAL(z, 3);
    x = 3;  y = 2;   TRY(z = int_power(x, y));  TEST_EQUAL(z, 9);
    x = 3;  y = 3;   TRY(z = int_power(x, y));  TEST_EQUAL(z, 27);
    x = 3;  y = 4;   TRY(z = int_power(x, y));  TEST_EQUAL(z, 81);
    x = 3;  y = 5;   TRY(z = int_power(x, y));  TEST_EQUAL(z, 243);
    x = 3;  y = 6;   TRY(z = int_power(x, y));  TEST_EQUAL(z, 729);
    x = 3;  y = 7;   TRY(z = int_power(x, y));  TEST_EQUAL(z, 2'187);
    x = 3;  y = 8;   TRY(z = int_power(x, y));  TEST_EQUAL(z, 6'561);
    x = 3;  y = 9;   TRY(z = int_power(x, y));  TEST_EQUAL(z, 19'683);
    x = 3;  y = 10;  TRY(z = int_power(x, y));  TEST_EQUAL(z, 59'049);
    x = 3;  y = 11;  TRY(z = int_power(x, y));  TEST_EQUAL(z, 177'147);
    x = 3;  y = 12;  TRY(z = int_power(x, y));  TEST_EQUAL(z, 531'441);
    x = 3;  y = 13;  TRY(z = int_power(x, y));  TEST_EQUAL(z, 1'594'323);
    x = 3;  y = 14;  TRY(z = int_power(x, y));  TEST_EQUAL(z, 4'782'969);
    x = 3;  y = 15;  TRY(z = int_power(x, y));  TEST_EQUAL(z, 14'348'907);
    x = 3;  y = 16;  TRY(z = int_power(x, y));  TEST_EQUAL(z, 43'046'721);
    x = 3;  y = 17;  TRY(z = int_power(x, y));  TEST_EQUAL(z, 129'140'163);
    x = 3;  y = 18;  TRY(z = int_power(x, y));  TEST_EQUAL(z, 387'420'489);

}

void test_rs_core_arithmetic_bitmask_functions() {

    enum class MyBitmask: int {
        none     = 0,
        alpha    = 1,
        bravo    = 2,
        charlie  = 4,
        all      = 7,
    };

    int n;

    n = 0;  TEST(! has_bit(n, 0));  TEST(! has_bits(n, 0));
    n = 0;  TEST(! has_bit(n, 1));  TEST(! has_bits(n, 1));
    n = 6;  TEST(! has_bit(n, 1));  TEST(! has_bits(n, 1));
    n = 6;  TEST(has_bit(n, 2));    TEST(has_bits(n, 2));
    n = 6;  TEST(has_bit(n, 4));    TEST(has_bits(n, 4));
    n = 6;  TEST(has_bit(n, 7));    TEST(! has_bits(n, 7));

    unsigned u;

    u = 0;  TEST(! has_bit(u, 0));  TEST(! has_bits(u, 0));
    u = 0;  TEST(! has_bit(u, 1));  TEST(! has_bits(u, 1));
    u = 6;  TEST(! has_bit(u, 1));  TEST(! has_bits(u, 1));
    u = 6;  TEST(has_bit(u, 2));    TEST(has_bits(u, 2));
    u = 6;  TEST(has_bit(u, 4));    TEST(has_bits(u, 4));
    u = 6;  TEST(has_bit(u, 7));    TEST(! has_bits(u, 7));

    MyBitmask b;

    b = MyBitmask::none;   TEST(! has_bit(b, 0));  TEST(! has_bits(b, 0));
    b = MyBitmask::none;   TEST(! has_bit(b, 1));  TEST(! has_bits(b, 1));
    b = MyBitmask::bravo;  TEST(! has_bit(b, 1));  TEST(! has_bits(b, 1));
    b = MyBitmask::bravo;  TEST(has_bit(b, 2));    TEST(has_bits(b, 2));
    b = MyBitmask::bravo;  TEST(! has_bit(b, 4));  TEST(! has_bits(b, 4));
    b = MyBitmask::bravo;  TEST(has_bit(b, 7));    TEST(! has_bits(b, 7));

    b = MyBitmask::none;   TEST(! has_bit(b, MyBitmask::none));     TEST(! has_bits(b, MyBitmask::none));
    b = MyBitmask::none;   TEST(! has_bit(b, MyBitmask::alpha));    TEST(! has_bits(b, MyBitmask::alpha));
    b = MyBitmask::bravo;  TEST(! has_bit(b, MyBitmask::alpha));    TEST(! has_bits(b, MyBitmask::alpha));
    b = MyBitmask::bravo;  TEST(has_bit(b, MyBitmask::bravo));      TEST(has_bits(b, MyBitmask::bravo));
    b = MyBitmask::bravo;  TEST(! has_bit(b, MyBitmask::charlie));  TEST(! has_bits(b, MyBitmask::charlie));
    b = MyBitmask::bravo;  TEST(has_bit(b, MyBitmask::all));        TEST(! has_bits(b, MyBitmask::all));

}

void test_rs_core_arithmetic_angle_conversions() {

    using std::numbers::pi;

    TEST_NEAR(degrees(0.0),     0,       1e-10);
    TEST_NEAR(degrees(pi / 2),  90,      1e-10);
    TEST_NEAR(degrees(pi),      180,     1e-10);
    TEST_NEAR(degrees(2 * pi),  360,     1e-10);
    TEST_NEAR(radians(0.0),     0,       1e-10);
    TEST_NEAR(radians(90.0),    pi / 2,  1e-10);
    TEST_NEAR(radians(180.0),   pi,      1e-10);
    TEST_NEAR(radians(360.0),   2 * pi,  1e-10);
    TEST_NEAR(0_deg,            0,       1e-10);
    TEST_NEAR(90_deg,           pi / 2,  1e-10);
    TEST_NEAR(180_deg,          pi,      1e-10);
    TEST_NEAR(360_deg,          2 * pi,  1e-10);
    TEST_NEAR(0.0_deg,          0,       1e-10);
    TEST_NEAR(90.0_deg,         pi / 2,  1e-10);
    TEST_NEAR(180.0_deg,        pi,      1e-10);
    TEST_NEAR(360.0_deg,        2 * pi,  1e-10);

}

void test_rs_core_arithmetic_geometry_functions() {

    double r, s, v;

    TRY(s = sphere_area_from_radius<1>(10.0));   TEST_NEAR(s, 2.0,               1e-6);
    TRY(s = sphere_area_from_radius<2>(10.0));   TEST_NEAR(s, 62.83185,          1e-5);
    TRY(s = sphere_area_from_radius(10.0));      TEST_NEAR(s, 1'256.6371,        1e-4);
    TRY(s = sphere_area_from_radius<4>(10.0));   TEST_NEAR(s, 19'739.209,        1e-3);
    TRY(s = sphere_area_from_radius<5>(10.0));   TEST_NEAR(s, 263'189.45,        1e-2);
    TRY(s = sphere_area_from_radius<6>(10.0));   TEST_NEAR(s, 3'100'627.7,       1e-1);
    TRY(s = sphere_area_from_radius<7>(10.0));   TEST_NEAR(s, 33'073'362.0,      1);
    TRY(s = sphere_area_from_radius<8>(10.0));   TEST_NEAR(s, 324'696'970.0,     1e1);
    TRY(s = sphere_area_from_radius<9>(10.0));   TEST_NEAR(s, 2'968'658'000.0,   1e2);
    TRY(s = sphere_area_from_radius<10>(10.0));  TEST_NEAR(s, 25'501'640'000.0,  1e3);

    TRY(v = sphere_volume_from_radius<1>(10.0));   TEST_NEAR(v, 20.0,              1e-5);
    TRY(v = sphere_volume_from_radius<2>(10.0));   TEST_NEAR(v, 314.1593,          1e-4);
    TRY(v = sphere_volume_from_radius(10.0));      TEST_NEAR(v, 4'188.790,         1e-3);
    TRY(v = sphere_volume_from_radius<4>(10.0));   TEST_NEAR(v, 49'348.02,         1e-2);
    TRY(v = sphere_volume_from_radius<5>(10.0));   TEST_NEAR(v, 526'378.9,         1e-1);
    TRY(v = sphere_volume_from_radius<6>(10.0));   TEST_NEAR(v, 5'167'713.0,       1);
    TRY(v = sphere_volume_from_radius<7>(10.0));   TEST_NEAR(v, 47'247'660.0,      1e1);
    TRY(v = sphere_volume_from_radius<8>(10.0));   TEST_NEAR(v, 405'871'200.0,     1e2);
    TRY(v = sphere_volume_from_radius<9>(10.0));   TEST_NEAR(v, 3'298'509'000.0,   1e3);
    TRY(v = sphere_volume_from_radius<10>(10.0));  TEST_NEAR(v, 25'501'640'000.0,  1e4);

    TRY(r = sphere_radius_from_area<2>(62.83185));           TEST_NEAR(r, 10.0, 1e-5);
    TRY(r = sphere_radius_from_area(1'256.6371));            TEST_NEAR(r, 10.0, 1e-5);
    TRY(r = sphere_radius_from_area<4>(19'739.209));         TEST_NEAR(r, 10.0, 1e-5);
    TRY(r = sphere_radius_from_area<5>(263'189.45));         TEST_NEAR(r, 10.0, 1e-5);
    TRY(r = sphere_radius_from_area<6>(3'100'627.7));        TEST_NEAR(r, 10.0, 1e-5);
    TRY(r = sphere_radius_from_area<7>(33'073'362.0));       TEST_NEAR(r, 10.0, 1e-5);
    TRY(r = sphere_radius_from_area<8>(324'696'970.0));      TEST_NEAR(r, 10.0, 1e-5);
    TRY(r = sphere_radius_from_area<9>(2'968'658'000.0));    TEST_NEAR(r, 10.0, 1e-5);
    TRY(r = sphere_radius_from_area<10>(25'501'640'000.0));  TEST_NEAR(r, 10.0, 1e-5);

    TRY(r = sphere_radius_from_volume<1>(20.0));               TEST_NEAR(r, 10.0, 1e-5);
    TRY(r = sphere_radius_from_volume<2>(314.1593));           TEST_NEAR(r, 10.0, 1e-5);
    TRY(r = sphere_radius_from_volume(4'188.790));             TEST_NEAR(r, 10.0, 1e-5);
    TRY(r = sphere_radius_from_volume<4>(49'348.02));          TEST_NEAR(r, 10.0, 1e-5);
    TRY(r = sphere_radius_from_volume<5>(526'378.9));          TEST_NEAR(r, 10.0, 1e-5);
    TRY(r = sphere_radius_from_volume<6>(5'167'713.0));        TEST_NEAR(r, 10.0, 1e-5);
    TRY(r = sphere_radius_from_volume<7>(47'247'660.0));       TEST_NEAR(r, 10.0, 1e-5);
    TRY(r = sphere_radius_from_volume<8>(405'871'200.0));      TEST_NEAR(r, 10.0, 1e-5);
    TRY(r = sphere_radius_from_volume<9>(3'298'509'000.0));    TEST_NEAR(r, 10.0, 1e-5);
    TRY(r = sphere_radius_from_volume<10>(25'501'640'000.0));  TEST_NEAR(r, 10.0, 1e-5);

}
