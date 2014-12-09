/*
 * game_state.cc
 *
 *  Created on: Dec 8, 2014
 *      Author: frejo105
 */

#include "game_state.h"

GameState::GameState(const int gravity)
{

}

GameState::~GameState()
{

}

AbstractGameState::StateCommand GameState::update(std::vector<GameInput> const&)
{
	return StateCommand::kPlay;
}

std::pair<int, int> GameState::get_viewport() const
{
	return std::make_pair(0,0);
}

std::vector<Sprite const*> GameState::get_sprites() const{
	return std::vector<Sprite const*>();
}
