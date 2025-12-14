#include <stdlib.h>
#include <stdio.h>

void verifier_erreur_fichier(FILE* fichier){//procédure permettant de vérifier qu'il n y a pas eu d'erreur lors de l'ouverture du fichier
  if (fichier==NULL){
    printf("Erreur lors de l'ouverture du fichier.\n");
    exit(EXIT_FAILURE);}
}

void lecture(FILE* fichier, AVL* avl){
  while(){#le fichier n'est pas nul
    
