#include <stdio.h> // printf

#include "../yacc_da.h"

typedef struct {
    int *items;
    size_t len;
    size_t capacity;
} DaInt;

void test_append_many(void)
{
    DaInt da1 = {0};
    YacDynamicArrayAppend(&da1, 1);
    YacDynamicArrayAppend(&da1, 2);

    DaInt da2 = {0};
    YacDynamicArrayAppend(&da2, 10);
    YacDynamicArrayAppend(&da2, 20);

    YacDynamicArrayAppendMany(&da1, da2.items, da2.len);

    assert(da1.items[0] == 1);
    assert(da1.items[1] == 2);
    assert(da1.items[2] == 10);
    assert(da1.items[3] == 20);

    YacDynamicArrayClearAndFree(da2);
    YacDynamicArrayClearAndFree(da1);
}

void test_remove_unordered(void)
{
    DaInt da1 = {0};
    YacDynamicArrayAppend(&da1, 1);
    YacDynamicArrayAppend(&da1, 2);
    YacDynamicArrayAppend(&da1, 3);
    YacDynamicArrayAppend(&da1, 4);
    YacDynamicArrayAppend(&da1, 5);
    YacDynamicArrayAppend(&da1, 6);

    YacDynamicArrayRemoveUnordered(&da1, 0);

    // for (size_t i = 0; i < da1.len; ++i)
    //     printf("%d\n", da1.items[i]);

    YacDynamicArrayClearAndFree(da1);
}

void test_pop(void)
{
    DaInt da1 = {0};
    int* p = YacDynamicArrayPop(&da1);
    // if (p == NULL) puts("NULL");

    YacDynamicArrayAppend(&da1, 11);
    p = YacDynamicArrayPop(&da1);
    // if (*p == 11) puts("11");

    YacDynamicArrayClearAndFree(da1);
}

void test_remove(void)
{
    DaInt da1 = {0};
    YacDynamicArrayAppend(&da1, 1);
    YacDynamicArrayAppend(&da1, 2);
    YacDynamicArrayAppend(&da1, 3);
    YacDynamicArrayAppend(&da1, 4);
    YacDynamicArrayAppend(&da1, 5);

    YacDynamicArrayRemove(&da1, 0);

    // for (size_t i = 0; i < da1.len; ++i)
    //     printf("%d\n", da1.items[i]);

    YacDynamicArrayClearAndFree(da1);
}

void test_get_last(void)
{
    DaInt da1 = {0};
    // printf("%d\n", YacDynamicArrayGetLast(&da1));
    // "da is empty"

    YacDynamicArrayAppend(&da1, 1);
    YacDynamicArrayAppend(&da1, 2);
    YacDynamicArrayAppend(&da1, 3);

    // printf("%d\n", YacDynamicArrayGetLast(&da1));

    YacDynamicArrayClearAndFree(da1);
}

void test_get_last_or_null(void)
{
    DaInt da1 = {0};
    int* p = YacDynamicArraygetLastOrNull(&da1);
    // if (p == NULL) puts("NULL");

    YacDynamicArrayAppend(&da1, 1);
    YacDynamicArrayAppend(&da1, 2);
    YacDynamicArrayAppend(&da1, 3);

    p = YacDynamicArraygetLastOrNull(&da1);
    // if (*p == 3) puts("3");

    YacDynamicArrayClearAndFree(da1);
}

void test_insert(void)
{
    DaInt da1 = {0};

    YacDynamicArrayAppend(&da1, 1);
    YacDynamicArrayAppend(&da1, 2);
    YacDynamicArrayAppend(&da1, 3);

    // YacDynamicArrayInsert(&da1, 0, 10);
    // for (size_t i = 0; i < da1.len; ++i)
    //     printf(" %d", da1.items[i]);
    // puts("");
    // 10 1 2 3

    // YacDynamicArrayInsert(&da1, 2, 100);
    // for (size_t i = 0; i < da1.len; ++i)
    //     printf(" %d", da1.items[i]);
    // puts("");
    // 10 1 100 2 3

    // YacDynamicArrayInsert(&da1, da1.len, 1000);
    // for (size_t i = 0; i < da1.len; ++i)
    //     printf(" %d", da1.items[i]);
    // puts("");
    // 10 1 100 2 3 1000

    // YacDynamicArrayInsert(&da1, 7, 10000);
    // out of range

    YacDynamicArrayClearAndFree(da1);
}

int main(void)
{
    test_append_many();
    test_remove_unordered();
    test_pop();
    test_remove();
    test_get_last();
    test_get_last_or_null();
    test_insert();

    return 0;
}
