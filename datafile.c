#include "todo.h"

static int parse_buffer(char* buf, s_data* data)
{
	uint j = data->count;
	char* token;
	uint tokenlen;

	for (uint i = 0;; ++i, buf = NULL) {
		token = strtok(buf, "|");
		if (token == NULL)
			break;
		switch (i % 4) {
			case 0:
				data->items[j].id = strtoul(token, NULL, 10);
				break;
			case 1:
				strncpy(data->items[j].title, token, MAX_TITLE_LEN);
				break;
			case 2:
				tokenlen = strlen(token) + 1;
				data->items[j].description = malloc(sizeof(char) * tokenlen);
				if (data->items[j].description == NULL) {
					return -1;
				}
				memcpy(data->items[j].description, token, tokenlen);
				break;
			case 3:
				if (token[0] == 'P') {
					data->items[j++].status = TODO_PENDING;
				} else if (token[0] == 'D') {
					data->items[j++].status = TODO_DONE;
				}
				break;
		}
	}

	data->count = j;

	return 0;
	//resize_data(&data);
}

int read_datafile(int fd, s_data* data)
{
	char buf[BUFFER_SIZE];
	int bytes_read;

	while (true) {
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == 0) {
			break;
		} else if (bytes_read == -1) {
			return EXIT_FAILURE;
		}
	
		if (parse_buffer(buf, data) == -1)
			return -1;
	}

	return 0;
}

