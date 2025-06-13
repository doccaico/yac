// The MIT License (MIT)
// Original work Copyright (C) 2016 ZongXian Shen <andy.zsshen@gmail.com>
// Modified work Copyright (C) 2025 Doccaico
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.

// Original work
// https://github.com/ZSShen/C-Common-Data-Structures

#ifndef YACC_UNORDERED_MAP_H_
#define YACC_UNORDERED_MAP_H_


#ifndef YACC_MAP_PAIR_DEFINED
#define YACC_MAP_PAIR_DEFINED
// The key value pair for associative data structures.
typedef struct _Pair {
    void* key;
    void* value;
} Unordered_Map_Pair;

typedef struct _Pair {
    void* key;
    void* value;
} YacUnorderedMapPair;
#endif

#endif // YACC_UNORDERED_MAP_H_


// IMPLEMENTATION

#ifdef YACC_UNORDERED_MAP_IMPLEMENTATION

#endif // YACC_UNORDERED_MAP_IMPLEMENTATION
