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
#include <walker_enemy.h>
#include <spitter_enemy.h>
#include <runner_enemy.h>
#include <utility>
#include <vector>

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
  std::list<TextTexture> get_texts() const;
  std::string get_background() const;
  std::pair<int, int> get_viewport() const;

  /// Get the current score
  int get_score() const;

  /// Width of the game world
  const int kWorldWidth { 2400 };
  /// Height of the game world
  const int kWorldHeight { 600 };

  /// Maximum amount of frames per second
  const int kFPSGoal { 60 };

  /// Maximum amount of frames before player gets no score
  const int kTimeLimit { 60 * kFPSGoal };

  /// Directions
  enum class Direction
  {
    kLeft, kRight, kAbove, kBelow
  };

  enum class PlayerType
  {
    kFast, kNormal, kTank
  };

  PlayState* operator()(PlayerType type);

private:

  struct PlayerStats
  {
    PlayerStats(Player::TextureColor c, int h, int v)
        : color { c }, hp { h }, x_velocity { v }
    {
    }
    Player::TextureColor color;
    int hp;
    int x_velocity;
  };

  std::map<PlayerType, PlayerStats> stats_map_ { { PlayerType::kFast, {
      Player::TextureColor::kBlue, 50, 10 } }, { PlayerType::kNormal, {
      Player::TextureColor::kYellow, 100, 5 } }, { PlayerType::kTank, {
      Player::TextureColor::kRed, 200, 3 } } };

  std::vector<std::pair<int, int>> checkpoints_ { { 50, 220 }, { 930, 270 } };



  /// Game world gravity
  const int kGravity { 1 };

  /// Amount of score accumulated by the player
  int score_ { 1000 };

  /// Maximum number of frames the player has to finish the game
  int time_ { kTimeLimit };

  /// The player
  Player* player_ { new Player () };

  Sprite* powerup_ { new Sprite ("if_gun.png", { 700, 10, 40, 40 }) };

  /// A list of all terrain rectangles in the world
  std::list<Rectangle> terrain_ {};

  /// All projectiles currently in existance
  std::list<Projectile*> active_projectiles_ {};

  /// A list of all active enemies in the world
  std::list<Enemy*> enemies_ {};

  ///A list of all powerups still in the world
  std::list<Sprite*> powerups_ {};

  /// A list of all malware in the world
  std::list<Sprite*> malware_ {};

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

  /// Generate enemies in the world
  void generate_enemies();

  /// Generate powerups in the world
  void generate_powerups();

  /// Generate malware in the world
  void generate_malware();

  /**
   * Check if any terrain is currently colliding with rectangle r
   * @param r The rectangle to check for collisions
   * @return A list of all terrain r is colliding with
   */
  std::list<Rectangle *> check_terrain_collision(Rectangle const& r);

  /**
   * Attempt to figure out from which direction a moving rectangle
   * collides with a target
   * @param moving_rect The rectangle after moving
   * @param moving_from The rectangle before moving
   * @param collision_target The target being collided with
   * @return The direction from which the moving rectangle hits the target
   */
  Direction get_collision_direction(Rectangle const& moving_rect,
                                    Rectangle const& moving_from,
                                    Rectangle const& collision_target);

  /**
   * Solve collisions between a moving rect and whatever it was colliding with.
   * Will attempt to figure out which direction the moving rect is colliding from,
   * then move it back in the same direction until just before it collides.
   * @param moving_rect Current position of moving rect
   * @param moving_from Original position of the moving rect. Used to figure out direction
   * @param collision_target The rectangle the moving rect is colliding with
   */
  Direction handle_collision(Sprite& moving_rect, Rectangle const& moving_from,
                             Rectangle const& collision_target);

  /**
   * Request the player to update for current tick
   * @param commands  All actions requested by the human player
   */
  void do_player_update(std::list<Player::MovementCommand> commands);

  /// Request all enemies to update themselves for new frame
  void do_enemy_update();

  /// Request all projectiles to update for current tick
  void do_projectile_updates();

  void move_to_checkpoint();

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
