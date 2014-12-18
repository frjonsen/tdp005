/*
 * menu.cc
 *
 *  Created on: 10 dec 2014
 *      Author: alest170
 */

#include <SDL2/SDL.h>
#include <menu_state.h>
#include <highscore_handler.h>



//Handles the return key for the update function.
MenuState::StateCommand MenuState::return_handler()
{
  if( selected_ == MenuPointer::kPlay )
  {
    return StateCommand::kPlay;
  }
  else if( selected_ == MenuPointer::kHighscore )
  {
    current_ = MenuDirectory::kHighscore;
  }
  else if( selected_ == MenuPointer::kControls )
  {
    current_ = MenuDirectory::kControls;
  }

  return StateCommand::kMenu;
}

//Updates background, selector location and if game state should change.
MenuState::StateCommand MenuState::update(
    std::list<MenuState::GameInput> const& input)
{
  background_src_ =
  { backgrounds_.at (current_)};

  for (GameInput i : input)
  {
    switch (i)
    {
      case GameInput::kUp:
      if (!keydown_)
      {
        selected_ = MenuPointer ( ((int ( selected_ ) + 2) % 3) );
        keydown_ = true;
        break;
      }
      break;
      case GameInput::kDown:
      if (!keydown_)
      {
        selected_ = MenuPointer ( ((int ( selected_ ) + 1) % 3) );
        keydown_ = true;
        break;
      }
      break;
      case GameInput::kReturn:
      return return_handler ();
      break;
      case GameInput::kEscape:
      current_ = MenuDirectory::kRoot;
      break;
      default:
      break;
    }
  }

  coffe_cup_.set_x(std::get<0> (selector_coordinates_.at (selected_)));
  coffe_cup_.set_y(std::get<1> (selector_coordinates_.at (selected_)));

  if (input.size() == 0) keydown_ = false;

  return StateCommand::kNone;
}

//Returns the menu selector as a vector of sprites
std::list<Sprite const*> MenuState::get_sprites() const
{
  std::list<Sprite const*> empty;
  std::list<Sprite const*> CoffeVector { &coffe_cup_ };

  if( current_ == MenuDirectory::kRoot )
  {
    return CoffeVector;
  }
  else
  {
    return empty;
  }
}

std::list<TextTexture> MenuState::get_texts() const
{

  if( current_ == MenuDirectory::kHighscore )
  {
    Highscore scoreboard_;

    TextTexture first_place_ { scoreboard_.get_highscore ().at ( 0 ), 374, 280 };
    TextTexture second_place_ { scoreboard_.get_highscore ().at ( 1 ), 374, 361 };
    TextTexture third_place_ { scoreboard_.get_highscore ().at ( 2 ), 374, 442 };

    std::list<TextTexture> scores_ { first_place_, second_place_, third_place_ };

    return scores_;
  }

  std::list<TextTexture> empty;

  return empty;
}

//Returns the location of the currently used background as a string.
std::string MenuState::get_background() const
{
  return background_src_;

}
