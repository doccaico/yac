#include <stdio.h> // printf

#define YAC_STRING_VIEW_IMPLEMENTATION
#include "../yac_string_view.h"

void test_empty(void)
{
    YacStringView sv1 = YacStringViewEmpty;

    assert(sv1.begin == 0);
    assert(sv1.len == 0);
}

void test_from_cstr(void)
{
    YacStringView sv1 = YacStringViewFromCstr("Hello");

    assert(sv1.len == 5);
    // printf(YacStringViewFarg "\n", YacStringViewExpand(sv1));
    // "Hello"
}

void test_from_cstr_slice(void)
{
    YacStringView sv1 = YacStringViewFromCstrSlice("0123456789", 5, 2);

    assert(sv1.len == 2);
    // printf(YacStringViewFarg "\n", YacStringViewExpand(sv1));
    // "56"
}

void test_from_constant(void)
{
#define N "2244"
    YacStringView sv1 = YacStringViewFromConstant(N);

    assert(sv1.len == 4);
    // printf(YacStringViewFarg "\n", YacStringViewExpand(sv1));
    // "2244"
#undef N
}

void test_slice(void)
{
    YacStringView sv1 = YacStringViewFromCstr("xxyyzz");
    YacStringView sv2 = YacStringViewSlice(sv1, 2, 2);

    assert(sv2.begin == &"xxyyzz"[2]);
    assert(sv2.len == 2);

    // printf(YacStringViewFarg "\n", YacStringViewExpand(sv2));
    // "yy"
}

void test_equals(void)
{
    {
        YacStringView sv1 = YacStringViewFromCstr("song");
        YacStringView sv2 = YacStringViewFromCstr("song");

        assert(YacStringViewEquals(&sv1, &sv2));
    }
    {
        YacStringView sv1 = YacStringViewFromCstr("joe");
        YacStringView sv2 = YacStringViewFromCstr("tommy");

        assert(!YacStringViewEquals(&sv1, &sv2));
    }

    {
        YacStringView sv1 = YacStringViewFromCstr("song");
        YacStringView sv2 = YacStringViewFromCstr("SonG");

        assert(YacStringViewEqualsIcase(&sv1, &sv2));
    }
    {
        YacStringView sv1 = YacStringViewFromCstr("joe");
        YacStringView sv2 = YacStringViewFromCstr("toMMy");

        assert(!YacStringViewEqualsIcase(&sv1, &sv2));
    }
}

void test_starts_with_cstr(void)
{
    {
        YacStringView sv1 = YacStringViewFromCstr("I'm Joe.");

        assert(YacStringViewStartsWithCstr(&sv1, "I'm"));
        assert(!YacStringViewStartsWithCstr(&sv1, "Z'm"));
    }
    {
        YacStringView sv1 = YacStringViewFromCstr("I'm Joe.");

        assert(YacStringViewStartsWithCstrIcase(&sv1, "i'M"));
        assert(!YacStringViewStartsWithCstrIcase(&sv1, "z'M"));
    }
}

void test_ends_with_cstr(void)
{
    {
        YacStringView sv1 = YacStringViewFromCstr(">> Lisp");

        assert(YacStringViewEndsWithCstr(&sv1, "Lisp"));
        assert(!YacStringViewEndsWithCstr(&sv1, "Risp"));
    }
    {
        YacStringView sv1 = YacStringViewFromCstr(">> Lisp");

        assert(YacStringViewEndsWithCstrIcase(&sv1, "liSP"));
        assert(!YacStringViewEndsWithCstrIcase(&sv1, "riSP"));
    }
}

void test_strip(void)
{
    {
        YacStringView sv1 = YacStringViewFromCstr("     House    !");
        YacStringViewStripL(&sv1);

        // printf(YacStringViewFarg "\n", YacStringViewExpand(sv1));
        // "House    !"
    }
    {
        YacStringView sv1 = YacStringViewFromCstr("!     House    ");
        YacStringViewStripR(&sv1);

        // printf(YacStringViewFarg "\n", YacStringViewExpand(sv1));
        // "!     House"
    }
    {
        YacStringView sv1 = YacStringViewFromCstr("    House    ");
        YacStringViewStrip(&sv1);

        // printf(YacStringViewFarg "\n", YacStringViewExpand(sv1));
        // "House"
    }
}

void test_index_of(void)
{
    {
        YacStringView sv1 = YacStringViewFromCstr("abcdefg");

        int i = YacStringViewIndexOf(&sv1, 'f');
        assert(i == 5); // found

        i = YacStringViewIndexOf(&sv1, 'z');
        assert(i == -1); // not found
    }
    {
        YacStringView sv1 = YacStringViewFromCstr("aaabbbccc");

        int i = YacStringViewLastIndexOf(&sv1, 'b');
        assert(i == 5); // found

        i = YacStringViewLastIndexOf(&sv1, 'z');
        assert(i == -1); // not found
    }
    {
        YacStringView sv1 = YacStringViewFromCstr("year month week");

        int i = YacStringViewIndexOfCstr(&sv1, "ar");
        assert(i == 2); // found

        i = YacStringViewIndexOfCstr(&sv1, "ween");
        assert(i == -1); // not found
    }
}

void test_split(void)
{
    YacStringView sv1 = YacStringViewFromCstr("year month week");

    YacStringView word = YacStringViewSplit(&sv1, " ");

    // printf(YacStringViewFarg "\n", YacStringViewExpand(word));
    // "year"

    // printf(YacStringViewFarg "\n", YacStringViewExpand(sv1));
    // " month week"

    (void)word;
}

void test_split_exclude_delim(void)
{
    YacStringView sv1 = YacStringViewFromCstr("year month week");

    YacStringView word = YacStringViewSplitExcludeDelim(&sv1, " ");

    // printf(YacStringViewFarg "\n", YacStringViewExpand(word));
    // "year"

    // printf(YacStringViewFarg "\n", YacStringViewExpand(sv1));
    // "month week"

    (void)word;
}

int main(void)
{
    test_empty();
    test_from_cstr();
    test_from_cstr_slice();
    test_from_constant();
    test_slice();

    test_equals();
    test_starts_with_cstr();
    test_ends_with_cstr();
    test_strip();
    test_index_of();
    test_split();
    test_split_exclude_delim();

    return 0;
}
