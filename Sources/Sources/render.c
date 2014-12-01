// ****************************************************************************
//                                                                            *
//                                  RENDER C                                  *
//                                                                            *
// Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  28  /  09  /  2014  *
// ****************************************************************************

#include <stdarg.h>

#include "modulary.h"
#include "render.h"
#include "score.h"
#include "grid.h"

// ****************************************************************************
//                                                                            *
//                                  METHODS                                   *
//                                                                            *
// ****************************************************************************

static int values[]=
{
  2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, -1
};

/***
 * Find in the cache the asset matching the value
 ***/
static SDL_Texture  *texture_from_value(Render this, int value)
{
  int               i = 0;

  while (values[i] > 0)
    {
      if (values[i] == value)
        return (this->asset[i]->texture);
      i++;
    }
  return (this->asset[EMPTY]->texture);
}

/***
 * Refresh the screen and display the grid and the score
 ***/
static int          display(Render this, Grid grid, Score score, int end)
{
  int               i = 0;
  SDL_Texture       *texture;
  SDL_Rect          dest;

  if (SDL_RenderClear(this->ptr) < 0)
    {
      LOG_ERROR("%s\n", SDL_GetError());
      return (false);
    }
  SDL_RenderCopy(this->ptr, this->asset[BACKGROUND]->texture, NULL, NULL);
  while (i < GRID_X * GRID_Y)
    {
      if (grid->grid[i] != 0)
        {
          dest.x = 30 + 242.5 * X(i);
          dest.y = 430 + 242.5 * Y(i);
          dest.w = 212;
          dest.h = 212;
          texture = this->texture_from_value(this, grid->grid[i]);
          SDL_RenderCopy(this->ptr, texture, NULL, &dest);
        }
      i++;
    }
  if (end == false)
    {
      dest.x = 0;
      dest.y = 400;
      dest.w = 1000;
      dest.h = 1000;
      SDL_RenderCopy(this->ptr, this->asset[GAME_OVER]->texture, NULL, &dest);
    }
  score->display(score, this->ptr);
  SDL_RenderPresent(this->ptr);
  return (true);
}

// ****************************************************************************
//                                                                            *
//                                    CLASS                                   *
//                                                                            *
// ****************************************************************************

char *__RENDER = "render";

t_module __Render = { sizeof(t_render), render_ctor, render_dtor,
  "render",
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

static void         __methods(Render this)
{
  this->display = display;
  this->texture_from_value = (pfct)texture_from_value;
}

char   *paths[]=
{
  "../Resources/assets/2.bmp",
  "../Resources/assets/4.bmp",
  "../Resources/assets/8.bmp",
  "../Resources/assets/16.bmp",
  "../Resources/assets/32.bmp",
  "../Resources/assets/64.bmp",
  "../Resources/assets/128.bmp",
  "../Resources/assets/256.bmp",
  "../Resources/assets/512.bmp",
  "../Resources/assets/1024.bmp",
  "../Resources/assets/2048.bmp",
  "../Resources/assets/4096.bmp",
  "../Resources/assets/background.bmp",
  "../Resources/assets/empty.bmp",
  "../Resources/assets/game_over.bmp"
};

int                 render_ctor(Render this)
{
  int               i = 0;

  if ((this->sdl = new(__Sdl)) == NULL)
    return (false);
  LOG_INFO("Create render\n");
  if ((this->ptr = SDL_CreateRenderer(this->sdl->window, -1, 0)) == NULL)
    {
      LOG_ERROR("%s\n", SDL_GetError());
      return (false);
    }
  SDL_SetRenderDrawColor(this->ptr, 250, 248, 239, 255);
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
  SDL_RenderSetLogicalSize(this->ptr, 1000, 1400);
  while (i < LEN_ASSET)
    {
      if ((this->asset[i] = new(__Asset, this->ptr, paths[i])) == NULL)
        {
          LOG_ERROR("Can't load the asset %s\n", paths[i]);
          return (false);
        }
      i++;
    }
  __methods(this);
  return (true);
}

int                 render_dtor(Render this)
{
  delete(this->sdl);
  return (true);
}
