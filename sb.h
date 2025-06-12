#ifndef SB_H_
#define SB_H_

#include <assert.h>
#include <stdarg.h>

#ifndef SB_API
#ifdef SB_STATIC
#define SB_API static
#else
#define SB_API extern
#endif // SB_STATIC
#endif // SB_API


// DECLARATIONS

typedef struct {
    char *items;
    size_t len;
    size_t capacity;
} StringBuilder;


#define sb_clear_and_free(sb) da_clear_and_free((sb))

#define sb_expand_buffer(sb, new_cap)      \
    do {                                   \
        if ((sb)->capacity < (new_cap)) {  \
            da_reserve((sb), (new_cap));   \
        }                                  \
    } while (0)

#define sb_farg "%.*s"

#define sb_expand(sb) (int)(sb).len, (sb).items

SB_API StringBuilder sb_create(size_t capacity);
SB_API StringBuilder sb_clone(const StringBuilder *sb);
SB_API void sb_append_rune(StringBuilder *sb, int rune);
SB_API void sb_append_sv(StringBuilder *sb, const StringView *sv);
SB_API void sb_append_cstr(StringBuilder *sb, const char *cstr);
SB_API void sb_append_sb(StringBuilder *dest, const StringBuilder *src);
SB_API void sb_appendf(StringBuilder *sb, const char *fmt, ...);

// for COW String
#define sb_append_str(sb_ptr, str_ptr) sb_append_sb((sb_ptr), &(str_ptr)->h->b)

SB_API char *sb_get_cstr(StringBuilder *sb);


#endif // SB_H_


// IMPLEMENTATION

#ifdef SB_IMPLEMENTATION

SB_API StringBuilder sb_create(size_t capacity)
{
  StringBuilder sb = {0};
  da_reserve(&sb, capacity);
  return sb;
}

SB_API StringBuilder sb_clone(const StringBuilder *sb)
{
  StringBuilder clone = sb_create(sb->len);
  memcpy(clone.items, sb->items, sb->len);
  return clone;
}

SB_API void sb_append_rune(StringBuilder *sb, int rune)
{
  assert(rune >= -128 && rune <= 127);

  da_append(sb, (char)rune);
}

SB_API void sb_append_sv(StringBuilder *sb, const StringView *sv)
{
  for (size_t i = 0; i < sv->len; ++i) {
    sb_append_rune(sb, sv->begin[i]);
  }
}

SB_API void sb_append_cstr(StringBuilder *sb, const char *cstr)
{
  StringView sv = sv_from_cstr(cstr);
  sb_append_sv(sb, &sv);
}

SB_API void sb_append_sb(StringBuilder *dest, const StringBuilder *src)
{
  size_t new_capacity = dest->len + src->len;
  if (dest->capacity < new_capacity) {
    sb_expand_buffer(dest, new_capacity);
    dest->capacity = new_capacity;
  }
  memcpy(dest->items + dest->len, src->items, src->len);
  dest->len = new_capacity;
}

SB_API char *sb_get_cstr(StringBuilder *sb)
{
  if ('\0' != sb->items[sb->len])
    da_append(sb, '\0');

  return sb->items;
}

SB_API void sb_appendf(StringBuilder *sb, const char *fmt, ...)
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


#endif // SB_IMPLEMENTATION
