// ****************************************************************************
//                                                                            *
//                                   GAME C                                   *
//                                                                            *
// Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  28  /  09  /  2014  *
// ****************************************************************************

#include        <stdlib.h>
#include        <string.h>
#include        <time.h>

#include        "modulary.h"
#include        "game.h"
#include        "asset.h"
#include        "grid.h"

// ****************************************************************************
//                                                                            *
//                                  METHODS                                   *
//                                                                            *
// ****************************************************************************

/***
 * Main loop of the game
 ***/
static int      __launch(Game this)
{
  int           end = this->grid->rand_square(this->grid);
  SDL_Event     event;

  LOG_INFO("Game launch\n");
  if (this->render->display(this->render, this->grid, this->score, end) == false)
    return (false);
  while (42)
  {
    SDL_WaitEvent(&event);
    LOG_INFO("Game event\n");
    if (event.type == SDL_QUIT ||
       (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
      return (true);
    if (event.type == SDL_KEYDOWN && end == true)
      {
        end = this->grid->update(this->grid, this->score, event.key.keysym.sym);
        this->render->display(this->render, this->grid, this->score, end);
      }
  }
  LOG_INFO("End game\n");
  return (true);
}

// ****************************************************************************
//                                                                            *
//                                    CLASS                                   *
//                                                                            *
// ****************************************************************************

char *__GAME = "game";

t_module __Game = { sizeof(t_game), game_ctor, game_dtor,
  "game",
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

static void    __methods(Game this)
{
  this->__launch = __launch;
}

int            game_ctor(Game this)
{
  srand(time(NULL));
  DEFAULT_LOG("2048.log");
  if ((this->grid = new(__Grid)) == NULL
    || (this->score = new(__Score)) == NULL
    || (this->render = new(__Render)) == NULL)
    return (false);
  this->score->retrieve(this->score, this->render->ptr);
  __methods(this);
  return (true);
}

int            game_dtor(Game this)
{
  this->score->save(this->score);
  delete(this->score);
  delete(this->grid);
  delete(this->render);
  return (true);
}
