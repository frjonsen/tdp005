/*
 * end_state.cc
 *
 *  Created on: 15 dec 2014
 *      Author: alest170
 */

#include <end_state.h>
#include <SDL2/SDL.h>
#include <iostream>

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
  TextTexture geek_score_{"9000", 426, 411};
//  std::cout << geek_score_.kText << std::endl;
  std::list<TextTexture> score_list_
  {
    geek_score_
  };

  return score_list_;
}

std::string EndState::get_background() const
{
  return background_src_;
}
