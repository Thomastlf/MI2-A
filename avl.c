#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max2(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

int min2(int a, int b) {
    if (a < b) {
        return a;
    } else {
        return b;
    }
}

int min3(int a, int b, int c) {
    int m = min2(b, c);
    if (a < m) {
        return a;
    } else {
        return m;
    }
}

int max3(int a, int b, int c) {
    int m = max2(b, c);
    if (a > m) {
        return a;
    } else {
        return m;
    }
}

char* dupliquer_chaine(const char *s) {
    if (s == NULL) {
        return NULL;
    }
    size_t taille = strlen(s) + 1;
    char *nouveau = malloc(taille);
    if (nouveau != NULL) {
        strcpy(nouveau, s);
    } 
    return nouveau;
}

Usine* trouver_usine(Usine *racine, const char *id) {
    if (racine == NULL) {
        return NULL;
    }
    if (strcmp(racine->id, id) == 0) {
        return racine;
    }
    if (strcmp(id, racine->id) < 0) {
        return trouver_usine(racine->gauche, id);
    } else {
        return trouver_usine(racine->droite, id);
    }
}

Noeud* trouver_noeud_avl(Noeud *racine, const char *id) {
    if (racine == NULL) {
        return NULL;
    }
    if (strcmp(racine->id, id) == 0) {
        return racine;
    }
    if (strcmp(id, racine->id) < 0) {
        return trouver_noeud_avl(racine->avl_gauche, id);
    } else {
        return trouver_noeud_avl(racine->avl_droite, id);
    }
}

Usine *rotation_gauche_usine(Usine *a) {
    Usine *pivot = a->droite;
    int eq_a = a->equilibre;
    int eq_p = pivot->equilibre;

    a->droite = pivot->gauche;
    pivot->gauche = a;

    a->equilibre = eq_a - max2(eq_p, 0) - 1;
    pivot->equilibre = min3(eq_a - 2, eq_a + eq_p - 2, eq_p - 1);
    return pivot;
}

Usine *rotation_droite_usine(Usine *a) {
    Usine *pivot = a->gauche;
    int eq_a = a->equilibre;
    int eq_p = pivot->equilibre;

    a->gauche = pivot->droite;
    pivot->droite = a;

    a->equilibre = eq_a - min2(eq_p, 0) + 1;
    pivot->equilibre = max3(eq_a + 2, eq_a + eq_p + 2, eq_p + 1);
    return pivot;
}

Usine* equilibrer_usine(Usine *a) {
    if (a->equilibre >= 2) {
        if (a->droite->equilibre >= 0) {
            return rotation_gauche_usine(a);
        } else {
            a->droite = rotation_droite_usine(a->droite);
            return rotation_gauche_usine(a);
        }
    } else if (a->equilibre <= -2) {
        if (a->gauche->equilibre <= 0) {
            return rotation_droite_usine(a);
        } else {
            a->gauche = rotation_gauche_usine(a->gauche);
            return rotation_droite_usine(a);
        }
    }
    return a;
}

Noeud *rotation_gauche_noeud(Noeud *a) {
    Noeud *pivot = a->avl_droite;
    int eq_a = a->equilibre;
    int eq_p = pivot->equilibre;

    a->avl_droite = pivot->avl_gauche;
    pivot->avl_gauche = a;

    a->equilibre = eq_a - max2(eq_p, 0) - 1;
    pivot->equilibre = min3(eq_a - 2, eq_a + eq_p - 2, eq_p - 1);
    return pivot;
}

Noeud *rotation_droite_noeud(Noeud *a) {
    Noeud *pivot = a->avl_gauche;
    int eq_a = a->equilibre;
    int eq_p = pivot->equilibre;

    a->avl_gauche = pivot->avl_droite;
    pivot->avl_droite = a;

    a->equilibre = eq_a - min2(eq_p, 0) + 1;
    pivot->equilibre = max3(eq_a + 2, eq_a + eq_p + 2, eq_p + 1);
    return pivot;
}

Noeud* equilibrer_noeud(Noeud *a) {
    if (a->equilibre >= 2) {
        if (a->avl_droite->equilibre >= 0) {
            return rotation_gauche_noeud(a);
        } else {
            a->avl_droite = rotation_droite_noeud(a->avl_droite);
            return rotation_gauche_noeud(a);
        }
    } else if (a->equilibre <= -2) {
        if (a->avl_gauche->equilibre <= 0) {
            return rotation_droite_noeud(a);
        } else {
            a->avl_gauche = rotation_gauche_noeud(a->avl_gauche);
            return rotation_droite_noeud(a);
        }
    }
    return a;
}

Usine *creer_usine(const char *id, long capa) {
    Usine *u = malloc(sizeof(Usine));
    if (u == NULL) return NULL;
    u->id = dupliquer_chaine(id);
    u->capa_max = capa; 
    u->total_capte = 0; u->total_traite = 0; 
    u->gauche = u->droite = NULL;
    u->stockages_initiaux = NULL;
    u->equilibre = 0;
    return u;
}

Usine* inserer_usine(Usine *a, Usine *nouvelle, int *h) {
    if (a == NULL) {
        *h = 1; 
        return nouvelle;
    }
    
    int comp = strcmp(nouvelle->id, a->id);

    if (comp < 0) {
        a->gauche = inserer_usine(a->gauche, nouvelle, h);
        *h = -(*h);
    } 
    else if (comp > 0) {
        a->droite = inserer_usine(a->droite, nouvelle, h);
    } 
    else {
        if (nouvelle->capa_max > a->capa_max) {
            a->capa_max = nouvelle->capa_max;
        }
        
        if (nouvelle->id != NULL) {
            free(nouvelle->id);
        }
        free(nouvelle);
        
        *h = 0; 
        return a;
    }

    if (*h != 0) {
        a->equilibre = a->equilibre + *h;
        
        a = equilibrer_usine(a);
        
        if (a->equilibre == 0) {
            *h = 0; 
        } else {
            *h = 1; 
        }
    }

    return a;
}

Noeud* creer_noeud(const char *id, float fuite) {
    Noeud *n = malloc(sizeof(Noeud));
    
    if (n == NULL) {
        return NULL;
    }
    
    n->id = dupliquer_chaine(id);
    n->pourcentage_fuite = fuite;
    n->nb_enfants = 0;
    n->est_libere = 0;
    n->liste_enfants = NULL;
    n->avl_gauche = NULL;
    n->avl_droite = NULL;
    n->equilibre = 0;
    
    return n;
}

Noeud* inserer_noeud_avl(Noeud *a, Noeud *nouveau, int *h) {
    if (a == NULL) {
        *h = 1; 
        return nouveau;
    }

    int comp = strcmp(nouveau->id, a->id);

    if (comp < 0) {
        a->avl_gauche = inserer_noeud_avl(a->avl_gauche, nouveau, h);
        *h = -(*h);
    } 
    else if (comp > 0) {
        a->avl_droite = inserer_noeud_avl(a->avl_droite, nouveau, h);
    } 
    else {
        if (nouveau->id != NULL) {
            free(nouveau->id);
        }
        free(nouveau);
        
        *h = 0; 
        return a;
    }

    if (*h != 0) {
        a->equilibre = a->equilibre + *h;
        
        a = equilibrer_noeud(a);
        
        if (a->equilibre == 0) {
            *h = 0; 
        } else {
            *h = 1; 
        }
    }

    return a;
}

void ajouter_enfant(Noeud *parent, Noeud *enfant) {
    if (parent == NULL) {
        return;
    }
    if (enfant == NULL) {
        return;
    }
    
    Lien *l = malloc(sizeof(Lien));
    
    if (l == NULL) {
        return;
    }
    
    l->enfant = enfant;
    l->suivant = parent->liste_enfants;
    parent->liste_enfants = l;
    parent->nb_enfants = parent->nb_enfants + 1;
}

void liberer_arbre_usine(Usine *a) {
    if (a != NULL) {
        liberer_arbre_usine(a->gauche);
        liberer_arbre_usine(a->droite);
        if (a->id != NULL) free(a->id);
        Lien *courant = a->stockages_initiaux;
        while (courant != NULL) {
            Lien *temp = courant;
            courant = courant->suivant;
            free(temp);
        }
        free(a);
    }
}

void liberer_arbre(Noeud *racine) {
    if (racine == NULL) {
        return;
    }

    if (racine->est_libere == 1) {
        return;
    }

    racine->est_libere = 1;
    Lien *courant = racine->liste_enfants;

    while (courant != NULL) {
        liberer_graphe(courant->enfant);
        
        Lien *temp = courant;
        courant = courant->suivant;
        free(temp);
    }
}

void liberer_avl_noeud(Noeud *racine) {
    if (racine == NULL) {
        return;
    }

    liberer_avl_noeud(racine->avl_gauche);
    liberer_avl_noeud(racine->avl_droite);

    if (racine->id != NULL) {
        free(racine->id);
    }

    free(racine);
}
