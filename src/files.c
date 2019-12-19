//
// Created by danny on 26/10/19.
//

#include "files.h"


Circuit circuit;
F1_Car car_array[20];

void save_ranking() {

    FILE *file = fopen(circuit.step_name, "w");

    if (file == NULL) perror("fopen failed !"), exit(EXIT_FAILURE);;

    for (int i = 0; i < circuit.number_of_cars; i++) {
        char best_lap_str[10];
        to_string(car_array[i].best_lap_time, best_lap_str);
        fprintf(file, "%d --> %s\n", car_array[i].id, best_lap_str);
    }

    if (fclose(file) != 0) perror("fclose failed !"), exit(EXIT_FAILURE);;
}

void
read_files(int qualified_cars[], int race_ranking[], int last_cars_of_Q1[], int last_cars_of_Q2[], char file_to_read[],
           int lines_to_read) {

    int file_size = findSize(file_to_read);
    char absolute_path[file_size];
    getcwd(absolute_path, file_size);
    char full_absolute_path[file_size];
    sprintf(full_absolute_path, "%s/%s", absolute_path, file_to_read);

    FILE *cmd;
    char result[NUMBER_OF_CARS];
    char grep_file_result[file_size];
    sprintf(grep_file_result, "egrep -o '^[0-9]{1,2}' '%s'", full_absolute_path);

    cmd = popen(grep_file_result, "r");
    if (cmd == NULL) perror("popen failed !"), exit(EXIT_FAILURE);;

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

    if (pclose(cmd) != 0) perror("pclose failed !"), exit(EXIT_FAILURE);;
}

int findSize(char file_name[]) {

    FILE *file = fopen(file_name, "r");

    if (file == NULL) {
        printf("%s : %s", circuit.step_name, "file not Found!\n");
        return -1;
    }

    fseek(file, 0L, SEEK_END);

    int res = ftell(file);
    if (fclose(file) != 0) perror("fclose failed !"), exit(EXIT_FAILURE);;
    return res;
}

void save_eliminated_cars(char file_to_save[], int array[]) {

    FILE *file = fopen(file_to_save, "w");

    if (file == NULL)
        perror("fopen failed !"), exit(EXIT_FAILURE);;

    for (int i = 0; i < 5; i++) {
        fprintf(file, "%d\n", array[i]);
    }

    if (fclose(file) != 0)
        perror("fclose failed !"), exit(EXIT_FAILURE);;
}

void read_eliminated_cars(char file_to_read[], int array[]) {

    char results[5];

    FILE *file = fopen(file_to_read, "r");

    if (file == NULL)perror("fopen failed !"), exit(EXIT_FAILURE);;

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
        perror("fclose failed !"), exit(EXIT_FAILURE);;
}