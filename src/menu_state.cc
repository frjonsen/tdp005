/*
 * menu.cc
 *
 *  Created on: 10 dec 2014
 *      Author: alest170
 */


#include <menu_state.h>

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
    std::vector<MenuState::GameInput> const& input)
{
  for (GameInput i : input)
  {
    switch (i)
    {
      case GameInput::kUp:
        selected_ = MenuPointer ( (int ( selected_ ) - 1 % 3) );
        break;
      case GameInput::kDown:
        selected_ = MenuPointer ( (int ( selected_ ) + 1 % 3) );
        break;
      case GameInput::kReturn:
        return_handler ();
        break;
      case GameInput::kEscape:
        current_ = MenuDirectory::kRoot;
        break;
      default:
        break;
    }
  }
  return StateCommand::kMenu;
}

//Returns the menu selector as a vector of sprites
std::vector<Sprite const*> MenuState::get_sprites() const
{
  std::vector<Sprite const*> CoffeVector;
  CoffeVector.push_back ( &coffe_cup_ );

  return CoffeVector;
}

//Returns the location of the currently used background as a string.
std::string MenuState::get_background() const
{
  return background_src_;
}

