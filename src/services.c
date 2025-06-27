#include <stdio.h>
#include "../include/services.h"

void interactWithService(Player *player, Service *service) {
    switch (service->type) {
        case HEAL:
            if (player->energy >= service->cost) {
                player->health = 100;
                player->energy -= service->cost;
                printf("Vous avez été soigné ! Santé restaurée.\n");
            } else {
                printf("Pas assez d'énergie pour ce service.\n");
            }
            break;
        case TRAIN:
            if (player->energy >= service->cost) {
                player->strength += 5;
                player->energy -= service->cost;
                printf("Entraînement terminé. Force augmentée !\n");
            } else {
                printf("Vous êtes trop fatigué pour vous entraîner.\n");
            }
            break;
        case SHOP:
            printf("Achat d'objets non implémenté pour l'instant.\n");
            break;
    }
}