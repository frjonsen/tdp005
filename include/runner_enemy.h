/*
 * runner_enemy.h
 *
 *  Created on: Dec 16, 2014
 *      Author: vakz
 */

#ifndef RUNNER_ENEMY_H_
#define RUNNER_ENEMY_H_

#include <enemy.h>

/**
 * A Runner enemy.
 * A Runner will phase between walking and running. While running,
 * the Runner will take no damage, and will have three times the
 * horizontal velocity as when walking
 */
class RunnerEnemy : public Enemy
{
public:
  /**
   * Initialize Runner
   * @param x X coordinate to spawn at
   * @param y Y coordinate to spawn at
   */
  RunnerEnemy(const int x, const int y);

  /// Deleted copy constructor
  RunnerEnemy(RunnerEnemy const& other) = delete;
  /// Deleted move constructor
  RunnerEnemy(RunnerEnemy&& other) = delete;

  /// Deleted assigment operator
  RunnerEnemy& operator=(RunnerEnemy const& rhs) = delete;
  /// Deleted move-assignment operator
  RunnerEnemy& operator=(RunnerEnemy&& rhs) = delete;

  /// Request Runner to update for new frame
  void update();
  /// Handle gravity based on world gravity constant
  void handle_gravity(const int gravity);
  /**
   * Take damage. No damage will be taken if is_invulnerable is true
   * @param dmg The amount of damage to take
   */
  void take_damage(int dmg);

private:
  /// Whether Runner can take damage. If true, no damage will be taken
  bool is_invulnerable_{false};

  /// How often to change between running and walking
  const size_t kRunningInterval{300};
  /// Horizontal velocity when running
  const int kRunVelocity;
  /// How long Runner has currently been in running or walking phase
  size_t run_timer_{0};
};


#endif /* RUNNER_ENEMY_H_ */
