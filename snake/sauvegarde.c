#include <stdio.h>
#include "sauvegarde.h"

/* genere automatiquement le nom du fichier de sauvegarde selon le slot  (static)*/
static void nom_fichier_slot(char* nom, int slot) {
    sprintf(nom, "sauvegarde_slot_%d.txt", slot);
}

int sauvegarder_partie(const Serpent* serpent, /*const psq on lit seulement on modifie rien*/
                       const Fruit* fruit,
                       int score,
                       int slot) {

    char nom[32];
    nom_fichier_slot(nom, slot);

    FILE* f = fopen(nom, "w");
    if (f == NULL)
        return 0;

    fprintf(f, "%d\n", score); /*1ere ligne du ficher, le score*/
    fprintf(f, "%d\n", serpent->longueur); /*taille du serpent*/
    fprintf(f, "%d\n", serpent->direction);

    for (int i = 0; i < serpent->longueur; i++) /*elle écrit chaque case du serpent ligne par ligne*/
        fprintf(f, "%d %d\n",
                serpent->corps[i].x, /*position horizontale*/
                serpent->corps[i].y); /*positio verticale*/

    fprintf(f, "%d %d\n", fruit->x, fruit->y); /*écriture de la position du fruit*/

    fclose(f); /*on ferme le fichier*/
    return 1;
}

int charger_partie(Serpent* serpent,
                   Fruit* fruit,
                   int* score,
                   int slot) {

    char nom[32];
    nom_fichier_slot(nom, slot);

    FILE* f = fopen(nom, "r"); /*ouverture en lecture*/
    if (f == NULL) /*si le fichier ne s'ouvre pas ou n'existe pas on ne peut pas charger*/
        return 0;

    fscanf(f, "%d", score); /* on lit la premiere ligne du code*/
    fscanf(f, "%d", &serpent->longueur);
    fscanf(f, "%d", (int*)&serpent->direction);

    for (int i = 0; i < serpent->longueur; i++)
        fscanf(f, "%d %d",
               &serpent->corps[i].x,
               &serpent->corps[i].y);

    fscanf(f, "%d %d", &fruit->x, &fruit->y);

    fclose(f);
    return 1;
}

int sauvegarde_existe(int slot) {

    char nom[32];
    nom_fichier_slot(nom, slot);

    FILE* f = fopen(nom, "r");
    if (f == NULL)
        return 0;

    fclose(f);
    return 1;
}
