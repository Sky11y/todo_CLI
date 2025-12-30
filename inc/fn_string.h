#ifndef FN_STRING_H
# define FN_STRING_H

#include <stdlib.h>
#include <string.h>

size_t fn_strlen(const char* restrict str);
/*
 * Remove all the *chars* from the beginning and end of *str*.
 * Important! This function modifies the *str* in place.
 */
void strtrim(char *restrict str, const char* restrict chars);
/*
 * Remove all the *chars* from the beginning of *str*.
 * Important! This function modifies the *str* in place.
 */
void strtrim_front(char *restrict str, const char *restrict chars);
/*
 * Remove all the *chars* from the back of hte *str*.
 * Important! This function modifies the *str* in place.
 */
void strtrim_back(char *restrict str, const char *restrict chars);
/*
 * Replace every occurence of *to_replace* with *c* in *str*
 * Note. It is callers responsibility to make sure *c* and *to_replace* are printable chars.
 * Important! This function modifies the *str* in place.
 */
void replace_all(char *restrict str, char to_replace, char c);
/*
 * Copies max. *dsize* - 1 chars from *src* to *dst*.
 * Guarantees to '\0'-terminate the *dst* (hence max. dsize - 1).
 * Returns the number of characters copied, exluding the terminating '\0'.
 * Note. It is users responsiblity to make sure the size of *dst* is large enough.
 */
size_t safe_strlcpy(char *restrict dst, const char *restrict src, size_t dsize);
/*
 * Checks if string *test* contains any of the characters in *chars*.
 * Returns 1 if any of the *chars* is found in *test* and 0 if not.
 * Note. If *test* is empty returns -1 (user can handle this as an error).
 * Note. If *chars* is empty returns 1 (i.e. always true when compared to nothing).
 */
int contains(const char *restrict test, const char *restrict chars);
/*
 * Checks if a character *test* is any of the character in *chars*.
 * Returns 1 if test matches any of the *chars*, and 0 if not.
 * Note. If *test* is null-character returns -1 (user can handle this as an error).
 * Note. If *chars* is empty returns 1 (i.e. always true when compared to nothing).
 */
int is_any_of(const char test, const char *restrict chars);
/*
 * Check if all the characters in *test* are one of *chars*
 * Returns 1 if true, and 0 if not.
 * Note. If *test* is empty returns -1 (user can handle this as an error).
 * Note. If *chars* is empty returs 1 (i.e. always true when compared to nothing).
 */
int is_all_of(const char *restrict test, const char *restrict chars);
/*
 * Change all capital characters of *str* to lower characters.
 * Important! This function modifies the *str* in place.
 */
void str_to_lower(char *restrict str);
/*
 * Change all lower characters of *str* to capital characters.
 * Important! This function modifies the *str* in place.
 */
void str_to_upper(char *restrict str);
char ** fn_split(const char *str, char delim, char escape);


#endif
