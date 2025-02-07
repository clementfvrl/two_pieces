#ifndef WORLD_H
#define WORLD_H

#include "player.h"

typedef struct World {
    char name[20];
    char description[100];
    struct World *next;
} World;

World *initializeWorlds();
void exploreWorld(World *worlds, Player *player);
void freeWorlds(World *worlds);

#endif