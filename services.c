#include <stdio.h>
#include "services.h"

void interactWithService(Player *player, Service *service) {
    switch (service->type) {
        case HEAL:
            if (player->energy >= service->cost) {
                player->health = 100;
                player->energy -= service->cost;
                printf("Vous avez ete soigne ! Sante restauree.\n");
            } else {
                printf("Pas assez d'energie pour ce service.\n");
            }
            break;
        case TRAIN:
            if (player->energy >= service->cost) {
                player->strength += 5;
                player->energy -= service->cost;
                printf("Entraînement termine. Force augmentee !\n");
            } else {
                printf("Vous etes trop fatigue pour vous entraîner.\n");
            }
            break;
        case SHOP:
            printf("Achat d'objets non implemente pour l'instant.\n");
            break;
    }
}