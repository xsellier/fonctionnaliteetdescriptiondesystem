#include "sudoku.h"

void fill_grid(uint16_t color, uint16_t* tmp_grid, int position) {
  if (isxdigit(color)) {
      tmp_grid[position] = color;
  } else {
    if (color == '_') {
	    *(tmp_grid + position) = 0xFF;
	  }
  }
}

void print_grid(uint16_t *grid) {
  int loop = nb_color*nb_color;
  int index;

  for (index = 0; index <= loop; ++index) {
    printf("%c ",grid[index]);

    if((index+1)%nb_color==0 && index!=0) {
      printf("\n");
    }
  }

  printf("\n");
}

void
grid_cpy(uint16_t* tmp_grid)
{
  int index;
  int loop = nb_color*nb_color;
  for(index=0;index<=loop;++index)
    {
      grid2[index]=tmp_grid[index];
    }
}

void
grid_cpy_invert(uint16_t* tmp_grid, uint16_t* grid)
{
  int index;
  int loop = nb_color * nb_color;

  for ( index = 0; index <= loop; ++index) {
    tmp_grid[index]=grid[index];
  }
}

void parsing(char *file) {
  FILE *my_file = NULL;
  int buf_tmp = 0;
  int position = 0;
  uint16_t* tmp_grid=malloc(grid_size * sizeof(uint16_t));
  my_file = fopen(file,"r");

  if(my_file == NULL) {
    perror(file);
    exit(0);
  }

  buf_tmp = fgetc(my_file);

  // Keep reading the file until the file has been read to the end
  while (buf_tmp != EOF) {

    if (grid_size < nb_color) {
      grid_size = grid_size * 2;
      tmp_grid = realloc(tmp_grid, grid_size * sizeof(uint16_t)); 
    }

    nb_color++;

    fill_grid((uint16_t)buf_tmp, tmp_grid, position);

    if (!isspace(buf_tmp)) {
      position++;
    }

    buf_tmp = fgetc(my_file);
  }
  
  fclose(my_file);

  grid2 = malloc(nb_color + 1 * sizeof(uint16_t));
  nb_color = sqrt(nb_color/2);

  grid_cpy(tmp_grid);
}
 
int
main(int argc, char **argv) 
{ 
  if (argc != 2) {
    printf("It takes one argument, the grid file only, no more no less\n");

    return EXIT_FAILURE;
  }

  uint16_t* grid = NULL;

  parsing(argv[1]);

  printf("Detected size of the grid: %i\n", nb_color);

  grid = malloc(nb_color * nb_color * sizeof(uint16_t));

  grid_cpy_invert(grid,grid2);

  sudoku(grid);

  return EXIT_SUCCESS;
}

void search_color(bool* c_available, uint16_t position, uint16_t* grid) {
  uint16_t d = sqrt(nb_color);
  uint16_t tmp_pos;
  uint16_t tmp;
  uint16_t index;
  
  for (index = 0; index < nb_color; ++index) {
    c_available[index] = 1;
  }
  
   /* filling columns */
  tmp_pos = position % nb_color;

  for (; tmp_pos < nb_color * nb_color; tmp_pos += nb_color) {
    if (grid[tmp_pos] != 0xFF) {
	    if (grid[tmp_pos] > 57) {
        c_available[(grid[tmp_pos] - 65)] = 0;
      } else {
	      c_available[(grid[tmp_pos] - 48)] = 0;
      }
	  }
	}
  
  /* filling line */
  tmp_pos = position;

  while (tmp_pos % nb_color != 0) {
    tmp_pos--;
  }

  tmp = tmp_pos;

  for (; tmp_pos < tmp + nb_color; ++tmp_pos) {
    if (grid[tmp_pos] != 0xFF) {
	    if (grid[tmp_pos] > 57) {
	      c_available[(grid[tmp_pos] - 65)] = 0;
      } else {
    	  c_available[(grid[tmp_pos] - 48)] = 0;
	    }
    }
  }
  
  /* filling blocks */
  tmp_pos = position;

  while (tmp_pos % d != 0) {
    tmp_pos--;
  }

  do {
    if (grid[tmp_pos] != 0xFF) {
	    if (grid[tmp_pos] > 57) {
	      c_available[(grid[tmp_pos] - 65)] = 0;
	    } else {
	      c_available[(grid[tmp_pos] - 48)] = 0;
	    }
    }
    ++tmp_pos;

    if (tmp_pos % d == 0) {
      tmp_pos = tmp_pos + nb_color - d;
    }
  } while (tmp_pos < d * nb_color); 
}

void sudoku(uint16_t* grid_old) {
  int index;
  uint16_t pos;
  bool* condition = malloc(nb_color*sizeof(bool));
  bool complete = true;
  uint16_t* grid = malloc(nb_color*nb_color*sizeof(uint16_t));

  grid_cpy_invert(grid,grid_old);
  print_grid(grid);

  if (grid_check(grid)) {
    ordonnanceur(grid);
    
    for (index = 0; index < (nb_color * nb_color); ++index) {
	    if(grid[index]==0xFF) {
        complete=false;
      }
    }

    if (complete) {
      print_grid(grid);
    } else {
      pos = 0;
  
	    while (grid[pos] != 0xFF && pos < (nb_color * nb_color - 1)) {
	      pos++;
      }

      search_color(condition, pos, grid);

      for (index = 0; index < nb_color; ++index) {
        if (condition[index]) {
          if (index + 48 > 57) {
            grid[pos] = index + 65;
          } else {
            grid[pos] = index + 48;
          }

          sudoku(grid);
        }
      }
    }
  }
}

