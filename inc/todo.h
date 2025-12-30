#ifndef TODO_H
# define TODO_H

#include <fcntl.h> //open()
#include <unistd.h> //close()
#include <stdio.h> //fprintf
#include <stdlib.h> //malloc, realloc, free, EXIT_SUCCESS, EXIT_FAILURE
#include <stdint.h>

#include "fn_string.h"

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

#endif
