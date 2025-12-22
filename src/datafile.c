#include "todo.h"

static int parse_buffer(char* buf, s_data* data)
{
	uint j;
	char* token;

	j = data->count;
	for (uint i = 0;; ++i, buf = NULL) {
		token = strtok(buf, "|");
		if (token == NULL)
			break;
		switch (i % 4) {
			case 0:
				data->items[j].id = j + 1;
				//data->items[j].id = strtoul(token, NULL, 10);
				break;
			case 1:
				safe_strlcpy(data->items[j].title, token, MAX_TITLE_LEN);
				break;
			case 2:
				safe_strlcpy(data->items[j].description, token, MAX_DESCRIPTION_LEN);
				break;
			case 3:
				if (token[0] == 'P' || token[0] == 'p') {
					data->items[j++].status = TODO_PENDING;
				} else if (token[0] == 'D' || token[0] == 'd') {
					data->items[j++].status = TODO_DONE;
				}
				if (j == data->capacity) {
					resize_data(data);
				}
				break;
		}
	}

	data->count = j;

	return 0;
}

int read_datafile(int fd, s_data* data)
{
	char buf[BUFFER_SIZE];
	int bytes_read;

	while (TRUE) {
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

int save_datafile(s_data* data)
{
	FILE* datafile;
	uint i;
	s_item item;

	datafile = fopen("data.psv", "w");
	if (datafile == NULL) {
		return -1;
	}

	for (i = 0; i < data->count; ++i) {
		item = data->items[i];
		if (item.id == 0) {
			continue;
		}	
		fprintf(datafile, "%u|%s|%s|%s|\n", item.id,
									 item.title,
									 item.description,
									 item.status == TODO_DONE ? "Done" : "Pending");
	}
	return 0;
}
