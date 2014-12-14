/*
 * sprite.cc
 *
 *  Created on: Dec 7, 2014
 *      Author: vakz
 */

#include "sprite.h"
#include "rectangle.h"
#include <string>

Sprite::Sprite(std::string texture, Rectangle const& rectangle, int hp,
               const int top_velocity)
    : Rectangle ( rectangle ), texture_ { texture, false, 0 }, kTopXVelocity { top_velocity }, hp_{hp}
{

}

Sprite::~Sprite()
{

}

void Sprite::update()
{
}

const Sprite::TextureInfo& Sprite::get_texture() const
{
  return texture_;
}

void Sprite::handle_gravity(const int gravity)
{
}

void Sprite::reset_y_velocity()
{
  velocity_.y = 0;
}
