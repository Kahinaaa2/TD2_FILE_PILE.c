Exercice 4 (Vérification du parenthésage)
La plupart des traitements de texte ou de calculs sont capables d’analyser la syntaxe et d’indiquer un problème de
parenthésage.
Pour vérifier qu’un texte/une expression contient des parenthèses correctes, il ne suffit pas que le nombre de parenthèses
ouvrantes soit le même que le nombre de parenthèses fermantes : l’ordre dans lequel on rencontre les parenthèses fermantes
doit correspondre à l’ordre dans lequel on a rencontré les parenthèses ouvrantes.
Exemple : "Je suis Luffy )le futur roi des pirates( !" a un mauvais parenthésage bien qu’il y ait une parenthèse ouvrante
et fermante.
1. Quelle structure (tableau, liste chaînée, pile, file) est la plus adaptée pour vérifier le parenthésage d’une phrase ?
2. Déclarer ce type de structure qui contiendra des caractères.
3. Ecrire un programme permettant de vérifier le bon parenthèsage d’une chaîne de caractères. Vérifier votre algorithme
en saisissant une formule mathématique.
4. Faire de même pour des phrases pouvant contenir deux types de symboles : les parenthèses "()" et les crochets "[]".
Les règles sont les suivantes :
https ://fr.overleaf.com/project/62fbe2c4b75d7e9e42e3c150comme précédement, les symboles fermants doivent correspondre à l’ordre dans lequel on a rencontré les symboles ouvrants. le type (parenthèse ou crochet) d’un symbole
fermant doit toujours correspondre au type du dernier symbole ouvrant rencontré (et non encore fermé).
Exemple :
"a(b[c()e]f)g" est bien parenthésé.
"a(b[c)d]e" ne l’est pas.

  Correction 1 : Kahina 

#include<stdio.h>
#include<stdlib.h>

typedef struct chainon{
  char valeur;
  struct chainon *suivant;
}Chainon;

typedef struct pile{
  chainon *tete;
  int taille;
}Pile;

Chainon *createChainon(char c){
  Chainon *new = malloc(sizeof(Chainon));
  if(new==NULL){
    printf("error malloc");
    exit(1);
  }
  new->mot = c;
  new->valeur = NULL;
  return new;
}

Chainon *insertDebut(Chainon *tete, char c){
  if(tete==NULL){
    tete=createChainon(c);
  }
  else{
    Chainon *new = createChainon(c);
    if(new==NULL){
      printf("error malloc");
      exit(2);
    }
    new->suivant =tete;
    tete=new;
  }
  retrun tete;
}

Chainon *insertFin(Chainon *tete, char c){
  if(tete==NULL){
    tete=createChainon(c);
  }
  else{
    Chainon *new = createChainon(c);
    if(new==NULL){
      printf("error malloc");
      exit(3);
    }
    Chainon *tmp = tete;
    while(tmp->suivant!=NULL){
      tmp=tmp->suivant;
    }
    tmp->suivant=new;
  }
  return tete;
}

Chainon afficherListe (Chainon *liste){
  if(liste==NULL){
    printf("la liste est vide.\n");
  }
  else{
    while(liste!=NULL){
      printf("%c", liste->valeur);
      if(liste->suivant!=NULL){
        printf("->");
      }
      liste = liste->suivant;
    }
    printf("\n");
  }
}

Pile createPile(){
  Pile *pile = malloc(sizeof(Pile));
  if(pile==NULL){
    printf("error malloc");
    exit(4);
  }
  pile->tete=NULL; //initialisation de la tete de pile
  return pile;
}

void empiler(Pile *pile, char c){
  Pile*new=createPile(c);
  if(pile==NULL){
    exit(5);
  }
  pile->tete = insertDebut(pile->tete, c);
  return pile;
}

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

void afficherPile(Pile *pile){
  affiherListe(pile->tete);// Affiche les éléments de la pile en utilisant afficheListe
}

char inverserParenthesage(char a){
  switch(a){
    case '(':
      return ')';
    case ')':
      return '(';
    case'[':
      return ']';

    default: 
      return 0; //retourner 0 si aucun ne match
  }
}

int parenthesage(char *nb){
  if(nb == NULL){
    exit(12);
  }

  Pile*pile=createPile(); //creer une pile pour stocker les char ouvrants
  int taille = strlen(nb);//taille de la chaine
  char depile;

  //on parcours chaque caractere de la chaine
  for(int i=0; i<taille; i++){
    switch(str[i]){
      //si on rencontre une parenthese, un crochet ou une accolade ouvrante
      case '(':
      case '[':
      case '{':
        empiler(pile, str[i]);//on empile l'element
      break;

      // Si on rencontre une parenthèse, un crochet ou une accolade fermante
      case ')':
      case ']':
      case '}':
        depiler(ppile, &depile_var);// Dépile un caractère ouvrant
      if (str[i] != inverse_parenthesage(depile_var)) {   
        printf("%s faux \n", str); // Si le caractère fermant ne correspond pas, affiche "faux"
        return 0; // Retourne 0 pour indiquer que la chaîne est mal parenthésée
      }
      break;
      // Ignore les autres caractères
      default:
          break;
    }
  }
  
}

int main() {
    // Test des chaînes avec différentes combinaisons de parenthèses, crochets et accolades
    char c1[] = "Je suis Luffy )le futur roi des pirates( !";
    parenthesage(c1);

    char c2[] = "a(b[c()e]f)g";
    parenthesage(c2);

    char c3[] = "a(b[c)d]e";
    parenthesage(c3);

    char c4[] = "dfg.dfgg.gfggg( cy.deltahmed.fr/egg/hehe.gif )sd.gwdf.gdd";
    parenthesage(c4);

    char c5[] = "x(1+2)([2+5]*3)";
    parenthesage(c5);

    return 0; // Fin du programme
}




  Correction 2 : Romuald Grignon MI2


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
        printf("%c ", p->c);
        p = p->pNext;
    }
    printf("\n");
}

typedef struct{
    Node* pHead;
    int size;    
} Stack;

Stack* createStack(){
    Stack* st = malloc(sizeof(Stack));
    if(st == NULL){
        exit(10);
    }
    st->size  = 0;
    st->pHead = NULL;
    return st;
}

void push(Stack* st, char c){
    if(st == NULL){
        exit(11);
    }
    st->pHead = addStart(st->pHead, c);
    st->size++;
}

void pop(Stack* st, char* pC){
    if(st == NULL || pC == NULL || st->size <= 0){
        exit(12);
    }
    st->pHead = removeStart(st->pHead, pC); 
    st->size--;    
}

void displayStack(Stack* st){
    if(st == NULL){
        exit(13);
    }
    printf("Stack size = %d\n", st->size);
    displayList(st->pHead);
}

int getSize(Stack* st){
    if(st == NULL){
        exit(14);
    }
    return st->size;
}



int main(){

    Stack* st = createStack(); 
    char c=0;
    
    if(st == NULL){
        exit(20);
    }   

    char str[256] = "{(jbjjkn[)kjnkjn] kjnkn { ljnl  }   (  ) )}";

    int str_OK = 1;

    char* p = str;
    while(*p != '\0' && str_OK==1){
        switch(*p){
            case '(':
            case '{':
            case '[':
                push(st, *p);            
                displayStack(st);
                printf("\n");
                break;
            
            case ')':
            case ']':
            case '}':
                if(getSize(st) <= 0){
                    str_OK = 0;
                    break;
                }        
                pop(st, &c);
                printf("popped %c \n", c);
                displayStack(st);
                // c  contains closing character
                // *p contains opening character
                if((*p==')' && c!='(') || (*p==']' && c!='[') || (*p=='}' && c!='{')){
                    str_OK = 0;
                }
                break;
            default:
                break;                
        }
        p++;
    }
    
    if(str_OK){
        printf("OK\n");
    }    
    else{
        printf("FAILURE !!\n");
    }    
    return 0;
}

