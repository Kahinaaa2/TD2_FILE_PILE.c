1. Quelle structure (tableau, liste chaînée, pile, file) semble la plus appropriée pour ce type d’exercice ?
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


Correction Romuald Grignon

#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
    char          c;
    struct _node* pNext;
} Node;

Node* createNode(char c){
    Node *pNew = malloc(sizeof(Node));
    if(pNew == NULL){
        exit(1);
    } 
    pNew->c     = c;
    pNew->pNext = NULL;
    return pNew;
}

Node* addStart(Node* pHead, char c){
    Node* pNew = createNode(c);
    if(pNew == NULL){
        exit(2);
    } 
    pNew->pNext = pHead;
    pHead = pNew;
    return pHead;    
}

Node* addEnd(Node* pHead, char c){
    if(pHead == NULL){
        pHead = addStart(pHead, c);
    }
    else{
        Node* p1 = pHead;
        while(p1->pNext != NULL){
            p1 = p1->pNext;
        }
        Node* pNew = createNode(c);    
        if(pNew == NULL){
            exit(50);
        }
        p1->pNext = pNew;
    }
    return pHead;
}

Node* removeStart(Node* pHead, char* pC){
    if(pHead == NULL){
        exit(3);
    }
    Node* pRemove = pHead;
    pHead = pHead->pNext;    
    *pC = pRemove->c;    
    pRemove->pNext = NULL;
    free(pRemove);
    return pHead;
}

void displayList(Node* p){
    printf("Values : ");
    while(p != NULL){
        printf("[%02d]", p->c);
        p = p->pNext;
    }
    printf("\n");
}

typedef struct{
    Node* pHead;
    Node* pTail;
    int   size;    
} Queue;

Queue* createQueue(){
    Queue* qu = malloc(sizeof(Queue));
    if(qu == NULL){
        exit(10);
    }
    qu->size  = 0;
    qu->pHead = NULL;
    qu->pTail = NULL;
    return qu;
}

void push(Queue* qu, char c){
    if(qu == NULL){
        exit(11);
    }
    qu->pTail = addEnd(qu->pTail, c);
    if(qu->pHead == NULL){
        // very first insertion
        qu->pHead = qu->pTail;
    }
    else{
        // any other ones
        qu->pTail = qu->pTail->pNext;
    }
    qu->size++;
}

void pop(Queue* qu, char* pC){
    if(qu == NULL || pC == NULL || qu->size <= 0){
        exit(12);
    }
    qu->pHead = removeStart(qu->pHead, pC); 
    if(qu->pHead == NULL){
        // very last remove
        qu->pTail = NULL;
    }
    qu->size--;    
}

void displayQueue(Queue* qu){
    if(qu == NULL){
        exit(13);
    }
    printf("Queue size = %d\n", qu->size);
    displayList(qu->pHead);
}

int getSize(Queue* qu){
    if(qu == NULL){
        exit(14);
    }
    return qu->size;
}



int main(){

    Queue* cash1 = createQueue();

    srand(0);

    for(int i=0;i<3;i++){
        push(cash1, rand()%50 + 1);
    }    

//    displayQueue(cash1);    


    while( getSize(cash1) > 0 ){
        char customer = 0;
        // Pop oldest customer
        pop(cash1, &customer);
        printf("Customer with %d articles has left the supermarket !\n", customer);
//        displayQueue(cash1);    
        // check if new customers
        if(rand()%101 <= 50){
            int n = rand()%3 + 1;
            // random (1-3) new customers
            for(int i=0;i<n;i++){
                push(cash1, rand()%50 + 1);
            }
        } 
        displayQueue(cash1);    
    }



    return 0;
}


