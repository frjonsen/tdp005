/*
 * main.cc
 *
 *  Created on: Nov 13, 2014
 *      Author: vakz
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <sprite.h>
#include <surface.h>
#include <rectangle.h>
#include <vector>
#include "game_engine.h"
#include <iostream>
#include <tuple>
#include <map>
#include <utility>
#include "texture_handler.h"
/*
 void initialize(int width, int height)
 {

 Window window("GEEK HERO", width, height);
 Renderer renderer(window);

 Rectangle viewport(250, 0, width, height);
 renderer.set_logical_size (width, height);
 renderer.set_render_draw_color (0, 0, 0);

 renderer.clear ();

 SDL_Surface* temp = IMG_Load ("Geek_background.png");
 Texture text (renderer, temp);
 Rectangle rect (0, 0, temp->w, temp->h);
 Rectangle r = rect;
 r.set_x (-100);
 renderer.render_copy (text, rect, r);
 renderer.render_present ();

 SDL_Delay (3000);
 }
 */

enum class menupointer
{
  kPlay, kHighscore, kControls
};
// värden 0-2

void testeru(int width, int height)
{
  menupointer selected { menupointer::kPlay };

  std::map<menupointer, std::pair<int, int>> FREIDRICH { { menupointer::kPlay, {
      310, 240 } }, { menupointer::kHighscore, { 240, 315 } }, {
      menupointer::kControls, { 260, 385 } } };

  SDL_Window* window = SDL_CreateWindow ("GEEK HERO", SDL_WINDOWPOS_UNDEFINED,
  SDL_WINDOWPOS_UNDEFINED,
                                         width, height, SDL_WINDOW_RESIZABLE);
  SDL_Renderer* renderer = SDL_CreateRenderer (window, -1, 0);

  SDL_SetHint (SDL_HINT_RENDER_SCALE_QUALITY, "linear");
  SDL_RenderSetLogicalSize (renderer, width, height);

  SDL_Texture* wallpaper { nullptr };
  SDL_Texture* coffe_cup { nullptr };
  int wallpaper_width { 0 };
  int wallpaper_height { 0 };
  int coffe_width { 0 };
  int coffe_height { 0 };

  {
    SDL_Surface* temp = IMG_Load ("Geek_background.png");

    wallpaper = SDL_CreateTextureFromSurface (renderer, temp);

    wallpaper_width = temp->w;
    wallpaper_height = temp->h;
    SDL_FreeSurface (temp);

    temp = IMG_Load ("coffe.png");
    coffe_cup = SDL_CreateTextureFromSurface (renderer, temp);
    coffe_width = temp->w;
    coffe_height = temp->h;
    SDL_FreeSurface (temp);
  }

  SDL_Rect coffe_rect;

  coffe_rect.x = std::get<0> (FREIDRICH.at (selected)); //1: 310x240 2: 240x315 3: 260x385
  coffe_rect.y = std::get<1> (FREIDRICH.at (selected));
  coffe_rect.w = coffe_width;
  coffe_rect.h = coffe_height;

  SDL_Rect wall_rect;

  wall_rect.x = 0;
  wall_rect.y = 0;
  wall_rect.w = wallpaper_width;
  wall_rect.h = wallpaper_height;

  bool running { true };
  while (running)
  {
    SDL_Event event;
    while (SDL_PollEvent (&event))
    {
      if (event.type == SDL_QUIT)
      {
        running = false;
      }
      else if (event.type == SDL_KEYDOWN)
      {
        if (event.key.keysym.sym == SDLK_UP)
        {
          selected = menupointer::kHighscore;
          std::cout << "upp" << std::endl;
        }
        if (event.key.keysym.sym == SDLK_RIGHT)
        {
          selected = menupointer::kControls;
          std::cout << "höger" << std::endl;
        }
        if (event.key.keysym.sym == SDLK_DOWN)
        {
          selected = menupointer::kPlay;
          std::cout << "ned" << std::endl;
        }
      }
    }
    coffe_rect.x = std::get < 0 > (FREIDRICH.at (selected)); //1: 310x240 2: 240x315 3: 260x385
    coffe_rect.y = std::get < 1 > (FREIDRICH.at (selected));


    SDL_SetRenderDrawColor (renderer, 0, 0, 0, 255);
    SDL_RenderClear (renderer);

    SDL_RenderCopy (renderer, wallpaper, nullptr, &wall_rect);
    SDL_RenderCopy (renderer, coffe_cup, nullptr, &coffe_rect);

    SDL_RenderPresent (renderer);
    SDL_Delay (10);
  }

  SDL_DestroyTexture (wallpaper);
  wallpaper = nullptr;
  SDL_DestroyTexture (coffe_cup);
  coffe_cup = nullptr;
  SDL_DestroyRenderer (renderer);
  SDL_DestroyWindow (window);

//	SDL_Quit();
}

void initialize(int width, int height)
{
  GraphicsEngine::Viewport v { 120, 0 };

  GraphicsEngine ge ("Geek Hero", width, height);
  std::vector<Sprite const*> sprites;

  ge.set_background ("TESTGROUND.png");
  Rectangle enclosing { 110, 395 - 50, 30, 50 };
  Sprite sf { "Hero_Standing_R.png", enclosing, { 0, 0 } };
  sprites.push_back (&sf);

  ge.set_viewport (v);
  ge.redraw_screen (sprites);

  SDL_Delay (3000);
}

int main()
{
  if (SDL_Init (SDL_INIT_VIDEO) != 0)
  {
    std::runtime_error ("Failed to initialize SDL");
    exit (1);
  }
  
  //initialize (kWindowWidth, kWindowHeight);
  testeru(800, 600);

  GameEngine game_engine;
  game_engine.run ();
}
