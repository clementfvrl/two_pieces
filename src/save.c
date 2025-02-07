#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "save.h"

void saveGame(const Player *player, const World *worlds, const SimulationTime *simTime, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Erreur : Impossible d'ouvrir le fichier de sauvegarde.\n");
        return;
    }

    // Sauvegarde des informations du joueur
    fprintf(file, "[Joueur]\n");
    fprintf(file, "%s %d %d %d\n", player->name, player->health, player->energy, player->strength);

    // Sauvegarde du temps de simulation
    fprintf(file, "[Temps]\n");
    fprintf(file, "%d %d\n", simTime->current_time, simTime->time_speed);

    fclose(file);
    printf("✔ Sauvegarde réussie dans %s !\n", filename);
}

void loadGame(Player *player, SimulationTime *simTime, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("❌ Aucun fichier de sauvegarde trouvé.\n");
        return;
    }

    char section[20];

    while (fscanf(file, "%s", section) != EOF) {
        if (strcmp(section, "[Joueur]") == 0) {
            fscanf(file, "%s %d %d %d", player->name, &player->health, &player->energy, &player->strength);
        } else if (strcmp(section, "[Temps]") == 0) {
            fscanf(file, "%d %d", &simTime->current_time, &simTime->time_speed);
        }
    }

    fclose(file);
    printf("✔ Chargement réussi depuis %s !\n", filename);
}