#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/player.h"

Player createPlayer(const char *name) {
    Player player;
    strncpy(player.name, name, 20);
    player.health = 100;
    player.energy = 50;
    player.strength = 10;
    player.crew = NULL; // Pas encore de membres recrutés
    return player;
}

void displayPlayerStats(const Player *player) {
    printf("=== Stats de %s ===\n", player->name);
    printf("Santé: %d\n", player->health);
    printf("Énergie: %d\n", player->energy);
    printf("Force: %d\n", player->strength);
}