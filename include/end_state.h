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

/**
 * State representing the end of the game
 */
class EndState : public AbstractGameState
{
public:

  StateCommand update(std::list<GameInput> const& input);
  std::list<Sprite const*> get_sprites() const;
  std::list<TextTexture> get_texts() const;
  std::string get_background() const;

  /// Sets the end type for state. If reached by loss or win
  void set_end_type(std::string end_type_);

  EndState* operator()(EndState::EndDirectory end_type, int score);

  /// Names of end state types
  enum class EndDirectory
  {
    kKilled, kFell, kWin
  };

private:

  /// Map of backgrounds for end states
  std::map<EndDirectory, std::string> current_background_ { {
      EndDirectory::kKilled, "game_over_caffeine.png" }, {
      EndDirectory::kFell, "game_over_fly.png" }, {
      EndDirectory::kWin, "game_over_win.png" } };

  /// Current end state type
  EndDirectory current_ { EndDirectory::kWin };

  /// Currently active background
  std::string background_src_{ current_background_.at(current_) };

};
#endif /* END_STATE_H_ */
