/*
 * spitter_enemy.h
 *
 *  Created on: Dec 16, 2014
 *      Author: vakz
 */

#ifndef SPITTER_ENEMY_H_
#define SPITTER_ENEMY_H_

#include <enemy.h>
#include <vector>

class SpitterEnemy : public Enemy
{
public:
  SpitterEnemy(const int x, const int y);

  SpitterEnemy(SpitterEnemy const& other) = delete;
  SpitterEnemy(SpitterEnemy&& other) = delete;

  SpitterEnemy& operator=(SpitterEnemy const& rhs) = delete;
  SpitterEnemy& operator=(SpitterEnemy&& rhs) = delete;

  void update();
  Projectile* fire(Sprite const& player);

private:
  void handle_animation();

  int kProjectileVelocity{5};
  int kProjectileCooldown{60};

  int projectile_timer_{-1};

  const std::vector<std::string> animations
  {
    "Slime_1.png",
    "Slime_2.png",
    "Slime_3.png"
  };

  int current_animation{0};
  size_t animation_timer_{0};
  size_t animation_change_frequency{25};

};


#endif /* SPITTER_ENEMY_H_ */
