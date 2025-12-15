#ifndef TODO_H
# define TODO_H

#include <fcntl.h> //open()
#include <unistd.h> //close()
#include <stdio.h> //fprintf
#include <stdlib.h> //malloc, realloc, free, EXIT_SUCCESS, EXIT_FAILURE
#include <stdbool.h> //true, false
#include <string.h> //strtok(), memcpy(), strncpy()

typedef unsigned int uint;

#define BUFFER_SIZE 512
#define MAX_TITLE_LEN 16
#define MAX_DESCRIPTION_LEN 256

typedef enum {
	TODO_PENDING,
	TODO_DONE,
} e_status;

typedef struct {
	uint		id;
	char		title[MAX_TITLE_LEN];
	char		description[MAX_DESCRIPTION_LEN];
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
uint safe_strlcpy(char *restrict dst, const char *restrict src, uint dsize);

#endif
