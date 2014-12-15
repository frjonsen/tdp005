/*
 * abstract_game_state.h
 *
 *  Created on: Dec 5, 2014
 *      Author: vakz
 */

#ifndef ABSTRACT_GAME_STATE_H_
#define ABSTRACT_GAME_STATE_H_

#include <list>
#include <sprite.h>
#include <utility>
#include <string>
#include <text_texture.h>

/**
 * Common base class for all state classes
 */
class AbstractGameState
{
public:
  virtual ~AbstractGameState()
  {
  }

  /**
   *  All commands states can returned to be handled
   *  by the game engine.
   */
  enum class StateCommand
  {
    kPlay, kMenu, kExit, kKilled, kFell, kWin, kNone, kOutOfTime
  };

  /**
   * The commands sent by the game engine expected
   * to be handled by the state.
   */
  enum class GameInput
  {
    kUp, kRight, kLeft, kSpace, kEscape, kReturn, kDown
  };

  /**
   * Request the state to update itself
   * @param input All input from the game engine to the state
   * @return A StateCommand to be handled by the engine
   */
  virtual StateCommand update(std::list<GameInput> const& input) = 0;

  /**
   * The current viewport of the state.
   * @return x and y coordinates for the upper left corner of the viewport
   */
  virtual std::pair<int, int> get_viewport() const
  {
    return std::make_pair (0, 0);
  }

  /**
   * Get all active sprites
   * @return A list consisting of all active sprites in the state
   */
  virtual std::list<Sprite const*> get_sprites() const = 0;

  /**
   * Get the filename of the current background being used
   * @return Filename of background
   */
  virtual std::string get_background() const = 0;

  virtual std::list<TextTexture> get_texts() const = 0;

};

#endif /* ABSTRACT_GAME_STATE_H_ */
