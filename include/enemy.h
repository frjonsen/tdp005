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

class Enemy : public Sprite
{
public:
  enum class EnemyType
  {
    kWalker,
    kSpitter,
    kRunner
  };

  const EnemyType kType;
  const bool kIsRanged;

  void reverse_direction();
  virtual Projectile* fire(Sprite const& player);

protected:
  Enemy(std::string texture, Rectangle const& rectangle, int hp,
        const int top_velocity, EnemyType type, bool ranged);

};



#endif /* INCLUDE_ENEMY_H_ */
