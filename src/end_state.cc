/*
 * end_state.cc
 *
 *  Created on: 15 dec 2014
 *      Author: alest170
 */

#include <end_state.h>
#include <SDL2/SDL.h>

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
  return StateCommand::kNone;
}

std::list<Sprite const*> EndState::get_sprites() const
    {
  std::list<Sprite const*> empty;

  return empty;
    }

std::list <TextTexture> EndState::get_texts() const
{
  std::list<TextTexture> empty;

  return empty;
}

std::string EndState::get_background() const
{
  return background_src_;
}
