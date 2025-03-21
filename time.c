#include <stdio.h>
#include <string.h>
#include "time.h"

void initSimulationTime(SimulationTime *simTime)
{
    simTime->minutes = 0;
    simTime->hours = 8; // Start at 8:00 AM
    simTime->days = 1;
    simTime->months = 1;
    simTime->years = 0;
    simTime->time_speed = 1;
}

void advanceTime(SimulationTime *simTime, int minutes)
{
    // Apply time speed multiplier
    int totalMinutesToAdd = minutes * simTime->time_speed;

    // Add minutes and handle overflow
    simTime->minutes += totalMinutesToAdd;

    // Handle overflow for minutes -> hours
    while (simTime->minutes >= MINUTES_PER_HOUR)
    {
        simTime->minutes -= MINUTES_PER_HOUR;
        simTime->hours++;

        // Handle overflow for hours -> days
        if (simTime->hours >= HOURS_PER_DAY)
        {
            simTime->hours -= HOURS_PER_DAY;
            simTime->days++;

            // Handle overflow for days -> months
            if (simTime->days > DAYS_PER_MONTH)
            {
                simTime->days = 1;
                simTime->months++;

                // Handle overflow for months -> years
                if (simTime->months > 12)
                {
                    simTime->months = 1;
                    simTime->years++;
                }
            }
        }
    }
}

void setTimeSpeed(SimulationTime *simTime, int speed)
{
    if (speed > 0)
    {
        simTime->time_speed = speed;
        printf("Vitesse de simulation réglée à x%d\n", speed);
    }
    else
    {
        printf("La vitesse doit être positive !\n");
    }
}

void displayTime(const SimulationTime *simTime)
{
    char timeStr[100];
    formatTimeString(simTime, timeStr, sizeof(timeStr));
    printf("Temps simulé actuel: %s\n", timeStr);
    printf("Vitesse de simulation: x%d\n", simTime->time_speed);
}

int getTimeInMinutes(const SimulationTime *simTime)
{
    return simTime->minutes +
           simTime->hours * MINUTES_PER_HOUR +
           simTime->days * HOURS_PER_DAY * MINUTES_PER_HOUR +
           simTime->months * DAYS_PER_MONTH * HOURS_PER_DAY * MINUTES_PER_HOUR +
           simTime->years * 12 * DAYS_PER_MONTH * HOURS_PER_DAY * MINUTES_PER_HOUR;
}

void formatTimeString(const SimulationTime *simTime, char *buffer, int bufferSize)
{
    // Format the time as Jour X, Mois Y, Année Z - HH:MM
    const char *monthNames[] = {
        "Janvier", "Février", "Mars", "Avril", "Mai", "Juin",
        "Juillet", "Août", "Septembre", "Octobre", "Novembre", "Décembre"};

    snprintf(buffer, bufferSize, "Jour %d, %s, An %d - %02d:%02d",
             simTime->days,
             monthNames[simTime->months - 1],
             simTime->years,
             simTime->hours,
             simTime->minutes);
}