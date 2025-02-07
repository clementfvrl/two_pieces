#ifndef TIME_H
#define TIME_H

typedef struct {
    int current_time;  // Temps simulé actuel
    int time_speed;    // Facteur de vitesse (ex: 1 seconde = 1 heure)
} SimulationTime;

void initSimulationTime(SimulationTime *simTime);
void advanceTime(SimulationTime *simTime, int ticks);
void setTimeSpeed(SimulationTime *simTime, int speed);
void displayTime(const SimulationTime *simTime);

#endif