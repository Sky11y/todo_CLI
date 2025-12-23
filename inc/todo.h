#ifndef TODO_H
# define TODO_H

#include <fcntl.h> //open()
#include <unistd.h> //close()
#include <stdio.h> //fprintf
#include <stdlib.h> //malloc, realloc, free, EXIT_SUCCESS, EXIT_FAILURE
#include <string.h> //strtok()
#include <stdint.h>

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

#define TRUE 1
#define FALSE 0

#define BUFFER_SIZE 2048
#define MAX_TITLE_LEN 16
#define MAX_DESCRIPTION_LEN 1024

typedef enum {
	TODO_PENDING,
	TODO_DONE,
} e_status;

typedef struct {
	u32			id;
	char		title[MAX_TITLE_LEN];
	char		description[MAX_DESCRIPTION_LEN];
	e_status	status;
} s_item;

typedef struct {
	s_item*	items;
	u32	count;
	u32	capacity;
} s_data;

//data.c
i8 init_data(s_data* data);
i8 resize_data(s_data* data);
void free_data(s_data* data);

//datafile.c
i8 read_datafile(int fd, s_data* data);
i8 save_datafile(s_data* data);

//commands.c
i8 add(s_data* data);
i8 del(s_data* data, uint id);
i8 fin(s_data* data, uint id);
i8 mod(s_data* data, uint id);
i8 show(s_data* data, uint id);
void list(s_data* data);

//utils.c
void print_welcome(void);
void print_help(void);
void print_warning(void);
void debug_print(s_data* data);
s_item* get_item(s_data* data, uint id);

//input.c
i8 prompt_user(s_data* data);
i8 read_buf_from_stdin(char *restrict buf, size_t n);

//getline.c
char *fn_getline(int fd);

//strings.c
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
 * Change all capital characters of *str* to lower characters.
 * Important! This function modifies the *str* in place.
 */
void str_to_lower(char *restrict str);

/*
 * Change all lower characters of *str* to capital characters.
 * Important! This function modifies the *str* in place.
 */
void str_to_upper(char *restrict str);

#endif
