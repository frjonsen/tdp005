/*
 * surface.h
 *
 *  Created on: Nov 24, 2014
 *      Author: frejo105
 */

#ifndef SURFACE_H_
#define SURFACE_H_

#include <SDL2/SDL.h>

/**
 * Wrapper for SDL_Surface
 */
class Surface
{
public:
  /**
   * Initialize surface
   * @param surface Pointer to SDL_Surface* to handle
   */
	Surface(SDL_Surface* surface);
	~Surface();

	/// Deleted copy constructor
	Surface(Surface const&) = delete;

	/// Deleted assignment operator
	Surface& operator=(Surface const&) = delete;

	/// Get the internal SDL_Surface pointer
	SDL_Surface* get_surface();

	/// Get surface width
	int get_width() const;

	/// Get surface hight
	int get_height() const;

private:
	/// Internal SDL_Surface pointer
	SDL_Surface* surface_;
};


#endif /* SURFACE_H_ */
