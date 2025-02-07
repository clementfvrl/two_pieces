#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "event.h"

void initEventQueue(EventQueue *queue) {
    queue->head = NULL;
}

void addEvent(EventQueue *queue, char *emitter, char *target, EventType type, int exec_time) {
    Event *newEvent = (Event *)malloc(sizeof(Event));
    strncpy(newEvent->emitter, emitter, 20);
    strncpy(newEvent->target, target, 20);
    newEvent->type = type;
    newEvent->execution_time = exec_time;
    newEvent->next = queue->head;
    queue->head = newEvent;
}

void processEvents(EventQueue *queue, int current_time) {
    Event *prev = NULL, *current = queue->head;
    while (current != NULL) {
        if (current->execution_time <= current_time) {
            printf("Exécution de l'événement: %s -> %s [%d]\n", current->emitter, current->target, current->type);
            if (prev) prev->next = current->next;
            else queue->head = current->next;
            free(current);
            current = (prev) ? prev->next : queue->head;
        } else {
            prev = current;
            current = current->next;
        }
    }
}