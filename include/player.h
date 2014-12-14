/*
 * player.h
 *
 *  Created on: Dec 8, 2014
 *      Author: frejo105
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "sprite.h"
#include <list>
#include <map>
#include "projectile.h"

/**
 * Representation of the actual player in the game
 */
class Player : public Sprite
{
public:

  /// The movement commands the player can be given
  enum class MovementCommand
  {
    kMoveLeft, kMoveRight, kJump
  };

  /**
   * Initialize player
   * @param texture Texture used by the player
   * @param rect The rect enclosing the player
   */
  Player(std::string texture, Rectangle const& rect);
  ~Player();

  /// Set y velocity to 0 and remove jumping flag
  void reset_y_velocity();

  /// Ask player to update for new frame
  void update();

  /**
   * Give player movement commands
   * @param moves A list of movement commands for the
   * player to do
   */
  void order_player(std::list<MovementCommand> moves);

  /**
   * Ask player to handle the world gravity
   * @param gravity The world gravity constant
   */
  void handle_gravity(const int gravity);

  /**
   * Set player to be stunned for a certain duration
   * and give the player a push speed
   * @param time Duraction
   * @param velocity_x Push velocity
   */
  void set_stunned(const size_t time, int velocity_x);

private:
  /// Name of weapons usable by player
  enum class WeaponName
  {
    kIfGun, kWhileGun, kForGun
  };

  /// Contains weapon statistics
  struct Weapon
  {
    Weapon(std::string texture, int nr, int v, int dmg, int cd, int w, int h)
        : projectile_texture (texture), nr_of_projectiles (nr), projectile_velocity (
            v), damage (dmg), cooldown (cd), projectile_width (w), projectile_height (
            h)
    {
    }
    std::string projectile_texture; /// Texture used by projectiles
    int nr_of_projectiles; /// The  number of projectiles launched
    int projectile_velocity; /// The projectile velocity
    int damage; /// The damage a projectile causes
    int cooldown; /// How long until the weapon can be fired again
    int projectile_width; /// The width of the projectile texture
    int projectile_height; /// The height of the projectile texture
  };

  /**
   * Weapon properties
   */
  std::map<WeaponName, Weapon> weapons_ { { WeaponName::kWhileGun, Weapon (
      "while_gun.png", 1, 15, 10, 10, 27, 38) }, { WeaponName::kIfGun, Weapon (
      "normal_projectile.png", 1, 15, 15, 35, 7, 6) } };

  /// The vertical velocity a jump has
  const int kJumpVelocity;

  /// How many frames since the player's weapon was last fired
  int frames_since_firing_;

  /// Is player jumping
  bool jumping_;

  /// Is player stunned
  bool stunned_;

  /// How long is player stunned. Should be set to 0 if not stunned
  size_t stunned_timer_ { 0 };

  /// The weapon player is currently using
  Weapon current_weapon_ { weapons_.at (WeaponName::kIfGun) };

public:
  /**
   * Ask player to fire weapon
   * @return If possible, and active projectile.
   * nullptr if weapon is on cooldown or player is stunned.
   */
  Projectile* fire();
};

#endif /* PLAYER_H_ */
