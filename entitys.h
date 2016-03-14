#ifndef ENTITYS_H
#define ENTITYS_H

#include <stdlib.h>

struct entity
{
	int x;
	int y;
	int collides;
	char representation;
};

//The entity structure defines entitys that are places in the world.
struct entityList
{
	struct entityList* next;
	struct entity value;
};

void listInsert(struct entityList *list, struct entity ent);
void listClean(struct entityList *list);
#endif /* ENTITYS_H */
