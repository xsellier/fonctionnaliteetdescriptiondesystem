#ifndef _SUDOKU_H_
#define _SUDOKU_H_

#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <ctype.h>

int nb_color = 0;
int grid_size = 10;
uint16_t *grid=NULL;

void
fill_grid(uint16_t color, uint16_t* tmp_grid, int position);

void
print_grid(uint16_t *grid);

void
grid_cpy(uint16_t* tmp_grid);

void
parsing(char *file);

#endif 