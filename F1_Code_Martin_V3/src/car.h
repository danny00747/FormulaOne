#ifndef CAR_H_   /* Include guard */
#define CAR_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "globalvars.h"

float PmaxTime;

void sharedMemory();

void updateBest();

float float_rand( float min, float max );

int int_rand(int min, int max);

short crashed;
void crash();

/**
 * 
 * @param type : le type de session ("P1", "P2", "P3", "Q1", "Q2", "Q3") 
 */
void drive(char type[]);  

void race();


#endif // CAR_H_