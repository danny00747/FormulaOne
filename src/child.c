#include "child.h"

int time_passed = 0;
int current_lap = 0;
Voiture *vehicule;
Circuit circuit;

void car_crash() {
    if (car_crashed(10000000))
        vehicule->out = 1;
    else
        vehicule->out = 0;
}

int step_done() {
    if (!strcmp(circuit.step_name, "RACE")) {
        return current_lap == circuit.number_of_laps;
    } else {
        return time_passed >= circuit.step_total_time;
    }
}

int msleep(unsigned int tms) {
    return usleep(tms * 1000);
}


void child(sem_t *sem, Voiture *car, int *car_names) {

    random_seed(getpid());
    vehicule = car;
    vehicule->id = *car_names;

    while (!step_done()) {

        //(!strcmp(circuit.step_name, "RACE")) ? sleep(10) : 0;

        sem_wait(sem);
        vehicule->s1 = sector_range(30, 45, 10000000);
        if (vehicule->best_s2 == 0 || vehicule->best_s1 > vehicule->s1) {
            vehicule->best_s1 = vehicule->s1;
        }
        car_crash();
        sem_post(sem);

        sem_wait(sem);
        vehicule->s2 = sector_range(30, 45, 10000000);
        if (vehicule->best_s2 == 0 || vehicule->best_s2 > vehicule->s2) {
            vehicule->best_s2 = vehicule->s2;
        }
        car_crash();
        sem_post(sem);

        sem_wait(sem);
        vehicule->s3 = sector_range(30, 45, 10000000);

        int i = 1;
        vehicule->stand = 0;
        while (stand_probability(10)) {

            vehicule->s3 += stand_duration(1, 100);
            i++;
            vehicule->stand = 1;
        }
        if (vehicule->best_s3 == 0 || vehicule->best_s3 > vehicule->s3) {
            vehicule->best_s3 = vehicule->s3;
        }
        car_crash();
        msleep(80);

        vehicule->lap_time = vehicule->s1 + vehicule->s2 + vehicule->s3;
        time_passed += vehicule->lap_time;

        if (vehicule->best_lap_time == 0 ||
            vehicule->best_lap_time > vehicule->lap_time)
            vehicule->best_lap_time = vehicule->lap_time;
        vehicule->lap++;
        current_lap = vehicule->lap;
        (time_passed >= circuit.step_total_time || current_lap == circuit.number_of_laps) ? vehicule->done = 1 : 0;
        sem_post(sem);
        sleep(1);
    }
}
