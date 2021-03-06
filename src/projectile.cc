/*
 * projectile.cc
 *
 *  Created on: Dec 12, 2014
 *      Author: frejo105
 */

#include "projectile.h"

Projectile::Projectile(const std::string texture, Rectangle const& rect,
                       const int damage, const Velocity velocity, ProjectileOwner owner)
    : Sprite (texture, rect, 0), kDamage { damage }, owner_{owner}
{
  velocity_ = velocity;
}

void Projectile::update()
{
  set_x (get_x () + velocity_.x);
  set_y (get_y () + velocity_.y);
}
