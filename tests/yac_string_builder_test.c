#include <stdio.h> // printf

#define YAC_STRING_VIEW_IMPLEMENTATION
#include "../yac_string_view.h"

#define YAC_STRING_BUILDER_IMPLEMENTATION
#include "../yac_string_builder.h"

void test_expand_buffer(void)
{
    {
        YacStringBuilder sb1 = YacStringBuilderCreate(0);

        YacStringBuilderExpandBuffer(&sb1, 4);

        // printf("len: %zd\n", sb1.len);
        // printf("capacity: %zd\n", sb1.capacity);
        // len: 0
        // capacity: 8 (value of YAC_DYNAMIC_ARRAY_INIT_CAP)

        YacStringBuilderClearAndFree(sb1);
    }
    {
        YacStringBuilder sb1 = YacStringBuilderCreate(0);

        YacStringBuilderExpandBuffer(&sb1, 40);

        // printf("len: %zd\n", sb1.len);
        // printf("capacity: %zd\n", sb1.capacity);
        // len: 0
        // capacity: 64 (YAC_DYNAMIC_ARRAY_GROW_FACTOR = 2)

        YacStringBuilderClearAndFree(sb1);
    }
}

void test_append_rune(void)
{
    YacStringBuilder sb1 = YacStringBuilderCreate(0);

    for (int rune = 65; rune < 65 + 10; ++rune) {
        YacStringBuilderAppendRune(&sb1, rune);
    }
    // printf(YacStringBuilderFarg "\n", YacStringBuilderExpand(sb1));
    // "ABCDEFGHIJ"

    YacStringBuilderClearAndFree(sb1);
}

void test_append_sv(void)
{
    YacStringBuilder sb1 = YacStringBuilderCreate(0);

    YacStringView sv1 = YacStringViewFromCstr("year");
    YacStringView sv2 = YacStringViewFromCstr("month");
    YacStringView sv3 = YacStringViewFromCstr("week");

    YacStringBuilderAppendStringView(&sb1, &sv1);
    YacStringBuilderAppendRune(&sb1, ' ');
    YacStringBuilderAppendStringView(&sb1, &sv2);
    YacStringBuilderAppendRune(&sb1, ' ');
    YacStringBuilderAppendStringView(&sb1, &sv3);

    // printf(YacStringBuilderFarg "\n", YacStringBuilderExpand(sb1));
    // "year month week"

    YacStringBuilderClearAndFree(sb1);
}

void test_append_cstr(void)
{
    YacStringBuilder sb1 = YacStringBuilderCreate(0);

    YacStringBuilderAppendCstr(&sb1, "year");
    YacStringBuilderAppendRune(&sb1, ' ');
    YacStringBuilderAppendCstr(&sb1, "month");
    YacStringBuilderAppendRune(&sb1, ' ');
    YacStringBuilderAppendCstr(&sb1, "week");

    // printf(YacStringBuilderFarg "\n", YacStringBuilderExpand(sb1));
    // "year month week"

    YacStringBuilderClearAndFree(sb1);
}

void test_append_sb(void)
{
    YacStringBuilder sb1 = YacStringBuilderCreate(0);
    YacStringBuilderAppendCstr(&sb1, "I'm");

    YacStringBuilder sb2 = YacStringBuilderCreate(0);
    YacStringBuilderAppendCstr(&sb2, " Rob");

    YacStringBuilderAppendStringBuilder(&sb1, &sb2);

    // printf(YacStringBuilderFarg "\n", YacStringBuilderExpand(sb1));
    // "I'm Rob"

    // printf(YacStringBuilderFarg "\n", YacStringBuilderExpand(sb2));
    // " Rob"

    YacStringBuilderClearAndFree(sb2);
    YacStringBuilderClearAndFree(sb1);
}

void test_get_cstr(void)
{
    YacStringBuilder sb1 = YacStringBuilderCreate(0);
    YacStringBuilderAppendCstr(&sb1, "Rust");
    YacStringBuilderAppendCstr(&sb1, " and ");
    YacStringBuilderAppendCstr(&sb1, "Go");

    // printf("%s\n", YacStringBuilderGetCstr(&sb1));
    // "Rust and Go"

    YacStringBuilderClearAndFree(sb1);
}

void test_appendf(void)
{
    YacStringBuilder sb1 = YacStringBuilderCreate(0);
    YacStringBuilderAppendFormat(&sb1, "%s %s %s", "Rust", "and", "Go");

    // printf(YacStringBuilderFarg "\n", YacStringBuilderExpand(sb1));
    // "Rust and Go"

    YacStringBuilderClearAndFree(sb1);
}

int main(void)
{
    test_expand_buffer();
    test_append_rune();
    test_append_sv();
    test_append_cstr();
    test_append_sb();
    test_get_cstr();
    test_appendf();

    return 0;
}
