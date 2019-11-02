#include "ranking.h"

void rank_cars(){

    Cars = (Car*)shmat(shmid,0,0);
    for(int i=0;i<NUMBER_OF_CARS;i++){
        ranking[i]=Cars[i];
    }
    sem_wait(&mutex);
    shmdt((void *) Cars);
    Car buff;
    for(int i=0;i<NUMBER_OF_CARS;i++){
      for(int j =0;j<NUMBER_OF_CARS-1;j++){
         if(ranking[j].bestLapTime>ranking[j+1].bestLapTime){
            buff = ranking[j+1];
            ranking[j+1] = ranking[j];
            ranking[j] = buff;
         }
      }
   }
    sem_post(&mutex);
}

