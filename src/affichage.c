#include "affichage.h"
#include "curses.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void affichage(void) {
  ft_table_t *table = ft_create_table();
  ft_set_border_style(table, FT_DOUBLE2_STYLE);
  ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
  ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_CELL_TEXT_STYLE,
                   FT_TSTYLE_BOLD);
  ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_CONT_FG_COLOR,
                   FT_COLOR_CYAN);

  ft_write_ln(table, "N", "Driver", "Time", "Avg Speed", "out");
  ft_set_cell_span(table, 0, 4, 10);

  add_line(table, 1, "1", "Ricciardo", "1:25.945", "222.128", 0);

  ft_set_cell_span(table, 1, 4, 10);
  add_line(table, 2, "2", "Hamilton", "1:26.373", "221.027", 1);
  ft_set_cell_span(table, 2, 4, 10);
  add_line(table, 3, "3", "Verstappen", "1:26.469", "220.782", 1);
  ft_set_cell_span(table, 3, 4, 10);
  ft_add_separator(table);
  ft_set_cell_span(table, 4, 0, 14);
  ft_u8write_ln(table, "BEST");
  ft_set_cell_prop(table, 4, FT_ANY_COLUMN, FT_CPROP_CELL_TEXT_STYLE,
                   FT_TSTYLE_BOLD);
  ft_set_cell_prop(table, 4, FT_ANY_COLUMN, FT_CPROP_TEXT_ALIGN,
                   FT_ALIGNED_CENTER);
  ft_add_separator(table);
  ft_set_cell_span(table, 5, 2, 12);
  ft_write_ln(table, "Sectors", "Name", "Timee", "", "");
  ft_set_cell_prop(table, 5, FT_ANY_COLUMN, FT_CPROP_CONT_FG_COLOR,
                   FT_COLOR_CYAN);
  ft_set_cell_prop(table, 5, FT_ANY_COLUMN, FT_CPROP_CELL_TEXT_STYLE,
                   FT_TSTYLE_ITALIC);
  ft_set_cell_span(table, 6, 2, 12);
  ft_u8write_ln(table, "S1", "12", "1:25.945", "", "");
  ft_set_cell_span(table, 7, 2, 12);
  ft_u8write_ln(table, "S2", "4", "1:25.945", "", "");
  ft_set_cell_span(table, 8, 2, 12);
  ft_u8write_ln(table, "S3", "17", "1:25.945", "", "");

  printf("%s\n", ft_to_string(table));
  ft_destroy_table(table);
  print();
  // printt();
}

void add_line(ft_table_t *table, int line, char *n, char *driver, char *time,
              char *avg_speed, int out) {
  char *out_str = out ? "✔" : "✗";
  ft_u8write_ln(table, n, driver, time, avg_speed, out_str);

  ft_set_cell_prop(table, line, 0, FT_CPROP_CONT_FG_COLOR, FT_COLOR_YELLOW);
  enum ft_color out_color = out ? FT_COLOR_GREEN : FT_COLOR_RED;
  ft_set_cell_prop(table, line, 4, FT_CPROP_CONT_FG_COLOR, out_color);
}

void print() {

  ft_table_t *table = ft_create_table();
  /* Change border style */
  ft_set_border_style(table, FT_DOUBLE2_STYLE);

  /* Set "header" type for the first row */
  // ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE,
  // FT_ROW_HEADER);
  ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_CONT_FG_COLOR,
                   FT_COLOR_CYAN);

  ft_write_ln(table, "Movie title", "Director", "Year", "Rating");

  ft_u8write_ln(table, "The Shawshank Redemption", "Frank Darabont", "1994",
                "✔");
  ft_set_cell_prop(table, 1, 0, FT_CPROP_CONT_FG_COLOR, FT_COLOR_GREEN);
  ft_u8write_ln(table, "The Godfather", "Francis Ford Coppola", "1972", "X");
  ft_set_cell_prop(table, 2, 3, FT_CPROP_CELL_BG_COLOR, FT_COLOR_RED);
  ft_u8write_ln(table, "2001: A Space Odyssey", "Stanley Kubrick", "1968", "✔");
  ft_set_cell_prop(table, 3, 0, FT_CPROP_CONT_FG_COLOR, FT_COLOR_GREEN);

  printf("%s\n", ft_to_string(table));
  ft_destroy_table(table);
}

void printt() {
  ft_table_t *table = ft_create_table();
  /* Change border style */
  ft_set_border_style(table, FT_DOUBLE2_STYLE);

  ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
  ft_write_ln(table, "Sed", "Aenean", "Text");

  ft_write_ln(table, "Duis", "Aliquam", "Lorem ipsum dolor");
  ft_write_ln(table, "Mauris", "Curabitur", "Proin condimentum");
  ft_write_ln(table, "Summary", "",
              "Sed tempor est eget odio varius dignissim.");

  /* Set cell span */
  ft_set_cell_span(table, 3, 0, 2);
  ft_set_cell_span(table, 2, 2, 2);
  printf("%s\n", ft_to_string(table));
  ft_destroy_table(table);
}