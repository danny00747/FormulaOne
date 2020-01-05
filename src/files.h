#pragma once

#include "child.h"
#include "window.h"
#include "time.h"
#include "../lib/fort.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>

void save_ranking();

int find_size(char *file_name);

void read_files(int qualified_cars[], int race_ranking[], int last_cars_of_Q1[], int last_cars_of_Q2[], char file[], int lines_to_read);

void save_eliminated_cars(char file_to_save[], int array[]);

void read_eliminated_cars(char file_to_read[], int array[]);

void read_resources_files(char *file_name);

char* get_resources_file(char *file_name);