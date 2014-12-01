// ****************************************************************************
//                                                                            *
//                                   GRID C                                   *
//                                                                            *
// Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  28  /  09  /  2014  *
// ****************************************************************************

#include        <SDL2/SDL.h>
#include        <stdarg.h>
#include        <stdlib.h>

#include        "modulary.h"
#include        "asset.h"
#include        "score.h"
#include        "grid.h"

// ****************************************************************************
//                                                                            *
//                                  METHODS                                   *
//                                                                            *
// ****************************************************************************

/***
 *  Check if a moove is possible
 ***/
static int     __end_game(Grid this)
{
  int          i = 0;

  while (i < GRID_X * GRID_Y)
  {
    if (this->grid[i] == 0
      || (i % 4 != 3 && this->grid[i] == this->grid[i + 1])
      || (i < 12 && this->grid[i] == this->grid[i + 4]))
        return (true);
    i++;
  }
  LOG_INFO("End game detected\n");
  return (false);
}

/***
 * Count the number of occurence of the given value
 *
 * @value : researched value
 ***/
static int      __count(Grid this, int value)
{
  int          i = 0;
  int          len = 0;

  while (i < GRID_X * GRID_Y)
  {
    if (this->grid[i] == value)
      len++;
    i++;
  }
  return (len);
}

/***
 * Add a random square on the grid
 ***/
static int      __rand_square(Grid this)
{
  int           i = 0;
  int           n = this->count(this, 0);

  if (n == 0)
    return (false);
  n = rand() % n + 1;
  while (i < GRID_X * GRID_Y && n > 0)
  {
    if (this->grid[i] == 0)
      {
        n--;
        if (n == 0)
          this->grid[i] = 2;
      }
    i++;
  }
  return (true);
}

/***
 * Delete the shift between two square
 * ex: key pressed: '->' line: [2, ,4,16]
 *     result: [ ,2,4,16]
 ***/
static int      __delete_shift(Grid this, int index, int next_square)
{
  int           i = index;
  int           last_index;
  int           next;

  while (i != index + 3 * next_square)
    {
      last_index = i;
      next = i + next_square;
      if (this->grid[i] == 0 && this->grid[next] != 0)
        {
          this->has_movement = true;
          while (this->grid[i - next_square] == 0 && i != index)
            i -= next_square;
          this->grid[i] = this->grid[next];
          this->grid[next] = 0;
        }
      i = last_index + next_square;
    }
  return (true);
}

/***
 * Merge neighboors square with same contents
 * ex: key pressed: '->' line: [2,4,4,16]
 *     result: [ ,2,8,16]
 ***/
static int      __merge(Grid this, int index, int next_square)
{
  int           i = index;
  int           last_index;
  int           next;
  int           score = 0;

  while (i != index + 3 * next_square)
    {
      last_index = i;
      next = i + next_square;
      if (this->grid[i] == this->grid[next] && this->grid[i] != 0)
      {
        this->has_movement = true;
        this->grid[i] *= 2;
        score += this->grid[i];
        i = next;
        while (i != index + 3 * next_square)
          {
            this->grid[i] = this->grid[i + next_square];
            i += next_square;
          }
        this->grid[i] = 0;
      }
      i = last_index + next_square;
    }
  return (score);
}


/***
 * Update the line at the given index. Could be a column or a row
 *
 * @index : index of the updated line
 * @next_square : direction to the next square on the line
 ***/
static int      __update_line(Grid this, int index, int next_square)
{
  this->delete_shift(this, index, next_square);
  return (this->merge(this, index, next_square));
}

static int      mooves[5][4]=
{
  {  SDLK_LEFT,  0,  4,  1},
  { SDLK_RIGHT,  3,  4, -1},
  {  SDLK_DOWN, 12,  1, -4},
  {    SDLK_UP,  0,  1,  4},
  {          0,  0,  0,  0},
};

static int      __update(Grid this, Score score, int key_code)
{
  int           l;
  int           i = 0;
  int           s = 0;

  this->has_movement = false;
  while (i < 4)
    {
      if (mooves[i][0] == key_code)
        {
          l = 0;
          while (l < 4)
            s += this->update_line(this, mooves[i][1] + l++ * mooves[i][2], mooves[i][3]);
          sum(score, &s);
          if (this->has_movement == false)
            return (true);
          this->rand_square(this);
          return (this->end_game(this));
        }
      i++;
    }
  return (true);
}

// ****************************************************************************
//                                                                            *
//                            BUILT_IN METHODS                                *
//                                                                            *
// ****************************************************************************

static char    *__str(Grid this)
{
  int          i = 0;

  while (i < GRID_X * GRID_Y)
    {
      printf("%d\t", this->grid[i]);
      if (i % GRID_X == GRID_X - 1)
        printf("\n");
      i++;
    }
  printf("==================================\n");
  return (NULL);
}

// ****************************************************************************
//                                                                            *
//                                    CLASS                                   *
//                                                                            *
// ****************************************************************************

char *__GRID = "grid";

t_module __Grid = { sizeof(t_grid), grid_ctor, grid_dtor,
  "grid",
  0,
  0,
  __str,
  0,
  0,
  0
};

// ****************************************************************************
//                                                                            *
//                                  CTOR/DTOR                                 *
//                                                                            *
// ****************************************************************************

static void    __methods(Grid this)
{
  this->update = __update;
  this->update_line = __update_line;
  this->count = __count;
  this->rand_square = __rand_square;
  this->end_game = __end_game;
  this->delete_shift = __delete_shift;
  this->merge = __merge;
}

int            grid_ctor(Grid this)
{
  int          i = 0;

  while (i < GRID_X * GRID_Y)
    this->grid[i++] = 0;
  __methods(this);
  return (true);
}

int            grid_dtor(Grid ptr)
{
  (void)ptr;
  return (true);
}
