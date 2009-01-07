#ifndef _ORDONNANCEUR_H_
#define _ORDONNANCEUR_H_

#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <ctype.h>
#include <pthread.h>

extern int nb_color;
extern int grid_size;
extern uint16_t *grid;


void ordonnanceur();

#endif
