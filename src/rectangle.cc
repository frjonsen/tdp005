/*
 * rectangle.cc
 *
 *  Created on: Nov 24, 2014
 *      Author: frejo105
 */

#include "rectangle.h"

Rectangle::Rectangle(const int x, const int y, const int width,
		const int height) :
		rect_ { new SDL_Rect() } {
	rect_->x = x;
	rect_->y = y;
	rect_->w = width;
	rect_->h = height;
}

Rectangle::~Rectangle() {
	delete rect_;
}

SDL_Rect* Rectangle::get_rect() {
	return rect_;
}

const SDL_Rect* Rectangle::get_rect() const {
	return rect_;
}
