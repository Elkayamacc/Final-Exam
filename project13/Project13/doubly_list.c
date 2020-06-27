#include <stdlib.h>
#include "doubly_list.h"

void initList(list* lst)
{
	lst->head = lst->tail = NULL;
}

//is list empty
int isEmpty(list* lst)
{
	return lst->head == NULL;
}

//return amount of nodes in the list
int length(list* lst)
{
	int length = 0;
	node* current;

	for (current = lst->head; current != NULL; current = current->next)
		length++;

	return length;
}

//allocate a new item
node* allocItem(list_type value)
{
	node* item = (node*)malloc(sizeof(node));
	item->value = value;
	return item;
}

////return item located in spesific index
node* getLinkByIndex(list* lst, int idx)
{
	int i;
	//start from the first link
	node* link = lst->head;

	//navigate through list
	for (i = 0; i < idx && link != NULL; i++)
		link = link->next;

	return link;
}

//insert item at the first location
int insertFirst(list* lst, node* item)
{
	if (item != NULL)
	{
		//reset item pointers
		item->next = item->prev = NULL;

		if (isEmpty(lst))
		{
			//make head & tail pointing to item
			lst->head = lst->tail = item;
		}
		else
		{
			//update first prev link
			lst->head->prev = item;
			//point item to old first link
			item->next = lst->head;
			//point head to new first node
			lst->head = item;
		}
		return 1;
	}
	return 0;
}

//insert item at the last location
int insertLast(list* lst, node* item)
{
	if (item != NULL)
	{
		//reset item pointers
		item->next = item->prev = NULL;

		if (isEmpty(lst))
		{
			//make head & tail pointing to item
			lst->head = lst->tail = item;
		}
		else
		{
			//update last next link
			lst->tail->next = item;
			//point item to old last link
			item->prev = lst->tail;
			//point last to new last node
			lst->tail = item;
		}
		return 1;
	}
	return 0;
}

//delete first item
int deleteFirst(list* lst)
{
	//if list is empty there is nothing to delete
	if (!isEmpty(lst))
	{
		//save reference to first link
		node* temp = lst->head;

		//if only one link
		if (temp->next == NULL)
		{
			initList(lst);
		}
		else
		{
			lst->head->next->prev = NULL;
			lst->head = lst->head->next;
		}
		free(temp);
		return 1;
	}
	return 0;
}

//delete link at the last location
int deleteLast(list* lst)
{
	//if list is empty there is nothing to delete
	if (!isEmpty(lst))
	{
		//save reference to last link
		node* temp = lst->tail;

		//if only one link
		if (temp->prev == NULL)
		{
			initList(lst);
		}
		else
		{
			lst->tail->prev->next = NULL;
			lst->tail = lst->tail->prev;
		}
		free(temp);
		return 1;
	}
	return 0;
}

//delete link from list
int deleteLink(list* lst, node* link)
{
	if (!isEmpty(lst))
	{
		if (link == NULL)
			return 0;
		if (link == lst->head)
			return deleteFirst(lst);
		if (link == lst->tail)
			return deleteLast(lst);

		//bypass the current link
		link->prev->next = link->next;
		link->next->prev = link->prev;
		free(link);
		return 1;
	}
	return 0;
}

//insert a new item after link
int insertAfter(list* lst, node* item, node* link)
{
	if (!isEmpty(lst))
	{
		if ((item == NULL) || (link == NULL))
			return 0;
		if (link == lst->tail)
			return insertLast(lst, item);

		//assign new item pointers
		item->prev = link;
		item->next = link->next;
		//chain link and link->next to new item
		link->next->prev = item;
		link->next = item;
		return 1;
	}
	return 0;
}

//insert a new item before link
int insertBefore(list* lst, node* item, node* link)
{
	if (!isEmpty(lst))
	{
		if ((item == NULL) || (link == NULL))
			return 0;
		if (link == lst->head)
			return insertFirst(lst, item);

		//assign new item pointers
		item->next = link;
		item->prev = link->prev;
		//chain link and link->prev to new item
		link->prev->next = item;
		link->prev = item;
		return 1;
	}
	return 0;
}