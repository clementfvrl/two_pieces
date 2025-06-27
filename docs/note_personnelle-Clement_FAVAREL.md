# Note Personnelle - Développement Simulateur RPG

**Projet :** Simulateur RPG à Événements Discrets
**Développeur :** Clément
**Date :** Juin 2025
**Contexte :** Projet Techniques de Programmation - C ANSI

## Parties Développées Personnellement

### 🕒 **Système de Simulation Temporelle**
J'ai conçu et implémenté l'intégralité du moteur de simulation de temps :

- **Gestion du temps simulé** avec vitesse paramétrable
- **File d'événements prioritaire** avec traitement chronologique
- **Boucle principale de simulation** avec cycles contrôlés
- **Mécanisme d'avancement temporel** avec effets automatiques (fatigue progressive)

### ⚔️ **Système de Ressources du Héros**
J'ai développé la logique complète de gestion des stats et ressources :

#### **Attributs Dynamiques**
- **Santé** : Système de points de vie
- **Fatigue** : Accumulation progressive, récupération en zones sûres
- **Expérience/Niveau** : System XP → Level up automatique avec bonus
- **Force/Magie** : Stats offensives évolutives
- **Or** : Économie basique avec gains via combats/exploration

### 🎯 **Logiques de Jeu Avancées**

#### **Système d'Événements Contextuels**
- **Exploration dynamique** avec événements aléatoires selon le danger de zone
- **Gestion des rencontres** : Combat, Trésor, Piège, Récupération
- **Combat tour-par-tour** avec calcul de dégâts variable
- **Spawn automatique d'ennemis** adaptés au type de zone

### 📊 **Interface Administrateur**
J'ai créé un module admin complet pour le debugging et configuration :

- **Modification en temps réel** des stats du héros
- **Création dynamique de NPCs** avec paramètres personnalisés
- **Contrôle temporel** (vitesse, saut dans le temps)
- **Ajout d'événements manuels** pour tests
- **Visualisation de la file d'événements**

## Points Techniques Particuliers

### **Gestion Mémoire Propre**
- Aucune variable globale utilisée
- Structures passées par pointeur entre fonctions
- Allocation statique suffisante pour les limites du projet

### **Architecture Modulaire**
- Séparation claire : Simulation / Jeu / Admin / Affichage
- Code ANSI C strict sans dépendances externes

### **Robustesse**
- Vérifications de limites sur toutes les opérations
- Gestion d'erreurs sur fichiers et entrées utilisateur

## Défis Résolus

1. **Synchronisation événements** : Tri et traitement chronologique correct
2. **Équilibrage gameplay** : Progression satisfaisante sans être triviale
3. **Flexibilité admin** : Interface puissante sans casser la logique du jeu
4. **Performance** : Gestion efficace de nombreux événements simultanés

## Technologies Maîtrisées

- **C ANSI** : Respect strict de la norme, portabilité maximale
- **Structures complexes** : GameState centralisée, files d'événements
- **Algorithmes de tri** : Recherche d'événements prioritaires
- **I/O fichiers** : Sauvegarde/chargement binaire
- **Génération procédurale** : Ennemis et événements aléatoires
