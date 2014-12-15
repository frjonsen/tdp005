/*
 * enemy.h
 *
 *  Created on: Dec 15, 2014
 *      Author: vakz
 */

#ifndef ENEMY_H_
#define ENEMY_H_

class Enemy : public Sprite
{
public:
  enum class EnemyType
  {
    kWalker,
    kSpitter,
    kRunner
  };
};



#endif /* INCLUDE_ENEMY_H_ */
