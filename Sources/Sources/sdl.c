// ****************************************************************************
//                                                                            *
//                                   SDL C                                    *
//                                                                            *
// Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  28  /  09  /  2014  *
// ****************************************************************************

#include        <stdlib.h>

#include        "modulary.h"
#include        "sdl.h"

// ****************************************************************************
//                                                                            *
//                                    CLASS                                   *
//                                                                            *
// ****************************************************************************

char *__SDL = "sdl";

t_module __Sdl =  { sizeof(t_sdl), sdl_ctor, sdl_dtor,
  "sdl",
  0,
  0,
  0,
  0,
  0,
  0
};

// ****************************************************************************
//                                                                            *
//                                  CTOR/DTOR                                 *
//                                                                            *
// ****************************************************************************

int            sdl_ctor(Sdl this)
{
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0
   || (this->window = SDL_CreateWindow(WINDOW_TITLE,
                                       SDL_WINDOWPOS_UNDEFINED,
                                       SDL_WINDOWPOS_UNDEFINED,
                                       1000, 1000,
                                       SDL_WINDOW_FULLSCREEN)
                                      ) == NULL)
    {
      LOG_ERROR("%s\n", SDL_GetError());
      return (false);
    }
  return (true);
}

int            sdl_dtor(Sdl this)
{
  SDL_DestroyWindow(this->window);
  SDL_Quit();
  return (true);
}
