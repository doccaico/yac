#include <stdio.h> // printf

#define YACC_SV_IMPLEMENTATION
#include "../yacc_sv.h"

void test_sv_empty(void)
{
    StringView sv1 = sv_empty;

    assert(sv1.begin == 0);
    assert(sv1.len == 0);
}

void test_sv_from_cstr(void)
{
    StringView sv1 = sv_from_cstr("Hello");

    assert(sv1.len == 5);
    // printf(sv_farg "\n", sv_expand(sv1));
    // "Hello"
}

void test_sv_from_cstr_slice(void)
{
    StringView sv1 = sv_from_cstr_slice("0123456789", 5, 2);

    assert(sv1.len == 2);
    // printf(sv_farg "\n", sv_expand(sv1));
    // "56"
}

void test_sv_from_constant(void)
{
#define N "2244"
    StringView sv1 = sv_from_constant(N);

    assert(sv1.len == 4);
    // printf(sv_farg "\n", sv_expand(sv1));
    // "2244"
#undef N
}

void test_sv_slice(void)
{
    StringView sv1 = sv_from_cstr("xxyyzz");
    StringView sv2 = sv_slice(sv1, 2, 2);

    assert(sv2.begin == &"xxyyzz"[2]);
    assert(sv2.len == 2);

    // printf(sv_farg "\n", sv_expand(sv2));
    // "yy"
}

void test_sv_equals(void)
{
    {
        StringView sv1 = sv_from_cstr("song");
        StringView sv2 = sv_from_cstr("song");

        assert(sv_equals(&sv1, &sv2));
    }
    {
        StringView sv1 = sv_from_cstr("joe");
        StringView sv2 = sv_from_cstr("tommy");

        assert(!sv_equals(&sv1, &sv2));
    }

    {
        StringView sv1 = sv_from_cstr("song");
        StringView sv2 = sv_from_cstr("SonG");

        assert(sv_equals_icase(&sv1, &sv2));
    }
    {
        StringView sv1 = sv_from_cstr("joe");
        StringView sv2 = sv_from_cstr("toMMy");

        assert(!sv_equals_icase(&sv1, &sv2));
    }
}

void test_sv_starts_with_cstr(void)
{
    {
        StringView sv1 = sv_from_cstr("I'm Joe.");

        assert(sv_starts_with_cstr(&sv1, "I'm"));
        assert(!sv_starts_with_cstr(&sv1, "Z'm"));
    }
    {
        StringView sv1 = sv_from_cstr("I'm Joe.");

        assert(sv_starts_with_cstr_icase(&sv1, "i'M"));
        assert(!sv_starts_with_cstr_icase(&sv1, "z'M"));
    }
}

void test_sv_ends_with_cstr(void)
{
    {
        StringView sv1 = sv_from_cstr(">> Lisp");

        assert(sv_ends_with_cstr(&sv1, "Lisp"));
        assert(!sv_ends_with_cstr(&sv1, "Risp"));
    }
    {
        StringView sv1 = sv_from_cstr(">> Lisp");

        assert(sv_ends_with_cstr_icase(&sv1, "liSP"));
        assert(!sv_ends_with_cstr_icase(&sv1, "riSP"));
    }
}

void test_sv_strip(void)
{
    {
        StringView sv1 = sv_from_cstr("     House    !");
        sv_stripl(&sv1);

        // printf(sv_farg "\n", sv_expand(sv1));
        // "House    !"
    }
    {
        StringView sv1 = sv_from_cstr("!     House    ");
        sv_stripr(&sv1);

        // printf(sv_farg "\n", sv_expand(sv1));
        // "!     House"
    }
    {
        StringView sv1 = sv_from_cstr("    House    ");
        sv_strip(&sv1);

        // printf(sv_farg "\n", sv_expand(sv1));
        // "House"
    }
}

void test_sv_index_of(void)
{
    {
        StringView sv1 = sv_from_cstr("abcdefg");

        int i = sv_index_of(&sv1, 'f');
        assert(i == 5); // found

        i = sv_index_of(&sv1, 'z');
        assert(i == -1); // not found
    }
    {
        StringView sv1 = sv_from_cstr("aaabbbccc");

        int i = sv_last_index_of(&sv1, 'b');
        assert(i == 5); // found

        i = sv_last_index_of(&sv1, 'z');
        assert(i == -1); // not found
    }
    {
        StringView sv1 = sv_from_cstr("year month week");

        int i = sv_index_of_str(&sv1, "ar");
        assert(i == 2); // found

        i = sv_index_of_str(&sv1, "ween");
        assert(i == -1); // not found
    }
}

void test_sv_split(void)
{
    StringView sv1 = sv_from_cstr("year month week");

    StringView word = sv_split(&sv1, " ");

    // printf(sv_farg "\n", sv_expand(word));
    // "year"

    // printf(sv_farg "\n", sv_expand(sv1));
    // " month week"

    (void)word;
}

void test_sv_split_exclude_delim(void)
{
    StringView sv1 = sv_from_cstr("year month week");

    StringView word = sv_split_exclude_delim(&sv1, " ");

    // printf(sv_farg "\n", sv_expand(word));
    // "year"

    // printf(sv_farg "\n", sv_expand(sv1));
    // "month week"

    (void)word;
}

int main(void)
{
    test_sv_empty();
    test_sv_from_cstr();
    test_sv_from_cstr_slice();
    test_sv_from_constant();
    test_sv_slice();

    test_sv_equals();
    test_sv_starts_with_cstr();
    test_sv_ends_with_cstr();
    test_sv_strip();
    test_sv_index_of();
    test_sv_split();
    test_sv_split_exclude_delim();

    return 0;
}
