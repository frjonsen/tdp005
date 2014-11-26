/*
 * rectangle.h
 *
 *  Created on: Nov 24, 2014
 *      Author: frejo105
 */

#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include <SDL2/SDL.h>

class Rectangle
{
public:
	Rectangle(const int x, const int y, const int width, const int height);
	~Rectangle();
	SDL_Rect* get_rect();
	const SDL_Rect* get_rect() const;

	Rectangle(Rectangle const&) = delete;
	Rectangle& operator=(Rectangle const&) = delete;
private:
	SDL_Rect* rect_;
};


#endif /* RECTANGLE_H_ */
