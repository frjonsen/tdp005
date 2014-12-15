/*
 * main.cc
 *
 *  Created on: Nov 13, 2014
 *      Author: vakz
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "game_engine.h"
#include "texture_handler.h"


int main()
{
  if (SDL_Init (SDL_INIT_VIDEO) != 0)
  {
    std::runtime_error ("Failed to initialize SDL");
    exit (1);
  }

  GameEngine game_engine;
  game_engine.run ();
}
