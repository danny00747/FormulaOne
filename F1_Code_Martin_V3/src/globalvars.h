#ifndef GLOBALVARS_H_   /* Include guard */
#define GLOBALVARS_H_

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <semaphore.h>

static short carNumbers[]={7,99,5,16,8,20,4,55,10,26,44,77,11,18,23,33,3,27,63,88};

#define NUMBER_OF_CARS 5


typedef struct Car {
   int carNumber;
   int numberOfLaps;
   float s1Time;
   float s2Time;
   float s3Time;
   float lapTime;
   float bestS1Time;
   float bestS2Time;
   float bestS3Time;
   float bestLapTime;
   float totalSessionTime;
   char state;
   int carID;
} Car;

Car car;

int shmid;
sem_t mutex;
Car *Cars; //memory alloc

Car ranking[NUMBER_OF_CARS]; 

#endif // GLOBALVARS_H_