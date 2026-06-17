#include <MLV/MLV_all.h>
#include "plateau.h"
#include "type.h"


/*DESSINER LE PLATEAU */

void dessiner_quadrillage(int dx, int dy) {

    int l, c;
    
    /* Parcours des lignes du plateau */
    for (l = 0; l < NB_LIGNES; l++) {

        /* Parcours des colonnes du plateau */      
        for (c = 0; c < NB_COLONNES; c++) {
          
            /* Conversion des coordonnées grille → pixels */
            int x = dx + c * TAILLE_CASE;
            int y = dy + l * TAILLE_CASE;
            
            /* Couleur des cases en damier) */
            if ((l + c) % 2 == 0)
                MLV_draw_filled_rectangle(
                    x, y,
                    TAILLE_CASE, TAILLE_CASE,
                    MLV_rgba(190, 80, 232, 100)
                );
            else
                MLV_draw_filled_rectangle(
                    x, y,
                    TAILLE_CASE, TAILLE_CASE,
                    MLV_rgba(180, 80, 232, 50)
                );
        }
    }

    /*contour de la grille*/
    MLV_draw_rectangle(
        dx, dy,
        NB_COLONNES * TAILLE_CASE,
        NB_LIGNES * TAILLE_CASE,
        MLV_rgba(191, 85, 236, 200)
    );
}
