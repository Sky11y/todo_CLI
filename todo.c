#include "todo.h"

void main_loop(s_data* data)
{
	//uint id = 3;
	printf("What would you like to do? (ADD/DEL/MOD/FIN/LST/EXIT/HELP)\n");

	//working commands
	//add(data);
	//help();
	//del(data, id);
	//fin(data, id);
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

