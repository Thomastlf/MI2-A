#include <stdio.h>
#include <stdlib.h>

typedef struct avl{
    struct avl* fg;
    struct avl* fd;
    char valeur[32];
    int eq;
}AVL;

AVL* creerAVL(char e[]){
    AVL* avl=malloc(sizeof(AVL));
    if(avl==NULL){
        exit(1);
    }
    avl->fg=NULL;
    avl->fd=NULL;
    avl->valeur=e;
    avl->eq=0;
    return avl;
}

AVL* insertionAVL(AVL* avl,char e[],int* h){
    if(avl==NULL){
        *h=1;
        avl=creerAVL(e);
    }
    if(e<avl->valeur){
        avl->fg=insertionAVL(avl->fg,e);
        *h=-*h
    }
    if(e>avl->valeur){
        avl->fd=insertionAVL(avl->fd,e);
    }
    if(e==avl->valeur){
        *h=0
    }
    if(*h!=0){
        avl->eq=avl->eq+*h;
        avl=equilibrageAVL(avl);
        if(avl->eq==0){
            *h=0;
        }
        else{
            *h=1;
        }
    }
    return avl;
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


AVL* suppMax(AVL* a,char* pe[32],int* h){
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

AVL* suppressionAVL(AVL* a,int e,int* h){
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

int main(){
  return 0;
}
