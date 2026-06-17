#include <MLV/MLV_all.h>
#include "serpent.h"
#include "type.h"





/* Initialise le serpent au début de la partie, le serpent commence
   avec une longueur de 3 cases orienté vers la droite. */

void initialiser_serpent(Serpent* s) {

    s->longueur = 3;
    s->direction = DROITE;

    /* Position initiale du serpent */

    s->corps[0].x = 5; s->corps[0].y = 5; /* tête */
    s->corps[1].x = 4; s->corps[1].y = 5; /* corps */
    s->corps[2].x = 3; s->corps[2].y = 5; /* queue */
}




/* Fais avancer le serpent d'une case dans la direction actuelle
 Le corps suit la tête : chaque segment prend la position du précédent*/

void avancer_serpent(Serpent* s) {

    int i;
    
    /* Déplacement du corps : de la queue vers la tête */
    for (i = s->longueur - 1; i > 0; i--)
        s->corps[i] = s->corps[i - 1];

    /* Déplacement de la tête selon la direction */
    if (s->direction == HAUT)    s->corps[0].y--;
    if (s->direction == BAS)     s->corps[0].y++;
    if (s->direction == GAUCHE)  s->corps[0].x--;
    if (s->direction == DROITE)  s->corps[0].x++;

    /* Gestion du passage par les bords de la grille */    
    if (s->corps[0].x < 0) s->corps[0].x = NB_COLONNES - 1;
    if (s->corps[0].x >= NB_COLONNES) s->corps[0].x = 0;
    if (s->corps[0].y < 0) s->corps[0].y = NB_LIGNES - 1;
    if (s->corps[0].y >= NB_LIGNES) s->corps[0].y = 0;
}




/*  Détermine la direction entre deux cases adjacentes pour orienter
 correctement la tête du serpent. */

Direction direction_entre(Case position_tete, Case position_corps) {

    /* Si le corps est juste AU-DESSUS de la tête */
    if (position_corps.x == position_tete.x &&
        position_corps.y == position_tete.y - 1)
        return HAUT;

    /* Si le corps est juste EN DESSOUS de la tête */
    if (position_corps.x == position_tete.x &&
        position_corps.y == position_tete.y + 1)
        return BAS;

    /* Si le corps est juste À GAUCHE de la tête */
    if (position_corps.x == position_tete.x - 1 &&
        position_corps.y == position_tete.y)
        return GAUCHE;

    /* Si le corps est juste À DROITE de la tête */
    if (position_corps.x == position_tete.x + 1 &&
        position_corps.y == position_tete.y)
        return DROITE;

    /* Cas de sécurité (ne devrait pas arriver) */
    return DROITE;
}





/* Affichage du serpent à l'écran.
  La tête est orientée  selon la direction du mouvement, le reste
  du serpent est dessiné avec l'image du corps. */

void dessiner_serpent(const Serpent* serpent,
                      int decalage_x,
                      int decalage_y,
                      MLV_Image* tete_haut,
                      MLV_Image* tete_bas,
                      MLV_Image* tete_gauche,
                      MLV_Image* tete_droite,
                      MLV_Image* corps) {

    /* Parcours de tous les segments du serpent */  
    for (int i = 0; i < serpent->longueur; i++) {
      
        /* Conversion des coordonnées grille → pixels */
        int px = decalage_x + serpent->corps[i].x * TAILLE_CASE;
        int py = decalage_y + serpent->corps[i].y * TAILLE_CASE;

        /* TÊTE  */
        if (i == 0) {
            /* Détermination de la direction de la tête */
            Direction d = direction_entre(serpent->corps[0],
                                          serpent->corps[1]);

            /* Dessin de la tête selon sa direction */            
            if (d == HAUT)    MLV_draw_image(tete_haut, px, py);
            if (d == BAS)     MLV_draw_image(tete_bas, px, py);
            if (d == GAUCHE)  MLV_draw_image(tete_gauche, px, py);
            if (d == DROITE)  MLV_draw_image(tete_droite, px, py);
        }

        /* CORPS  */
        else {
            MLV_draw_image(corps, px, py);
        }
    }
}





/* Augmente la longueur du serpent après avoir mangé un fruit,
   la limite est imposée pour éviter le dépassement de TAILLE_MAX_SERPENT  */

void agrandir_serpent(Serpent* s) {
    if (s->longueur < 100)
        s->longueur++;
}





/*  Vérifie si la tête du serpent entre en collision avec son corps,
    retourne 1 si collision, 0 sinon.  */

int collision_avec_soi_meme(const Serpent* s) {

    int i;
    /* On compare la tête avec chaque segment du corps */
    for (i = 1; i < s->longueur; i++) {
        if (s->corps[0].x == s->corps[i].x &&
            s->corps[0].y == s->corps[i].y)
            return 1;
    }
    return 0;
}

