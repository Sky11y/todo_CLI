#include "todo.h"

i8 init_data(s_data* data)
{
	data->items = malloc(10 * sizeof(s_item));
	if (data->items == NULL) {
		return -1;
	}
	data->count = 0;
	data->capacity = 10;

	return 0;
}

i8 resize_data(s_data* data)
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
	free(data->items);
}

