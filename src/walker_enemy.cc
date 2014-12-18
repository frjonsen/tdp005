/*
 * walker_enemy.cc
 *
 *  Created on: Dec 16, 2014
 *      Author: vakz
 */

#include <walker_enemy.h>

WalkerEnemy::WalkerEnemy(const int x, const int y)
  : Enemy("enemy_walker_1.png", {x, y, 25, 35}, 15, 2, EnemyType::kWalker, false)
{
  velocity_.x = kTopXVelocity;
}

void WalkerEnemy::handle_gravity(const int gravity)
{
  velocity_.y += gravity;
}

void WalkerEnemy::update()
{
  set_x(get_x() + velocity_.x);
  set_y(get_y() + velocity_.y);
  handle_animation();
}

void WalkerEnemy::handle_animation()
{
  if (velocity_.x != 0)
  {

    ++animation_timer_;
    if (animation_timer_ > animation_change_frequency)
    {
      texture_.texture_name = animations.at (current_animation);
      current_animation = (current_animation + 1) % animations.size ();
      animation_timer_ = 0;
    }
  }
  else
  {
    animation_timer_ = 0;
    current_animation = 0;
  }
}
