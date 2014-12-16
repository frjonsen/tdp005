/*
 * WalkerEnemy.h
 *
 *  Created on: Dec 16, 2014
 *      Author: vakz
 */

#ifndef WALKERENEMY_H_
#define WALKERENEMY_H_

#include <enemy.h>
#include <vector>

class WalkerEnemy : public Enemy
{
public:
  WalkerEnemy(const int x, const int y);

  WalkerEnemy(WalkerEnemy const& other) = delete;
  WalkerEnemy(WalkerEnemy&& other) = delete;

  WalkerEnemy& operator=(WalkerEnemy const& rhs) = delete;
  WalkerEnemy& operator=(WalkerEnemy&& rhs) = delete;

  void update();
  void handle_gravity(const int gravity);

private:
  void handle_animation();

  const std::vector<std::string> animations
  {
    "enemy_walker_1.png",
    "enemy_walker_2.png",
    "enemy_walker_3.png"
  };

  int current_animation{0};
  size_t animation_timer_{0};
  size_t animation_change_frequency{10};

};



#endif /* INCLUDE_WALKERENEMY_H_ */
