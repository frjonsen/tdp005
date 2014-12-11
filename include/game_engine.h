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

class AbstractGameState;

class GameEngine {

	// Constants
	const std::string kGameTitle { "Geek Hero" };
	const int kWindowHeight { 600 };
	const int kWindowWidth { 800 };
	const int kGravity { 1 };
	const size_t kFrameTimeGoal { 1000 / 60 };

	GraphicsEngine graphics_engine_;
	bool engine_running_ { true };
	AbstractGameState* active_state_ { nullptr };

	MenuState is_;
	PlayState ps_;
	//GameOverState gos_;

	void handle_state_command(AbstractGameState::StateCommand cmd);
	void handle_input_translation(std::vector<AbstractGameState::GameInput>&);

public:
	GameEngine();

	GameEngine(GameEngine const&) = delete;
	GameEngine(GameEngine&&) = delete;

	GameEngine& operator=(GameEngine const&) = delete;
	GameEngine& operator=(GameEngine&&) = delete;

	void run();

};

#endif /* GAME_ENGINE_H_ */
