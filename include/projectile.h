/*
 * projectile.h
 *
 *  Created on: Dec 12, 2014
 *      Author: frejo105
 */

#ifndef INCLUDE_PROJECTILE_H_
#define INCLUDE_PROJECTILE_H_

#include "sprite.h"

class Projectile : public Sprite
{
public:
  Projectile(const std::string texture, Rectangle const& rect, const int damage, const Velocity velocity);
  void update();

  const int damage_;
};


#endif /* INCLUDE_PROJECTILE_H_ */
