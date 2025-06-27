#ifndef SERVICES_H
#define SERVICES_H

#include "player.h"

typedef enum { HEAL, TRAIN, SHOP } ServiceType;

typedef struct Service {
    char name[20];
    ServiceType type;
    int cost;  // Coût en énergie ou en monnaie
} Service;

void interactWithService(Player *player, Service *service);

#endif