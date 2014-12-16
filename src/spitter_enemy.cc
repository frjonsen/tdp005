/*
 * spitter_enemy.cc
 *
 *  Created on: Dec 16, 2014
 *      Author: vakz
 */

#include <spitter_enemy.h>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <projectile.h>

SpitterEnemy::SpitterEnemy(const int x, const int y)
    : Enemy ("Slime_1.png", { x, y, 25, 35 }, 30, 0, EnemyType::kSpitter, true)
{
}

void SpitterEnemy::update()
{
  handle_animation ();
}

void SpitterEnemy::handle_animation()
{

  texture_.texture_name = animations.at (current_animation);
  ++animation_timer_;
  if (animation_timer_ > animation_change_frequency)
  {
    current_animation = (current_animation + 1) % animations.size ();
    animation_timer_ = 0;
  }
}

Projectile* SpitterEnemy::fire(Sprite const& player)
{
  if (projectile_timer_ > kProjectileCooldown) projectile_timer_ = -1;
  if (projectile_timer_ >= 0){
    ++projectile_timer_;
    return nullptr;
  }
  int player_x{abs(get_x() - player.get_x())};
  int player_y{abs(get_y() - player.get_y())};
  double player_distance{sqrt(player_x*player_x + player_y*player_y)};
  if (player_distance > 400)
  {
    return nullptr;
  }
  int longest{std::max(player_x, player_y)};
  int shortest{std::min(player_x, player_y)};

  double factor{double(shortest) / longest};
  int x_velocity{kProjectileVelocity};
  if (player.get_x() < get_x()) x_velocity *= -1;
  Projectile *p = new Projectile{"normal_projectile.png", {get_x(), get_y() + 20, 7, 6}, 40, {x_velocity, -int(ceil(x_velocity*factor))}, Projectile::ProjectileOwner::kEnemy};
  ++projectile_timer_;
  return p;
}
