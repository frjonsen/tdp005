/*
 * main.cc
 *
 *  Created on: Nov 13, 2014
 *      Author: vakz
 */

#include <SDL2/SDL.h>
#include "game_engine.h"
#include <SDL2/SDL_ttf.h>

int main()
{
  // Initiate SDL. Must be done here
  // since GameEngine will attempt to create use SDL
  // functions before there is an opportunity to initialize.
  if (SDL_Init (SDL_INIT_VIDEO) != 0)
  {
    std::runtime_error ("Failed to initialize SDL");
    exit (1);
  }
  TTF_Init();
  GameEngine game_engine;
  game_engine.run ();
}
