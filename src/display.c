//
// Created by danny on 5/10/19.
//

#include "display.h"


Circuit circuit;
Voiture copy[20];


int compare(const void *left, const void *right) {
    const Voiture *process_a = (Voiture *) left;
    const Voiture *process_b = (Voiture *) right;

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
        Voiture current = copy[i];

        char s1_str[10];
        to_string(current.s1, s1_str);

        char s2_str[10];
        to_string(current.s2, s2_str);

        char s3_str[10];
        to_string(current.s3, s3_str);

        char lap_str[10];
        to_string(current.lap_time, lap_str);

        char best_lap_str[10];
        to_string(current.best_lap_time, best_lap_str);

        ft_printf_ln(table, "%d|%d|%.6s|%.6s|%.6s|%d|%d|%d|%.7s|%.7s", i + 1,
                     current.id, s1_str, s2_str, s3_str, current.out,
                     current.stand, current.lap, lap_str, best_lap_str);

        (current.stand)
        ? ft_set_cell_prop(table, i + 1, FT_ANY_COLUMN, FT_CPROP_CONT_FG_COLOR, FT_COLOR_DARK_GRAY)
        : ft_set_cell_prop(table, i + 1, 6, FT_CPROP_CONT_FG_COLOR, FT_COLOR_LIGHT_GRAY);
    }

    ft_set_cell_prop(table, 1, FT_ANY_COLUMN, FT_CPROP_CONT_FG_COLOR, FT_COLOR_LIGHT_GREEN);
    ft_set_cell_prop(table, 2, FT_ANY_COLUMN, FT_CPROP_CONT_FG_COLOR, FT_COLOR_LIGHT_BLUE);
    ft_set_cell_prop(table, 3, FT_ANY_COLUMN, FT_CPROP_CONT_FG_COLOR, FT_COLOR_LIGHT_YELLOW);

    /* Second table */

    ft_table_t *second_table = ft_create_table();
    ft_write_ln(second_table, "SECTORS", "NAME", "TIME");
    ft_set_border_style(second_table, FT_DOUBLE2_STYLE);

    ft_set_cell_prop(second_table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
    ft_set_cell_prop(second_table, 0, FT_ANY_COLUMN, FT_CPROP_CELL_TEXT_STYLE, FT_TSTYLE_BOLD);
    ft_set_cell_prop(second_table, 0, FT_ANY_COLUMN, FT_CPROP_CONT_FG_COLOR, FT_COLOR_CYAN);

    int s1 = best_sector("S1");
    char s1_value[10];
    to_string(copy[s1].best_s1, s1_value);

    int s2 = best_sector("S2");
    char s2_value[10];
    to_string(copy[s2].best_s2, s2_value);

    int s3 = best_sector("S3");
    char s3_value[10];
    to_string(copy[s3].best_s3, s3_value);

    ft_printf_ln(second_table, "%s|%d|%s", "S1", copy[best_sector("S1")].id, s1_value);
    ft_printf_ln(second_table, "%s|%d|%s", "S2", copy[best_sector("S2")].id, s2_value);
    ft_printf_ln(second_table, "%s|%d|%s", "S3", copy[best_sector("S3")].id, s3_value);

    clear();
    printf("%s", ft_to_string(table));
    printf("%s", ft_to_string(second_table));
    ft_destroy_table(table);
    ft_destroy_table(second_table);
}

int best_sector(char sector[]) {
    int best = 0;
    int index = 0;
    for (int i = 0; i < circuit.number_of_cars; i++) {

        if (!strcmp(sector, "S1")) {
            if (best == 0 || copy[i].best_s1 < best) {
                best = copy[i].best_s1;
                index = i;
            }
        } else if (!strcmp(sector, "S2")) {
            if (best == 0 || copy[i].best_s2 < best) {
                best = copy[i].best_s2;
                index = i;
            }
        } else if (!strcmp(sector, "S3")) {
            if (best == 0 || copy[i].best_s3 < best) {
                best = copy[i].best_s3;
                index = i;
            }
        }
    }
    return index;
}

int finished() {
    for (int i = 0; i < circuit.number_of_cars; ++i) {
        if (copy[i].out) {
            return 1;
        }
    }
    return 0;
}

void display(sem_t *sem, Voiture *data) {

    init_window();

    while (1) {
        sem_wait(sem);
        memcpy(copy, data, sizeof(Voiture) * circuit.number_of_cars);
        sem_post(sem);
        qsort(copy, circuit.number_of_cars, sizeof(Voiture), compare);
        if (finished() || copy[9].done) {
            break;
        }
        print_table();
        sleep(1);
    }
    sleep(1);
    save_ranking();
    terminate_window();
}
