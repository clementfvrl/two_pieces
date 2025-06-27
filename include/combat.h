#ifndef COMBAT_H
#define COMBAT_H

#include "player.h"

typedef struct {
    char name[20];
    int health;
    int attack;
} Enemy;

Enemy *createEnemy(const char *name, int health, int attack);
void startCombat(Player *player, Enemy *enemy);
void freeEnemy(Enemy *enemy);

#endif