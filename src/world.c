
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "world.h"

World *initializeWorlds() {
    World *world1 = malloc(sizeof(World));
    strncpy(world1->name, "East Blue", 20);
    strncpy(world1->description, "Le début de l'aventure.", 100);
    world1->next = NULL; // Pas encore de mondes suivants
    return world1;
}

void exploreWorld(World *worlds, Player *player) {
    printf("Vous explorez : %s\n", worlds->name);
    printf("%s\n", worlds->description);
}

void freeWorlds(World *worlds) {
    while (worlds) {
        World *temp = worlds;
        worlds = worlds->next;
        free(temp);
    }
}