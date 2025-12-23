#include "todo.h"

void print_welcome(void)
{
	printf("\
====================================================================================\n\
		Welcome to Sky11y's simple todo program!!\n\
");
}

void print_help(void)
{
	printf("\
====================================================================================\n\
\n\
usage: CMD [<id>]\
\n\n\
Available commands (CMD)\n\
	ADD		add an item to the todo list\n\
	DEL  <id>	remove an item with given id from the todo list\n\
	MOD  <id>	modify an item with given id in the todo list\n\
	FIN  <id>	mark an item with given id finished\n\
	SHOW <id>	show the item with given id with the description\n\
	LST		list all the items in the todo list\n\
	EXIT		exit the program\n\
	HELP		output the help\n\
\n\
Note. Since program is using pipe-separated-values (.psv) to save data, all the \n\
possible '|' characters given as an input will be replaced by exclamation marks '!'.\n\
====================================================================================\
\n\
");
}

void print_warning(void)
{
	printf("\
Warning. The progress will be saved on data.psv file on your filesystem.\n\
The data is not encrypted in any way.\n\
Keep the data.psv file save and/or don't write any sensitive information.\n\
====================================================================================\n\
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
