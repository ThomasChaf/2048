// ****************************************************************************
//                                                                            *
//                                   MAIN C                                   *
//                                                                            *
// Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  28  /  09  /  2014  *
// ****************************************************************************

#include <stdlib.h>
#include <unistd.h>

#include "modulary.h"
#include "game.h"

/***
 * Instancy a game and launch it.
 ***/
int      main()
{
  Game   game = new(__Game);

  if (game == NULL)
    return (EXIT_FAILURE);
  launch(game);
  delete(game);
  return (EXIT_SUCCESS);
}
