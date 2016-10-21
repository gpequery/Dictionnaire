// les fonctions
#include <dirent.h>

int getLesDicos();          //Retourne le nombre de dico & les affiches;
int getLesFichiers(int);    //Retourne le nombre de fichier & les affiches (int:le nombre de dico)
void ajouterDico(char*);    //(char* nomNewDico sans le .txt)
void supprimerDico(char*);  //(char* delDico sans le .txt)
char* getNomDico(int);      //Retourne le nom du dico sans le .txt (int:numDico)
int existFichier(char*);    //Boolean si exist (char* nomCherché sans .txt)
int existDico(char*);       //Boolean si exist (char* nomCherché sans .txt)
void ajouterDicoFile(char*, char*);    //(char* nom fichier existant, char* nom du dico qui seras creer)

int getLesDicos() {
    DIR* dossier = opendir("LesDictionnaires");
    struct dirent* fichier = NULL;
    int count = 0;

    char* nom;
    printf("Les dictionnaires disponible: \n\n");
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
    return count;
}

int getLesFichiers(int nbDico) {
    DIR* dossier = opendir("LesFichiers");
    struct dirent* fichier = NULL;
    int count = nbDico;

    char* nom;
    printf("\tLes fichiers disponible: \n");
    if ( dossier != NULL ) {
        while ( fichier = readdir(dossier) ) {
            if ( (strcmp(fichier->d_name, ".") != 0) && (strcmp(fichier->d_name, "..") != 0) ) {
                nom = fichier->d_name;
                nom[strlen(nom)-4] = '\0';
                count++;
                printf("\t\t- %s\n", nom);
            }
        }
        closedir(dossier);
    }
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
    char* nomDico;

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
    return nom;
}

int existFichier(char* nom)  {
    int result = 0 ;
    strcat(nom, ".txt");

    DIR* dossier = opendir("LesFichiers");
    struct dirent* fichier = NULL;

    if ( dossier != NULL ) {
        while ( fichier = readdir(dossier) ) {
            if ( strcmp(fichier->d_name, nom) == 0 ) {
                result = 1 ;
            }
        }
        closedir(dossier);
    }
    return result;
}

int existDico(char* nom) {
    int result = 0 ;
    strcat(nom, ".txt");

    DIR* dossier = opendir("LesDictionnaires");
    struct dirent* fichier = NULL;

    if ( dossier != NULL ) {
        while ( fichier = readdir(dossier) ) {
            if ( strcmp(fichier->d_name, nom) == 0 ) {
                result = 1 ;
            }
        }
        closedir(dossier);
    }
    return result;
}

void ajouterDicoFile(char* oldName, char* name) {
    printf("\n\nFILE : %s  |  DICO : %s\n\n", oldName, name);

    char newName[50] = "LesDictionnaires/";
    strcat(oldName, name);
    /*
    FILE* oldFile = fopen(oldName, "r")l
    if () {

    }*/

}

