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

typedef struct chainon{
  int valeur;
  struct chainon *suivant;
}Chainon;

typedef struct pile{
  Chainon *tete;
}Pile;

Chainon*createChainon(int a){
  Chainon *p1=malloc(sizeof(Chainon));
  if(p1==NULL){
    exit(1);
  }
  p1->valeur=a;
  p1->suivant=NULL;
  return p1;
}

Chainon *ajoutDebut(Chainon *tete, int val){
  Chainon *new=createChainon(val);
  if(new==NULL){
    exit(1);
  }
  new->suivant=tete;
  tete=new;
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

//fonction pour creer une nouvelle pile et l'initialiser

Pile *createPile(){
  Pile *pile = malloc(sizeof(Pile));
  if(pile == NULL){
    exit(1);
  }
  pile->tete=NULL; //la pile est nulle donc le sommet est vide
  return pile;
}

//fonction pour empiler un entier dans la pile

void empiler(Pile *pile, int val){
  Pile *new =createPile();
  if(new == NULL){
    exit(23);
  }
  pile->tete=ajouterDebut(pile->tete,val);
  return pile;
}

void afficherPile(Pile *pile){
  affiherListe(pile->tete);// Affiche les éléments de la pile en utilisant afficheListe
}
//autre maniere recurssive

void afficherPileRec(Chainon *pile){
  if(pile != NULL){
    printf("%d\n", pile->valeur);
    affichePileRec(pile->suivant);
  }
}

//On crée la fonction qui permet de dépiler une valeur sur la pile

Pile *depiler(Pile *pile, int *val){//a retenir a chaque suppression ou free on est obliger de declarer ou de mettre la valeur en pointeur dans le parametre, ca permet de stocker la valeur qui est supprimee en memeoire et ne pas la perdre OK!!
      if(pile == NULL){
        exit(18);// la pile n'existe pasdonc on ne peut pas depiler
      }
      if(pile->tete == NULL){//la pile est vide donc on ne peut pas depiler
        exit(19);
      }

    Chainon *tmp = pile->tete->suivant;//sauvegarder le deuxieme element*val
    *val = pile->tete->valeur;//recuperer la valeur du premier element
    free(pile->tete);//supprimer le premier element
    pile->tete =tmp; //mettre a jour le nouveau premier element 2
    return pile;
}

int main(){
  Pile *p1 =createPile();
  for(int i=0; i<20; i++){
    P1= empiler(P1, i);
  }
  affichePile(p1);

  Pile *pilePair = createPile();
  Pile *pileImpair = createPile();

  int nb;
  while(p1!=NULL){
    p1=depiler(p1,&nb);
      if(nb%2==0){
        pilePair = empiler(pilePair, nb);
      }
      else{
        pileImpair = empiler(pileImpair, nb);
    }
  }
  afficherPile(pilePair);
  afficherPile(pileImpaire);

  return 0;
}
