#ifndef TYPE_H
#define TYPE_H

#define TAILLE_CASE  50
#define NB_COLONNES  22
#define NB_LIGNES    15

#define TAILLE_MAX_SERPENT 100
#define NB_MEILLEURS_SCORES 10


/* Une case de la grille */
typedef struct {
    int x;   /* colonne */
    int y;   /* ligne   */
} Case;

/* Directions possibles du serpent */
typedef enum {
    HAUT,
    BAS,
    GAUCHE,
    DROITE
} Direction;

/* Structure du serpent */
typedef struct {
    Case corps[TAILLE_MAX_SERPENT];  /* positions successives du corps du serpent */
    int longueur;             /* nombre de segments du serpent */
    Direction direction;      /* direction actuelle du serpent */
} Serpent;


typedef struct {
  int x;
  int y;
} Fruit;


#endif
