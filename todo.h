#ifndef TODO_H
# define TODO_H

#include <fcntl.h> //open()
#include <unistd.h> //close()
#include <stdio.h> //fprintf
#include <stdlib.h> //malloc, realloc, free, EXIT_SUCCESS, EXIT_FAILURE
#include <string.h> //strtok()

typedef unsigned int uint;

#define TRUE 1
#define FALSE 0

#define BUFFER_SIZE 512
#define MAX_TITLE_LEN 15
#define MAX_DESCRIPTION_LEN 255

typedef enum {
	TODO_PENDING,
	TODO_DONE,
} e_status;

typedef struct {
	uint		id;
	char		title[MAX_TITLE_LEN + 1];
	char		description[MAX_DESCRIPTION_LEN + 1];
	e_status	status;
} s_item;

typedef struct {
	s_item*	items;
	uint	count;
	uint	capacity;
} s_data;

//data.c
int init_data(s_data* data);
int resize_data(s_data* data);
void free_data(s_data* data);

//datafile.c
int read_datafile(int fd, s_data* data);
//int save_datafile(s_data* data);

//utils

/*
 * Copies max. *dsize* - 1 chars from *src* to *dst*.
 * Guarantees to '\0'-terminate the *dst* (hence max. dsize - 1).
 * Returns the number of characters copied, exluding the terminating '\0'.
 */
uint safe_strlcpy(char *restrict dst, const char *restrict src, uint dsize);

/*
 * Checks if string *test* contains any of the characters in *chars*.
 * Returns 1 if any of the *chars* is found in *test* and 0 if not.
 * If *test* is empty returns -1 (user can handle this as an error).
 * If *chars* is empty returns 1 (i.e. always true when compared to nothing).
 */
int contains(const char *restrict test, const char *restrict chars);

/*
 * Checks if a character *test* is any of the character in *chars*.
 * Returns 1 if test matches any of the *chars*, and 0 if not.
 * If *test* is null-character returns -1 (user can handle this as an error).
 * If *chars* is empty returns 1 (i.e. always true when compared to nothing).
 */
int is_any_of(const char test, const char *restrict chars);

/*
 * Check if all the characters in *test* are one of *chars*
 * Returns 1 if true, and 0 if not.
 * If *test* is empty returns -1 (user can handle this as an error).
 * If *chars* is empty returs 1 (i.e. always true when compared to nothing).
 */
int is_all_of(const char *restrict test, const char *restrict chars);

/*
 * Flushes everything from stdin until and including '\n'
 * Returns 0 on success and -1 if read fails
 */
int flush_stdin(void);

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

#endif
