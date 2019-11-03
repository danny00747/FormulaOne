//
// Created by danny on 2/10/19.
//
#pragma once

#include "time.h"
#include "generated_random_numbers.h"
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

enum step {
    P1, P2, P3, Q1, Q2, Q3, RACE
};

enum days {
    fri, sat, sun
};

typedef struct Circuit {
    enum step choosen_step;
    enum days choosen_day;
    char *step_name;
    int step_total_time;
    int number_of_laps;
    int lap_km;
    int number_of_cars;
    int race_km;
} Circuit;


typedef struct Voiture {
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
} Voiture;

void asciiArt();

void child(sem_t *sem, Voiture *car, int *car_names);

void car_crash();

int step_done();

int msleep(unsigned int tms);


