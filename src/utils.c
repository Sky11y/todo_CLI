#include "todo.h"

void help(void)
{
	printf("\
This is a simple todo program where you can save todo's, modify them and mark them as finished.\
\n\n\
usage: CMD [<args>]\
\n\n\
These are the possible commands (CMD)\n\
	ADD		add an item to the todo list.\n\
	DEL <id>	remove an item from the todo list\n\
	MOD <id>	modify an item on the todo list\n\
	FIN <id>	mark an item finished\n\
	LST		list all the items in the todo list\n\
	SHOW <id>	show the full item with the description\n\
	EXIT		exit the program\n\
	HELP		output the help\n\
\n\
");
}

void debug_data(s_data* data)
{
	printf("\n%5s|%15s|%15s|%10s|\n", "id", "title", "description", "status");
	for (uint j = 0; j < data->count; ++j) {
		printf("%5u|%15s|%15s|%10d|\n",
				data->items[j].id,
				data->items[j].title,
				data->items[j].description,
				data->items[j].status);
	}
}

s_item* get_item(s_data* data, uint id)
{
	uint i;

	if (id == 0) {
		printf("No such id\n");
		return NULL;
	}

	for (i = 0; i < data->count; ++i) {
		if (data->items[i].id == id) {
			return &data->items[i];
		}
	}
	printf("No such id\n");
	return NULL;
}

void list(s_data* data)
{
	printf("%5s|%15s|%8s|\n", "id", "title", "status");
	for (uint i = 0; i < data->count; ++i) {
		if (data->items[i].id == 0) {
			continue;
		}
		printf("%5u|%15s|%8s|\n",
				data->items[i].id,
				data->items[i].title,
				data->items[i].status == 0 ? "Pending" : "Done");
	}	
}

int show(s_data* data, uint id)
{
	s_item* item;

	item = get_item(data, id);
	if (!item) {
		return -1;
	}

	printf("Title: %s\nDescription: %s\n", item->title, item->description);

	return 0;
}
