
#include "window.h"

void init_window() { printf("\e[?1049h\e[?7l\e[?25l\e[2J\e[1;52r"); }

void clear() { printf("\e[55H\e[9999C\e[1J\e[1;55r"); }

void terminate_window() { printf("\e[?7h\e[?25h\e[2J\e[;r\e[?1049l"); }

void return_cursor() {
  clear();
  terminate_window();
  exit(EXIT_SUCCESS);
}
