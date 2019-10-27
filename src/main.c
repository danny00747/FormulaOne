#include "child.h"
#include "display.h"
#include <getopt.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

Commands command;
Voiture *car;


int car_names[NUMBER_OF_CARS] = {44, 77, 5, 7, 3, 33, 11, 31, 18, 35,
                                 27, 55, 10, 28, 8, 20, 2, 14, 9, 16};

int qualified_cars[15], race_ranking[20], last_cars_of_Q1[15], last_cars_of_Q2[10];

void print_usage() {
    printf("Usage: prog --day [dayName] --step [stepName]\n");
}

int main(int argc, char **argv) {

   // (argc) ? print_usage() : 0;


    signal(SIGINT, return_cursor);
    command.number_of_cars = 20;


    command.lap_length = 7.0;

    static struct option long_options[] = {{"day",  required_argument, NULL, 'd'},
                                           {"step", required_argument, NULL, 's'},
                                           {NULL, 0,                   NULL, 0}};

    char opt;
    while ((opt = getopt_long(argc, argv, "d:s:", long_options, NULL)) != EOF) {
        switch (opt) {


            case 'd':
                command.choosen_day = (enum days) optarg;
                break;
            case 's':

                if (strcasecmp(optarg, "P1") == 0) {
                    command.number_of_cars = 20;
                    command.choosen_step = P1;
                    command.step_name = "P1";
                    command.step_total_time = minutes_to_ms(90);
                } else if (strcasecmp(optarg, "P2") == 0) {
                    command.number_of_cars = 20;
                    command.choosen_step = P2;
                    command.step_name = "P2";
                    command.step_total_time = minutes_to_ms(90);
                } else if (strcasecmp(optarg, "P3") == 0) {
                    command.number_of_cars = 20;
                    command.choosen_step = P3;
                    command.step_name = "P3";
                    command.step_total_time = minutes_to_ms(60);
                } else if (strcasecmp(optarg, "Q1") == 0) {
                    command.number_of_cars = 20;
                    command.choosen_step = Q1;
                    command.step_name = "Q1";
                    command.step_total_time = minutes_to_ms(18);
                } else if (strcasecmp(optarg, "Q2") == 0) {
                    command.number_of_cars = 15;
                    command.choosen_step = Q2;
                    command.step_name = "Q2";
                    command.step_total_time = minutes_to_ms(15);
                    read_files(qualified_cars, race_ranking, last_cars_of_Q1, last_cars_of_Q2, "Q1", 15);
                } else if (strcasecmp(optarg, "Q3") == 0) {
                    command.number_of_cars = 10;
                    command.choosen_step = Q3;
                    command.step_name = "Q3";
                    command.step_total_time = minutes_to_ms(12);
                    read_files(qualified_cars, race_ranking, last_cars_of_Q1, last_cars_of_Q2, "Q2", 10);
                } else if (strcasecmp(optarg, "RACE") == 0) {
                    command.number_of_cars = 20;
                    command.choosen_step = RACE;
                    command.step_name = "RACE";
                    command.step_total_time = minutes_to_ms(60);
                    read_files(qualified_cars, race_ranking, last_cars_of_Q1, last_cars_of_Q2, "Q3", 10);
                    read_eliminated_cars("lastQ2", race_ranking);
                    read_eliminated_cars("lastQ1", race_ranking);
                    read_eliminated_cars("Q3", race_ranking);
                } else {
                    break;
                    default:
                        print_usage();
                    exit(EXIT_FAILURE);
                }
        }
    }


    (strcmp(command.step_name, "Q2") == 0) ? save_eliminated_cars("lastQ1", last_cars_of_Q1)
                                           : (strcmp(command.step_name, "Q3") == 0) ? save_eliminated_cars("lastQ2",
                                                                                                           last_cars_of_Q2)
                                                                                    : NULL;

    int struct_shm_id = shmget(
            IPC_PRIVATE, sizeof(Voiture) * command.number_of_cars, 0600 | IPC_CREAT);
    if (struct_shm_id == -1) {
        perror("shmget failed !");
        exit(1);
    }

    car = shmat(struct_shm_id, NULL, 0);
    if (car == (void *) (-1)) {
        perror("shmat failed !");
        exit(1);
    }

    int sem_shm_id = shmget(IPC_PRIVATE, sizeof(sem_t), 0600 | IPC_CREAT);
    if (sem_shm_id == -1) {
        perror("shmget failed !");
        exit(1);
    }
    sem_t *sem = shmat(sem_shm_id, NULL, 0);
    if (sem == (void *) (-1)) {
        perror("shmat failed !");
        exit(1);
    }

    // init semaphore with 1 as initial value
    sem_init(sem, 1, 1);

    int i;
    pid_t pid = 0;
    for (i = 0; i < command.number_of_cars; i++) {
        pid = fork();
        if (pid == 0)
            break;
    }

    switch (pid) {
        case -1:
            fprintf(stderr, "fork failed !");
            exit(-1);
        case 0:
            (strcmp(command.step_name, "Q2") == 0 || strcmp(command.step_name, "Q3") == 0) ?
            child(sem, &car[i], &qualified_cars[i]) : (strcmp(command.step_name, "RACE") == 0) ?
                                                      child(sem, &car[i], &race_ranking[i]) :
                                                      child(sem, &car[i], &car_names[i]);
            exit(0);
        default:
            display(sem, car);
            for (int j = 0; j < command.number_of_cars; j++) {
                wait(NULL);
            }
    }
    shmdt(car);
    shmctl(struct_shm_id, IPC_RMID, NULL);

    sem_destroy(sem);
    shmdt(sem);
    shmctl(sem_shm_id, IPC_RMID, NULL);
    exit(0);

}