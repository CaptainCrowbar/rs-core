#include "rs-core/hash.hpp"
#include "rs-core/unit-test.hpp"
#include <array>
#include <cstdint>
#include <string>

using namespace RS;

void test_rs_core_hash_concepts() {

    static_assert(Hashable<int>);
    static_assert(Hashable<void*>);
    static_assert(Hashable<std::string>);
    static_assert(! Hashable<void>);
    static_assert(RegularHashable<int>);
    static_assert(RegularHashable<void*>);
    static_assert(RegularHashable<std::string>);
    static_assert(! RegularHashable<void>);

}

void test_rs_core_hash_kernighan() {

    std::string s;

    s = "";                    TEST_EQUAL(kernighan_hash(s.data(), s.size()), 0x0000'0000ul);
    s = "Hello world";         TEST_EQUAL(kernighan_hash(s.data(), s.size()), 0xce59'8aa4ul);
    s = "Goodnight moon";      TEST_EQUAL(kernighan_hash(s.data(), s.size()), 0x6758'daa6ul);
    s = "Here comes the sun";  TEST_EQUAL(kernighan_hash(s.data(), s.size()), 0xdda4'f4dcul);

}

void test_rs_core_hash_mix() {

    auto h = 0uz;

    TRY(h = hash_mix());                                 TEST_EQUAL(h, 0uz);
    TRY(h = hash_mix(42uz));                             TEST_EQUAL(h, 42uz);
    TRY(h = hash_mix(42uz, 86uz));                       TEST_EQUAL(h, 0x9e37'84b3uz);
    TRY(h = hash_mix(42uz, 86uz, 99uz));                 TEST_EQUAL(h, 0x28'cd91'0cbbuz);
    TRY(h = hash_mix(42uz, 86uz, 99uz, 666uz));          TEST_EQUAL(h, 0xa16'f84f'e2fauz);
    TRY(h = hash_mix(42uz, 86uz, 99uz, 666uz, 2501uz));  TEST_EQUAL(h, 0x2'8252'880b'd846uz);

}

void test_rs_core_hash_sip() {

    static const std::array<std::uint64_t, 64> expect_sip64 {

        0x726f'db47'dd0e'0e31ull,  0x74f8'39c5'93dc'67fdull,  0x0d6c'8009'd9a9'4f5aull,  0x8567'6696'd7fb'7e2dull,
        0xcf27'94e0'2771'87b7ull,  0x1876'5564'cd99'a68dull,  0xcbc9'466e'58fe'e3ceull,  0xab02'00f5'8b01'd137ull,
        0x93f5'f579'9a93'2462ull,  0x9e00'82df'0ba9'e4b0ull,  0x7a5d'bbc5'94dd'b9f3ull,  0xf4b3'2f46'226b'ada7ull,
        0x751e'8fbc'860e'e5fbull,  0x14ea'5627'c084'3d90ull,  0xf723'ca90'8e7a'f2eeull,  0xa129'ca61'49be'45e5ull,
        0x3f2a'cc7f'57c2'9bdbull,  0x699a'e9f5'2cbe'4794ull,  0x4bc1'b3f0'968d'd39cull,  0xbb6d'c91d'a779'61bdull,
        0xbed6'5cf2'1aa2'ee98ull,  0xd0f2'cbb0'2e3b'67c7ull,  0x9353'6795'e3a3'3e88ull,  0xa80c'038c'cd5c'cec8ull,
        0xb8ad'50c6'f649'af94ull,  0xbce1'92de'8a85'b8eaull,  0x17d8'35b8'5bbb'15f3ull,  0x2f2e'6163'076b'cfadull,
        0xde4d'aaac'a71d'c9a5ull,  0xa6a2'5066'8795'6571ull,  0xad87'a353'5c49'ef28ull,  0x32d8'92fa'd841'c342ull,
        0x7127'512f'72f2'7cceull,  0xa7f3'2346'f959'78e3ull,  0x12e0'b01a'bb05'1238ull,  0x15e0'34d4'0fa1'97aeull,
        0x314d'ffbe'0815'a3b4ull,  0x0279'90f0'2962'3981ull,  0xcadc'd4e5'9ef4'0c4dull,  0x9abf'd876'6a33'735cull,
        0x0e3e'a96b'5304'a7d0ull,  0xad0c'42d6'fc58'5992ull,  0x1873'06c8'9bc2'15a9ull,  0xd4a6'0abc'f379'2b95ull,
        0xf935'451d'e4f2'1df2ull,  0xa953'8f04'1975'5787ull,  0xdb9a'cddf'f56c'a510ull,  0xd06c'98cd'5c09'75ebull,
        0xe612'a3cb'9ecb'a951ull,  0xc766'e62c'fcad'af96ull,  0xee64'435a'9752'fe72ull,  0xa192'd576'b245'165aull,
        0x0a87'87bf'8ecb'74b2ull,  0x81b3'e73d'20b4'9b6full,  0x7fa8'220b'a3b2'eceaull,  0x2457'31c1'3ca4'2499ull,
        0xb78d'bfaf'3a8d'83bdull,  0xea1a'd565'322a'1a0bull,  0x60e6'1c23'a379'5013ull,  0x6606'd7e4'4628'2b93ull,
        0x6ca4'ecb1'5c5f'91e1ull,  0x9f62'6da1'5c96'25f3ull,  0xe51b'3860'8ef2'5f57ull,  0x958a'324c'eb06'4572ull,

    };

    std::array<std::uint8_t, 16> key;
    std::array<std::uint8_t, 64> in;

    for (auto i = 0uz; i < key.size(); ++i) {
        key[i] = static_cast<std::uint8_t>(i);
    }

    SipHash sip;
    std::uint64_t hash{};

    for (auto i = 0uz; i < in.size(); ++i) {
        in[i] = static_cast<std::uint8_t>(i);
        TRY(sip = SipHash(key.data()));
        TRY(hash = sip(in.data(), i));
        TEST_EQUAL(hash, expect_sip64[i]);
    }

}
