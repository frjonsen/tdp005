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
#include <SDL2/SDL_ttf.h>
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
  }
}


int main()
{
  if (SDL_Init (SDL_INIT_VIDEO) != 0)
  {
    std::runtime_error ("Failed to initialize SDL");
    exit (1);
  }
  TTF_Init();
  GameEngine game_engine;
  game_engine.run ();
}
