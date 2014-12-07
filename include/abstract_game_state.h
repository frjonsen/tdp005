/*
 * abstract_game_state.h
 *
 *  Created on: Dec 5, 2014
 *      Author: vakz
 */

#ifndef ABSTRACT_GAME_STATE_H_
#define ABSTRACT_GAME_STATE_H_

#include <vector>

class AbstractGameState
{
public:
  virtual ~AbstractGameState();

  enum class StateCommand
  {
    kPlay, kMenu, kExit, kGameOver,
  };

  enum class GameInput
  {
    kUp, kRight, kLeft, kSpace, kEscape, kReturn
  };

  virtual StateCommand update(std::vector<GameInput> const&) = 0;
  virtual int get_viewport_x() const;
  virtual int get_viewport_y() const;

};

#endif /* ABSTRACT_GAME_STATE_H_ */
