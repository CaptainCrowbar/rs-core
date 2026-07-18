#include "rs-core/unit-test.hpp"
#include <string>
#include <utility>

using namespace RS;
using namespace RS::UnitTest;

void test_rs_core_unit_counted() {

    using CS = Counted<std::string>;

    TEST_EQUAL(CS::count(), 0);

    {

        CS a{"a"};  TEST_EQUAL(a.get(), "a");  TEST_EQUAL(CS::count(), 1);
        CS b{"b"};  TEST_EQUAL(b.get(), "b");  TEST_EQUAL(CS::count(), 2);
        CS c{"c"};  TEST_EQUAL(c.get(), "c");  TEST_EQUAL(CS::count(), 3);

        CS d{a};  TEST_EQUAL(a.get(), "a");  TEST_EQUAL(d.get(), "a");  TEST_EQUAL(CS::count(), 4);
        CS e{b};  TEST_EQUAL(b.get(), "b");  TEST_EQUAL(e.get(), "b");  TEST_EQUAL(CS::count(), 5);
        CS f{c};  TEST_EQUAL(c.get(), "c");  TEST_EQUAL(f.get(), "c");  TEST_EQUAL(CS::count(), 6);

        CS g{std::move(a)};  TEST_EQUAL(a.get(), "");  TEST_EQUAL(g.get(), "a");  TEST_EQUAL(CS::count(), 7);
        CS h{std::move(b)};  TEST_EQUAL(b.get(), "");  TEST_EQUAL(h.get(), "b");  TEST_EQUAL(CS::count(), 8);
        CS i{std::move(c)};  TEST_EQUAL(c.get(), "");  TEST_EQUAL(i.get(), "c");  TEST_EQUAL(CS::count(), 9);

        CS j;  TRY(j = d);  TEST_EQUAL(j.get(), "a");  TEST_EQUAL(CS::count(), 10);
        CS k;  TRY(k = e);  TEST_EQUAL(k.get(), "b");  TEST_EQUAL(CS::count(), 11);
        CS l;  TRY(l = f);  TEST_EQUAL(l.get(), "c");  TEST_EQUAL(CS::count(), 12);

        CS m;  TRY(m = std::move(d));  TEST_EQUAL(m.get(), "a");  TEST_EQUAL(CS::count(), 13);
        CS n;  TRY(n = std::move(e));  TEST_EQUAL(n.get(), "b");  TEST_EQUAL(CS::count(), 14);
        CS o;  TRY(o = std::move(f));  TEST_EQUAL(o.get(), "c");  TEST_EQUAL(CS::count(), 15);

    }

    TEST_EQUAL(CS::count(), 0);

    {

        CS a{"a"};
        CS b{"b"};
        CS c{"c"};

        TEST_EQUAL(CS::count(), 3);
        TRY(CS::reset());
        TEST_EQUAL(CS::count(), 0);

    }

    TEST_EQUAL(CS::count(), -3);
    TRY(CS::reset());
    TEST_EQUAL(CS::count(), 0);

}
