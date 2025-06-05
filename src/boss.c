#include <stdio.h>
#include "player.h"
#include "combat.h"

typedef struct {
    char name[20];
    int hp;
    int attack;
    int defense;
} Boss;

void start_boss_fight(Player *player) {
    Boss kaido = {"Kaido", 200, 30, 10};

    printf("⚠️ Vous entrez dans la zone du boss : %s !\n", kaido.name);
    printf("Un combat épique commence !\n");
    int choice;

    switch(choice) {
    printf("Choisissez votre action :\n");
    printf("1. Attaquer %s\n", kaido.name);
    printf("2. Fuir le combat\n");
    printf("> ");
    scanf(" %c", &choice);
    case 1:
        printf("Vous attaquez %s !\n", kaido.name);
        kaido.hp -= player->strength - kaido.defense;

        if (kaido.hp <= 0) {
            printf("🎉 Vous avez vaincu %s !\n", kaido.name);
            break;
        }

        printf("%s vous attaque !\n", kaido.name);
        player->health -= kaido.attack;

        if (player->health <= 0) {
            printf("💀 Vous avez été vaincu...\n");
        }

        case 2:
            printf("Vous essayez de fuir le combat...\n");
            if (rand() % 2 == 0) {
                printf("Vous avez réussi à fuir !\n");
                
            } else {
                printf("Vous n'avez pas pu fuir ! %s vous attaque !\n", kaido.name);
                player->health -= kaido.attack;

                if (player->health <= 0) {
                    printf("💀 Vous avez été vaincu...\n");
                }
            }
            break;
    }
}
