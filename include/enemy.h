/*
 * enemy.h
 *
 *  Created on: Dec 15, 2014
 *      Author: vakz
 */

#ifndef ENEMY_H_
#define ENEMY_H_

#include <sprite.h>

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

  void reverse_direction();

protected:
  Enemy(std::string texture, Rectangle const& rectangle, int hp,
        const int top_velocity, EnemyType type);

};



#endif /* INCLUDE_ENEMY_H_ */
