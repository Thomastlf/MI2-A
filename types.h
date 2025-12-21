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

void verifier_erreur_fichier(FILE* fichier);
Usine* trouver_usine(Usine* racine, const char* id);
Usine* creer_usine(const char* id, long capa);
Usine* inserer_usine(Usine* a, Usine* nouvelle, int* h);
Noeud* creer_noeud(const char* id, float fuite);
Noeud* inserer_noeud_avl(Noeud* a, Noeud *nouveau, int* h);
Noeud* trouver_noeud_avl(Noeud* racine, const char* id);
void ajouter_enfant(Noeud* parent, Noeud* enfant);
void lecture(const char* nom_fichier, Usine** usine);
void liberer_arbre_usine(Usine* a);
void liberer_avl_noeud(Noeud *racine);
void ecrire(Usine* usine, const char* nom_fichier, const char* type);
double calculer_fuites(const char* nom_fichier, const char* id_usine);

#endif
