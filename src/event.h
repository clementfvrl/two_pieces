#ifndef EVENT_H
#define EVENT_H

typedef enum { COMBAT, DIALOGUE, DEPLACEMENT, SOIN, RECRUTEMENT, BOSS } EventType;

typedef struct Event {
    char emitter[20];  // Qui genere l'evenement ?
    char target[20];   // Qui est concerne ?
    EventType type;    // Type de l'evenement
    int execution_time;// Temps d'execution dans la simulation
    struct Event *next;// Liste chaînee pour l'echeancier
} Event;

typedef struct {
    Event *head;
} EventQueue;

void initEventQueue(EventQueue *queue);
void addEvent(EventQueue *queue, char *emitter, char *target, EventType type, int exec_time);
void processEvents(EventQueue *queue, int current_time);

#endif