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

  Correction Romuale Grignon MI2


4 sur 2 502
Document de Kahinaaaaaa
Boîte de réception

kahina Hammad <hammadkahina5@gmail.com>
Pièces jointes
mer. 30 oct. 09:47 (il y a 2 jours)
À moi

 1 pièce jointe
  • Analyse effectuée par Gmail
margot.rouille@cyje.fr. Appuyez sur Tabulation pour insérer.
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

