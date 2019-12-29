//
// Created by danny on 5/10/19.
//

#pragma once

#include <semaphore.h>
#include "child.h"
#include "window.h"
#include "time.h"
#include "files.h"
#include "../lib/fort.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void display(sem_t *_sem, F1_Car *data);
int compare(const void *left, const void *right);
int best_sector(char sector[]);
int best_car();