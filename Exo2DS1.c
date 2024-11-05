#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Définition de la structure d'un chainon pour le deque
typedef struct Chainon {
    char* url;                   // URL allouée dynamiquement
    struct Chainon* suivant;     // Pointeur vers le chainon suivant
    struct Chainon* precedent;   // Pointeur vers le chainon précédent
} Chainon;

// Définition de la structure Deque
typedef struct {
    Chainon* premier;            // Premier élément du deque
    Chainon* dernier;            // Dernier élément du deque
    int taille;                  // Taille actuelle du deque
} Deque;

// Création d'un chainon avec l'URL donnée (simulé ici)
Chainon* creerChainon(const char* url) {
    Chainon* nouveau = (Chainon*)malloc(sizeof(Chainon));
    if (nouveau == NULL) {
        exit(1); // En cas d'échec d'allocation, on arrête le programme
    }
    nouveau->url = strdup(url); // Allouer dynamiquement et copier l'URL
    nouveau->suivant = NULL;
    nouveau->precedent = NULL;
    return nouveau;
}

// Suppression d'un chainon (simulé ici)
void supprimerChainon(Chainon* chainon) {
    if (chainon) {
        free(chainon->url); // Libérer l'URL allouée dynamiquement
        free(chainon);      // Libérer le chainon lui-même
    }
}

// 3. Ajout d'un chainon en début de Deque
void ajoutDebutDeque(Deque* deque, const char* url) {
    Chainon* nouveau = creerChainon(url);
    nouveau->suivant = deque->premier;

    if (deque->premier != NULL) {
        deque->premier->precedent = nouveau;
    } else {
        deque->dernier = nouveau; // Si deque vide, dernier devient le nouveau chainon
    }

    deque->premier = nouveau;
    deque->taille++;
}

// 4. Suppression du dernier élément du Deque
void supprimerFinDeque(Deque* deque) {
    if (deque->dernier == NULL) {
        return; // Rien à supprimer si deque vide
    }

    Chainon* aSupprimer = deque->dernier;
    deque->dernier = deque->dernier->precedent;

    if (deque->dernier != NULL) {
        deque->dernier->suivant = NULL;
    } else {
        deque->premier = NULL; // Si dernier élément supprimé, premier devient NULL
    }

    supprimerChainon(aSupprimer);
    deque->taille--;
}

// 5. Ajout d'une adresse dans l'historique (en début) avec limite de taille
void ajoutHistorique(Deque* deque, const char* url) {
    ajoutDebutDeque(deque, url); // Ajouter l'URL en début

    if (deque->taille > 10) {
        supprimerFinDeque(deque); // Supprimer l'ancien élément si la taille dépasse 10
    }
}

// 6. Récupération de l'URL précédente
char* precedent(Deque* deque) {
    if (deque->premier == NULL || deque->premier->suivant == NULL) {
        return NULL; // Si pas de précédent, retourner NULL
    }

    return deque->premier->suivant->url; // Retourner l'URL de la page précédente
}

int main() {
    Deque historique = {NULL, NULL, 0}; // Initialisation de l'historique

    // Ajout de quelques sites dans l'historique pour tester
    ajoutHistorique(&historique, "https://example1.com");
    ajoutHistorique(&historique, "https://example2.com");
    ajoutHistorique(&historique, "https://example3.com");

    // Affichage de la page précédente
    char* urlPrecedente = precedent(&historique);
    if (urlPrecedente) {
        printf("Page précédente: %s\n", urlPrecedente);
    } else {
        printf("Pas de page précédente.\n");
    }

    // Suppression des éléments pour éviter les fuites de mémoire
    while (historique.taille > 0) {
        supprimerFinDeque(&historique);
    }

    return 0;
}
