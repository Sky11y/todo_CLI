#include "todo.h"

void print_data(s_data* data);

int add(s_data* data)
{
	s_item *item = &data->items[data->count];

	//title can't be empty
	while (TRUE) {
		printf("Add title (max. %u characters)\n", MAX_TITLE_LEN - 1);
		fgets(item->title, MAX_TITLE_LEN, stdin);
		if (is_all_of(item->title, "\n\t \v") == 1) {
			printf("Title can't be empty\n");
			//stdin needs to be flushed
			continue;
		}
		int len = strlen(item->title) - 1;
		item->title[len] = '\0';
		break;
	}

	//decription is optional, hence can be empty
	printf("Add description (max. %u characters)\n", MAX_DESCRIPTION_LEN - 1);
	fgets(item->description, MAX_DESCRIPTION_LEN, stdin);
	int len = strlen(item->description) - 1;
	if (len > 0) {
		item->description[len] = '\0';
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
		fprintf(stderr, "%m\n");
		return EXIT_FAILURE;
	}

	if (init_data(&data) == -1) {
		fprintf(stderr, "%m\n");
		return EXIT_FAILURE;
	}

	if (read_datafile(fd, &data) == -1) {
		fprintf(stderr, "%m\n");
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
