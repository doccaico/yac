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

void test_push_pop(void)
{

}

int main(void)
{
    test_init_deinit();
    test_push_pop();

    return 0;
}
