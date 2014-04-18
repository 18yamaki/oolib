#include <stdbool.h>
#include "List.h"

int
main(void)
{
	List* list;
	list = List_new();

	List_destory(&list, true);
	return 0;
}


