#include "rs-core/mp-integer.hpp"
#include "rs-core/unit-test.hpp"
#include <string>

using namespace RS;

void test_rs_core_mp_integer_signed_arithmetic() {

    Integer a, b, c, d, x;
    std::string s;

    TRY(x = a + b);  TRY(s = x.str());  TEST_EQUAL(s, "0");
    TRY(x = a - b);  TRY(s = x.str());  TEST_EQUAL(s, "0");
    TRY(x = a * b);  TRY(s = x.str());  TEST_EQUAL(s, "0");

    TRY(b = 10);

    TRY(x = a + b);  TRY(s = x.str());  TEST_EQUAL(s, "10");
    TRY(x = a - b);  TRY(s = x.str());  TEST_EQUAL(s, "-10");
    TRY(x = b - a);  TRY(s = x.str());  TEST_EQUAL(s, "10");
    TRY(x = a * b);  TRY(s = x.str());  TEST_EQUAL(s, "0");
    TRY(x = a / b);  TRY(s = x.str());  TEST_EQUAL(s, "0");
    TRY(x = a % b);  TRY(s = x.str());  TEST_EQUAL(s, "0");

    TRY(a = Integer("42"));
    TRY(b = Integer("10"));
    TRY(c = - a);
    TRY(d = - b);

    TRY(x = a + b);  TRY(s = x.str());  TEST_EQUAL(s, "52");
    TRY(x = a - b);  TRY(s = x.str());  TEST_EQUAL(s, "32");
    TRY(x = b - a);  TRY(s = x.str());  TEST_EQUAL(s, "-32");
    TRY(x = a * b);  TRY(s = x.str());  TEST_EQUAL(s, "420");
    TRY(x = a / b);  TRY(s = x.str());  TEST_EQUAL(s, "4");
    TRY(x = a % b);  TRY(s = x.str());  TEST_EQUAL(s, "2");

    TRY(x = a + d);  TRY(s = x.str());  TEST_EQUAL(s, "32");
    TRY(x = a - d);  TRY(s = x.str());  TEST_EQUAL(s, "52");
    TRY(x = d - a);  TRY(s = x.str());  TEST_EQUAL(s, "-52");
    TRY(x = a * d);  TRY(s = x.str());  TEST_EQUAL(s, "-420");
    TRY(x = a / d);  TRY(s = x.str());  TEST_EQUAL(s, "-4");
    TRY(x = a % d);  TRY(s = x.str());  TEST_EQUAL(s, "2");

    TRY(x = c + b);  TRY(s = x.str());  TEST_EQUAL(s, "-32");
    TRY(x = c - b);  TRY(s = x.str());  TEST_EQUAL(s, "-52");
    TRY(x = b - c);  TRY(s = x.str());  TEST_EQUAL(s, "52");
    TRY(x = c * b);  TRY(s = x.str());  TEST_EQUAL(s, "-420");
    TRY(x = c / b);  TRY(s = x.str());  TEST_EQUAL(s, "-5");
    TRY(x = c % b);  TRY(s = x.str());  TEST_EQUAL(s, "8");

    TRY(x = c + d);  TRY(s = x.str());  TEST_EQUAL(s, "-52");
    TRY(x = c - d);  TRY(s = x.str());  TEST_EQUAL(s, "-32");
    TRY(x = d - c);  TRY(s = x.str());  TEST_EQUAL(s, "32");
    TRY(x = c * d);  TRY(s = x.str());  TEST_EQUAL(s, "420");
    TRY(x = c / d);  TRY(s = x.str());  TEST_EQUAL(s, "5");
    TRY(x = c % d);  TRY(s = x.str());  TEST_EQUAL(s, "8");

    TRY(x = a / 1);  TEST_EQUAL(x, a);
    TRY(x = b / 1);  TEST_EQUAL(x, b);
    TRY(x = c / 1);  TEST_EQUAL(x, c);
    TRY(x = d / 1);  TEST_EQUAL(x, d);

}

void test_rs_core_mp_integer_signed_division() {

    Integer a, b, q, r;

    TRY(a = -6);  TRY(b = 3);   TRY(q = a / b);  TRY(r = a % b);  TEST_EQUAL(q, -2);  TEST_EQUAL(r, 0);  TEST_EQUAL(b * q + r, a);
    TRY(a = -5);  TRY(b = 3);   TRY(q = a / b);  TRY(r = a % b);  TEST_EQUAL(q, -2);  TEST_EQUAL(r, 1);  TEST_EQUAL(b * q + r, a);
    TRY(a = -4);  TRY(b = 3);   TRY(q = a / b);  TRY(r = a % b);  TEST_EQUAL(q, -2);  TEST_EQUAL(r, 2);  TEST_EQUAL(b * q + r, a);
    TRY(a = -3);  TRY(b = 3);   TRY(q = a / b);  TRY(r = a % b);  TEST_EQUAL(q, -1);  TEST_EQUAL(r, 0);  TEST_EQUAL(b * q + r, a);
    TRY(a = -2);  TRY(b = 3);   TRY(q = a / b);  TRY(r = a % b);  TEST_EQUAL(q, -1);  TEST_EQUAL(r, 1);  TEST_EQUAL(b * q + r, a);
    TRY(a = -1);  TRY(b = 3);   TRY(q = a / b);  TRY(r = a % b);  TEST_EQUAL(q, -1);  TEST_EQUAL(r, 2);  TEST_EQUAL(b * q + r, a);
    TRY(a = 0);   TRY(b = 3);   TRY(q = a / b);  TRY(r = a % b);  TEST_EQUAL(q, 0);   TEST_EQUAL(r, 0);  TEST_EQUAL(b * q + r, a);
    TRY(a = 1);   TRY(b = 3);   TRY(q = a / b);  TRY(r = a % b);  TEST_EQUAL(q, 0);   TEST_EQUAL(r, 1);  TEST_EQUAL(b * q + r, a);
    TRY(a = 2);   TRY(b = 3);   TRY(q = a / b);  TRY(r = a % b);  TEST_EQUAL(q, 0);   TEST_EQUAL(r, 2);  TEST_EQUAL(b * q + r, a);
    TRY(a = 3);   TRY(b = 3);   TRY(q = a / b);  TRY(r = a % b);  TEST_EQUAL(q, 1);   TEST_EQUAL(r, 0);  TEST_EQUAL(b * q + r, a);
    TRY(a = 4);   TRY(b = 3);   TRY(q = a / b);  TRY(r = a % b);  TEST_EQUAL(q, 1);   TEST_EQUAL(r, 1);  TEST_EQUAL(b * q + r, a);
    TRY(a = 5);   TRY(b = 3);   TRY(q = a / b);  TRY(r = a % b);  TEST_EQUAL(q, 1);   TEST_EQUAL(r, 2);  TEST_EQUAL(b * q + r, a);
    TRY(a = 6);   TRY(b = 3);   TRY(q = a / b);  TRY(r = a % b);  TEST_EQUAL(q, 2);   TEST_EQUAL(r, 0);  TEST_EQUAL(b * q + r, a);
    TRY(a = -6);  TRY(b = -3);  TRY(q = a / b);  TRY(r = a % b);  TEST_EQUAL(q, 2);   TEST_EQUAL(r, 0);  TEST_EQUAL(b * q + r, a);
    TRY(a = -5);  TRY(b = -3);  TRY(q = a / b);  TRY(r = a % b);  TEST_EQUAL(q, 2);   TEST_EQUAL(r, 1);  TEST_EQUAL(b * q + r, a);
    TRY(a = -4);  TRY(b = -3);  TRY(q = a / b);  TRY(r = a % b);  TEST_EQUAL(q, 2);   TEST_EQUAL(r, 2);  TEST_EQUAL(b * q + r, a);
    TRY(a = -3);  TRY(b = -3);  TRY(q = a / b);  TRY(r = a % b);  TEST_EQUAL(q, 1);   TEST_EQUAL(r, 0);  TEST_EQUAL(b * q + r, a);
    TRY(a = -2);  TRY(b = -3);  TRY(q = a / b);  TRY(r = a % b);  TEST_EQUAL(q, 1);   TEST_EQUAL(r, 1);  TEST_EQUAL(b * q + r, a);
    TRY(a = -1);  TRY(b = -3);  TRY(q = a / b);  TRY(r = a % b);  TEST_EQUAL(q, 1);   TEST_EQUAL(r, 2);  TEST_EQUAL(b * q + r, a);
    TRY(a = 0);   TRY(b = -3);  TRY(q = a / b);  TRY(r = a % b);  TEST_EQUAL(q, 0);   TEST_EQUAL(r, 0);  TEST_EQUAL(b * q + r, a);
    TRY(a = 1);   TRY(b = -3);  TRY(q = a / b);  TRY(r = a % b);  TEST_EQUAL(q, 0);   TEST_EQUAL(r, 1);  TEST_EQUAL(b * q + r, a);
    TRY(a = 2);   TRY(b = -3);  TRY(q = a / b);  TRY(r = a % b);  TEST_EQUAL(q, 0);   TEST_EQUAL(r, 2);  TEST_EQUAL(b * q + r, a);
    TRY(a = 3);   TRY(b = -3);  TRY(q = a / b);  TRY(r = a % b);  TEST_EQUAL(q, -1);  TEST_EQUAL(r, 0);  TEST_EQUAL(b * q + r, a);
    TRY(a = 4);   TRY(b = -3);  TRY(q = a / b);  TRY(r = a % b);  TEST_EQUAL(q, -1);  TEST_EQUAL(r, 1);  TEST_EQUAL(b * q + r, a);
    TRY(a = 5);   TRY(b = -3);  TRY(q = a / b);  TRY(r = a % b);  TEST_EQUAL(q, -1);  TEST_EQUAL(r, 2);  TEST_EQUAL(b * q + r, a);
    TRY(a = 6);   TRY(b = -3);  TRY(q = a / b);  TRY(r = a % b);  TEST_EQUAL(q, -2);  TEST_EQUAL(r, 0);  TEST_EQUAL(b * q + r, a);

}

void test_rs_core_mp_integer_signed_large_arithmetic() {

    Integer a, b, c, d, x, y, z;
    std::string s;

    TRY(a = Integer("123456789123456789123456789123456789123456789"));
    TRY(b = Integer("1357913579135791357913579"));
    TRY(c = - a);
    TRY(d = - b);

    TRY(x = a + b);  TRY(s = x.str());  TEST_EQUAL(s, "123456789123456789124814702702592580481370368");
    TRY(x = a - b);  TRY(s = x.str());  TEST_EQUAL(s, "123456789123456789122098875544320997765543210");
    TRY(x = b - a);  TRY(s = x.str());  TEST_EQUAL(s, "-123456789123456789122098875544320997765543210");
    TRY(x = a * b);  TRY(s = x.str());  TEST_EQUAL(s, "167643650387245846409206049247037049247037049079393398859791202837831");
    TRY(x = a / b);  TRY(s = x.str());  TEST_EQUAL(s, "90916528872203810704");
    TRY(x = a % b);  TRY(s = x.str());  TEST_EQUAL(s, "603972940850418616307173");

    TRY(x = a + d);  TRY(s = x.str());  TEST_EQUAL(s, "123456789123456789122098875544320997765543210");
    TRY(x = a - d);  TRY(s = x.str());  TEST_EQUAL(s, "123456789123456789124814702702592580481370368");
    TRY(x = d - a);  TRY(s = x.str());  TEST_EQUAL(s, "-123456789123456789124814702702592580481370368");
    TRY(x = a * d);  TRY(s = x.str());  TEST_EQUAL(s, "-167643650387245846409206049247037049247037049079393398859791202837831");
    TRY(x = a / d);  TRY(s = x.str());  TEST_EQUAL(s, "-90916528872203810704");
    TRY(x = a % d);  TRY(s = x.str());  TEST_EQUAL(s, "603972940850418616307173");

    TRY(x = c + b);  TRY(s = x.str());  TEST_EQUAL(s, "-123456789123456789122098875544320997765543210");
    TRY(x = c - b);  TRY(s = x.str());  TEST_EQUAL(s, "-123456789123456789124814702702592580481370368");
    TRY(x = b - c);  TRY(s = x.str());  TEST_EQUAL(s, "123456789123456789124814702702592580481370368");
    TRY(x = c * b);  TRY(s = x.str());  TEST_EQUAL(s, "-167643650387245846409206049247037049247037049079393398859791202837831");
    TRY(x = c / b);  TRY(s = x.str());  TEST_EQUAL(s, "-90916528872203810705");
    TRY(x = c % b);  TRY(s = x.str());  TEST_EQUAL(s, "753940638285372741606406");

    TRY(x = c + d);  TRY(s = x.str());  TEST_EQUAL(s, "-123456789123456789124814702702592580481370368");
    TRY(x = c - d);  TRY(s = x.str());  TEST_EQUAL(s, "-123456789123456789122098875544320997765543210");
    TRY(x = d - c);  TRY(s = x.str());  TEST_EQUAL(s, "123456789123456789122098875544320997765543210");
    TRY(x = c * d);  TRY(s = x.str());  TEST_EQUAL(s, "167643650387245846409206049247037049247037049079393398859791202837831");
    TRY(x = c / d);  TRY(s = x.str());  TEST_EQUAL(s, "90916528872203810705");
    TRY(x = c % d);  TRY(s = x.str());  TEST_EQUAL(s, "753940638285372741606406");

    TRY(x = 1);   TRY(y = 1);   TRY(z = x * y);  TEST_EQUAL(z.str(), "1");
    TRY(x = 1);   TRY(y = 0);   TRY(z = x * y);  TEST_EQUAL(z.str(), "0");
    TRY(x = 1);   TRY(y = -1);  TRY(z = x * y);  TEST_EQUAL(z.str(), "-1");
    TRY(x = 0);   TRY(y = 1);   TRY(z = x * y);  TEST_EQUAL(z.str(), "0");
    TRY(x = 0);   TRY(y = 0);   TRY(z = x * y);  TEST_EQUAL(z.str(), "0");
    TRY(x = 0);   TRY(y = -1);  TRY(z = x * y);  TEST_EQUAL(z.str(), "0");
    TRY(x = -1);  TRY(y = 1);   TRY(z = x * y);  TEST_EQUAL(z.str(), "-1");
    TRY(x = -1);  TRY(y = 0);   TRY(z = x * y);  TEST_EQUAL(z.str(), "0");
    TRY(x = -1);  TRY(y = -1);  TRY(z = x * y);  TEST_EQUAL(z.str(), "1");

}
