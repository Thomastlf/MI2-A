#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

#define TAILLE_LIGNE 512

void verifier_erreur_fichier(FILE* fichier){//procédure permettant de vérifier qu'il n'y a pas eu d'erreur lors de l'ouverture du fichier
  if (fichier==NULL){
    printf("Erreur lors de l'ouverture du fichier.\n");
    exit(EXIT_FAILURE);
  }
}

void lecture(const char* nom_fichier, AVL** avl){//procédure qui va lire toutes les lignes du fichier et remplir l'avl
  FILE* fichier=fopen(nom_fichier,"r");
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
    if(!strcmp(colonne[0],"-") && !strcmp(colonne[2],"-") && !strcmp(colonne[4],"-")){//si la ligne correspond à une usine
      AVL* est_dans_avl=recherche(*avl,colonne[1]);
      if(est_dans_avl==NULL){//usine pas encore crée
        AVL* nouveau=creerAVL(colonne[1],atof(colonne[3]);
        *avl=insertAVL(*avl,nouveau);
      }
      else{
        est_dans_avl->capacite_max=atof(colonne[3]);
      }
    }
    else if(!strcmp(colonne[0],"-") && strcmp(colonne[3],"-")){//si la ligne correspond à un captage
      AVL* est_dans_avl=recherche(*avl,colonne[2]);
      if(est_dans_avl==NULL){//usine pas encore créer
        AVL* nouveau=creerAVL(colonne[2],0);
        *avl=insertAVL(*avl,nouveau);
        nouveau->volume_total_capte=nouveau->volume_total_capte+atof(colonne[3]);
        nouveau->volume_total_traite=nouveau->volume_total_traite+atof(colonne[3])*(1-atof(colonne[4])/100);
      }
      else{
        est_dans_avl->volume_total_capte=est_dans_avl->volume_total_capte+atof(colonne[3]);
        est_dans_avl->volume_total_traite=est_dans_avl->volume_total_traite+atof(colonne[3])*(1-atof(colonne[4])/100);
      }
    }
  }
  fclose(fichier);
}

void ecrire(Avl* avl,const char* nom_fichier,const char* mode){

}
