/*Exercice 2:*/

#include <stdio.h>
#include <stdlib.h>


//exercice 2: Liste doublement chainée

typedef struct chainonD{
  char valeur;
  struct chainonD *suivant;
  struct chainonD *precedent;
}ChainonD;

ChainonD *creationChainonD(char val){
  ChainonD *new =malloc(sizeof(ChainonD));
  if(new==NULL){
    printf("Erreur d'allocation mémoire\n");
    exit(1);
  }
  new->valeur=val;
  new->suivant = NULL;
  new->precedent = NULL;
  return new;
}

//on ecris une fonction qui permet d'inserer un new chainon dans la liste a la poisition pos, si pos egal a zero new chainon au debut, si pos egal a1 alors on le place en deuxieme pos

int insertPos(ChainonD *tete, int pos, char val){
    if(tete==NULL){
       tete=creationChainonD(val); 
    }
  ChainonD *tmp =tete; //pointeur pour parcourir la liste
  int i=0;//compteur pour la position
  //on parcourt la liste jusqu'a atteindre la position pos ou la fin de la liste
  while(tmp->suivant != NULL && i<pos - 1){
    tmp=tmp->suivant;
    i++;
  }
  Chainon *tmp2 = tmp->suivant;//sauvegarde le chainon suivant a la position de l'insertion
  tmp->suivant = creationChainonD(val);//on insere le nouveau chainon
  tmp->suivant->suivant = tmp2;//lie le new chainon au chainon suivant
  tmp->suivant->precedent = tmp;//lie le new chainon au chainon precedent
  if(tmp!=NULL){//si un chainon suivant existe
    tmp2->precedent=tmp->suivant;
  }
  return tete;
}

//on cree la fonction qui affiche les caracteres majuscules de la liste chainée

void afficheMaj(ChainonD *tete){
  Chainon *tmp = tete;
  while(tmp != NULL){
    //verifie si le caractere est majuscule
    if('A' <= tmp->valeur && tmp->valeur <='Z'){
      printf("%c\n", tmp->valeur);
    }
    tmp=tmp->suivant;
  }
}

/*Exercice 4: on souhaite ecrire une fonction coupe en deux qui prend en entrée une liste chainée et qui va coupé cette liste en 2 sous listes de tailles egales*/
typedef strcut chainon{
  int valeur;
  struct chainon *suivant;
}Chainon;

//on nous donne la fonction taille qui retourne la taille de la liste

int taille(Chainon *tete);

//on crée la fonction qui coupe une liste en dexu parties egales

int coupeEn2(Chainon *tete, Chainon **liste1, Chainon **liste2){
  if(liste1 == NULL || liste2 == NULL){
    exit(1);;
  }
  //recuperer la taille de la liste
  int taille = taille(tete);
  //si la taille est impaire la division d'une liste en deux ne donne pas de resultat
  if(taille %2 != 0){
    return 0;
  }

  //si la liste d'origine est vide
  if(tete == NULL){
    *liste2 = NULL; // initialise la deuxieme liste
  }else{
    int pos = taille/2;//calcule la position pour couper la liste
    Chainon *tmp =tete;
    int i=0;
    for(int i=0; i<pos; i++){
      tmp = tmp->suivant;
    }
    Chainon *tmp2=tmp->suivant;
    tmp->suivant = NULL;
    liste2 = tmp2;//assigne la deuxieme liste a partir de l'element suivant
    
  }
  *liste1 = tete;
  return 1;
  
}
