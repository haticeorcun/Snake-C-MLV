#ifndef MENU_H
#define MENU_H

#include <MLV/MLV_all.h>

/* MENU PRINCIPAL */
typedef enum {
    NOUVELLE_PARTIE,
    CHARGER_PARTIE,
    MEILLEURS_SCORES,
    QUITTER,
    NB_OPTIONS_MENU
} OptionMenuPrincipal;

/* MENU PAUSE  */
typedef enum {
    REPRENDRE,
    SAUVEGARDER,
    QUITTER_PAUSE,
    NB_OPTIONS_PAUSE
} OptionMenuPause;

/* AFFICHAGE MENUS */
OptionMenuPrincipal afficher_menu_principal(MLV_Image* fond,
                                            MLV_Font* font,
                                            MLV_Font* font_titre);

OptionMenuPause afficher_menu_pause(MLV_Image* fond,
                                    MLV_Font* font,
                                    MLV_Font* font_titre);


/* menu choix slot */
int menu_choix_slot(
                    MLV_Image* fond,
                    MLV_Font* font,
                    MLV_Font* font_titre
                    );


/* BOUTONS */
void dessiner_bouton(int x, int y,
                     int largeur, int hauteur,
                     const char* texte,
                     int survole,
                     MLV_Font* font);

int souris_sur_bouton(int souris_x, int souris_y,
                      int x, int y,
                      int largeur, int hauteur);

#endif
