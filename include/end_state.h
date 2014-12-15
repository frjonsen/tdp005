/*
 * end_state.h
 *
 *  Created on: 15 dec 2014
 *      Author: alest170
 */

#ifndef END_STATE_H_
#define END_STATE_H_

#include <abstract_game_state.h>
#include <string>
#include <map>


class EndState : public AbstractGameState
{
public:

  StateCommand update(std::list<GameInput> const& input);
  std::list<Sprite const*> get_sprites() const;
  std::list<TextTexture> get_texts() const;
  std::string get_background() const;

  void set_end_type(std::string end_type_);

private:
  enum class EndDirectory
  {
    kKilled, kFell, kWin
  };

  std::map<EndDirectory, std::string> current_background_ { {
      EndDirectory::kKilled, "game_over_caffeine.png" }, {
      EndDirectory::kFell, "game_over_fly.png" }, {
      EndDirectory::kWin, "game_over_win.png" } };

  EndDirectory current_ { EndDirectory::kWin };

  Sprite score_ { "coffe.png", { 475, 380, 51, 40 }, 0 };

  std::string background_src_{ current_background_.at(current_) };

};
#endif /* END_STATE_H_ */
