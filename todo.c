#include "todo.h"

void main_loop(s_data* data)
{
	printf("What would you like to do? (ADD/DEL/MOD/FIN/LST/EXIT/HELP)\n");

	//working commands
	add(data);
	//help();
	del(data, 4);
	fin(data, 2);
	//
	
}

int main(int argc, char** argv)
{
	int		fd;
	s_data	data;
	(void)argc;
	(void)argv;

	fd = open("data.psv", O_CREAT|O_RDONLY);
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

	printf("data count before: %d\n", data.count);
	main_loop(&data);
	print_data(&data);

	printf("data count after: %d\n", data.count);
	//save the work and clean up
	save_datafile(&data);
	free_data(&data);
	return EXIT_SUCCESS;
}

