#include <dirent.h>

#define color(param) printf("\033[%sm",param)

int my_strlen(char* word);
int my_strcmp(char*, char*);
char my_cTolower(char c);
char* my_tolower(char* word); // Malloc !
char* my_strcat(char*, char*); // Malloc !
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

int my_strlen(char* word) {
    int count = 0;

    while ( word[count] != '\0' ) {
        count ++;
    }

    return count;
}

int my_strcmp(char* wordA, char* wordB) {
    int count = 0;
    int i = 0;
    int nbLettreA = my_strlen(wordA);
    int nbLettreB = my_strlen(wordB);
    int diff = nbLettreB - nbLettreA;

    while (wordA[i] != '\0') {
        if (wordA[i] != wordB[i] ) {
            count ++;
        }
        i++;
    }

    if (diff > 0 ) {
        count += diff;
    }

    return count;
}

char my_cTolower(char c) {
    char lower;
    int i;

    if (c >= 65 && c <= 90) {
        lower = c + 32;
    } else {
        lower = c;
    }


    return lower;
}

char* my_tolower(char* word) {
    char* lower = malloc(sizeof(char)*(my_strlen(word)+1));
    int i;

    for (i=0; i< my_strlen(word); i++) {
        if (word[i] >= 65 && word[i] <= 90) {
            lower[i] = word[i] + 32;
        } else {
            lower[i] = word[i];
        }
    }
    lower[i] = '\0';

    return lower;
}

char* my_strcat(char* wordA, char* wordB) {
    int lenthA = my_strlen(wordA);
    int lenthB = my_strlen(wordB);
    char* result = malloc(sizeof(char) * (lenthA + lenthB + 1));

    int a = 0;
    int b = 0;
    int i;

    for (i = 0; i < lenthA + lenthB; i ++) {
            if (a < lenthA) {
                result[i] = wordA[a];
                a++;
            } else {
                result[i] = wordB[b];
                b++;
            }
    }
    result[i] = '\0';

    return result;
}

int getLesDicos() {
    DIR* directory = opendir("LesDictionnaires");
    struct dirent* file = NULL;
    int count = 0;

    char* name;
    printf("Les dictionnaires disponible: \n\n");
    color("33");
    if ( directory != NULL ) {
        while ( file = readdir(directory) ) {
            if ( (my_strcmp(file->d_name, ".") != 0) && (my_strcmp(file->d_name, "..") != 0) ) {
                name = file->d_name;
                name[my_strlen(name)-4] = '\0';
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
    color("33");
    if ( dossier != NULL ) {
        while ( fichier = readdir(dossier) ) {
            if ( (my_strcmp(fichier->d_name, ".") != 0) && (my_strcmp(fichier->d_name, "..") != 0) ) {
                name = fichier->d_name;
                name[my_strlen(name)-4] = '\0';
                count++;
                printf("\t\t- %s\n", name);
            }
        }
        closedir(dossier);
    }
    printf("\n");
    color("33");
    return count;
}

void ajouterDico(char* input) {
    char path[50] = "LesDictionnaires/";

    char* newFile;
    newFile = my_strcat(path, input);
    newFile = my_strcat(newFile, ".txt");

    FILE* f = fopen(newFile, "w");
    fclose(f);
    free(newFile);
}

void supprimerDico(char* input) {
    char path[50] = "LesDictionnaires/";

    char* file;
    file = my_strcat(path, input);
    file = my_strcat(file, ".txt");

    remove(file);
    free(file);
}

char* getNomDico(int numDico)  {
    DIR* directory = opendir("LesDictionnaires");
    struct dirent* file = NULL;
    int count = 1;

    char* name;

    if ( directory != NULL ) {
        while ( file = readdir(directory) ) {
            if ( (my_strcmp(file->d_name, ".") != 0) && (my_strcmp(file->d_name, "..") != 0) ) {
                if ( count == numDico ) {
                    name = file->d_name;
                    name[my_strlen(name)-4] = '\0';
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
            if ( my_strcmp(fichier->d_name, name) == 0 ) {
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
            if ( my_strcmp(fichier->d_name, name) == 0 ) {
                result = 1 ;
            }
        }
        closedir(directory);
    }
    return result;
}

void ajouterDicoFile(char* oldName, char* newName) {
    char pathDico[50] = "LesDictionnaires/";
    char pathFile[50] = "LesFichiers/";

    char* directoryDico;
    char* directoryFile;
    directoryDico = my_strcat(pathDico, newName);
    directoryFile = my_strcat(pathFile, oldName);

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
    free(directoryDico);
    free(directoryFile);
}

char* finalyWord(char* word) {
    char* result = malloc(sizeof(char)*50);

    int j = 0;
    int i;

    for (i = 0; i < my_strlen(word); i ++ ) {
        if ( (word[i] > 64 && word[i] < 91) || (word[i] > 96 && word[i] < 123) || (word[i] > -65 && word[i] < -48) || (word[i] > -48 && word[i] < -41) || (word[i] > -40 && word[i] < -34) || (word[i] > -33 && word[i] < -16) || (word[i] > -16 && word[i] < -9) || (word[i] > -8 && word[i] < -2) ) {

            result[j] = my_cTolower(word[i]);
            j ++;
        }
    }
    result[j] = '\0';

    return result;
}

short wordInDico(char* directoryDico, char* word) {
    int in = 0;

    if (my_strcmp(word, "") == 0) {
        return 1;
    } else {
        FILE* dico = fopen(directoryDico, "r");
        if (dico) {

            char compare[50];
            while(!feof(dico)) {
                fscanf(dico, "%s", compare);
                if ( my_strcmp(word, compare) == 0) {
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
    printf("\nDico : %s  |  Mot : %s\n", pathDico, my_tolower(word)); //free !!

    return result;
}
