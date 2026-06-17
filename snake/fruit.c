#include <MLV/MLV_all.h>
#include <stdlib.h>
#include "fruit.h"
#include "type.h"


/*placer un fruit a une position aleatoire sur la grille (sans qu'il apparaisse sur le corps du serpent)  */
void initialiser_fruit(Fruit* fruit, const Serpent* serpent) {

    int position_valide = 0;

    while (!position_valide) {

        /* Génération aléatoire */
        fruit->x = rand() % NB_COLONNES;
        fruit->y = rand() % NB_LIGNES;

        position_valide = 1;  /* on suppose que c'est bon */

        /* Vérification : le fruit ne doit pas être sur le serpent */
        for (int i = 0; i < serpent->longueur; i++) {

            if (fruit->x == serpent->corps[i].x &&
                fruit->y == serpent->corps[i].y) {

                position_valide = 0; /* si le fruit tombe sur le corps mauvaise position */
                break;
            }
        }
    }
}

/*afficher le fruit a l'ecran*/
void dessiner_fruit(const Fruit* f,
                    int dx, int dy,
                    MLV_Image* img) {

    if (img != NULL)
        MLV_draw_image(
            img,
            dx + f->x * TAILLE_CASE,
            dy + f->y * TAILLE_CASE
        );
}

int serpent_mange_fruit(const Serpent* s,
                        const Fruit* f) {

    return (s->corps[0].x == f->x &&
            s->corps[0].y == f->y);
}
/*s->corps[0] : la tête du serpent (premier élément du tableau)
Compare les coordonnées de la tête avec celles du fruit
Retourne 1 (vrai) si collision, 0 (faux) sinon*/
