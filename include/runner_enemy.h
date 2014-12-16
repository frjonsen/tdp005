/*
 * runner_enemy.h
 *
 *  Created on: Dec 16, 2014
 *      Author: vakz
 */

#ifndef RUNNER_ENEMY_H_
#define RUNNER_ENEMY_H_

#include <enemy.h>

class RunnerEnemy : public Enemy
{
public:
  RunnerEnemy(const int x, const int y);

  RunnerEnemy(RunnerEnemy const& other) = delete;
  RunnerEnemy(RunnerEnemy&& other) = delete;

  RunnerEnemy& operator=(RunnerEnemy const& rhs) = delete;
  RunnerEnemy& operator=(RunnerEnemy&& rhs) = delete;

  void update();
  void handle_gravity(const int gravity);
  void take_damage(int dmg);

private:
  bool is_invulnerable_{false};

  const size_t kRunningInterval{300};
  const int kRunVelocity;
  size_t run_timer_{0};
};


#endif /* RUNNER_ENEMY_H_ */
