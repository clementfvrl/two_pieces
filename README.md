# TwoPieces - Simulateur RPG à Événements Discrets

Un simulateur RPG développé en C ANSI utilisant la simulation à événements discrets, permettant de gérer un héros dans un monde dynamique avec système de combat, exploration et quêtes.

## 🎮 Aperçu

TwoPieces simule un monde RPG où le temps s'écoule de manière discrète, déclenchant des événements qui modifient l'état du monde et du héros. Le joueur peut contrôler directement son personnage ou observer la simulation se dérouler automatiquement.

## 🏗️ Architecture

```
TwoPieces/
├── src/           # Code source
├── include/       # Headers (.h)
├── obj/           # Fichiers objets (généré)
├── bin/           # Exécutable (généré)
└── docs/          # Documentation
```

## 🚀 Installation et Compilation

### Prérequis
- **Compilateur C** : GCC recommandé
- **Make** : Pour la compilation automatisée
- **Système** : Linux/macOS/Windows (avec MinGW)

### Compilation
```bash
# Cloner le projet
git clone https://github.com/clementfvrl/two_pieces.git
cd two_pieces

# Compiler
make

# Exécuter
make run

# Nettoyage
make clean
```

## 🎯 Fonctionnalités

### Core Simulation
- ✅ **Moteur de temps simulé** avec vitesse paramétrable
- ✅ **File d'événements prioritaire** avec traitement chronologique  
- ✅ **Système de sauvegarde/chargement** complet
- ✅ **Interface administrateur** pour configuration

### Gameplay
- ✅ **Héros évolutif** : stats, expérience
- ✅ **Système de combat** tour par tour
- ✅ **Exploration de zones** avec événements dynamiques
- ✅ **Gestion des ressources** : santé, énergie
- ✅ **NPCs interactifs** et ennemis génératifs

## 🕹️ Utilisation

### Commandes de Jeu
- **Exploration automatique** : Le héros explore selon les événements programmés
- **Combat interactif** : Tours de combat avec calculs de dégâts
- **Progression** : Gain d'XP, level up, amélioration des stats

## 📊 Système d'Événements

Chaque événement contient :
- **Émetteur** : Entité qui génère l'action
- **Destinataire** : Cible de l'action
- **Temps d'exécution** : Quand l'événement se déclenche
- **Données** : Paramètres spécifiques

## 🛠️ Configuration

### Paramètres Modifiables
- **Vitesse de simulation** : 1x à 10x
- **Stats du héros** : Santé, Force, Energie
- **Difficulté des zones** : Niveau de danger

### Fichiers de Sauvegarde
- Format texte
- Sauvegarde complète de l'état du jeu

## 🔧 Développement

### Standards de Code
- **Langage** : C ANSI strict
- **Architecture** : Modulaire, pas de variables globales
- **Fonctions** : Maximum 20 lignes
- **Mémoire** : Gestion statique, pas de fuites

### Structure des Modules
```c
// Modules principaux
main.c      // Point d'entrée et menu
game.c      // État global et logique centrale  
player.c    // Gestion du héros
world.c     // Zones et exploration
npc.c       // NPCs et ennemis
combat.c    // Système de combat
event.c     // File d'événements
time.c      // Gestion temporelle
save.c      // Persistance
services.c  // Services utilitaires
```

## Auteurs
- Corentin BOISSIE
- Clément FAVAREL
- Angel PUTZ