#include "todo.h"

int flush_stdin(void)
{
	char c;
	int bytes_read;

	while (1) {
		bytes_read = read(STDIN_FILENO, &c, 1);
		if (bytes_read == -1) {
			return -1;
		} else if (c == '\n') {
			break;
		}
	}
	return 0;
}

