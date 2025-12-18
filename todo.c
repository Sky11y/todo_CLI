#include "todo.h"

void print_data(s_data* data);

int add(s_data* data)
{
	s_item *item = &data->items[data->count];
	int bytes_read;
	char c;
	int len = 0;
	
	//title can't be empty
	printf("Add title (max. %u characters)\n", MAX_TITLE_LEN);
	while (TRUE) {
		bytes_read = read(STDIN_FILENO, &c, 1);
		if (bytes_read < 1) {
			return -1;
		}

		if (c == '\n') {
			item->title[len] = '\0';
			strtrim(item->title, " \t\v");
			if (*item->title) {
				break;
			}
			printf("Title can't be empty\n");
			printf("Add title (max. %u characters)\n", MAX_TITLE_LEN);
			len = 0;
			continue;
		}

		if (is_any_of(c, "\t\v")) {
			item->title[len] = 32;
		} else {
			item->title[len] = c;
		}

		if (len + 1 == MAX_TITLE_LEN) {
			item->title[len + 1] = '\0';
			strtrim(item->title, " \t\v");
			flush_stdin();
			if (*item->title) {
				break;
			}
			printf("Title can't be empty\n");
			printf("Add title (max. %u characters)\n", MAX_TITLE_LEN);
			len = 0;
			continue;
		} 
		++len;
	}
	
	len = 0;
	//decription is optional, hence can be empty
	printf("Add description (max. %u characters)\n", MAX_DESCRIPTION_LEN);
	while (TRUE) {
		bytes_read = read(STDIN_FILENO, &item->description[len], 1);
		if (bytes_read == -1) {
			return -1;
		} else if (bytes_read == 0) {
			break;
		} else if (item->description[len] == '\n') {
			item->description[len] = '\0';
			strtrim(item->description, " \t\v");
			break;
		}

		if (len + 1 == MAX_DESCRIPTION_LEN) {
			item->description[len + 1] = '\0';
			strtrim(item->description, " \t\v");
			flush_stdin();
			break;
		}
		++len;
	}

	item->status = 0;
	item->id = ++data->count;

	if (data->count == data->capacity) {
		resize_data(data);
	}
	return 0;
}

void main_loop(s_data* data)
{
	printf("What would you like to do? (ADD/DEL/MOD/FIN/EXIT/HELP)\n");

	add(data);
	//char *fgets(char s[restrict .size], int size, FILE *restrict stream);
}

int main(int argc, char** argv)
{
	int		fd;
	s_data	data;

	if (argc > 1) {
		fd = open(argv[1], O_RDONLY);	
	} else {
		fd = open("data.psv", O_CREAT|O_RDONLY);
	}
	if (fd == -1) {
		perror("Couldn't open datafile");
		return EXIT_FAILURE;
	}

	if (init_data(&data) == -1) {
		perror("Couldn't set the data");
		return EXIT_FAILURE;
	}

	if (read_datafile(fd, &data) == -1) {
		perror("Failed to read the datafile");
		close(fd);
		free_data(&data);
		return EXIT_FAILURE;
	}

	close(fd);

	main_loop(&data);
	print_data(&data);

	//save the work and clean up
	//save_datafile(&data);
	free_data(&data);
	return EXIT_SUCCESS;
}

void print_data(s_data* data)
{
	printf("%5s|%15s|%15s|%10s|\n", "id", "title", "description", "status");
	for (uint j = 0; j < data->count; ++j) {
		printf("%5u|%15s|%15s|%10d|\n",
				data->items[j].id,
				data->items[j].title,
				data->items[j].description,
				data->items[j].status);
	}
}
