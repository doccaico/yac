#ifndef YAC_STRING_BUILDER_H_
#define YAC_STRING_BUILDER_H_


#include <stdarg.h> // va_list
#include <stdio.h> // vsnprintf

#include "./yac_dynamic_array.h"

#ifndef YAC_STRING_BUILDER_ASSERT
#include <assert.h> // assert
#define YAC_STRING_BUILDER_ASSERT assert
#endif // YAC_STRING_BUILDER_ASSERT

#ifndef YAC_STRING_BUILDER_API
#ifdef YAC_STRING_BUILDER_STATIC
#define YAC_STRING_BUILDER_API static
#else
#define YAC_STRING_BUILDER_API extern
#endif // YAC_STRING_BUILDER_STATIC
#endif // YAC_STRING_BUILDER_API


// DECLARATIONS

typedef struct {
    char* items;
    size_t len;
    size_t capacity;
} YacStringBuilder;

#define YacStringBuilderClearAndFree(sb) YacDynamicArrayClearAndFree((sb))

#define YacStringBuilderExpandBuffer(sb, new_cap)     \
    do {                                              \
        if ((sb)->capacity < (new_cap)) {             \
            YacDynamicArrayReserve((sb), (new_cap));  \
        }                                             \
    } while (0)

#define YacStringBuilderFarg "%.*s"

#define YacStringBuilderExpand(sb) (int)(sb).len, (sb).items

YAC_STRING_BUILDER_API YacStringBuilder YacStringBuilderCreate(size_t capacity);
YAC_STRING_BUILDER_API YacStringBuilder YacStringBuilderClone(const YacStringBuilder* sb);
YAC_STRING_BUILDER_API void YacStringBuilderAppendRune(YacStringBuilder* sb, int rune);
YAC_STRING_BUILDER_API void YacStringBuilderAppendStringView(YacStringBuilder* sb, const YacStringView* sv);
YAC_STRING_BUILDER_API void YacStringBuilderAppendCstr(YacStringBuilder* sb, const char* cstr);
YAC_STRING_BUILDER_API void YacStringBuilderAppendStringBuilder(
        YacStringBuilder* dest, const YacStringBuilder* src);
YAC_STRING_BUILDER_API void YacStringBuilderAppendFormat(YacStringBuilder* sb, const char* fmt, ...);
YAC_STRING_BUILDER_API char* YacStringBuilderGetCstr(YacStringBuilder* sb);


#endif // YAC_STRING_BUILDER_H_


// IMPLEMENTATION

#ifdef YAC_STRING_BUILDER_IMPLEMENTATION

YAC_STRING_BUILDER_API YacStringBuilder YacStringBuilderCreate(size_t capacity)
{
  YacStringBuilder sb = {0};
  YacDynamicArrayReserve(&sb, capacity);
  return sb;
}

YAC_STRING_BUILDER_API YacStringBuilder YacStringBuilderClone(const YacStringBuilder* sb)
{
  YAC_STRING_BUILDER_ASSERT(NULL != sb);

  YacStringBuilder clone = YacStringBuilderCreate(sb->len);
  memcpy(clone.items, sb->items, sb->len);
  return clone;
}

YAC_STRING_BUILDER_API void YacStringBuilderAppendRune(YacStringBuilder* sb, int rune)
{
  YAC_STRING_BUILDER_ASSERT(NULL != sb);

  YAC_STRING_BUILDER_ASSERT(rune >= -128 && rune <= 127);

  YacDynamicArrayAppend(sb, (char)rune);
}

YAC_STRING_BUILDER_API void YacStringBuilderAppendStringView(YacStringBuilder* sb, const YacStringView* sv)
{
  YAC_STRING_BUILDER_ASSERT(NULL != sb);

  for (size_t i = 0; i < sv->len; ++i) {
    YacStringBuilderAppendRune(sb, sv->begin[i]);
  }
}

YAC_STRING_BUILDER_API void YacStringBuilderAppendCstr(YacStringBuilder* sb, const char* cstr)
{
  YAC_STRING_BUILDER_ASSERT(NULL != sb);

  YacStringView sv = YacStringViewFromCstr(cstr);
  YacStringBuilderAppendStringView(sb, &sv);
}

YAC_STRING_BUILDER_API void YacStringBuilderAppendStringBuilder(
        YacStringBuilder* dest, const YacStringBuilder* src)
{
  YAC_STRING_BUILDER_ASSERT(NULL != dest);
  YAC_STRING_BUILDER_ASSERT(NULL != src);

  size_t new_capacity = dest->len + src->len;
  if (dest->capacity < new_capacity) {
    YacStringBuilderExpandBuffer(dest, new_capacity);
    dest->capacity = new_capacity;
  }
  memcpy(dest->items + dest->len, src->items, src->len);
  dest->len = new_capacity;
}

YAC_STRING_BUILDER_API char* YacStringBuilderGetCstr(YacStringBuilder* sb)
{
  YAC_STRING_BUILDER_ASSERT(NULL != sb);

  if ('\0' != sb->items[sb->len])
    YacDynamicArrayAppend(sb, '\0');

  return sb->items;
}

YAC_STRING_BUILDER_API void YacStringBuilderAppendFormat(YacStringBuilder* sb, const char* fmt, ...)
{
  YAC_STRING_BUILDER_ASSERT(NULL != sb);

  va_list args;

  va_start(args, fmt);
  int n = vsnprintf(NULL, 0, fmt, args);
  YacStringBuilderExpandBuffer(sb, sb->len + n + 1);
  vsnprintf(sb->items + sb->len, n + 1, fmt, args);

  va_end(args);

  sb->len += n;
}


#endif // YAC_STRING_BUILDER_IMPLEMENTATION
