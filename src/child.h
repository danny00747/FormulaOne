//
// Created by danny on 2/10/19.
//
#pragma once

#include "time.h"
#include "prng.h"
#include <semaphore.h>
#include <time.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <stdbool.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>


#define NUMBER_OF_CARS 20

typedef struct Circuit {
    char *step_name;
    int step_total_time;
    int number_of_laps;
    int lap_km;
    int number_of_cars;
    int race_km;
} Circuit;


typedef struct F1_Car {
    int id;
    double lap_time;
    double s1;
    double s2;
    double s3;
    int best_s1;
    int best_s2;
    int best_s3;
    int stand;
    int out;
    int lap;
    int best_lap_time;
    int done;
} F1_Car;

void child(sem_t *sem, F1_Car *car, int *car_names);

void car_crash();

int finished_running();

int msleep(unsigned int tms);


