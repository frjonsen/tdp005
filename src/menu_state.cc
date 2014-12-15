/*
 * menu.cc
 *
 *  Created on: 10 dec 2014
 *      Author: alest170
 */


#include <menu_state.h>
#include <iostream>
#include <SDL2/SDL.h>

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
  background_src_ = {current_background_.at (current_) };

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
  std::list<Sprite const*> CoffeVector
  {
    &coffe_cup_
  };

  if (current_ == MenuDirectory::kRoot)
  {
    return CoffeVector;
  }
  else
  {
  return empty;
  }
}

//Returns the location of the currently used background as a string.
std::string MenuState::get_background() const
{
  return background_src_;

}

