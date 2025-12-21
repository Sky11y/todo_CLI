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
	EXIT		exit the program\n\
	HELP		output the help\n\
\n\
");
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
