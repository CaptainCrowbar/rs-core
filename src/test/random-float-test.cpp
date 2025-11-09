#include "rs-core/random.hpp"
#include "rs-core/unit-test.hpp"
#include <cmath>
#include <random>

using namespace RS;

void test_rs_core_random_uniform_real() {

    static constexpr auto n = 10'000;
    static constexpr auto nd = static_cast<double>(n);
    static constexpr auto nf = static_cast<float>(n);

    {

        std::minstd_rand rng(42);
        UniformReal<double> dist;

        TEST_EQUAL(dist.min(), 0.0);
        TEST_EQUAL(dist.max(), 1.0);

        auto expect_mean = 0.5 * (dist.min() + dist.max());
        auto expect_sd = (dist.max() - dist.min()) / std::sqrt(12.0);
        auto tolerance = (dist.max() - dist.min()) / std::sqrt(nd);
        auto sum = 0.0;
        auto sum2 = 0.0;
        double x{};

        for (auto i = 0; i < n; ++i) {
            TRY(x = dist(rng));
            TEST(x >= dist.min());
            TEST(x <= dist.max());
            sum += x;
            sum2 += x * x;
        }

        auto mean = sum / nd;
        auto sd = std::sqrt((nd / (nd - 1.0)) * (sum2 / nd - mean * mean));

        TEST_NEAR(mean, expect_mean, tolerance);
        TEST_NEAR(sd, expect_sd, tolerance);

    }

    {

        Pcg rng(42);
        UniformReal<double> dist(10.0);

        TEST_EQUAL(dist.min(), 0.0);
        TEST_EQUAL(dist.max(), 10.0);

        auto expect_mean = 0.5 * (dist.min() + dist.max());
        auto expect_sd = (dist.max() - dist.min()) / std::sqrt(12.0);
        auto tolerance = (dist.max() - dist.min()) / std::sqrt(nd);
        auto sum = 0.0;
        auto sum2 = 0.0;
        double x{};

        for (auto i = 0; i < n; ++i) {
            TRY(x = dist(rng));
            TEST(x >= dist.min());
            TEST(x <= dist.max());
            sum += x;
            sum2 += x * x;
        }

        auto mean = sum / nd;
        auto sd = std::sqrt((nd / (nd - 1.0)) * (sum2 / nd - mean * mean));

        TEST_NEAR(mean, expect_mean, tolerance);
        TEST_NEAR(sd, expect_sd, tolerance);

    }

    {

        Pcg rng(42);
        UniformReal<double> dist(100.0, -100.0);

        TEST_EQUAL(dist.min(), -100.0);
        TEST_EQUAL(dist.max(), 100.0);

        auto expect_mean = 0.5 * (dist.min() + dist.max());
        auto expect_sd = (dist.max() - dist.min()) / std::sqrt(12.0);
        auto tolerance = (dist.max() - dist.min()) / std::sqrt(nd);
        auto sum = 0.0;
        auto sum2 = 0.0;
        double x{};

        for (auto i = 0; i < n; ++i) {
            TRY(x = dist(rng));
            TEST(x >= dist.min());
            TEST(x <= dist.max());
            sum += x;
            sum2 += x * x;
        }

        auto mean = sum / nd;
        auto sd = std::sqrt((nd / (nd - 1.0)) * (sum2 / nd - mean * mean));

        TEST_NEAR(mean, expect_mean, tolerance);
        TEST_NEAR(sd, expect_sd, tolerance);

    }

    {

        Pcg rng(42);
        UniformReal<float> dist(100.0f, -100.0f);

        TEST_EQUAL(dist.min(), -100.0);
        TEST_EQUAL(dist.max(), 100.0);

        auto expect_mean = 0.5f * (dist.min() + dist.max());
        auto expect_sd = (dist.max() - dist.min()) / std::sqrt(12.0f);
        auto tolerance = (dist.max() - dist.min()) / std::sqrt(nf);
        auto sum = 0.0f;
        auto sum2 = 0.0f;
        float x{};

        for (auto i = 0; i < n; ++i) {
            TRY(x = dist(rng));
            TEST(x >= dist.min());
            TEST(x <= dist.max());
            sum += x;
            sum2 += x * x;
        }

        auto mean = sum / nf;
        auto sd = std::sqrt((nf / (nf - 1.0f)) * (sum2 / nf - mean * mean));

        TEST_NEAR(mean, expect_mean, tolerance);
        TEST_NEAR(sd, expect_sd, tolerance);

    }

}

void test_rs_core_random_normal_distribution() {

    static constexpr auto n = 1'000'000;
    static constexpr auto nd = static_cast<double>(n);

    {

        std::minstd_rand rng(42);
        NormalDistribution<double> dist;

        TEST_EQUAL(dist.mean(), 0.0);
        TEST_EQUAL(dist.sd(), 1.0);

        auto tolerance = 5.0 * dist.sd() / std::sqrt(nd);
        auto sum = 0.0;
        auto sum2 = 0.0;
        double x{};

        for (auto i = 0; i < n; ++i) {
            TRY(x = dist(rng));
            TEST(x >= dist.min());
            TEST(x <= dist.max());
            sum += x;
            sum2 += x * x;
        }

        auto mean = sum / nd;
        auto sd = std::sqrt((nd / (nd - 1.0)) * (sum2 / nd - mean * mean));

        TEST_NEAR(mean, dist.mean(), tolerance);
        TEST_NEAR(sd, dist.sd(), tolerance);

    }

    {

        std::minstd_rand rng(42);
        NormalDistribution<double> dist(100, 50);

        TEST_EQUAL(dist.mean(), 100.0);
        TEST_EQUAL(dist.sd(), 50.0);

        auto tolerance = 5.0 * dist.sd() / std::sqrt(nd);
        auto sum = 0.0;
        auto sum2 = 0.0;
        double x{};

        for (auto i = 0; i < n; ++i) {
            TRY(x = dist(rng));
            TEST(x >= dist.min());
            TEST(x <= dist.max());
            sum += x;
            sum2 += x * x;
        }

        auto mean = sum / nd;
        auto sd = std::sqrt((nd / (nd - 1.0)) * (sum2 / nd - mean * mean));

        TEST_NEAR(mean, dist.mean(), tolerance);
        TEST_NEAR(sd, dist.sd(), tolerance);

    }

}

void test_rs_core_random_normal_distribution_properties() {

    struct Sample { double z, pdf, cdf; };

    static constexpr Sample samples[] = {

        { -5.00,  0.00000'14867'20,  0.00000'02866'52 },
        { -4.75,  0.00000'50295'07,  0.00000'10170'83 },
        { -4.50,  0.00001'59837'41,  0.00000'33976'73 },
        { -4.25,  0.00004'77186'37,  0.00001'06885'26 },
        { -4.00,  0.00013'38302'26,  0.00003'16712'42 },
        { -3.75,  0.00035'25956'82,  0.00008'84172'85 },
        { -3.50,  0.00087'26826'95,  0.00023'26290'79 },
        { -3.25,  0.00202'90480'57,  0.00057'70250'42 },
        { -3.00,  0.00443'18484'12,  0.00134'98980'32 },
        { -2.75,  0.00909'35625'02,  0.00297'97632'35 },
        { -2.50,  0.01752'83004'94,  0.00620'96653'26 },
        { -2.25,  0.03173'96518'36,  0.01222'44726'55 },
        { -2.00,  0.05399'09665'13,  0.02275'01319'48 },
        { -1.75,  0.08627'73188'27,  0.04005'91568'64 },
        { -1.50,  0.12951'75956'66,  0.06680'72012'69 },
        { -1.25,  0.18264'90853'89,  0.10564'97736'67 },
        { -1.00,  0.24197'07245'19,  0.15865'52539'31 },
        { -0.75,  0.30113'74321'55,  0.22662'73523'77 },
        { -0.50,  0.35206'53267'64,  0.30853'75387'26 },
        { -0.25,  0.38666'81168'03,  0.40129'36743'17 },
        { 0.00,   0.39894'22804'01,  0.50000'00000'00 },
        { 0.25,   0.38666'81168'03,  0.59870'63256'83 },
        { 0.50,   0.35206'53267'64,  0.69146'24612'74 },
        { 0.75,   0.30113'74321'55,  0.77337'26476'23 },
        { 1.00,   0.24197'07245'19,  0.84134'47460'69 },
        { 1.25,   0.18264'90853'89,  0.89435'02263'33 },
        { 1.50,   0.12951'75956'66,  0.93319'27987'31 },
        { 1.75,   0.08627'73188'27,  0.95994'08431'36 },
        { 2.00,   0.05399'09665'13,  0.97724'98680'52 },
        { 2.25,   0.03173'96518'36,  0.98777'55273'45 },
        { 2.50,   0.01752'83004'94,  0.99379'03346'74 },
        { 2.75,   0.00909'35625'02,  0.99702'02367'65 },
        { 3.00,   0.00443'18484'12,  0.99865'01019'68 },
        { 3.25,   0.00202'90480'57,  0.99942'29749'58 },
        { 3.50,   0.00087'26826'95,  0.99976'73709'21 },
        { 3.75,   0.00035'25956'82,  0.99991'15827'15 },
        { 4.00,   0.00013'38302'26,  0.99996'83287'58 },
        { 4.25,   0.00004'77186'37,  0.99998'93114'74 },
        { 4.50,   0.00001'59837'41,  0.99999'66023'27 },
        { 4.75,   0.00000'50295'07,  0.99999'89829'17 },
        { 5.00,   0.00000'14867'20,  0.99999'97133'48 },

    };

    NormalDistribution<double> norm;

    for (auto [z,pdf,cdf]: samples) {
        TEST_NEAR(norm.pdf(z),          pdf,      1e-10);
        TEST_NEAR(norm.cdf(z),          cdf,      1e-10);
        TEST_NEAR(norm.ccdf(z),         1 - cdf,  1e-10);
        TEST_NEAR(norm.quantile(cdf),   z,        1e-6);
        TEST_NEAR(norm.cquantile(cdf),  - z,      1e-6);
    }

}
