#include <MLV/MLV_all.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "jeu.h"
#include "scores.h"
#include "menu.h"
#include "sauvegarde.h"
#include "type.h"

/* slot utilisé pour sauvegarder / charger une partie */
int slot_actuel = 1;

int main() {

    MLV_create_window("GALACTIC SERPENT", "snake", 1000, 800);
    srand(time(NULL));

    /*chargement des images*/
    
    MLV_Image* fond = MLV_load_image("ressources/fond.jpeg");
    MLV_Image* image_boule = MLV_load_image("ressources/image_boule.png");
    
    /*chargement des polices*/
    
    MLV_Font* font = MLV_load_font("ressources/game.TTF", 30);
    MLV_Font* font_titre = MLV_load_font("ressources/game.TTF", 60);
    
    /* Vérification du chargement des ressources */

    if (fond == NULL) printf("Attention : image de fond introuvable\n");
    if (font == NULL) printf("Attention : police introuvable\n");
    if (font_titre == NULL) {
        printf("Attention : police titre introuvable\n");
        font_titre = font;
    }
    
    /*ajustement de la taille de la fenetre à celle de l'image de fond*/

    int largeur_fond = 800, hauteur_fond = 600;
    if (fond != NULL)
      MLV_get_image_size(fond, &largeur_fond, &hauteur_fond);
    
    MLV_change_window_size(largeur_fond, hauteur_fond);

    /*redimension de l'image du fruit*/
    if (image_boule != NULL)
      MLV_resize_image(image_boule, TAILLE_CASE, TAILLE_CASE);

    /* chargement des scores */

    int scores[NB_MEILLEURS_SCORES]; /*defini dans type.h*/
    charger_scores(scores);

    

               /*    BOUCLE PRINCIPALE DU PROGRAMME    */


    
    int programme_actif = 1;

    while (programme_actif) {

        /* Affichage du menu principal et récupération du choix */
      
        OptionMenuPrincipal choix =
          afficher_menu_principal(fond, font, font_titre);


        /* gestion du menu */
        
        switch (choix) {

            /*nouvelle partie*/
        case NOUVELLE_PARTIE: {
            int rejouer = 1;

            /* boucle permettant de rejouer après un game over */
            
            while (rejouer) {
                int score =
                  lancer_partie(fond, font, font_titre, image_boule, 0);
                
                /* si la partie finit correctement */              
                if (score >= 0) { 
                  ajouter_score(scores, score);/*ajoute score au tab*/
                  sauvegarder_scores(scores);/*et l'écrit dans scores.txt*/
   
                  /* Ecran GAME OVER  */      
                    
                  int continuer_game_over = 1;
                  int choix_game_over = 0; /*1 = rejouer, 2 = retour menu*/
                  
                  while (continuer_game_over) {
                    
                    int souris_x, souris_y;
                    MLV_clear_window(MLV_COLOR_BLACK); /*efface fenetre*/
                    
                    if (fond)
                      MLV_draw_image(fond, 0, 0);/*redessine le fond*/

                    /*ecrit GAME OVER */
                    if (font_titre)
                      MLV_draw_text_with_font(520, 300, "GAME OVER",
                                              font_titre, MLV_COLOR_RED);
                    /*affiche le Score final*/
                    char texte_score[50];
                    sprintf(texte_score, "Score final : %d", score);
                    if (font)
                      MLV_draw_text_with_font(590, 150, texte_score,
                                              font, MLV_COLOR_WHITE);
                    
                    /* affiche les meilleurs scores*/
                    afficher_scores(scores, score, font);

                    
                    /* taille et position des boutons */
                    int largeur_bouton = 360, hauteur_bouton = 60;
                    int x_bouton = (largeur_fond - largeur_bouton) / 2;
                    int y_rejouer = 400, y_menu = 500;

                    
                    /*recupere la position actuelle de la souris*/
                    MLV_get_mouse_position(&souris_x, &souris_y);

                    /*detecte si la souris est sur le bouton*/
                    int survole_rejouer = /*bouton Rejouer*/
                      souris_x >= x_bouton &&
                      souris_x <= x_bouton + largeur_bouton && 
                      souris_y >= y_rejouer &&
                      souris_y <= y_rejouer + hauteur_bouton;
                    
                    int survole_menu = /*bouton Retour menu*/
                      souris_x >= x_bouton &&
                      souris_x <= x_bouton + largeur_bouton && 
                      souris_y >= y_menu &&
                      souris_y <= y_menu + hauteur_bouton;

                    /*les boutons detectent la souris*/
                    dessiner_bouton(x_bouton, y_rejouer,
                                    largeur_bouton, hauteur_bouton,
                                    "REJOUER", survole_rejouer, font);
                    
                    dessiner_bouton(x_bouton, y_menu,
                                    largeur_bouton, hauteur_bouton,
                                    "RETOUR MENU", survole_menu, font);

                    MLV_actualise_window(); /*affiche tout ce qui
                                              a été dessiné*/

                    /*attend un clic souris*/
                    MLV_Event ev = MLV_get_event(NULL, NULL, NULL,
                                                 NULL, NULL,
                                                 &souris_x, &souris_y,
                                                 NULL, NULL);
                    /*si un clic est détecté*/
                    if (ev == MLV_MOUSE_BUTTON) {
                      if (survole_rejouer) { /*Rejouer*/
                        continuer_game_over = 0;
                        choix_game_over = 1;
                      }
                      else if (survole_menu) {
                        continuer_game_over = 0;/*Retour menu*/
                        choix_game_over = 2;
                      }/*dans les 2 cas on sort de la boucle Game over*/
                      
                    }
                    
                    MLV_wait_milliseconds(10);/*evite de surcharger
                                                le CPU*/

                    
                  }  /*  FIN while(continuer_game_over) */

                  
                  /* rejouer ou retour menu après le GAME OVER*/
                  if (choix_game_over == 1){
                    rejouer = 1;
                  }
                  
                } /* FIN if(score >= 0) */
                
                else {
                  /*sortie depuis la pause*/
                    rejouer = 0;
                }
                
          } /*  FIN while(rejouer) */
                
          break;
            
        } /* FIN case NOUVELLE_PARTIE */

            
        /* CHARGER PARTIE */
            
        case CHARGER_PARTIE: {

          /* affiche un menu avec les 4 slots de sauvegarde*/
          slot_actuel = menu_choix_slot(fond, font, font_titre);

          /*verifie si une sauvegarde existe pour ce slot*/
          if (sauvegarde_existe(slot_actuel)) {


            /*lance une partie en mode chargement: 1 = charger*/
            int score =
              lancer_partie(fond, font, font_titre, image_boule, 1);
            
            if (score >= 0) {
              ajouter_score(scores, score);
              sauvegarder_scores(scores);
            }
          } 

          else {
            MLV_clear_window(MLV_COLOR_BLACK); /*nettoie la fenetre*/
            if (fond)
              MLV_draw_image(fond, 0, 0);
            if (font)
              MLV_draw_text_with_font(280, 400,
                                      "Aucune sauvegarde dans ce slot",
                                      font, MLV_COLOR_RED);
            
            MLV_actualise_window();
            MLV_wait_milliseconds(1500);
          }
          
          break;
        }


        /* MEILLEURS_SCORES */
        case MEILLEURS_SCORES:
            afficher_scores_menu(scores, fond, font, font_titre);
            break;
            
        /* QUITTER */
        case QUITTER:
            programme_actif = 0;
            break;

        default:
          break;
          
        } /* FIN swhitch */
          
    } /* FIN while(programme_actif) */


        
        /*  liberation des ressources  */

    if (font && font != font_titre) MLV_free_font(font);
    if (font_titre) MLV_free_font(font_titre);
    if (fond) MLV_free_image(fond);
    if (image_boule) MLV_free_image(image_boule);
    
    MLV_free_window();

    return 0;
    
} /* FIN main */
