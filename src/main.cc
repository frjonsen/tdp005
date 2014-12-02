/*
 * main.cc
 *
 *  Created on: Nov 13, 2014
 *      Author: vakz
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <window.h>
#include <renderer.h>
#include <texture.h>
#include <rectangle.h>


void initialize(int width, int height) {
	Window window("title", width, height);
	Renderer renderer(window);
	renderer.set_logical_size(width, height);
	renderer.set_render_draw_color(0, 0, 0);
	renderer.clear();
	SDL_Surface* temp = IMG_Load("Geek_background.jpg");
	Texture text(renderer, temp);
	Rectangle rect(0, 0, temp->w, temp->h);
	renderer.render_copy(text, rect, rect);
	renderer.render_present();


	SDL_Delay(3000);

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
