#include "todo.h"

static int flush_stdin(void);
/*
 * read, readline, fgets, and similar have the problem that they don't flush the stdin when the reading is done.
 * Uses clib read() to Reads from *fd* to *buf* maximum of *n-1* amount of characters.
 * This function has the next features:
 * - always flush the stdin from the extra characters
 * - guarantees to '\0'-terminate the buffer, hence read n-1 characters
 *   - provided that the caller has allocated n size of space to the buffer
 * - check if the read fails -> return -1
 */
int read_buf_from_stdin(char *restrict buf, size_t n)
{
	ssize_t bytes_read;

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


static int flush_stdin(void)
{
	ssize_t bytes_read;
	char temp[64];

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
