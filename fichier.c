#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_LIGNE 256


void verifier_erreur_fichier(FILE* fichier){//procédure permettant de vérifier qu'il n y a pas eu d'erreur lors de l'ouverture du fichier
  if (fichier==NULL){
    printf("Erreur lors de l'ouverture du fichier.\n");
    exit(EXIT_FAILURE);
  }
}

void lecture(const char* nom_fichier, AVL* avl){
  FILE* fichier=fopen(nom_fichier,"r");
  verifier_erreur_fichier(fichier);
  char ligne[TAILLE_LIGNE];
  while(fgets(ligne,TAILLE_LIGNE,fichier)!=NULL){
    char* colonne[5];
    char* temp=strtok(ligne,";");
    for(int i=0;i<5;i++){
      colonne[i]=temp;
      temp=strtok(NULL,";");
    }
    if(!strcmp(colonne[0],"-") && !strcmp(colonne[2],"-")){//si la ligne correspond à une usine
      
