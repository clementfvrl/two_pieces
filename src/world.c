#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "world.h"
#include "npc.h"
#include "combat.h"

World *initializeWorlds() {
    World *eastBlue = malloc(sizeof(World));
    strncpy(eastBlue->name, "East Blue", 20);
    strncpy(eastBlue->description, "Une mer calme, parfaite pour commencer l'aventure.", 100);
    
    eastBlue->npcs = createNPC("Shanks", "Deviens plus fort et rejoins-moi sur Grand Line !", QUEST_GIVER);
    eastBlue->enemies = NULL;

    World *grandLine = malloc(sizeof(World));
    strncpy(grandLine->name, "Grand Line", 20);
    strncpy(grandLine->description, "Un océan imprévisible avec des ennemis redoutables.", 100);
    
    grandLine->npcs = createNPC("Rayleigh", "Je peux t'aider à maîtriser le Haki.", FRIENDLY);
    grandLine->enemies = NULL;
    
    eastBlue->next = grandLine;
    grandLine->next = NULL;

    return eastBlue;
}

void exploreWorld(World *world, Player *player) {
    printf("\n🌍 Vous explorez : %s\n", world->name);
    printf("📜 %s\n", world->description);

    displayWorldMap(world);
    
    // Déclenchement d'un événement aléatoire
    triggerRandomEvent(world, player);
}

void displayWorldMap(World *world) {
    printf("\n🗺️ Carte de %s :\n", world->name);
    printf("+------------------+\n");
    printf("|       🌊         |\n");
    printf("|  🏝️  🏠  🏝️        |\n");
    printf("|       🚢         |\n");
    printf("+------------------+\n");
}

void triggerRandomEvent(World *world, Player *player) {
    srand(time(NULL)); // Initialisation de l'aléatoire
    int event = rand() % 3; // Trois types d'événements possibles

    switch (event) {
        case 0:
            printf("⚔️ Un ennemi surgit !\n");
            Enemy *enemy = createEnemy("Bandit", 30, 5);
            startCombat(player, enemy);
            freeEnemy(enemy);
            break;
        case 1:
            printf("💬 Vous rencontrez un PNJ mystérieux...\n");
            // TODO : Interaction avec un personnage
            break;
        case 2:
            printf("🎁 Vous trouvez un coffre avec une potion d'énergie !\n");
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