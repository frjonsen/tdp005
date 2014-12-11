/*
 * abstract_game_state.h
 *
 *  Created on: Dec 5, 2014
 *      Author: vakz
 */

#ifndef ABSTRACT_GAME_STATE_H_
#define ABSTRACT_GAME_STATE_H_

#include <vector>
#include <sprite.h>
#include <utility>
#include <string>

class AbstractGameState
{
public:
  virtual ~AbstractGameState() {}

  enum class StateCommand
  {
    kPlay, kMenu, kExit, kGameOver, kNone
  };

  enum class GameInput
  {
    kUp, kRight, kLeft, kSpace, kEscape, kReturn
  };

  virtual StateCommand update(std::vector<GameInput> const&) = 0;
  virtual std::pair<int, int> get_viewport() const { return std::make_pair(0,0); }
  virtual std::vector<Sprite const*> get_sprites() const = 0;
  virtual std::string get_background() const = 0;

};

#endif /* ABSTRACT_GAME_STATE_H_ */
