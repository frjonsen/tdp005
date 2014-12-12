/*
 * player.h
 *
 *  Created on: Dec 8, 2014
 *      Author: frejo105
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "sprite.h"
#include <vector>
#include <map>
#include "projectile.h"

class Player : public Sprite
{
public:
  enum class MovementCommand
  {
    kMoveLeft, kMoveRight, kJump
  };

  Player(std::string texture, Rectangle const&, Velocity velocity);
  ~Player();

  void reset_y_velocity();

  void update();
  void order_player(std::vector<MovementCommand>);
  void handle_gravity(const int gravity);
  float get_moving_angle() const;

private:
  enum class WeaponName
  {
    kIfGun, kWhileGun, kForGun
  };

  struct Weapon
  {
    Weapon(std::string texture, int nr, int v, int dmg, int cd, int w, int h)
        : projectile_texture ( texture ), nr_of_projectiles ( nr ), projectile_velocity (
            v ), damage ( dmg ), cooldown ( cd ), projectile_width ( w ), projectile_height (
            h )
    {
    }
    std::string projectile_texture;
    int nr_of_projectiles;
    int projectile_velocity;
    int damage;
    int cooldown;
    int projectile_width;
    int projectile_height;
  };

  std::map<WeaponName, Weapon> weapons_ { { WeaponName::kWhileGun, Weapon (
      "while_gun.png", 1, 15, 10, 10, 27, 38 ) }, { WeaponName::kIfGun, Weapon (
      "normal_projectile.png", 1, 15, 15, 10, 7, 6 ) } };

  const int kJumpVelocity;

  int frames_since_firing_;
  bool jumping_;
  bool stunned_;
  Weapon current_weapon_ { weapons_.at ( WeaponName::kIfGun ) };

public:
  Projectile* fire();
};

#endif /* PLAYER_H_ */
