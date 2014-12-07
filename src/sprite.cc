/*
 * sprite.cc
 *
 *  Created on: Dec 7, 2014
 *      Author: vakz
 */

#include "sprite.h"
#include "surface.h"
#include "rectangle.h"

Sprite::Sprite(Renderer& renderer, Surface& surface, const int x,
               const int y, const int width, const int height)
    : Rectangle (x, y, width, height), texture_ { renderer, surface }
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
