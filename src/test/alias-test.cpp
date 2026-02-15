#include "rs-core/alias.hpp"
#include "rs-core/unit-test.hpp"
#include <compare>
#include <concepts>
#include <cstddef>
#include <format>
#include <functional>
#include <ranges>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <vector>

using namespace RS;
using namespace std::literals;

namespace {

    #define LIFE_CYCLE_TEST_TYPE(T, default_flag, copy_flag, move_flag, equality_flag) \
        struct T { \
            std::string str; \
            T() = default_flag; \
            T(const T&) = copy_flag; \
            T(T&&) = move_flag; \
            T& operator=(const T&) = copy_flag; \
            T& operator=(T&&) = move_flag; \
            bool operator==(const T& b) const = equality_flag; \
            explicit T(const char* p): str(p) {} \
            explicit T(const char* p, std::size_t n): str(p, n) {} \
        }; \
        using Alias ## T = Alias<T>;

    LIFE_CYCLE_TEST_TYPE(DefaultMove, default, delete, default, delete);
    LIFE_CYCLE_TEST_TYPE(DefaultCopy, default, default, default, delete);
    LIFE_CYCLE_TEST_TYPE(MoveOnly, delete, delete, default, delete);
    LIFE_CYCLE_TEST_TYPE(CopyOnly, delete, default, default, delete);
    LIFE_CYCLE_TEST_TYPE(Equality, default, default, default, default);

    template <typename T>
    concept BooleanTestable = requires (T t) {
        { static_cast<bool>(t) };
        { ! t } -> std::convertible_to<bool>;
    };

    template <typename T>
    concept AdditionOperators = requires (T t, T u, T& tr) {
        { t + u } -> std::convertible_to<T>;
        { tr += u } -> std::convertible_to<T&>;
    };

    template <typename T>
    concept ArithmeticOperators = AdditionOperators<T>
        && requires (T t, T u, T& tr) {
            { + t } -> std::convertible_to<T>;
            { - t } -> std::convertible_to<T>;
            { t - u } -> std::convertible_to<T>;
            { t * u } -> std::convertible_to<T>;
            { t / u } -> std::convertible_to<T>;
            { tr -= u } -> std::convertible_to<T&>;
            { tr *= u } -> std::convertible_to<T&>;
            { tr /= u } -> std::convertible_to<T&>;
        };

    template <typename T>
    concept BitwiseOperators = requires (T t, T u, T& tr, int i) {
        { ~ t } -> std::convertible_to<T>;
        { t & u } -> std::convertible_to<T>;
        { t | u } -> std::convertible_to<T>;
        { t ^ u } -> std::convertible_to<T>;
        { t << i } -> std::convertible_to<T>;
        { t >> i } -> std::convertible_to<T>;
        { tr &= u } -> std::convertible_to<T&>;
        { tr |= u } -> std::convertible_to<T&>;
        { tr ^= u } -> std::convertible_to<T&>;
        { tr <<= i } -> std::convertible_to<T&>;
        { tr >>= i } -> std::convertible_to<T&>;
    };

    template <typename T>
    concept IntegerOperators = ArithmeticOperators<T>
        && BitwiseOperators<T>
        && requires (T t, T u, T& tr) {
            { ++ tr } -> std::convertible_to<T&>;
            { tr ++ } -> std::convertible_to<T>;
            { -- tr } -> std::convertible_to<T&>;
            { tr -- } -> std::convertible_to<T>;
            { t % u } -> std::convertible_to<T>;
            { tr %= u } -> std::convertible_to<T&>;
        };

    template <typename T>
    concept Indexed = requires (T t, std::size_t i) {
        { t[i] };
    };

    template <typename T>
    concept MutableIndexed = requires (T& t, std::size_t i) {
        { t[i] } -> MutableReference;
    };

}

void test_rs_core_alias_constructors() {

    TEST(std::default_initializable<DefaultMove>);  TEST(std::default_initializable<AliasDefaultMove>);
    TEST(std::movable<DefaultMove>);                TEST(std::movable<AliasDefaultMove>);
    TEST(! std::copyable<DefaultMove>);             TEST(! std::copyable<AliasDefaultMove>);

    TEST(std::default_initializable<DefaultCopy>);  TEST(std::default_initializable<AliasDefaultCopy>);
    TEST(std::movable<DefaultCopy>);                TEST(std::movable<AliasDefaultCopy>);
    TEST(std::copyable<DefaultCopy>);               TEST(std::copyable<AliasDefaultCopy>);

    TEST(! std::default_initializable<MoveOnly>);  TEST(! std::default_initializable<AliasMoveOnly>);
    TEST(std::movable<MoveOnly>);                  TEST(std::movable<AliasMoveOnly>);
    TEST(! std::copyable<MoveOnly>);               TEST(! std::copyable<AliasMoveOnly>);

    TEST(! std::default_initializable<CopyOnly>);  TEST(! std::default_initializable<AliasCopyOnly>);
    TEST(std::movable<CopyOnly>);                  TEST(std::movable<AliasCopyOnly>);
    TEST(std::copyable<CopyOnly>);                 TEST(std::copyable<AliasCopyOnly>);

    DefaultMove dm;
    DefaultCopy dc;

    TRY(dm = DefaultMove("Hello world"));     TEST_EQUAL(dm.str, "Hello world");
    TRY(dc = DefaultCopy("Hello world"));     TEST_EQUAL(dc.str, "Hello world");
    TRY(dm = DefaultMove("Hello world", 5));  TEST_EQUAL(dm.str, "Hello");
    TRY(dc = DefaultCopy("Hello world", 5));  TEST_EQUAL(dc.str, "Hello");

}

void test_rs_core_alias_conversions() {

    class Tag1;
    class Tag2;
    class Tag3;
    class Tag4;

    using AS1 = Alias<std::string, Tag1>;
    using AS2 = Alias<std::string, Tag2>;
    using AS3 = Alias<std::string, Tag3, AliasFlags::implicit_to_alias>;
    using AS4 = Alias<std::string, Tag4, AliasFlags::implicit_from_alias>;

    TEST((std::constructible_from<AS1, std::string>));  TEST((std::constructible_from<std::string, AS1>));
    TEST((std::constructible_from<AS2, std::string>));  TEST((std::constructible_from<std::string, AS2>));
    TEST((std::constructible_from<AS3, std::string>));  TEST((std::constructible_from<std::string, AS3>));
    TEST((std::constructible_from<AS4, std::string>));  TEST((std::constructible_from<std::string, AS4>));
    TEST((std::constructible_from<AS2, AS1>));          TEST((std::constructible_from<AS1, AS2>));

    TEST((! std::convertible_to<std::string, AS1>));  TEST((! std::convertible_to<AS1, std::string>));
    TEST((! std::convertible_to<std::string, AS2>));  TEST((! std::convertible_to<AS2, std::string>));
    TEST((std::convertible_to<std::string, AS3>));    TEST((! std::convertible_to<AS3, std::string>));
    TEST((! std::convertible_to<std::string, AS4>));  TEST((std::convertible_to<AS4, std::string>));
    TEST((! std::convertible_to<AS1, AS2>));          TEST((! std::convertible_to<AS2, AS1>));

    AS1 as1;
    AS2 as2;
    AS3 as3;
    AS4 as4;
    std::string s;

    TRY(as1 = AS1{"Alpha"s});    TEST_EQUAL(*as1, "Alpha");
    TRY(as2 = AS2{"Alpha"s});    TEST_EQUAL(*as2, "Alpha");
    TRY(as3 = "Bravo"s);         TEST_EQUAL(*as3, "Bravo");
    TRY(as4 = AS4{"Charlie"s});  TEST_EQUAL(*as4, "Charlie");

    TRY(s = std::string{as1});  TEST_EQUAL(s, "Alpha");
    TRY(s = std::string{as2});  TEST_EQUAL(s, "Alpha");
    TRY(s = std::string{as3});  TEST_EQUAL(s, "Bravo");
    TRY(s = as4);               TEST_EQUAL(s, "Charlie");

    using AI = Alias<int>;

    TEST(BooleanTestable<AI>);
    TEST(! BooleanTestable<AS1>);

    AI ai{};

    TEST(! ai);
    TRY(ai = AI{1});
    TEST(ai);

}

void test_rs_core_alias_arithmetic_operators() {

    using AI = Alias<int>;
    using AD = Alias<double>;
    using AS = Alias<std::string>;

    TEST(AdditionOperators<AI>);  TEST(ArithmeticOperators<AI>);    TEST(BitwiseOperators<AI>);    TEST(IntegerOperators<AI>);
    TEST(AdditionOperators<AD>);  TEST(ArithmeticOperators<AD>);    TEST(! BitwiseOperators<AD>);  TEST(! IntegerOperators<AD>);
    TEST(AdditionOperators<AS>);  TEST(! ArithmeticOperators<AS>);  TEST(! BitwiseOperators<AS>);  TEST(! IntegerOperators<AS>);

    AI i{3};
    AI j{5};
    AI k;
    AI l;
    AD x{1.25};
    AD y{2.5};
    AD z;
    AS s{"abc"};
    AS t{"xyz"};
    AS u;

    TRY(k = + i);    TEST_EQUAL(*k, 3);
    TRY(k = - i);    TEST_EQUAL(*k, -3);
    TRY(k = i + j);  TEST_EQUAL(*k, 8);
    TRY(k = i - j);  TEST_EQUAL(*k, -2);
    TRY(k = i * j);  TEST_EQUAL(*k, 15);
    TRY(k = i / j);  TEST_EQUAL(*k, 0);
    TRY(k = i % j);  TEST_EQUAL(*k, 3);

    TRY(k = i);  TRY(l = ++ k);  TEST_EQUAL(*k, 4);  TEST_EQUAL(*l, 4);
    TRY(k = i);  TRY(l = k ++);  TEST_EQUAL(*k, 4);  TEST_EQUAL(*l, 3);
    TRY(k = i);  TRY(l = -- k);  TEST_EQUAL(*k, 2);  TEST_EQUAL(*l, 2);
    TRY(k = i);  TRY(l = k --);  TEST_EQUAL(*k, 2);  TEST_EQUAL(*l, 3);

    TRY(k = i);  TRY(k += j);  TEST_EQUAL(*k, 8);
    TRY(k = i);  TRY(k -= j);  TEST_EQUAL(*k, -2);
    TRY(k = i);  TRY(k *= j);  TEST_EQUAL(*k, 15);
    TRY(k = i);  TRY(k /= j);  TEST_EQUAL(*k, 0);
    TRY(k = i);  TRY(k %= j);  TEST_EQUAL(*k, 3);

    TRY(z = - x);    TEST_EQUAL(*z, -1.25);
    TRY(z = x + y);  TEST_EQUAL(*z, 3.75);
    TRY(z = x + y);  TEST_EQUAL(*z, 3.75);
    TRY(z = x - y);  TEST_EQUAL(*z, -1.25);
    TRY(z = x * y);  TEST_EQUAL(*z, 3.125);
    TRY(z = x / y);  TEST_EQUAL(*z, 0.5);

    TRY(z = x);  TRY(z += y);  TEST_EQUAL(*z, 3.75);
    TRY(z = x);  TRY(z -= y);  TEST_EQUAL(*z, -1.25);
    TRY(z = x);  TRY(z *= y);  TEST_EQUAL(*z, 3.125);
    TRY(z = x);  TRY(z /= y);  TEST_EQUAL(*z, 0.5);

    TRY(u = s + t);  TEST_EQUAL(*u, "abcxyz");

    TRY(u = s);  TRY(u += t);  TEST_EQUAL(*u, "abcxyz");

}

void test_rs_core_alias_bitwise_operators() {

    using AI = Alias<int>;
    using AD = Alias<double>;
    using AS = Alias<std::string>;

    TEST(BitwiseOperators<AI>);
    TEST(! BitwiseOperators<AD>);
    TEST(! BitwiseOperators<AS>);

    AI i(3);
    AI j(5);
    AI k;

    TRY(k = i & j);   TEST_EQUAL(*k, 1);
    TRY(k = i | j);   TEST_EQUAL(*k, 7);
    TRY(k = i ^ j);   TEST_EQUAL(*k, 6);
    TRY(k = i << 1);  TEST_EQUAL(*k, 6);
    TRY(k = i >> 1);  TEST_EQUAL(*k, 1);

    TRY(k = i);  TRY(k &= j);   TEST_EQUAL(*k, 1);
    TRY(k = i);  TRY(k |= j);   TEST_EQUAL(*k, 7);
    TRY(k = i);  TRY(k ^= j);   TEST_EQUAL(*k, 6);
    TRY(k = i);  TRY(k <<= 1);  TEST_EQUAL(*k, 6);
    TRY(k = i);  TRY(k >>= 1);  TEST_EQUAL(*k, 1);

}

void test_rs_core_alias_comparison_operators() {

    class Tag1;
    class Tag2;

    using AS = Alias<std::string, Tag1>;
    using ASC = Alias<std::string, Tag2, AliasFlags::cross_compare>;

    TEST(! std::equality_comparable<AliasDefaultCopy>);
    TEST(! std::totally_ordered<AliasDefaultCopy>);
    TEST(std::equality_comparable<AliasEquality>);
    TEST(! std::totally_ordered<AliasEquality>);

    AliasEquality a{"abc"};
    AliasEquality b{"abc"};
    AliasEquality c{"xyz"};
    AS d{"abc"};
    AS e{"abc"};
    AS f{"xyz"};
    ASC g{"abc"};
    ASC h{"abc"};
    ASC i{"xyz"};
    std::string s{"abc"};
    std::string t{"abc"};
    std::string u{"xyz"};

    auto so = std::strong_ordering::equal;

    TEST(a == b);
    TEST(a != c);
    TEST(! (a != b));
    TEST(! (a == c));

    TEST(d == e);
    TEST(d <= e);
    TEST(d >= e);
    TEST(! (d != e));
    TEST(! (d < e));
    TEST(! (d > e));
    TEST(d != f);
    TEST(d < f);
    TEST(d <= f);
    TEST(! (d == f));
    TEST(! (d > f));
    TEST(! (d >= f));

    TEST(g == h);
    TEST(g <= h);
    TEST(g >= h);
    TEST(! (g != h));
    TEST(! (g < h));
    TEST(! (g > h));
    TEST(g != i);
    TEST(g < i);
    TEST(g <= i);
    TEST(! (g == i));
    TEST(! (g > i));
    TEST(! (g >= i));

    TRY(so = d <=> e);
    TEST(so == std::strong_ordering::equal);
    TRY(so = d <=> f);
    TEST(so == std::strong_ordering::less);

    TEST_EQUAL(g, "abc");  TEST_EQUAL("abc", g);
    TEST_EQUAL(h, "abc");  TEST_EQUAL("abc", h);
    TEST_EQUAL(i, "xyz");  TEST_EQUAL("xyz", i);

    TEST(s == t);
    TEST(s <= t);
    TEST(s >= t);
    TEST(! (s != t));
    TEST(! (s < t));
    TEST(! (s > t));
    TEST(s != u);
    TEST(s < u);
    TEST(s <= u);
    TEST(! (s == u));
    TEST(! (s > u));
    TEST(! (s >= u));

    TEST(t == s);
    TEST(t >= s);
    TEST(t <= s);
    TEST(! (t != s));
    TEST(! (t < s));
    TEST(! (t > s));
    TEST(u != s);
    TEST(u > s);
    TEST(u >= s);
    TEST(! (u == s));
    TEST(! (u < s));
    TEST(! (u <= s));

}

void test_rs_core_alias_range_access() {

    using AI = Alias<int>;
    using AS = Alias<std::string>;
    using AV = Alias<std::vector<bool>>;

    TEST(! std::ranges::range<AI>);
    TEST(! std::ranges::random_access_range<AI>);
    TEST(! Indexed<AI>);
    TEST(! MutableIndexed<AI>);

    TEST(std::ranges::range<AS>);
    TEST(std::ranges::random_access_range<AS>);
    TEST(Indexed<AS>);
    TEST(MutableIndexed<AS>);

    TEST(std::ranges::range<AV>);
    TEST(std::ranges::random_access_range<AV>);
    TEST(Indexed<AV>);
    TEST(! MutableIndexed<AV>);

    AS as{"Hello"};
    const auto& cas{as};

    TEST_EQUAL(as[0], 'H');   TEST_EQUAL(cas[0], 'H');
    TEST_EQUAL(as[1], 'e');   TEST_EQUAL(cas[1], 'e');
    TEST_EQUAL(as[2], 'l');   TEST_EQUAL(cas[2], 'l');
    TEST_EQUAL(as[3], 'l');   TEST_EQUAL(cas[3], 'l');
    TEST_EQUAL(as[4], 'o');   TEST_EQUAL(cas[4], 'o');
    TEST_EQUAL(as[5], '\0');  TEST_EQUAL(cas[5], '\0');

    TEST_EQUAL(as->at(0), 'H');  TEST_EQUAL(cas->at(0), 'H');
    TEST_EQUAL(as->at(1), 'e');  TEST_EQUAL(cas->at(1), 'e');
    TEST_EQUAL(as->at(2), 'l');  TEST_EQUAL(cas->at(2), 'l');
    TEST_EQUAL(as->at(3), 'l');  TEST_EQUAL(cas->at(3), 'l');
    TEST_EQUAL(as->at(4), 'o');  TEST_EQUAL(cas->at(4), 'o');

    TEST_THROW(as->at(5), std::out_of_range, "string");
    TEST_THROW(cas->at(5), std::out_of_range, "string");
    TEST_THROW(as->at(6), std::out_of_range, "string");
    TEST_THROW(cas->at(6), std::out_of_range, "string");

    TRY(as[4] = '!');
    TEST_EQUAL(*as, "Hell!");
    int n = 0;

    for (auto c: as) {
        if (c >= 'a' && c <= 'z') {
            ++n;
        }
    }

    TEST_EQUAL(n, 3);

    for (auto& c: as) {
        c = '*';
    }

    TEST_EQUAL(*as, "*****");

}

void test_rs_core_alias_string_functions() {

    using AS = Alias<std::string>;

    AS as{"Hello world"};
    AS at;

    TRY(at = as.substr(0, 5));  TEST_EQUAL(*at, "Hello");
    TRY(at = as.substr(6, 5));  TEST_EQUAL(*at, "world");
    TRY(at = as.substr(6));     TEST_EQUAL(*at, "world");

}

void test_rs_core_alias_formatting() {

    Alias<int> ai{42};
    Alias<std::string> as{"Hello\tworld\n"};

    TEST_EQUAL(std::format("{}", ai),      "42");
    TEST_EQUAL(std::format("{:04x}", ai),  "002a");
    TEST_EQUAL(std::format("{}", as),      "Hello\tworld\n");
    TEST_EQUAL(std::format("{:?}", as),    R"("Hello\tworld\n")");

}

void test_rs_core_alias_hashing() {

    using AS = Alias<std::string>;

    std::string a;
    std::string b{"Hello world"};
    std::string c{"Goodbye"};
    AS s{a};
    AS t{b};
    AS u{c};
    std::size_t m{};
    std::size_t n{};
    std::hash<std::string> hs;
    std::hash<AS> ha;

    m = hs(a);  TRY(n = ha(s));  TEST_EQUAL(m, n);
    m = hs(b);  TRY(n = ha(t));  TEST_EQUAL(m, n);
    m = hs(c);  TRY(n = ha(u));  TEST_EQUAL(m, n);

    std::unordered_set<AS> set;

    TRY(set.insert(s));
    TRY(set.insert(t));
    TRY(set.insert(u));
    TRY(set.insert(s));
    TRY(set.insert(t));
    TRY(set.insert(u));

    TEST_EQUAL(set.size(), 3u);
    TEST(set.contains(s));
    TEST(set.contains(t));
    TEST(set.contains(u));

}
