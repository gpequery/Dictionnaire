#include <dirent.h>

int getLesDicos();          //Retourne le nombre de dico & les affiches;
int getLesFichiers(int);    //Retourne le nombre de fichier & les affiches (int:le nombre de dico)
void ajouterDico(char*);    //(char* nomNewDico sans le .txt)
void supprimerDico(char*);  //(char* delDico sans le .txt)
char* getNomDico(int);      //Retourne le nom du dico sans le .txt (int:numDico)
short existFichier(char*);    //Boolean : exist ? (char* nomCherché sans .txt)
short existDico(char*);       //Boolean : exist ? (char* nomCherché sans .txt)
void ajouterDicoFile(char*, char*);     //(char* nom fichier existant, char* nom du dico qui seras creer)
char* finalyWord(char*);                // Retourne le mot sans caractère speciale  Malloc !!
short wordInDico(char*, char*);         //Boolean : moot dans dico ? (char* nom dico, char* mot a chercher)

int getLesDicos() {
    DIR* directory = opendir("LesDictionnaires");
    struct dirent* file = NULL;
    int count = 0;

    char* name;
    printf("Les dictionnaires disponible: \n\n");
    if ( directory != NULL ) {
        while ( file = readdir(directory) ) {
            if ( (strcmp(file->d_name, ".") != 0) && (strcmp(file->d_name, "..") != 0) ) {
                name = file->d_name;
                name[strlen(name)-4] = '\0';
                count++;
                printf("%d. %s\n", count, name);
            }
        }
        closedir(directory);
    }
    return count;
}

int getLesFichiers(int countDico) {
    DIR* dossier = opendir("LesFichiers");
    struct dirent* fichier = NULL;
    int count = countDico;

    char* name;
    printf("\tLes fichiers disponible: \n");
    if ( dossier != NULL ) {
        while ( fichier = readdir(dossier) ) {
            if ( (strcmp(fichier->d_name, ".") != 0) && (strcmp(fichier->d_name, "..") != 0) ) {
                name = fichier->d_name;
                name[strlen(name)-4] = '\0';
                count++;
                printf("\t\t- %s\n", name);
            }
        }
        closedir(dossier);
    }
    printf("\n");
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

    int test = remove(file);
    printf("\nFile : %s | %d\n\n", file, test);
}

char* getNomDico(int numDico)  {
    DIR* directory = opendir("LesDictionnaires");
    struct dirent* file = NULL;
    int count = 1;

    char* name;

    if ( directory != NULL ) {
        while ( file = readdir(directory) ) {
            if ( (strcmp(file->d_name, ".") != 0) && (strcmp(file->d_name, "..") != 0) ) {
                if ( count == numDico ) {
                    name = file->d_name;
                    name[strlen(name)-4] = '\0';
                    break;
                }
                count ++;
            }
        }
        closedir(directory);
    }
    return name;
}

short existFichier(char* name)  {
    short result = 0 ;
    strcat(name, ".txt");

    DIR* directory = opendir("LesFichiers");
    struct dirent* fichier = NULL;

    if ( directory != NULL ) {
        while ( fichier = readdir(directory) ) {
            if ( strcmp(fichier->d_name, name) == 0 ) {
                result = 1 ;
            }
        }
        closedir(directory);
    }
    return result;
}

short existDico(char* name) {
    short result = 0 ;
    strcat(name, ".txt");

    DIR* directory = opendir("LesDictionnaires");
    struct dirent* fichier = NULL;

    if ( directory != NULL ) {
        while ( fichier = readdir(directory) ) {
            if ( strcmp(fichier->d_name, name) == 0 ) {
                result = 1 ;
            }
        }
        closedir(directory);
    }
    return result;
}

void ajouterDicoFile(char* oldName, char* newName) {
    char directoryDico[50] = "LesDictionnaires/";
    char directoryFile[50] = "LesFichiers/";

    strcat(directoryDico, newName);
    strcat(directoryFile, oldName);

    FILE* file = fopen(directoryFile, "r");

    if (file) {
        char word[50];
        char* safeWord;

        while(!feof(file)) {
            fscanf(file, "%s", &word);

            safeWord = finalyWord(word);
            if ( ! wordInDico(directoryDico, safeWord) ) {
                FILE* dico = fopen(directoryDico, "a");
                if (dico) {
                    fprintf(dico, "%s\n", safeWord);
                    fclose(dico);
                }
            }
        }
        free(safeWord);
        fclose(file);
    }
}

char* finalyWord(char* word) {
    char* result = malloc(sizeof(char)*50);
    int j = 0;
    int i;

    for (i = 0; i < strlen(word); i ++ ) {
        if ( (word[i] > 64 && word[i] < 91) || (word[i] > 96 && word[i] < 123) || (word[i] > -65 && word[i] < -48) || (word[i] > -48 && word[i] < -41) || (word[i] > -40 && word[i] < -34) || (word[i] > -33 && word[i] < -16) || (word[i] > -16 && word[i] < -9) || (word[i] > -8 && word[i] < -2) ) {
            result[j] = tolower(word[i]);
            j ++;
        }
    }
    result[j] = '\0';

    return result;
}

short wordInDico(char* directoryDico, char* word) {
    int in = 0;

    if (strcmp(word, "") == 0) {
        return 1;
    } else {
        FILE* dico = fopen(directoryDico, "r");
        if (dico) {

            char compare[50];
            while(!feof(dico)) {
                fscanf(dico, "%s", compare);
                if ( strcmp(word, compare) == 0) {
                    return 1;
                }
            }
            fclose(dico);
        }
    }
    return in;
}

short addWord(char* pathDico, char* word) {
    short result = 0;
    printf("\nDico : %s  |  Mot : %s\n", pathDico, tolower(word));

    return result;
}
