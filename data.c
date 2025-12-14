#include "todo.h"

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


