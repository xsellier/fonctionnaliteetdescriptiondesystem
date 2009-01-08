#ifndef _ORDONNANCEUR_H_
#define _ORDONNANCEUR_H_

#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include <pthread.h>
#include <stdbool.h>

extern int nb_color;
extern int grid_size;
extern uint16_t *grid;

bool is_change=1;

uint16_t search_next_position(uint16_t position);

bool grid_check();

void ordonnanceur();

void* max_solver(void* test);


#endif
