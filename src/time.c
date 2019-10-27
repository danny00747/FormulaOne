//
// Created by danny on 19/10/19.
//

#include "time.h"

Time time_to_ms(int msec) {
    Time formated_time;
    div_t result;

    result = div(msec, 60000);
    formated_time.min = result.quot;
    msec = result.rem;

    result = div(msec, 1000);
    formated_time.sec = result.quot;
    msec = result.rem;

    formated_time.msec = msec;
    return formated_time;
}

int minutes_to_ms(int minutes) { return minutes * 60000; }

void to_string(int msec, char *str) {
    Time time = time_to_ms(msec);
    (time.min) ? sprintf(str, "%d':%d\"%d", time.min, time.sec, time.msec)
               : sprintf(str, "%d\":%d", time.sec, time.msec);
}