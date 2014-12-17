/*
 * game_engine.h
 *
 *  Created on: Nov 26, 2014
 *      Author: frejo105
 */

#ifndef GAME_ENGINE_H_
#define GAME_ENGINE_H_

#include <SDL2/SDL.h>
#include <string>
#include "abstract_game_state.h"
#include "graphics_engine.h"
#include "play_state.h"
#include "menu_state.h"
#include "end_state.h"


/**
 * Game engine handling input and game loop
 */
class GameEngine
{

  // Constants
  /// Window title
  const std::string kGameTitle { "Geek Hero" };
  /// Window Height
  const int kWindowHeight { 600 };
  /// Window Width
  const int kWindowWidth { 800 };

  /// Minimum time per frme
  const size_t kFrameTimeGoal { 1000 / 60 };

  /// Should engine keep running
  bool engine_running_ { true };
  /// Current active state
  AbstractGameState* active_state_ { nullptr };

  /// Menu state instance
  MenuState is_;
  /// End state instance
  EndState go_;
  /// Play state instance
  PlayState ps_{};


  /// Graphics engine used to render screen
  GraphicsEngine graphics_engine_;

  /**
   * Used to handle the StateCommand returned by state after
   * requesting an update
   * @param cmd The command to handle
   */
  void handle_state_command(AbstractGameState::StateCommand cmd);

  /**
   * Translate the input given by SDL to enums the states understand
   * @param tick_input Output parameter to store GameInputs in
   */
  void handle_input_translation(std::list<AbstractGameState::GameInput>& tick_input);

public:
  GameEngine();

  /// Deleted copy constructor
  GameEngine(GameEngine const&) = delete;
  /// Deleted move constructor
  GameEngine(GameEngine&&) = delete;

  /// Deleted assignment operator
  GameEngine& operator=(GameEngine const&) = delete;

  /// Deleted move-assignment operator
  GameEngine& operator=(GameEngine&&) = delete;

  /**
   * Start the game engine
   */
  void run();

};

#endif /* GAME_ENGINE_H_ */
