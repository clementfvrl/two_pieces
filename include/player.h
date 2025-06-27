#ifndef PLAYER_H
#define PLAYER_H

typedef struct CrewMember {
    char name[20];
    int skill;
    struct CrewMember *next;
} CrewMember;

typedef struct {
    char name[20];
    int health;
    int energy;
    int strength;
    CrewMember *crew;
} Player;

Player createPlayer(const char *name);
void displayPlayerStats(const Player *player);

#endif