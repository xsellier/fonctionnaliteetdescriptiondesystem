#ifndef _SUDOKU_H_
#define _SUDOKU_H_

#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

int nb_color = 0;
int grid_size = 10;
uint16_t *grid2=NULL;

void ordonnanceur(uint16_t* grid);

void
sudoku(uint16_t* grid);

void
fill_grid(uint16_t color, uint16_t* tmp_grid, int position);

void
print_grid(uint16_t *grid);

void
grid_cpy(uint16_t* tmp_grid);

void
grid_cpy_invert(uint16_t* tmp_grid);

void
parsing(char *file);

#endif 
