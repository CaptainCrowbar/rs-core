#include "rs-core/arithmetic.hpp"
#include "rs-core/mp-integer.hpp"
#include "rs-core/unit-test.hpp"
#include <numeric>
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

void test_rs_core_arithmetic_gcd_lcm() {

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
