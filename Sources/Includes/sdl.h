// ****************************************************************************
//                                                                            *
//                                   SDL H                                    *
//                                                                            *
// Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  28  /  09  /  2014  *
// ****************************************************************************

#ifndef __SDL_H__
#define __SDL_H__

#include <SDL2/SDL.h>

#include "modulary.h"

#define WINDOW_TITLE "2048"

typedef struct         s_sdl
{
  t_module             module;
  SDL_Window           *window;
  fct                  create_window;
}                      t_sdl;

typedef t_sdl *        Sdl;

int                    sdl_ctor(Sdl);
int                    sdl_dtor();

extern t_module        __Sdl;

#endif /* __SDL_H__ */
