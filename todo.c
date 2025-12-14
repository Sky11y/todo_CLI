#include "todo.h"

int init_data(s_data* data);
int resize_data(s_data* data);
void free_data(s_data* data);
void print_data(s_data* data);

int parse_buffer(char* buf, s_data* data)
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

int read_data(int fd, s_data* data)
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

	print_data(data);

	return 0;
}

void main_loop(s_data* data)
{
	printf("What would you like to do? (ADD/DEL/MOD/FIN/EXIT/HELP)\n");
	answer = fgets();
	hash_the_answer(answer)
	switch (answer_hash) {
		case 0:
			break;
		default:
			printf("invalid input");
			print_help();
	}
}

int main(int argc, char** argv)
{
	int		fd;
	s_data	data;

	//load data
	if (argc > 1) {
		fd = open(argv[1], O_RDONLY);	
	} else {
		fd = open("data.psv", O_CREAT|O_RDONLY);
	}
	if (fd == -1) {
		fprintf(stderr, "%m\n");
		return EXIT_FAILURE;
	}

	//allocate initial working memory
	if (init_data(&data) == -1) {
		fprintf(stderr, "%m\n");
		return EXIT_FAILURE;
	}

	//read data from file in-memory
	if (read_data(fd, &data) == -1) {
		fprintf(stderr, "%m\n");
		close(fd);
		free_data(&data);
		return EXIT_FAILURE;
	}

	close(fd);

	main_loop(&data);

	//save the work and clean up
	//save_file(&data);
	free_data(&data);
	return EXIT_SUCCESS;
}
	
int init_data(s_data* data)
{
	data->items = malloc(10 * sizeof(s_item));
	if (data->items == NULL) {
		return -1;
	}
	data->count = 0;
	data->capacity = 10;

	return 0;
}

int resize_data(s_data* data)
{
	data->capacity *= 2;
	data->items = realloc(data->items, data->capacity * sizeof(s_item));
	if (data->items == NULL) {
		return -1;
	}
	return 0;
}

void free_data(s_data* data)
{
	for (uint i = 0; i < data->count; ++i) {
		free(data->items[i].description);
	}
	free(data->items);
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
