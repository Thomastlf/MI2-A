#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#define TAILLE_LIGNE 512

Noeud* lire_fuites(const char* nom_fichier, const char* usine_id, Noeud** noeud) {
  FILE* fichier=fopen(nom_fichier, "r");
  verifier_erreur_fichier(fichier);
  Noeud* racine_arbre=creer_noeud(usine_id, 0.0);
  *noeud=inserer_noeud_avl(*noeud, racine_arbre);
  char ligne[TAILLE_LIGNE];
  while (fgets(ligne,TAILLE_LIGNE,fichier) != NULL) {
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
    if (!colonne[0] || !colonne[1] || !colonne[2] || !colonne[3] || !colonne[4]) {
      continue; 
    }
    char *id_aval = colonne[2];
    double fuite=0.0;
    if (strcmp(colonne[4],"-")){
      fuite=atof(colonne[4]);
    }
    if (strstr(colonne[1], "Storage") || strstr(colonne[1], "Junction") || strstr(colonne[1], "Service")) {//réseau de distribution aval
      char *id_amont=colonne[1]; 
      Noeud *noeud_aval=recherche_avl(*noeud,id_aval);
      if (noeud_aval==NULL) {
        noeud_aval=creer_noeud(id_aval, fuite);
        *noeud=inserer_noeud_avl(*noeud,noeud_aval);
      } 
      else {
        noeud_aval->pourcentage_fuite=fuite;
      }
      Noeud *noeud_amont=recherche_avl(*noeud,id_amont);
      if (noeud_amont == NULL) {
        noeud_amont=creer_noeud(id_amont, 0.0);
        *noeud=inserer_noeud_avl(*noeud,noeud_amont);
      }
      ajouter_enfant(noeud_amont,noeud_aval);
    }
    else if (!strcmp(colonne[0],"-") && !strcmp(colonne[1],usine_id) && strstr(colonne[2],"Storage")) {//stockage
      Noeud *noeud_aval=recherche_avl(*noeud,id_aval);
      if (noeud_aval == NULL) {
        noeud_aval=creer_noeud(id_aval,fuite);
        *noeud=inserer_noeud_avl(*noeud,noeud_aval);
      }
      else {
        noeud_aval->pourcentage_fuite=fuite;
      }
      Noeud *noeud_amont=racine_arbre; 
      ajouter_enfant(noeud_amont,noeud_aval);
    }
  }
  fclose(fichier);
  return racine_arbre;
}

double calculer_fuites_rec(Noeud* noeud,double volume_entrant){
  if(noeud==NULL || volume_entrant<=0.0){
    return 0.0;
  }
  if(noeud->est_visite==1){
    return 0.0;
  }
  noeud->est_visite=1;
  double fuite_troncon_actuel=volume_entrant*(noeud->pourcentage_fuite/100.0);
  double total_fuites = fuite_troncon_actuel;
  double volume_restant = volume_entrant - fuite_troncon_actuel;
  if (noeud->nombre_enfants > 0) {
    double volume_par_enfant = volume_restant / (double)noeud->nombre_enfants;
    Lien *lien = noeud->enfants;
    while (lien != NULL) {
      total_fuites += calculer_fuites_rec(lien->enfant, volume_par_enfant);
      lien = lien->suivant;
    }
  }
  noeud->est_visite = 0; 
  return total_fuites;
}

double calculer_fuites(const char* nom_fichier,const char* usine_id){
  Usine* racine_usine=NULL;
  lecture(nom_fichier,&racine_usine);
  Usine* usine=trouver_usine(racine_usine,usine_id);
  if (usine==NULL || usine->total_traite==0){
    liberer_arbre_usine(racine_usine);
    return -1.0;
  }
  double volume_initial=usine->total_traite/1000.0;//conversion
  Noeud* noeud_avl=NULL;
  Noeud* noeud_arbre=lire_fuites(nom_fichier,usine_id,&noeud_avl);
  double fuites=0.0;
  if(noeud_arbre!=NULL){
    fuites=calculer_fuites_rec(noeud_arbre,volume_initial);
  }
  liberer_arbre_usine(racine_usine);
  liberer_avl_noeud(noeud_avl);
  return fuites;
}
