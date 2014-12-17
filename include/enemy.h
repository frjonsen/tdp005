/*
 * enemy.h
 *
 *  Created on: Dec 15, 2014
 *      Author: vakz
 */

#ifndef ENEMY_H_
#define ENEMY_H_

#include <sprite.h>
#include <projectile.h>
/**
 * Base class of all the enemy objects
 */
class Enemy : public Sprite
{
public:
  /// Names of enemy types
  enum class EnemyType
  {
    kWalker,
    kSpitter,
    kRunner
  };

  /// Currently active enemy type
  const EnemyType kType;

  /// Declaration if the enemy type is ranged
  const bool kIsRanged;

  /// Reverses the direction the enemy is moving
  void reverse_direction();

  /// Projectiles fired if enemy type can fire
  virtual Projectile* fire(Sprite const& player);

protected:
  /**
   * Constructor used by all enemys
   * @param texture for the enemy
   * @param rectangle for the enmy
   * @param hp represents how much health the enemy has
   * @param top_velocity movement speed for enemy
   * @param type type of enemy constructed
   * @param ranged if enemy is ranged
   */
  Enemy(std::string texture, Rectangle const& rectangle, int hp,
        const int top_velocity, EnemyType type, bool ranged);

};



#endif /* INCLUDE_ENEMY_H_ */
