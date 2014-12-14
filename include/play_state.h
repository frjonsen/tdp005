/*
 * GameState.h
 *
 *  Created on: Dec 8, 2014
 *      Author: frejo105
 */

#ifndef GAME_STATE_H_
#define GAME_STATE_H_

#include "abstract_game_state.h"
#include <string>
#include <player.h>
#include <list>

/**
 * State representing the actual game
 */
class PlayState : public AbstractGameState
{
public:
  PlayState();
  ~PlayState();

  /// Deleted copy constructor
  PlayState(PlayState const&) = delete;
  /// Deleted move constructor
  PlayState(PlayState&&) = delete;

  /// Deleted assignment operator
  PlayState& operator=(PlayState const&) = delete;
  /// Delete move-assignment operator
  PlayState& operator=(PlayState&&) = delete;

  StateCommand update(std::list<GameInput> const& input);
  std::list<Sprite const*> get_sprites() const;
  std::string get_background() const;
  std::pair<int, int> get_viewport() const;

  /// Width of the game world
  const int kWorldWidth { 2400 };
  /// Height of the game world
  const int kWorldHeight { 600 };
  /// Maximum amount of frames per second
  const size_t kFPSGoal { 60 };

private:

  /// Game world gravity
  const int kGravity { 1 };

  /// Amount of score accumulated by the player
  int score_ { 0 };

  /// Maximum number of frames the player has to finish the game
  size_t time_ { 60 * kFPSGoal };

  /// The player
  Player player_ { "Hero_Standing_R.png", { 50, 200, 30, 53 } };

  /// A list of all terrain rectangles in the world
  std::list<Rectangle> terrain_ {};

  /// All projectiles currently in existance
  std::list<Projectile*> active_projectiles_ {};

  /// Background image
  std::string background_ { "playstate_background.png" };

  /**
   * Translates the given input into actions the player can perform
   * @param input The input given by the user
   * @return A list of player movements
   */
  std::list<Player::MovementCommand> translate_input(
      std::list<GameInput> const& input);
  /// Generate the game world terrain

  void generate_terrain();

  /**
   * Check if any terrain is currently colliding with rectangle r
   * @param r The rectangle to check for collisions
   * @return A list of all terrain r is colliding with
   */
  std::list<Rectangle *> check_terrain_collision(Rectangle const& r);

  /**
   * Solve collisions between a moving rect and whatever it was colliding with.
   * Will attempt to figure out which direction the moving rect is colliding from,
   * then move it back in the same direction until just before it collides.
   * @param moving_rect Current position of moving rect
   * @param moving_from Original position of the moving rect. Used to figure out direction
   * @param collision_target The rectangle the moving rect is colliding with
   */
  void handle_collision(Sprite& moving_rect, Rectangle const& moving_from,
                        Rectangle const& collision_target);

  /**
   * Request the player to update for current tick
   * @param commands  All actions requested by the human player
   */
  void do_player_update(std::list<Player::MovementCommand> commands);

  /**
   * Request all projectiles to update for current tick
   */
  void do_projectile_updates();

  /**
   * Delete a single projectile from the list of active projectiles.
   * This will delete the projectile at the position of the iterator,
   * and move the iterator back one step before deleting, to avoid
   * the iterator becoming invalidated
   * @param it Iterator currently pointing at the element to be deleted
   */
  void delete_projectile(std::list<Projectile*>::iterator& it);

};

#endif /* GAME_STATE_H_ */
