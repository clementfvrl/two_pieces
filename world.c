#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "world.h"
#include "npc.h"
#include "combat.h"
#include "services.h"

World *initializeWorlds()
{
    // Initialize East Blue
    World *eastBlue = malloc(sizeof(World));
    strncpy(eastBlue->name, "East Blue", 20);
    strncpy(eastBlue->description, "Une mer calme, parfaite pour commencer l'aventure.", 100);

    // East Blue NPCs
    eastBlue->npcs = createNPC("Shanks", "Deviens plus fort et rejoins-moi sur Grand Line !", QUEST_GIVER);
    NPC *makino = createNPC("Makino", "Bienvenue au bar du village ! Je peux te restaurer.", MERCHANT);
    makino->next = eastBlue->npcs->next;
    eastBlue->npcs->next = makino;

    NPC *mayor = createNPC("Woop Slap", "Fais attention à toi, Luffy. La mer est dangereuse!", FRIENDLY);
    mayor->next = makino->next;
    makino->next = mayor;

    // East Blue Services
    eastBlue->services = malloc(sizeof(Service));
    strcpy(eastBlue->services->name, "Bar de Makino");
    eastBlue->services->type = HEAL;
    eastBlue->services->cost = 5;

    // Initialize Grand Line
    World *grandLine = malloc(sizeof(World));
    strncpy(grandLine->name, "Grand Line", 20);
    strncpy(grandLine->description, "Un océan imprévisible avec des ennemis redoutables.", 100);

    // Grand Line NPCs
    grandLine->npcs = createNPC("Rayleigh", "Je peux t'aider à maîtriser le Haki.", FRIENDLY);
    NPC *shakky = createNPC("Shakky", "Bienvenue au bar de l'Arnaque. Des nouvelles fraîches?", MERCHANT);
    shakky->next = grandLine->npcs->next;
    grandLine->npcs->next = shakky;

    NPC *crocus = createNPC("Crocus", "J'étais le médecin de bord de Gold Roger.", QUEST_GIVER);
    crocus->next = shakky->next;
    shakky->next = crocus;

    // Grand Line Services
    grandLine->services = malloc(sizeof(Service));
    strcpy(grandLine->services->name, "Entraînement de Rayleigh");
    grandLine->services->type = TRAIN;
    grandLine->services->cost = 15;

    // Initialize Water 7
    World *water7 = malloc(sizeof(World));
    strncpy(water7->name, "Water 7", 20);
    strncpy(water7->description, "Une ville construite sur l'eau, célèbre pour ses charpentiers.", 100);

    // Water 7 NPCs
    water7->npcs = createNPC("Iceburg", "Merry ne peut plus naviguer. Je te propose un nouveau navire.", QUEST_GIVER);
    NPC *franky = createNPC("Franky", "SUPER! Tu as besoin d'un charpentier dans ton équipage?", FRIENDLY);
    franky->next = water7->npcs->next;
    water7->npcs->next = franky;

    NPC *paulie = createNPC("Paulie", "Je peux te vendre des cordages spéciaux pour ton navire.", MERCHANT);
    paulie->next = franky->next;
    franky->next = paulie;

    // Water 7 Services
    water7->services = malloc(sizeof(Service));
    strcpy(water7->services->name, "Galley-La Company");
    water7->services->type = SHOP;
    water7->services->cost = 20;

    // Initialize Skypiea
    World *skypiea = malloc(sizeof(World));
    strncpy(skypiea->name, "Skypiea", 20);
    strncpy(skypiea->description, "Une île dans les nuages avec des technologies étranges.", 100);

    // Skypiea NPCs
    skypiea->npcs = createNPC("Gan Fall", "Je suis l'ancien dieu de cette île céleste.", FRIENDLY);
    NPC *conis = createNPC("Conis", "Je peux vous guider à travers Skypiea.", QUEST_GIVER);
    conis->next = skypiea->npcs->next;
    skypiea->npcs->next = conis;

    NPC *mckinely = createNPC("McKinley", "Paiement de l'extorsion, s'il vous plaît !", MERCHANT);
    mckinely->next = conis->next;
    conis->next = mckinely;

    // Skypiea Services
    skypiea->services = malloc(sizeof(Service));
    strcpy(skypiea->services->name, "Dials de Conis");
    skypiea->services->type = SHOP;
    skypiea->services->cost = 25;

    // Initialize New World
    World *newWorld = malloc(sizeof(World));
    strncpy(newWorld->name, "Nouveau Monde", 20);
    strncpy(newWorld->description, "La partie la plus dangereuse de Grand Line, où les plus forts règnent.", 100);

    // New World NPCs
    newWorld->npcs = createNPC("Jinbe", "La route est dangereuse, je peux vous aider à naviguer.", FRIENDLY);
    NPC *hancock = createNPC("Boa Hancock", "Luffy, je ferai tout pour t'aider!", QUEST_GIVER);
    hancock->next = newWorld->npcs->next;
    newWorld->npcs->next = hancock;

    NPC *ivankov = createNPC("Emporio Ivankov", "Hee-Haw! Tu as besoin de motivation?", MERCHANT);
    ivankov->next = hancock->next;
    hancock->next = ivankov;

    // New World Services
    newWorld->services = malloc(sizeof(Service));
    strcpy(newWorld->services->name, "Entraînement intensif");
    newWorld->services->type = TRAIN;
    newWorld->services->cost = 30;

    // Link worlds together
    eastBlue->next = grandLine;
    grandLine->next = water7;
    water7->next = skypiea;
    skypiea->next = newWorld;
    newWorld->next = NULL;

    return eastBlue;
}

void exploreWorld(World *world, Player *player)
{
    printf("\n🌍 Vous explorez : %s\n", world->name);
    printf("📜 %s\n", world->description);

    displayWorldMap(world);

    // Display available services
    if (world->services)
    {
        printf("\n🏪 Services disponibles :\n");
        printf("- %s (", world->services->name);

        switch (world->services->type)
        {
        case HEAL:
            printf("Soins");
            break;
        case TRAIN:
            printf("Entraînement");
            break;
        case SHOP:
            printf("Boutique");
            break;
        }

        printf(", coût: %d énergie)\n", world->services->cost);

        printf("\nVoulez-vous utiliser ce service? (1: Oui, 0: Non) > ");
        int useService;
        scanf("%d", &useService);

        if (useService == 1)
        {
            interactWithService(player, world->services);
        }
    }

    // Trigger random event with more variety
    triggerRandomEvent(world, player);
}

void displayWorldMap(World *world)
{
    printf("\n🗺️ Carte de %s :\n", world->name);

    if (strcmp(world->name, "East Blue") == 0)
    {
        printf("+------------------+\n");
        printf("|  🏠  🌊  🏝️       |\n");
        printf("|       🚢         |\n");
        printf("|  🐟    🌊  🏝️     |\n");
        printf("+------------------+\n");
    }
    else if (strcmp(world->name, "Grand Line") == 0)
    {
        printf("+------------------+\n");
        printf("|  🌪️  🌊  ⛈️    ☠️ |\n");
        printf("|  🏝️  🚢  🐋       |\n");
        printf("|  🌋    🌊  🏝️     |\n");
        printf("+------------------+\n");
    }
    else if (strcmp(world->name, "Water 7") == 0)
    {
        printf("+------------------+\n");
        printf("|  🏢  🌊  🏢       |\n");
        printf("|  🚢  🌉  🚢       |\n");
        printf("|  🏠  🌊  🏠       |\n");
        printf("+------------------+\n");
    }
    else if (strcmp(world->name, "Skypiea") == 0)
    {
        printf("+------------------+\n");
        printf("|  ☁️  🏝️  ☁️       |\n");
        printf("|  ☁️  🚢  ☁️       |\n");
        printf("|  ☁️  ⚡  ☁️       |\n");
        printf("+------------------+\n");
    }
    else if (strcmp(world->name, "Nouveau Monde") == 0)
    {
        printf("+------------------+\n");
        printf("|  🌋  🌊  ❄️       |\n");
        printf("|  🏝️  🚢  🔥       |\n");
        printf("|  ⚡  🌊  🌪️       |\n");
        printf("+------------------+\n");
    }
}

void triggerRandomEvent(World *world, Player *player)
{
    srand(time(NULL)); // Initialize random seed

    // More varied random events based on world
    int maxEvents = 5; // Increase number of possible events
    int event = rand() % maxEvents;

    // Common event probability
    if (event < 3)
    {
        // Basic events that can happen anywhere
        switch (event)
        {
        case 0:
            printf("⚔️ Un ennemi surgit !\n");
            // Different enemies based on world
            Enemy *enemy;
            if (strcmp(world->name, "East Blue") == 0)
            {
                enemy = createEnemy("Bandit des Montagnes", 20, 3);
            }
            else if (strcmp(world->name, "Grand Line") == 0)
            {
                enemy = createEnemy("Marine", 40, 5);
            }
            else if (strcmp(world->name, "Water 7") == 0)
            {
                enemy = createEnemy("Agent du CP9", 60, 8);
            }
            else if (strcmp(world->name, "Skypiea") == 0)
            {
                enemy = createEnemy("Guerrier Shandian", 50, 7);
            }
            else
            {
                enemy = createEnemy("Pirate du Nouveau Monde", 80, 10);
            }

            startCombat(player, enemy);
            freeEnemy(enemy);
            break;

        case 1:
            printf("💬 Vous rencontrez un voyageur mystérieux...\n");
            printf("'Ah, un pirate! Je cherche quelqu'un pour m'aider.'\n");
            printf("Acceptez-vous de l'aider? (1: Oui, 0: Non) > ");

            int choice;
            scanf("%d", &choice);

            if (choice == 1)
            {
                printf("'Merci! Voici une récompense pour ta gentillesse.'\n");
                player->energy += 15;
                printf("Vous gagnez 15 points d'énergie! (Total: %d)\n", player->energy);
            }
            else
            {
                printf("'Je comprends, bonne route pirate!'\n");
            }
            break;

        case 2:
            printf("🎁 Vous trouvez un coffre !\n");
            int treasureType = rand() % 3;

            switch (treasureType)
            {
            case 0:
                printf("Le coffre contient une potion de soin !\n");
                player->health += 20;
                if (player->health > 100)
                    player->health = 100;
                printf("Vous récupérez 20 points de vie ! (Total: %d/100)\n", player->health);
                break;
            case 1:
                printf("Le coffre contient un fruit étrange...\n");
                player->strength += 3;
                printf("Vous gagnez 3 points de force ! (Total: %d)\n", player->strength);
                break;
            case 2:
                printf("Le coffre contient une boisson énergisante !\n");
                player->energy += 25;
                printf("Vous gagnez 25 points d'énergie ! (Total: %d)\n", player->energy);
                break;
            }
            break;
        }
    }
    else
    {
        // World-specific events
        if (strcmp(world->name, "East Blue") == 0)
        {
            printf("🌊 Une petite tempête se lève...\n");
            printf("Vous décidez de vous abriter dans une grotte côtière.\n");
            printf("À l'intérieur, vous trouvez un vieux coffre abandonné !\n");
            player->energy += 10;
            printf("Vous gagnez 10 points d'énergie ! (Total: %d)\n", player->energy);
        }
        else if (strcmp(world->name, "Grand Line") == 0)
        {
            printf("🧲 La boussole devient folle à cause du champ magnétique !\n");
            printf("Vous vous perdez pendant quelques heures...\n");
            player->energy -= 10;
            if (player->energy < 0)
                player->energy = 0;
            printf("Vous perdez 10 points d'énergie. (Total: %d)\n", player->energy);
        }
        else if (strcmp(world->name, "Water 7") == 0)
        {
            printf("🌊 L'Aqua Laguna approche ! L'eau monte dans les rues.\n");
            printf("Vous aidez des habitants à se mettre à l'abri.\n");
            player->strength += 2;
            printf("Cet effort vous rend plus fort ! (+2 force, Total: %d)\n", player->strength);
        }
        else if (strcmp(world->name, "Skypiea") == 0)
        {
            printf("⚡ Un éclair d'Enel frappe près de vous !\n");
            int damage = rand() % 10 + 5;
            player->health -= damage;
            printf("Vous prenez %d points de dégâts ! (Santé: %d/100)\n", damage, player->health);
        }
        else if (strcmp(world->name, "Nouveau Monde") == 0)
        {
            printf("🌋 Une île volcanique entre en éruption près de vous !\n");
            printf("La chaleur est intense mais vous résistez...\n");
            player->strength += 5;
            player->health -= 10;
            printf("Vous gagnez 5 points de force mais perdez 10 points de vie.\n");
            printf("Force: %d, Santé: %d/100\n", player->strength, player->health);
        }
    }
}

void freeWorlds(World *worlds)
{
    while (worlds)
    {
        World *temp = worlds;
        worlds = worlds->next;

        // Free NPCs linked to this world
        freeNPCs(temp->npcs);

        // Free services
        if (temp->services)
        {
            free(temp->services);
        }

        free(temp);
    }
}