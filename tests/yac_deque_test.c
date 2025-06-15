#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define YAC_DEQUE_IMPLEMENTATION
#include "../yac_deque.h"

// See more information.
// https://github.com/KaisenAmin/c_std/tree/main/deque

void test_init_deinit(void)
{
    YacDeque* deque = YacDequeInit(sizeof(int));
    YacDequeDeinit(deque); // or YacDequeDeinitExtra(deque);
}

void test_push_pop_on_stack(void)
{
    YacDeque* deque = YacDequeInit(sizeof(int));

    int a = 1, b = 2, c = 3, d = 4;

    YacDequePushFront(deque, &a);
    YacDequePushFront(deque, &b);
    YacDequePushFront(deque, &c);
    YacDequePushFront(deque, &d);

    YacDequePopFront(deque);

    int* val = YacDequeFront(deque);
    assert(*val == 3);

    YacDequeDeinit(deque); // use YacDequeDeinit on stack
}

void test_push_pop_on_heap(void)
{
    YacDeque* deque = YacDequeInit(sizeof(int));

    int* a = malloc(sizeof(int));
    int* b = malloc(sizeof(int));
    int* c = malloc(sizeof(int));
    int* d = malloc(sizeof(int));

    *a = 1, *b = 2, *c = 3, *d = 4;

    YacDequePushBack(deque, a);
    YacDequePushBack(deque, b);
    YacDequePushBack(deque, c);
    YacDequePushBack(deque, d);

    YacDequePopBack(deque);

    int* val;
    val= YacDequeBack(deque);
    assert(*val == 3);
    val= YacDequeFront(deque);
    assert(*val == 1);

    YacDequeDeinitExtra(deque); // use YacDequeDeinitExtra on heap
}

int main(void)
{
    test_init_deinit();
    test_push_pop_on_stack();
    test_push_pop_on_heap();

    return 0;
}
