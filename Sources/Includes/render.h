// ****************************************************************************
//                                                                            *
//                                  RENDER H                                  *
//                                                                            *
// Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  28  /  09  /  2014  *
// ****************************************************************************

#ifndef __RENDER_H__
#define __RENDER_H__

#include <SDL2/SDL.h>
#include <stdarg.h>

#include "modulary.h"
#include "sdl.h"
#include "asset.h"

typedef struct   s_render
{
  t_module       module;
  Sdl            sdl;
  SDL_Renderer   *ptr;
  Asset          asset[LEN_ASSET];
  fct            display;
  pfct           texture_from_value;
}                t_render;

typedef t_render * Render;

int              render_ctor(Render);
int              render_dtor();

#define X(x) (x % GRID_X)
#define Y(x) (x / GRID_X)

extern t_module  __Render;

#endif /* __RENDER_H__ */
