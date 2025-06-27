#ifndef WORLD_H
#define WORLD_H

#include "player.h"
#include "npc.h"
#include "combat.h"
#include "services.h"

typedef struct World
{
    char name[20];
    char description[100];
    struct NPC *npcs;
    struct Enemy *enemies;
    struct Service *services;
    struct World *next;
} World;

World *initializeWorlds();
void exploreWorld(World *world, Player *player);
void displayWorldMap(World *world);
void triggerRandomEvent(World *world, Player *player);
void freeWorlds(World *world);

#endif