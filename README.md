# 🐍 Galactic Serpent

Un Snake graphique en C ANSI (C89) avec la bibliothèque MLV.  
Thème Dragon Ball : le serpent est Shenron, le fruit est une boule de cristal.

---

## Fonctionnalités

- Déplacement fluide avec les touches directionnelles
- Grille 22×15 centrée dans la fenêtre
- Fruit positionné aléatoirement (jamais sur le corps du serpent)
- Menu pause (touche `P`) avec sauvegarde de partie
- 4 slots de sauvegarde indépendants
- Top 10 des meilleurs scores (persistant entre les sessions)
- Écran Game Over avec boutons Rejouer / Retour menu
- Images custom : tête orientée selon la direction, corps uniforme

---

## Prérequis

- GCC
- [MLV](https://www-igm.univ-mlv.fr/~boussica/mlv/api/French/html/index.html) (bibliothèque graphique)

Sur Debian/Ubuntu :
```bash
sudo apt install libmlv3-dev
```

---

## Compilation

```bash
make
```

Cible par défaut : `snake` (binaire dans le dossier courant).

```bash
make clean   # supprime les .o et le binaire
```

Le code est conforme **C89/ANSI** (`-ansi -pedantic`).

---

## Lancement

```bash
./snake
```

Le jeu doit être lancé depuis la racine du projet (là où se trouve le dossier `ressources/`).

---

## Commandes

| Touche | Action |
|---|---|
| ← ↑ → ↓ | Déplacer le serpent |
| `P` | Pause |
| Clic souris | Naviguer dans les menus |

---

## Structure du projet

```
snake/
├── main.c            # point d'entrée, boucle principale
├── jeu.c / jeu.h     # boucle de jeu, gestion des événements
├── serpent.c / .h    # initialisation, déplacement, affichage, collisions
├── fruit.c / .h      # placement et détection du fruit
├── plateau.c / .h    # dessin de la grille
├── menu.c / .h       # menus (principal, pause, slots, game over)
├── scores.c / .h     # chargement, sauvegarde, affichage du top 10
├── sauvegarde.c / .h # sérialisation / désérialisation des parties
├── type.h            # types partagés (Case, Serpent, Fruit, Direction)
├── makefile
└── ressources/
    ├── fond.jpeg
    ├── image_boule.png
    ├── shenron_tete_haut.png
    ├── shenron_tete_bas.png
    ├── shenron_tete_gauche.png
    ├── shenron_tete_droite.png
    ├── shenron_corps.png
    └── game.TTF
```

---

## Auteurs

Avan Yelda · Orcun Hatice — Licence Informatique L2, Université Jean Monnet
