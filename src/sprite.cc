/*
 * sprite.cc
 *
 *  Created on: Dec 7, 2014
 *      Author: vakz
 */

#include "sprite.h"
#include "surface.h"
#include "rectangle.h"

Sprite::Sprite(Renderer& renderer, Surface& surface, Rectangle const& rectangle, Velocity velocity, const int top_velocity)
    : Rectangle (rectangle), texture_ { renderer, surface }, velocity_{velocity.x, velocity.y}, kTopXVelocity{top_velocity}
{

}

Sprite::~Sprite()
{

}

void Sprite::update()
{
}

const Texture& Sprite::get_texture() const
{
  return texture_;
}

float Sprite::get_moving_angle() const
{
	return 0;
}

void Sprite::handle_gravity(const int gravity)
{
}
