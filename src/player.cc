/*
 * player.cc
 *
 *  Created on: Dec 8, 2014
 *      Author: frejo105
 */

#include "player.h"
#include <iostream>
#include <random>
#include <cmath>

Player::Player(TextureColor color, int hp, int x_velocity, int jump_velocity)
    : Sprite ("Hero_Standing_R.png", { 50, 220, 33, 53 }, hp, x_velocity), current_color_{color}, kJumpVelocity { jump_velocity }, kStartingHp{hp}, frames_since_firing_ {
        -1 }, jumping_ { false }, stunned_ { false }
{

}


Player::~Player()
{

}

void Player::update()
{
  // If weapon has been fired, increment
  if (frames_since_firing_ >= 0) ++frames_since_firing_;
  // If cooldown is completed
  if (frames_since_firing_ > current_weapon_.cooldown) frames_since_firing_ =
      -1;
  handle_animation ();
  handle_move ();
}

void Player::order_player(std::list<MovementCommand> moves)
{
  for (MovementCommand mc : moves)
  {
    switch (mc)
    {
      case MovementCommand::kJump:
        if (!jumping_ && !stunned_)
        {
          jump ();
          jumping_ = true;
          velocity_.y = -kJumpVelocity;
        }
        break;
      case MovementCommand::kMoveLeft:
        if (!stunned_)
        {
          texture_.flip = true;
          velocity_.x = -kTopXVelocity;
        }
        break;
      case MovementCommand::kMoveRight:
        if (!stunned_)
        {
          texture_.flip = false;
          velocity_.x = kTopXVelocity;
        }
        break;
    }
  }
  update ();
}

void Player::handle_gravity(const int gravity)
{
  velocity_.y += gravity;
  //if (velocity_.y > 0) jumping_ = true; // Set flag jumping if falling
}

void Player::reset_y_velocity()
{
  if (jumping_) jumping_ = false;
  velocity_.y = 0;
}

std::list<Projectile*> Player::fire()
{
  std::list<Projectile*> projectiles {};
  if (frames_since_firing_ >= 0)
  {
    return projectiles;
  }
  // Calculate where projectile should spawn
  int spawn_x { texture_.flip ? get_x () : get_x () + get_width () };
  int spawn_y { get_y () + 30 - current_weapon_.projectile_height };

  // Calculate direction the projectile should fly
  int velocity {
      texture_.flip ? -current_weapon_.projectile_velocity :
                      current_weapon_.projectile_velocity };
  Rectangle projectile_rect (spawn_x, spawn_y, current_weapon_.projectile_width,
                             current_weapon_.projectile_height);
  frames_since_firing_ = 0;
  // If an odd number of projectiles is to be fired, fire one at 0 degrees
  if (current_weapon_.nr_of_projectiles % 2 == 1){
  projectiles.push_back (
      new Projectile (current_weapon_.projectile_texture, projectile_rect,
                      current_weapon_.damage, { velocity, 0 },
                      Projectile::ProjectileOwner::kPlayer));
  }
  bool positive { true };
  float difference{0.1};
  // If additional projectiles should be fire, keep should with some degree angle.
  for (int i { 0 }; int(projectiles.size()) < current_weapon_.nr_of_projectiles; ++i)
  {
    // Whether projectile should be fired downwards or upwards
    int m{positive ? 1 : -1};
    int y_velocity{int (round (velocity * difference))*m};
    projectiles.push_back (
        new Projectile (
            current_weapon_.projectile_texture, projectile_rect,
            current_weapon_.damage,
            { int (round (velocity * 1-difference)), y_velocity },
            Projectile::ProjectileOwner::kPlayer));

    if (i % 2) difference += 0.1;
    positive = !positive;
  }
  return projectiles;
}

void Player::set_stunned(const size_t time, int velocity_x = 0)
{
  stunned_timer_ = time;
  stunned_ = true;
  velocity_.x = velocity_x;
}

void Player::handle_move()
{
  set_x (get_x () + velocity_.x);
  if (stunned_)
  {
    --stunned_timer_;
    if (stunned_timer_ == 0) stunned_ = false;
  }
  else
  {
    velocity_.x = 0;
  }

  set_y (get_y () + velocity_.y);
}

void Player::handle_animation()
{
  if (velocity_.x != 0)
  {
    ++animation_timer_;
    if (animation_timer_ > animation_change_frequency_)
    {
      texture_.texture_name = animations_.at(current_color_).at (current_animation_);
      current_animation_ = (current_animation_ + 1) % animations_.size ();
      animation_timer_ = 0;
    }
  }
  else
  {
    texture_.texture_name = standing_textures_.at(current_color_);
    animation_timer_ = 0;
    current_animation_ = 0;
  }
}

void Player::jump()
{
  jumping_ = true;
  velocity_.y = -kJumpVelocity;
}

void Player::randomize_weapon()
{
  std::random_device r;
  std::uniform_int_distribution<int> d { 0, 2 };
  WeaponName new_weapon { WeaponName (d (r)) };
  current_weapon_ = weapons_.at (new_weapon);
}

std::string Player::get_weapon_sprite() const{
  switch (current_weapon_.name)
  {
    case WeaponName::kForGun:
      return "for_gun.png";
    case WeaponName::kIfGun:
      return "if_gun.png";
    case WeaponName::kWhileGun:
      return "while_gun.png";
  }
  // Will never reach this point, only to make compiler happy
  return "for_gun.png";
}

void Player::reset()
{
  current_weapon_ = weapons_.at(WeaponName::kWhileGun);
  velocity_.x = 0;
  stunned_ = false;
  jumping_ = false;
  set_hp(kStartingHp);
}

int Player::get_extra_lives() const
{
  return lives_;
}

void Player::lose_extra_life()
{
  --lives_;
}

void Player::gain_extra_life()
{
  ++lives_;
}
