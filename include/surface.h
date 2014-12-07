/*
 * surface.h
 *
 *  Created on: Nov 24, 2014
 *      Author: frejo105
 */

#ifndef SURFACE_H_
#define SURFACE_H_

#include <SDL2/SDL.h>

class Surface
{
public:
	Surface(SDL_Surface* surface);
	Surface& operator=(Surface const&) = delete;
	~Surface();

	Surface(Surface const&) = delete;

	SDL_Surface* get_surface();
	int get_width() const;
	int get_height() const;

private:
	SDL_Surface* surface_;
};


#endif /* SURFACE_H_ */
