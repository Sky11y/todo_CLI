#ifndef FN_STRING_H
# define FN_STRING_H

#include <stdlib.h>
#include <string.h>

size_t fn_strlen(const char* restrict str);
void strtrim(char *restrict str, const char* restrict chars);
void strtrim_front(char *restrict str, const char *restrict chars);
void strtrim_back(char *restrict str, const char *restrict chars);
void replace_all(char *restrict str, char to_replace, char c);
size_t safe_strlcpy(char *restrict dst, const char *restrict src, size_t dsize);
int contains(const char *restrict test, const char *restrict chars);
int is_any_of(const char test, const char *restrict chars);
int is_all_of(const char *restrict test, const char *restrict chars);
void str_to_lower(char *restrict str);
void str_to_upper(char *restrict str);
char ** fn_split(const char *str, char delim, char escape);


#endif
