#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Usine *rotation_gauche(Usine *a) {
    Usine *pivot = a->droit;
    int eq_a = a->equilibre;
    int eq_p = pivot->equilibre;

    a->droit = pivot->gauche;
    pivot->gauche = a;

    a->equilibre = eq_a - max2(eq_p, 0) - 1;
    pivot->equilibre = min3(eq_a - 2, eq_a + eq_p - 2, eq_p - 1);
    return pivot;
}

Usine *rotation_droite(Usine *a) {
    Usine *pivot = a->gauche;
    int eq_a = a->equilibre;
    int eq_p = pivot->equilibre;

    a->gauche = pivot->droit;
    pivot->droit = a;

    a->equilibre = eq_a - min2(eq_p, 0) + 1;
    pivot->equilibre = max3(eq_a + 2, eq_a + eq_p + 2, eq_p + 1);
    return pivot;
}

Usine *equilibrer_avl(Usine *a) {
    if (a->equilibre >= 2) {
        if (a->droit->equilibre >= 0) return rotation_gauche(a);
        else {
            a->droit = rotation_droite(a->droit);
            return rotation_gauche(a);
        }
    } else if (a->equilibre <= -2) {
        if (a->gauche->equilibre <= 0) return rotation_droite(a);
        else {
            a->gauche = rotation_gauche(a->gauche);
            return rotation_droite(a);
        }
    }
    return a;
}



