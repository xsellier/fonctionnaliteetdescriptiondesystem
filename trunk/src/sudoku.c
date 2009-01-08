#include "sudoku.h"

void
fill_grid(uint16_t color, uint16_t* tmp_grid, int position)
{
  if(isxdigit(color))
    {
      tmp_grid[position]=color;
    }
  else
    {
      if(color=='_')
	{
	  *(tmp_grid+position)= 0xFF;
	}
    }
}

void
print_grid(uint16_t *grid)
{
  int loop = nb_color*nb_color;
  int i;
  for(i=0; i<=loop;++i)
    {
      printf("%c ",grid[i]);
      if((i+1)%nb_color==0 && i!=0)
	printf("\n");
    }
}

void
grid_cpy(uint16_t* tmp_grid)
{
  int i;
  int loop = nb_color*nb_color;
  for(i=0;i<=loop;++i)
    {
      grid[i]=tmp_grid[i];
    }
}

void
parsing(char *file)
{
  FILE *my_file = NULL;
  int buf_tmp = 0;
  int position = 0;
  uint16_t* tmp_grid=malloc(grid_size * sizeof(uint16_t));
  my_file = fopen(file,"r");
  if(my_file == NULL)
    {
      perror(file);
      exit(0);
    }
  buf_tmp = fgetc(my_file);
  while (buf_tmp != EOF)
    {
      if(grid_size<nb_color)
	{
	  grid_size = grid_size*2;
	  tmp_grid = realloc(tmp_grid, grid_size * sizeof(uint16_t)); 
	}
      nb_color++;
      fill_grid((uint16_t)buf_tmp,tmp_grid,position);
      if(!isspace(buf_tmp))
	 position++;
      buf_tmp = fgetc(my_file);
    }
  
  fclose(my_file);
  grid = malloc(nb_color+1 * sizeof(uint16_t));
  nb_color = sqrt(nb_color/2);
  grid_cpy(tmp_grid);
}
 
main(int argc, char **argv) 
{ 
  parsing(argv[1]);

  ordonnanceur();

  print_grid(grid);

  return EXIT_SUCCESS;
}
