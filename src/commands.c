#include "todo.h"

i8 add(s_data* data)
{
	s_item *item = &(data->items[data->count]);
	
	//title can't be empty
	while (1) {
		printf("Add title (max. %u characters)\n", MAX_TITLE_LEN - 1);
		if (read_buf_from_stdin(item->title, MAX_TITLE_LEN) == -1) {
			return -1;
		}
		strtrim(item->title, " \t\v");
		if (*item->title) {
			replace_all(item->title, '|', '!');	
			break;
		}
		printf("Title can't be empty\n");

	}
	
	//decription is optional, hence can be empty
	printf("Add description (max. %u characters)\n", MAX_DESCRIPTION_LEN - 1);
	if (read_buf_from_stdin(item->description, MAX_DESCRIPTION_LEN) == -1) {
		return -1;
	}
	strtrim(item->description, " \t\v");
	replace_all(item->description, '|', '!');	

	data->count += 1;
	item->status = 0;
	item->id = data->count;

	if (data->count == data->capacity) {
		resize_data(data);
	}

	return 0;
}

i8 del(s_data* data, uint id)
{
	s_item* item;

	item = get_item(data, id);
	if (!item) {
		return -1;
	}
	item->id = 0;

	return 0;	
}

i8 fin(s_data* data, uint id)
{
	s_item* item;

	item = get_item(data, id);
	if (!item) {
		return -1;
	}

	if (item->status == TODO_DONE) {
		printf("Item already finished!\n");
	}
	else {
		item->status = TODO_DONE;
		printf("Item successfully marked as finished\n");
	}

	return 0;
}

i8 mod(s_data* data, uint id)
{
	s_item* item;

	item = get_item(data, id);
	if (!item) {
		return -1;
	}

	if (item->status == TODO_DONE) {
		printf("Item already finished. Modification not allowed!\n");
		return 0;
	}

	printf("Add a new description for %s (max. %u characters)\n",
			item->title,
			MAX_DESCRIPTION_LEN - 1);

	if (read_buf_from_stdin(item->description, MAX_DESCRIPTION_LEN) == -1) {
		return -1;
	}

	strtrim(item->description, " \t\v");
	replace_all(item->description, '|', '!');	
	printf("Item description successfully changed\n");

	return 0;
}

i8 show(s_data* data, uint id)
{
	s_item* item;

	item = get_item(data, id);
	if (!item) {
		return -1;
	}

	printf("Title: %s\nDescription: %s\n", item->title, item->description);

	return 0;
}

void list(s_data* data)
{
	u32 i;

	printf("%5s|%15s|%8s|\n", "id", "title", "status");
	for (i = 0; i < data->count; ++i) {
		if (data->items[i].id == 0) {
			continue;
		}
		printf("%5u|%15s|%8s|\n",
				data->items[i].id,
				data->items[i].title,
				data->items[i].status == 0 ? "Pending" : "Done");
	}	
}
