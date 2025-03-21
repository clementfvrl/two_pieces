#ifndef SAVE_H
#define SAVE_H

#include "player.h"
#include "world.h"
#include "time.h"

// Save game state to file
void saveGame(const Player *player, const World *worlds, const SimulationTime *simTime, const char *filename);

// Load game state from file
void loadGame(Player *player, SimulationTime *simTime, const char *filename);

#endif