#include "types.h" // Importe les déclarations

int main(int argc, char *argv[]) {
    
    // 1. Vérification des arguments minimaux
    if (argc < 3) {
        fprintf(stderr, "Erreur Main : Arguments manquants. Utilisez le script shell.\n");
        return 1;
    }

    // 2. Récupération des arguments
    const char *fichier_donnees = argv[1];
    const char *commande = argv[2];
    const char *option_cmd = (argc > 3) ? argv[3] : NULL;

    struct Usine *racine_avl = NULL;
    int code_retour = 0;

    // --- CAS 1 : HISTO ---
    if (strcmp(commande, "histo") == 0) {
        if (option_cmd == NULL) {
            fprintf(stderr, "Erreur Main : Type d'histo manquant.\n");
            return 2;
        }
        
        // Appel fonction : lecture
        lecture(fichier_donnees, &racine_avl);

        char nom_fichier_sortie[256];
        snprintf(nom_fichier_sortie, sizeof(nom_fichier_sortie), "vol_%s.dat", option_cmd);
            
        ecrire(racine_avl, nom_fichier_sortie, option_cmd);
        
    }
    
    // --- CAS 2 : LEAKS ---
    else if (strcmp(commande, "leaks") == 0) {
        if (option_cmd == NULL) {
            fprintf(stderr, "Erreur Main : ID usine manquant.\n");
            return 3;
        }
        
        // Appel fonction : calculer_fuites
        float volume_fuites = calculer_fuites(fichier_donnees, option_cmd);
        printf("%.3f\n", volume_fuites);
    }
        
    // --- DEFAUT ---
    else {
        fprintf(stderr, "Erreur : Commande '%s' inconnue.\n", commande);
        code_retour = 99;
    }

    // Nettoyage
    if (strcmp(commande, "histo") == 0 && racine_avl != NULL) {
        // Appel fonction : liberer_arbre_usine
        liberer_arbre_usine(racine_avl);
    }
    
    return code_retour;
}
