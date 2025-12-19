#ifndef TYPES_H
#define TYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Lien {
    struct Noeud *enfant;
    struct Lien *suivant;
} Lien;

typedef struct Usine {
    char *id;
    long capa_max;
    long total_capte;
    long total_traite;
    int equilibre;
    struct Usine *gauche;
    struct Usine *droite;
} Usine;

typedef struct Noeud {
    char *id;
    float pourcentage_fuite;
    int nb_enfants;
    int est_visite;
    Lien *liste_enfants;
    int equilibre;
    struct Noeud *avl_gauche;
    struct Noeud *avl_droite;
} Noeud;

void verifier_erreur_fichier(FILE* fichier);
Usine* trouver_usine(Usine *root, const char *id);
Usine* creer_usine(const char* id, long capa);
Usine* inserer_usine(Usine *a, Usine *nouvelle, int *h);
Noeud* creer_noeud(const char* id, float fuite);
Noeud* inserer_noeud_avl(Noeud *a, Noeud *nouv, int *h);
Noeud* trouver_noeud_avl(Noeud *racine, const char *id);
void ajouter_enfant(Noeud *parent, Noeud *enfant);
void lecture(const char *fichier, Usine **racine);
void liberer_arbre_usine(Usine *a);
void liberer_avl_noeud(Noeud *racine);
void ecrire(Usine *racine, const char *fichier, const char *type);
double calculer_fuites(const char *fichier, const char *id_usine);

#endif
