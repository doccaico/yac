#ifndef YAC_STRING_BUILDER_H_
#define YAC_STRING_BUILDER_H_

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>

#ifndef YAC_STRING_BUILDER_API
#ifdef YAC_STRING_BUILDER_STATIC
#define YAC_STRING_BUILDER_API static
#else
#define YAC_STRING_BUILDER_API extern
#endif // YAC_STRING_BUILDER_STATIC
#endif // YAC_STRING_BUILDER_API


// DECLARATIONS

typedef struct {
    char *items;
    size_t len;
    size_t capacity;
} StringBuilder;


#define sb_clear_and_free(sb) YacDynamicArrayClearAndFree((sb))

#define sb_expand_buffer(sb, new_cap)      \
    do {                                   \
        if ((sb)->capacity < (new_cap)) {  \
            YacDynamicArrayReserve((sb), (new_cap));   \
        }                                  \
    } while (0)

#define sb_farg "%.*s"

#define sb_expand(sb) (int)(sb).len, (sb).items

YAC_STRING_BUILDER_API StringBuilder sb_create(size_t capacity);
YAC_STRING_BUILDER_API StringBuilder sb_clone(const StringBuilder *sb);
YAC_STRING_BUILDER_API void sb_append_rune(StringBuilder *sb, int rune);
YAC_STRING_BUILDER_API void sb_append_sv(StringBuilder *sb, const StringView *sv);
YAC_STRING_BUILDER_API void sb_append_cstr(StringBuilder *sb, const char *cstr);
YAC_STRING_BUILDER_API void sb_append_sb(StringBuilder *dest, const StringBuilder *src);
YAC_STRING_BUILDER_API void sb_appendf(StringBuilder *sb, const char *fmt, ...);

// for COW String
// #define sb_append_str(sb_ptr, str_ptr) sb_append_sb((sb_ptr), &(str_ptr)->h->b)

YAC_STRING_BUILDER_API char *sb_get_cstr(StringBuilder *sb);


#endif // YAC_STRING_BUILDER_H_


// IMPLEMENTATION

#ifdef YAC_STRING_BUILDER_IMPLEMENTATION

YAC_STRING_BUILDER_API StringBuilder sb_create(size_t capacity)
{
  StringBuilder sb = {0};
  YacDynamicArrayReserve(&sb, capacity);
  return sb;
}

YAC_STRING_BUILDER_API StringBuilder sb_clone(const StringBuilder *sb)
{
  StringBuilder clone = sb_create(sb->len);
  memcpy(clone.items, sb->items, sb->len);
  return clone;
}

YAC_STRING_BUILDER_API void sb_append_rune(StringBuilder *sb, int rune)
{
  assert(rune >= -128 && rune <= 127);

  YacDynamicArrayAppend(sb, (char)rune);
}

YAC_STRING_BUILDER_API void sb_append_sv(StringBuilder *sb, const StringView *sv)
{
  for (size_t i = 0; i < sv->len; ++i) {
    sb_append_rune(sb, sv->begin[i]);
  }
}

YAC_STRING_BUILDER_API void sb_append_cstr(StringBuilder *sb, const char *cstr)
{
  StringView sv = sv_from_cstr(cstr);
  sb_append_sv(sb, &sv);
}

YAC_STRING_BUILDER_API void sb_append_sb(StringBuilder *dest, const StringBuilder *src)
{
  size_t new_capacity = dest->len + src->len;
  if (dest->capacity < new_capacity) {
    sb_expand_buffer(dest, new_capacity);
    dest->capacity = new_capacity;
  }
  memcpy(dest->items + dest->len, src->items, src->len);
  dest->len = new_capacity;
}

YAC_STRING_BUILDER_API char *sb_get_cstr(StringBuilder *sb)
{
  if ('\0' != sb->items[sb->len])
    YacDynamicArrayAppend(sb, '\0');

  return sb->items;
}

YAC_STRING_BUILDER_API void sb_appendf(StringBuilder *sb, const char *fmt, ...)
{
  assert(NULL != sb);

  va_list args;

  va_start(args, fmt);
  int n = vsnprintf(NULL, 0, fmt, args);
  sb_expand_buffer(sb, sb->len + n + 1);
  vsnprintf(sb->items + sb->len, n + 1, fmt, args);

  va_end(args);

  sb->len += n;
}


#endif // YAC_STRING_BUILDER_IMPLEMENTATION
