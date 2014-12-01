// ****************************************************************************
//                                                                            *
//                                  SCORE C                                   *
//                                                                            *
// Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  28  /  09  /  2014  *
// ****************************************************************************

#include <fcntl.h>

#include "modulary.h"
#include "score.h"

// ****************************************************************************
//                                                                            *
//                                  METHODS                                   *
//                                                                            *
// ****************************************************************************

/***
 * Convert int to string
 ***/
char    *m_itoa(int value)
{
  char  result[10];
  int   i = 9;
  int   _value = (value >= 0 ? value : -1 * value);

  result[i--] = 0;
  while (_value >= 10)
    {
      result[i--] = _value % 10 + 48;
      _value /= 10;
    }
  result[i--] = _value % 10 + 48;
  if (value < 0)
    result[i--] = '-';
  while (i >= 0)
    result[i--] = ' ';
  return (m_strdup(result));
}

/***
 * Retrieve the best score saved in the cache file
 ***/
static int      __retrieve(Score this, void *render)
{
  Json          data = NULL;
  Stream        file = NULL;
  SDL_Surface   *surface = NULL;
  char          *best = NULL;

  if ((file = new(__Stream, m_open(".save", O_RDONLY))) == NULL
    || (data = new(__Json, file)) == NULL
    || data->json_decode(data) == false
    || (best = data->json_get(data, new(__String, "score"), NULL)) == NULL)
    best = NULL;
  this->best = INT(best);
  LOG_INFO("Retrieve best score [%d]\n", this->best);
  if ((surface = TTF_RenderText_Blended(this->font, (best ? best : "0"), this->color)) == NULL
    || (this->texture = SDL_CreateTextureFromSurface(render, surface)) == NULL)
    {
      LOG_ERROR("%s\n", SDL_GetError());
      return (false);
    }
  SDL_QueryTexture(this->texture, NULL, NULL, &this->rect.w, &this->rect.h);
  this->rect.x = 800;
  this->rect.y = 120;
  delete(data);
  delete(file);
  return (true);
}

/***
 * Save the score if the player beat his record.
 ***/
static int      __save(Score this)
{
  Stream        file;

  LOG_INFO("Save best score [%d]\n", this->score);
  if (this->best >= this->score)
    return (true);
  if ((file = new(__Stream, m_create(".save"))) == NULL)
    {
      LOG_ERROR("Can't creat stream\n");
      return (false);
    }
  file->write(file, "{ \"score\": %d }", this->score);
  return (true);
}

/***
 * Display and refresh the score of the player
 ***/
static int      __display(Score this, void *render)
{
  char          *_score = m_itoa(this->score);
  SDL_Surface   *surface;
  SDL_Texture   *texture;
  SDL_Rect      dest;

  if (_score == NULL)
    return (false);
  LOG_INFO("Score display\n");
  if ((surface = TTF_RenderText_Blended(this->font, _score, this->color)) == NULL
    || (texture = SDL_CreateTextureFromSurface(render, surface)) == NULL)
    {
      LOG_ERROR("%s\n", SDL_GetError());
      return (false);
    }
  SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
  dest.x = 480;
  dest.y = 120;
  SDL_RenderCopy(render, texture, NULL, &dest);
  SDL_RenderCopy(render, this->texture, NULL, &this->rect);
  free(_score);
  return (true);
}

// ****************************************************************************
//                                                                            *
//                            BUILT_IN METHODS                                *
//                                                                            *
// ****************************************************************************

static Objet   __sum(Score this, int *sum)
{
  this->score += *sum;
  return (this);
}

// ****************************************************************************
//                                                                            *
//                                    CLASS                                   *
//                                                                            *
// ****************************************************************************

char *__SCORE = "score";

t_module __Score =  { sizeof(t_score), score_render_ctor, score_render_dtor,
  "score",
  0,
  __sum,
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

static void    __methods(Score this)
{
  this->display = __display;
  this->retrieve = __retrieve;
  this->save = __save;
}

int            score_render_ctor(Score this)
{
  if (TTF_Init() != 0
    || (this->font = TTF_OpenFont("assets/ClearSans-Medium.ttf", 42)) == NULL)
    {
      LOG_ERROR("%s\n", SDL_GetError());
      return (false);
    }
  this->score = 0;
  this->color.r = 255;
  this->color.g = 255;
  this->color.b = 255;
  this->color.a = 0;
  __methods(this);
  return (true);
}

int            score_render_dtor(Score this)
{
  (void)this;
  return (true);
}
