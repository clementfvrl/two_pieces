#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "player.h"
#include "world.h"
#include "save.h"
#include "time.h"
#include "event.h"

void startGame() {
    Player luffy = createPlayer("Luffy");
    SimulationTime simTime;
    EventQueue eventQueue;
    
    initSimulationTime(&simTime);
    initEventQueue(&eventQueue);

    World *worlds = initializeWorlds();
    
    int running = 1;
    while (running) {
        displayTime(&simTime);
        
        printf("\nQue voulez-vous faire ?\n");
        printf("1. Explorer un monde\n");
        printf("2. Modifier la vitesse de simulation\n");
        printf("3. Avancer le temps simulé\n");
        printf("4. Sauvegarder la simulation\n");
        printf("5. Charger une sauvegarde\n");
        printf("6. Quitter\n");
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                exploreWorld(worlds, &luffy);
                break;
            case 2:
                printf("Nouvelle vitesse (facteur de simulation) : ");
                int newSpeed;
                scanf("%d", &newSpeed);
                setTimeSpeed(&simTime, newSpeed);
                break;
            case 3:
                printf("Combien de ticks avancer ? ");
                int ticks;
                scanf("%d", &ticks);
                advanceTime(&simTime, ticks);
                processEvents(&eventQueue, simTime.current_time);
                break;
            case 4:
                saveGame(&luffy, worlds, &simTime, "save.txt");
                printf("Simulation sauvegardée.\n");
                break;
            case 5:
                loadGame(&luffy, &simTime, "save.txt");
                printf("Simulation chargée.\n");
                break;
            case 6:
                running = 0;
                printf("Fin de la simulation.\n");
                break;
            default:
                printf("Choix invalide.\n");
        }
    }

    freeWorlds(worlds);
}