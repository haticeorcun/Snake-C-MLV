#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H

#include "type.h"

/* Sauvegarder une partie dans un slot */
int sauvegarder_partie(const Serpent* serpent,
                       const Fruit* fruit,
                       int score,
                       int slot);

/* Charger une partie depuis un slot */
int charger_partie(Serpent* serpent,
                   Fruit* fruit,
                   int* score,
                   int slot);

/* Vérifier si une sauvegarde existe pour un slot */
int sauvegarde_existe(int slot);

#endif
