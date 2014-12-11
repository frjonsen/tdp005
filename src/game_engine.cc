/*
 * game_engine.cc
 *
 *  Created on: Dec 5, 2014
 *      Author: vakz
 */

#include "game_engine.h"
#include <vector>
#include <iostream>

GameEngine::GameEngine()
    : graphics_engine_ { kGameTitle, kWindowWidth, kWindowHeight, kWorldWidth,
        kWorldHeight }, ps_ { kGravity }

{
  active_state_ = &is_;
}

void GameEngine::run()
{
  using GameInput = AbstractGameState::GameInput;
  while (engine_running_)
  {
    size_t start_time { SDL_GetTicks () };

    std::vector<GameInput> tick_input;
    handle_input_translation (tick_input);

    if (!engine_running_) break; // Special case to break if player pressed the window close button.

    // Ask activate state to update for this tick
    AbstractGameState::StateCommand cmd { active_state_->update (tick_input) };
    handle_state_command (cmd);
    graphics_engine_.set_background (active_state_->get_background ());
    graphics_engine_.set_viewport (active_state_->get_viewport ());
    graphics_engine_.redraw_screen (active_state_->get_sprites ());

    size_t end_time { SDL_GetTicks () };
    size_t difference { end_time - start_time };
    if (difference < kFrameTimeGoal)
    {
      SDL_Delay (kFrameTimeGoal - difference);
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
      //active_state_ = &(is_("Resume"));
      break;
    case StateCommand::kGameOver:
      // TODO: Add reset
      break;
    case StateCommand::kNone:
      // Do nothing
      break;
  }
}
/*
 void GameEngine::handle_input_translation(
 std::vector<AbstractGameState::GameInput>& tick_input)
 {
 using GameInput = AbstractGameState::GameInput;
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
 else if (event.type == SDL_QUIT)
 {
 engine_running_ = false;
 }
 }
 }
 */

void GameEngine::handle_input_translation(
    std::vector<AbstractGameState::GameInput>& tick_input)
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

