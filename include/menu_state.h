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


class MenuState : public AbstractGameState
{
public:
  MenuState(Renderer&);

  StateCommand update(std::vector<GameInput> const&);
  std::vector<Sprite const*> get_sprites() const;
  std::string get_background() const;

private:
  enum class MenuPointer
  {
    kPlay, kHighscore, kControls
  };

  MenuPointer selected { MenuPointer::kPlay };

  std::map<MenuPointer, std::pair<int, int>> selector_coordinates_ { {
      MenuPointer::kPlay, { 310, 240 } }, { MenuPointer::kHighscore,
      { 240, 315 } }, { MenuPointer::kControls, { 260, 385 } } };

};

#endif /* INCLUDE_MENU_STATE_H_ */
