//
// Created by danny on 4/10/19.
//

#pragma once

#include <stdlib.h>

void random_seed(unsigned int seed);

int sector_range(int min, int max, int crashing_probability);

int stand_duration(int min, int max);

int stand_probability(int seed);

int car_crashed(unsigned int seed);

