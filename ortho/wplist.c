
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "wplist.h"


void wplist_addpoint(wplist** head, const waypoint* wp)
{
	wplist* tmp = (wplist*)malloc(sizeof(wplist));
	if (tmp != NULL)
	{
		/* copy data */
		strcpy(tmp->value.code, wp->code);
		tmp->value.lat = wp->lat;
		tmp->value.lon = wp->lon;
		tmp->value.magvar = wp->magvar;

		tmp->next = (*head);
		(*head) = tmp;
	}

}

void wplist_reverse(wplist** ppList)
{
	if (ppList != NULL)
	{
		wplist* reversed = NULL;
		wplist* current = *ppList;
		wplist* temp = NULL;
		while (current != NULL)
		{
			temp = current;
			current = current->next;
			temp->next = reversed;
			reversed = temp;
		}
		*ppList = reversed;
	}
}

void pop(wplist** head, waypoint* res)
{
	if (*head != NULL)
	{
		wplist* prev = (*head);
		/* copy data */
		strcpy(res->code, prev->value.code);
		res->lat = prev->value.lat;
		res->lon = prev->value.lon;
		res->magvar = prev->value.magvar;

		(*head) = (*head)->next;
		free(prev);
	}
}

/* This the most dangerous function */
void wplist_free(wplist** head)
{
		wplist* prev = NULL;
		/* Using uninitialized memory '**head' */
		while ((*head)->next)
		{
				prev = (*head);
				(*head) = (*head)->next;
				free(prev);
		}
		free(*head);
}

void wplist_print(const wplist* head)
{
		while (head)
		{
				printf("%s\n", head->value.code);
				head = head->next;
		}
}


size_t wplist_size(const wplist* head)
{
	size_t count = 0;
	if (head != NULL)
	{
		while (head)
		{
			count++;
			head = head->next;
		}
	}
	return count;
}



const wplist* getNth(const wplist* head, unsigned long n)
{
	unsigned long counter = 0;
	while (counter < n && head)
	{
		head = head->next;
		counter++;
	}
	return head;
}


const wplist* wplist_getlast(const wplist* head)
{
	if (head == NULL)
	{
		return NULL;
	}
	while (head->next)
	{
		head = head->next;
	}
	return head;
}


void list_push_back(wplist* head, const waypoint* wp)
{
	wplist* last = (wplist*)wplist_getlast(head);
	if (last != NULL)
	{
		wplist* tmp = (wplist*)malloc(sizeof(wplist));
		if (tmp != NULL)
		{
			/* copy data */
			strcpy(tmp->value.code, wp->code);
			tmp->value.lat = wp->lat;
			tmp->value.lon = wp->lon;
			tmp->value.magvar = wp->magvar;

			tmp->next = NULL;
			last->next = tmp;
		}
	}
}

