#include <stdio.h>
#include <MLV/MLV_all.h>

#include "scores.h"
#include "type.h"   /* POUR NB_MEILLEURS_SCORES */


/* Charge les meilleurs scores depuis le fichier "scores.txt",
   si le fichier n'existe pas ou est invalide, les scores sont initialisés à 0 */

void charger_scores(int scores[]) {

    /* Ouverture du fichier en lecture */
    FILE* f = fopen("scores.txt", "r");
    int i;
    /* Si le fichier n'existe pas */
    if (f == NULL) {
        for (i = 0; i < NB_MEILLEURS_SCORES; i++)
            scores[i] = 0;      /* Initialisation des scores à 0 */
        return; /* Fin de la fonction */
    }

     /* Lecture des scores depuis le fichier */
    for (i = 0; i < NB_MEILLEURS_SCORES; i++) {
        /* Sécurité : si lecture invalide ou score négatif */
        if (fscanf(f, "%d", &scores[i]) != 1 || scores[i] < 0)
            scores[i] = 0;
    }
    /* Fermeture du fichier */
    fclose(f);
}


/* Sauvegarde le tableau des scores dans le fichier "scores.txt",
   chaque score est écrit sur une ligne.  */

void sauvegarder_scores(int scores[]) {
  
    /* Ouverture du fichier en écriture (écrase l'ancien contenu) */
    FILE* f = fopen("scores.txt", "w");
    int i;
    
    /* Si l'ouverture échoue, on quitte la fonction */
    if (f == NULL)
        return;
    
    /* Écriture de chaque score dans le fichier */
    for (i = 0; i < NB_MEILLEURS_SCORES; i++) {
        fprintf(f, "%d\n", scores[i]);
    }
    
    /* Fermeture du fichier */
    fclose(f);
}

/* Insère un nouveau score dans le tableau des meilleurs scores,
   le tableau reste trié par ordre décroissant. */

void ajouter_score(int scores[], int nouveau_score) {

    int i, j;
    
    /* on ignore les scores invalides */
    if (nouveau_score < 0)
        return;

    /* recherche de la position d'insertion */    
    for (i = 0; i < NB_MEILLEURS_SCORES; i++) {
      
        /* si le nouveau score est meilleur */
        if (nouveau_score > scores[i]) {

          /* décalage des scores vers la droite */
          for (j = NB_MEILLEURS_SCORES - 1; j > i; j--) {
                scores[j] = scores[j - 1];
            }
            
            /* insertion du nouveau score */
            scores[i] = nouveau_score;
            return;
        }
    }
}



/* affiche le classement des meilleurs scores,
   le nouveau score est en couleur */


void afficher_scores(int scores[], int nouveau_score, MLV_Font* font) {

    int y = 300;  /* Position verticale de départ */
    int deja_colore = 0;  /* Pour ne surligner qu'un seul score */

    /* affichage titre */
    if (font != NULL)
        MLV_draw_text_with_font(
            450, 230,
            "Top 10 des meilleurs scores",
            font,
            MLV_COLOR_YELLOW
        );
    else
        MLV_draw_text(
            450, 230,
            "Top 10 des meilleurs scores",
            MLV_COLOR_YELLOW
        );

    /* liste des scores */
    for (int i = 0; i < NB_MEILLEURS_SCORES; i++) {

        char texte[50];
        sprintf(texte, "%d. %d", i + 1, scores[i]);

        MLV_Color couleur = MLV_COLOR_WHITE;

        /* Couleur du nouveau score */
        if (!deja_colore &&
            nouveau_score >= 0 &&
            scores[i] == nouveau_score) {

            couleur = MLV_COLOR_GOLD;
            deja_colore = 1;
        }

        /*affichage du score*/
        if (font != NULL)
            MLV_draw_text_with_font(
                300, y,
                texte,
                font,
                couleur
            );
        else
            MLV_draw_text(
                300, y,
                texte,
                couleur
            );

        y += 45; /*espace entre les scores*/
    }
}


void afficher_scores_menu(int scores[],
                          MLV_Image* fond,
                          MLV_Font* font,
                          MLV_Font* font_titre) {

    /* scores à jour */
    charger_scores(scores);

    /* Nettoyage pour eviter la superposition des dessins*/
    MLV_clear_window(MLV_COLOR_BLACK);

    /* affichage du fond */
    if (fond != NULL)
        MLV_draw_image(fond, 0, 0);

    /* Titre principal */
    if (font_titre != NULL)
        MLV_draw_text_with_font(
            360, 150,
            "MEILLEURS SCORES",
            font_titre,
            MLV_COLOR_YELLOW
        );
    else
        MLV_draw_text(
            360, 150,
            "MEILLEURS SCORES",
            MLV_COLOR_YELLOW
        );

    /* affiichage des meilleurs scores
       -1 car aucun score à surligner */
    afficher_scores(scores, -1, font);

    /* Message revenir au menu */
    if (font != NULL)
        MLV_draw_text_with_font(
            300, 800,
            "Appuyez sur une touche pour revenir au menu",
            font,
            MLV_COLOR_GRAY
        );
    else
        MLV_draw_text(
            300, 800,
            "Appuyez sur une touche pour revenir au menu",
            MLV_COLOR_GRAY
        );
    /* mise à jour et attente que l'utilisateur tape une touche*/
    MLV_actualise_window();
    MLV_wait_keyboard(NULL, NULL, NULL);
}
