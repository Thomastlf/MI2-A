#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_LIGNE 512

void verifier_erreur_fichier(FILE* fichier){//procédure permettant de vérifier qu'il n'y a pas eu d'erreur lors de l'ouverture du fichier
  if (fichier==NULL){
    perror("Erreur lors de l'ouverture du fichier.");
    exit(EXIT_FAILURE);
  }
}

Usine* lire_fuites(const char* nom_fichier,const char* usine_id,Usine** usine){
  FILE* file=fopen(nom_ficher,"r");
  verifier_erreur_fichier(fichier);
  char ligne[TAILLE_LIGNE];
  while(fgets(ligne,TAILLE_LIGNE,fichier)!=NULL){//tant qu'il y a des lignes non traitées dans le fichier..
    ligne[strcspn(ligne,"\r\n")] ='\0';//enlève le retour à la ligne
    char* colonne[5];
    for(int i=0; i<5; i++){ 
      colonne[i] = NULL;
    }
    char* temp=strtok(ligne,";");
    int i=0;
    while(i<5 && temp!=NULL){
      colonne[i]=temp;
      temp=strtok(NULL,";");
      i++;
    }
    if (!colonne[0] || !colonne[1] || !colonne[2] || !colonne[3] || !colonne[4]){
      fprintf(stderr, "Données corrompues détectées.\n");
      exit(EXIT_FAILURE);
    }
[ à finir]
}

double calculer_fuites(Noeud* noeud,double volume_entrant){
  if(noeud==NULL || volume<=0.0){
    return 0.0;
  }
  if(noeud_actuel->est_libere==1){
    return 0.0;
  }
  noeud->est_libere=1;
  double fuite_troncon_actuel=volume_entrant*(noeud->pourcentage_fuite/100.0);
  double total_fuites = fuite_troncon_actuel;
  double volume_restant = volume_entrant - fuite_troncon_actuel;
  if (noeud_actuel->nombre_enfants > 0) {
    double volume_par_enfant = volume_restant / (double)noeud->nombre_enfants;
    Lien *lien = noeud_actuel->enfants;
    while (lien != NULL) {
      total_fuites += calculer_fuites_recursif(lien->enfant, volume_par_enfant);
      lien = lien->suivant;
    }
  }
  noeud_actuel->est_visite = 0; 
  return total_fuites;
}
