#ifndef NPC_H
#define NPC_H

typedef struct NPC {
    char name[20];
    char dialogue[100];
    int isRecruited;
    struct NPC *next;
} NPC;

NPC *createNPC(const char *name, const char *dialogue);
void talkToNPC(NPC *npc);

#endif