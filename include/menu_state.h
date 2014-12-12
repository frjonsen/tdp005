/*
 * menu_state.h
 *
 *  Created on: 9 dec 2014
 *      Author: alest170
 */

#ifndef MENU_STATE_H_
#define MENU_STATE_H_

#include <abstract_game_state.h>
#include <vector>
#include <map>
#include <string>
#include <utility>

class MenuState : public AbstractGameState
{

public:
  //MenuState();

  StateCommand update(std::vector<GameInput> const&);

  std::vector<Sprite const*> get_sprites() const;

  std::string get_background() const;

  void set_background();

private:
  enum class MenuPointer
  {
    kPlay, kHighscore, kControls
  };

  enum class MenuDirectory
  {
    kRoot, kHighscore, kControls
  };

  MenuPointer selected_ { MenuPointer::kPlay };
  MenuDirectory current_ { MenuDirectory::kRoot };
  std::string background_src_ { current_background_[current_] };

  std::map<MenuPointer, std::pair<int, int>> selector_coordinates_ { {
      MenuPointer::kPlay, { 310, 240 } }, { MenuPointer::kHighscore,
      { 240, 315 } }, { MenuPointer::kControls, { 260, 385 } } };

  std::map<MenuDirectory, std::string> current_background_ { {
      MenuDirectory::kRoot, "images/root_background.png" }, {
      MenuDirectory::kHighscore, "images/highscore_background.png" }, {
      MenuDirectory::kControls, "images/controls_background.png" } };

  int coffe_x { std::get < 0 > (selector_coordinates_.at ( selected_ )) };
  int coffe_y { std::get < 1 > (selector_coordinates_.at ( selected_ )) };

  Sprite coffe_cup_ { "images/coffe.png", { coffe_x, coffe_y, 51, 40 }, { 0, 0 } };

  StateCommand return_handler();


};
#endif /* INCLUDE_MENU_STATE_H_ */
