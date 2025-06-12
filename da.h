#ifndef DA_H_
#define DA_H_

#ifndef DA_ASSERT
#include <assert.h>
#define DA_ASSERT assert
#endif // DA_ASSERT

#ifndef DA_ASSERT
#include <assert.h>
#define DA_ASSERT assert
#endif // DA_ASSERT

#ifndef DA_REALLOC
#include <stdlib.h>
#define DA_REALLOC realloc
#endif // DA_REALLOC

#ifndef DA_FREE
#include <stdlib.h>
#define DA_FREE free
#endif // DA_FREE


#include <string.h> // memcpy


// Da (Dynamic array) works on any struct with *items, len and capacity fields

// Grow factor of the da.
#ifndef DA_GROW_FACTOR
#define DA_GROW_FACTOR 2
#endif

// Initial capacity of the da.
#ifndef DA_INIT_CAP
#define DA_INIT_CAP 8
#endif


#define da_reserve(da, expected_capacity)                                                  \
    do {                                                                                   \
        if ((expected_capacity) > (da)->capacity) {                                        \
            if ((da)->capacity == 0) {                                                     \
                (da)->capacity = DA_INIT_CAP;                                              \
            }                                                                              \
            while ((expected_capacity) > (da)->capacity) {                                 \
                (da)->capacity *= DA_GROW_FACTOR;                                          \
            }                                                                              \
            (da)->items = DA_REALLOC((da)->items, (da)->capacity * sizeof(*(da)->items));  \
            DA_ASSERT((da)->items != NULL && "could not allocate memory");                 \
        }                                                                                  \
    } while (0)

// Append an item to the da.
#define da_append(da, item)                 \
    do {                                    \
        da_reserve((da), (da)->len + 1);    \
        (da)->items[(da)->len++] = (item);  \
    } while (0)

// Insert item at index i.
#define da_insert(da, i, item)                             \
    do {                                                   \
        DA_ASSERT((i) < (da)->len + 1 && "out of range");  \
        da_reserve((da), (da)->len + 1);                   \
        for (size_t _i = (da)->len; _i > (i); --_i) {      \
            (da)->items[_i] = (da)->items[_i - 1];         \
        }                                                  \
        (da)->items[i] = (item);                           \
        (da)->len += 1;                                    \
    } while (0)

// Invalidates all element pointers.
#define da_clear_and_free(da)                                 \
    do {                                                      \
        DA_ASSERT((da).items != NULL && "da.items is NULL");  \
        DA_FREE((da).items);                                  \
        (da).items = NULL;                                    \
        (da).len = 0;                                         \
        (da).capacity = 0;                                    \
    } while (0)

// Invalidates all element pointers, but retaining capacity.
#define da_clear_retaining_capacity(da) (da).len = 0

// Append several items to the da.
#define da_append_many(da, new_items, new_items_len)                                         \
    do {                                                                                     \
        da_reserve((da), (da)->len + (new_items_len));                                       \
        memcpy((da)->items + (da)->len, (new_items), (new_items_len)*sizeof(*(da)->items));  \
        (da)->len += (new_items_len);                                                        \
    } while (0)

// #define da_resize(da, new_len)      \
//     do {                            \
//         da_reserve((da), new_len);  \
//         (da)->len = (new_len);      \
//     } while (0)

// Returns the last element from the da. Asserts that the da is not empty.
#define da_get_last(da) (da)->items[(DA_ASSERT((da)->len > 0 && "da->items is empty"), (da)->len-1)]

// Returns the last element from the da, or null if da is empty.
#define da_get_last_or_null(da) ((da)->len == 0) ? NULL : &(da)->items[(da)->len-1]

// Remove and return the last element from the da, or return null if da is empty.
// Invalidates element pointers to the removed element, if any.
#define da_pop(da) (((da)->len == 0) ? NULL : &(da)->items[--((da)->len)])

#define da_remove(da, i)                                                                                \
    do {                                                                                                \
        DA_ASSERT((i) < (da)->len && "out of range");                                                   \
        memmove((da)->items + (i), (da)->items + (i) + 1, ((da)->len - (i) - 1)*sizeof(*(da)->items));  \
        (da)->len--;                                                                                    \
    } while(0)

// Also known as: swap remove
#define da_remove_unordered(da, i)                     \
    do {                                               \
        DA_ASSERT((i) < (da)->len && "out of range");  \
        (da)->items[i] = (da)->items[--(da)->len];     \
    } while(0)


#endif // DA_H_
