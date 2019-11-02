#include "child.h"

int time_passed = 0;
Voiture *vehicule;
Circuit circuit;

void car_crash() {
    if (car_crashed(10000000))
        vehicule->out = 1;
    else
        vehicule->out = 0;
}

void child(sem_t *sem, Voiture *car, int *car_names) {

    random_seed(getpid());
    vehicule = car;
    vehicule->id = *car_names;

    while (time_passed <= circuit.step_total_time) {

        (strcmp(circuit.step_name, "RACE") == 0) ? sleep(10) : 0;

        sem_wait(sem);
        vehicule->s1 = sector_range(30, 45, 10000000);
        car_crash();
        sem_post(sem);

        sem_wait(sem);
        vehicule->s2 = sector_range(30, 45, 10000000);
        car_crash();
        sem_post(sem);

        sem_wait(sem);
        vehicule->s3 = sector_range(30, 45, 10000000);

        int i = 1;
        vehicule->stand = 0;
        while (stand_probability(10)) {

            vehicule->s3 += stand_duration(1, 10);
            i++;
            vehicule->stand = 1;
        }
        car_crash();

        vehicule->lap_time = vehicule->s1 + vehicule->s2 + vehicule->s3;
        time_passed += vehicule->lap_time;

        if (vehicule->best_lap_time == 0 ||
            vehicule->best_lap_time > vehicule->lap_time)
            vehicule->best_lap_time = vehicule->lap_time;

        (time_passed >= circuit.step_total_time) ? vehicule->done = 1 : 0;
        vehicule->lap++;
        sem_post(sem);
        sleep(1);
    }
}
