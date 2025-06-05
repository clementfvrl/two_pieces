#ifndef EVENT_H
#define EVENT_H

typedef enum { COMBAT, DIALOGUE, DEPLACEMENT, SOIN, RECRUTEMENT, BOSS } EventType;

typedef struct Event {
    char emitter[20];  // Qui génère l'événement ?
    char target[20];   // Qui est concerné ?
    EventType type;    // Type de l'événement
    int execution_time;// Temps d'exécution dans la simulation
    struct Event *next;// Liste chaînée pour l'échéancier
} Event;

typedef struct {
    Event *head;
} EventQueue;

void initEventQueue(EventQueue *queue);
void addEvent(EventQueue *queue, char *emitter, char *target, EventType type, int exec_time);
void processEvents(EventQueue *queue, int current_time);

#endif