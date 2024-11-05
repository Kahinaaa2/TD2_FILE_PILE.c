#include <stdio.h>
#include <stdlib.h>

// Structure de chaque groupe dans la file
typedef struct Chainon {
    int groupe;                // Nombre de personnes dans le groupe
    struct Chainon* suivant;   // Pointeur vers le prochain groupe
} Chainon;

// Structure pour gérer la file
typedef struct {
    Chainon* tete;             // Début de la file
    Chainon* fin;              // Fin de la file
    int personneTot;           // Nombre total de personnes dans la file
} File;

// Fonction pour créer un nouveau chaînon (groupe)
Chainon* createChainon(int v) {
    Chainon* p = malloc(sizeof(Chainon));
    if (p == NULL) {
        exit(1);
    }
    p->groupe = v;
    p->suivant = NULL;
    return p;
}

// Fonction pour ajouter un groupe dans la file
void entrerFile(File* file) {
    if (file == NULL) {
        exit(2);
    }
    int groupe = rand() % 9 + 2;  // Taille du groupe aléatoire entre 2 et 10

    // Vérification de la capacité maximale
    if (file->personneTot + groupe > 500) {
        printf("La capacité de l'attraction est atteinte\n");
        return;
    }

    // Création du nouveau groupe
    Chainon* nouveau = createChainon(groupe);

    // Ajout du groupe à la fin de la file
    if (file->fin == NULL) {
        file->tete = nouveau;  // Si la file est vide, tête et fin pointent sur le même chaînon
    } else {
        file->fin->suivant = nouveau;
    }

    file->fin = nouveau;  // Mise à jour de la fin de la file
    file->personneTot += groupe;
    printf("Un groupe de %d personnes a entré dans l'attraction\n", groupe);
}

// Fonction pour retirer un groupe de la file
int sortirFile(File* file, int* grp) {
    if (file == NULL || file->tete == NULL) {
        return 0;  // File vide
    }

    *grp = file->tete->groupe;  // Taille du groupe en tête
    Chainon* temp = file->tete;  // Sauvegarde de la tête actuelle
    file->tete = file->tete->suivant;

    if (file->tete == NULL) {
        file->fin = NULL;  // Si la file est vide après le retrait, mettre la fin à NULL
    }

    file->personneTot -= *grp;  // Mise à jour du total
    free(temp);  // Libération de l'ancien chaînon
    return 1;
}

// Fonction pour vérifier si la file est pleine
int filePleine(File* file) {
    return file->personneTot >= 500;
}

// Fonction pour remplir le train avec les groupes dans la file
void remplirTrain(File* file) {
    int placesTot = 8 * 4;  // Nombre total de places (8 rangées de 4 places)
    int placesPrises = 0;
    int groupe;

    while (placesPrises < placesTot && sortirFile(file, &groupe)) {
        int rangeNec;

        // Détermination du nombre de rangées nécessaires pour le groupe
        if (groupe <= 4) {
            rangeNec = 1;
        } else if (groupe <= 8) {
            rangeNec = 2;
        } else {
            rangeNec = 3;
        }

        if (placesPrises + rangeNec * 4 <= placesTot) {
            placesPrises += rangeNec * 4;
            printf("Le groupe de %d personnes a embarqué.\n", groupe);
        } else {
            printf("Pas assez de place pour le groupe de %d personnes.\n", groupe);
            break;
        }
    }

    int placesLibres = placesTot - placesPrises;
    printf("Le train part avec %d places libres.\n", placesLibres);
}

// Fonction pour simuler 3 minutes d'activité
void three_minutes(File* pFile) {
    // Simuler 2 trains
    for (int i = 0; i < 2; i++) {
        printf("Train %d en départ:\n", i + 1);
        remplirTrain(pFile);
    }

    // Simuler l'entrée de 16 groupes
    for (int i = 0; i < 16; i++) {
        if (!filePleine(pFile)) {
            entrerFile(pFile);
        } else {
            printf("La file est pleine. Aucun autre groupe ne peut entrer.\n");
            break;
        }
    }
}

int main() {
    srand(time(NULL));  // Initialisation du générateur de nombres aléatoires
    File file = {NULL, NULL, 0};  // Initialisation de la file

    // Simulation de 3 minutes
    three_minutes(&file);

    return 0;
}
