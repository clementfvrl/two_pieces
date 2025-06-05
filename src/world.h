#ifndef WORLD_H
#define WORLD_H

#include "player.h"
#include "npc.h"
#include "combat.h"

typedef struct World {
    char name[20];
    char description[100];
    struct NPC *npcs;
    struct Enemy *enemies;
    struct World *next;
} World;

World *initializeWorlds();
void exploreWorld(World *world, Player *player);
void displayWorldMap(World *world);
void triggerRandomEvent(World *world, Player *player);
void freeWorlds(World *world);
void moveOnMap(World *world, Player *player, char direction);


#endif