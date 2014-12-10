/*
 * player.cc
 *
 *  Created on: Dec 8, 2014
 *      Author: frejo105
 */

#include "player.h"

Player::Player(Renderer& renderer, Surface& surface, Rectangle const& rectangle,
		Velocity velocity) :
		Sprite(renderer, surface, rectangle, velocity), kJumpVelocity { 20 }, frames_since_firing_ {
				-1 }, jumping_ { false } {

}

Player::~Player() {

}

void Player::update() {
	++frames_since_firing_;
	set_y(get_y() + velocity_.y);
}

void Player::order_player(std::vector<MovementCommand> moves) {
	for (MovementCommand mc : moves)
	{
		switch(mc)
		{
		case MovementCommand::kJump:
			if (!jumping_)
			{
				jumping_ = true;
				velocity_.y = -kJumpVelocity;
			}
			break;
		case MovementCommand::kMoveLeft:
			set_x(get_x() - velocity_.x);
			break;
		case MovementCommand::kMoveRight:
			set_x(get_x() + velocity_.x);
			break;
		}
	}
	update();
}

void Player::handle_gravity(const int gravity) {
	velocity_.y = 5;
}

float Player::get_moving_angle() const {
	return 0;
}
