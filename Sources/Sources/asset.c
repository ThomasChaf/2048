// ****************************************************************************
//                                                                            *
//                                  ASSET C                                   *
//                                                                            *
// Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  28  /  09  /  2014  *
// ****************************************************************************

#include <stdarg.h>

#include "modulary.h"
#include "asset.h"

// ****************************************************************************
//                                                                            *
//                                    CLASS                                   *
//                                                                            *
// ****************************************************************************

char *__ASSET = "asset";

t_module __Asset =  { sizeof(t_asset), asset_ctor, asset_dtor,
  "asset",
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

int            asset_ctor(Asset this, va_list *ap)
{
  SDL_Renderer *renderer = va_arg(*ap, SDL_Renderer *);
  char          *path = va_arg(*ap, char *);

  if ((this->asset = SDL_LoadBMP(path)) == NULL)
    {
      LOG_ERROR(SDL_GetError());
      return (false);
    }
  this->texture = SDL_CreateTextureFromSurface(renderer, this->asset);
  return (true);
}

int            asset_dtor(Asset this)
{
  SDL_FreeSurface(this->asset);
  return (true);
}
