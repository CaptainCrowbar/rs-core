#include "rs-core/arithmetic.hpp"
#include "rs-core/mp-integer.hpp"
#include "rs-core/unit-test.hpp"
#include <cstdint>
#include <numeric>
#include <optional>
#include <tuple>

using namespace RS;
using namespace RS::Literals;

void test_rs_core_arithmetic_euclidean_division() {

    {

        unsigned q{};
        unsigned r{};
        unsigned x{};
        unsigned y{};

        x = 0;   y = 3;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 0u);  TEST_EQUAL(r, 0u);  TEST_EQUAL(q * y + r, x);
        x = 1;   y = 3;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 0u);  TEST_EQUAL(r, 1u);  TEST_EQUAL(q * y + r, x);
        x = 2;   y = 3;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 0u);  TEST_EQUAL(r, 2u);  TEST_EQUAL(q * y + r, x);
        x = 3;   y = 3;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 1u);  TEST_EQUAL(r, 0u);  TEST_EQUAL(q * y + r, x);
        x = 4;   y = 3;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 1u);  TEST_EQUAL(r, 1u);  TEST_EQUAL(q * y + r, x);
        x = 5;   y = 3;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 1u);  TEST_EQUAL(r, 2u);  TEST_EQUAL(q * y + r, x);
        x = 6;   y = 3;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 2u);  TEST_EQUAL(r, 0u);  TEST_EQUAL(q * y + r, x);
        x = 7;   y = 3;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 2u);  TEST_EQUAL(r, 1u);  TEST_EQUAL(q * y + r, x);
        x = 8;   y = 3;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 2u);  TEST_EQUAL(r, 2u);  TEST_EQUAL(q * y + r, x);
        x = 9;   y = 3;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 3u);  TEST_EQUAL(r, 0u);  TEST_EQUAL(q * y + r, x);
        x = 10;  y = 3;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 3u);  TEST_EQUAL(r, 1u);  TEST_EQUAL(q * y + r, x);

    }

    {

        int q{};
        int r{};
        int x{};
        int y{};

        x = -6;  y = 3;   TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, -2);  TEST_EQUAL(r, 0);   TEST_EQUAL(q * y + r, x);
        x = -5;  y = 3;   TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, -2);  TEST_EQUAL(r, 1);   TEST_EQUAL(q * y + r, x);
        x = -4;  y = 3;   TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, -2);  TEST_EQUAL(r, 2);   TEST_EQUAL(q * y + r, x);
        x = -3;  y = 3;   TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, -1);  TEST_EQUAL(r, 0);   TEST_EQUAL(q * y + r, x);
        x = -2;  y = 3;   TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, -1);  TEST_EQUAL(r, 1);   TEST_EQUAL(q * y + r, x);
        x = -1;  y = 3;   TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, -1);  TEST_EQUAL(r, 2);   TEST_EQUAL(q * y + r, x);
        x = 0;   y = 3;   TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 0);   TEST_EQUAL(r, 0);   TEST_EQUAL(q * y + r, x);
        x = 1;   y = 3;   TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 0);   TEST_EQUAL(r, 1);   TEST_EQUAL(q * y + r, x);
        x = 2;   y = 3;   TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 0);   TEST_EQUAL(r, 2);   TEST_EQUAL(q * y + r, x);
        x = 3;   y = 3;   TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 1);   TEST_EQUAL(r, 0);   TEST_EQUAL(q * y + r, x);
        x = 4;   y = 3;   TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 1);   TEST_EQUAL(r, 1);   TEST_EQUAL(q * y + r, x);
        x = 5;   y = 3;   TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 1);   TEST_EQUAL(r, 2);   TEST_EQUAL(q * y + r, x);
        x = 6;   y = 3;   TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 2);   TEST_EQUAL(r, 0);   TEST_EQUAL(q * y + r, x);
        x = -6;  y = -3;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 2);   TEST_EQUAL(r, 0);   TEST_EQUAL(q * y + r, x);
        x = -5;  y = -3;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 2);   TEST_EQUAL(r, 1);   TEST_EQUAL(q * y + r, x);
        x = -4;  y = -3;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 2);   TEST_EQUAL(r, 2);   TEST_EQUAL(q * y + r, x);
        x = -3;  y = -3;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 1);   TEST_EQUAL(r, 0);   TEST_EQUAL(q * y + r, x);
        x = -2;  y = -3;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 1);   TEST_EQUAL(r, 1);   TEST_EQUAL(q * y + r, x);
        x = -1;  y = -3;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 1);   TEST_EQUAL(r, 2);   TEST_EQUAL(q * y + r, x);
        x = 0;   y = -3;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 0);   TEST_EQUAL(r, 0);   TEST_EQUAL(q * y + r, x);
        x = 1;   y = -3;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 0);   TEST_EQUAL(r, 1);   TEST_EQUAL(q * y + r, x);
        x = 2;   y = -3;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 0);   TEST_EQUAL(r, 2);   TEST_EQUAL(q * y + r, x);
        x = 3;   y = -3;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, -1);  TEST_EQUAL(r, 0);   TEST_EQUAL(q * y + r, x);
        x = 4;   y = -3;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, -1);  TEST_EQUAL(r, 1);   TEST_EQUAL(q * y + r, x);
        x = 5;   y = -3;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, -1);  TEST_EQUAL(r, 2);   TEST_EQUAL(q * y + r, x);
        x = 6;   y = -3;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, -2);  TEST_EQUAL(r, 0);   TEST_EQUAL(q * y + r, x);

    }

    {

        double q{};
        double r{};
        double x{};
        double y{};

        x = -6;  y = 3;   TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, -2);  TEST_EQUAL(r, 0);   TEST_EQUAL(q * y + r, x);
        x = -5;  y = 3;   TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, -2);  TEST_EQUAL(r, 1);   TEST_EQUAL(q * y + r, x);
        x = -4;  y = 3;   TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, -2);  TEST_EQUAL(r, 2);   TEST_EQUAL(q * y + r, x);
        x = -3;  y = 3;   TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, -1);  TEST_EQUAL(r, 0);   TEST_EQUAL(q * y + r, x);
        x = -2;  y = 3;   TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, -1);  TEST_EQUAL(r, 1);   TEST_EQUAL(q * y + r, x);
        x = -1;  y = 3;   TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, -1);  TEST_EQUAL(r, 2);   TEST_EQUAL(q * y + r, x);
        x = 0;   y = 3;   TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 0);   TEST_EQUAL(r, 0);   TEST_EQUAL(q * y + r, x);
        x = 1;   y = 3;   TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 0);   TEST_EQUAL(r, 1);   TEST_EQUAL(q * y + r, x);
        x = 2;   y = 3;   TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 0);   TEST_EQUAL(r, 2);   TEST_EQUAL(q * y + r, x);
        x = 3;   y = 3;   TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 1);   TEST_EQUAL(r, 0);   TEST_EQUAL(q * y + r, x);
        x = 4;   y = 3;   TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 1);   TEST_EQUAL(r, 1);   TEST_EQUAL(q * y + r, x);
        x = 5;   y = 3;   TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 1);   TEST_EQUAL(r, 2);   TEST_EQUAL(q * y + r, x);
        x = 6;   y = 3;   TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 2);   TEST_EQUAL(r, 0);   TEST_EQUAL(q * y + r, x);
        x = -6;  y = -3;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 2);   TEST_EQUAL(r, 0);   TEST_EQUAL(q * y + r, x);
        x = -5;  y = -3;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 2);   TEST_EQUAL(r, 1);   TEST_EQUAL(q * y + r, x);
        x = -4;  y = -3;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 2);   TEST_EQUAL(r, 2);   TEST_EQUAL(q * y + r, x);
        x = -3;  y = -3;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 1);   TEST_EQUAL(r, 0);   TEST_EQUAL(q * y + r, x);
        x = -2;  y = -3;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 1);   TEST_EQUAL(r, 1);   TEST_EQUAL(q * y + r, x);
        x = -1;  y = -3;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 1);   TEST_EQUAL(r, 2);   TEST_EQUAL(q * y + r, x);
        x = 0;   y = -3;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 0);   TEST_EQUAL(r, 0);   TEST_EQUAL(q * y + r, x);
        x = 1;   y = -3;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 0);   TEST_EQUAL(r, 1);   TEST_EQUAL(q * y + r, x);
        x = 2;   y = -3;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 0);   TEST_EQUAL(r, 2);   TEST_EQUAL(q * y + r, x);
        x = 3;   y = -3;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, -1);  TEST_EQUAL(r, 0);   TEST_EQUAL(q * y + r, x);
        x = 4;   y = -3;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, -1);  TEST_EQUAL(r, 1);   TEST_EQUAL(q * y + r, x);
        x = 5;   y = -3;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, -1);  TEST_EQUAL(r, 2);   TEST_EQUAL(q * y + r, x);
        x = 6;   y = -3;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, -2);  TEST_EQUAL(r, 0);   TEST_EQUAL(q * y + r, x);

    }

    {

        Natural q{};
        Natural r{};
        Natural x{};
        Natural y{};

        x = 0u;   y = 3u;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 0u);  TEST_EQUAL(r, 0u);  TEST_EQUAL(q * y + r, x);
        x = 1u;   y = 3u;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 0u);  TEST_EQUAL(r, 1u);  TEST_EQUAL(q * y + r, x);
        x = 2u;   y = 3u;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 0u);  TEST_EQUAL(r, 2u);  TEST_EQUAL(q * y + r, x);
        x = 3u;   y = 3u;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 1u);  TEST_EQUAL(r, 0u);  TEST_EQUAL(q * y + r, x);
        x = 4u;   y = 3u;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 1u);  TEST_EQUAL(r, 1u);  TEST_EQUAL(q * y + r, x);
        x = 5u;   y = 3u;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 1u);  TEST_EQUAL(r, 2u);  TEST_EQUAL(q * y + r, x);
        x = 6u;   y = 3u;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 2u);  TEST_EQUAL(r, 0u);  TEST_EQUAL(q * y + r, x);
        x = 7u;   y = 3u;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 2u);  TEST_EQUAL(r, 1u);  TEST_EQUAL(q * y + r, x);
        x = 8u;   y = 3u;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 2u);  TEST_EQUAL(r, 2u);  TEST_EQUAL(q * y + r, x);
        x = 9u;   y = 3u;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 3u);  TEST_EQUAL(r, 0u);  TEST_EQUAL(q * y + r, x);
        x = 10u;  y = 3u;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 3u);  TEST_EQUAL(r, 1u);  TEST_EQUAL(q * y + r, x);

    }

    {

        Integer q{};
        Integer r{};
        Integer x{};
        Integer y{};

        x = -6;  y = 3;   TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, -2);  TEST_EQUAL(r, 0);   TEST_EQUAL(q * y + r, x);
        x = -5;  y = 3;   TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, -2);  TEST_EQUAL(r, 1);   TEST_EQUAL(q * y + r, x);
        x = -4;  y = 3;   TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, -2);  TEST_EQUAL(r, 2);   TEST_EQUAL(q * y + r, x);
        x = -3;  y = 3;   TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, -1);  TEST_EQUAL(r, 0);   TEST_EQUAL(q * y + r, x);
        x = -2;  y = 3;   TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, -1);  TEST_EQUAL(r, 1);   TEST_EQUAL(q * y + r, x);
        x = -1;  y = 3;   TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, -1);  TEST_EQUAL(r, 2);   TEST_EQUAL(q * y + r, x);
        x = 0;   y = 3;   TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 0);   TEST_EQUAL(r, 0);   TEST_EQUAL(q * y + r, x);
        x = 1;   y = 3;   TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 0);   TEST_EQUAL(r, 1);   TEST_EQUAL(q * y + r, x);
        x = 2;   y = 3;   TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 0);   TEST_EQUAL(r, 2);   TEST_EQUAL(q * y + r, x);
        x = 3;   y = 3;   TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 1);   TEST_EQUAL(r, 0);   TEST_EQUAL(q * y + r, x);
        x = 4;   y = 3;   TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 1);   TEST_EQUAL(r, 1);   TEST_EQUAL(q * y + r, x);
        x = 5;   y = 3;   TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 1);   TEST_EQUAL(r, 2);   TEST_EQUAL(q * y + r, x);
        x = 6;   y = 3;   TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 2);   TEST_EQUAL(r, 0);   TEST_EQUAL(q * y + r, x);
        x = -6;  y = -3;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 2);   TEST_EQUAL(r, 0);   TEST_EQUAL(q * y + r, x);
        x = -5;  y = -3;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 2);   TEST_EQUAL(r, 1);   TEST_EQUAL(q * y + r, x);
        x = -4;  y = -3;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 2);   TEST_EQUAL(r, 2);   TEST_EQUAL(q * y + r, x);
        x = -3;  y = -3;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 1);   TEST_EQUAL(r, 0);   TEST_EQUAL(q * y + r, x);
        x = -2;  y = -3;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 1);   TEST_EQUAL(r, 1);   TEST_EQUAL(q * y + r, x);
        x = -1;  y = -3;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 1);   TEST_EQUAL(r, 2);   TEST_EQUAL(q * y + r, x);
        x = 0;   y = -3;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 0);   TEST_EQUAL(r, 0);   TEST_EQUAL(q * y + r, x);
        x = 1;   y = -3;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 0);   TEST_EQUAL(r, 1);   TEST_EQUAL(q * y + r, x);
        x = 2;   y = -3;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, 0);   TEST_EQUAL(r, 2);   TEST_EQUAL(q * y + r, x);
        x = 3;   y = -3;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, -1);  TEST_EQUAL(r, 0);   TEST_EQUAL(q * y + r, x);
        x = 4;   y = -3;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, -1);  TEST_EQUAL(r, 1);   TEST_EQUAL(q * y + r, x);
        x = 5;   y = -3;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, -1);  TEST_EQUAL(r, 2);   TEST_EQUAL(q * y + r, x);
        x = 6;   y = -3;  TRY(std::tie(q, r) = euclidean_divide(x, y));  TEST_EQUAL(q, -2);  TEST_EQUAL(r, 0);   TEST_EQUAL(q * y + r, x);

    }

}

void test_rs_core_arithmetic_gcd_lcm_int() {

    {

        int x{};
        int y{};
        int z{};

        x = 0;    y = 0;    TRY(z = gcd(x, y));  TEST_EQUAL(z, 0);   TEST_EQUAL(z, std::gcd(x, y));
        x = 0;    y = 10;   TRY(z = gcd(x, y));  TEST_EQUAL(z, 10);  TEST_EQUAL(z, std::gcd(x, y));
        x = 10;   y = 0;    TRY(z = gcd(x, y));  TEST_EQUAL(z, 10);  TEST_EQUAL(z, std::gcd(x, y));
        x = 1;    y = 10;   TRY(z = gcd(x, y));  TEST_EQUAL(z, 1);   TEST_EQUAL(z, std::gcd(x, y));
        x = 10;   y = 1;    TRY(z = gcd(x, y));  TEST_EQUAL(z, 1);   TEST_EQUAL(z, std::gcd(x, y));
        x = 3;    y = 5;    TRY(z = gcd(x, y));  TEST_EQUAL(z, 1);   TEST_EQUAL(z, std::gcd(x, y));
        x = 5;    y = 3;    TRY(z = gcd(x, y));  TEST_EQUAL(z, 1);   TEST_EQUAL(z, std::gcd(x, y));
        x = 30;   y = 75;   TRY(z = gcd(x, y));  TEST_EQUAL(z, 15);  TEST_EQUAL(z, std::gcd(x, y));
        x = 75;   y = 30;   TRY(z = gcd(x, y));  TEST_EQUAL(z, 15);  TEST_EQUAL(z, std::gcd(x, y));
        x = -30;  y = 75;   TRY(z = gcd(x, y));  TEST_EQUAL(z, 15);  TEST_EQUAL(z, std::gcd(x, y));
        x = -75;  y = 30;   TRY(z = gcd(x, y));  TEST_EQUAL(z, 15);  TEST_EQUAL(z, std::gcd(x, y));
        x = 30;   y = -75;  TRY(z = gcd(x, y));  TEST_EQUAL(z, 15);  TEST_EQUAL(z, std::gcd(x, y));
        x = 75;   y = -30;  TRY(z = gcd(x, y));  TEST_EQUAL(z, 15);  TEST_EQUAL(z, std::gcd(x, y));
        x = -30;  y = -75;  TRY(z = gcd(x, y));  TEST_EQUAL(z, 15);  TEST_EQUAL(z, std::gcd(x, y));
        x = -75;  y = -30;  TRY(z = gcd(x, y));  TEST_EQUAL(z, 15);  TEST_EQUAL(z, std::gcd(x, y));

        x = 0;    y = 0;    TRY(z = lcm(x, y));  TEST_EQUAL(z, 0);    TEST_EQUAL(z, std::lcm(x, y));
        x = 0;    y = 10;   TRY(z = lcm(x, y));  TEST_EQUAL(z, 0);    TEST_EQUAL(z, std::lcm(x, y));
        x = 10;   y = 0;    TRY(z = lcm(x, y));  TEST_EQUAL(z, 0);    TEST_EQUAL(z, std::lcm(x, y));
        x = 1;    y = 10;   TRY(z = lcm(x, y));  TEST_EQUAL(z, 10);   TEST_EQUAL(z, std::lcm(x, y));
        x = 10;   y = 1;    TRY(z = lcm(x, y));  TEST_EQUAL(z, 10);   TEST_EQUAL(z, std::lcm(x, y));
        x = 3;    y = 5;    TRY(z = lcm(x, y));  TEST_EQUAL(z, 15);   TEST_EQUAL(z, std::lcm(x, y));
        x = 5;    y = 3;    TRY(z = lcm(x, y));  TEST_EQUAL(z, 15);   TEST_EQUAL(z, std::lcm(x, y));
        x = 30;   y = 75;   TRY(z = lcm(x, y));  TEST_EQUAL(z, 150);  TEST_EQUAL(z, std::lcm(x, y));
        x = 75;   y = 30;   TRY(z = lcm(x, y));  TEST_EQUAL(z, 150);  TEST_EQUAL(z, std::lcm(x, y));
        x = -30;  y = 75;   TRY(z = lcm(x, y));  TEST_EQUAL(z, 150);  TEST_EQUAL(z, std::lcm(x, y));
        x = -75;  y = 30;   TRY(z = lcm(x, y));  TEST_EQUAL(z, 150);  TEST_EQUAL(z, std::lcm(x, y));
        x = 30;   y = -75;  TRY(z = lcm(x, y));  TEST_EQUAL(z, 150);  TEST_EQUAL(z, std::lcm(x, y));
        x = 75;   y = -30;  TRY(z = lcm(x, y));  TEST_EQUAL(z, 150);  TEST_EQUAL(z, std::lcm(x, y));
        x = -30;  y = -75;  TRY(z = lcm(x, y));  TEST_EQUAL(z, 150);  TEST_EQUAL(z, std::lcm(x, y));
        x = -75;  y = -30;  TRY(z = lcm(x, y));  TEST_EQUAL(z, 150);  TEST_EQUAL(z, std::lcm(x, y));

    }

    {

        unsigned x{};
        unsigned y{};
        unsigned z{};

        x = 0;   y = 0;   TRY(z = gcd(x, y));  TEST_EQUAL(z, 0u);   TEST_EQUAL(z, std::gcd(x, y));
        x = 0;   y = 10;  TRY(z = gcd(x, y));  TEST_EQUAL(z, 10u);  TEST_EQUAL(z, std::gcd(x, y));
        x = 10;  y = 0;   TRY(z = gcd(x, y));  TEST_EQUAL(z, 10u);  TEST_EQUAL(z, std::gcd(x, y));
        x = 1;   y = 10;  TRY(z = gcd(x, y));  TEST_EQUAL(z, 1u);   TEST_EQUAL(z, std::gcd(x, y));
        x = 10;  y = 1;   TRY(z = gcd(x, y));  TEST_EQUAL(z, 1u);   TEST_EQUAL(z, std::gcd(x, y));
        x = 3;   y = 5;   TRY(z = gcd(x, y));  TEST_EQUAL(z, 1u);   TEST_EQUAL(z, std::gcd(x, y));
        x = 5;   y = 3;   TRY(z = gcd(x, y));  TEST_EQUAL(z, 1u);   TEST_EQUAL(z, std::gcd(x, y));
        x = 30;  y = 75;  TRY(z = gcd(x, y));  TEST_EQUAL(z, 15u);  TEST_EQUAL(z, std::gcd(x, y));
        x = 75;  y = 30;  TRY(z = gcd(x, y));  TEST_EQUAL(z, 15u);  TEST_EQUAL(z, std::gcd(x, y));

        x = 0;   y = 0;   TRY(z = lcm(x, y));  TEST_EQUAL(z, 0u);    TEST_EQUAL(z, std::lcm(x, y));
        x = 0;   y = 10;  TRY(z = lcm(x, y));  TEST_EQUAL(z, 0u);    TEST_EQUAL(z, std::lcm(x, y));
        x = 10;  y = 0;   TRY(z = lcm(x, y));  TEST_EQUAL(z, 0u);    TEST_EQUAL(z, std::lcm(x, y));
        x = 1;   y = 10;  TRY(z = lcm(x, y));  TEST_EQUAL(z, 10u);   TEST_EQUAL(z, std::lcm(x, y));
        x = 10;  y = 1;   TRY(z = lcm(x, y));  TEST_EQUAL(z, 10u);   TEST_EQUAL(z, std::lcm(x, y));
        x = 3;   y = 5;   TRY(z = lcm(x, y));  TEST_EQUAL(z, 15u);   TEST_EQUAL(z, std::lcm(x, y));
        x = 5;   y = 3;   TRY(z = lcm(x, y));  TEST_EQUAL(z, 15u);   TEST_EQUAL(z, std::lcm(x, y));
        x = 30;  y = 75;  TRY(z = lcm(x, y));  TEST_EQUAL(z, 150u);  TEST_EQUAL(z, std::lcm(x, y));
        x = 75;  y = 30;  TRY(z = lcm(x, y));  TEST_EQUAL(z, 150u);  TEST_EQUAL(z, std::lcm(x, y));

    }

    {

        Integer x{};
        Integer y{};
        Integer z{};

        x = 0_Z;    y = 0_Z;    TRY(z = gcd(x, y));  TEST_EQUAL(z, 0_Z);
        x = 0_Z;    y = 10_Z;   TRY(z = gcd(x, y));  TEST_EQUAL(z, 10_Z);
        x = 10_Z;   y = 0_Z;    TRY(z = gcd(x, y));  TEST_EQUAL(z, 10_Z);
        x = 1_Z;    y = 10_Z;   TRY(z = gcd(x, y));  TEST_EQUAL(z, 1_Z);
        x = 10_Z;   y = 1_Z;    TRY(z = gcd(x, y));  TEST_EQUAL(z, 1_Z);
        x = 3_Z;    y = 5_Z;    TRY(z = gcd(x, y));  TEST_EQUAL(z, 1_Z);
        x = 5_Z;    y = 3_Z;    TRY(z = gcd(x, y));  TEST_EQUAL(z, 1_Z);
        x = 30_Z;   y = 75_Z;   TRY(z = gcd(x, y));  TEST_EQUAL(z, 15_Z);
        x = 75_Z;   y = 30_Z;   TRY(z = gcd(x, y));  TEST_EQUAL(z, 15_Z);
        x = -30_Z;  y = 75_Z;   TRY(z = gcd(x, y));  TEST_EQUAL(z, 15_Z);
        x = -75_Z;  y = 30_Z;   TRY(z = gcd(x, y));  TEST_EQUAL(z, 15_Z);
        x = 30_Z;   y = -75_Z;  TRY(z = gcd(x, y));  TEST_EQUAL(z, 15_Z);
        x = 75_Z;   y = -30_Z;  TRY(z = gcd(x, y));  TEST_EQUAL(z, 15_Z);
        x = -30_Z;  y = -75_Z;  TRY(z = gcd(x, y));  TEST_EQUAL(z, 15_Z);
        x = -75_Z;  y = -30_Z;  TRY(z = gcd(x, y));  TEST_EQUAL(z, 15_Z);

        x = 0_Z;    y = 0_Z;    TRY(z = lcm(x, y));  TEST_EQUAL(z, 0_Z);
        x = 0_Z;    y = 10_Z;   TRY(z = lcm(x, y));  TEST_EQUAL(z, 0_Z);
        x = 10_Z;   y = 0_Z;    TRY(z = lcm(x, y));  TEST_EQUAL(z, 0_Z);
        x = 1_Z;    y = 10_Z;   TRY(z = lcm(x, y));  TEST_EQUAL(z, 10_Z);
        x = 10_Z;   y = 1_Z;    TRY(z = lcm(x, y));  TEST_EQUAL(z, 10_Z);
        x = 3_Z;    y = 5_Z;    TRY(z = lcm(x, y));  TEST_EQUAL(z, 15_Z);
        x = 5_Z;    y = 3_Z;    TRY(z = lcm(x, y));  TEST_EQUAL(z, 15_Z);
        x = 30_Z;   y = 75_Z;   TRY(z = lcm(x, y));  TEST_EQUAL(z, 150_Z);
        x = 75_Z;   y = 30_Z;   TRY(z = lcm(x, y));  TEST_EQUAL(z, 150_Z);
        x = -30_Z;  y = 75_Z;   TRY(z = lcm(x, y));  TEST_EQUAL(z, 150_Z);
        x = -75_Z;  y = 30_Z;   TRY(z = lcm(x, y));  TEST_EQUAL(z, 150_Z);
        x = 30_Z;   y = -75_Z;  TRY(z = lcm(x, y));  TEST_EQUAL(z, 150_Z);
        x = 75_Z;   y = -30_Z;  TRY(z = lcm(x, y));  TEST_EQUAL(z, 150_Z);
        x = -30_Z;  y = -75_Z;  TRY(z = lcm(x, y));  TEST_EQUAL(z, 150_Z);
        x = -75_Z;  y = -30_Z;  TRY(z = lcm(x, y));  TEST_EQUAL(z, 150_Z);

    }

    {

        Natural x{};
        Natural y{};
        Natural z{};

        x = 0_N;   y = 0_N;   TRY(z = gcd(x, y));  TEST_EQUAL(z, 0_N);
        x = 0_N;   y = 10_N;  TRY(z = gcd(x, y));  TEST_EQUAL(z, 10_N);
        x = 10_N;  y = 0_N;   TRY(z = gcd(x, y));  TEST_EQUAL(z, 10_N);
        x = 1_N;   y = 10_N;  TRY(z = gcd(x, y));  TEST_EQUAL(z, 1_N);
        x = 10_N;  y = 1_N;   TRY(z = gcd(x, y));  TEST_EQUAL(z, 1_N);
        x = 3_N;   y = 5_N;   TRY(z = gcd(x, y));  TEST_EQUAL(z, 1_N);
        x = 5_N;   y = 3_N;   TRY(z = gcd(x, y));  TEST_EQUAL(z, 1_N);
        x = 30_N;  y = 75_N;  TRY(z = gcd(x, y));  TEST_EQUAL(z, 15_N);
        x = 75_N;  y = 30_N;  TRY(z = gcd(x, y));  TEST_EQUAL(z, 15_N);

        x = 0_N;   y = 0_N;   TRY(z = lcm(x, y));  TEST_EQUAL(z, 0_N);
        x = 0_N;   y = 10_N;  TRY(z = lcm(x, y));  TEST_EQUAL(z, 0_N);
        x = 10_N;  y = 0_N;   TRY(z = lcm(x, y));  TEST_EQUAL(z, 0_N);
        x = 1_N;   y = 10_N;  TRY(z = lcm(x, y));  TEST_EQUAL(z, 10_N);
        x = 10_N;  y = 1_N;   TRY(z = lcm(x, y));  TEST_EQUAL(z, 10_N);
        x = 3_N;   y = 5_N;   TRY(z = lcm(x, y));  TEST_EQUAL(z, 15_N);
        x = 5_N;   y = 3_N;   TRY(z = lcm(x, y));  TEST_EQUAL(z, 15_N);
        x = 30_N;  y = 75_N;  TRY(z = lcm(x, y));  TEST_EQUAL(z, 150_N);
        x = 75_N;  y = 30_N;  TRY(z = lcm(x, y));  TEST_EQUAL(z, 150_N);

    }

}

namespace {

    enum class MyBitmask: int {
        none     = 0,
        alpha    = 1,
        bravo    = 2,
        charlie  = 4,
        all      = 7,
    };

}

void test_rs_core_arithmetic_bitmask_functions() {

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

void test_rs_core_arithmetic_checked_cast() {

    std::int8_t i8;
    std::int16_t i16;
    std::int32_t i32;
    std::uint8_t u8;
    std::uint16_t u16;
    std::uint32_t u32;
    std::optional<std::int16_t> oi;
    std::optional<std::uint16_t> ou;

    // Signed to signed

    i8 = 0;        TRY(oi = checked_cast<std::int16_t>(i8));   TEST(oi); TEST_EQUAL(oi.value(), 0);
    i8 = 1;        TRY(oi = checked_cast<std::int16_t>(i8));   TEST(oi); TEST_EQUAL(oi.value(), 1);
    i8 = 127;      TRY(oi = checked_cast<std::int16_t>(i8));   TEST(oi); TEST_EQUAL(oi.value(), 127);
    i8 = -1;       TRY(oi = checked_cast<std::int16_t>(i8));   TEST(oi); TEST_EQUAL(oi.value(), -1);
    i8 = -128;     TRY(oi = checked_cast<std::int16_t>(i8));   TEST(oi); TEST_EQUAL(oi.value(), -128);
    i16 = 0;       TRY(oi = checked_cast<std::int16_t>(i16));  TEST(oi); TEST_EQUAL(oi.value(), 0);
    i16 = 1;       TRY(oi = checked_cast<std::int16_t>(i16));  TEST(oi); TEST_EQUAL(oi.value(), 1);
    i16 = 32767;   TRY(oi = checked_cast<std::int16_t>(i16));  TEST(oi); TEST_EQUAL(oi.value(), 32767);
    i16 = -1;      TRY(oi = checked_cast<std::int16_t>(i16));  TEST(oi); TEST_EQUAL(oi.value(), -1);
    i16 = -32768;  TRY(oi = checked_cast<std::int16_t>(i16));  TEST(oi); TEST_EQUAL(oi.value(), -32768);
    i32 = 0;       TRY(oi = checked_cast<std::int16_t>(i32));  TEST(oi); TEST_EQUAL(oi.value(), 0);
    i32 = 1;       TRY(oi = checked_cast<std::int16_t>(i32));  TEST(oi); TEST_EQUAL(oi.value(), 1);
    i32 = 32767;   TRY(oi = checked_cast<std::int16_t>(i32));  TEST(oi); TEST_EQUAL(oi.value(), 32767);
    i32 = 32768;   TRY(oi = checked_cast<std::int16_t>(i32));  TEST(! oi);
    i32 = 65535;   TRY(oi = checked_cast<std::int16_t>(i32));  TEST(! oi);
    i32 = 65536;   TRY(oi = checked_cast<std::int16_t>(i32));  TEST(! oi);
    i32 = -1;      TRY(oi = checked_cast<std::int16_t>(i32));  TEST(oi); TEST_EQUAL(oi.value(), -1);
    i32 = -32768;  TRY(oi = checked_cast<std::int16_t>(i32));  TEST(oi); TEST_EQUAL(oi.value(), -32768);
    i32 = -32769;  TRY(oi = checked_cast<std::int16_t>(i32));  TEST(! oi);
    i32 = -65535;  TRY(oi = checked_cast<std::int16_t>(i32));  TEST(! oi);
    i32 = -65536;  TRY(oi = checked_cast<std::int16_t>(i32));  TEST(! oi);

    // Unsigned to unsigned

    u8 = 0;       TRY(ou = checked_cast<std::uint16_t>(u8));   TEST(ou); TEST_EQUAL(ou.value(), 0u);
    u8 = 1;       TRY(ou = checked_cast<std::uint16_t>(u8));   TEST(ou); TEST_EQUAL(ou.value(), 1u);
    u8 = 255;     TRY(ou = checked_cast<std::uint16_t>(u8));   TEST(ou); TEST_EQUAL(ou.value(), 255u);
    u16 = 0;      TRY(ou = checked_cast<std::uint16_t>(u16));  TEST(ou); TEST_EQUAL(ou.value(), 0u);
    u16 = 1;      TRY(ou = checked_cast<std::uint16_t>(u16));  TEST(ou); TEST_EQUAL(ou.value(), 1u);
    u16 = 32767;  TRY(ou = checked_cast<std::uint16_t>(u16));  TEST(ou); TEST_EQUAL(ou.value(), 32767u);
    u16 = 32768;  TRY(ou = checked_cast<std::uint16_t>(u16));  TEST(ou); TEST_EQUAL(ou.value(), 32768u);
    u16 = 65535;  TRY(ou = checked_cast<std::uint16_t>(u16));  TEST(ou); TEST_EQUAL(ou.value(), 65535u);
    u32 = 0;      TRY(ou = checked_cast<std::uint16_t>(u32));  TEST(ou); TEST_EQUAL(ou.value(), 0u);
    u32 = 1;      TRY(ou = checked_cast<std::uint16_t>(u32));  TEST(ou); TEST_EQUAL(ou.value(), 1u);
    u32 = 32767;  TRY(ou = checked_cast<std::uint16_t>(u32));  TEST(ou); TEST_EQUAL(ou.value(), 32767u);
    u32 = 32768;  TRY(ou = checked_cast<std::uint16_t>(u32));  TEST(ou); TEST_EQUAL(ou.value(), 32768u);
    u32 = 65535;  TRY(ou = checked_cast<std::uint16_t>(u32));  TEST(ou); TEST_EQUAL(ou.value(), 65535u);
    u32 = 65536;  TRY(ou = checked_cast<std::uint16_t>(u32));  TEST(! ou);

    // Signed to unsigned

    i8 = 0;        TRY(ou = checked_cast<std::uint16_t>(i8));   TEST(ou); TEST_EQUAL(ou.value(), 0u);
    i8 = 1;        TRY(ou = checked_cast<std::uint16_t>(i8));   TEST(ou); TEST_EQUAL(ou.value(), 1u);
    i8 = 127;      TRY(ou = checked_cast<std::uint16_t>(i8));   TEST(ou); TEST_EQUAL(ou.value(), 127u);
    i8 = -1;       TRY(ou = checked_cast<std::uint16_t>(i8));   TEST(! ou);
    i8 = -128;     TRY(ou = checked_cast<std::uint16_t>(i8));   TEST(! ou);
    i16 = 0;       TRY(ou = checked_cast<std::uint16_t>(i16));  TEST(ou); TEST_EQUAL(ou.value(), 0u);
    i16 = 1;       TRY(ou = checked_cast<std::uint16_t>(i16));  TEST(ou); TEST_EQUAL(ou.value(), 1u);
    i16 = 32767;   TRY(ou = checked_cast<std::uint16_t>(i16));  TEST(ou); TEST_EQUAL(ou.value(), 32767u);
    i16 = -1;      TRY(ou = checked_cast<std::uint16_t>(i16));  TEST(! ou);
    i16 = -32768;  TRY(ou = checked_cast<std::uint16_t>(i16));  TEST(! ou);
    i32 = 0;       TRY(ou = checked_cast<std::uint16_t>(i32));  TEST(ou); TEST_EQUAL(ou.value(), 0u);
    i32 = 1;       TRY(ou = checked_cast<std::uint16_t>(i32));  TEST(ou); TEST_EQUAL(ou.value(), 1u);
    i32 = 32767;   TRY(ou = checked_cast<std::uint16_t>(i32));  TEST(ou); TEST_EQUAL(ou.value(), 32767u);
    i32 = 32768;   TRY(ou = checked_cast<std::uint16_t>(i32));  TEST(ou); TEST_EQUAL(ou.value(), 32768u);
    i32 = 65535;   TRY(ou = checked_cast<std::uint16_t>(i32));  TEST(ou); TEST_EQUAL(ou.value(), 65535u);
    i32 = 65536;   TRY(ou = checked_cast<std::uint16_t>(i32));  TEST(! ou);
    i32 = -1;      TRY(ou = checked_cast<std::uint16_t>(i32));  TEST(! ou);
    i32 = -32768;  TRY(ou = checked_cast<std::uint16_t>(i32));  TEST(! ou);
    i32 = -32769;  TRY(ou = checked_cast<std::uint16_t>(i32));  TEST(! ou);
    i32 = -65535;  TRY(ou = checked_cast<std::uint16_t>(i32));  TEST(! ou);
    i32 = -65536;  TRY(ou = checked_cast<std::uint16_t>(i32));  TEST(! ou);

    // Unsigned to signed

    u8 = 0;       TRY(oi = checked_cast<std::int16_t>(u8));   TEST(oi); TEST_EQUAL(oi.value(), 0);
    u8 = 1;       TRY(oi = checked_cast<std::int16_t>(u8));   TEST(oi); TEST_EQUAL(oi.value(), 1);
    u8 = 255;     TRY(oi = checked_cast<std::int16_t>(u8));   TEST(oi); TEST_EQUAL(oi.value(), 255);
    u16 = 0;      TRY(oi = checked_cast<std::int16_t>(u16));  TEST(oi); TEST_EQUAL(oi.value(), 0);
    u16 = 1;      TRY(oi = checked_cast<std::int16_t>(u16));  TEST(oi); TEST_EQUAL(oi.value(), 1);
    u16 = 32767;  TRY(oi = checked_cast<std::int16_t>(u16));  TEST(oi); TEST_EQUAL(oi.value(), 32767);
    u16 = 32768;  TRY(oi = checked_cast<std::int16_t>(u16));  TEST(! oi);
    u16 = 65535;  TRY(oi = checked_cast<std::int16_t>(u16));  TEST(! oi);
    u32 = 0;      TRY(oi = checked_cast<std::int16_t>(u32));  TEST(oi); TEST_EQUAL(oi.value(), 0);
    u32 = 1;      TRY(oi = checked_cast<std::int16_t>(u32));  TEST(oi); TEST_EQUAL(oi.value(), 1);
    u32 = 32767;  TRY(oi = checked_cast<std::int16_t>(u32));  TEST(oi); TEST_EQUAL(oi.value(), 32767);
    u32 = 32768;  TRY(oi = checked_cast<std::int16_t>(u32));  TEST(! oi);
    u32 = 65535;  TRY(oi = checked_cast<std::int16_t>(u32));  TEST(! oi);
    u32 = 65536;  TRY(oi = checked_cast<std::int16_t>(u32));  TEST(! oi);

}

void test_rs_core_arithmetic_interpolation() {

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
