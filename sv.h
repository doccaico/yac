#ifndef SV_H_
#define SV_H_

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#ifndef SV_API
#ifdef SV_STATIC
#define SV_API static
#else
#define SV_API extern
#endif // SV_STATIC
#endif // SV_API


// DECLARATIONS

typedef struct {
    const char *begin;
    size_t len;
} StringView;

#define sv_empty ((StringView){0})

#define sv_from_cstr(str) ((StringView){.begin = str, .len = strlen(str)})

#define sv_from_cstr_slice(str, offset, len_)                 \
    ((StringView){.begin = (str) + (offset), .len = (len_)})

#define sv_from_constant(c)                               \
    ((StringView){.begin = (c), .len = sizeof((c)) - 1})

#define sv_from_sb(sb) ((StringView){.begin = (sb).items, .len = (sb).count})

#define sv_from_str(str) sv_from_sb((str).h->b)

#define sv_farg "%.*s"

#define sv_expand(sv) (int)(sv).len, (sv).begin

#define sv_slice(sv, offset, len_)                      \
    (sv_from_cstr_slice((sv).begin, (offset), (len_)))

#define sv_advance(sv) (++(sv).begin, --(sv).len)

SV_API bool sv_equals(const StringView *lhs, const StringView *rhs);
SV_API bool sv_equals_icase(const StringView *lhs, const StringView *rhs);

SV_API bool sv_starts_with_cstr(const StringView *sv, const char *start);
SV_API bool sv_starts_with_cstr_icase(const StringView *sv, const char *start);
SV_API bool sv_ends_with_cstr(const StringView *sv, const char *end);
SV_API bool sv_ends_with_cstr_icase(const StringView *sv, const char *end);

SV_API bool sv_starts_with(const StringView *sv, const StringView *start);
SV_API bool sv_starts_with_icase(const StringView *sv, const StringView *start);
SV_API bool sv_ends_with(const StringView *sv, const StringView *end);
SV_API bool sv_ends_with_icase(const StringView *sv, const StringView *end);
SV_API void sv_stripl(StringView *sv);
SV_API void sv_stripr(StringView *sv);
SV_API void sv_strip(StringView *sv);

SV_API int sv_index_of(const StringView *sv, int rune);
SV_API int sv_last_index_of(const StringView *sv, int rune);
SV_API int sv_index_of_str(const StringView *sv, const char *str);
SV_API StringView sv_split(StringView *sv, const char *delim);
SV_API StringView sv_split_exclude_delim(StringView *sv, const char *delim);

#endif // SV_H_


// IMPLEMENTATION

#ifdef SV_IMPLEMENTATION

#ifdef _MSC_VER
#define strncasecmp _strnicmp
#endif

SV_API bool sv_equals(const StringView *lhs, const StringView *rhs)
{
    assert(NULL != lhs);
    assert(NULL != rhs);

    return lhs->len == rhs->len && 0 == strncmp(lhs->begin, rhs->begin, lhs->len);
}

SV_API bool sv_equals_icase(const StringView *lhs, const StringView *rhs)
{
    assert(NULL != lhs);
    assert(NULL != rhs);

    return lhs->len == rhs->len && 0 == strncasecmp(lhs->begin, rhs->begin, lhs->len);
}

SV_API bool sv_starts_with_cstr(const StringView *sv, const char *start)
{
  assert(NULL != sv);

  size_t start_len = strlen(start);
  return sv->len >= start_len && 0 == strncmp(sv->begin, start, start_len);
}

SV_API bool sv_starts_with_cstr_icase(const StringView *sv, const char *start)
{
  assert(NULL != sv);

  size_t start_len = strlen(start);
  return sv->len >= start_len && 0 == strncasecmp(sv->begin, start, start_len);
}

SV_API bool sv_ends_with_cstr(const StringView *sv, const char *end)
{
  assert(NULL != sv);

  size_t end_len = strlen(end);
  return sv->len >= end_len && 0 == strncmp(sv->begin + sv->len - end_len, end, end_len);
}

SV_API bool sv_ends_with_cstr_icase(const StringView *sv, const char *end)
{
  assert(NULL != sv);

  size_t end_len = strlen(end);
  return sv->len >= end_len && 0 == strncasecmp(sv->begin + sv->len - end_len, end, end_len);
}

SV_API bool sv_starts_with(const StringView *sv, const StringView *start)
{
  assert(NULL != sv);
  assert(NULL != start);

  return sv->len >= start->len && 0 == strncmp(sv->begin, start->begin, start->len);
}

SV_API bool sv_starts_with_icase(const StringView *sv, const StringView *start)
{
  assert(NULL != sv);
  assert(NULL != start);

  return sv->len >= start->len && 0 == strncasecmp(sv->begin, start->begin, start->len);
}

SV_API bool sv_ends_with(const StringView *sv, const StringView *end)
{
  assert(NULL != sv);
  assert(NULL != end);

  return sv->len >= end->len && 0 == strncmp(sv->begin + sv->len - end->len, end->begin, end->len);
}

SV_API bool sv_ends_with_icase(const StringView *sv, const StringView *end)
{
  assert(NULL != sv);
  assert(NULL != end);

  return sv->len >= end->len && 0 == strncasecmp(sv->begin + sv->len - end->len, end->begin, end->len);
}

SV_API void sv_stripl(StringView *sv)
{
  assert(NULL != sv);

  while (sv->len > 0 && isspace(sv->begin[0])) {
      sv_advance(*sv);
  }
}

SV_API void sv_stripr(StringView *sv)
{
  assert(NULL != sv);

  while (sv->len > 0 && isspace(sv->begin[sv->len - 1])) {
    sv->len -= 1;
  }
}

SV_API void sv_strip(StringView *sv)
{
  assert(NULL != sv);

  sv_stripl(sv);
  sv_stripr(sv);
}

SV_API int sv_index_of(const StringView *sv, int rune)
{
  assert(NULL != sv);

  const char *found = strchr(sv->begin, rune);
  return found == NULL ? -1 : (int)(found - sv->begin);
}

SV_API int sv_last_index_of(const StringView *sv, int rune)
{
  assert(NULL != sv);

  const char *found = strrchr(sv->begin, rune);
  return found == NULL ? -1 : (int)(found - sv->begin);
}

SV_API int sv_index_of_str(const StringView *sv, const char *str)
{
  assert(NULL != sv);

  const char *found = strstr(sv->begin, str);
  return found == NULL ? -1 : (int)(found - sv->begin);
}

SV_API StringView sv_split(StringView *sv, const char *delim)
{
  assert(NULL != sv);

  // returns StringView before the delim (not including)
  // sv becomes StringView from the delim (including) to the end of the given sv
  int index = sv_index_of_str(sv, delim);
  if (index < 0) {
    StringView result = *sv;
    sv->len = 0;
    return result;
  }

  StringView result = sv_slice(*sv, 0, index);
  *sv = sv_slice(*sv, index, sv->len - index);
  return result;
}

SV_API StringView sv_split_exclude_delim(StringView *sv, const char *delim)
{
  assert(NULL != sv);

  int index = sv_index_of_str(sv, delim);
  if (index < 0) {
    StringView result = *sv;
    sv->len = 0;
    return result;
  }

  StringView result = sv_slice(*sv, 0, index);
  size_t delimlen = strlen(delim);
  *sv = sv_slice(*sv, index + delimlen, sv->len - (index + delimlen));
  return result;
}

#endif // SV_IMPLEMENTATION
