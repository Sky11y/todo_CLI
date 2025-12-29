#include "todo.h"

static int parse_line(char *line, s_data *data)
{
	u32 i;
	u32 j;
	s_item *item;

	item = &data->items[data->count];
	item->id = data->count + 1;

	for (i = 0; line[i] != '|'; ++i) {
		if (!line[i]) {
			return -1;
		}
		item->title[i] = line[i];
	}
	item->title[i++] = '\0';

	for (j = 0; line[i + j] != '|'; ++j) {
		if (!line[i + j]) {
			return -1;
		}
		item->description[j] = line[i + j];
	}
	item->description[j++] = '\0';
	item->status = line[i + j] == 'P' ? TODO_PENDING : TODO_DONE;	
	data->count++;
	if (data->count == data->capacity) {
		resize_data(data);
	}

	return 0;
}

i8 read_datafile(int fd, s_data* data)
{
	char *line;

	while (TRUE) {
		line = fn_getline(fd);
		if (!line)
			break;
		if (parse_line(line, data) == -1) {
			free(line);
			return -1;	
		}
		free(line);
	}

	return 0;
}

i8 save_datafile(s_data* data)
{
	FILE*	datafile;
	u32		i;
	s_item	item;

	datafile = fopen("data.psv", "w");
	if (datafile == NULL) {
		return -1;
	}

	for (i = 0; i < data->count; ++i) {
		item = data->items[i];
		if (item.id == 0) {
			continue;
		}	
		fprintf(datafile, "%s|%s|%s|\n", item.title,
									 	 item.description,
									 	 item.status == TODO_DONE ? "D" : "P");
	}

	fclose(datafile);
	return 0;
}
