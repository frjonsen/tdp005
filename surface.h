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
	~Surface();
	SDL_Surface* get_surface();
	Surface(Surface const&) = delete;

	Surface& operator=(Surface const&) = delete;

private:
	SDL_Surface* surface_;
};


#endif /* SURFACE_H_ */
