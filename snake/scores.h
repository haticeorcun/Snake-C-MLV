#ifndef SCORES_H
#define SCORES_H

#include <MLV/MLV_all.h>

/* Charger les scores */
void charger_scores(int scores[]);

/* Ajouter un score */
void ajouter_score(int scores[], int nouveau_score);

/* Sauvegarder les scores */
void sauvegarder_scores(int scores[]);

void afficher_scores(int scores[], int nouveau_score, MLV_Font* font);

/* Afficher les scores */
void afficher_scores_menu(int scores[],
                          MLV_Image* fond,
                          MLV_Font* font,
                          MLV_Font* font_titre);


#endif
