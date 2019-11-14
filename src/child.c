#include "child.h"

int time_passed = 0;
int current_lap = 0;
F1_Car *vehicle;
Circuit circuit;

void car_crash() {
    if (car_crashed(10000000))
        vehicle->out = 1;
    else
        vehicle->out = 0;
}

int finished_running() {
    if (!strcmp(circuit.step_name, "RACE")) {
        return current_lap == circuit.number_of_laps;
    } else {
        return time_passed >= circuit.step_total_time;
    }
}

int msleep(unsigned int tms) {
    return usleep(tms * 1000);
}

void child(sem_t *sem, F1_Car *car, int *car_names) {

    random_seed(getpid());
    vehicle = car;
    vehicle->id = *car_names;

    while (!finished_running()) {

        //(!strcmp(circuit.step_name, "RACE")) ? sleep(10) : 0;

        sem_wait(sem);
        vehicle->s1 = sector_range(30, 45, 10000000);
        if (vehicle->best_s1 == 0 || vehicle->best_s1 > vehicle->s1) {
            vehicle->best_s1 = vehicle->s1;
        }
        car_crash();
        sem_post(sem);

        sem_wait(sem);
        vehicle->s2 = sector_range(30, 45, 10000000);
        if (vehicle->best_s2 == 0 || vehicle->best_s2 > vehicle->s2) {
            vehicle->best_s2 = vehicle->s2;
        }
        car_crash();
        sem_post(sem);

        sem_wait(sem);
        vehicle->s3 = sector_range(30, 45, 10000000);

        int i = 1;
        vehicle->stand = 0;
        while (stand_probability(10)) {

            vehicle->s3 += stand_duration(1, 100);
            i++;
            vehicle->stand = 1;
        }
        if (vehicle->best_s3 == 0 || vehicle->best_s3 > vehicle->s3) {
            vehicle->best_s3 = vehicle->s3;
        }
        car_crash();
        msleep(80);

        vehicle->lap_time = vehicle->s1 + vehicle->s2 + vehicle->s3;
        time_passed += vehicle->lap_time;

        if (vehicle->best_lap_time == 0 ||
            vehicle->best_lap_time > vehicle->lap_time)
            vehicle->best_lap_time = vehicle->lap_time;
        vehicle->lap++;
        current_lap = vehicle->lap;
        (time_passed >= circuit.step_total_time || current_lap == circuit.number_of_laps) ? vehicle->done = 1 : 0;
        sem_post(sem);
        sleep(1);
    }
}
