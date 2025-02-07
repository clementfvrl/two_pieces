#include <stdio.h>
#include "time.h"

void initSimulationTime(SimulationTime *simTime) {
    simTime->current_time = 0;
    simTime->time_speed = 1;
}

void advanceTime(SimulationTime *simTime, int ticks) {
    simTime->current_time += ticks * simTime->time_speed;
}

void setTimeSpeed(SimulationTime *simTime, int speed) {
    if (speed > 0) {
        simTime->time_speed = speed;
        printf("Vitesse de simulation réglée à x%d\n", speed);
    }
}

void displayTime(const SimulationTime *simTime) {
    printf("Temps simulé actuel: %d\n", simTime->current_time);
}