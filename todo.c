#include "todo.h"

void print_data(s_data* data);

void main_loop(s_data* data)
{
	printf("What would you like to do? (ADD/DEL/MOD/FIN/EXIT/HELP)\n");
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

	print_data(&data);
	main_loop(&data);

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
