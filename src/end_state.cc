/*
 * end_state.cc
 *
 *  Created on: 15 dec 2014
 *      Author: alest170
 */

#include <end_state.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <highscore_handler.h>

 EndState* EndState::operator()(EndState::EndDirectory end_type, int score)
 {
   Highscore check;
   score_ = std::to_string(score);

   if ( end_type == EndState::EndDirectory::kWin )
   {
     check.add_score(score);
     check.handle_highscore();
   }
   return this;
 }

void EndState::set_end_type(std::string end_type_)
{
  if ( end_type_ == "kKilled" )
  {
    EndState::current_ =  EndState::EndDirectory::kKilled;
  }
  else if ( end_type_ == "kFell" )
  {
    EndState::current_ = EndState::EndDirectory::kFell;
  }
  else
  {
    EndState::current_ = EndState::EndDirectory::kWin;
  }
}

EndState::StateCommand EndState::update(std::list<EndState::GameInput> const& input)
{
  background_src_ = { current_background_.at(current_) };
  return StateCommand::kNone;
}

std::list<Sprite const*> EndState::get_sprites() const
    {
  std::list<Sprite const*> empty;

  return empty;
    }

std::list <TextTexture> EndState::get_texts() const
{

  if ( current_ == EndState::EndDirectory::kWin )
  {
    TextTexture game_score_{score_, 426, 411};

    std::list<TextTexture> score_list_
    {
      game_score_
    };
  return score_list_;
  }

  std::list<TextTexture> empty;
  return empty;
}

std::string EndState::get_background() const
{
  return background_src_;
}
