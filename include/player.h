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

class Player: public Sprite {
public:
	enum class MovementCommand {
		kMoveLeft, kMoveRight, kJump
	};

	struct Weapon {
		int nr_of_projectiles;
		int projectile_velocity;
		int damage;
		int cooldown;
	};

	Player(Renderer& renderer, Surface& surface, Rectangle const&,
			Velocity velocity);
	~Player();

	void update();
	void order_player(std::vector<MovementCommand>);
	void handle_gravity(const int gravity);
	float get_moving_angle() const;
	bool fire(Weapon&) const;

private:
	const int kJumpVelocity;

	int frames_since_firing_;
	bool jumping_;
};

#endif /* PLAYER_H_ */
