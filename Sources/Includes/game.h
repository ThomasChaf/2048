// ****************************************************************************
//                                                                            *
//                                   GAME H                                   *
//                                                                            *
// Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  28  /  09  /  2014  *
// ****************************************************************************

#ifndef __GAME_H__
#define __GAME_H__

#include <SDL2/SDL.h>

#include "modulary.h"
#include "render.h"
#include "score.h"
#include "grid.h"

typedef struct         s_game
{
  t_module             module;
  Render               render;
  Score                score;
  Grid                 grid;
  fct                  __launch;
}                      t_game;

typedef t_game *       Game;

int                    game_ctor(Game);
int                    game_dtor();

#define launch(x) ((Game)x)->__launch(x);

extern t_module        __Game;

#endif /* __GAME_H__ */
