#include "car.h"

void drive(char type[]){

    if (strcmp(type,"P1" ) == 0|| strcmp(type,"P2" ) == 0){
        PmaxTime = 5400;
    } 
    else if (strcmp(type,"P3" ) == 0){
        PmaxTime = 3600;
    }
    car.totalSessionTime = 0;

    while(car.totalSessionTime <= PmaxTime){
        if(crashed){
            car.state = 'C';
            car.totalSessionTime = 99999;
            sharedMemory();
            usleep(200000);
        }
        else{
            car.state = ' ';
            car.numberOfLaps ++;
            car.s1Time = float_rand(40.0,50.0);
            car.s2Time = float_rand(40.0,50.0);
            car.s3Time = float_rand(40.0,50.0);
            car.lapTime = car.s1Time + car.s2Time + car.s3Time;
            car.totalSessionTime += car.lapTime;
            updateBest();
            sharedMemory();
            crash();
            usleep(200000);//400000
        }
    }
    //printf("%d ",int_rand(1,10));
}


void crash(){
    if(int_rand(1,500)== 1){
        crashed = 1;
    }
    else{
        crashed = 0;
    }
}


void updateBest(){
    if(car.s1Time < car.bestS1Time || car.bestS1Time == 0){
            car.bestS1Time = car.s1Time;
        }
        if(car.s2Time < car.bestS2Time || car.bestS2Time == 0){
            car.bestS2Time = car.s2Time;
        }
        if(car.s3Time < car.bestS3Time || car.bestS3Time == 0){
            car.bestS3Time = car.s3Time;
        }
        if(car.lapTime < car.bestLapTime || car.bestLapTime == 0){
            car.bestLapTime = car.lapTime;
        }
}

void sharedMemory(){
    sem_wait(&mutex);
    Cars = (Car*)shmat(shmid,0,0);
        if(Cars == (Car *)(-1)) {
            perror("shmat");
            exit(1);
        }
    Cars[car.carID-1] = car; 
    shmdt((void *) Cars);
    sem_post(&mutex);
}

float float_rand( float min, float max )
{
    float scale = rand() / (float) RAND_MAX; /* [0, 1.0] */
    return min + scale * ( max - min );      /* [min, max] */
}

int int_rand(int min, int max){
    return min + rand()%(max-min);
}

