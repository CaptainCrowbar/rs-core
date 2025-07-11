#include "rs-core/uuid.hpp"
#include "rs-core/format.hpp"
#include "rs-core/random.hpp"
#include "rs-core/unit-test.hpp"
#include <format>
#include <stdexcept>
#include <string>

using namespace RS;

void test_rs_core_uuid_class() {

    Uuid u, v, w, z;
    std::string s;

    TEST_EQUAL(u.str(),                      "00000000-0000-0000-0000-000000000000");
    TEST_EQUAL(static_cast<std::string>(u),  "00000000-0000-0000-0000-000000000000");
    TEST_EQUAL(std::format("{}", u),         "00000000-0000-0000-0000-000000000000");

    TRY((u = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}));

    TEST_EQUAL(u.str(),                      "01020304-0506-0708-090a-0b0c0d0e0f10");
    TEST_EQUAL(static_cast<std::string>(u),  "01020304-0506-0708-090a-0b0c0d0e0f10");
    TEST_EQUAL(std::format("{}", u),         "01020304-0506-0708-090a-0b0c0d0e0f10");

    for (unsigned i = 0; i < 16; ++i) {
        TEST_EQUAL(u[i], i + 1);
    }

    TRY((u = {0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf0, 0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf0}));

    TEST_EQUAL(u.str(),                      "12345678-9abc-def0-1234-56789abcdef0");
    TEST_EQUAL(static_cast<std::string>(u),  "12345678-9abc-def0-1234-56789abcdef0");
    TEST_EQUAL(std::format("{}", u),         "12345678-9abc-def0-1234-56789abcdef0");

    s = "abcdefghijklmnopqrstuvwxyz";
    TRY(u = Uuid::read(s.data()));
    TEST_EQUAL(u.str(), "61626364-6566-6768-696a-6b6c6d6e6f70");

    TRY(u = Uuid(""));                                                                                   TEST_EQUAL(u.str(), "00000000-0000-0000-0000-000000000000");
    TRY(u = Uuid("123456789abcdef123456789abcdef12"));                                                   TEST_EQUAL(u.str(), "12345678-9abc-def1-2345-6789abcdef12");
    TRY(u = Uuid("3456789a-bcde-f123-4567-89abcdef1234"));                                               TEST_EQUAL(u.str(), "3456789a-bcde-f123-4567-89abcdef1234");
    TRY(u = Uuid("56,78,9a,bc,de,f1,23,45,67,89,ab,cd,ef,12,34,56"));                                    TEST_EQUAL(u.str(), "56789abc-def1-2345-6789-abcdef123456");
    TRY(u = Uuid("{0x78,0x9a,0xbc,0xde,0xf1,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0x12,0x34,0x56,0x78}"));  TEST_EQUAL(u.str(), "789abcde-f123-4567-89ab-cdef12345678");
    TRY(u = Uuid("{0xbcdef123, 0x4567, 0x89ab, 0xcd, 0xef, 0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc};"));      TEST_EQUAL(u.str(), "bcdef123-4567-89ab-cdef-123456789abc");

    TEST_THROW(u = Uuid("123456789abcdef123456789abcdefgh"),      std::invalid_argument,  "Invalid UUID");
    TEST_THROW(u = Uuid("123456789abcdef123456789abcdef"),        std::invalid_argument,  "Invalid UUID");
    TEST_THROW(u = Uuid("123456789abcdef123456789abcdef1"),       std::invalid_argument,  "Invalid UUID");
    TEST_THROW(u = Uuid("123456789abcdef123456789abcdef123"),     std::invalid_argument,  "Invalid UUID");
    TEST_THROW(u = Uuid("123456789abcdef123456789abcdef1234"),    std::invalid_argument,  "Invalid UUID");
    TEST_THROW(u = Uuid("123456789-abc-def1-2345-6789abcdef12"),  std::invalid_argument,  "Invalid UUID");

    TRY((u = {0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf1, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0x12}));
    TRY((v = {0xab, 0xcd, 0xef, 0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf1, 0x23, 0x45, 0x67, 0x89, 0xab}));
    TRY(w = v);

    TEST(! (u == v));  TEST(u != v);      TEST(u < v);      TEST(! (u > v));  TEST(u <= v);      TEST(! (u >= v));
    TEST(! (u == w));  TEST(u != w);      TEST(u < w);      TEST(! (u > w));  TEST(u <= w);      TEST(! (u >= w));
    TEST(! (u == z));  TEST(u != z);      TEST(! (u < z));  TEST(u > z);      TEST(! (u <= z));  TEST(u >= z);
    TEST(! (v == u));  TEST(v != u);      TEST(! (v < u));  TEST(v > u);      TEST(! (v <= u));  TEST(v >= u);
    TEST(v == w);      TEST(! (v != w));  TEST(! (v < w));  TEST(! (v > w));  TEST(v <= w);      TEST(v >= w);
    TEST(! (v == z));  TEST(v != z);      TEST(! (v < z));  TEST(v > z);      TEST(! (v <= z));  TEST(v >= z);
    TEST(! (w == u));  TEST(w != u);      TEST(! (w < u));  TEST(w > u);      TEST(! (w <= u));  TEST(w >= u);
    TEST(w == v);      TEST(! (w != v));  TEST(! (w < v));  TEST(! (w > v));  TEST(w <= v);      TEST(w >= v);
    TEST(! (w == z));  TEST(w != z);      TEST(! (w < z));  TEST(w > z);      TEST(! (w <= z));  TEST(w >= z);
    TEST(! (z == u));  TEST(z != u);      TEST(z < u);      TEST(! (z > u));  TEST(z <= u);      TEST(! (z >= u));
    TEST(! (z == v));  TEST(z != v);      TEST(z < v);      TEST(! (z > v));  TEST(z <= v);      TEST(! (z >= v));
    TEST(! (z == w));  TEST(z != w);      TEST(z < w);      TEST(! (z > w));  TEST(z <= w);      TEST(! (z >= w));

}

void test_rs_core_uuid_random() {

    static constexpr auto iterations = 20;

    Uuid u, v;
    std::string s;
    Pcg rng;

    for (auto i = 0; i < iterations; ++i) {
        TRY(u = Uuid::random(rng));
        TEST(u != v);
        TEST_EQUAL(u.version(), 4);
        TRY(s = u.str());
        TEST_MATCH(s, "^[0-9a-f]{8}-[0-9a-f]{4}-4[0-9a-f]{3}-[89ab][0-9a-f]{3}-[0-9a-f]{12}$");
    }

}
