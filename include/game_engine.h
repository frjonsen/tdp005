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
  const size_t kFrameTimeGoal { 1000 / 60 };

  bool engine_running_ { true };
  AbstractGameState* active_state_ { nullptr };

  MenuState is_;
  PlayState ps_{};

  //GameOverState gos_;

  GraphicsEngine graphics_engine_;

  void handle_state_command(AbstractGameState::StateCommand cmd);
  void handle_input_translation(std::list<AbstractGameState::GameInput>&);

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
