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

/**
 * A Spitter enemy.
 * A spitter is a stationary enemy, firing projectiles
 * towards the player when player is within a certain distance.
 * Will attempt to figure directly at the player, taking angle
 * into accout.
 */
class SpitterEnemy : public Enemy
{
public:
  /**
   * Initialize Spitter
   * @param x X coordinate to spawn at
   * @param y Y coordinate to spawn at
   */
  SpitterEnemy(const int x, const int y);

  /// Deleted copy constructor
  SpitterEnemy(SpitterEnemy const& other) = delete;
  /// Deleted move constructor
  SpitterEnemy(SpitterEnemy&& other) = delete;

  /// Deleted assignment operator
  SpitterEnemy& operator=(SpitterEnemy const& rhs) = delete;
  /// Deleted move-assignment operator
  SpitterEnemy& operator=(SpitterEnemy&& rhs) = delete;

  /**
   * Request Spitter to update for new tick.
   */
  void update();
  /**
   * Fire at the player if player is within a certain distance
   * @param player Player to fire at
   * @return If player is within distance and weapon is off cooldown,
   * returns a projectile pointer. Else returns nullptr
   */
  Projectile* fire(Sprite const& player);

private:
  /// Handle the animatin
  void handle_animation();

  /// Velocity of projectile
  int kProjectileVelocity{5};

  /// Cooldown before Spitter will fire again
  int kProjectileCooldown{60};

  /// How long since weapon went on cooldown. Should be negative if off cooldown
  int projectile_timer_{-1};

  /// Animation textures
  const std::vector<std::string> animations
  {
    "Slime_1.png",
    "Slime_2.png",
    "Slime_3.png"
  };

  /// Index of current animation texture
  int current_animation{0};
  /// How long current texture has been in use
  size_t animation_timer_{0};
  /// How often to chnge texture
  size_t animation_change_frequency{25};

};


#endif /* SPITTER_ENEMY_H_ */
