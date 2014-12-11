/*
 * menu.cc
 *
 *  Created on: 10 dec 2014
 *      Author: alest170
 */


#include <menu_state.h>

MenuState::StateCommand MenuState::update(std::vector<MenuState::GameInput> const&)
{
 MenuState::StateCommand nejje{StateCommand::kExit};

 return nejje;
}

std::vector<Sprite const*> MenuState::get_sprites() const
{
  std::vector<Sprite const*> hej;

  return hej;
}

std::string MenuState::get_background() const
{
  std::string hej;

  return hej;
}
