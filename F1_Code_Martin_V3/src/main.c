
#include "main.h"


int main(){
    
    shmctl(shmid, IPC_RMID, NULL); // deleting shared memory   si erreur persiste: ipcrm -M <key> pour le deleter depuis la ligne de cmd
    shmid = shmget(2,NUMBER_OF_CARS*sizeof(Car),IPC_CREAT | 0666);
    if(shmid == -1){
        perror("shmget");
        exit(1); 
    }
    
    
    if( sem_init(&mutex,1,1) < 0)
    {
      perror("semaphore initilization");
      exit(0);
    }
    
    pid_t pid;
    for(int i=0;i<NUMBER_OF_CARS;i++){
        car.carNumber = carNumbers[i];
        car.carID = i+1;
        pid = fork();
        if(pid==0){
            srand(time(NULL)^ (getpid()<<16));
            drive("P1");
            exit(0);
        } 
    }
    for(int i=0;i<NUMBER_OF_CARS;i++){
        int status;
        while (waitpid(pid, &status, WNOHANG) == 0) {
            rank_cars();
            display();
            usleep(100000);
        }    
    }
    shmctl(shmid, IPC_RMID, NULL); // deleting shared memory

}

