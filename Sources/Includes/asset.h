// ****************************************************************************
//                                                                            *
//                                  ASSET H                                   *
//                                                                            *
// Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  28  /  09  /  2014  *
// ****************************************************************************

#ifndef __ASSET_H__
#define __ASSET_H__

#include <SDL2/SDL.h>
#include <stdarg.h>

#include "modulary.h"

enum           e_asset
{
  _2,
  _4,
  _8,
  _16,
  _32,
  _64,
  _128,
  _256,
  _512,
  _1024,
  _2048,
  _4096,
  BACKGROUND,
  EMPTY,
  GAME_OVER,
  LEN_ASSET
};

typedef struct         s_asset
{
  t_module             module;
  SDL_Surface          *asset;
  SDL_Texture          *texture;
}                      t_asset;

typedef t_asset *      Asset;

int                    asset_ctor(Asset, va_list *);
int                    asset_dtor();

extern t_module        __Asset;

#endif /* __GAME_H__ */
