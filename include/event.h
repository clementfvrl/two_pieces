#ifndef EVENT_H
#define EVENT_H

#include "time.h"

typedef enum
{
    COMBAT,
    DIALOGUE,
    DEPLACEMENT,
    SOIN,
    RECRUTEMENT,
    METEO,        // Weather events
    MARCHANDISE,  // Merchandise arrival
    ENTRAINEMENT, // Training events
    RECURRING     // Special type for recurring events
} EventType;

// Definition types for event handler functions
struct Player; // Forward declaration
struct World;  // Forward declaration

typedef void (*EventHandler)(void *emitter, void *target, void *context);
typedef int (*RecurringEventHandler)(void *emitter, void *target, void *context); // Returns 1 to continue, 0 to stop

// Structure to hold context for recurring events
struct EventQueue; // Forward declaration
typedef struct RecurringEventContext
{
    void *userData;                     // Original context data
    struct EventQueue *queue;           // The event queue
    char *emitter;                      // Copy of emitter name
    char *target;                       // Copy of target name
    EventType type;                     // Event type
    int interval;                       // Interval in minutes for recurrence
    void *emitterPtr;                   // Pointer to the emitter object
    void *targetPtr;                    // Pointer to the target object
    EventHandler handler;               // Function to handle the event
    RecurringEventHandler recurHandler; // Function to decide if event should recur
} RecurringEventContext;

typedef struct Event
{
    char emitter[20];     // Who generates the event?
    char target[20];      // Who is affected?
    EventType type;       // Event type
    int execution_time;   // Execution time in minutes since game start
    void *emitterPtr;     // Pointer to the emitter object (Player, NPC, etc.)
    void *targetPtr;      // Pointer to the target object
    void *contextData;    // Additional context-specific data
    EventHandler handler; // Function to call when event is processed
    struct Event *next;   // Linked list for the scheduler
} Event;

typedef struct EventQueue
{
    Event *head;
} EventQueue;

void initEventQueue(EventQueue *queue);

// Add event with specific execution time
void addEvent(
    EventQueue *queue,
    char *emitter,
    char *target,
    EventType type,
    const SimulationTime *execTime,
    void *emitterPtr,
    void *targetPtr,
    void *contextData,
    EventHandler handler);

// Add event that executes after a delay
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
    void *handler);

// Schedule a recurring event
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
    RecurringEventHandler recurHandler);

// Wrapper function for recurring events
void recurringEventWrapper(void *emitter, void *target, void *context);

// Get current simulation time
void getCurrentTime(SimulationTime *time);

// Process all events that should execute by the current time
void processEvents(EventQueue *queue, const SimulationTime *currentTime);

// Free all events in the queue
void freeEventQueue(EventQueue *queue);

#endif