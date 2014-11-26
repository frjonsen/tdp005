/*
 * surface.cc
 *
 *  Created on: Nov 24, 2014
 *      Author: frejo105
 */

#include "surface.h"

Surface::Surface(SDL_Surface* surface) : surface_{surface}
{ }

SDL_Surface* Surface::get_surface()
{
	return surface_;
}

Surface::~Surface()
{
	SDL_FreeSurface(surface_);
}
