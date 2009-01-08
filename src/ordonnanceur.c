#include "ordonnanceur.h"

void* max_solver(void*);

uint16_t
search_next_position(uint16_t position)
{
  uint16_t i=position;
  for(;i<=nb_color*nb_color;++i)
    {
      if(grid[i]==0xFF)
	return i; 
    }
  return i;
}
 
bool
grid_check()
{
  uint16_t d = sqrt(nb_color);
  uint16_t position = 0;
  uint16_t color;
  uint16_t tmp_pos;
  uint16_t tmp;

  /* reach every position */
  for(position = 0; position < (nb_color-1) * (nb_color); ++position)
    {
      while(grid[position]==0xFF && (nb_color-1) * nb_color )
	{
	  position++;
	}
      color = grid[position];
      /* checking columns */
      tmp_pos = position % nb_color;
      for(; tmp_pos < nb_color * nb_color; tmp_pos = tmp_pos+nb_color)
	{
	  if(grid[tmp_pos] == color && grid[tmp_pos]!= 0xFF && tmp_pos != position)
	    return false;
	}
      
      /* checking line */
      tmp_pos = position;
      while(tmp_pos%nb_color!=0)
	tmp_pos--;
      tmp = tmp_pos;
      for(; tmp_pos < tmp + nb_color; ++tmp_pos)
	{
	  if(grid[tmp_pos] == color && grid[tmp_pos]!= 0xFF && tmp_pos != position)
	    return false;
	}

      /* checking blocks */
      tmp_pos = position;
      while(tmp_pos%d!=0)
	tmp_pos--;
      do 
	{
	  if(grid[tmp_pos] == color && grid[tmp_pos]!= 0xFF && tmp_pos != position)
	    return false;
	  ++tmp_pos;
	  if(tmp_pos % d == 0)
	    tmp_pos = tmp_pos + nb_color - d;
	} while (tmp_pos < d * nb_color);
    }
  return 1;
}

void
ordonnanceur()
{
  uint16_t position=0;
  pthread_t thread;

  
  grid_check();
  
  position = search_next_position(position);
  while(is_change)
    {
      
  pthread_create (&thread, NULL, max_solver, NULL);
 
  pthread_join(thread, NULL);
  }
  

  
}
 
 
void* max_solver(void* test)
{
  uint16_t d = sqrt(nb_color);
  uint16_t position = 0;
  uint16_t tmp_pos;
  uint16_t tmp;
  int nb_available = 0;
  uint16_t i;
  bool* c_available = malloc(nb_color * sizeof(bool));

  is_change=0;

  for(position = 0; position < (nb_color-1) * (nb_color); ++position)
    {
      for(i=0x00;i<nb_color;++i)
	c_available[i]=0x01;
      
      while(grid[position]!=0xFF && (nb_color-1) * nb_color )
	  position++;

      /* filling columns */
      tmp_pos = position % nb_color;
      for(; tmp_pos < nb_color * nb_color; tmp_pos = tmp_pos+nb_color)
	{
	  if(grid[tmp_pos]!= 0xFF)
	      c_available[(grid[tmp_pos]-48)]=0;
	  
	}
      
      /* filling line */
      tmp_pos = position;
      while(tmp_pos%nb_color!=0)
	tmp_pos--;
      tmp = tmp_pos;
      for(; tmp_pos < tmp + nb_color; ++tmp_pos)
	{
	  if(grid[tmp_pos]!= 0xFF)
	      c_available[(grid[tmp_pos]-48)]=0;
	}
      
      /* filling blocks */
      tmp_pos = position;
      while(tmp_pos%d!=0)
	tmp_pos--;
      do 
	{
	  if(grid[tmp_pos]!= 0xFF)
	      c_available[(grid[tmp_pos]-48)]=0;
      
	  ++tmp_pos;
	  if(tmp_pos % d == 0)
	    tmp_pos = tmp_pos + nb_color - d;
	} while (tmp_pos < d * nb_color);
      
      /* filling grid */
      nb_available = 0;
      for(i=0x00;i<nb_color;++i)
	{
	  if(c_available[i]==1)
	    {
	      tmp = i;
	      nb_available++;
	    }
	}
      if(nb_available==1)
	{
	  is_change=1;  
	  grid[position]=(tmp+48);
	}
    }
  return test;
}
