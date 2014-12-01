// ****************************************************************************
//                                                                            *
//                                  SCORE H                                   *
//                                                                            *
// Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  28  /  09  /  2014  *
// ****************************************************************************

#ifndef __SCORE_H__
#define __SCORE_H__

#include <SDL2/SDL.h>
#include "SDL_ttf.h"

#include "modulary.h"

typedef struct   s_score
{
  t_module       module;
  int            best;
  int            score;
  SDL_Texture    *texture;
  SDL_Rect       rect;
  TTF_Font       *font;
  SDL_Color      color;
  fct            display;
  fct            retrieve;
  fct            save;
}                t_score;

typedef t_score * Score;

int              score_render_ctor(Score);
int              score_render_dtor();

extern t_module  __Score;

#endif /* __SCORE_H__ */
