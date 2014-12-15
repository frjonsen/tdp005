/*
 * player.cc
 *
 *  Created on: Dec 8, 2014
 *      Author: frejo105
 */

#include "player.h"
#include <iostream>

Player::Player(std::string texture, Rectangle const& rectangle)
    : Sprite (texture, rectangle, 100, 5), kJumpVelocity { 15 }, frames_since_firing_ {
        -1 }, jumping_ { false }, stunned_ { false }
{

}

Player::~Player()
{

}

void Player::update()
{
  if (frames_since_firing_ >= 0) ++frames_since_firing_;
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
          jump();          jumping_ = true;
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

Projectile* Player::fire()
{
  if (frames_since_firing_ >= 0)
  {
    return nullptr;
  }
  int spawn_x { texture_.flip ? get_x () : get_x () + get_width () };
  int spawn_y { get_y () + 30 - current_weapon_.projectile_height };

  int velocity {
      texture_.flip ? -current_weapon_.projectile_velocity :
                      current_weapon_.projectile_velocity };
  Rectangle projectile_rect (spawn_x, spawn_y, current_weapon_.projectile_width,
                             current_weapon_.projectile_height);
  frames_since_firing_ = 0;
  return new Projectile (current_weapon_.projectile_texture, projectile_rect,
                         current_weapon_.damage, { velocity, 0 },
                         Projectile::ProjectileOwner::kPlayer);
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
    if (stunned_timer_ == 0)
    {
      stunned_ = false;
    }
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
    texture_.texture_name = animations.at (current_animation);
    ++animation_timer_;
    if (animation_timer_ > animation_change_frequency)
    {
      current_animation = (current_animation + 1) % animations.size ();
      animation_timer_ = 0;
    }
  }
  else
  {
    texture_.texture_name = "Hero_Standing_R.png";
    animation_timer_ = 0;
    current_animation = 0;
  }
}

void Player::jump()
{
  jumping_ = true;
  velocity_.y = -kJumpVelocity;
}
