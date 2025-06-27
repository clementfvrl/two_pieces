#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/npc.h"

NPC *createNPC(const char *name, const char *dialogue, NPCType type) {
    NPC *npc = malloc(sizeof(NPC));
    strncpy(npc->name, name, 20);
    strncpy(npc->dialogue, dialogue, 100);
    npc->type = type;
    npc->next = NULL;
    return npc;
}

void talkToNPC(NPC *npc) {
    if (!npc) return;
    printf("\n💬 %s : \"%s\"\n", npc->name, npc->dialogue);

    if (npc->type == MERCHANT) {
        printf("🛒 Ce PNJ vend des objets (à implémenter).\n");
    } else if (npc->type == QUEST_GIVER) {
        printf("🎯 Ce PNJ peut donner une quête !\n");
    }
}

void freeNPCs(NPC *head) {
    while (head) {
        NPC *temp = head;
        head = head->next;
        free(temp);
    }
}