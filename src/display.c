//
// Created by danny on 5/10/19.
//

#include "display.h"


Circuit circuit;
Voiture copy[20];


int compare(const void *left, const void *right) {
    const Voiture *process_a = (Voiture *) left;
    const Voiture *process_b = (Voiture *) right;

    if (process_a->best_lap_time < process_b->best_lap_time)
        return -1;
    else if (process_a->best_lap_time > process_b->best_lap_time)
        return 1;
    else
        return 0;

}

void print_table() {

    ft_table_t *table = ft_create_table();

    ft_set_border_style(table, FT_DOUBLE2_STYLE);

    ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
    ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_CELL_TEXT_STYLE,
                     FT_TSTYLE_BOLD);
    ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_CONT_FG_COLOR,
                     FT_COLOR_CYAN);
    ft_write_ln(table, "POSITION", "NAME", "S1", "S2", "S3", "OUT", "PIT", "LAP",
                "LAP TIME", "BEST LAP TIME");

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
        ? ft_set_cell_prop(table, i + 1, FT_ANY_COLUMN, FT_CPROP_CONT_FG_COLOR,
                           FT_COLOR_DARK_GRAY)
        : ft_set_cell_prop(table, i + 1, 6, FT_CPROP_CONT_FG_COLOR,
                           FT_COLOR_LIGHT_GRAY);
       // printf("%s%d\n", "The laps remaning : ", current.lap);
    }

    ft_set_cell_prop(table, 1, FT_ANY_COLUMN, FT_CPROP_CONT_FG_COLOR, FT_COLOR_LIGHT_GREEN);
    ft_set_cell_prop(table, 2, FT_ANY_COLUMN, FT_CPROP_CONT_FG_COLOR, FT_COLOR_LIGHT_BLUE);
    ft_set_cell_prop(table, 3, FT_ANY_COLUMN, FT_CPROP_CONT_FG_COLOR, FT_COLOR_LIGHT_YELLOW);



    clear();
    printf("%s\n", ft_to_string(table));
    ft_destroy_table(table);
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
        if (finished() || data->done) {
            break;
        }
        print_table();
        sleep(1);
    }
    sleep(10);
    save_ranking();
    terminate_window();
}
