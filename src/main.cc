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
#include <graphics_engine.h>
#include <iostream>

/*
void initialize(int width, int height) {

	Window window("GEEK HERO", width, height);
	Renderer renderer(window);

	Rectangle viewport(250, 0, width, height);


	renderer.set_logical_size(width, height);
	renderer.set_render_draw_color(0, 0, 0);

	renderer.clear();

	SDL_Surface* temp = IMG_Load("Geek_background.png");
	Texture text(renderer, temp);
	Rectangle rect(0, 0, temp->w, temp->h);
	renderer.render_copy(text, rect, rect);
	renderer.render_present();

	SDL_Delay(3000);

}

*/

void initialize(int width, int height)
{
  Window window("Geek Hero", width, height);
  Renderer renderer (window);
  GraphicsEngine::Viewport v{10, 0};

  renderer.set_logical_size(width, height);
  renderer.set_render_draw_color(0, 0, 0);

  GraphicsEngine ge("Geek Hero", width, height);
  Surface sur{IMG_Load("Geek_background.png")};
  Sprite s{ge.get_renderer(), sur, 0, 0, sur.get_width(), sur.get_height()};
  std::vector<Sprite const*> sprites;
  sprites.push_back(&s);

  ge.set_viewport(v);
  ge.redraw_screen(sprites);
}

int main() {
	const int kWindowHeight = 600;
	const int kWindowWidth = 800;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cerr << "Error initializing SDL" << std::endl;
		exit(1);
	}
	initialize(kWindowWidth, kWindowHeight);

	SDL_Quit();
}
