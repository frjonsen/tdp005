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

class GameEngine {
	AbstractGameState *const active_state_;

	// TODO: Better constants
	const int kGravity;
	const int kFrameTimeGoal;

	IntroState is;
	PlayState ps;
	GameOverState gos;

	GameEngine() :
			kGravity { 5 }, kFrameTimeGoal { 1000 / 60 } {
		active_state_ = &is;
	}

	void run();

};

#endif /* GAME_ENGINE_H_ */
