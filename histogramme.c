#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#define TAILLE_LIGNE 512

void verifier_erreur_fichier(FILE* fichier){//procédure permettant de vérifier qu'il n'y a pas eu d'erreur lors de l'ouverture du fichier
  if (fichier==NULL){
    perror("Erreur lors de l'ouverture du fichier CSV");
    exit(EXIT_FAILURE);
  }
}

void lecture(const char* nom_fichier,Usine** usine){//procédure qui va lire toutes les lignes du fichier et remplir l'avl
  FILE* fichier=fopen(nom_fichier,"r");
  verifier_erreur_fichier(fichier);
  char ligne[TAILLE_LIGNE];
                                      int compteur_lignes_lues = 0;int compteur_usines_trouvees = 0;
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
      continue;
    }
    if(!strcmp(colonne[0],"-") && !strcmp(colonne[2],"-") && !strcmp(colonne[4],"-")){//si la ligne correspond à une usine
                                compteur_usines_trouvees++;
      Usine* est_dans_avl=trouver_usine(*usine,colonne[1]);
      if(est_dans_avl==NULL){//usine pas encore crée
        int h = 0;
        Usine* nouveau=creer_usine(colonne[1],atof(colonne[3]));
        *usine=inserer_usine(*usine,nouveau,&h);
      }
      else{
        est_dans_avl->capa_max=atof(colonne[3]);
      }
    }
    else if(!strcmp(colonne[0],"-") && strcmp(colonne[3],"-")){//si la ligne correspond à un captage
      Usine* est_dans_avl=trouver_usine(*usine,colonne[2]);
      if(est_dans_avl==NULL){//usine pas encore créer
        Usine* nouveau=creer_usine(colonne[2],0);
        int h=0;
        *usine=inserer_usine(*usine,nouveau,&h);
        nouveau->total_capte=nouveau->total_capte+atof(colonne[3]);
        nouveau->total_traite=nouveau->total_traite+atof(colonne[3])*(1-atof(colonne[4])/100);
      }
      else{
        est_dans_avl->total_capte=est_dans_avl->total_capte+atof(colonne[3]);
        est_dans_avl->total_traite=est_dans_avl->total_traite+atof(colonne[3])*(1-atof(colonne[4])/100);
      }
    }
  }printf("Usines détectées dans le fichier : %d\n", compteur_usines_trouvees);
  fclose(fichier);
}

void ecrire_rec(Usine* usine,FILE* fichier,const char* mode){//parcours infixe en commençant par la droite pour avoir les id dans l'ordre décroissant
  if (usine!=NULL){
    ecrire_rec(usine->droite,fichier,mode);
    double valeur=0.0;
    if(!strcmp(mode,"max")){
      valeur=(double)usine->capa_max;
    }
    else if(!strcmp(mode,"src")){
      valeur=(double)usine->total_capte;
    }
    else if(!strcmp(mode,"real")){
      valeur=(double)usine->total_traite;
    }
    fprintf(fichier,"%s;%.3f\n",usine->id,valeur/1000.0);//écris dans le fichier l'id puis valeur jusqu'à 3 chiffres après la virgule
    ecrire_rec(usine->gauche,fichier,mode);
  }
}

void ecrire(Usine* usine,const char* nom_fichier,const char* mode){//fonction qui va écrire le fichier.csv
  FILE* fichier=fopen(nom_fichier,"w");
  verifier_erreur_fichier(fichier);
  //On écrit en première ligne du fichier les noms des colonnes suivantes
  if (strcmp(mode, "max") == 0){
    fprintf(fichier, "identifier;max volume (M.m³.year⁻¹)\n");
  }
  else if (strcmp(mode, "src") == 0){
    fprintf(fichier, "identifier;source volume (M.m³.year⁻¹)\n");
  }
  else if (strcmp(mode, "real") == 0){
    fprintf(fichier, "identifier;real volume (M.m³.year⁻¹)\n");
  }
  else{
    fprintf(stderr, "Erreur : parametre %s incorrect\n", mode);
    fclose(fichier);
    exit(EXIT_FAILURE);
  }
  ecrire_rec(usine,fichier,mode);
  fclose(fichier);
}
