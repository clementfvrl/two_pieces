#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "player.h"
#include "world.h"
#include "save.h"
#include "time.h"
#include "event.h"
#include "combat.h"

void combatEventHandler(void *emitter, void *target, void *context)
{
    Player *player = (Player *)emitter;
    Enemy *enemy = (Enemy *)target;

    printf("⚔️ Combat déclenché entre %s et %s !\n", player->name, enemy->name);
    startCombat(player, enemy);
}

void healEventHandler(void *emitter, void *target, void *context)
{
    (void)emitter;
    Player *player = (Player *)target;
    int healAmount = *((int *)context);

    player->health += healAmount;
    if (player->health > 100)
        player->health = 100;

    printf("💚 %s a regagné %d points de vie ! (Total: %d/100)\n",
           player->name, healAmount, player->health);
}

void startGame()
{
    Player luffy = createPlayer("Luffy");
    SimulationTime simTime;
    EventQueue eventQueue;

    initSimulationTime(&simTime);
    initEventQueue(&eventQueue);

    World *worlds = initializeWorlds();

    int healAmount = 20;
    scheduleEvent(&eventQueue, "System", luffy.name, SOIN, &simTime, 60,
                  NULL, &luffy, &healAmount, healEventHandler);

    int running = 1;
    while (running)
    {
        printf("\n===================================\n");
        displayTime(&simTime);
        printf("===================================\n");
        displayPlayerStats(&luffy);
        printf("===================================\n");

        printf("\nQue voulez-vous faire ?\n");
        printf("1. Explorer un monde\n");
        printf("2. Modifier la vitesse de simulation\n");
        printf("3. Avancer le temps simulé\n");
        printf("4. Sauvegarder la simulation\n");
        printf("5. Charger une sauvegarde\n");
        printf("6. Quitter\n");
        printf("> ");

        int choice;
        if (scanf("%d", &choice) != 1)
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Entrée invalide. Veuillez entrer un nombre.\n");
            continue;
        }

        switch (choice)
        {
        case 1:
        {
            printf("\nSélectionnez un monde :\n");
            World *current = worlds;
            int i = 1;
            while (current != NULL)
            {
                printf("%d. %s\n", i, current->name);
                current = current->next;
                i++;
            }
            printf("> ");

            int worldChoice;
            if (scanf("%d", &worldChoice) != 1)
            {
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                printf("Entrée invalide. Veuillez entrer un nombre.\n");
                continue;
            }

            current = worlds;
            for (int j = 1; j < worldChoice && current != NULL; j++)
                current = current->next;

            if (current != NULL)
            {
                int inWorld = 1;
                while (inWorld)
                {
                    printf("\nVous êtes dans le monde : %s\n", current->name);
                    printf("1. Explorer (événement aléatoire)\n");
                    printf("2. Se déplacer sur la carte\n");
                    printf("3. Revenir au menu principal\n");
                    printf("> ");
                    int action;
                    if (scanf("%d", &action) != 1)
                    {
                        int c;
                        while ((c = getchar()) != '\n' && c != EOF);
                        printf("Entrée invalide.\n");
                        continue;
                    }

                    switch (action)
                    {
                    case 1:
                        exploreWorld(current, &luffy);
                        if (current->npcs)
                        {
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
            }
            else
            {
                printf("❌ Monde invalide !\n");
            }
            break;
        }
        case 2:
        {
            printf("Nouvelle vitesse (facteur de simulation, 1-10) : ");
            int newSpeed;
            if (scanf("%d", &newSpeed) != 1)
            {
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                printf("Entrée invalide. Veuillez entrer un nombre.\n");
                continue;
            }

            if (newSpeed < 1 || newSpeed > 10)
            {
                printf("La vitesse doit être entre 1 et 10.\n");
            }
            else
            {
                setTimeSpeed(&simTime, newSpeed);
            }
            break;
        }
        case 3:
        {
            printf("Options d'avancement du temps:\n");
            printf("1. Minutes\n");
            printf("2. Heures\n");
            printf("3. Jours\n");
            printf("> ");

            int timeChoice;
            if (scanf("%d", &timeChoice) != 1)
            {
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                printf("Entrée invalide. Veuillez entrer un nombre.\n");
                continue;
            }

            int timeAmount = 0;
            switch (timeChoice)
            {
            case 1:
                printf("Combien de minutes avancer ? ");
                scanf("%d", &timeAmount);
                break;
            case 2:
                printf("Combien d'heures avancer ? ");
                scanf("%d", &timeAmount);
                timeAmount *= 60;
                break;
            case 3:
                printf("Combien de jours avancer ? ");
                scanf("%d", &timeAmount);
                timeAmount *= 24 * 60;
                break;
            default:
                printf("Option invalide.\n");
                continue;
            }

            if (timeAmount <= 0)
            {
                printf("Le temps à avancer doit être positif.\n");
                continue;
            }

            printf("Avancement du temps...\n");
            advanceTime(&simTime, timeAmount);
            processEvents(&eventQueue, &simTime);
            break;
        }
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

    freeEventQueue(&eventQueue);
    freeWorlds(worlds);
}
