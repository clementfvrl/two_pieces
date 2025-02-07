#ifndef SAVE_H
#define SAVE_H

#include "player.h"
#include "world.h"
#include "time.h"

// Fonctions de sauvegarde au format texte
void saveGame(const Player *player, const World *worlds, const SimulationTime *simTime, const char *filename);
void loadGame(Player *player, SimulationTime *simTime, const char *filename);

#endif