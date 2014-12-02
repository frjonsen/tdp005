/*
 * sprite.h
 *
 *  Created on: Dec 1, 2014
 *      Author: vakz
 */

#ifndef INCLUDE_SPRITE_H_
#define INCLUDE_SPRITE_H_

class Texture;

class Sprite : public Rectangle
{
public:
  Sprite(Surface surface, const int y, const int width, const int height);
protected:
  Texture texture_;
};



#endif /* INCLUDE_SPRITE_H_ */
