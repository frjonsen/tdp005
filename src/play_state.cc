/*
 * game_state.cc
 *
 *  Created on: Dec 8, 2014
 *      Author: frejo105
 */

#include "play_state.h"

PlayState::PlayState(const int gravity)
{

}

PlayState::~PlayState()
{

}

AbstractGameState::StateCommand PlayState::update(std::vector<GameInput> const&)
{
  return StateCommand::kPlay;
}

std::pair<int, int> PlayState::get_viewport() const
{
  return std::make_pair (0, 0);
}

std::vector<Sprite const*> PlayState::get_sprites() const
{
  return std::vector<Sprite const*> ();
}
