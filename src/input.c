#include "todo.h"

static i8 flush_stdin(void);
/*
 * read, readline, fgets, and similar have the problem that they don't flush the stdin when the reading is done.
 * Uses clib read() to Reads from *fd* to *buf* maximum of *n-1* amount of characters.
 * This function has the next features:
 * - always flush the stdin from the extra characters
 * - guarantees to '\0'-terminate the buffer, hence read n-1 characters
 *   - provided that the caller has allocated n size of space to the buffer
 * - check if the read fails -> return -1
 */
i8 read_buf_from_stdin(char *restrict buf, size_t n)
{
	ssize_t	bytes_read;

	if (n < 1) {
		return 0;
	} else if (n == 1) {
		buf[0] = '\0';
		return 0;
	}
	bytes_read = read(STDIN_FILENO, buf, n);
	if (bytes_read < 1) {
		return -1;
	}
	if (bytes_read < (ssize_t)n) {
		buf[bytes_read - 1] = '\0';
	} else {
		buf[n - 1] = '\0';
		flush_stdin();
	}

	return 0;
}


static i8 flush_stdin(void)
{
	ssize_t	bytes_read;
	char	temp[64];

	while (1) {
		bytes_read = read(STDIN_FILENO, temp, 64);
		if (bytes_read < 1) {
			return -1;
		}

		if (temp[bytes_read - 1] == '\n') {
			break;
		}
	}
	
	return 0;
}

i8 prompt_user(s_data* data)
{
	char	buffer[10];
	u32		id;

	if (read_buf_from_stdin(buffer, 10) == -1) {
		perror("Could not read the user input\n");
		return -1;
	}

	strtrim(buffer, " \t\v");
	str_to_upper(buffer);
	
	if (strncmp(buffer, "ADD", 3) == 0) {
		add(data);
	}
	else if (strncmp(buffer, "DEL", 3) == 0) {
		id = strtoul(&buffer[3], NULL, 10);
		del(data, id);
	}
	else if (strncmp(buffer, "FIN", 3) == 0) {
		id = strtoul(&buffer[3], NULL, 10);
		fin(data, id);
	}
	else if (strncmp(buffer, "MOD", 3) == 0) {
		id = strtoul(&buffer[3], NULL, 10);
		mod(data, id);
	}
	else if (strncmp(buffer, "SHOW", 4) == 0) {
		id = strtoul(&buffer[4], NULL, 10);
		show(data, id);
	}
	else if (strncmp(buffer, "LST", 4) == 0) {
		list(data);
	}
	else if (strncmp(buffer, "HELP", 4) == 0) {
		print_help();
	}
	else if (strncmp(buffer, "EXIT", 4) == 0) {
		return 0;
	}
	else {
		printf("Invalid input\n");
	}

	return 1;
}
