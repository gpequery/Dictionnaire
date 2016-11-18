#include <stdio.h>
#include <stdlib.h>

#include "gestbib.c"

#define color(param) printf("\033[%sm",param)

void clearConsole(char*);   //Affichage en tete (char* le titre a afficher)
void accueil();             //Gestion des dicos
void menu(int, int, char*);             //Apres selection d'un dico (int: numDico)

enum {WORD_NOT_IN_DICO, WORD_IN_DICO, WAS_ADD, WAS_NOT_ADD};
enum {SEARCH = 1, ADD_WORD, RETOUR};

int main() {
    accueil();
    return 0;
}

void clearConsole(char* dico) {
    system("cls");
    color("35");
    printf("Dictionnaire %s\n", dico);
    printf("--------------");

    int size = my_strlen(dico);
    int i;
    for ( i = 0; i < size; i ++ ) {
        printf("-");
    }
    printf("\n\n");
    color("37");
}

void accueil() {
    clearConsole("accueil");

    int countDico = getLesDicos();
    color("36");
    printf("\n");
    printf("%d. Nouveau vide\n", countDico+1);
    printf("%d. Nouveau avec fichier\n", countDico+2);
    printf("%d. Supprimer\n", countDico+3);
    printf("%d. Quitter\n\n\n", countDico+4);

    int action;
    color("37");
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
        color("37");
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
            menu(action, -1, "");
        } else {
            accueil();                          //Si sélection d'un int non valide (retour accueil)
        }
    }
 }

void menu(int numDico, int alert, char* word) {
    int action;
    char* nomDico = getNomDico(numDico);
    char input[50];

    char* pathDico = "";

    pathDico = my_strcat(pathDico, "LesDictionnaires/");
    pathDico = my_strcat(pathDico, nomDico);
    pathDico = my_strcat(pathDico, ".txt");

    clearConsole(nomDico);

    //Message pour indiquer le résultat de l'action
    switch (alert) {
        case WORD_NOT_IN_DICO :
            color("31");
            printf("'%s' n'est pas dans le dictionnaire", word);
            break;

        case WORD_IN_DICO :
            color("32");
            printf("'%s' est dans le dictionnaire", word);
            break;

        case WAS_ADD :
            color("32");
            printf("'%s' a bien été ajouté dans le dictionnaire", word);
            break;

        case WAS_NOT_ADD :
            color("31");
            printf("'%s' est déjà dans le dictionnaire", word);
    }

    color("36");
    printf("\n\n");

    printf("1. Chercher un mot\n");
    printf("2. Ajouter un mot\n");
    printf("3. Retour \n\n");

    color("37");
    printf("Que voulez vous faire : ");
    scanf("%d", &action);

    switch (action) {
        case SEARCH :
            printf("Mot recherche : ");
            scanf("%s", input);

            if (wordInDico(pathDico, my_tolower(input))) {
                menu(numDico, WORD_IN_DICO, input);
            } else {
                menu(numDico, WORD_NOT_IN_DICO, input);
            }
            break;

        case ADD_WORD :
            printf("Mot a ajouter : ");
            scanf("%s", input);

            if (!wordInDico(pathDico, my_tolower(input))) {
                addWord(pathDico, my_tolower(input));
                menu(numDico, WAS_ADD, input);
            } else {
                menu(numDico, WAS_NOT_ADD, input);
            }
            break;

        case RETOUR :
            accueil();
            break;

        default :
            menu(numDico, alert, word);
    }








    /*if (action == SEARCH) {
        printf("Mot recherche : ");
        scanf("%s", input);

        if (wordInDico(pathDico, my_tolower(input))) {
            menu(numDico, WORD_IN_DICO, input);
        } else {
            menu(numDico, WORD_NOT_IN_DICO, input);
        }
    } else if (action == ADD_WORD) {
        printf("Mot a ajouter : ");
        scanf("%s", input);

        if (!wordInDico(pathDico, my_tolower(input))) {
            addWord(pathDico, my_tolower(input));
            menu(numDico, WAS_ADD, input);
        } else {

        }

    } else if (action == RETOUR) {
        accueil();
    } else {
        menu(numDico, alert, word);
    }*/

    free(pathDico);
}
