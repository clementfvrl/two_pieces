#ifndef NPC_H
#define NPC_H

typedef enum { FRIENDLY, MERCHANT, QUEST_GIVER } NPCType;

typedef struct NPC {
    char name[20];
    char dialogue[100];
    NPCType type;
    struct NPC *next;
} NPC;

NPC *createNPC(const char *name, const char *dialogue, NPCType type);
void talkToNPC(NPC *npc);
void freeNPCs(NPC *head);

#endif