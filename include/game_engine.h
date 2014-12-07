/*
 * game_engine.h
 *
 *  Created on: Nov 26, 2014
 *      Author: frejo105
 */

#ifndef GAME_ENGINE_H_
#define GAME_ENGINE_H_

#include <SDL2/SDL.h>

class AbstractGameState;

class GameEngine
{
  AbstractGameState * const active_state_;

  const int kGravity;
  const size_t kFrameTimeGoal;

  //IntroState is_;
  //PlayState ps_;
  //GameOverState gos_;

  bool engine_running_;

  void handle_state_command(AbstractGameState::StateCommand cmd);

public:
  GameEngine();
  void run();

};

#endif /* GAME_ENGINE_H_ */
