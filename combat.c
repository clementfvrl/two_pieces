#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "combat.h"
#include "player.h"

Enemy *createEnemy(const char *name, int health, int attack) {
    Enemy *enemy = malloc(sizeof(Enemy));
    strncpy(enemy->name, name, 20);
    enemy->health = health;
    enemy->attack = attack;
    return enemy;
}

void startCombat(Player *player, Enemy *enemy) {
    printf("⚔️ Combat contre %s !\n", enemy->name);

    while (player->health > 0 && enemy->health > 0) {
        printf("\n1. Attaquer\n2. Esquiver\n3. Fuir\n> ");
        int choice;
        scanf("%d", &choice);

        if (choice == 1) {
            enemy->health -= 10;
            printf("💥 Vous infligez 10 dégâts à %s !\n", enemy->name);
        } else if (choice == 2) {
            printf("🛡️ Vous esquivez l'attaque !\n");
            continue;
        } else if (choice == 3) {
            printf("🏃‍♂️ Vous fuyez !\n");
            return;
        }

        player->health -= enemy->attack;
        printf("⚡ %s vous inflige %d dégâts !\n", enemy->name, enemy->attack);
    }

    if (player->health <= 0) {
        printf("💀 Vous avez perdu !\n");
    } else {
        printf("🎉 Vous avez vaincu %s !\n", enemy->name);
    }
}

void freeEnemy(Enemy *enemy) {
    free(enemy);
}