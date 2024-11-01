Exercice 2 (Gestion de piles)
1. Déclarer la structure PileDyn permettant de gérer une pile dynamique contenant des entiers.
2. Ecrire une fonction empiler(int nb, PileDyn* ppile) permettant d’empiler nb sur la pile dynamique pointée par
ppile.
3. Déclarer une nouvelle pile p1 et lui empiler les nombres entiers de 1 à 20 dans l’ordre croissant. Que vaudra le sommet
de la pile ?
4. Ecrire une procédure affichePile(PileDyn * ppile) permettant d’afficher le contenu d’une pile de manière récursive.
Afficher p1.
5. Ecrire une fonction depile(PileDyn * ppile, int *pnmb) permettant de dépiler une pile d’entiers passée en paramètre et de modifier la valeur de la variable pointée par pnmb avec la valeur stocké dans l’element supprimé.
6. Déclarer deux autres piles pilePair et pileImpair qui seront remplies à partir de p1 de la manière suivante :
— p1 est dépilée
— Si l’élément dépilé est pair il est empilé dans pilePair
— Si l’élément dépilé est impair il est empilé dans pileImpair
A quoi vont ressembler ces deux piles ? Vérifier grâce à affichePile(PileDyn * ppile).
7. Réecrire le programme en utilisant une pile statique.

Correction:

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct chainon {
    int valeur;
    struct chainon *suivant;
}Chainon;

typedef struct pile{
    Chainon *tete; //pointeur vers le sommet de la pile;
    int nombre;
}Pile;

Chainon *createChainon(int v){
    Chainon *new = malloc(sizeof(Chainon));
    if(new==NULL){
        exit(1);
    }
    new->valeur =v;
    new->suivant=NULL;
    return new;
}

Chainon *ajoutDebut(Chainon *tete, int val){
    if(tete == NULL){
        tete=createChainon(val);
    }else{
        Chainon *new = createChainon(val);
            if(new==NULL){
                exit(2);
            }
        new->suivant=tete;
        tete=new;//mise a jour de la tete
    }
        return tete;
}

Chainon *ajoutFin(Chainon *tete, int val){
    if (tete == NULL){
        tete= createChainon(val);
    }
    else{
        Chainon*new=createChainon(val);
            if(new==NULL){
                exit(3);
            }
        Chainon *tmp=tete;
        while(tmp->suivant != NULL){
                tmp=tmp->suivant;
            }
            tmp->suivant = new;
        }
        return tete;
}

void afficherListe(Chainon *liste){
    if(liste==NULL){
        printf("la liste est vide.\n");
    }else{
        while(liste->suivant != NULL){
            printf("%d->", liste->valeur);
            liste=liste->suivant;
        }
    }
    printf("\n");
}

Pile *createPile(){
    Pile *new =malloc(sizeof(Pile));//alloue de la memoire pour une nouvelle pile
    if(new==NULL){
        exit(5);
    }
    new->tete=NULL; //initialise la pile comme vide
    return new;//retourner la nouvelle pile
}

//fonction pour empiler
Pile *empiler(Pile *ppile, int nb){
    if(ppile==NULL){
        exit(1);
    }
    ppile->tete = ajoutDebut(ppile->tete, nb);//inserer l'element au sommet de la pile
    return ppile;
}

//fonction pour afficher la pile
void afficherPile(Pile *ppile){
    afficherListe(ppile->tete);
}

void affichePileRec(Chainon *actual){
    if(actual != NULL){
        printf("%d\n", actual->valeur);
        affichePileRec(actual->suivant);
    }
}

Pile *depiler(Pile *ppile, int *pnmb){
    if(ppile == NULL){
        exit(6);
    }
    if(ppile->tete ==NULL){
        return ppile;
    }
    Chainon *tmp = ppile->tete->suivant;//sauvegarde du deuxieme element
    *pnmb = ppile->tete->valeur; //stock la valeur de l'element a depiler
    free(ppile->tete);
    ppile->tete = tmp;//met a jour le sommet de la pile
    return ppile;
}
a suivre...
