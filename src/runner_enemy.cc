/*
 * runner_enemy.cc
 *
 *  Created on: Dec 16, 2014
 *      Author: vakz
 */

#include <runner_enemy.h>

RunnerEnemy::RunnerEnemy(const int x, const int y)
    : Enemy ("Cloud_walking.png", { x, y, 58, 35 }, 40, -2, EnemyType::kRunner,
             false), kRunVelocity { kTopXVelocity * 3 }
{
  velocity_.x = kTopXVelocity;
}

void RunnerEnemy::handle_gravity(const int gravity)
{
  velocity_.y += gravity;
}

void RunnerEnemy::update()
{
  set_x (get_x () + velocity_.x);
  set_y (get_y () + velocity_.y);
  ++run_timer_;
  if (run_timer_ == kRunningInterval)
  {
    is_invulnerable_ = !is_invulnerable_;
    if (is_invulnerable_)
    {
      texture_.texture_name = "Cloud_running.png";
      velocity_.x = kRunVelocity;
    }
    else
    {
      texture_.texture_name = "Cloud_walking.png";
      velocity_.x = kTopXVelocity;
    }
    velocity_.x *= texture_.flip ? -1 : 1;
    texture_.flip = !texture_.flip;
    run_timer_ = 0;
  }
}

void RunnerEnemy::take_damage(int dmg)
{
  if (!is_invulnerable_)
  {
    Sprite::take_damage(dmg);
  }
}
