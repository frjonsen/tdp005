/*
 * sprite.h
 *
 *  Created on: Dec 1, 2014
 *      Author: vakz
 */

#ifndef SPRITE_H_
#define SPRITE_H_

#include "rectangle.h"
#include "texture.h"

class Texture;

class Sprite: public Rectangle {
public:
	struct Velocity {
		int x;
		int y;
	};

	Sprite(Renderer& renderer, Surface& surface, Rectangle const& rectangle,
			Velocity velocity);
	virtual ~Sprite();

	Sprite(Sprite const&) = delete;
	Sprite(Sprite const&&) = delete;

	Sprite& operator=(Sprite const&) = delete;
	Sprite& operator=(Sprite&&) = delete;

	virtual void update();
	virtual void handle_gravity(const int gravity);
	virtual float get_moving_angle() const;
	const Texture& get_texture() const;

protected:
	Texture texture_;
	Velocity velocity_;
};

#endif /* SPRITE_H_ */
