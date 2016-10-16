#include <stdio.h>
#include <stdlib.h>

#include "functions.h"

void clearConsole(char*);
void accueil();
void menu(int);


int main() {
    accueil();
    return 0;
}

void clearConsole(char* dico) {
    system("cls");
    printf("Dictionnaire %s\n", dico);
    printf("--------------");

    int size = strlen(dico);
    int i;
    for ( i = 0; i < size; i ++ ) {
        printf("-");
    }
    printf("\n\n\n");
}

void accueil() {
    clearConsole("accueil");
    printf("Les dictionnaires disponible: \n\n");

    int nbDico = getLesDicos();
    int action;

    printf("Selectionner un dictionnaire: ");
    scanf("%d", &action);

    if (action == nbDico + 1 ) {
        char name[30];

        printf("\nNom du nouveau dictionnaire: ");
        scanf("%s", &name);

        ajouterDico(name);
        accueil();
    } else if (action == nbDico + 2 ) {
        char name[30];

        printf("\nNom du dictionnaire a supprimer: ");
        scanf("%s", &name);

        supprimerDico(name);
        accueil();
    } else if (action == nbDico + 3 )  {
        system("exit");
    } else {
        if ( action > 0 && action <= nbDico) {
            menu(action);
        } else {
            accueil();
        }
    }
 }

void menu(int numDico) {
    char* nomDico = getNomDico(numDico);

    clearConsole(nomDico);
    printf("MENU\n\n");

 }

