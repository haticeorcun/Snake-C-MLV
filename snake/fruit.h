#ifndef FRUIT_H
#define FRUIT_H

#include "type.h"

void initialiser_fruit(Fruit* fruit, const Serpent* serpent);

void dessiner_fruit(const Fruit* f,
                    int dx, int dy,
                    MLV_Image* img);

int serpent_mange_fruit(const Serpent* s,
                        const Fruit* f);


#endif
