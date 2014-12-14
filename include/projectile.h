/*
 * projectile.h
 *
 *  Created on: Dec 12, 2014
 *      Author: frejo105
 */

#ifndef INCLUDE_PROJECTILE_H_
#define INCLUDE_PROJECTILE_H_

#include "sprite.h"

/**
 * Representation of a projectile
 */
class Projectile : public Sprite
{
public:
  /// The projectiles owner, to know who the projectile is hostile to
  enum class ProjectileOwner
  {
    kPlayer, kEnemy
  };

  /**
   * Initialize projectile
   * @param texture Texture used by projectile
   * @param rect Enclosing rectangle
   * @param damage The damage caused by the projectile
   * @param velocity The velocity of the proctile
   * @param owner Owner of the projectile
   */
  Projectile(const std::string texture, Rectangle const& rect, const int damage,
             const Velocity velocity, ProjectileOwner owner);

  /// Request projectile to update for new frame
  void update();

  /// Damage caused by the weapon
  const int damage_;

  /// Projectile owner
  const ProjectileOwner owner_;

};

#endif /* INCLUDE_PROJECTILE_H_ */
