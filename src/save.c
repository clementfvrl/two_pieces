#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/save.h"

void saveGame(const Player *player, const SimulationTime *simTime, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        printf("Erreur : Impossible d'ouvrir le fichier de sauvegarde.\n");
        return;
    }

    // Save version information
    fprintf(file, "[Version]\n");
    fprintf(file, "1.0\n");

    // Save player information
    fprintf(file, "[Joueur]\n");
    fprintf(file, "%s %d %d %d\n",
            player->name,
            player->health,
            player->energy,
            player->strength);

    // Save simulation time
    fprintf(file, "[Temps]\n");
    fprintf(file, "%d %d %d %d %d %d\n",
            simTime->minutes,
            simTime->hours,
            simTime->days,
            simTime->months,
            simTime->years,
            simTime->time_speed);

    // We could also save world state, events, etc.

    fclose(file);
    printf("✔ Sauvegarde réussie dans %s !\n", filename);
}

void loadGame(Player *player, SimulationTime *simTime, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("❌ Aucun fichier de sauvegarde trouvé.\n");
        return;
    }

    char section[20];
    char version[10];

    // Read file section by section
    while (fscanf(file, "%s", section) != EOF)
    {
        if (strcmp(section, "[Version]") == 0)
        {
            fscanf(file, "%s", version);
            printf("Version de sauvegarde: %s\n", version);
        }
        else if (strcmp(section, "[Joueur]") == 0)
        {
            fscanf(file, "%s %d %d %d",
                   player->name,
                   &player->health,
                   &player->energy,
                   &player->strength);
        }
        else if (strcmp(section, "[Temps]") == 0)
        {
            fscanf(file, "%d %d %d %d %d %d",
                   &simTime->minutes,
                   &simTime->hours,
                   &simTime->days,
                   &simTime->months,
                   &simTime->years,
                   &simTime->time_speed);
        }
    }

    fclose(file);
    printf("✔ Chargement réussi depuis %s !\n", filename);
}