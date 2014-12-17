/*
 * sprite.h
 *
 *  Created on: Dec 1, 2014
 *      Author: vakz
 */

#ifndef SPRITE_H_
#define SPRITE_H_

#include "rectangle.h"
#include <string>

class Texture;

/**
 * The common base class for all objects in the game world
 * which have a visual representation
 */
class Sprite: public Rectangle {
public:
  /**
   * Representation of vertical and horizontal velocity
   */
	struct Velocity {
	  /// Horizontal velocity. A positive value will move an object to the right,
	  /// a negative to the left
		int x;
		/// Vertical velocity. A positive value will move an object down, a negative up.
		int y;
	};

	/**
	 * Contains basic information about how a texture should be displayed
	 */
	struct TextureInfo
	{
	  /// Filename of texture
	  std::string texture_name;
	  /// Whether texture should be flipper horizontally
	  bool flip;
	  /// Angle in degrees the texture should be rotated
	  int angle;
	};

	/**
	 * Initialize sprite
	 * @param texture Filename of texture image
	 * @param rectangle /// Enclosing rectangle. Width and height should be the same as the texture image
	 * @param hp /// Amount of health object has
	 * @param top_velocity /// The top horizontal velocity the object can move at.
	 * Set to zero if object should be stationary
	 */
	Sprite(std::string texture, Rectangle const& rectangle, int hp,
			const int top_velocity = 0);
	virtual ~Sprite();

	/// Deleted copy constructor
	Sprite(Sprite const&) = delete;

	/// Deleted move constructor
	Sprite(Sprite const&&) = delete;

	/// Deleted assignment constructor
	Sprite& operator=(Sprite const&) = delete;

	/// Deleted move-assignment constructor
	Sprite& operator=(Sprite&&) = delete;

	/// Request sprite to update for new frame
	virtual void update();

	/**
	 * Request sprite to handle the world gravity
	 * @param gravity World gravity constant
	 */
	virtual void handle_gravity(const int gravity);

	/**
	 * Set the vertical velocity to 0.
	 */
	virtual void reset_y_velocity();

	/**
	 * Get the filename of the texture the sprite is using as visual representation
	 * @return Filename of texture
	 */
	const TextureInfo& get_texture() const;

	int get_hp() const;
	void gain_hp(const int hp);
	virtual void take_damage(int dmg);

protected:
	/// Information regarding the visual representation of the sprite
	TextureInfo texture_;

	/// Current horizontal and vertical velocity
	Velocity velocity_{0,0};

	/// Top horizontal velocity
	const int kTopXVelocity;

	/// Current health
	int hp_;
};

#endif /* SPRITE_H_ */
