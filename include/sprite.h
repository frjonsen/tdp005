/*
 * sprite.h
 *
 *  Created on: Dec 1, 2014
 *      Author: vakz
 */

#ifndef SPRITE_H_
#define SPRITE_H_

#include "rectangle.h"
#include <string>

class Texture;

class Sprite: public Rectangle {
public:
	struct Velocity {
		int x;
		int y;
	};

	Sprite(std::string texture, Rectangle const& rectangle, Velocity velocity,
			const int top_velocity = 0);
	virtual ~Sprite();

	Sprite(Sprite const&) = delete;
	Sprite(Sprite const&&) = delete;

	Sprite& operator=(Sprite const&) = delete;
	Sprite& operator=(Sprite&&) = delete;

	virtual void update();
	virtual void handle_gravity(const int gravity);
	virtual void reset_y_velocity();

	virtual float get_moving_angle() const;
	const std::string get_texture() const;

protected:
	std::string texture_;
	Velocity velocity_;

	const int kTopXVelocity;
};

#endif /* SPRITE_H_ */
