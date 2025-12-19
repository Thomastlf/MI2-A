#ifndef TYPES_H
#define TYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lien {
    struct noeud *enfant;
    struct lien *suivant;
} Lien;

typedef struct usine {
    char *id;
    long capa_max;
    long total_capte;
    long total_traite;
    int equilibre;
    struct usine *gauche;
    struct usine *droite;
} Usine;

typedef struct noeud {
    char *id;
    float pourcentage_fuite;
    int nb_enfants;
    int est_visite;
    Lien *liste_enfants;
    int equilibre;
    struct noeud *avl_gauche;
    struct noeud *avl_droite;
} Noeud;

int max2(int a, int b);
int min2(int a, int b);
int max3(int a, int b, int c);
int min3(int a, int b, int c);
Usine* inserer_usine(Usine *a, Usine *nouvelle, int *h);
Noeud* inserer_noeud_avl(Noeud *a, Noeud *nouv, int *h);
void liberer_arbre_usine(Usine *a);
void liberer_arbre(Noeud *racine);
int lecture(const char *fichier, Usine **racine);
void ecrire(Usine *racine, const char *fichier, const char *type);
float calculer_fuites(const char *fichier, const char *id_usine);

#endif
