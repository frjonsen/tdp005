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

class PlayState : public AbstractGameState
{
public:
  PlayState(const int gravity);
  ~PlayState();

  PlayState(PlayState const&) = delete;
  PlayState(PlayState&&) = delete;

  PlayState& operator=(PlayState const&) = delete;
  PlayState& operator=(PlayState&&) = delete;

  StateCommand update(std::vector<GameInput> const& input);
  std::vector<Sprite const*> get_sprites() const;
  std::string get_background() const;
  std::pair<int, int> get_viewport() const;

private:

  const int kGravity;

  Player player_;
  std::vector<Rectangle> terrain_;
  std::string background_ { "TESTGROUND.png" };

  std::vector<Player::MovementCommand> translate_input(
      std::vector<GameInput> const& input);

  void generate_terrain();
  std::vector<Rectangle *> check_terrain_collision(Rectangle const& r);
  void handle_collision(Sprite& moving_rect, Rectangle const& moving_from,
                       Rectangle const& collision_target);
  void do_player_update(std::vector<Player::MovementCommand> commands);

};

#endif /* GAME_STATE_H_ */