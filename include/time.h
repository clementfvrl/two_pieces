#ifndef TIME_H
#define TIME_H

// Define time constants
#define MINUTES_PER_HOUR 60
#define HOURS_PER_DAY 24
#define DAYS_PER_MONTH 30 // Simplified calendar for game

typedef struct
{
    int minutes;    // Current minutes (0-59)
    int hours;      // Current hours (0-23)
    int days;       // Current days (1-30)
    int months;     // Current months (1-12)
    int years;      // Current years
    int time_speed; // Acceleration factor (1x, 2x, etc.)
} SimulationTime;

// Initialize the simulation time structure
void initSimulationTime(SimulationTime *simTime);

// Advance time by specified minutes
void advanceTime(SimulationTime *simTime, int minutes);

// Set the time acceleration factor
void setTimeSpeed(SimulationTime *simTime, int speed);

// Display time in a readable format
void displayTime(const SimulationTime *simTime);

// Convert simulation time to total minutes (for event comparisons)
int getTimeInMinutes(const SimulationTime *simTime);

// Format the current time as a string
void formatTimeString(const SimulationTime *simTime, char *buffer, int bufferSize);

#endif