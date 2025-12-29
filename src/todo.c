#include "todo.h"

void main_loop(s_data* data)
{
	i8 running;

	running = TRUE;
	while (running) {
		printf("What would you like to do? (ADD/DEL/MOD/FIN/SHOW/LST/EXIT/HELP)\n");
		running = prompt_user(data);
		if (running == -1) {
			return;
		}
	}
}

int main()
{
	int		fd;
	s_data	data;

	fd = open("data.psv", O_CREAT|O_RDONLY, 00644);
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

	print_welcome();
	print_help();
	print_warning();

	main_loop(&data);
	//debug_print(&data);

	save_datafile(&data);
	free_data(&data);
	
	return EXIT_SUCCESS;
}

