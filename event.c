#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "event.h"
#include "time.h"

void initEventQueue(EventQueue *queue)
{
    queue->head = NULL;
}

void addEvent(
    EventQueue *queue,
    char *emitter,
    char *target,
    EventType type,
    const SimulationTime *execTime,
    void *emitterPtr,
    void *targetPtr,
    void *contextData,
    EventHandler handler)
{
    Event *newEvent = (Event *)malloc(sizeof(Event));
    if (!newEvent)
    {
        printf("Erreur: Échec d'allocation de mémoire pour nouvel événement.\n");
        return;
    }

    strncpy(newEvent->emitter, emitter, 19);
    newEvent->emitter[19] = '\0'; // Ensure null-termination

    strncpy(newEvent->target, target, 19);
    newEvent->target[19] = '\0'; // Ensure null-termination

    newEvent->type = type;
    newEvent->execution_time = getTimeInMinutes(execTime);
    newEvent->emitterPtr = emitterPtr;
    newEvent->targetPtr = targetPtr;
    newEvent->contextData = contextData;
    newEvent->handler = handler;

    // Insert the event in order of execution time
    if (queue->head == NULL || queue->head->execution_time > newEvent->execution_time)
    {
        // Insert at the beginning
        newEvent->next = queue->head;
        queue->head = newEvent;
    }
    else
    {
        // Find the right position
        Event *current = queue->head;
        while (current->next != NULL && current->next->execution_time <= newEvent->execution_time)
        {
            current = current->next;
        }
        // Insert after current
        newEvent->next = current->next;
        current->next = newEvent;
    }
}

void scheduleEvent(
    EventQueue *queue,
    char *emitter,
    char *target,
    EventType type,
    const SimulationTime *currentTime,
    int delayMinutes,
    void *emitterPtr,
    void *targetPtr,
    void *contextData,
    EventHandler handler)
{
    // Create a copy of the current time
    SimulationTime execTime = *currentTime;

    // Add the delay
    advanceTime(&execTime, delayMinutes);

    // Add the event with the calculated execution time
    addEvent(queue, emitter, target, type, &execTime, emitterPtr, targetPtr, contextData, handler);
}

// Schedule a recurring event that repeats periodically
void scheduleRecurringEvent(
    EventQueue *queue,
    char *emitter,
    char *target,
    EventType type,
    const SimulationTime *currentTime,
    int delayMinutes,
    void *emitterPtr,
    void *targetPtr,
    void *contextData,
    EventHandler handler,
    RecurringEventHandler recurHandler)
{
    // Store the recurring handler and interval in the context
    RecurringEventContext *recurContext = malloc(sizeof(RecurringEventContext));
    if (!recurContext)
    {
        printf("Erreur: Impossible d'allouer la mémoire pour l'événement récurrent.\n");
        return;
    }

    recurContext->userData = contextData;
    recurContext->queue = queue;
    recurContext->emitter = strdup(emitter);
    recurContext->target = strdup(target);
    recurContext->type = type;
    recurContext->interval = delayMinutes;
    recurContext->emitterPtr = emitterPtr;
    recurContext->targetPtr = targetPtr;
    recurContext->handler = handler;
    recurContext->recurHandler = recurHandler;

    // Schedule the initial event with the recurring context
    scheduleEvent(queue, emitter, target, type, currentTime, delayMinutes,
                  emitterPtr, targetPtr, recurContext, recurringEventWrapper);
}

// Wrapper that executes the event and reschedules it
void recurringEventWrapper(void *emitter, void *target, void *context)
{
    RecurringEventContext *recurContext = (RecurringEventContext *)context;

    // Call the actual handler
    if (recurContext->handler)
    {
        recurContext->handler(emitter, target, recurContext->userData);
    }

    // Get current time
    SimulationTime currentTime;
    getCurrentTime(&currentTime); // This function would need to be implemented

    // Check if we should reschedule based on custom logic
    if (recurContext->recurHandler == NULL ||
        recurContext->recurHandler(emitter, target, recurContext->userData))
    {

        // Reschedule the event
        scheduleEvent(recurContext->queue, recurContext->emitter, recurContext->target,
                      recurContext->type, &currentTime, recurContext->interval,
                      recurContext->emitterPtr, recurContext->targetPtr,
                      recurContext, recurringEventWrapper);
    }
    else
    {
        // Clean up if we're not rescheduling
        free(recurContext->emitter);
        free(recurContext->target);
        free(recurContext);
    }
}

// Function to get the current simulation time (would need to be implemented elsewhere)
void getCurrentTime(SimulationTime *time)
{
    // This would normally access the game's global time
    // For now, we'll just initialize it to defaults
    time->minutes = 0;
    time->hours = 8;
    time->days = 1;
    time->months = 1;
    time->years = 0;
    time->time_speed = 1;
}

void processEvents(EventQueue *queue, const SimulationTime *currentTime)
{
    int currentTimeInMinutes = getTimeInMinutes(currentTime);
    Event *prev = NULL, *current = queue->head;

    // Print debug info
    char timeStr[100];
    formatTimeString(currentTime, timeStr, sizeof(timeStr));
    printf("\nTraitement des événements à %s...\n", timeStr);

    while (current != NULL)
    {
        if (current->execution_time <= currentTimeInMinutes)
        {
            // Execute the event
            printf("Exécution de l'événement: %s -> %s [",
                   current->emitter, current->target);

            // Print event type
            switch (current->type)
            {
            case COMBAT:
                printf("COMBAT");
                break;
            case DIALOGUE:
                printf("DIALOGUE");
                break;
            case DEPLACEMENT:
                printf("DEPLACEMENT");
                break;
            case SOIN:
                printf("SOIN");
                break;
            case RECRUTEMENT:
                printf("RECRUTEMENT");
                break;
            case METEO:
                printf("METEO");
                break;
            case MARCHANDISE:
                printf("MARCHANDISE");
                break;
            case ENTRAINEMENT:
                printf("ENTRAINEMENT");
                break;
            default:
                printf("INCONNU");
                break;
            }
            printf("]\n");

            // Call the handler if it exists
            if (current->handler)
            {
                current->handler(current->emitterPtr, current->targetPtr, current->contextData);
            }

            // Remove the event from the queue
            if (prev)
            {
                prev->next = current->next;
            }
            else
            {
                queue->head = current->next;
            }

            Event *toFree = current;
            current = (prev) ? prev->next : queue->head;

            // Free recurring event context if needed
            if (toFree->type == RECURRING)
            {
                RecurringEventContext *recurContext = (RecurringEventContext *)toFree->contextData;
                if (recurContext)
                {
                    free(recurContext->emitter);
                    free(recurContext->target);
                    free(recurContext);
                }
            }

            free(toFree);
        }
        else
        {
            prev = current;
            current = current->next;
        }
    }

    if (prev == NULL && queue->head == NULL)
    {
        printf("Aucun événement à traiter.\n");
    }
}

void freeEventQueue(EventQueue *queue)
{
    Event *current = queue->head;
    while (current)
    {
        Event *next = current->next;

        // Free recurring event context if needed
        if (current->type == RECURRING)
        {
            RecurringEventContext *recurContext = (RecurringEventContext *)current->contextData;
            if (recurContext)
            {
                free(recurContext->emitter);
                free(recurContext->target);
                free(recurContext);
            }
        }

        free(current);
        current = next;
    }
    queue->head = NULL;
}