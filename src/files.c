//
// Created by danny on 26/10/19.
//

#include "files.h"


Circuit circuit;
F1_Car car_array[20];

/** la fonction get_resources_file récupérer les fichiers dans le dossier src/resources un fichier
 *
*@param char file_name nom du fichier qui se trouve dans le dossier resources.
 */

char *get_resources_file(char *file_name) {

    /*** static array in the function, to avoid lose of the array when the function ends ***/
    static char resource_files[20];
    strcpy(resource_files, "src/resources/");
    strcat(resource_files, file_name);
    return resource_files;

}

void save_ranking() {

    char rsrc_file[20];
    strcpy(rsrc_file, get_resources_file(circuit.step_name));

    FILE *file = fopen(rsrc_file, "w");

    if (file == NULL) perror("fopen failed !"), exit(EXIT_FAILURE);

    for (int i = 0; i < circuit.number_of_cars; i++) {
        char best_lap_str[10];
        to_string(car_array[i].best_lap_time, best_lap_str);
        fprintf(file, "%d --> %s\n", car_array[i].id, best_lap_str);
    }

    if (fclose(file) != 0) perror("fclose failed !"), exit(EXIT_FAILURE);
}

/** la fonction read_files lit un fichier passé en paramètre pour stocker les qualifiés et
*	les élimninés dans les tableaux passé en paramètre également.

*@param int qualified_cars[] un tableau pour stocker les voiutures qualifiés
*@param int race_ranking[] un tableau pour stocker les voiutures en fonction du classement de dimanche
*@param int last_cars_of_Q1[] un tableau pour stocker les élimninés de Q1
*@param int last_cars_of_Q2[] un tableau pour stocker les élimninés de Q2
*@param char file_to_read[] le fichier à lire.
*@param int lines_to_read le nombre de lignes à lire dans ce fichier passé en paramètre.

*/

void
read_files(int qualified_cars[], int race_ranking[], int last_cars_of_Q1[], int last_cars_of_Q2[], char file_to_read[],
           int lines_to_read) {

    int file_size = find_size(file_to_read);
    char absolute_path[file_size];
    getcwd(absolute_path, file_size);

    char rsrc_file[20];
    strcpy(rsrc_file, get_resources_file(file_to_read));

    char full_absolute_path[file_size];
    sprintf(full_absolute_path, "%s/%s", absolute_path, rsrc_file);

    FILE *cmd;
    char result[NUMBER_OF_CARS];
    char grep_file_result[file_size];
    sprintf(grep_file_result, "egrep -o '^[0-9]{1,2}' '%s'", full_absolute_path);

    cmd = popen(grep_file_result, "r");
    if (cmd == NULL) perror("popen failed !"), exit(EXIT_FAILURE);

    int i = 0, j = 0, k = 0;
    while (fgets(result, sizeof(result), cmd)) {

        if (i < lines_to_read) {
            qualified_cars[i] = atoi(result);
            if (strcmp(file_to_read, "Q3") == 0) {
                race_ranking[i] = atoi(result);
            }
            i++;
        } else {
            if (strcmp(file_to_read, "Q1") == 0) {
                last_cars_of_Q1[j] = atoi(result);
                j++;
            } else if (strcmp(file_to_read, "Q2") == 0) {
                last_cars_of_Q2[k] = atoi(result);
                k++;
            }
        }
    }

    if (pclose(cmd) != 0) perror("pclose failed !"), exit(EXIT_FAILURE);
}

/** la fonction find_size calcule la taille du fichier passé en paramètre

*@param char *file_name le fichier à lire.
*@return int size qui est la taille du fichier.
*/

int find_size(char *file_name) {

    char rsrc_file[20];
    strcpy(rsrc_file, get_resources_file(file_name));

    FILE *file = fopen(rsrc_file, "r");

    if (file == NULL) {
        printf("%s '%s' %s", "File previous to", circuit.step_name, "NOT found !\n"), exit(EXIT_FAILURE);
    }

    fseek(file, 0L, SEEK_END);

    int size = ftell(file);
    if (fclose(file) != 0) perror("fclose failed !"), exit(EXIT_FAILURE);
    return size;
}

/** la fonction save_eliminated_cars sauvegarde les voitures élimninés dans un fichier.

*@param char file_to_save[] le fichier qui va contenir les voitures éliminés.
*@param int array[] le tableau qui contient les voitures éliminés.
*/

void save_eliminated_cars(char file_to_save[], int array[]) {

    char rsrc_file[20];
    strcpy(rsrc_file, get_resources_file(file_to_save));

    FILE *file = fopen(rsrc_file, "w");

    if (file == NULL)
        perror("fopen failed !"), exit(EXIT_FAILURE);

    for (int i = 0; i < 5; i++) {
        fprintf(file, "%d\n", array[i]);
    }

    if (fclose(file) != 0)
        perror("fclose failed !"), exit(EXIT_FAILURE);
}

/** la fonction read_eliminated_cars lit les voitures élimninés depuis un fichier
 *  vers un tableau qui va contenir le classement de la course de dimanche.

*@param char file_to_read[] le fichier à lire qui contient les éliminés
*@param int array[] le tableau qui contient le classmeent de la course de dimanche.
*/

void read_eliminated_cars(char file_to_read[], int array[]) {

    char results[5];

    char rsrc_file[20];
    strcpy(rsrc_file, get_resources_file(file_to_read));

    FILE *file = fopen(rsrc_file, "r");

    if (file == NULL) perror("fopen failed !"), exit(EXIT_FAILURE);

    int i = 15, j = 10;
    while (fgets(results, sizeof(results), file)) {

        if (strcmp(file_to_read, "lastQ1") == 0) {
            array[i] = atoi(results);
            i++;
        }

        if (strcmp(file_to_read, "lastQ2") == 0) {
            array[j] = atoi(results);
            j++;
        }
    }

    if (fclose(file) != 0)
        perror("fclose failed !"), exit(EXIT_FAILURE);
}


/** la fonction read_resources_files permet de lire les fichiers dans le dossier src/resources un fichier
 *
*@param char file_name nom du fichier qui se trouve dans le dossier resources.
 */

void read_resources_files(char *file_name) {

    int file_size = find_size(file_name);

    FILE *file;

    char result[file_size];

    char rsrc_file[20];
    strcpy(rsrc_file, get_resources_file(file_name));

    file = fopen(rsrc_file, "r");

    if (file == NULL)
        perror("fopen failed !"), exit(EXIT_FAILURE);

    while (fgets(result, sizeof(result), file)) {

        printf("%s", result);
    }
}