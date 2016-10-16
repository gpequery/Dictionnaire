// les fonctions
#include <dirent.h>

int getLesDicos();    //Retourne le nombre de dico & les affiches;
void ajouterDico(char*);
void supprimerDico(char*);
char* getNomDico(int);

int getLesDicos() {
    DIR* dossier = opendir("LesDictionnaires");
    struct dirent* fichier = NULL;
    int count = 0;

    char* nom;

    if ( dossier != NULL ) {
        while ( fichier = readdir(dossier) ) {
            if ( (strcmp(fichier->d_name, ".") != 0) && (strcmp(fichier->d_name, "..") != 0) ) {
                nom = fichier->d_name;
                nom[strlen(nom)-4] = '\0';
                count++;
                printf("%d. %s\n", count, nom);
            }
        }
        closedir(dossier);
    }

    printf("\n");
    printf("%d. Nouveau\n", count+1, fichier->d_name);
    printf("%d. Supprimer\n", count+2, fichier->d_name);
    printf("%d. Quitter\n\n", count+3, fichier->d_name);
    return count;
}

void ajouterDico(char* input) {
    char newFile[50] = "LesDictionnaires/";

    strcat(newFile, input);
    strcat(newFile, ".txt");

    FILE* f = fopen(newFile, "w");
    fclose(f);
}

void supprimerDico(char* input) {
    char file[50] = "LesDictionnaires/";

    strcat(file, input);
    strcat(file, ".txt");

    remove(file);
}

char* getNomDico(int numDico)  {
    char* nomDico ;


    DIR* dossier = opendir("LesDictionnaires");
    struct dirent* fichier = NULL;
    int count = 1;

    char* nom;

    if ( dossier != NULL ) {
        while ( fichier = readdir(dossier) ) {
            if ( (strcmp(fichier->d_name, ".") != 0) && (strcmp(fichier->d_name, "..") != 0) ) {
                if ( count == numDico ) {
                    nom = fichier->d_name;
                    nom[strlen(nom)-4] = '\0';
                    break;
                }
                count ++;
            }
        }
        closedir(dossier);
    }

    //printf("nomDico : %s\n\n", nom);

    return nom;
}
