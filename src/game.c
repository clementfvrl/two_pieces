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
                printf("\nSélectionnez un monde :\n");
                World *current = worlds;
                int i = 1;
                while (current != NULL) {
                    printf("%d. %s\n", i, current->name);
                    current = current->next;
                    i++;
                }
                printf("> ");
                int worldChoice;
                scanf("%d", &worldChoice);

                current = worlds;
                for (int j = 1; j < worldChoice && current != NULL; j++) {
                    current = current->next;
                }

                if (current != NULL) {
                    int inWorld = 1;
                    while (inWorld) {
                        printf("\nVous êtes dans le monde : %s\n", current->name);
                        printf("1. Explorer (événement aléatoire)\n");
                        printf("2. Se déplacer sur la carte\n");
                        printf("3. Revenir au menu principal\n");
                        printf("> ");
                        int action;
                        if (scanf("%d", &action) != 1) {
                            int c;
                            while ((c = getchar()) != '\n' && c != EOF);
                            printf("Entrée invalide.\n");
                            continue;
                        }

                        switch (action) {
                            case 1:
                                exploreWorld(current, &luffy);
                                if (current->npcs) {
                                    printf("\n💬 Vous rencontrez %s !\n", current->npcs->name);
                                    talkToNPC(current->npcs);
                                }
                                break;
                            case 2:
                                printf("Direction ? (z=haut, s=bas, q=gauche, d=droite) : ");
                                char dir;
                                scanf(" %c", &dir);
                                moveOnMap(current, &luffy, dir);
                                break;
                            case 3:
                                inWorld = 0;
                                break;
                            default:
                                printf("Choix invalide.\n");
                        }
                    }
                } else {
                    printf("❌ Monde invalide !\n");
                }
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
