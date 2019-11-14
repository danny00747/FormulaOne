//
// Created by danny on 5/10/19.
//

#include "display.h"


Circuit circuit;
F1_Car car_array[20];


int compare(const void *left, const void *right) {
    const F1_Car *process_a = (F1_Car *) left;
    const F1_Car *process_b = (F1_Car *) right;

    if (strcmp(circuit.step_name, "RACE")) {
        if (process_a->best_lap_time < process_b->best_lap_time)
            return -1;
        else if (process_a->best_lap_time > process_b->best_lap_time)
            return 1;
        else
            return 0;
    } else {
        if (process_a->lap < process_b->lap)
            return 1;
        else if (process_a->lap > process_b->lap)
            return -1;
        else
            return 0;
    }
}

void print_table() {

    ft_table_t *table = ft_create_table();

    ft_set_border_style(table, FT_DOUBLE2_STYLE);

    ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
    ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_CELL_TEXT_STYLE, FT_TSTYLE_BOLD);
    ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_CONT_FG_COLOR, FT_COLOR_CYAN);

    ft_write_ln(table, "POSITION", "NAME", "S1", "S2", "S3", "OUT", "PIT", "LAP", "LAP TIME", "BEST LAP TIME");

    for (int i = 0; i < circuit.number_of_cars; i++) {
        F1_Car current = car_array[i];

        char sector1_time[10];
        to_string(current.s1, sector1_time);

        char sector2_time[10];
        to_string(current.s2, sector2_time);

        char sector3_time[10];
        to_string(current.s3, sector3_time);

        char lap_time[10];
        to_string(current.lap_time, lap_time);

        char best_lap_time[10];
        to_string(current.best_lap_time, best_lap_time);

        ft_printf_ln(table, "%d|%d|%.6s|%.6s|%.6s|%d|%d|%d|%.7s|%.7s", i + 1,
                     current.id, sector1_time, sector2_time, sector3_time, current.out,
                     current.stand, current.lap, lap_time, best_lap_time);

        (current.stand)
        ? ft_set_cell_prop(table, i + 1, FT_ANY_COLUMN, FT_CPROP_CONT_FG_COLOR, FT_COLOR_DARK_GRAY)
        : ft_set_cell_prop(table, i + 1, 6, FT_CPROP_CONT_FG_COLOR, FT_COLOR_LIGHT_GRAY);
    }

    ft_set_cell_prop(table, 1, FT_ANY_COLUMN, FT_CPROP_CONT_FG_COLOR, FT_COLOR_LIGHT_GREEN);
    ft_set_cell_prop(table, 2, FT_ANY_COLUMN, FT_CPROP_CONT_FG_COLOR, FT_COLOR_LIGHT_BLUE);
    ft_set_cell_prop(table, 3, FT_ANY_COLUMN, FT_CPROP_CONT_FG_COLOR, FT_COLOR_LIGHT_YELLOW);

    ft_table_t *second_table = ft_create_table();
    ft_write_ln(second_table, "SECTORS", "NAME", "TIME");
    ft_set_border_style(second_table, FT_DOUBLE2_STYLE);

    ft_set_cell_prop(second_table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
    ft_set_cell_prop(second_table, 0, FT_ANY_COLUMN, FT_CPROP_CELL_TEXT_STYLE, FT_TSTYLE_BOLD);
    ft_set_cell_prop(second_table, 0, FT_ANY_COLUMN, FT_CPROP_CONT_FG_COLOR, FT_COLOR_CYAN);

    char s1_time[10];
    to_string(car_array[best_sector("S1")].best_s1, s1_time);

    char s2_time[10];
    to_string(car_array[best_sector("S2")].best_s2, s2_time);

    char s3_time[10];
    to_string(car_array[best_sector("S3")].best_s3, s3_time);

    char winner[10];
    to_string(car_array[best_lap_time()].best_lap_time, winner);

    ft_printf_ln(second_table, "%s|%d|%s", "S1", car_array[best_sector("S1")].id, s1_time);
    ft_printf_ln(second_table, "%s|%d|%s", "S2", car_array[best_sector("S2")].id, s2_time);
    ft_printf_ln(second_table, "%s|%d|%s", "S3", car_array[best_sector("S3")].id, s3_time);
    (!strcmp(circuit.step_name, "RACE")) ?
    ft_printf_ln(second_table, "%s|%d|%.7s", "Winner", car_array[best_lap_time()].id, winner) : 0;

    clear();
    printf("%s", ft_to_string(table));
    printf("%s", ft_to_string(second_table));
    ft_destroy_table(table);
    ft_destroy_table(second_table);
}

int best_sector(char sector[]) {
    int sector_number = 0;
    int id = 0;
    for (int i = 0; i < circuit.number_of_cars; i++) {

        if (!strcmp(sector, "S1")) {
            if (sector_number == 0 || car_array[i].best_s1 < sector_number) {
                sector_number = car_array[i].best_s1;
                id = i;
            }
        } else if (!strcmp(sector, "S2")) {
            if (sector_number == 0 || car_array[i].best_s2 < sector_number) {
                sector_number = car_array[i].best_s2;
                id = i;
            }
        } else if (!strcmp(sector, "S3")) {
            if (sector_number == 0 || car_array[i].best_s3 < sector_number) {
                sector_number = car_array[i].best_s3;
                id = i;
            }
        }
    }
    return id;
}

int best_lap_time() {
    int winner = 0;
    int id = 0;
    for (int i = 0; i < circuit.number_of_cars; i++) {
        if (winner == 0 || car_array[i].best_lap_time < winner) {
            winner = car_array[i].best_lap_time;
            id = i;
        }
    }
    return id;
}

int finished() {
    for (int i = 0; i < circuit.number_of_cars; ++i) {
        if (car_array[i].out) {
            return 1;
        }
    }
    return 0;
}

void display(sem_t *sem, F1_Car *data) {

    init_window();

    while (1) {
        sem_wait(sem);
        memcpy(car_array, data, sizeof(F1_Car) * circuit.number_of_cars);
        sem_post(sem);
        qsort(car_array, circuit.number_of_cars, sizeof(F1_Car), compare);
        if (finished() || car_array[9].done) {
            break;
        }
        print_table();
        sleep(1);
    }
    sleep(1);
    save_ranking();
    terminate_window();
}
