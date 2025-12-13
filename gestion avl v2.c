#include <stdio.h>
#include <stdlib.h>

typedef struct avl{
  struct avl* fg;
  struct avl* fd;
  int eq;
  char id[32];
  float capacite_max;
  float volume_total_capte;
  float volume_total_traite;
}AVL;

AVL* creerAVL(char id[]){
  AVL* avl=malloc(sizeof(AVL));
  if(avl==NULL){
    exit(1);
  }
  avl->fg=NULL;
  avl->fd=NULL;
  avl->eq=0;
  strcpy(avl->id,id)
  avl->capacite_max=0;
  avl->volume_total_capte=0;
  avl->volume_total_traite=0;
  return avl;
}

AVL* rechercher_usine(AVL* racine, const char id_recherche[]) {
    if (racine == NULL) {
        return NULL;
    }
  
    int comparaison = strcmp(id_recherche, racine->id);

    if (comparaison == 0) {
        return racine;
    }
    else if (comparaison < 0) {
        return rechercher_usine(racine->fg, id_recherche);
    }
    else {
        return rechercher_usine(racine->fd, id_recherche);
    }
}



AVL* rotationGauche(AVL* avl){
    AVL* pivot=avl->fd;
    int eq_a=avl->eq;
    int eq_p=pivot->eq;
    
    avl->fd=pivot->fg;
    pivot->fg=avl;
    
    avl->eq=eq_a-max(eq_p,0)-1;
    pivot->eq=min(eq_a-2,eq_a+eq_p-2,eq_p-1);
    return pivot;
}

AVL* rotationDroite(AVL* avl){
    AVL* pivot=avl->fg;
    int eq_a=avl->eq,eq_p=pivot->eq;
    avl->fg=pivot->fd;
    pivot->fd=avl;
    a->eq=eq_a-min(eq_p,0)+1;
    pivot->eq=max(eq_a+2,eq_a+eq_p+2,eq_p+1);
    return pivot;
}

AVL* doubleRotationGauche(AVL* avl){
    avl->fd=rotationDroite(avl->fd);
    avl=rotationGauche(avl);
    return avl;
}

AVL* doubleRotationDroite(AVL* avl){
    avl->fg=rotationGauche(avl->fg);
    avl=rotationDroite(avl);
    return avl;
}

AVL* equilibrageAVL(AVL* a){
    if(a->eq<=-2){
        if(a->fg->eq>0){
            a=doubleRotationDroite(a);
        }
        else{
            a=rotationDroite(a);
        }
    }
    if(a->eq>=2){
        if(a->fd->eq<0){
            a=doubleRotationGauche(a);
        }
        else{
            a=rotationGauche(a);
        }
    }
    return a;
}

int inverse_alphabetique(char a[],char b[]){// retourne 1 si b est avant a dans l'alphabet, sinon 0
    if(b[0]>a[0]){
        return 1;
    }
    if(b[0]<a[0]){
        return 0;
    }
    return inverse_alphabetique(a+1,b+1);
}

AVL* insertionAVL(AVL* a,char e[],int* h){
    if(a==NULL){
        *h=1;
        return creerAVL(e);
    }
    if(e<a->valeur){
        a->fg=insertionAVL(a->fg,e,h);
        *h=-*h;
    }
    if(e>a->valeur){
        a->fd=insertionAVL(a->fd,e,h);
    }
    if(e==a->valeur){
        *h=0;
    }
    if(*h!=0){
        a->eq=a->eq+*h;
        equilibrageAVL(a);
        if(a->eq==0){
            *h=0;
        }
        else{
            *h=-1;
        }
    }
    return a;
}

AVL* suppMax(AVL* a,char* pe[],int* h){
    if(a->fg!=NULL){
        a->fg=suppMax(a->fg,pe);
        *h=-*h;
    }
    else{
        *pe=a->valeur;
        AVL* temp=a;
        a=a->fd;
        free(temp);
        *h=-1;
    }
    if(*h!=0){
        a->eq=a->eq+*h;
        a=equilibrageAVL(a);
        if(a->eq==0){
            *h=-1;
        }
        else{
            *h=0;
        }
    }
    return a;
}

AVL* suppressionAVL(AVL* a,char* e,int* h){
    if(a==NULL){
        *h=0;
        return NULL;
    }
    if(e<a->valeur){
        a->fg=suppressionAVL(a->fg,e,h);
        *h=-*h;
    }
    if(e>a->valeur){
        a->fd=suppressionAVL(a->fd,e,h);
    }
    if(e==a->valeur){
        if(a->fd==NULL){
            AVL* temp=a;
            a=a->fg;
            free(temp);
            *h=-1;
        }
        else{
            a->fd=suppMin(a->fd,&a->valeur,h);
        }
    }
    if(*h!=0){
        a->eq=a->eq+*h;
        a=equilibrageAVL(a);
        if(a->eq==0){
            *h=-1;
        }
        else{
            *h=0;
        }
    }
    return a;
}
