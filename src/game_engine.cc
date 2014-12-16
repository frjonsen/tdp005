/*
 * game_engine.cc
 *
 *  Created on: Dec 5, 2014
 *      Author: vakz
 */

#include "game_engine.h"
#include <iostream>

GameEngine::GameEngine()
    : is_{}, go_{}, graphics_engine_ {
        kGameTitle, kWindowWidth, kWindowHeight, ps_.kWorldWidth,
        ps_.kWorldHeight }


{
  active_state_ = &is_;
}

void GameEngine::run()
{
  using GameInput = AbstractGameState::GameInput;
  size_t time_per_frame { 1000 / ps_.kFPSGoal };

  while (engine_running_)
  {
    size_t start_time { SDL_GetTicks () };

    std::list<GameInput> tick_input;
    handle_input_translation (tick_input);

    // Ask activate state to update for this tick
    AbstractGameState::StateCommand cmd { active_state_->update (tick_input) };
    handle_state_command (cmd);
    graphics_engine_.set_background (active_state_->get_background ());
    graphics_engine_.set_viewport (active_state_->get_viewport ());
    graphics_engine_.redraw_screen (active_state_->get_sprites (), active_state_->get_texts());

    size_t end_time { SDL_GetTicks () };
    size_t difference { end_time - start_time };
    if (difference < time_per_frame)
    {
      SDL_Delay (time_per_frame - difference);
    }
  }
}

void GameEngine::handle_state_command(AbstractGameState::StateCommand cmd)
{
  using StateCommand = AbstractGameState::StateCommand;

  switch (cmd)
  {
    case StateCommand::kPlay:
      active_state_ = &ps_;
      break;
    case StateCommand::kExit:
      engine_running_ = false;
      break;
    case StateCommand::kMenu:
      // TODO: Add some way to set whether "Resume" or "Start New Game"
      // (Overload () operator to take a string and return *this?
      //active_state_ = &(is_("Resume"));
     active_state_ = &is_;
      break;
    case StateCommand::kWin:
      go_.set_end_type("kWin");
      active_state_ = &go_;
      break;
    case StateCommand::kKilled:
      go_.set_end_type("kKilled");
      active_state_ = &go_;
      // TODO: Change variable to see what kind
      break;
    case StateCommand::kFell:
      go_.set_end_type("kFell");
      active_state_ = &go_;
      break;
    case StateCommand::kOutOfTime:
      active_state_ = &go_;
      break;
    case StateCommand::kNone:
      // Do nothing
      break;
  }
}

void GameEngine::handle_input_translation(
    std::list<AbstractGameState::GameInput>& tick_input)
{
  using GameInput = AbstractGameState::GameInput;

  SDL_PumpEvents ();

  const Uint8* state { SDL_GetKeyboardState (nullptr) };

  if (state[SDL_SCANCODE_UP])
  {
    tick_input.push_back (GameInput::kUp);
  }
  if (state[SDL_SCANCODE_LEFT])
  {
    tick_input.push_back (GameInput::kLeft);
  }
  if (state[SDL_SCANCODE_RIGHT])
  {
    tick_input.push_back (GameInput::kRight);
  }
  if (state[SDL_SCANCODE_DOWN])
  {
    tick_input.push_back (GameInput::kDown);
  }
  if (state[SDL_SCANCODE_ESCAPE])
  {
    tick_input.push_back (GameInput::kEscape);
    active_state_ = &is_;

  }
  if (state[SDL_SCANCODE_RETURN])
  {
    tick_input.push_back (GameInput::kReturn);
  }
  if (state[SDL_SCANCODE_SPACE])
  {
    tick_input.push_back (GameInput::kSpace);
  }
  if (state[SDL_SCANCODE_Q])
  {
    engine_running_ = false;
  }
}

