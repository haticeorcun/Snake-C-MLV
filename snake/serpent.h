#ifndef SERPENT_H
#define SERPENT_H

#include <MLV/MLV_all.h>
#include "type.h"

/* Initialisation */
void initialiser_serpent(Serpent* s);

/* Déplacement */
void avancer_serpent(Serpent* s);

Direction direction_entre(Case position_tete, Case position_corps);

/* Affichage */
void dessiner_serpent(const Serpent* serpent,
                      int decalage_x,
                      int decalage_y,
                      MLV_Image* tete_haut,
                      MLV_Image* tete_bas,
                      MLV_Image* tete_gauche,
                      MLV_Image* tete_droite,
                      MLV_Image* corps) ;

/* Croissance  */
void agrandir_serpent(Serpent* s);

/* Collisions */
int collision_avec_soi_meme(const Serpent* s);
#endif
