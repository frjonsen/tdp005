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

	struct TextureInfo
	{
	  std::string texture_name;
	  bool flip;
	  int angle;
	};

	Sprite(std::string texture, Rectangle const& rectangle, int hp,
			const int top_velocity = 0);
	virtual ~Sprite();

	Sprite(Sprite const&) = delete;
	Sprite(Sprite const&&) = delete;

	Sprite& operator=(Sprite const&) = delete;
	Sprite& operator=(Sprite&&) = delete;

	virtual void update();
	virtual void handle_gravity(const int gravity);
	virtual void reset_y_velocity();

	const TextureInfo& get_texture() const;

protected:
	TextureInfo texture_;
	Velocity velocity_{0,0};

	const int kTopXVelocity;

	int hp_;
};

#endif /* SPRITE_H_ */
