/*
 * game_engine.cc
 *
 *  Created on: Dec 5, 2014
 *      Author: vakz
 */

#include "game_engine.h"
#include "graphics_engine.h"
#include <vector>

GameEngine::GameEngine()
    : active_state_ { nullptr }, kGravity { 5 }, kFrameTimeGoal { 1000 / 60 },
      engine_running_ { true }

{
  //active_state_ = &is_;
}

void GameEngine::run()
{
  using GameInput = AbstractGameState::GameInput;
  GraphicsEngine ge{kGameTitle, kWindowWidth, kWindowHeight};

  while (engine_running_)
  {
    size_t start_time { SDL_GetTicks () };

    std::vector<GameInput> tick_input;

    SDL_Event event;
    while (SDL_PollEvent (&event))
    {
      if (event.type == SDL_KEYDOWN)
      {
        switch (event.key.keysym.sym)
        {
          case SDLK_ESCAPE:
            tick_input.push_back (GameInput::kEscape);
            break;
          case SDLK_SPACE:
            tick_input.push_back (GameInput::kSpace);
            break;
          case SDLK_RETURN:
            tick_input.push_back (GameInput::kReturn);
            break;
          case SDLK_UP:
            tick_input.push_back (GameInput::kUp);
            break;
          case SDLK_RIGHT:
            tick_input.push_back (GameInput::kRight);
            break;
          case SDLK_LEFT:
            tick_input.push_back (GameInput::kLeft);
            break;
        }
      }
    }

    // Ask activate state to update for this tick
    AbstractGameState::StateCommand cmd { active_state_->update (tick_input) };
    handle_state_command (cmd);

    size_t end_time { SDL_GetTicks () };
    size_t difference { end_time - start_time };
    if (difference < kFrameTimeGoal)
    {
      SDL_Delay (difference - kFrameTimeGoal);
    }

  }
}

void GameEngine::handle_state_command(AbstractGameState::StateCommand cmd)
{
  using StateCommand = AbstractGameState::StateCommand;

  switch (cmd)
  {
    case StateCommand::kPlay:
      //active_state_ = &ps_;
      break;
    case StateCommand::kExit:
      engine_running_ = false;
      break;
    case StateCommand::kMenu:
      // TODO: Add some way to set whether "Resume" or "Start New Game"
      // (Overload () operator to take a string and return *this?
      //active_state_ = &is_;
      break;
    case StateCommand::kGameOver:
      // TODO: Add reset
      break;
  }
}

