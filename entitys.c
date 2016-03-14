#include "entitys.h"

void listInsert(struct entityList *list, struct entity ent)
{
	if(list->next == NULL){
		list->next = (struct entityList*) malloc(sizeof(struct entityList));
	}else{
		listInsert(list->next, ent);
	}

}

void listClean(struct entityList *list)
{
	if(list->next != NULL){
		listClean(list->next);
	}
	free(list);
}
