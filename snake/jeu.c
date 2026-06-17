#include <MLV/MLV_all.h>
#include <stdio.h>
#include <stdlib.h>

#include "jeu.h"
#include "plateau.h"
#include "serpent.h"
#include "fruit.h"
#include "menu.h"
#include "sauvegarde.h"
#include "type.h"

extern int slot_actuel;

/*
   lancer_partie est la fonction principale du jeu
   Elle gère : déplacements, collisions, affichage, pause et sauvegarde.
   
 */
/*int : retourne le score final du joueur ou -1 si il quitte (menu de pause sans game over) */
int lancer_partie(MLV_Image* fond, MLV_Font* font, MLV_Font* font_titre, MLV_Image* image_boule, int charger) {

  /* initialisation de la partie */
  int score = 0;
  int jeu_en_cours = 1; /*devient 0 qd le serpent meurt*/

  Serpent serpent; /*struct definie dans type.H*/
  Fruit fruit;

  if (charger && charger_partie(&serpent, &fruit, &score, slot_actuel)) { /* charger : parametre de la fonction lancer partie (cf appel dans main))*/
    /* partie chargée */
  } else {
    initialiser_serpent(&serpent);
    initialiser_fruit(&fruit, &serpent);
    score = 0;
  }

    unsigned int largeur_fenetre, hauteur_fenetre;
    MLV_get_window_size(&largeur_fenetre, &hauteur_fenetre); /*recupere les dimensions de la fenetre et remplit les variables largeur_fenetre et hauteur_fenetre*/

    int largeur_grille = NB_COLONNES * TAILLE_CASE;
    int hauteur_grille = NB_LIGNES * TAILLE_CASE;

    /*decalage pour centrer la grille du jeu*/ 
    int dx = (largeur_fenetre - largeur_grille) / 2;
    int dy = (hauteur_fenetre - hauteur_grille) / 2;

    /* chargement des images du serpent */

    MLV_Image* tete_haut =
      MLV_load_image("ressources/shenron_tete_haut.png");
    MLV_Image* tete_bas  =
      MLV_load_image("ressources/shenron_tete_bas.png");
    MLV_Image* tete_gauche =
      MLV_load_image("ressources/shenron_tete_gauche.png");
    MLV_Image* tete_droite =
      MLV_load_image("ressources/shenron_tete_droite.png");
    MLV_Image* corps  =
      MLV_load_image("ressources/shenron_corps.png");

    if (!tete_haut || !tete_bas || !tete_gauche || !tete_droite || !corps) {
        printf("ERREUR : impossible de charger les images du serpent\n");
        return -1;
    }
/*redimensionnement*/
    MLV_resize_image(tete_haut,   TAILLE_CASE, TAILLE_CASE);
    MLV_resize_image(tete_bas,    TAILLE_CASE, TAILLE_CASE);
    MLV_resize_image(tete_gauche, TAILLE_CASE, TAILLE_CASE);
    MLV_resize_image(tete_droite, TAILLE_CASE, TAILLE_CASE);
    MLV_resize_image(corps,       TAILLE_CASE, TAILLE_CASE);

    while (jeu_en_cours) {
      
        MLV_Event ev;
        MLV_Keyboard_button touche;

        ev = MLV_get_event(&touche, NULL, NULL,
                           NULL, NULL, NULL,
                           NULL, NULL, NULL);

        if (ev == MLV_KEY) {
          
            if (touche == MLV_KEYBOARD_p) {
              /*affiche le menu de pause*/
                OptionMenuPause choix = afficher_menu_pause(fond, font,
                                                            font_titre);

                if (choix == SAUVEGARDER) {
                    slot_actuel = menu_choix_slot(fond, font, font_titre);
                    sauvegarder_partie(&serpent, &fruit, score, slot_actuel);
                }
                else if (choix == QUITTER_PAUSE) {
                    MLV_free_image(tete_haut);
                    MLV_free_image(tete_bas);
                    MLV_free_image(tete_gauche);
                    MLV_free_image(tete_droite);
                    MLV_free_image(corps);
                    return -1;
                }
            }
            /*changement de direction*/
            else if (touche == MLV_KEYBOARD_UP &&
                     serpent.direction != BAS)
                serpent.direction = HAUT;
            
            else if (touche == MLV_KEYBOARD_DOWN &&
                     serpent.direction != HAUT)
                serpent.direction = BAS;
            
            else if (touche == MLV_KEYBOARD_LEFT &&
                     serpent.direction != DROITE)
                serpent.direction = GAUCHE;
            
            else if (touche == MLV_KEYBOARD_RIGHT &&
                     serpent.direction != GAUCHE)
                serpent.direction = DROITE;
            
        } /* FIN if(ev == MLV_KEY) */

        avancer_serpent(&serpent); /*deplace le serpent*/

        if (collision_avec_soi_meme(&serpent)) /*verifie collision*/
            jeu_en_cours = 0; /*game over*/

        if (serpent_mange_fruit(&serpent, &fruit)) { /*verifie si la tete du serpent touche le fruit*/
            agrandir_serpent(&serpent); /*ajt un segment au serpent*/
            initialiser_fruit(&fruit, &serpent); /*place un nv fruit aleatoire*/
            score++; /*incremente le sport*/
        }

        MLV_clear_window(MLV_COLOR_BLACK);
        if (fond) MLV_draw_image(fond, 0, 0);

        dessiner_quadrillage(dx, dy);
        dessiner_serpent(&serpent, dx, dy,
                         tete_haut, tete_bas, tete_gauche,
                         tete_droite, corps);
        dessiner_fruit(&fruit, dx, dy, image_boule);

        /*affiche le score en haut a gauche*/
        char texte[40];
        sprintf(texte, "Score : %d", score);
        if (font) MLV_draw_text_with_font(20, 20, texte, font, MLV_COLOR_WHITE);

        MLV_actualise_window();
        MLV_wait_milliseconds(60);
    } /* FIN while(jeu_en_cours) */



    /*libere la memoire des images*/
    MLV_free_image(tete_haut);
    MLV_free_image(tete_bas);
    MLV_free_image(tete_gauche);
    MLV_free_image(tete_droite);
    MLV_free_image(corps);

    return score;
    
} /* FIN lancer_partie */
