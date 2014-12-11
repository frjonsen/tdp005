/*
 * sprite.cc
 *
 *  Created on: Dec 7, 2014
 *      Author: vakz
 */

#include "sprite.h"
#include "rectangle.h"
#include <string>

Sprite::Sprite(std::string texture, Rectangle const& rectangle, Velocity velocity, const int top_velocity)
    : Rectangle (rectangle), texture_ { texture }, velocity_{velocity.x, velocity.y}, kTopXVelocity{top_velocity}
{

}

Sprite::~Sprite()
{

}

void Sprite::update()
{
}

const std::string Sprite::get_texture() const
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

void Sprite::reset_y_velocity()
{
  velocity_.y = 0;
}
