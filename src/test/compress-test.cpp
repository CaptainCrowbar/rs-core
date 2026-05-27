#include "rs-core/compress.hpp"
#include "rs-core/random.hpp"
#include "rs-core/unit-test.hpp"
#include <cstddef>
#include <string>
#include <string_view>
#include <vector>

using namespace RS;

namespace {

    std::string generate_text(std::size_t length, Pcg& rng) {
        UniformInteger<int> chargen {'a', 'z'};
        std::string str(length, '\0');
        for (auto& c: str) {
            c = static_cast<char>(chargen(rng));
        }
        return str;
    }

}

void test_rs_core_compress_single_block() {

    std::string original, compressed, decompressed;
    Pcg rng {42};
    Zlib z;
    Zlib::result res;

    TRY(z.encode(original, compressed));
    TRY(res = z.decode(compressed, decompressed));
    TEST_EQUAL(res.bytes_in, compressed.size());
    TEST_EQUAL(res.bytes_out, original.size());
    TEST_EQUAL(decompressed, original);

    compressed.clear();
    decompressed.clear();
    original = "Hello world";
    TRY(z.encode(original, compressed));
    TRY(res = z.decode(compressed, decompressed));
    TEST_EQUAL(res.bytes_in, compressed.size());
    TEST_EQUAL(res.bytes_out, original.size());
    TEST_EQUAL(decompressed, original);

    compressed.clear();
    decompressed.clear();
    original = generate_text(123'456, rng);
    TRY(z.encode(original, compressed));
    TRY(res = z.decode(compressed, decompressed));
    TEST_EQUAL(res.bytes_in, compressed.size());
    TEST_EQUAL(res.bytes_out, original.size());
    TEST(decompressed == original);

    compressed.clear();
    decompressed.clear();
    original = generate_text(5'678'999, rng);
    TRY(z.encode(original, compressed));
    TRY(res = z.decode(compressed, decompressed));
    TEST_EQUAL(res.bytes_in, compressed.size());
    TEST_EQUAL(res.bytes_out, original.size());
    TEST(decompressed == original);

}

void test_rs_core_compress_multiple_blocks() {

    std::vector<std::string> original (5);
    std::vector<std::string> decompressed (original.size());
    std::string compressed;
    std::vector<std::size_t> sizes;
    Pcg rng {42};
    Zlib z;
    Zlib::result res;

    for (auto& ori: original) {
        ori = generate_text(1'234'567, rng);
        TRY(res = z.encode(ori, compressed));
        sizes.push_back(res.bytes_out);
    }

    std::string_view view {compressed};

    for (auto i = 0uz; i < original.size(); ++i) {
        const auto& ori {original[i]};
        auto& dec {decompressed[i]};
        TRY(res = z.decode(view, dec));
        TEST_EQUAL(res.bytes_in, sizes[i]);
        TEST_EQUAL(res.bytes_out, ori.size());
        TEST(dec == ori);
        view = view.substr(res.bytes_in, npos);
    }

    TEST(view.empty());

}
