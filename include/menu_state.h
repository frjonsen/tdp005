/*
 * menu_state.h
 *
 *  Created on: 9 dec 2014
 *      Author: alest170
 */

#ifndef MENU_STATE_H_
#define MENU_STATE_H_

#include <abstract_game_state.h>
#include <map>
#include <string>
#include <utility>

/**
 * State representing the menu of the game
 */

class MenuState : public AbstractGameState
{

public:

  StateCommand update(std::list<GameInput> const&);
  std::list<Sprite const*> get_sprites() const;
  std::list<TextTexture> get_texts() const;
  std::string get_background() const;

  void set_background();

private:
  /// Names of current selected menu item
  enum class MenuPointer
  {
    kPlay, kHighscore, kControls
  };

  /// Names of current active menu section
  enum class MenuDirectory
  {
    kRoot, kHighscore, kControls
  };

  /// Map of background images for current menu section
  std::map<MenuDirectory, std::string> current_background_ { {
      MenuDirectory::kRoot, "root_background.png" }, {
      MenuDirectory::kHighscore, "highscore_background.png" }, {
      MenuDirectory::kControls, "controls_background.png" } };

  /// Selected menu item
  MenuPointer selected_ { MenuPointer::kPlay };

  /// Current active menu section
  MenuDirectory current_ { MenuDirectory::kRoot };

  /// Background image
  std::string background_src_ { current_background_.at (current_) };

  /// Map of x:y coordinates for menu selector
  std::map<MenuPointer, std::pair<int, int>> selector_coordinates_ { {
      MenuPointer::kPlay, { 310, 240 } }, {
      MenuPointer::kHighscore, { 240, 315 } }, { MenuPointer::kControls, {
      260, 385 } } };

  /// X coordinate for menu selector
  int coffe_x { std::get<0> (selector_coordinates_.at (selected_)) };

  /// Y coordinate for menu selector
  int coffe_y { std::get<1> (selector_coordinates_.at (selected_)) };

  /// Controls if a key is pressed
  bool keydown_{false};

  /// Texture of the menu selector
  Sprite coffe_cup_ { "coffe.png", { coffe_x, coffe_y, 51, 40 }, 0 };

  /// Handles return key in menu
  StateCommand return_handler();

};
#endif /* INCLUDE_MENU_STATE_H_ */
