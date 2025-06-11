// #include <stdint.h>
#include <stdio.h>
// #include <stdlib.h>

#include "da.h"

typedef struct {
    int* items;
    size_t len;
    size_t capacity;
} DaInt;


void test_append_many(void)
{
    DaInt da1 = {0};
    da_append(&da1, 1);
    da_append(&da1, 2);

    DaInt da2 = {0};
    da_append(&da2, 10);
    da_append(&da2, 20);

    da_append_many(&da1, da2.items, da2.len);

    assert(da1.items[0] == 1);
    assert(da1.items[1] == 2);
    assert(da1.items[2] == 10);
    assert(da1.items[3] == 20);

    da_clear_and_free(da2);
    da_clear_and_free(da1);
}

void test_remove_unordered(void)
{
    DaInt da1 = {0};
    da_append(&da1, 1);
    da_append(&da1, 2);
    da_append(&da1, 3);
    da_append(&da1, 4);
    da_append(&da1, 5);
    da_append(&da1, 6);

    da_remove_unordered(&da1, 0);

    // for (size_t i = 0; i < da1.len; ++i)
    //     printf("%d\n", da1.items[i]);

    da_clear_and_free(da1);
}

void test_pop(void)
{
    DaInt da1 = {0};
    int* p = da_pop(&da1);
    // if (p == NULL) puts("NULL");

    da_append(&da1, 11);
    p = da_pop(&da1);
    // if (*p == 11) puts("11");

    da_clear_and_free(da1);
}

void test_remove(void)
{
    DaInt da1 = {0};
    da_append(&da1, 1);
    da_append(&da1, 2);
    da_append(&da1, 3);
    da_append(&da1, 4);
    da_append(&da1, 5);

    da_remove(&da1, 0);

    // for (size_t i = 0; i < da1.len; ++i)
    //     printf("%d\n", da1.items[i]);

    da_clear_and_free(da1);
}

void test_get_last(void)
{
    DaInt da1 = {0};
    // printf("%d\n", da_get_last(&da1));
    // "da is empty"

    da_append(&da1, 1);
    da_append(&da1, 2);
    da_append(&da1, 3);

    // printf("%d\n", da_get_last(&da1));

    da_clear_and_free(da1);
}

void test_get_last_or_null(void)
{
    DaInt da1 = {0};
    int* p = da_get_last_or_null(&da1);
    // if (p == NULL) puts("NULL");

    da_append(&da1, 1);
    da_append(&da1, 2);
    da_append(&da1, 3);

    p = da_get_last_or_null(&da1);
    // if (*p == 3) puts("3");

    da_clear_and_free(da1);
}

void test_insert(void)
{
    DaInt da1 = {0};

    da_append(&da1, 1);
    da_append(&da1, 2);
    da_append(&da1, 3);

    // da_insert(&da1, 0, 10);
    // for (size_t i = 0; i < da1.len; ++i)
    //     printf(" %d", da1.items[i]);
    // puts("");
    // // 10 1 2 3

    // da_insert(&da1, 2, 100);
    // for (size_t i = 0; i < da1.len; ++i)
    //     printf(" %d", da1.items[i]);
    // puts("");
    // // 10 1 100 2 3

    // da_insert(&da1, da1.len, 1000);
    // for (size_t i = 0; i < da1.len; ++i)
    //     printf(" %d", da1.items[i]);
    // puts("");
    // // 10 1 100 2 3 1000

    // da_insert(&da1, 7, 1000);
    // out of range

    da_clear_and_free(da1);
}

int main(void)
{
    test_append_many();
    test_remove_unordered();
    test_pop();
    test_remove();
    test_get_last();
    test_insert();

    return 0;
}
