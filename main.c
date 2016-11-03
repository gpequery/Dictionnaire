#include <stdio.h>
#include <stdlib.h>

#include "functions.h"

void clearConsole(char*);   //Affichage en tete (char* le titre a afficher)
void accueil();             //Gestion des dicos
void menu(int);             //Apres selection d'un dico (int: numDico)


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

    int countDico = getLesDicos();

    printf("\n");
    printf("%d. Nouveau vide\n", countDico+1);
    printf("%d. Nouveau avec fichier\n", countDico+2);
    printf("%d. Supprimer\n", countDico+3);
    printf("%d. Quitter\n\n\n", countDico+4);

    int action;

    printf("Selectionner un dictionnaire: ");
    scanf("%d", &action);

    if (action == countDico + 1 ) {                //Nouveau Dico vide
        char name[30];

        printf("Nom du nouveau dictionnaire: ");
        scanf("%s", &name);

        ajouterDico(name);
        accueil();
    } else if (action == countDico + 2 ) {         //Nouveau dico par fichier
        printf("----------------------\n\n");
        int nbFichier = getLesFichiers(countDico);

        char file[30] = "";
        int exist = 0;

        do {
            printf("\tNom du fichier texte a utiliser : ");
            scanf("%s", &file);
        } while (!(exist = existFichier(file)));

        char newName[30] = "";
        exist = 1;

        do {
            printf("\tNom du nouveau dictionnaire a creer : ");
            scanf("%s", &newName);
        } while ((exist = existDico(newName)));

        ajouterDicoFile(file, newName);
        accueil();
    } else if (action == countDico + 3 ) {         //Supprimer Dico
        char name[30];

        printf("Nom du dictionnaire a supprimer: ");
        scanf("%s", &name);

        supprimerDico(name);
        accueil();
    } else if (action == countDico + 4 )  {        //Quitter
        system("exit");
    } else {
        if ( action > 0 && action <= countDico) {  //Si sélection d'un dico existant (go menu)
            menu(action);
        } else {
            accueil();                          //Si sélection d'un int non valide (retour accueil)
        }
    }
 }

void menu(int numDico) {
    char* nomDico = getNomDico(numDico);

    clearConsole(nomDico);
    printf("MENU\n\n");

 }

