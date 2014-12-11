/*
 * player.cc
 *
 *  Created on: Dec 8, 2014
 *      Author: frejo105
 */

#include "player.h"

Player::Player(std::string texture, Rectangle const& rectangle, Velocity velocity)
    : Sprite (texture, rectangle, velocity, 5), kJumpVelocity { 15 }, frames_since_firing_ {
        -1 }, jumping_ { false }, stunned_ { false }
{

}

Player::~Player()
{

}

void Player::update()
{
  ++frames_since_firing_;
  set_x (get_x () + velocity_.x);
  if (!stunned_) velocity_.x = 0;
  set_y (get_y () + velocity_.y);
}

void Player::order_player(std::vector<MovementCommand> moves)
{
  for (MovementCommand mc : moves)
  {
    switch (mc)
    {
      case MovementCommand::kJump:
        if (!jumping_)
        {
          jumping_ = true;
          velocity_.y = -kJumpVelocity;
        }
        break;
      case MovementCommand::kMoveLeft:
        if (!stunned_) velocity_.x = -kTopXVelocity;
        break;
      case MovementCommand::kMoveRight:
        if (!stunned_) velocity_.x = kTopXVelocity;
        break;
    }
  }
  update ();
}

void Player::handle_gravity(const int gravity)
{
  velocity_.y += gravity;
}

float Player::get_moving_angle() const
{
  return 0;
}

void Player::reset_y_velocity()
{
  if (jumping_) jumping_ = false;
  velocity_.y = 0;
}


