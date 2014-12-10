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

class AbstractGameState;

class GameEngine
{
  AbstractGameState * const active_state_;

  const std::string kGameTitle{"Geek Hero"};
  const int kWindowHeight{600};
  const int kWindowWidth{800};

  const int kGravity;
  const size_t kFrameTimeGoal;

  //IntroState is_;
  //PlayState ps_;
  //GameOverState gos_;

  bool engine_running_;

  void handle_state_command(AbstractGameState::StateCommand cmd);

public:
  GameEngine();

  GameEngine(GameEngine const&) = delete;
  GameEngine(GameEngine&&) = delete;

  GameEngine& operator=(GameEngine const&) = delete;
  GameEngine& operator=(GameEngine&&) = delete;

  void run();

};

#endif /* GAME_ENGINE_H_ */
