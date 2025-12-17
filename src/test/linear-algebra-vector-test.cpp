#include "rs-core/linear-algebra.hpp"
#include "rs-core/unit-test.hpp"
#include <format>
#include <numbers>
#include <set>
#include <tuple>
#include <unordered_set>

using namespace RS;
using std::numbers::pi;

void test_rs_linear_algebra_vector_integer_construction() {

    Int3 v1, v2, v3;
    const Int3& cv1 = v1;
    const Int3& cv2 = v2;
    const Int3& cv3 = v3;

    TEST_EQUAL(sizeof(Int3), 3 * sizeof(int));

    TRY(v1 = Int3{1});
    TRY(v2 = Int3{0});
    TEST(! v1.is_null());
    TEST(v2.is_null());

    TEST_EQUAL(std::format("{}", v1), "[1,1,1]");
    TEST_EQUAL(std::format("{}", cv1), "[1,1,1]");

    TEST_EQUAL(v1[0], 1);  TEST_EQUAL(cv1[0], 1);
    TEST_EQUAL(v1[1], 1);  TEST_EQUAL(cv1[1], 1);
    TEST_EQUAL(v1[2], 1);  TEST_EQUAL(cv1[2], 1);

    TRY(v2[0] = 99);
    TRY(v2[1] = 98);
    TRY(v2[2] = 97);
    TEST_EQUAL(std::format("{}", v2), "[99,98,97]");
    TEST_EQUAL(std::format("{}", cv2), "[99,98,97]");

    TEST_EQUAL(v2[0], 99);   TEST_EQUAL(cv2[0], 99);
    TEST_EQUAL(v2[1], 98);   TEST_EQUAL(cv2[1], 98);
    TEST_EQUAL(v2[2], 97);   TEST_EQUAL(cv2[2], 97);
    TEST_EQUAL(v2.x(), 99);  TEST_EQUAL(cv2.x(), 99);
    TEST_EQUAL(v2.y(), 98);  TEST_EQUAL(cv2.y(), 98);
    TEST_EQUAL(v2.z(), 97);  TEST_EQUAL(cv2.z(), 97);

    TRY((v3 = Int3{1,2,3}));
    TEST_EQUAL(std::format("{}", v3), "[1,2,3]");
    TEST_EQUAL(std::format("{}", cv3), "[1,2,3]");

    TRY((v3 = Int3{2,4,6}));
    TEST_EQUAL(std::format("{}", v3), "[2,4,6]");
    TEST_EQUAL(std::format("{}", cv3), "[2,4,6]");

    TRY((v3 = {10,20,30}));
    TEST_EQUAL(std::format("{}", v3), "[10,20,30]");
    TEST_EQUAL(std::format("{}", cv3), "[10,20,30]");

    TEST_EQUAL(v3[0], 10);          TEST_EQUAL(cv3[0], 10);
    TEST_EQUAL(v3[1], 20);          TEST_EQUAL(cv3[1], 20);
    TEST_EQUAL(v3[2], 30);          TEST_EQUAL(cv3[2], 30);
    TEST_EQUAL(v3.begin()[0], 10);  TEST_EQUAL(cv3.begin()[0], 10);
    TEST_EQUAL(v3.begin()[1], 20);  TEST_EQUAL(cv3.begin()[1], 20);
    TEST_EQUAL(v3.begin()[2], 30);  TEST_EQUAL(cv3.begin()[2], 30);

}

void test_rs_linear_algebra_vector_integer_arithmetic() {

    int x = 0;
    Int3 v1, v2, v3, v4;

    TRY((v1 = {2,3,5}));
    TRY((v2 = {7,11,13}));
    TRY(v3 = Int3{0});
    TRY(v4 = Int3{0});
    TEST(v1 == v1);
    TEST(v1 != v2);
    TEST(v3 == v4);

    TRY(v3 = + v1);     TEST_EQUAL(std::format("{}", v3), "[2,3,5]");
    TRY(v3 = - v1);     TEST_EQUAL(std::format("{}", v3), "[-2,-3,-5]");
    TRY(v3 = v1 + v2);  TEST_EQUAL(std::format("{}", v3), "[9,14,18]");
    TRY(v3 = v1 - v2);  TEST_EQUAL(std::format("{}", v3), "[-5,-8,-8]");
    TRY(v3 = 17 * v1);  TEST_EQUAL(std::format("{}", v3), "[34,51,85]");
    TRY(v3 = v1 * 19);  TEST_EQUAL(std::format("{}", v3), "[38,57,95]");
    TRY(x = v1 % v2);   TEST_EQUAL(x, 112);
    TRY(v3 = v1 ^ v2);  TEST_EQUAL(std::format("{}", v3), "[-16,9,1]");
    TRY(v3 = v1 * v2);  TEST_EQUAL(std::format("{}", v3), "[14,33,65]");
    TRY(v3 = v2 / v1);  TEST_EQUAL(std::format("{}", v3), "[3,3,2]");

    TRY(v3 = Int3::unit(0));  TEST_EQUAL(std::format("{}", v3), "[1,0,0]");
    TRY(v3 = Int3::unit(1));  TEST_EQUAL(std::format("{}", v3), "[0,1,0]");
    TRY(v3 = Int3::unit(2));  TEST_EQUAL(std::format("{}", v3), "[0,0,1]");

    TRY((v1 = {1,5,9}));
    TRY((v2 = {2,3,4}));
    TRY((v3 = {4,6,8}));
    TRY(v1 = clampv(v1, v2, v3));
    TEST_EQUAL(std::format("{}", v1), "[2,5,8]");

    TRY((v1 = {1,3,5}));
    TRY((v2 = {2,3,4}));
    TRY(v3 = minv(v1, v2));
    TEST_EQUAL(std::format("{}", v3), "[1,3,4]");
    TRY(v3 = maxv(v1, v2));
    TEST_EQUAL(std::format("{}", v3), "[2,3,5]");
    TRY(std::tie(v3, v4) = minmaxv(v1, v2));
    TEST_EQUAL(std::format("{}", v3), "[1,3,4]");
    TEST_EQUAL(std::format("{}", v4), "[2,3,5]");

}

void test_rs_linear_algebra_vector_integer_hash() {

    std::unordered_set<Int3> set;
    Int3 v1, v2, v3;

    TRY((v1 = {1,2,3}));
    TRY((v2 = {4,5,6}));
    TRY((v3 = {7,8,9}));
    TRY(set.insert(v1));
    TRY(set.insert(v2));
    TRY(set.insert(v1));
    TEST_EQUAL(set.size(), 2u);
    TEST_EQUAL(set.count(v1), 1u);
    TEST_EQUAL(set.count(v2), 1u);
    TEST_EQUAL(set.count(v3), 0u);

}

void test_rs_linear_algebra_vector_integer_total_order() {

    std::set<Int3> set;
    Int3 v1, v2, v3;

    TRY((v1 = {1,2,3}));
    TRY((v2 = {4,5,6}));
    TRY((v3 = {7,8,9}));
    TRY(set.insert(v1));
    TRY(set.insert(v2));
    TRY(set.insert(v1));
    TEST_EQUAL(set.size(), 2u);
    TEST_EQUAL(set.count(v1), 1u);
    TEST_EQUAL(set.count(v2), 1u);
    TEST_EQUAL(set.count(v3), 0u);
    TEST_EQUAL(std::format("{}", set), "{[1,2,3], [4,5,6]}");

}

void test_rs_linear_algebra_vector_floating_construction() {

    Double3 v1, v2, v3;
    const Double3& cv1(v1);
    const Double3& cv2(v2);
    const Double3& cv3(v3);

    TEST_EQUAL(sizeof(Double3), 3 * sizeof(double));

    TRY(v1 = Double3{1.0});
    TRY(v2 = Double3{0.0});
    TEST(! v1.is_null());
    TEST(v2.is_null());

    TEST_EQUAL(std::format("{:.3f}", v1), "[1.000,1.000,1.000]");
    TEST_EQUAL(std::format("{:.3e}", v1), "[1.000e+00,1.000e+00,1.000e+00]");

    TEST_EQUAL(v1[0], 1);  TEST_EQUAL(cv1[0], 1);
    TEST_EQUAL(v1[1], 1);  TEST_EQUAL(cv1[1], 1);
    TEST_EQUAL(v1[2], 1);  TEST_EQUAL(cv1[2], 1);

    TRY(v2[0] = 99);
    TRY(v2[1] = 98);
    TRY(v2[2] = 97);
    TEST_EQUAL(std::format("{}", v2), "[99,98,97]");
    TEST_EQUAL(std::format("{}", v2), "[99,98,97]");

    TEST_EQUAL(v2[0], 99);   TEST_EQUAL(cv2[0], 99);
    TEST_EQUAL(v2[1], 98);   TEST_EQUAL(cv2[1], 98);
    TEST_EQUAL(v2[2], 97);   TEST_EQUAL(cv2[2], 97);
    TEST_EQUAL(v2.x(), 99);  TEST_EQUAL(cv2.x(), 99);
    TEST_EQUAL(v2.y(), 98);  TEST_EQUAL(cv2.y(), 98);
    TEST_EQUAL(v2.z(), 97);  TEST_EQUAL(cv2.z(), 97);

    TRY((v3 = Double3{1,2,3}));
    TEST_EQUAL(std::format("{}", v3), "[1,2,3]");
    TEST_EQUAL(std::format("{}", v3), "[1,2,3]");

    TRY((v3 = Double3{2,4,6}));
    TEST_EQUAL(std::format("{}", v3), "[2,4,6]");
    TEST_EQUAL(std::format("{}", v3), "[2,4,6]");

    TRY((v3 = {10,20,30}));
    TEST_EQUAL(std::format("{}", v3), "[10,20,30]");
    TEST_EQUAL(std::format("{}", v3), "[10,20,30]");

    TEST_EQUAL(v3[0], 10);          TEST_EQUAL(cv3[0], 10);
    TEST_EQUAL(v3[1], 20);          TEST_EQUAL(cv3[1], 20);
    TEST_EQUAL(v3[2], 30);          TEST_EQUAL(cv3[2], 30);
    TEST_EQUAL(v3.begin()[0], 10);  TEST_EQUAL(cv3.begin()[0], 10);
    TEST_EQUAL(v3.begin()[1], 20);  TEST_EQUAL(cv3.begin()[1], 20);
    TEST_EQUAL(v3.begin()[2], 30);  TEST_EQUAL(cv3.begin()[2], 30);

}

void test_rs_linear_algebra_vector_floating_arithmetic() {

    double x = 0;
    Double3 v1, v2, v3, v4, v5;

    TRY((v1 = {2,3,5}));
    TRY((v2 = {7,11,13}));
    TRY(v3 = Double3{0.0});
    TRY(v4 = Double3{0.0});
    TEST(v1 == v1);
    TEST(v1 != v2);
    TEST(v3 == v4);

    TRY(v3 = + v1);     TEST_EQUAL(std::format("{}", v3), "[2,3,5]");
    TRY(v3 = - v1);     TEST_EQUAL(std::format("{}", v3), "[-2,-3,-5]");
    TRY(v3 = v1 + v2);  TEST_EQUAL(std::format("{}", v3), "[9,14,18]");
    TRY(v3 = v1 - v2);  TEST_EQUAL(std::format("{}", v3), "[-5,-8,-8]");
    TRY(v3 = 17 * v1);  TEST_EQUAL(std::format("{}", v3), "[34,51,85]");
    TRY(v3 = v1 * 19);  TEST_EQUAL(std::format("{}", v3), "[38,57,95]");
    TRY(v3 = v1 / 23);  TEST_EQUAL(std::format("{:.4f}", v3), "[0.0870,0.1304,0.2174]");
    TRY(x = v1 % v2);   TEST_EQUAL(x, 112);
    TRY(v3 = v1 ^ v2);  TEST_EQUAL(std::format("{}", v3), "[-16,9,1]");
    TRY(v3 = v1 * v2);  TEST_EQUAL(std::format("{}", v3), "[14,33,65]");
    TRY(v3 = v1 / v2);  TEST_EQUAL(std::format("{:.4f}", v3), "[0.2857,0.2727,0.3846]");

    TEST_EQUAL(v1.r2(), 38);   TEST_NEAR(v1.r(), 6.164414, 1e-6);
    TEST_EQUAL(v2.r2(), 339);  TEST_NEAR(v2.r(), 18.411953, 1e-6);

    TRY(v3 = Double3::unit(0));  TEST_EQUAL(std::format("{}", v3), "[1,0,0]");
    TRY(v3 = Double3::unit(1));  TEST_EQUAL(std::format("{}", v3), "[0,1,0]");
    TRY(v3 = Double3::unit(2));  TEST_EQUAL(std::format("{}", v3), "[0,0,1]");

    TRY(v3 = Double3::null().dir());  TEST_EQUAL(std::format("{}", v3), "[0,0,0]");
    TRY(v3 = v1.dir());               TEST_EQUAL(std::format("{:.4f}", v3), "[0.3244,0.4867,0.8111]");
    TRY(v3 = v2.dir());               TEST_EQUAL(std::format("{:.4f}", v3), "[0.3802,0.5974,0.7061]");

    TRY((v1 = {1,2,3}));

    TRY((v2 = {0,0,0}));     TRY(x = v1.angle(v2));  TEST_EQUAL(x, 0);
    TRY((v2 = {2,4,6}));     TRY(x = v1.angle(v2));  TEST_EQUAL(x, 0);
    TRY((v2 = {-2,-4,-6}));  TRY(x = v1.angle(v2));  TEST_NEAR(x, pi, 1e-6);
    TRY((v2 = {3,2,1}));     TRY(x = v1.angle(v2));  TEST_NEAR(x, 0.775193, 1e-6);
    TRY((v2 = {-3,-2,-1}));  TRY(x = v1.angle(v2));  TEST_NEAR(x, 2.366399, 1e-6);

    TRY((v1 = {2,3,5}));
    TRY((v2 = {7,11,13}));
    TRY(v3 = v1.project(v2));
    TRY(v4 = v1.reject(v2));
    TEST_EQUAL(std::format("{:.4f}", v3), "[5.8947,8.8421,14.7368]");
    TEST_EQUAL(std::format("{:.4f}", v4), "[1.1053,2.1579,-1.7368]");
    TRY(v5 = v3 + v4);
    TEST_RANGES_NEAR(v5, v2, 1e-10);
    TRY(v5 = v1 ^ v3);
    TEST_RANGES_NEAR(v5, Double3::null(), 1e-10);
    TEST_NEAR(v1 % v4, 0, 1e-6);
    TEST_NEAR(v3 % v4, 0, 1e-6);

    TRY((v1 = {1,5,9}));
    TRY((v2 = {2,3,4}));
    TRY((v3 = {4,6,8}));
    TRY(v1 = clampv(v1, v2, v3));
    TEST_EQUAL(std::format("{}", v1), "[2,5,8]");

    TRY((v1 = {1,3,5}));
    TRY((v2 = {2,3,4}));
    TRY(v3 = minv(v1, v2));
    TEST_EQUAL(std::format("{}", v3), "[1,3,4]");
    TRY(v3 = maxv(v1, v2));
    TEST_EQUAL(std::format("{}", v3), "[2,3,5]");
    TRY(std::tie(v3, v4) = minmaxv(v1, v2));
    TEST_EQUAL(std::format("{}", v3), "[1,3,4]");
    TEST_EQUAL(std::format("{}", v4), "[2,3,5]");

}

void test_rs_linear_algebra_vector_floating_interpolation() {

    Double3 u = {10,20,30};
    Double3 v = {12,34,56};
    Double3 w;

    TRY(w = lerp(u, v, -0.50));  TEST_RANGES_NEAR(w, (Double3{9.0,13.0,17.0}), 0);
    TRY(w = lerp(u, v, -0.25));  TEST_RANGES_NEAR(w, (Double3{9.5,16.5,23.5}), 0);
    TRY(w = lerp(u, v, 0.00));   TEST_RANGES_NEAR(w, (Double3{10.0,20.0,30.0}), 0);
    TRY(w = lerp(u, v, 0.25));   TEST_RANGES_NEAR(w, (Double3{10.5,23.5,36.5}), 0);
    TRY(w = lerp(u, v, 0.50));   TEST_RANGES_NEAR(w, (Double3{11.0,27.0,43.0}), 0);
    TRY(w = lerp(u, v, 0.75));   TEST_RANGES_NEAR(w, (Double3{11.5,30.5,49.5}), 0);
    TRY(w = lerp(u, v, 1.00));   TEST_RANGES_NEAR(w, (Double3{12.0,34.0,56.0}), 0);
    TRY(w = lerp(u, v, 1.25));   TEST_RANGES_NEAR(w, (Double3{12.5,37.5,62.5}), 0);
    TRY(w = lerp(u, v, 1.50));   TEST_RANGES_NEAR(w, (Double3{13.0,41.0,69.0}), 0);

}
