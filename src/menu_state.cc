/*
 * menu.cc
 *
 *  Created on: 10 dec 2014
 *      Author: alest170
 */


#include <menu_state.h>

MenuState::StateCommand MenuState::return_handler()
{
  if (selected_ == MenuPointer::kPlay)
  {
    return StateCommand::kPlay;
  }
  else if ( selected_ == MenuPointer::kHighscore)
  {
    current_ = MenuDirectory::kHighscore;
  }
  else if ( selected_ == MenuPointer::kControls)
  {
    current_ = MenuDirectory::kControls;
  }

  return StateCommand::kMenu;
}

MenuState::StateCommand MenuState::update(std::vector<MenuState::GameInput> const& input)
{
 MenuState::StateCommand nejje{StateCommand::kExit};

 std::vector<MenuPointer> menu_select;



 for (GameInput i : input)
  {
    switch (i)
    {
      case GameInput::kUp:
        selected_ = MenuPointer((int(selected_) - 1 % 3));
        break;
      case GameInput::kDown:
        selected_ = MenuPointer((int(selected_) + 1 % 3));
        break;
      case GameInput::kReturn:
        return_handler();
        break;
      case GameInput::kEscape:
        current_ = MenuDirectory::kRoot;
        break;
      default:
        break;
    }
  }



 return nejje;
}

std::vector<Sprite const*> MenuState::get_sprites() const
{
  std::vector<Sprite const*> CoffeVector;
  CoffeVector.push_back (&coffe_cup_);

  return CoffeVector;
}

std::string MenuState::get_background() const
{
  return background_src_;
}

