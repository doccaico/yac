#include <stdio.h> // printf

#include "../yacc_da.h"

#define YACC_SV_IMPLEMENTATION
#include "../yacc_sv.h"

#define YACC_SB_IMPLEMENTATION
#include "../yacc_sb.h"

void test_sb_expand_buffer(void)
{
    {
        StringBuilder sb1 = sb_create(0);

        sb_expand_buffer(&sb1, 4);

        // printf("len: %zd\n", sb1.len);
        // printf("capacity: %zd\n", sb1.capacity);
        // len: 0
        // capacity: 8 (value of DA_INIT_CAP)

        sb_clear_and_free(sb1);
    }
    {
        StringBuilder sb1 = sb_create(0);

        sb_expand_buffer(&sb1, 40);

        // printf("len: %zd\n", sb1.len);
        // printf("capacity: %zd\n", sb1.capacity);
        // len: 0
        // capacity: 64 (DA_GROW_FACTOR = 2)

        sb_clear_and_free(sb1);
    }
}

void test_sb_append_rune(void)
{
    StringBuilder sb1 = sb_create(0);

    for (int rune = 65; rune < 65 + 10; ++rune) {
        sb_append_rune(&sb1, rune);
    }
    // printf(sb_farg "\n", sb_expand(sb1));
    // "ABCDEFGHIJ"

    sb_clear_and_free(sb1);
}

void test_sb_append_sv(void)
{
    StringBuilder sb1 = sb_create(0);

    StringView sv1 = sv_from_cstr("year");
    StringView sv2 = sv_from_cstr("month");
    StringView sv3 = sv_from_cstr("week");

    sb_append_sv(&sb1, &sv1);
    sb_append_rune(&sb1, ' ');
    sb_append_sv(&sb1, &sv2);
    sb_append_rune(&sb1, ' ');
    sb_append_sv(&sb1, &sv3);

    // printf(sb_farg "\n", sb_expand(sb1));
    // "year month week"

    sb_clear_and_free(sb1);
}

void test_sb_append_cstr(void)
{
    StringBuilder sb1 = sb_create(0);

    sb_append_cstr(&sb1, "year");
    sb_append_rune(&sb1, ' ');
    sb_append_cstr(&sb1, "month");
    sb_append_rune(&sb1, ' ');
    sb_append_cstr(&sb1, "week");

    // printf(sb_farg "\n", sb_expand(sb1));
    // "year month week"

    sb_clear_and_free(sb1);
}

void test_sb_append_sb(void)
{
    StringBuilder sb1 = sb_create(0);
    sb_append_cstr(&sb1, "I'm");

    StringBuilder sb2 = sb_create(0);
    sb_append_cstr(&sb2, " Rob");

    sb_append_sb(&sb1, &sb2);

    // printf(sb_farg "\n", sb_expand(sb1));
    // "I'm Rob"

    // printf(sb_farg "\n", sb_expand(sb2));
    // " Rob"

    sb_clear_and_free(sb2);
    sb_clear_and_free(sb1);
}

void test_sb_get_cstr(void)
{
    StringBuilder sb1 = sb_create(0);
    sb_append_cstr(&sb1, "Rust");
    sb_append_cstr(&sb1, " and ");
    sb_append_cstr(&sb1, "Go");

    // printf("%s\n", sb_get_cstr(&sb1));
    // "Rust and Go"

    sb_clear_and_free(sb1);
}

void test_sb_appendf(void)
{
    StringBuilder sb1 = sb_create(0);
    sb_appendf(&sb1, "%s %s %s", "Rust", "and", "Go");

    // printf(sb_farg "\n", sb_expand(sb1));
    // "Rust and Go"

    sb_clear_and_free(sb1);
}

int main(void)
{
    test_sb_expand_buffer();
    test_sb_append_rune();
    test_sb_append_sv();
    test_sb_append_cstr();
    test_sb_append_sb();
    test_sb_get_cstr();
    test_sb_appendf();

    return 0;
}
