#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "world.h"
#include "npc.h"
#include "combat.h"
#include "boss.h"

static int playerX = 1;
static int playerY = 1;

World *initializeWorlds() {
    World *eastBlue = malloc(sizeof(World));
    strncpy(eastBlue->name, "East Blue", 20);
    strncpy(eastBlue->description, "Une mer calme, parfaite pour commencer l'aventure.", 100);

    eastBlue->npcs = createNPC("Shanks", "Deviens plus fort et rejoins-moi sur Grand Line !", QUEST_GIVER);
    eastBlue->enemies = NULL;

    World *grandLine = malloc(sizeof(World));
    strncpy(grandLine->name, "Grand Line", 20);
    strncpy(grandLine->description, "Un ocean imprevisible avec des ennemis redoutables.", 100);

    grandLine->npcs = createNPC("Rayleigh", "Je peux t'aider a maitriser le Haki.", FRIENDLY);
    grandLine->enemies = NULL;

    eastBlue->next = grandLine;
    grandLine->next = NULL;

    return eastBlue;
}

void exploreWorld(World *world, Player *player) {
    printf("\n[EXPLORATION] Monde : %s\n", world->name);
    printf("Description : %s\n", world->description);

    displayWorldMap(world);

    triggerRandomEvent(world, player);
}

void displayWorldMap(World *world) {
    printf("\n=== Carte de %s ===\n", world->name);
    printf("+------------------+\n");
    for (int i = 0; i < 3; i++) {
        printf("| ");
        for (int j = 0; j < 3; j++) {
            if (i == playerX && j == playerY) {
                printf("J "); // Joueur
            } else if (i == 0 && j == 1) {
                printf("~ "); // Vague (meteo)
            } else if (i == 1 && (j == 0 || j == 1 || j == 2)) {
                printf("P "); // PNJ
            } else if (i == 2 && j == 0) {
                printf("B "); // Boss
            } else if (i == 2 && j == 1) {
                printf("N "); // Navire
            } else {
                printf(". "); // Vide
            }
        }
        printf("|\n");
    }
    printf("+------------------+\n");
}

void moveOnMap(World *world, Player *player, char direction) {
    int dx = 0, dy = 0;
    switch (direction) {
        case 'z': dx = -1; break;
        case 's': dx = 1; break;
        case 'q': dy = -1; break;
        case 'd': dy = 1; break;
        default:
            printf("[!] Direction invalide !\n");
            return;
    }

    int newX = playerX + dx;
    int newY = playerY + dy;

    if (newX >= 0 && newX < 3 && newY >= 0 && newY < 3) {
        playerX = newX;
        playerY = newY;
        displayWorldMap(world);

        if (playerX == 0 && playerY == 1) {
            printf("[METEO] Une tempete vous secoue ! -5 energie\n");
            player->energy -= 5;
        } else if (playerX == 1 && (playerY == 0 || playerY == 1 || playerY == 2)) {
            printf("[PNJ] Vous rencontrez un personnage.\n");
            if (world->npcs) talkToNPC(world->npcs);
        } else if (playerX == 2 && playerY == 0) {
            printf("[BOSS] Vous entrez dans la zone du boss !\n");
            start_boss_fight(player);
        } else if (playerX == 2 && playerY == 1) {
            printf("[DECOUVERTE] Vous decouvrez un navire abandonne.\n");
        } else {
            printf("[INFO] Rien d'interessant ici...\n");
        }
    } else {
        printf("[!] Impossible d'aller plus loin dans cette direction !\n");
    }
}

void triggerRandomEvent(World *world, Player *player) {
    srand(time(NULL));
    int event = rand() % 3;

    switch (event) {
        case 0:
            printf("[COMBAT] Un ennemi surgit !\n");
            Enemy *enemy = createEnemy("Bandit", 30, 5);
            startCombat(player, enemy);
            freeEnemy(enemy);
            break;
        case 1:
            printf("[RENCONTRE] Vous croisez un PNJ mysterieux...\n");
            break;
        case 2:
            printf("[TRESOR] Vous trouvez une potion d'energie !\n");
            player->energy += 10;
            break;
    }
}

void freeWorlds(World *worlds) {
    while (worlds) {
        World *temp = worlds;
        worlds = worlds->next;
        free(temp);
    }
}
