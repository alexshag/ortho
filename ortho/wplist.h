
#ifndef __WPLIST_H__
#define __WPLIST_H__

typedef struct waypoint
{
	char code[6];
	double lat;
	double lon;
	double magvar;
}waypoint; 

typedef struct node
{
	waypoint value;
	struct node* next;
} wplist;

/* Modify the list */
void wplist_addpoint(wplist** head, const waypoint* waypoint);
void wplist_free(wplist** head);
void wplist_reverse(wplist** ppList);

/* Does not modify the list */
void wplist_print(const wplist* head);
size_t wplist_size(const wplist* head);

#endif /*__WPLIST_H__*/
