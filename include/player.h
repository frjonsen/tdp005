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
#include <vector>

/**
 * Representation of the actual player in the game
 */
class Player : public Sprite
{
public:
  enum class TextureColor
  {
    kRed, kBlue, kYellow
  };

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
  Player(TextureColor color = TextureColor::kYellow,
         int hp = 100, int x_velocity = 5, int jump_velocity = 15);
  ~Player();

  //Player& operator=(Player const& rhs);

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
  /**
   * Ask player to fire weapon
   * @return If possible, and active projectile.
   * nullptr if weapon is on cooldown or player is stunned.
   */
  std::list<Projectile*> fire();
  /// Make player jumping, setting vertical velocity to kJumpVelocity and setting jump flag to true
  void jump();
  /**
   * Randomize a new weapon for player to use. Will never random to the weapon currently in use.
   */
  void randomize_weapon();

  /**
   * Get the sprite for the currently in-use weapon
   */
  std::string get_weapon_sprite() const;

  /// Reset player
  void reset();

  /// Get number of extra lives player currently has
  int get_extra_lives() const;

  /// Decrement player lives
  void gain_extra_life();

  /// Incement player lives
  void lose_extra_life();
private:
  /// The current texture color
  TextureColor current_color_;

  /// Name of weapons usable by player
  enum class WeaponName
  {
    kIfGun, kWhileGun, kForGun
  };

  /// Contains weapon statistics
  struct Weapon
  {
    /**
     * Initialize a weapon
     * @param texture Texture used by projectile
     * @param nr Number of projectiles
     * @param v Projectile horizontal velocity
     * @param dmg Damage done when a target is hit
     * @param cd Cooldown before weapon can be fired again
     * @param w Width of the projectile texture
     * @param h Height of the projectile texture
     */
    Weapon(std::string texture, int nr, int v, int dmg, int cd, int w, int h,
           WeaponName n)
        : projectile_texture (texture), nr_of_projectiles (nr), projectile_velocity (
            v), damage (dmg), cooldown (cd), projectile_width (w), projectile_height (
            h), name (n)
    {
    }
    /// Texture used by projectiles
    std::string projectile_texture;
    /// The  number of projectiles launched
    int nr_of_projectiles;
    /// The projectile velocity
    int projectile_velocity;
    /// The damage a projectile causes
    int damage;
    /// How long until the weapon can be fired again
    int cooldown;
    /// The width of the projectile texture
    int projectile_width;
    /// The height of the projectile texture
    int projectile_height;
    WeaponName name;
  };

  /**
   * Weapon properties
   */
  std::map<WeaponName, Weapon> weapons_ { { WeaponName::kWhileGun, Weapon (
      "normal_projectile.png", 1, 15, 10, 10, 7, 6, WeaponName::kWhileGun) }, {
      WeaponName::kIfGun, Weapon ("big_projectile.png", 1, 8, 15, 50, 25, 25,
                                  WeaponName::kIfGun) }, {
      WeaponName::kForGun, Weapon ("normal_projectile.png", 3, 7, 20, 60, 7, 6,
                                   WeaponName::kForGun) } };

  // nr, velocity, dmg, cd, w, h

  /// The vertical velocity a jump has
  const int kJumpVelocity;

  /// Starting hp
  const int kStartingHp;

  /// How many frames since the player's weapon was last fired
  int frames_since_firing_ { -1 };

  /// Is player jumping
  bool jumping_;

  /// Is player stunned
  bool stunned_;

  /// Player extra lives
  int lives_{2};

  /// How long is player stunned. Should be set to 0 if not stunned
  size_t stunned_timer_ { 0 };

  /// The weapon player is currently using
  Weapon current_weapon_ { weapons_.at (WeaponName::kWhileGun) };

  const std::map<TextureColor, std::string> standing_textures_ { {
      TextureColor::kYellow, "Hero_Standing_R.png" }, {
      TextureColor::kBlue, "Hero_Standing_R.png" }, {
      TextureColor::kRed, "Hero_Standing_R.png" } };

  const std::map<TextureColor, std::vector<std::string>> animations_ { {
      TextureColor::kYellow, {
          "Hero_Run_1_R.png", "Hero_Run_2_R.png", "Hero_Run_3_R.png",
          "Hero_Run_4_R.png", "Hero_Run_5_R.png", "Hero_Run_6_R.png",
          "Hero_Run_7_R.png", "Hero_Run_8_R.png" } }, { TextureColor::kRed, {
      "Hero_Run_1_R.png", "Hero_Run_2_R.png", "Hero_Run_3_R.png",
      "Hero_Run_4_R.png", "Hero_Run_5_R.png", "Hero_Run_6_R.png",
      "Hero_Run_7_R.png", "Hero_Run_8_R.png" } }, { TextureColor::kBlue, {
      "Hero_Run_1_R.png", "Hero_Run_2_R.png", "Hero_Run_3_R.png",
      "Hero_Run_4_R.png", "Hero_Run_5_R.png", "Hero_Run_6_R.png",
      "Hero_Run_7_R.png", "Hero_Run_8_R.png" } } };

  /// Index of the texture currently used
  int current_animation_ { 0 };
  /// Timer for texture change
  size_t animation_timer_ { 0 };
  /// The frequency for how often to change texture
  size_t animation_change_frequency_ { 7 };

  /// Move player based on horizontal and vertical velocity
  void handle_move();

  /// Handle the running animation
  void handle_animation();

};

#endif /* PLAYER_H_ */
