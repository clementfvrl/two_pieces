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
            printf("Bienvenue dans la boutique !\n");
            printf("Que voulez-vous acheter ?\n");
            printf("1. Potion d'energie (10 pieces d'or)\n");
            printf("2. equipement special (50 pieces d'or)\n");
            printf("3. Rien, merci.\n");
            int choice;
            scanf("%d", &choice);
            switch (choice) {
                case 1:
                    if (player->money >= 10) {
                        player->energy += 20;
                        player->money -= 10;
                        printf("Vous avez achete une potion d'energie !\n");
                    } else {
                        printf("Pas assez d'argent pour cette potion.\n");
                    }
                    break;
                case 2:
                    if (player->money >= 50) {
                        player->strength += 10;
                        player->money -= 50;
                        printf("Vous avez achete un equipement special !\n");
                    } else {
                        printf("Pas assez d'argent pour cet equipement.\n");
                    }
                    break;
                case 3:
                    printf("Merci de votre visite !\n");
                    break;
                default:
                    printf("Choix invalide.\n");
            }
            break;
    }
}