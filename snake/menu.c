#include <MLV/MLV_all.h>
#include "menu.h"


/*verifie si la souris est a l'interieur d'un rectangle*/
int souris_sur_bouton(int souris_x, int souris_y,
                      int x, int y, int largeur, int hauteur) {
    return (souris_x >= x && souris_x <= x + largeur &&
            souris_y >= y && souris_y <= y + hauteur);
}
/*fonction qui dessine un bouton : rectangle, bordure, texte centre*/
void dessiner_bouton(int x, int y, int largeur, int hauteur,
                     const char* texte, int survole, MLV_Font* font) {
/*couleur du bouton*/
    MLV_Color couleur_fond;
    MLV_Color couleur_texte;
    MLV_Color couleur_bordure;

    if (survole) { /*si la souris est sur le bouton : couleurs clairs, sinon couleurs fonces*/
        couleur_fond = MLV_rgba(191, 85, 236, 200);
        couleur_texte = MLV_COLOR_WHITE;
        couleur_bordure = MLV_rgba(220, 120, 255, 255);
    } else {
        couleur_fond = MLV_rgba(100, 50, 150, 150);
        couleur_texte = MLV_rgba(200, 200, 200, 255);
        couleur_bordure = MLV_rgba(150, 80, 200, 200);
    }

    MLV_draw_filled_rectangle(x, y, largeur, hauteur, couleur_fond); /*dessin du rectangle plein*/
    MLV_draw_rectangle(x, y, largeur, hauteur, couleur_bordure); /*bordure*/

    int texte_largeur, texte_hauteur; /*combien de pixels le texte prend en largeur et hauteur (pour pouvoir centrer le texte apres)*/

    if (font != NULL) { /*si on a une police personnalisée*/
        MLV_get_size_of_text_with_font(
            texte, &texte_largeur, &texte_hauteur, font);
        MLV_draw_text_with_font( /* centre le texte (sinon coller a gauche)*/
            x + (largeur - texte_largeur) / 2,
            y + (hauteur - texte_hauteur) / 2,
            texte, font, couleur_texte);
    } else {
        MLV_get_size_of_text(texte, &texte_largeur, &texte_hauteur);
        MLV_draw_text(
            x + (largeur - texte_largeur) / 2,
            y + (hauteur - texte_hauteur) / 2,
            texte, couleur_texte);
    }
}

OptionMenuPrincipal afficher_menu_principal(MLV_Image* fond, /*image de fond*/
                                           MLV_Font* font, /*police pour le texte du bouton*/
                                           MLV_Font* font_titre/*police pour le titre du bouton*/) {

    unsigned int largeur_fenetre, hauteur_fenetre;
    MLV_get_window_size(&largeur_fenetre, &hauteur_fenetre); /*on recup taille de la fenetre*/

    
    /*on definit la taille des boutons et de l'espacement*/
    int largeur_bouton = 470;
    int hauteur_bouton = 70;
    int espacement = 20;

    int x_bouton = (largeur_fenetre - largeur_bouton) / 2;
    int y_debut = 280;

    int positions_y[NB_OPTIONS_MENU]; 
    int i;
    for (i = 0; i < NB_OPTIONS_MENU; i++) { /*savoir ou dessiner chaque bouton verticalement*/
        positions_y[i] = y_debut + i * (hauteur_bouton + espacement);
    }
/*const pour ne pas modifier la variable*/
    const char* textes_boutons[NB_OPTIONS_MENU] = {
        "NOUVELLE PARTIE",
        "CHARGER PARTIE",
        "MEILLEURS SCORES",
        "QUITTER"
    };

    while (1) {

        MLV_clear_window(MLV_COLOR_BLACK);

        if (fond != NULL) /* si on a une image de fond on l'affiche*/
            MLV_draw_image(fond, 0, 0);

        if (font_titre != NULL) {
            int titre_largeur, titre_hauteur;
            MLV_get_size_of_text_with_font( /*mesurer le texte*/
                "GALACTIC SERPENT",
                &titre_largeur, &titre_hauteur, font_titre);  /*mesure combien de pixels prend le texte quand on l'affiche avec la police font titre ( on a besoin de ces valeurs pour centrer le texte) */
            MLV_draw_text_with_font( /*dessine galactic serpent (avec police)*/
                (largeur_fenetre - titre_largeur) / 2, /*calcul centrage*/
                100,
                "GALACTIC SERPENT",
                font_titre,
                MLV_rgba(191, 85, 236, 255));
        } else { /*cas sans police*/
            MLV_draw_text(
                largeur_fenetre / 2 - 150,
                100,
                "GALACTIC SERPENT",
                MLV_rgba(191, 85, 236, 255));
        }

        /*MLV lit ou se trouve la souris en ce moment** et stocke les coordonnees dans souris_x et souris_y*/
        int souris_x, souris_y;
        MLV_get_mouse_position(&souris_x, &souris_y);

        for (i = 0; i < NB_OPTIONS_MENU; i++) { /*dessine les 4 boutons un par un*/
            int survole =
                souris_sur_bouton( /*si la fonction est sur le bouton ou pass*/
                    souris_x, souris_y, /*position souris*/
                    x_bouton, positions_y[i], /*position bouton*/
                    largeur_bouton, hauteur_bouton); /*taille du bouton*/

            dessiner_bouton(
                x_bouton, positions_y[i],
                largeur_bouton, hauteur_bouton,
                textes_boutons[i], survole, font);
        }
        /*dans dessiner bouton on a survoke qui fait, si survole == 1 couleur_fond = VIOLET_CLAIR;  // Couleurs vives
sinon couleur_fond = VIOLET_FONCE; */

        MLV_actualise_window();
/*detecter un clic de souris*/
        MLV_Event evenement = MLV_get_event(
            NULL, NULL, NULL, /*touche du clavier (pas besoin ici)*/
            NULL, NULL,
            &souris_x, &souris_y, /*position de la souris*/
            NULL, NULL);

        if (evenement == MLV_MOUSE_BUTTON) { /*si l'utilisateur a clique...*/
            for (i = 0; i < NB_OPTIONS_MENU; i++) { /*on verifie sur ql bouton l'utilisateur a cliqué*/
                if (souris_sur_bouton(
                        souris_x, souris_y,
                        x_bouton, positions_y[i],
                        largeur_bouton, hauteur_bouton)) {
                    return (OptionMenuPrincipal)i;
                }
            }
        }

        MLV_wait_milliseconds(10);
    }/* exemple :
L'utilisateur clique sur QUITTER :
La boucle dessine le menu
MLV_get_event detecte un clic a (400,560)
La boucle verifie chaque bouton :

Bouton 0 () : Non
Bouton 1 () : Non
Bouton 2 () : Non
Bouton 3 (550) : OUI ! ✅
return 3
La fonction se termine
Le main.c recoit QUITTER et ferme le jeu: */
}

/*Cette fonction affiche le menu pause quand le joueur appuie sur "P" pendant le jeu.*/
OptionMenuPause afficher_menu_pause(MLV_Image* fond,
                                    MLV_Font* font,
                                    MLV_Font* font_titre) {

    unsigned int largeur_fenetre, hauteur_fenetre;
    MLV_get_window_size(&largeur_fenetre, &hauteur_fenetre);

    int largeur_bouton = 590;
    int hauteur_bouton = 80;
    int espacement = 30;

    int x_bouton = (largeur_fenetre - largeur_bouton) / 2;
    int y_debut = 280;

    int positions_y[NB_OPTIONS_PAUSE];
    int i;
    for (i = 0; i < NB_OPTIONS_PAUSE; i++) {
        positions_y[i] = y_debut + i * (hauteur_bouton + espacement);
    }

    const char* textes_boutons[NB_OPTIONS_PAUSE] = {
        "REPRENDRE",
        "SAUVEGARDER LA PARTIE",
        "MENU"
    };

    while (1) {

        MLV_clear_window(MLV_COLOR_BLACK);

        if (fond != NULL)
            MLV_draw_image(fond, 0, 0);

        if (font_titre != NULL) {
            int titre_largeur, titre_hauteur;
            MLV_get_size_of_text_with_font(
                "PAUSE",
                &titre_largeur, &titre_hauteur, font_titre);
            MLV_draw_text_with_font(
                (largeur_fenetre - titre_largeur) / 2,
                100,
                "PAUSE",
                font_titre,
                MLV_rgba(191, 85, 236, 255));
        } else {
            MLV_draw_text(
                largeur_fenetre / 2 - 50,
                100,
                "PAUSE",
                MLV_rgba(191, 85, 236, 255));
        }

        int souris_x, souris_y;
        MLV_get_mouse_position(&souris_x, &souris_y);

        for (i = 0; i < NB_OPTIONS_PAUSE; i++) {
            int survole =
                souris_sur_bouton(
                    souris_x, souris_y,
                    x_bouton, positions_y[i],
                    largeur_bouton, hauteur_bouton);

            dessiner_bouton(
                x_bouton, positions_y[i],
                largeur_bouton, hauteur_bouton,
                textes_boutons[i], survole, font);
        }

        MLV_actualise_window();

        MLV_Event evenement = MLV_get_event(
            NULL, NULL, NULL,
            NULL, NULL,
            &souris_x, &souris_y,
            NULL, NULL);

        if (evenement == MLV_MOUSE_BUTTON) {
            for (i = 0; i < NB_OPTIONS_PAUSE; i++) {
                if (souris_sur_bouton(
                        souris_x, souris_y,
                        x_bouton, positions_y[i],
                        largeur_bouton, hauteur_bouton)) {
                    return (OptionMenuPause)i;
                }
            }
        }

        MLV_Keyboard_button touche; /*creer une variable pour la touche*/
        evenement = MLV_get_event(
            &touche, NULL, NULL, /*on recupere la touche appuyer*/
            NULL, NULL,
            NULL, NULL,
            NULL, NULL);

        if (evenement == MLV_KEY) { /*si l'utilisateur a tape sur une touche du clavier*/
            if (touche == MLV_KEYBOARD_p || /*on verifie si la touche appuyee est p ou echap*/
                touche == MLV_KEYBOARD_ESCAPE) {
                return REPRENDRE;
            }
        }

        MLV_wait_milliseconds(10);
    }
}



/*menu avec 4 slots de sauvegarded*/
int menu_choix_slot(MLV_Image* fond,
                    MLV_Font* font,
                    MLV_Font* font_titre) {

 /*sans vider les evenements :le menu choisirait un slot automatiquement, on aura pas le temps de voir le menu
ca choisirait un slot au hasard selon où était le clic précédent*/                       
    while (MLV_get_event(NULL,NULL,NULL,
                         NULL,NULL,
                         NULL,NULL,
                         NULL,NULL) != MLV_NONE);

    unsigned int largeur_fenetre, hauteur_fenetre;
    MLV_get_window_size(&largeur_fenetre, &hauteur_fenetre);

    int largeur_bouton = 300;
    int hauteur_bouton = 70;
    int espacement = 20;

    int x_bouton = (largeur_fenetre - largeur_bouton) / 2;
    int y_depart = 280;

    const char* textes_boutons[4] = {
        "SLOT 1",
        "SLOT 2",
        "SLOT 3",
        "SLOT 4"
    };

    while (1) {

        MLV_clear_window(MLV_COLOR_BLACK);
        if (fond)
            MLV_draw_image(fond, 0, 0);

        if (font_titre) {
            int largeur_titre, hauteur_titre;
            MLV_get_size_of_text_with_font(
                "CHOISIR UN SLOT",
                &largeur_titre,
                &hauteur_titre,
                font_titre
            );
            MLV_draw_text_with_font(
                (largeur_fenetre - largeur_titre) / 2,
                120,
                "CHOISIR UN SLOT",
                font_titre,
                MLV_rgba(191, 85, 236, 255)
            );
        }

        int souris_x, souris_y;
        MLV_get_mouse_position(&souris_x, &souris_y);

        int i;
        for (i = 0; i < 4; i++) {
            int y = y_depart + i * (hauteur_bouton + espacement);
            dessiner_bouton(
                x_bouton, y,
                largeur_bouton, hauteur_bouton,
                textes_boutons[i],
                souris_sur_bouton(
                    souris_x, souris_y,
                    x_bouton, y,
                    largeur_bouton, hauteur_bouton
                ),
                font
            );
        }

        MLV_actualise_window();

        MLV_Event evenement = MLV_get_event(
            NULL, NULL, NULL,
            NULL, NULL,
            &souris_x, &souris_y,
            NULL, NULL
        );

        if (evenement == MLV_MOUSE_BUTTON) {
            for (i = 0; i < 4; i++) {
                int y = y_depart + i * (hauteur_bouton + espacement);
                if (souris_sur_bouton(
                        souris_x, souris_y,
                        x_bouton, y,
                        largeur_bouton, hauteur_bouton)) {
                    return i + 1;
                }
            }
        }

        MLV_wait_milliseconds(10);
    }
}
