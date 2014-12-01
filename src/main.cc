/*
 * main.cc
 *
 *  Created on: Nov 13, 2014
 *      Author: vakz
 */

#include <SDL2/SDL.h>
#include <iostream>
#include <window.h>
#include <renderer.h>

void initialize(int height, int width) {
	Window window("title", height, width);

	Renderer renderer(window);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	renderer.set_logical_size(width, height);
	renderer.set_render_draw_color(0, 0, 0);
	renderer.clear();
	renderer.render_present();

	SDL_Delay(3000);

}

int main() {
	const int kWindowHeight = 800;
	const int kWindowWidth = 600;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cerr << "Error initializing SDL" << std::endl;
		exit(1);
	}
	initialize(kWindowHeight, kWindowWidth);

	SDL_Quit();
}
