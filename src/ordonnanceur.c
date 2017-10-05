#include "ordonnanceur.h"

void* max_solver(void*);


void Init(stack *l)
{
   l->first = NULL;
   l->last = NULL;
}

void PushBack(stack *l, pthread_t val)
{
   elem *new = malloc(sizeof(elem));
   if(!new){
     perror(0);
     exit(1);
   }
   
   new->fred = val;
   new->prev = l->last;
   new->next = NULL;
   if(l->last) 
     l->last->next = new;
   else 
     l->first = new;
   l->last = new;        
}


void PushFront(stack *l, pthread_t val)
{
   elem *new = malloc(sizeof(elem));
   if(!new)
     {
       perror(0);
       exit(1);
     }
   new->fred = val;
   new->next = l->first;
   new->prev = NULL;      
   if(l->first) 
     l->first->prev = new;
   else 
     l->last = new;
   l->first = new;
}

pthread_t PopBack(stack *l)
{
   pthread_t val;
   elem *tmp = l->last;
   if(!tmp) return -1;
   val = tmp->fred;
   l->last = tmp->prev;
   if(l->last) l->last->next = NULL;
   else l->first = NULL;
   free(tmp);
   return val;
}

pthread_t PopFront(stack *l)
{
   pthread_t val;
   elem *tmp = l->first;
   if(!tmp) return -1;
   val = tmp->fred;
   l->first = tmp->next;
   if(l->first)l->first->prev = NULL;
   else l->last = NULL;
   free(tmp);
   return val;
}

uint16_t search_next_position(uint16_t position, uint16_t* grid) {
  uint16_t index = position;

  for(;index <= nb_color * nb_color; ++index) {
    if (grid[index] == 0xFF) {
      return index;
    }
  }

  return index;
}
 
bool grid_check(uint16_t* grid) {
  uint16_t d = sqrt(nb_color);
  uint16_t position = 0;
  uint16_t color;
  uint16_t tmp_pos;
  uint16_t tmp;

  /* reach every position */
  for (position = 0; position < ((nb_color-1) * nb_color); ++position) {
    while (grid[position]==0xFF && position < ((nb_color-1) * nb_color)) {
      position++;
    }

    color = grid[position];

    if (position >= (nb_color * nb_color)) {
      return 1;
    }

    /* checking columns */
    tmp_pos = position % nb_color;

    for (; tmp_pos < nb_color * nb_color; tmp_pos = tmp_pos + nb_color) {
	    if (grid[tmp_pos] == color && grid[tmp_pos] != 0xFF && tmp_pos != position) {
        return false;
      }
	  }
      
    /* checking line */
    tmp_pos = position;
    while ((tmp_pos % nb_color) != 0) {
      tmp_pos--;
    }

    tmp = tmp_pos;
    for(; tmp_pos < (tmp + nb_color); ++tmp_pos) {
      if(grid[tmp_pos] == color && grid[tmp_pos] != 0xFF && tmp_pos != position) {
        return false;
      }
	  }

    /* checking blocks */
    tmp_pos = position;

    while ((tmp_pos % d) != 0) {
      tmp_pos--;
    }

    do {
	    if (grid[tmp_pos] == color && grid[tmp_pos]!= 0xFF && tmp_pos != position) {
        return false;
      }

      ++tmp_pos;

	    if ((tmp_pos % d) == 0) {
        tmp_pos = tmp_pos + nb_color - d;
      }
	  } while (tmp_pos < (d * nb_color));
  }

  return 1;
}

void
ordonnanceur(uint16_t* grid)
{
  int index;
  pthread_t* thread = malloc(nb_color*sizeof(pthread_t));
  pthread_t tmp;
  pthread_attr_t new_attr;
  pthread_mutex_t verrou;
 
  if (grid_check(grid)) {
    pthread_attr_init(&new_attr);
    pthread_attr_setschedpolicy(&new_attr,SCHED_RR);

    Init(&My_stack);

    pthread_mutex_init(&verrou,NULL);
    
    for (index = 0; index < nb_color; ++index) {
      PushBack(&My_stack,thread[index]);
    }

    while (is_change!=0) {
      tmp=PopFront(&My_stack);
      pthread_mutex_lock (&verrou);      
      pthread_create (&tmp, &new_attr,max_solver, grid);
      pthread_join(tmp, NULL);
      pthread_mutex_unlock (&verrou);      
      PushBack(&My_stack,tmp);
    }
  }
}

void* max_solver(void* test) {
  uint16_t d = sqrt(nb_color);
  uint16_t position = 0;
  uint16_t tmp_pos;
  uint16_t tmp;
  int nb_available = 0;
  uint16_t index;
  bool* c_available = malloc(nb_color * sizeof(bool));
  uint16_t* grid = (uint16_t *)test;
  
  is_change=0;
  
  for (position = 0; position < (nb_color-1) * (nb_color); ++position) {
    for (index = 0x00; index < nb_color; ++index) {
      c_available[index] = 0x01;
    }
    
    while (grid[position] != 0xFF && position < ((nb_color-1) * nb_color)) {
      position++;
    }

    /* filling columns */
    tmp_pos = position % nb_color;

    for (; tmp_pos < (nb_color * nb_color); tmp_pos = tmp_pos + nb_color) {
      if (grid[tmp_pos] != 0xFF) {
        if(grid[tmp_pos]> 57) {
          c_available[(grid[tmp_pos]-65)] = 0;
        } else {
          c_available[(grid[tmp_pos]-48)] = 0;
        }
      }
    }
    
    /* filling line */
    tmp_pos = position;

    while ((tmp_pos % nb_color) != 0) {
      tmp_pos--;
    }

    tmp = tmp_pos;

    for (; tmp_pos < tmp + nb_color; ++tmp_pos) {
      if (grid[tmp_pos]!= 0xFF) {
        if (grid[tmp_pos]> 57) {
          c_available[(grid[tmp_pos]-65)] = 0;
        } else {
          c_available[(grid[tmp_pos]-48)] = 0;
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
        if(grid[tmp_pos] > 57) {
          c_available[(grid[tmp_pos]-65)] = 0;
        } else {
          c_available[(grid[tmp_pos]-48)] = 0;
        }
      }

      ++tmp_pos;

      if (tmp_pos % d == 0) {
        tmp_pos = tmp_pos + nb_color - d;
      }
    } while (tmp_pos < (d * nb_color));
    
    /* filling grid */
    nb_available = 0;
    for (index = 0x00; index < nb_color; ++index) {
      if (c_available[index] == 1) {
        tmp = index;
        nb_available++;
      }
    }

    if (nb_available == 1) {
      is_change = 1;

      if ((tmp + 48) > 57) {
        grid[position] = tmp + 65;
      } else {
        grid[position] = tmp + 48;
      }
    }
  }

  return test;
}
