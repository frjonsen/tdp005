/*
 * game_engine.cc
 *
 *  Created on: Dec 5, 2014
 *      Author: vakz
 */

#include "game_engine.h"
#include "gameinput.h"
#include <vector>

void GameEngine::run() {

	while (true) {
		size_t start_time{SDL_GetTicks()};

		std::vector<GameInput> tick_input;

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN){
				switch(event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					tick_input.push_back(GameInput::kEscape);
					break;
				case SDLK_SPACE:
					tick_input.push_back(GameInput::kSpace);
					break;
				case SDLK_RETURN:
					tick_input.push_back(GameInput::kReturn);
					break;
				case SDLK_UP:
					tick_input.push_back(GameInput::kUp);
					break;
				case SDLK_RIGHT:
					tick_input.push_back(GameInput::kRight);
					break;
				case SDLK_LEFT:
					tick_input.push_back(GameInput::kLeft);
					break;
				}
			}
		}

		active_state_->update(tick_input);

		size_t end_time{SDL_GetTicks()};
		size_t difference{end_time - start_time};
		if (difference < kFrameTimeGoal)
		{
			SDL_Delay(difference - kFrameTimeGoal);
		}

	}
}

