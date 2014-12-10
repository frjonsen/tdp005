/*
 * GameState.h
 *
 *  Created on: Dec 8, 2014
 *      Author: frejo105
 */

#ifndef GAME_STATE_H_
#define GAME_STATE_H_

#include "abstract_game_state.h"

class PlayState : public AbstractGameState
{
  PlayState(const int gravity);
  ~PlayState();

  PlayState(PlayState const&) = delete;
  PlayState(PlayState&&) = delete;

  PlayState& operator=(PlayState const&) = delete;
  PlayState& operator=(PlayState&&) = delete;

  StateCommand update(std::vector<GameInput> const& input);
  std::pair<int, int> get_viewport() const;
  std::vector<Sprite const*> get_sprites() const;
};

#endif /* GAME_STATE_H_ */
