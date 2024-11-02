1. Quelle structure (tableau, liste chaînée, pile, file) semble la plus appropriée pour ce type d’exercice ? une File
2. Déclarer ce type de structure avec comme type d’élément un entier.
3. Créer une fonction qui va créer une instance d’un client avec une valeur entière aléatoire entre 1 et 50 (simulant le
nombre d’articles dans son caddy).
4. Créer une fonction qui va afficher tous les clients dans l’ordre d’arrivée en caisse.
5. Créer un programme qui va simuler l’arrivée de clients à la caisse :
— Ajouter 3 clients en caisse
1
— Dans une boucle infinie, au début de chaque tour, on enlève le client le plus proche de la caisse (le prochain à payer
ses achats), si il existe
— Ensuite il y a 33% de chances d’ajouter de nouveaux clients en caisse
— Si on ajoute des clients, suite au point précédent, on en ajoute entre 1 et 3 (de manière aléatoire)
— A la fin de la boucle on affiche le client qui a payé ses achats et on affiche en dessous le reste des clients (dans l’ordre
d’arrivée à la caisse)
— Si il n’y a plus de clients en caisse, on arrête le programme
6. Proposer un algorithme pour modifier le programme précédent de la façon suivante :
— En commençant par les clients les plus proches de la caisse, déterminer ceux qui voudraient changer de caisse si la
somme des articles des autres clients situés devant dépasse un certain seuil
— Est ce que la structure choisie est appropriée pour ce type de calcul ? Justifier la réponse.


Correction 


#include<stdio.h>
#include<stdlib.h>

 typedef struct chainon {
    int valeur;
    strcut chainon *suivant;
 }Chainon;
//creation du chainon, element de la file
Chainon *createChainon(int a){
  Chainon *new = malloc(sizeof(Chainon));
  if(new == NULL){
    exit(1);
  }
  new->valeur = a;
  new->suivant =NULL;
  return new;
}
//ajouter chainon au debut
Chainon addDebut(Chainon *tete, int val){
  if(tete==NULL){
    tete =createChainon(val);
  }
  else{
    Chainon *nouveau = createChainon(val);
      if(nouveau == NULL){
        exit(2);
      }
    nouveau->suivant =tete;
    tete = nouveau; 
  }
  return tete;
}

Chainon *addFin(Chainon *tete, int val){
  if(tete == NULL){
    tete = createChainon(val);
  }
  else{
    Chainon *nouveau = createChainon(val);
      if(nouveau == NULL){
        exit(2);
      }
    Chainon *tmp =tete;
    while(tmp->suivant != NULL){
      tmp = tmp->suivant;
    }
    tmp->suivant = nouveau;
  }
  return tete;
}

void afficherListe(Chainon *liste){
  if(liste ==NULL){
    printf("la liste est vide");
  }
  else{
    while(liste != NULL){
      printf("%d", liste->valeur);
        if(liste->suivant != NULL){
          printf("->");
        }
      liste = liste->suivant;
    }
  printf("\n");
  }
}

Chainon supprimerDebut(Chainon *tete, int *val){
  if(tete == NULL){
    exite(3);
  }
  else{
    Chainon *tmp = tete; //stock l'element a supprimer et ne pas le perdre
    tete = tete->suivant; //on passe au suivant on met a jour la tete au deuxieme element
    *val=tmp-valeur; //on recupere la valeur de l'element a supprimer
    tmp->suivant = NULL; //on supprime le lien avec le suivant
    free(tmp); //on libere l'espace memoire
    return tete;
  }
}

typedef struct File {
    Chainon *tete; //pointeur au sommet de la file
    Chainon *fin; //pointeur en fin de file
}File;
//fonction pour creer une nouvelle file
File *createFile(){
  File newFile = malloc(sizeof(File));
  if(newFile == NULL){
    exit(11);
  }//initialisation de la file NULL NULL 0
  newFile->tete = NULL;
  newFile->queue = NULL;
  newFile->nb = 0; 
  return newFile;
}

//push : ajouter un element dans un file enfiler
//pop : enlever un element de la file defiler

void enfiler(File *file, int val){
  if(file==NULL){
    exit(12);// On vérifie si la file existe, sinon on quitte avec une erreur
  }
  if(file->fin == NULL){
    file->fin = createChainon(val);
    file->tete=file->fin;//tete` et `fin` pointent sur ce premier élément
  }
  else{
    file->fin->next = createChainon(val); // On crée un nouveau chaînon et le place après `fin`
    file->fin = file->fin->next;
  }
}

int defiler(File *file, int *val){
  if (file==NULL){
    exit(14); //si la file n'existe pas on quitte avec une erreur
  }
  if(file->tete == NULL){
    return -1; //la file est vide on quitte avec une erreur
  }
  Chainon *tmp = file->tete->suivant;//sauvegarde de l'element numero 2
  *nb = file->tete->valeur; //stock la valeur de l'element a supprimer
  free(file->tete); //on libere l'espace memoire
  file->tete=tmp;//on met a jour la tete  
  return 0; //succes
}
//quand on retourne des valeur -1 echec et 0 succes on met int en type de fonction, sinon void fera l'affaire /

void afficherFile(File *file){
  if(file == NULL){
    printf("la file n'existe pas.\n");
  }
  if(file->tete || file->fin ==NULL){
    printf("la file est vide.\n");
  }
  else{
    afficherListe(file->tete);
  }
}

/*grignon's version 
void displayQueue(Queue* qu){
    if(qu == NULL){
        exit(13);
    }
    printf("Queue size = %d\n", qu->size);
    displayList(qu->pHead);
}*/
int createClient(){
    return randint(1,50); // Un client a entre 1 et 50 articles
}

int main(){
  srand(time(NULL));
  File *file = createFile();

  //ajouter 3 client initiaux dans la file

  for(int i=0; i<3; i++){
    enfiler(&file,createClient());
  }
  int client_paye; // Variable pour stocker le client qui paye
  int ret_var // Variable pour stocker le retour de defiler
  afficheFile(&file);

  while(file->tete !=NULL && file->fin !=NULL){
        ret_var = defiler(&file, &client_paye);
        if(ret_var){
          return 1;//sors en cas d'erreur
        }
    
        if(randint(1,3)==1){
          for(int i=0; i<randint(1,3); i++){
            enfiler(&file, createClient());
          }
        }
      //afficher le client qui passe en caisse
      printf("%d passe en caisse\n", client_paye);
      afficheFile(&file);
  }
  return 0;
}



    return 0;
}


