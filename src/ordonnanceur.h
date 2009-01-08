#ifndef _ORDONNANCEUR_H_
#define _ORDONNANCEUR_H_

#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include <pthread.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h> 
#include <fcntl.h>

extern int nb_color;
extern int grid_size;
extern uint16_t *grid2;

typedef struct elem
{
  pthread_t fred; /* it is an english pronnonciation for thread by
		     O. BAUDON ;-) */
  struct elem *prev;
  struct elem *next;
} elem ;

typedef struct
{
  elem *first;
  elem *last;
}stack;

uint16_t position = 0;
stack My_stack;
bool is_change=1;

void print_grid(uint16_t* grid);

uint16_t search_next_position(uint16_t position,uint16_t* grid);

bool grid_check(uint16_t* grid);

void ordonnanceur(uint16_t* grid);

void* max_solver(void* test);


#endif
