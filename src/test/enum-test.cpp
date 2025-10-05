#include "rs-core/enum.hpp"
#include "rs-core/format.hpp"
#include "rs-core/unit-test.hpp"
#include <concepts>
#include <cstdint>
#include <format>
#include <type_traits>

using namespace RS;

namespace {

    RS_ENUM(Simple, int,
        alpha,
        bravo,
        charlie,
    )

    RS_ENUM(Complicated, unsigned,
        alpha_bravo,
        charlie_delta = 10,
        echo_foxtrot,
        golf_hotel = 0x20,
        india_juliet,
    )

    RS_BITMASK(Mask, std::uint16_t,
        none = 0,
        alpha = 1,
        bravo = 2,
        charlie = 4,
    )

    enum class Raw: int {
        alpha,
    };

}

void test_rs_core_enum_concepts() {

    static_assert(AutoEnum<Simple>);
    static_assert(AutoEnum<Complicated>);
    static_assert(AutoEnum<Mask>);
    static_assert(! AutoEnum<Raw>);

    static_assert(! AutoBitmask<Simple>);
    static_assert(! AutoBitmask<Complicated>);
    static_assert(AutoBitmask<Mask>);
    static_assert(! AutoBitmask<Raw>);

}

void test_rs_core_enum_class() {

    static_assert(std::same_as<std::underlying_type_t<Simple>, int>);
    static_assert(std::same_as<std::underlying_type_t<Complicated>, unsigned>);
    static_assert(std::formattable<Simple, char>);
    static_assert(std::formattable<Complicated, char>);

    TEST_EQUAL(static_cast<int>(Simple::alpha),               0);
    TEST_EQUAL(static_cast<int>(Simple::bravo),               1);
    TEST_EQUAL(static_cast<int>(Simple::charlie),             2);
    TEST_EQUAL(static_cast<int>(Complicated::alpha_bravo),    0);
    TEST_EQUAL(static_cast<int>(Complicated::charlie_delta),  10);
    TEST_EQUAL(static_cast<int>(Complicated::echo_foxtrot),   11);
    TEST_EQUAL(static_cast<int>(Complicated::golf_hotel),     32);
    TEST_EQUAL(static_cast<int>(Complicated::india_juliet),   33);

    TEST_EQUAL(to_string(Simple::alpha),                  "alpha");
    TEST_EQUAL(to_string(Simple::bravo),                  "bravo");
    TEST_EQUAL(to_string(Simple::charlie),                "charlie");
    TEST_EQUAL(to_string(static_cast<Simple>(-1)),        "-1");
    TEST_EQUAL(to_string(static_cast<Simple>(3)),         "3");
    TEST_EQUAL(to_string(Complicated::alpha_bravo),       "alpha_bravo");
    TEST_EQUAL(to_string(Complicated::charlie_delta),     "charlie_delta");
    TEST_EQUAL(to_string(Complicated::echo_foxtrot),      "echo_foxtrot");
    TEST_EQUAL(to_string(Complicated::golf_hotel),        "golf_hotel");
    TEST_EQUAL(to_string(Complicated::india_juliet),      "india_juliet");
    TEST_EQUAL(to_string(static_cast<Complicated>(1)),    "1");
    TEST_EQUAL(to_string(static_cast<Complicated>(999)),  "999");

    TEST_EQUAL(std::format("{}", Simple::alpha),                  "alpha");
    TEST_EQUAL(std::format("{}", Simple::bravo),                  "bravo");
    TEST_EQUAL(std::format("{}", Simple::charlie),                "charlie");
    TEST_EQUAL(std::format("{}", static_cast<Simple>(-1)),        "-1");
    TEST_EQUAL(std::format("{}", static_cast<Simple>(3)),         "3");
    TEST_EQUAL(std::format("{}", Complicated::alpha_bravo),       "alpha_bravo");
    TEST_EQUAL(std::format("{}", Complicated::charlie_delta),     "charlie_delta");
    TEST_EQUAL(std::format("{}", Complicated::echo_foxtrot),      "echo_foxtrot");
    TEST_EQUAL(std::format("{}", Complicated::golf_hotel),        "golf_hotel");
    TEST_EQUAL(std::format("{}", Complicated::india_juliet),      "india_juliet");
    TEST_EQUAL(std::format("{}", static_cast<Complicated>(1)),    "1");
    TEST_EQUAL(std::format("{}", static_cast<Complicated>(999)),  "999");
    TEST_EQUAL(std::format("{:s}", Complicated::alpha_bravo),     "Alpha_bravo");
    TEST_EQUAL(std::format("{:s}", Complicated::charlie_delta),   "Charlie_delta");
    TEST_EQUAL(std::format("{:s}", Complicated::echo_foxtrot),    "Echo_foxtrot");
    TEST_EQUAL(std::format("{:s}", Complicated::golf_hotel),      "Golf_hotel");
    TEST_EQUAL(std::format("{:s}", Complicated::india_juliet),    "India_juliet");
    TEST_EQUAL(std::format("{:t}", Complicated::alpha_bravo),     "Alpha_Bravo");
    TEST_EQUAL(std::format("{:t}", Complicated::charlie_delta),   "Charlie_Delta");
    TEST_EQUAL(std::format("{:t}", Complicated::echo_foxtrot),    "Echo_Foxtrot");
    TEST_EQUAL(std::format("{:t}", Complicated::golf_hotel),      "Golf_Hotel");
    TEST_EQUAL(std::format("{:t}", Complicated::india_juliet),    "India_Juliet");
    TEST_EQUAL(std::format("{: }", Complicated::alpha_bravo),     "alpha bravo");
    TEST_EQUAL(std::format("{: }", Complicated::charlie_delta),   "charlie delta");
    TEST_EQUAL(std::format("{: }", Complicated::echo_foxtrot),    "echo foxtrot");
    TEST_EQUAL(std::format("{: }", Complicated::golf_hotel),      "golf hotel");
    TEST_EQUAL(std::format("{: }", Complicated::india_juliet),    "india juliet");
    TEST_EQUAL(std::format("{:s }", Complicated::alpha_bravo),    "Alpha bravo");
    TEST_EQUAL(std::format("{:s }", Complicated::charlie_delta),  "Charlie delta");
    TEST_EQUAL(std::format("{:s }", Complicated::echo_foxtrot),   "Echo foxtrot");
    TEST_EQUAL(std::format("{:s }", Complicated::golf_hotel),     "Golf hotel");
    TEST_EQUAL(std::format("{:s }", Complicated::india_juliet),   "India juliet");
    TEST_EQUAL(std::format("{:t }", Complicated::alpha_bravo),    "Alpha Bravo");
    TEST_EQUAL(std::format("{:t }", Complicated::charlie_delta),  "Charlie Delta");
    TEST_EQUAL(std::format("{:t }", Complicated::echo_foxtrot),   "Echo Foxtrot");
    TEST_EQUAL(std::format("{:t }", Complicated::golf_hotel),     "Golf Hotel");
    TEST_EQUAL(std::format("{:t }", Complicated::india_juliet),   "India Juliet");

    TEST_EQUAL(std::format("{}", enum_values(Simple{})),       "{alpha, bravo, charlie}");
    TEST_EQUAL(std::format("{}", enum_values(Complicated{})),  "{alpha_bravo, charlie_delta, echo_foxtrot, golf_hotel, india_juliet}");

}

void test_rs_core_enum_bitmask() {

    static_assert(std::same_as<std::underlying_type_t<Mask>, std::uint16_t>);
    static_assert(std::formattable<Mask, char>);

    TEST_EQUAL(static_cast<int>(Mask::none),     0);
    TEST_EQUAL(static_cast<int>(Mask::alpha),    1);
    TEST_EQUAL(static_cast<int>(Mask::bravo),    2);
    TEST_EQUAL(static_cast<int>(Mask::charlie),  4);

    TEST(! Mask::none);
    TEST(!! Mask::alpha);
    TEST(!! Mask::bravo);
    TEST(!! Mask::charlie);

    TEST_EQUAL(static_cast<int>(~ Mask::none),                                                 0xffff);
    TEST_EQUAL(static_cast<int>(~ Mask::alpha),                                                0xfffe);
    TEST_EQUAL(static_cast<int>(~ Mask::bravo),                                                0xfffd);
    TEST_EQUAL(static_cast<int>(~ Mask::charlie),                                              0xfffb);
    TEST_EQUAL(static_cast<int>(Mask::alpha | Mask::bravo),                                    3);
    TEST_EQUAL(static_cast<int>((Mask::alpha | Mask::bravo) & Mask::alpha),                    1);
    TEST_EQUAL(static_cast<int>((Mask::alpha | Mask::bravo) & Mask::charlie),                  0);
    TEST_EQUAL(static_cast<int>((Mask::alpha | Mask::bravo) ^ (Mask::bravo | Mask::charlie)),  5);

    TEST_EQUAL(to_string(Mask::none),                                 "none");
    TEST_EQUAL(to_string(Mask::alpha),                                "alpha");
    TEST_EQUAL(to_string(Mask::bravo),                                "bravo");
    TEST_EQUAL(to_string(Mask::charlie),                              "charlie");
    TEST_EQUAL(to_string(Mask::alpha | Mask::bravo),                  "alpha|bravo");
    TEST_EQUAL(to_string(Mask::alpha | Mask::charlie),                "alpha|charlie");
    TEST_EQUAL(to_string(Mask::bravo | Mask::charlie),                "bravo|charlie");
    TEST_EQUAL(to_string(Mask::alpha | Mask::bravo | Mask::charlie),  "alpha|bravo|charlie");
    TEST_EQUAL(to_string(static_cast<Mask>(0xffff)),                  "0xffff");

    TEST_EQUAL(std::format("{}", Mask::none),                                 "none");
    TEST_EQUAL(std::format("{}", Mask::alpha),                                "alpha");
    TEST_EQUAL(std::format("{}", Mask::bravo),                                "bravo");
    TEST_EQUAL(std::format("{}", Mask::charlie),                              "charlie");
    TEST_EQUAL(std::format("{}", Mask::alpha | Mask::bravo),                  "alpha|bravo");
    TEST_EQUAL(std::format("{}", Mask::alpha | Mask::charlie),                "alpha|charlie");
    TEST_EQUAL(std::format("{}", Mask::bravo | Mask::charlie),                "bravo|charlie");
    TEST_EQUAL(std::format("{}", Mask::alpha | Mask::bravo | Mask::charlie),  "alpha|bravo|charlie");
    TEST_EQUAL(std::format("{}", static_cast<Mask>(0xffff)),                  "0xffff");

    TEST_EQUAL(std::format("{}", enum_values(Mask{})), "{none, alpha, bravo, charlie}");

}
