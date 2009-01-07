#include "ordonnanceur.h"

void* max_solver(void*);
 
uint16_t
look_for_next_position(uint16_t position)
{
  uint16_t i=position;
  for(;i<=nb_color*nb_color;++i)
    {
      if(grid[i]==0xFFFF)
	return i; 
    }
  return i;
}
 
void
ordonnanceur()
{
  uint16_t position=0;
  pthread_t thread;

  
  position = look_for_next_position(position);
  pthread_create (&thread, NULL, max_solver, NULL);
 
  pthread_join(thread, NULL);
}
 
 
void* max_solver(void* test)
{
  return test;
}
