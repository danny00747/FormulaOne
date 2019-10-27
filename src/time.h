#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef struct Time {
    int min;
    int sec;
    int msec;
} Time;

Time time_to_ms(int msec);

int minutes_to_ms(int minutes);

void to_string(int msec, char *str);