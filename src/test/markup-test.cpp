#include "rs-core/markup.hpp"
#include "rs-core/io.hpp"
#include "rs-core/unit-test.hpp"
#include <filesystem>
#include <string>

using namespace RS;

namespace fs = std::filesystem;

void test_rs_core_markup_xml() {

    static const fs::path test_file{"__test_file__"};

    static const std::string expected =
        "<h1>Header</h1>\n"
        "<br/>\n"
        "<ul>\n"
        "<li><code>alpha</code></li>\n"
        "<li><code>bravo</code></li>\n"
        "<li><code>charlie</code></li>\n"
        "</ul>\n";

    {
        std::string out;
        {
            {
                Xtag h1;
                TRY(h1 = Xtag("<h1>\n", out));
                out += "Header";
            }
            Xtag br;
            TRY(br = Xtag("<br/>\n", out));
            {
                Xtag ul;
                TRY(ul = Xtag("<ul>\n\n", out));
                for (auto item: {"alpha", "bravo", "charlie"}) {
                    Xtag li, code;
                    TRY(li = Xtag("<li>\n", out));
                    TRY(code = Xtag("<code>", out));
                    out += item;
                }
            }
        }
        TEST_EQUAL(out, expected);
    }

    {
        Cstdio out(test_file, IO::write_only);
        {
            Xtag h1;
            TRY(h1 = Xtag("<h1>\n", out));
            out.write_str("Header");
        }
        Xtag br;
        TRY(br = Xtag("<br/>\n", out));
        {
            Xtag ul;
            TRY(ul = Xtag("<ul>\n\n", out));
            for (auto item: {"alpha", "bravo", "charlie"}) {
                Xtag li, code;
                TRY(li = Xtag("<li>\n", out));
                TRY(code = Xtag("<code>", out));
                out.write_str(item);
            }
        }
    }

    {
        std::string str;
        Cstdio in{test_file};
        TRY(str = in.read_all());
        TEST_EQUAL(str, expected);
    }

    fs::remove(test_file);
    TEST(! fs::exists(test_file));

    {
        std::string out;
        {
            {
                Xtag h1("h1\n", out);
                out += "Header";
            }
            Xtag br("br/\n", out);
            {
                Xtag ul("ul\n\n", out);
                for (auto item: {"alpha", "bravo", "charlie"}) {
                    Xtag li("li\n", out);
                    Xtag code("code", out);
                    out += item;
                }
            }
        }
        TEST_EQUAL(out, expected);
    }

    {
        std::string out;
        {
            Xtag img("img", out);
            out += "hello";
        }
        TEST_EQUAL(out, "<img>hello</img>");
    }

    {
        std::string out;
        {
            Xtag img("img/", out);
            out += "hello";
        }
        TEST_EQUAL(out, "<img/>hello");
    }

}

void test_rs_core_markup_html() {

    {
        std::string out;
        {
            Htag img("img", out);
            out += "hello";
        }
        TEST_EQUAL(out, "<img>hello");
    }

    {
        std::string out;
        {
            Htag img("img/", out);
            out += "hello";
        }
        TEST_EQUAL(out, "<img/>hello");
    }

}
