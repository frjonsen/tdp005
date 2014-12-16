/*
 * enemy.cc
 *
 *  Created on: Dec 16, 2014
 *      Author: vakz
 */

#include <enemy.h>

Enemy::Enemy(std::string texture, Rectangle const& rectangle, int hp,
             const int top_velocity, EnemyType type)
    : Sprite (texture, rectangle, hp, top_velocity), kType { type }
{
}

void Enemy::reverse_direction()
{
  velocity_.x *= -1;
  texture_.flip = !texture_.flip;
}
