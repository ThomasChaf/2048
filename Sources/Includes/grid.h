// ****************************************************************************
//                                                                            *
//                                   GRID H                                   *
//                                                                            *
// Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  28  /  09  /  2014  *
// ****************************************************************************

#ifndef __GRID_H__
#define __GRID_H__

#include "modulary.h"

#define GRID_X (4)
#define GRID_Y (4)

typedef struct      s_grid
{
  t_module          module;
  int               grid[GRID_X * GRID_Y];
  int               has_movement;
  fct               update;
  fct               update_line;
  fct               count;
  fct               rand_square;
  fct               end_game;
  fct               delete_shift;
  fct               merge;
}                   t_grid;

typedef t_grid *    Grid;

int                 grid_ctor(Grid);
int                 grid_dtor(Grid);

extern t_module     __Grid;

#endif /* __GRID_H__ */
