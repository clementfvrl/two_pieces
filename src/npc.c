#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "npc.h"

NPC *createNPC(const char *name, const char *dialogue) {
    NPC *npc = malloc(sizeof(NPC));
    strncpy(npc->name, name, 20);
    strncpy(npc->dialogue, dialogue, 100);
    npc->isRecruited = 0;
    npc->next = NULL;
    return npc;
}

void talkToNPC(NPC *npc) {
    printf("%s vous dit : %s\n", npc->name, npc->dialogue);
}