// ISC License (ISC)
//
// Original work Copyright (C) 2023 Amin Tahmasebi
//   :: https://github.com/KaisenAmin/c_std
// Modified work Copyright (C) 2025 Doccaico
//   :: https://github.com/doccaico/yac
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
// WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
// ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
// ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR
// IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.


#ifndef YAC_DEQUE_H_
#define YAC_DEQUE_H_

#include <stdbool.h> // bool

#if defined(_MSC_VER) && !defined(ssize_t)
  // ssize_t is not standard, only posix which is not supported by MSVC
  #define ssize_t ptrdiff_t
#endif

#ifndef YAC_DEQUE_API
#ifdef YAC_DEQUE_STATIC
#define YAC_DEQUE_API static
#else
#define YAC_DEQUE_API extern
#endif // YAC_DEQUE_STATIC
#endif // YAC_DEQUE_API

#ifndef YAC_DEQUE_DEFAULT_BLOCK_SIZE
#define YAC_DEQUE_DEFAULT_BLOCK_SIZE 64
#endif


typedef struct YacDeque YacDeque;
typedef struct YacDequeIterator YacDequeIterator;

struct YacDequeIterator {
    const YacDeque* deque;
    bool isReverse;
    // Iterator state and functions
    void* current;        // Pointer to the current element
    size_t blockIndex;    // Current block index
    size_t indexInBlock;  // Index within the current block
};

struct YacDeque {
    size_t itemSize;
    size_t blockSize;   // Size of each block
    size_t size;        // Total number of elements
    size_t blockCount;  // Number of blocks
    size_t frontIndex;  // Index of the front element
    ssize_t backIndex;  // Index of the back element
    void*** blocks;     // Pointer to blocks of elements
};


YAC_DEQUE_API YacDeque* YacDequeInit(size_t itemSize);
// Core YacDeque Functions

YAC_DEQUE_API size_t YacDequeLength(const YacDeque* deque);
YAC_DEQUE_API size_t YacDequeMaxSize(const YacDeque* deque);

// Additional YacDeque Functions
YAC_DEQUE_API void YacDequePushFront(YacDeque* deque, void* item);
YAC_DEQUE_API void YacDequePushBack(YacDeque* deque, void* item);
YAC_DEQUE_API void YacDequePopFront(YacDeque* deque);
YAC_DEQUE_API void YacDequePopBack(YacDeque* deque);
YAC_DEQUE_API void YacDequeShrinkToFit(YacDeque* deque);
YAC_DEQUE_API void YacDequeInsert(YacDeque* deque, size_t index, void* item);
YAC_DEQUE_API void YacDequeErase(YacDeque* deque, size_t index);
YAC_DEQUE_API void YacDequereSize(YacDeque* deque, size_t newSize);
YAC_DEQUE_API void YacDequeSwap(YacDeque* deque, YacDeque* otherYacDeque);
YAC_DEQUE_API void YacDequeAssign(YacDeque* deque, size_t n, void* val, bool extra);
YAC_DEQUE_API void YacDequeEmplaceBack(YacDeque* deque, void* item);
YAC_DEQUE_API void YacDequeEmplaceFront(YacDeque* deque, void* item);
YAC_DEQUE_API void YacDequeEmplace(YacDeque* deque, size_t index, void* item);
YAC_DEQUE_API void YacDequeIteratorIncrement(YacDequeIterator* it);
YAC_DEQUE_API void YacDequeIteratorDecrement(YacDequeIterator* it);
YAC_DEQUE_API void YacDequeDeinit(YacDeque* deque);
YAC_DEQUE_API void YacDequeDeinitExtra(YacDeque* deque);


// Relational Operators
YAC_DEQUE_API bool YacDequeIsEqual(const YacDeque* deque1, const YacDeque* deque2);
YAC_DEQUE_API bool YacDequeIsLess(const YacDeque* deque1, const YacDeque* deque2);
YAC_DEQUE_API bool YacDequeIsGreater(const YacDeque* deque1, const YacDeque* deque2);
YAC_DEQUE_API bool YacDequeIsNotEqual(const YacDeque* deque1, const YacDeque* deque2);
YAC_DEQUE_API bool YacDequeIsLessOrEqual(const YacDeque* deque1, const YacDeque* deque2);
YAC_DEQUE_API bool YacDequeIsGreaterOrEqual(const YacDeque* deque1, const YacDeque* deque2);
YAC_DEQUE_API bool YacDequeIteratorEquals(const YacDequeIterator* it1, const YacDequeIterator* it2);
YAC_DEQUE_API bool YacDequeEmpty(const YacDeque* deque);

// Iterator Functions
YAC_DEQUE_API YacDequeIterator YacDequeBegin(const YacDeque* deque);
YAC_DEQUE_API YacDequeIterator YacDequeEnd(const YacDeque* deque);
YAC_DEQUE_API YacDequeIterator YacDequeRbegin(const YacDeque* deque);
YAC_DEQUE_API YacDequeIterator YacDequeRend(const YacDeque* deque);

YAC_DEQUE_API YacDequeIterator YacDequeCbegin(const YacDeque* deque);
YAC_DEQUE_API YacDequeIterator YacDequeCend(const YacDeque* deque);
YAC_DEQUE_API YacDequeIterator YacDequeCrbegin(const YacDeque* deque);
YAC_DEQUE_API YacDequeIterator YacDequeCrend(const YacDeque* deque);

YAC_DEQUE_API void* YacDequeFront(const YacDeque* deque);
YAC_DEQUE_API void* YacDequeBack(const YacDeque* deque);
YAC_DEQUE_API void* YacDequeIteratorGet(const YacDequeIterator* it);
YAC_DEQUE_API void* YacDequeAt(const YacDeque* deque, size_t index);

#endif // YAC_DEQUE_H_


//
// IMPLEMENTATION
//

#ifdef YAC_DEQUE_IMPLEMENTATION


#include <stdlib.h> // malloc, realloc, free
#include <string.h>
#include <stdint.h> // SIZE_MAX

#ifndef YAC_DEQUE_MALLOC
#define YAC_DEQUE_MALLOC malloc
#endif

#ifndef YAC_DEQUE_REALLOC
#define YAC_DEQUE_REALLOC realloc
#endif

#ifndef YAC_DEQUE_FREE
#define YAC_DEQUE_FREE free
#endif


//
// Definition for internal operations
//

static void YacDequeDeinitExtra_(YacDeque* deque);
static void YacDequeDeinit_(YacDeque* deque);


//
// Implementation for the exported operations
//

// @brief Creates a new deque with a specified item size.
//
// This function initializes a new deque with the given item size. It allocates memory for the deque structure
// and sets up the initial block of memory for storing elements. The front and back indices are initialized to
// the middle of the block to allow for efficient push operations at both ends.
//
// @param itemSize The size of each item in the deque. Must be greater than 0.
// @return Pointer to the newly created deque.
// @warning The function will exit the program if memory allocation fails or if itemSize is zero.
YAC_DEQUE_API YacDeque* YacDequeInit(size_t itemSize)
{
    if (itemSize == 0) {
        return NULL;
    }

    // Allocate memory for the YacDeque structure
    YacDeque* deque = YAC_DEQUE_MALLOC(sizeof(YacDeque));
    if (!deque) {
        return NULL;
    }

    // Initial values for the YacDeque structure
    deque->blockSize = YAC_DEQUE_DEFAULT_BLOCK_SIZE;
    deque->size = 0;
    deque->blockCount = 1; // Start with one block
    deque->frontIndex = YAC_DEQUE_DEFAULT_BLOCK_SIZE / 2; // Middle of the block
    deque->backIndex = deque->frontIndex - 1;
    deque->itemSize = itemSize;

    // Allocate memory for the blocks array
    deque->blocks = YAC_DEQUE_MALLOC(sizeof(void**) * deque->blockCount);
    if (!deque->blocks) {
        YAC_DEQUE_FREE(deque);
        return NULL;
    }

    // Allocate memory for the first block
    deque->blocks[0] = YAC_DEQUE_MALLOC(sizeof(void*) * YAC_DEQUE_DEFAULT_BLOCK_SIZE);
    if (!deque->blocks[0]) {
        YAC_DEQUE_FREE(deque->blocks);
        YAC_DEQUE_FREE(deque);
        return NULL;
    }

    return deque;
}

// @brief Checks if the deque is empty.
//
// This function returns true if the deque is empty (i.e., contains no elements) or if the deque is NULL.
//
// @param deque Pointer to the deque.
// @return True if the deque is empty or NULL, otherwise false.
YAC_DEQUE_API bool YacDequeEmpty(const YacDeque* deque)
{
    if (!deque) {
        return true;
    }
    return deque->size == 0;
}

// @brief Returns the number of elements in the deque.
//
// This function returns the current number of elements stored in the deque. If the deque is NULL,
// the function returns 0.
//
// @param deque Pointer to the deque.
// @return The number of elements in the deque, or 0 if the deque is NULL.
YAC_DEQUE_API size_t YacDequeLength(const YacDeque* deque)
{
    if (!deque) {
        return 0;
    }
    return deque->size;
}

// @brief Inserts an item at the front of the deque.
//
// This function inserts a new item at the front of the deque. If necessary, it allocates a new block
// at the front to accommodate the new item. If the deque or item is NULL, the function prints an error
// message and returns without making any changes.
//
// @param deque Pointer to the deque.
// @param item Pointer to the item to be inserted.
YAC_DEQUE_API void YacDequePushFront(YacDeque* deque, void* item)
{
    if (!deque) {
        return;
    }
    if (!item) {
        return;
    }

    // Check if a new block is needed at the front
    if (deque->frontIndex == 0) {
        // Allocate a new block at the front
        void*** newBlocks = YAC_DEQUE_REALLOC(deque->blocks, sizeof(void**) * (deque->blockCount + 1));
        if (!newBlocks) {
            return;
        }
        // Shift existing blocks to the right
        memmove(newBlocks + 1, newBlocks, sizeof(void**) * deque->blockCount);

        newBlocks[0] = YAC_DEQUE_MALLOC(sizeof(void*) * deque->blockSize);
        if (!newBlocks[0]) {
            return;
        }
        // Update deque properties
        deque->blocks = newBlocks;
        deque->blockCount++;
        deque->frontIndex = deque->blockSize;
    }
    // Insert item at the front
    deque->frontIndex--;
    deque->blocks[0][deque->frontIndex] = item;
    deque->size++;
}

// @brief Inserts an item at the back of the deque.
//
// This function inserts a new item at the back of the deque. If necessary, it allocates a new block
// at the back to accommodate the new item. If the deque or item is NULL, the function prints an error
// message and returns without making any changes.
//
// @param deque Pointer to the deque.
// @param item Pointer to the item to be inserted.
YAC_DEQUE_API void YacDequePushBack(YacDeque* deque, void* item)
{
    if (!deque) {
        return;
    }
    if (!item) {
        return;
    }

    // Check if a new block is needed at the back
    if (deque->backIndex == (ssize_t)deque->blockSize - 1) {
        void*** newBlocks = YAC_DEQUE_REALLOC(deque->blocks, sizeof(void**) * (deque->blockCount + 1));
        if (!newBlocks) {
            return;
        }
        newBlocks[deque->blockCount] = YAC_DEQUE_MALLOC(sizeof(void*) * deque->blockSize);
        if (!newBlocks[deque->blockCount]) {
            YAC_DEQUE_FREE(newBlocks);
            return;
        }
        deque->blocks = newBlocks;
        deque->blockCount++;
        deque->backIndex = -1;
    }

    // Allocate memory for the new item and copy the item contents
    void* newItem = YAC_DEQUE_MALLOC(deque->itemSize);
    if (!newItem) {
        return;
    }

    memcpy(newItem, item, deque->itemSize);

    YAC_DEQUE_FREE(item);

    // Insert the new item at the back
    deque->backIndex++;
    deque->blocks[deque->blockCount - 1][deque->backIndex] = newItem;
    deque->size++;
}

// @brief Returns a pointer to the front element of the deque.
//
// This function retrieves the front element of the deque without removing it.
// If the deque is empty or NULL, an error message is printed and NULL is returned.
//
// @param deque Pointer to the deque.
// @return Pointer to the front element, or NULL if the deque is empty or NULL.
YAC_DEQUE_API void* YacDequeFront(const YacDeque* deque)
{
    if (!deque) {
        return NULL;
    }
    if (YacDequeEmpty(deque)) {
        return NULL;
    }

    // Calculate the block and index for the front element
    size_t blockIndex = deque->frontIndex / deque->blockSize;
    size_t indexInBlock = deque->frontIndex % deque->blockSize;

    return deque->blocks[blockIndex][indexInBlock];
}


// @brief Returns a pointer to the back element of the deque.
//
// This function retrieves the back element of the deque without removing it.
// If the deque is empty or NULL, an error message is printed and NULL is returned.
//
// @param deque Pointer to the deque.
// @return Pointer to the back element, or NULL if the deque is empty or NULL.
YAC_DEQUE_API void* YacDequeBack(const YacDeque* deque)
{
    if (!deque) {
        return NULL;
    }
    if (YacDequeEmpty(deque)) {
        return NULL;
    }

    // Calculate the block and index for the back element
    size_t blockIndex = deque->backIndex / deque->blockSize;
    size_t indexInBlock = deque->backIndex % deque->blockSize;

    return deque->blocks[blockIndex][indexInBlock];
}

// @brief Removes the front element from the deque.
//
// This function removes the front element from the deque.
// If the deque becomes empty, the front index is adjusted and
// the memory for the blocks is managed accordingly.
//
// @param deque Pointer to the deque.
YAC_DEQUE_API void YacDequePopFront(YacDeque* deque)
{
    if (!deque) {
        return;
    }
    if (YacDequeEmpty(deque)) {
        return;
    }

    deque->frontIndex++;

    if (deque->frontIndex / deque->blockSize > 0) {
        YAC_DEQUE_FREE(deque->blocks[0]);
        memmove(deque->blocks, deque->blocks + 1, sizeof(void**) * (deque->blockCount - 1));
        deque->blockCount--;
        deque->frontIndex -= deque->blockSize;
    }

    deque->size--;
}

// @brief Removes the back element from the deque.
//
// This function removes the back element from the deque.
// If the deque becomes empty, the back index is adjusted and
// the memory for the blocks is managed accordingly.
//
// @param deque Pointer to the deque.
YAC_DEQUE_API void YacDequePopBack(YacDeque* deque)
{
    if (!deque) {
        return;
    }
    if (YacDequeEmpty(deque)) {
        return;
    }

    YAC_DEQUE_FREE(deque->blocks[deque->blockCount - 1][deque->backIndex]);

    // Normal decrement
    if (deque->backIndex > 0) {
        deque->backIndex--;
    } else if (deque->blockCount > 1) {
        YAC_DEQUE_FREE(deque->blocks[deque->blockCount - 1]);
        deque->blockCount--;
        deque->backIndex = deque->blockSize - 1;
    }

    deque->size--;
}

// @brief Returns a pointer to the element at the specified index in the deque.
//
// This function retrieves the element at the specified index in the deque.
// If the index is out of bounds or the deque is NULL, an error message is printed and NULL is returned.
//
// @param deque Pointer to the deque.
// @param index The index of the element to retrieve.
// @return Pointer to the element at the specified index, or NULL if the index is out of bounds or
//         the deque is NULL.
YAC_DEQUE_API void* YacDequeAt(const YacDeque* deque, size_t index)
{
    if (!deque) {
        return NULL;
    }
    if (index >= deque->size) {
        return NULL;
    }

    // Calculate the block and index within the block
    size_t blockIndex = (deque->frontIndex + index) / deque->blockSize;
    size_t indexInBlock = (deque->frontIndex + index) % deque->blockSize;

    // Adjusting the calculation for blockIndex when crossing block boundaries
    if (blockIndex >= deque->blockCount) {
        blockIndex = deque->blockCount - 1;
        indexInBlock = deque->backIndex - ((deque->size - 1) - index);
    }

    return deque->blocks[blockIndex][indexInBlock];
}


// @brief Deallocates all memory associated with the deque.
//
// This function frees all elements and blocks associated with the deque,
// and then deallocates the deque structure itself.
//
// @param deque Pointer to the deque.
YAC_DEQUE_API void YacDequeDeinitExtra(YacDeque* deque)
{
    if (!deque) {
        return;
    }
    YacDequeDeinitExtra_(deque);
    YAC_DEQUE_FREE(deque);
}

YAC_DEQUE_API void YacDequeDeinit(YacDeque* deque)
{
    if (!deque) {
        return;
    }
    YacDequeDeinit_(deque);
    YAC_DEQUE_FREE(deque);
}

// @brief Shrinks the deque's memory usage to fit its current size.
//
// This function reduces the memory used by the deque to match its current size.
// It deallocates any excess memory blocks that are no longer needed, keeping only
// the blocks that are required to store the current elements in the deque.
//
// @param deque Pointer to the deque.
YAC_DEQUE_API void YacDequeShrinkToFit(YacDeque* deque)
{
    if (!deque) {
        return;
    }
    if (deque->size == 0) {
        return;
    }

    // Calculate the optimal number of blocks needed
    size_t optimalBlockCount = (deque->size / deque->blockSize) + ((deque->size % deque->blockSize) ? 1 : 0);

    // If the current block count is greater than the optimal, reduce it
    if (deque->blockCount > optimalBlockCount) {
        // Free the excess blocks
        for (size_t i = optimalBlockCount; i < deque->blockCount; ++i) {
            YAC_DEQUE_FREE(deque->blocks[i]);
        }

        // Attempt to YAC_DEQUE_REALLOCate the blocks array to the new size
        void*** newBlocks = YAC_DEQUE_REALLOC(deque->blocks, sizeof(void**) * optimalBlockCount);
        if (!newBlocks) {
            return;
        }

        deque->blocks = newBlocks;
        deque->blockCount = optimalBlockCount;
    }
}

// @brief Inserts an element at a specified index in the deque.
//
// This function inserts a new element at the specified index in the deque.
// If necessary, it YAC_DEQUE_REALLOCates memory to accommodate the new element, and shifts
// existing elements to the right to make space for the insertion.
//
// @param deque Pointer to the deque.
// @param index The position at which to insert the new element.
// @param item Pointer to the item to insert.
YAC_DEQUE_API void YacDequeInsert(YacDeque* deque, size_t index, void* item)
{
    if (!deque || !item) {
        return;
    }
    if (index > deque->size) {
        return;
    }

    // Reallocate if more blocks are needed
    if (deque->size == deque->blockSize * deque->blockCount) {
        void*** newBlocks = YAC_DEQUE_REALLOC(deque->blocks, sizeof(void**) * (deque->blockCount + 1));
        if (!newBlocks) {
            return;
        }
        deque->blocks = newBlocks;
        deque->blocks[deque->blockCount] = YAC_DEQUE_MALLOC(sizeof(void*) * deque->blockSize);
        if (!deque->blocks[deque->blockCount]) {
            return;
        }
        deque->blockCount++;
    }

    // Shift elements to make space for the new item
    for (size_t i = deque->size; i > index; --i) {
        size_t srcBlockIndex = (deque->frontIndex + i - 1) / deque->blockSize;
        size_t srcIndexInBlock = (deque->frontIndex + i - 1) % deque->blockSize;
        size_t destBlockIndex = (deque->frontIndex + i) / deque->blockSize;
        size_t destIndexInBlock = (deque->frontIndex + i) % deque->blockSize;

        deque->blocks[destBlockIndex][destIndexInBlock] = deque->blocks[srcBlockIndex][srcIndexInBlock];
    }

    // Insert the item
    size_t blockIndex = (deque->frontIndex + index) / deque->blockSize;
    size_t indexInBlock = (deque->frontIndex + index) % deque->blockSize;
    deque->blocks[blockIndex][indexInBlock] = item;
    deque->size++;
}

// @brief Removes an element at a specified index in the deque.
//
// This function removes the element at the specified index in the deque.
// It shifts elements to the left to fill the gap left by the removed element,
// and may deallocate memory blocks if they are no longer needed.
//
// @param deque Pointer to the deque.
// @param index The position of the element to remove.
YAC_DEQUE_API void YacDequeErase(YacDeque* deque, size_t index)
{
    if (!deque || index >= YacDequeLength(deque)) {
        return;
    }

    // Iterate over all elements after the erased element and shift them one position left
    for (size_t i = index + 1; i < YacDequeLength(deque); ++i) {
        void* currentElement = YacDequeAt(deque, i);
        void* previousElement = YacDequeAt(deque, i - 1);

        if (currentElement && previousElement) {
            memcpy(previousElement, currentElement, deque->itemSize);  // Copy the element to its new location
        }
    }

    // Free the last element after shifting
    void* lastElement = YacDequeAt(deque, YacDequeLength(deque) - 1);
    if (lastElement) {
        YAC_DEQUE_FREE(lastElement);
    }

    deque->size--;  // Reduce the size
}

// @brief Resizes the deque to the specified size.
//
// This function changes the size of the deque to the specified new size.
// If the new size is larger than the current size, the deque is expanded with
// default-initialized elements. If the new size is smaller, elements are removed
// from the back of the deque. The function also optimizes memory usage if the new
// size is significantly smaller than the current size.
//
// @param deque Pointer to the deque.
// @param newSize The new size of the deque.
YAC_DEQUE_API void YacDequereSize(YacDeque* deque, size_t newSize)
{
    if (!deque) {
        return;
    }

    // Resize larger: add default-initialized elements to the back
    while (deque->size < newSize) {
        void* defaultItem = NULL;
        YacDequePushBack(deque, defaultItem);
    }
    while (deque->size > newSize) {
        YacDequePopBack(deque);
    }

    // Optimize memory usage if the new size is much smaller than the current size
    size_t optimalBlockCount = (newSize / deque->blockSize) + ((newSize % deque->blockSize) ? 1 : 0);
    if (optimalBlockCount < deque->blockCount) {
        for (size_t i = optimalBlockCount; i < deque->blockCount; ++i) {
            YAC_DEQUE_FREE(deque->blocks[i]);
        }

        void*** newBlocks = YAC_DEQUE_REALLOC(deque->blocks, sizeof(void**) * optimalBlockCount);
        if (!newBlocks) {
            return;
        }
        deque->blocks = newBlocks;
        deque->blockCount = optimalBlockCount;
    }
}

// @brief Swaps the contents of two deques.
//
// This function swaps the contents of the current deque with another deque.
// The two deques will exchange their contents, sizes, and internal structures.
//
// @param deque Pointer to the first deque.
// @param otherYacDeque Pointer to the second deque.
YAC_DEQUE_API void YacDequeSwap(YacDeque* deque, YacDeque* otherYacDeque)
{
    if (!deque || !otherYacDeque) {
        return;
    }

    YacDeque temp = *deque;
    *deque = *otherYacDeque;
    *otherYacDeque = temp;
}

// @brief Assigns the specified value to a range of elements in the deque.
//
// This function clears the current contents of the deque and then resizes the deque
// to hold 'n' elements, each initialized to the specified value. Memory is allocated
// as needed to accommodate the new size.
//
// @param deque Pointer to the deque.
// @param n The number of elements to assign to the deque.
// @param val Pointer to the value to assign to each element.
// @param extra YacDequeDeinitExtra or YacDequeDeinit.
YAC_DEQUE_API void YacDequeAssign(YacDeque* deque, size_t n, void* val, bool extra)
{
    if (!deque) {
        return;
    }

    if (extra) {
        YacDequeDeinitExtra_(deque);
    } else {
        YacDequeDeinit_(deque);
    }

    // Resize the deque to have 'n' elements
    for (size_t i = 0; i < n; ++i) {
        // If expanding beyond current block count, allocate new blocks as needed
        if (deque->size == deque->blockSize * deque->blockCount) {

            void*** newBlocks = YAC_DEQUE_REALLOC(deque->blocks, sizeof(void**) * (deque->blockCount + 1));
            if (!newBlocks) {
                return;
            }

            newBlocks[deque->blockCount] = YAC_DEQUE_MALLOC(sizeof(void*) * deque->blockSize);
            if (!newBlocks[deque->blockCount]) {
                return;
            }
            deque->blocks = newBlocks;
            deque->blockCount++;
        }

        // Calculate the block index and position within the block
        size_t blockIndex = deque->size / deque->blockSize;
        size_t indexInBlock = deque->size % deque->blockSize;

        deque->blocks[blockIndex][indexInBlock] = val;
        deque->size++;
    }
}

// @brief Inserts an element at the end of the deque.
//
// This function inserts a new element at the back of the deque. If the deque's
// current block is full, it allocates a new block and inserts the element there.
//
// @param deque Pointer to the deque.
// @param item Pointer to the item to insert.
YAC_DEQUE_API void YacDequeEmplaceBack(YacDeque* deque, void* item)
{
    if (!deque || !item) {
        return;
    }

    // Dynamically allocate memory for the new item
    void* newItem = YAC_DEQUE_MALLOC(deque->itemSize);
    if (!newItem) {
        return;
    }

    // Copy the content of 'item' into the newly allocated memory
    memcpy(newItem, item, deque->itemSize);

    // Handle inserting the item in a new block if necessary
    if (deque->backIndex == (ssize_t)deque->blockSize - 1) {
        void*** newBlocks = YAC_DEQUE_REALLOC(deque->blocks, sizeof(void**) * (deque->blockCount + 1));
        if (!newBlocks) {
            YAC_DEQUE_FREE(newItem);
            return;
        }
        deque->blocks = newBlocks;
        deque->blocks[deque->blockCount] = YAC_DEQUE_MALLOC(sizeof(void*) * deque->blockSize);
        if (!deque->blocks[deque->blockCount]) {
            YAC_DEQUE_FREE(newItem);
            YAC_DEQUE_FREE(newBlocks);
            return;
        }
        deque->blockCount++;
        deque->backIndex = -1;
    }

    // Insert the new item at the back
    deque->backIndex++;
    deque->blocks[deque->blockCount - 1][deque->backIndex] = newItem;
    deque->size++;
}

// @brief Inserts an element at the front of the deque.
//
// This function inserts a new element at the front of the deque. If the deque's
// current block is full at the front, it allocates a new block and inserts the
// element there.
//
// @param deque Pointer to the deque.
// @param item Pointer to the item to insert.
YAC_DEQUE_API void YacDequeEmplaceFront(YacDeque* deque, void* item)
{
    if (!deque) {
        return;
    }
    if (!item) {
        return;
    }

    // Check if a new block is needed at the front
    if (deque->frontIndex == 0) {
        void*** newBlocks = YAC_DEQUE_REALLOC(deque->blocks, sizeof(void**) * (deque->blockCount + 1));
        if (!newBlocks) {
            return;
        }

        memmove(newBlocks + 1, newBlocks, sizeof(void**) * deque->blockCount);
        newBlocks[0] = YAC_DEQUE_MALLOC(sizeof(void*) * deque->blockSize);
        if (!newBlocks[0]) {
            return;
        }

        deque->blocks = newBlocks;
        deque->blockCount++;
        deque->frontIndex = deque->blockSize;
    }

    deque->frontIndex--;
    size_t blockIndex = deque->frontIndex / deque->blockSize;
    size_t indexInBlock = deque->frontIndex % deque->blockSize;
    deque->blocks[blockIndex][indexInBlock] = item;
    deque->size++;
}

// @brief Inserts an element at the specified position in the deque.
//
// This function inserts an element at the given index in the deque. If the index is
// at the front or back, it calls the appropriate emplace function. It handles the
// necessary memory management, including allocating new blocks if needed.
//
// @param deque Pointer to the deque in which to insert the element.
// @param index The position at which to insert the element.
// @param item Pointer to the item to be inserted.
YAC_DEQUE_API void YacDequeEmplace(YacDeque* deque, size_t index, void* item)
{
    if (!deque) {
        return;
    }
    if (index > deque->size) {
        return;
    }
    if (!item) {
        return;
    }
    if (index == deque->size) {
        YacDequeEmplaceBack(deque, item);
        return;
    }
    if (index == 0) {
        YacDequeEmplaceFront(deque, item);
        return;
    }

    // Check if a new block is needed
    if (deque->size == deque->blockSize * deque->blockCount) {
        void*** newBlocks = YAC_DEQUE_REALLOC(deque->blocks, sizeof(void**) * (deque->blockCount + 1));
        if (!newBlocks) {
            return;
        }

        newBlocks[deque->blockCount] = YAC_DEQUE_MALLOC(sizeof(void*) * deque->blockSize);
        if (!newBlocks[deque->blockCount]) {
            return;
        }

        deque->blocks = newBlocks;
        deque->blockCount++;
    }

    // Shift elements to the right to make space for the new item
    for (size_t i = deque->size; i > index; --i) {
        size_t srcBlockIndex = (deque->frontIndex + i - 1) / deque->blockSize;
        size_t srcIndexInBlock = (deque->frontIndex + i - 1) % deque->blockSize;
        size_t destBlockIndex = (deque->frontIndex + i) / deque->blockSize;
        size_t destIndexInBlock = (deque->frontIndex + i) % deque->blockSize;

        deque->blocks[destBlockIndex][destIndexInBlock] = deque->blocks[srcBlockIndex][srcIndexInBlock];
    }

    size_t blockIndex = (deque->frontIndex + index) / deque->blockSize;
    size_t indexInBlock = (deque->frontIndex + index) % deque->blockSize;
    deque->blocks[blockIndex][indexInBlock] = item;
    deque->size++;
}

// @brief Returns the maximum size of the deque.
//
// This function returns the maximum possible number of elements that the deque
// can hold. This is typically a very large number, depending on system limits.
//
// @param deque Pointer to the deque.
// @return The maximum size of the deque.
YAC_DEQUE_API size_t YacDequeMaxSize(const YacDeque* deque)
{
    if (!deque) {
        return 0;
    }
    return SIZE_MAX;
}

// @brief Compares two deques for equality.
//
// This function checks whether two deques are equal, which means they have the
// same number of elements and each corresponding element is equal.
//
// @param deque1 Pointer to the first deque.
// @param deque2 Pointer to the second deque.
//
// @return true if the deques are equal, false otherwise.
YAC_DEQUE_API bool YacDequeIsEqual(const YacDeque* deque1, const YacDeque* deque2)
{
    if (deque1 == deque2) {
        return true;
    }
    if (!deque1 || !deque2) {
        return false;
    }
    if (deque1->size != deque2->size) {
        return false;
    }
    // Compare elements
    for (size_t i = 0; i < deque1->size; ++i) {
        if (YacDequeAt(deque1, i) != YacDequeAt(deque2, i)) {
            return false;
        }
    }
    return true;
}

// @brief Compares two deques to determine if the first is less than the second.
//
// This function performs a lexicographical comparison of two deques. It checks
// each element in sequence until it finds a pair that differs, or until one deque
// runs out of elements.
//
// @param deque1 Pointer to the first deque.
// @param deque2 Pointer to the second deque.
//
// @return true if the first deque is less than the second, false otherwise.
YAC_DEQUE_API bool YacDequeIsLess(const YacDeque* deque1, const YacDeque* deque2)
{
    if (!deque1 || !deque2) {
        return false;
    }

    for (size_t i = 0; i < deque1->size && i < deque2->size; ++i) {
        if (YacDequeAt(deque1, i) < YacDequeAt(deque2, i)) {
            return true;
        }
        if (YacDequeAt(deque1, i) > YacDequeAt(deque2, i)) {
            return false;
        }
    }
    bool result = deque1->size < deque2->size;

    return result;
}

// @brief Compares two deques to determine if the first is greater than the second.
//
// This function checks whether the first deque is greater than the second
// by comparing them using YacDequeIsLess with the arguments reversed.
//
// @param deque1 Pointer to the first deque.
// @param deque2 Pointer to the second deque.
//
// @return true if the first deque is greater than the second, false otherwise.
YAC_DEQUE_API bool YacDequeIsGreater(const YacDeque* deque1, const YacDeque* deque2)
{
    return YacDequeIsLess(deque2, deque1);
}

// @brief Compares two deques for inequality.
//
// This function checks whether two deques are not equal, which means either
// they have different sizes or at least one pair of corresponding elements is not equal.
//
// @param deque1 Pointer to the first deque.
// @param deque2 Pointer to the second deque.
//
// @return true if the deques are not equal, false otherwise.
YAC_DEQUE_API bool YacDequeIsNotEqual(const YacDeque* deque1, const YacDeque* deque2)
{
    return !YacDequeIsEqual(deque1, deque2);
}

// @brief Compares two deques to determine if the first is less than or equal to the second.
//
// This function checks if the first deque is less than or equal to the second
// by using the YacDequeIsLess and YacDequeIsEqual functions.
//
// @param deque1 Pointer to the first deque.
// @param deque2 Pointer to the second deque.
//
// @return true if the first deque is less than or equal to the second, false otherwise.
YAC_DEQUE_API bool YacDequeIsLessOrEqual(const YacDeque* deque1, const YacDeque* deque2)
{
    return YacDequeIsLess(deque1, deque2) || YacDequeIsEqual(deque1, deque2);
}

// @brief Compares two deques to determine if the first is greater than or equal to the second.
//
// This function checks if the first deque is greater than or equal to the second
// by using the YacDequeIsGreater and YacDequeIsEqual functions.
//
// @param deque1 Pointer to the first deque.
// @param deque2 Pointer to the second deque.
//
// @return true if the first deque is greater than or equal to the second, false otherwise.
YAC_DEQUE_API bool YacDequeIsGreaterOrEqual(const YacDeque* deque1, const YacDeque* deque2)
{
    return YacDequeIsGreater(deque1, deque2) || YacDequeIsEqual(deque1, deque2);
}

// @brief Returns an iterator to the beginning of the deque.
//
// This function returns an iterator pointing to the first element in the deque.
// If the deque is empty, the iterator will be set to the end position.
//
// @param deque Pointer to the deque.
// @return An iterator pointing to the first element of the deque.
YAC_DEQUE_API YacDequeIterator YacDequeBegin(const YacDeque* deque)
{
    YacDequeIterator it = {0};
    if (!deque) {
        return it; // Return default iterator on error
    }
    if (deque->size > 0) {
        it.deque = (YacDeque*)deque;
        it.current = deque->blocks[0][deque->frontIndex];
        it.blockIndex = deque->frontIndex / deque->blockSize;
        it.indexInBlock = deque->frontIndex % deque->blockSize;
    }

    return it;
}

// @brief Returns an iterator to the end of the deque.
//
// This function returns an iterator pointing to the position just past the last element
// in the deque. This is typically used as a sentinel in loops.
//
// @param deque Pointer to the deque.
// @return An iterator pointing just past the last element of the deque.
YAC_DEQUE_API YacDequeIterator YacDequeEnd(const YacDeque* deque)
{
    YacDequeIterator it = {0};
    if (!deque) {
        return it;
    }

    it.deque = (YacDeque*)deque;
    it.current = NULL;  // End iterator is past the last element

    size_t totalElements = deque->frontIndex + deque->size;
    it.blockIndex = totalElements / deque->blockSize;
    it.indexInBlock = totalElements % deque->blockSize;

    return it;
}

// @brief Returns a reverse iterator pointing to the last element in the deque.
//
// This function initializes a reverse iterator that points to the last element of the deque.
// The reverse iterator can be used to iterate backward through the deque.
//
// @param deque Pointer to the deque for which the reverse iterator is created.
// @return A YacDequeIterator pointing to the last element of the deque.
YAC_DEQUE_API YacDequeIterator YacDequeRbegin(const YacDeque* deque)
{
    YacDequeIterator it = {0};
    if (!deque) {
        return it;
    }

    if (deque->size > 0) {
        it.deque = (YacDeque*)deque;
        size_t lastBlock = (deque->frontIndex + deque->size - 1) / deque->blockSize;
        size_t indexInLastBlock = (deque->frontIndex + deque->size - 1) % deque->blockSize;

        it.current = deque->blocks[lastBlock][indexInLastBlock];
        it.blockIndex = lastBlock;
        it.indexInBlock = indexInLastBlock;
        it.isReverse = true; // Set isReverse to true for reverse iterator
    }

    return it;
}

// @brief Returns a reverse iterator pointing to the position before the first element in the deque.
//
// This function initializes a reverse iterator that represents the position before
// the first element in the deque, effectively the "rend" position for reverse iteration.
//
// @param deque Pointer to the deque for which the reverse end iterator is created.
// @return A YacDequeIterator representing the reverse end position of the deque.
YAC_DEQUE_API YacDequeIterator YacDequeRend(const YacDeque* deque)
{
    YacDequeIterator it = {0};
    if (!deque) {
        return it;
    }

    it.deque = (YacDeque*)deque;
    it.current = NULL;
    it.blockIndex = 0;
    it.indexInBlock = SIZE_MAX; // Representing an invalid position
    it.isReverse = true; // Set isReverse to true for reverse iterator

    return it;
}

// @brief Returns a constant iterator to the first element of the deque.
//
// This function provides a constant iterator (read-only) that points to the first element
// in the deque. The iterator can be used to traverse the deque from the beginning.
//
// @param deque Pointer to the deque for which the constant begin iterator is created.
// @return A constant YacDequeIterator pointing to the first element of the deque.
YAC_DEQUE_API YacDequeIterator YacDequeCbegin(const YacDeque* deque)
{
    if (!deque) {
        return (YacDequeIterator){0};  // Return an empty iterator
    }

    YacDequeIterator it = YacDequeBegin(deque);
    it.deque = deque;  // Ensure the iterator refers to the correct deque
    it.current = deque->blocks[it.blockIndex] + it.indexInBlock;  // Point to the first element
    return it;
}

// @brief Returns a constant iterator to the position after the last element of the deque.
//
// This function provides a constant iterator (read-only) that represents the position
// just after the last element in the deque, effectively the "end" position.
//
// @param deque Pointer to the deque for which the constant end iterator is created.
// @return A constant YacDequeIterator representing the end position of the deque.
YAC_DEQUE_API YacDequeIterator YacDequeCend(const YacDeque* deque)
{
    if (!deque) {
        return (YacDequeIterator){0};  // Return an empty iterator
    }

    YacDequeIterator it = YacDequeEnd(deque);
    it.deque = deque;  // Ensure the iterator refers to the correct deque
    it.current = NULL;  // End iterator doesn't point to a valid element
    return it;
}

// @brief Returns a constant reverse iterator to the last element of the deque.
//
// This function provides a constant reverse iterator (read-only) that points to the last element
// in the deque. The iterator can be used to traverse the deque in reverse order.
//
// @param deque Pointer to the deque for which the constant reverse begin iterator is created.
// @return A pointer to a constant YacDequeIterator pointing to the last element of the deque.
YAC_DEQUE_API YacDequeIterator YacDequeCrbegin(const YacDeque* deque)
{
    if (!deque) {
        return (YacDequeIterator){0};  // Return an empty iterator
    }

    YacDequeIterator it = YacDequeRbegin(deque);
    return it;
}

// @brief Returns a constant reverse iterator to the position before the first element of the deque.
//
// This function provides a constant reverse iterator (read-only) that represents the position
// before the first element in the deque, effectively the "rend" position.
//
// @param deque Pointer to the deque for which the constant reverse end iterator is created.
// @return A constant YacDequeIterator representing the reverse end position of the deque.
YAC_DEQUE_API YacDequeIterator YacDequeCrend(const YacDeque* deque)
{
    if (!deque) {
        return (YacDequeIterator){0};  // Return an empty iterator
    }

    YacDequeIterator it = YacDequeRend(deque);
    return it;
}

// @brief Moves the iterator to the previous position for reverse iteration.
//
// For reverse iterators, this function decrements the iterator's position, moving backwards
// through the deque. It properly handles moving between blocks and invalidates the iterator
// when it reaches the reverse end.
//
// @param it Pointer to the iterator to increment (move backward).
YAC_DEQUE_API void YacDequeIteratorIncrement(YacDequeIterator* it)
{
    if (!it || !it->deque) {
        return;
    }

    it->indexInBlock++;
    if (it->indexInBlock >= it->deque->blockSize) {  // Move to the next block
        it->blockIndex++;
        it->indexInBlock = 0;
    }

    if (it->blockIndex >= it->deque->blockCount ||  // Check if out of bounds
        (it->blockIndex == it->deque->blockCount - 1 && (ssize_t)it->indexInBlock > it->deque->backIndex)) {
        it->current = NULL;
    } else {
        it->current = it->deque->blocks[it->blockIndex] + it->indexInBlock;
    }
}

// @brief Decrements the position of the iterator.
//
// This function moves the iterator one position backward in the deque. If the iterator
// is a reverse iterator, it moves forward instead. It handles boundary conditions,
// such as moving between blocks of the deque.
//
// @param it Pointer to the iterator to decrement.
YAC_DEQUE_API void YacDequeIteratorDecrement(YacDequeIterator* it)
{
    if (!it || !it->deque) {
        return;
    }

    if (it->indexInBlock == 0) {  // Move to the previous block
        if (it->blockIndex == 0) {
            it->current = NULL;  // Reached the reverse end
            return;
        }
        it->blockIndex--;
        it->indexInBlock = it->deque->blockSize - 1;
    } else {
        it->indexInBlock--;
    }

    // Update current pointer
    if (it->blockIndex < it->deque->blockCount) {
        it->current = it->deque->blocks[it->blockIndex] + it->indexInBlock;
    } else {
        it->current = NULL;
    }
}

// @brief Compares two iterators for equality.
//
// This function checks if two iterators point to the same position in the deque.
// It also handles cases where one or both iterators are at the end (or rend) position.
//
// @param it1 Pointer to the first iterator.
// @param it2 Pointer to the second iterator.
//
// @return true if the iterators are equal, false otherwise.
YAC_DEQUE_API bool YacDequeIteratorEquals(const YacDequeIterator* it1, const YacDequeIterator* it2)
{
    if (!it1 || !it2) {
        return false; // Null pointer error
    }

    // Check if either iterator is at the end (or rend) position
    if (it1->current == NULL || it2->current == NULL) {
        return it1->current == it2->current;
    }

    return it1->blockIndex == it2->blockIndex && it1->indexInBlock == it2->indexInBlock;
}

// @brief Retrieves the value pointed to by the iterator.
//
// This function returns the value at the current position of the iterator. It handles
// both forward and reverse iteration, ensuring that the correct element is returned.
//
// @param it Pointer to the iterator from which to retrieve the value.
//
// @return A pointer to the value at the current position of the iterator, or NULL
//         if the iterator is out of bounds.
YAC_DEQUE_API void* YacDequeIteratorGet(const YacDequeIterator* it)
{
    if (!it || !it->deque) {
        return NULL;
    }

    // Handle out-of-bounds situation
    if (it->blockIndex >= it->deque->blockCount || it->indexInBlock >= it->deque->blockSize) {
        return NULL;
    }

    return it->deque->blocks[it->blockIndex][it->indexInBlock];
}


//
// Implementation for internal operations
//

static void YacDequeDeinitExtra_(YacDeque* deque)
{
    for (size_t i = 0; i < deque->blockCount; ++i) {
        size_t startIndex = (i == 0) ? deque->frontIndex : 0;
        size_t endIndex = (i == deque->blockCount - 1) ? deque->backIndex + 1 : deque->blockSize;

        for (size_t j = startIndex; j < endIndex; ++j) {
            if (deque->blocks[i][j] != NULL) {
                YAC_DEQUE_FREE(deque->blocks[i][j]);  // Free the element
                deque->blocks[i][j] = NULL;  // Mark as freed
            }
        }
        YAC_DEQUE_FREE(deque->blocks[i]);  // Free the block
        deque->blocks[i] = NULL;
    }

    // Free the blocks array and reset metadata
    YAC_DEQUE_FREE(deque->blocks);
    deque->blocks = NULL;
    deque->blockCount = 0;
    deque->size = 0;
    deque->frontIndex = 0;
    deque->backIndex = -1;
}

static void YacDequeDeinit_(YacDeque* deque)
{
    for (size_t i = 0; i < deque->blockCount; ++i) {
        YAC_DEQUE_FREE(deque->blocks[i]);  // Free the block
        deque->blocks[i] = NULL;
    }

    // Free the blocks array and reset metadata
    YAC_DEQUE_FREE(deque->blocks);
    deque->blocks = NULL;
    deque->blockCount = 0;
    deque->size = 0;
    deque->frontIndex = 0;
    deque->backIndex = -1;
}


#endif // YAC_DEQUE_IMPLEMENTATION
