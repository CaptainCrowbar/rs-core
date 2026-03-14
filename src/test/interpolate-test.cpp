#include "rs-core/interpolate.hpp"
#include "rs-core/unit-test.hpp"
#include <utility>
#include <vector>

using namespace RS;

void test_rs_core_interpolate_linear_interval() {

    TEST_EQUAL(interpolate(10.0, 50.0, 30.0, 10.0, 0.0),   70.0);
    TEST_EQUAL(interpolate(10.0, 50.0, 30.0, 10.0, 5.0),   60.0);
    TEST_EQUAL(interpolate(10.0, 50.0, 30.0, 10.0, 10.0),  50.0);
    TEST_EQUAL(interpolate(10.0, 50.0, 30.0, 10.0, 15.0),  40.0);
    TEST_EQUAL(interpolate(10.0, 50.0, 30.0, 10.0, 20.0),  30.0);
    TEST_EQUAL(interpolate(10.0, 50.0, 30.0, 10.0, 25.0),  20.0);
    TEST_EQUAL(interpolate(10.0, 50.0, 30.0, 10.0, 30.0),  10.0);
    TEST_EQUAL(interpolate(10.0, 50.0, 30.0, 10.0, 35.0),  0.0);
    TEST_EQUAL(interpolate(10.0, 50.0, 30.0, 10.0, 40.0),  -10.0);

    TEST_NEAR(interpolate<Lerp::log_x>(20.0, 50.0, 320.0, 10.0, 5.0),     70.0, 1e-10);
    TEST_NEAR(interpolate<Lerp::log_x>(20.0, 50.0, 320.0, 10.0, 10.0),    60.0, 1e-10);
    TEST_NEAR(interpolate<Lerp::log_x>(20.0, 50.0, 320.0, 10.0, 20.0),    50.0, 1e-10);
    TEST_NEAR(interpolate<Lerp::log_x>(20.0, 50.0, 320.0, 10.0, 40.0),    40.0, 1e-10);
    TEST_NEAR(interpolate<Lerp::log_x>(20.0, 50.0, 320.0, 10.0, 80.0),    30.0, 1e-10);
    TEST_NEAR(interpolate<Lerp::log_x>(20.0, 50.0, 320.0, 10.0, 160.0),   20.0, 1e-10);
    TEST_NEAR(interpolate<Lerp::log_x>(20.0, 50.0, 320.0, 10.0, 320.0),   10.0, 1e-10);
    TEST_NEAR(interpolate<Lerp::log_x>(20.0, 50.0, 320.0, 10.0, 640.0),   0.0, 1e-10);
    TEST_NEAR(interpolate<Lerp::log_x>(20.0, 50.0, 320.0, 10.0, 1280.0),  -10.0, 1e-10);

    TEST_NEAR(interpolate<Lerp::log_y>(10.0, 320.0, 30.0, 20.0, 0.0),   1280.0, 1e-10);
    TEST_NEAR(interpolate<Lerp::log_y>(10.0, 320.0, 30.0, 20.0, 5.0),   640.0, 1e-10);
    TEST_NEAR(interpolate<Lerp::log_y>(10.0, 320.0, 30.0, 20.0, 10.0),  320.0, 1e-10);
    TEST_NEAR(interpolate<Lerp::log_y>(10.0, 320.0, 30.0, 20.0, 15.0),  160.0, 1e-10);
    TEST_NEAR(interpolate<Lerp::log_y>(10.0, 320.0, 30.0, 20.0, 20.0),  80.0, 1e-10);
    TEST_NEAR(interpolate<Lerp::log_y>(10.0, 320.0, 30.0, 20.0, 25.0),  40.0, 1e-10);
    TEST_NEAR(interpolate<Lerp::log_y>(10.0, 320.0, 30.0, 20.0, 30.0),  20.0, 1e-10);
    TEST_NEAR(interpolate<Lerp::log_y>(10.0, 320.0, 30.0, 20.0, 35.0),  10.0, 1e-10);
    TEST_NEAR(interpolate<Lerp::log_y>(10.0, 320.0, 30.0, 20.0, 40.0),  5.0, 1e-10);

    TEST_NEAR(interpolate<Lerp::log_xy>(20.0, 320.0, 320.0, 20.0, 5.0),     1280.0, 1e-10);
    TEST_NEAR(interpolate<Lerp::log_xy>(20.0, 320.0, 320.0, 20.0, 10.0),    640.0, 1e-10);
    TEST_NEAR(interpolate<Lerp::log_xy>(20.0, 320.0, 320.0, 20.0, 20.0),    320.0, 1e-10);
    TEST_NEAR(interpolate<Lerp::log_xy>(20.0, 320.0, 320.0, 20.0, 40.0),    160.0, 1e-10);
    TEST_NEAR(interpolate<Lerp::log_xy>(20.0, 320.0, 320.0, 20.0, 80.0),    80.0, 1e-10);
    TEST_NEAR(interpolate<Lerp::log_xy>(20.0, 320.0, 320.0, 20.0, 160.0),   40.0, 1e-10);
    TEST_NEAR(interpolate<Lerp::log_xy>(20.0, 320.0, 320.0, 20.0, 320.0),   20.0, 1e-10);
    TEST_NEAR(interpolate<Lerp::log_xy>(20.0, 320.0, 320.0, 20.0, 640.0),   10.0, 1e-10);
    TEST_NEAR(interpolate<Lerp::log_xy>(20.0, 320.0, 320.0, 20.0, 1280.0),  5.0, 1e-10);

}

void test_rs_core_interpolate_linear_multipoint() {

    LinearMap<double> map;
    double y = 0;

    TRY(map.insert(10, 100));
    TRY(map.insert(20, 150));
    TRY(map.insert(30, 50));
    TRY(map.insert(60, 110));

    TRY(y = map(0));   TEST_EQUAL(y, 50);
    TRY(y = map(5));   TEST_EQUAL(y, 75);
    TRY(y = map(10));  TEST_EQUAL(y, 100);
    TRY(y = map(15));  TEST_EQUAL(y, 125);
    TRY(y = map(20));  TEST_EQUAL(y, 150);
    TRY(y = map(25));  TEST_EQUAL(y, 100);
    TRY(y = map(30));  TEST_EQUAL(y, 50);
    TRY(y = map(35));  TEST_EQUAL(y, 60);
    TRY(y = map(40));  TEST_EQUAL(y, 70);
    TRY(y = map(45));  TEST_EQUAL(y, 80);
    TRY(y = map(50));  TEST_EQUAL(y, 90);
    TRY(y = map(55));  TEST_EQUAL(y, 100);
    TRY(y = map(60));  TEST_EQUAL(y, 110);
    TRY(y = map(65));  TEST_EQUAL(y, 120);
    TRY(y = map(70));  TEST_EQUAL(y, 130);

    TRY((map = {
        { 100, 1000 },
        { 200, 1500 },
        { 300, 500 },
        { 600, 1100 },
    }));

    TRY(y = map(0));    TEST_EQUAL(y, 500);
    TRY(y = map(50));   TEST_EQUAL(y, 750);
    TRY(y = map(100));  TEST_EQUAL(y, 1000);
    TRY(y = map(150));  TEST_EQUAL(y, 1250);
    TRY(y = map(200));  TEST_EQUAL(y, 1500);
    TRY(y = map(250));  TEST_EQUAL(y, 1000);
    TRY(y = map(300));  TEST_EQUAL(y, 500);
    TRY(y = map(350));  TEST_EQUAL(y, 600);
    TRY(y = map(400));  TEST_EQUAL(y, 700);
    TRY(y = map(450));  TEST_EQUAL(y, 800);
    TRY(y = map(500));  TEST_EQUAL(y, 900);
    TRY(y = map(550));  TEST_EQUAL(y, 1000);
    TRY(y = map(600));  TEST_EQUAL(y, 1100);
    TRY(y = map(650));  TEST_EQUAL(y, 1200);
    TRY(y = map(700));  TEST_EQUAL(y, 1300);

}

void test_rs_core_interpolate_logarithmic_multipoint() {

    LinearMap<double, double, Lerp::log_xy> map1;
    double y = 0;

    TRY(map1.insert(4, 1e20));
    TRY(map1.insert(16, 1e30));
    TRY(map1.insert(64, 1e10));
    TRY(map1.insert(4096, 1e22));

    TRY(y = map1(1));      TEST_NEAR(y, 1e10, 1);
    TRY(y = map1(2));      TEST_NEAR(y, 1e15, 1e5);
    TRY(y = map1(4));      TEST_NEAR(y, 1e20, 1e10);
    TRY(y = map1(8));      TEST_NEAR(y, 1e25, 1e15);
    TRY(y = map1(16));     TEST_NEAR(y, 1e30, 1e20);
    TRY(y = map1(32));     TEST_NEAR(y, 1e20, 1e10);
    TRY(y = map1(64));     TEST_NEAR(y, 1e10, 1);
    TRY(y = map1(128));    TEST_NEAR(y, 1e12, 1e2);
    TRY(y = map1(256));    TEST_NEAR(y, 1e14, 1e4);
    TRY(y = map1(512));    TEST_NEAR(y, 1e16, 1e6);
    TRY(y = map1(1024));   TEST_NEAR(y, 1e18, 1e8);
    TRY(y = map1(2048));   TEST_NEAR(y, 1e20, 1e10);
    TRY(y = map1(4096));   TEST_NEAR(y, 1e22, 1e12);
    TRY(y = map1(8192));   TEST_NEAR(y, 1e24, 1e14);
    TRY(y = map1(16384));  TEST_NEAR(y, 1e26, 1e16);

    LinearMap<double, double, Lerp::log_y> map2 {
        { 10, 1e20 },
        { 20, 1e30 },
        { 30, 1e10 },
        { 60, 1e22 },
    };

    TRY(y = map2(0));   TEST_NEAR(y, 1e10, 1);
    TRY(y = map2(5));   TEST_NEAR(y, 1e15, 1e5);
    TRY(y = map2(10));  TEST_NEAR(y, 1e20, 1e10);
    TRY(y = map2(15));  TEST_NEAR(y, 1e25, 1e15);
    TRY(y = map2(20));  TEST_NEAR(y, 1e30, 1e20);
    TRY(y = map2(25));  TEST_NEAR(y, 1e20, 1e10);
    TRY(y = map2(30));  TEST_NEAR(y, 1e10, 1);
    TRY(y = map2(35));  TEST_NEAR(y, 1e12, 1e2);
    TRY(y = map2(40));  TEST_NEAR(y, 1e14, 1e4);
    TRY(y = map2(45));  TEST_NEAR(y, 1e16, 1e6);
    TRY(y = map2(50));  TEST_NEAR(y, 1e18, 1e8);
    TRY(y = map2(55));  TEST_NEAR(y, 1e20, 1e10);
    TRY(y = map2(60));  TEST_NEAR(y, 1e22, 1e12);
    TRY(y = map2(65));  TEST_NEAR(y, 1e24, 1e14);
    TRY(y = map2(70));  TEST_NEAR(y, 1e26, 1e16);

}

void test_rs_core_interpolate_lagrange_polynomial() {

    LagrangePolynomial<double> map1;
    double y = 0;

    TRY((map1 = LagrangePolynomial<double>{
        { 12, 5 },
        { 34, 25 },
        { 60, 8 },
        { 98, 28 },
    }));

    TRY(y = map1(1));    TEST_NEAR(y, -29.521, 0.001);
    TRY(y = map1(12));   TEST_NEAR(y, 5.000, 0.001);
    TRY(y = map1(23));   TEST_NEAR(y, 21.595, 0.001);
    TRY(y = map1(34));   TEST_NEAR(y, 25.000, 0.001);
    TRY(y = map1(47));   TEST_NEAR(y, 18.495, 0.001);
    TRY(y = map1(60));   TEST_NEAR(y, 8.000, 0.001);
    TRY(y = map1(79));   TEST_NEAR(y, 1.709, 0.001);
    TRY(y = map1(98));   TEST_NEAR(y, 28.000, 0.001);
    TRY(y = map1(117));  TEST_NEAR(y, 111.278, 0.001);

    std::vector<std::pair<double, double>> points = {
        { 12, 5 },
        { 34, 25 },
        { 60, 8 },
        { 98, 28 },
        { 102, 28 },
        { 140, 8 },
        { 166, 25 },
        { 188, 5 },
    };

    TRY(map1 = LagrangePolynomial<double>(points));

    TRY(y = map1(1));    TEST_NEAR(y, -103.458, 0.001);
    TRY(y = map1(12));   TEST_NEAR(y, 5.000, 0.001);
    TRY(y = map1(23));   TEST_NEAR(y, 31.322, 0.001);
    TRY(y = map1(34));   TEST_NEAR(y, 25.000, 0.001);
    TRY(y = map1(47));   TEST_NEAR(y, 11.665, 0.001);
    TRY(y = map1(60));   TEST_NEAR(y, 8.000, 0.001);
    TRY(y = map1(79));   TEST_NEAR(y, 18.743, 0.001);
    TRY(y = map1(98));   TEST_NEAR(y, 28.000, 0.001);
    TRY(y = map1(100));  TEST_NEAR(y, 28.100, 0.001);
    TRY(y = map1(102));  TEST_NEAR(y, 28.000, 0.001);
    TRY(y = map1(121));  TEST_NEAR(y, 18.743, 0.001);
    TRY(y = map1(140));  TEST_NEAR(y, 8.000, 0.001);
    TRY(y = map1(153));  TEST_NEAR(y, 11.665, 0.001);
    TRY(y = map1(166));  TEST_NEAR(y, 25.000, 0.001);
    TRY(y = map1(177));  TEST_NEAR(y, 31.322, 0.001);
    TRY(y = map1(188));  TEST_NEAR(y, 5.000, 0.001);
    TRY(y = map1(199));  TEST_NEAR(y, -103.458, 0.001);

    points = {
        { 1.3183, 1.1220 },
        { 2.1878, 1.7783 },
        { 3.9811, 1.2023 },
        { 9.5499, 1.9055 },
        { 10.471, 1.9055 },
        { 25.119, 1.2023 },
        { 45.709, 1.7783 },
        { 75.858, 1.1220 },
    };

    LagrangePolynomial<double, Lerp::log_xy> map2{points};

    TRY(y = map2(1.0233));  TEST_NEAR(y, 0.0923, 1e-4);
    TRY(y = map2(1.3183));  TEST_NEAR(y, 1.1220, 1e-4);
    TRY(y = map2(1.6982));  TEST_NEAR(y, 2.0569, 1e-4);
    TRY(y = map2(2.1878));  TEST_NEAR(y, 1.7783, 1e-4);
    TRY(y = map2(2.9512));  TEST_NEAR(y, 1.3081, 1e-4);
    TRY(y = map2(3.9811));  TEST_NEAR(y, 1.2023, 1e-4);
    TRY(y = map2(6.1660));  TEST_NEAR(y, 1.5397, 1e-4);
    TRY(y = map2(9.5499));  TEST_NEAR(y, 1.9055, 1e-4);
    TRY(y = map2(10.000));  TEST_NEAR(y, 1.9099, 1e-4);
    TRY(y = map2(10.471));  TEST_NEAR(y, 1.9055, 1e-4);
    TRY(y = map2(16.218));  TEST_NEAR(y, 1.5397, 1e-4);
    TRY(y = map2(25.119));  TEST_NEAR(y, 1.2023, 1e-4);
    TRY(y = map2(33.884));  TEST_NEAR(y, 1.3081, 1e-4);
    TRY(y = map2(45.709));  TEST_NEAR(y, 1.7783, 1e-4);
    TRY(y = map2(58.884));  TEST_NEAR(y, 2.0569, 1e-4);
    TRY(y = map2(75.858));  TEST_NEAR(y, 1.1220, 1e-4);
    TRY(y = map2(97.724));  TEST_NEAR(y, 0.0923, 1e-4);

    points = {
        { 12, 1.1220 },
        { 34, 1.7783 },
        { 60, 1.2023 },
        { 98, 1.9055 },
        { 102, 1.9055 },
        { 140, 1.2023 },
        { 166, 1.7783 },
        { 188, 1.1220 },
    };

    LagrangePolynomial<double, Lerp::log_y> map3{points};

    TRY(y = map3(1));    TEST_NEAR(y, 0.0923, 1e-4);
    TRY(y = map3(12));   TEST_NEAR(y, 1.1220, 1e-4);
    TRY(y = map3(23));   TEST_NEAR(y, 2.0569, 1e-4);
    TRY(y = map3(34));   TEST_NEAR(y, 1.7783, 1e-4);
    TRY(y = map3(47));   TEST_NEAR(y, 1.3081, 1e-4);
    TRY(y = map3(60));   TEST_NEAR(y, 1.2023, 1e-4);
    TRY(y = map3(79));   TEST_NEAR(y, 1.5397, 1e-4);
    TRY(y = map3(98));   TEST_NEAR(y, 1.9055, 1e-4);
    TRY(y = map3(100));  TEST_NEAR(y, 1.9099, 1e-4);
    TRY(y = map3(102));  TEST_NEAR(y, 1.9055, 1e-4);
    TRY(y = map3(121));  TEST_NEAR(y, 1.5397, 1e-4);
    TRY(y = map3(140));  TEST_NEAR(y, 1.2023, 1e-4);
    TRY(y = map3(153));  TEST_NEAR(y, 1.3081, 1e-4);
    TRY(y = map3(166));  TEST_NEAR(y, 1.7783, 1e-4);
    TRY(y = map3(177));  TEST_NEAR(y, 2.0569, 1e-4);
    TRY(y = map3(188));  TEST_NEAR(y, 1.1220, 1e-4);
    TRY(y = map3(199));  TEST_NEAR(y, 0.0923, 1e-4);

}

void test_rs_core_interpolate_cubic_spline() {

    CubicSpline<double> cs;
    std::vector<std::pair<double, double>> points;
    double y = 0;

    points = {
        { 12, 5 },
        { 34, 25 },
        { 60, 8 },
        { 98, 28 },
    };

    TRY(cs = CubicSpline<double>(points));

    TRY(y = cs(1));    TEST_NEAR(y, -8.6066, 1e-4);
    TRY(y = cs(12));   TEST_NEAR(y, 5.0000, 1e-4);
    TRY(y = cs(23));   TEST_NEAR(y, 18.6066, 1e-4);
    TRY(y = cs(34));   TEST_NEAR(y, 25.0000, 1e-4);
    TRY(y = cs(47));   TEST_NEAR(y, 18.1768, 1e-4);
    TRY(y = cs(60));   TEST_NEAR(y, 8.0000, 1e-4);
    TRY(y = cs(79));   TEST_NEAR(y, 10.8217, 1e-4);
    TRY(y = cs(98));   TEST_NEAR(y, 28.0000, 1e-4);
    TRY(y = cs(117));  TEST_NEAR(y, 45.1783, 1e-4);

    points = {
        { 12, 5 },
        { 34, 25 },
        { 60, 8 },
        { 98, 28 },
        { 102, 28 },
        { 140, 8 },
        { 166, 25 },
        { 188, 5 },
    };

    TRY(cs = CubicSpline<double>(points));

    TRY(y = cs(1));    TEST_NEAR(y, -8.8157, 1e-4);
    TRY(y = cs(12));   TEST_NEAR(y, 5.0000, 1e-4);
    TRY(y = cs(23));   TEST_NEAR(y, 18.8157, 1e-4);
    TRY(y = cs(34));   TEST_NEAR(y, 25.0000, 1e-4);
    TRY(y = cs(47));   TEST_NEAR(y, 17.3904, 1e-4);
    TRY(y = cs(60));   TEST_NEAR(y, 8.0000, 1e-4);
    TRY(y = cs(79));   TEST_NEAR(y, 15.8511, 1e-4);
    TRY(y = cs(98));   TEST_NEAR(y, 28.0000, 1e-4);
    TRY(y = cs(100));  TEST_NEAR(y, 28.1625, 1e-4);
    TRY(y = cs(102));  TEST_NEAR(y, 28.0000, 1e-4);
    TRY(y = cs(121));  TEST_NEAR(y, 15.8511, 1e-4);
    TRY(y = cs(140));  TEST_NEAR(y, 8.0000, 1e-4);
    TRY(y = cs(153));  TEST_NEAR(y, 17.3904, 1e-4);
    TRY(y = cs(166));  TEST_NEAR(y, 25.0000, 1e-4);
    TRY(y = cs(177));  TEST_NEAR(y, 18.8157, 1e-4);
    TRY(y = cs(188));  TEST_NEAR(y, 5.0000, 1e-4);
    TRY(y = cs(199));  TEST_NEAR(y, -8.8157, 1e-4);

}
