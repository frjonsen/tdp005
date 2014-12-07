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

class Sprite : public Rectangle
{
public:
  Sprite(Renderer& renderer, Surface& surface, const int x,
         const int y, const int width, const int height);
  virtual ~Sprite();

  Sprite(Sprite const&) = delete;
  Sprite(Sprite const&&) = delete;

  Sprite& operator=(Sprite const&) = delete;
  Sprite& operator=(Sprite&&) = delete;

  virtual void update();
  const Texture& get_texture() const;
protected:
  Texture texture_;
};

#endif /* SPRITE_H_ */
