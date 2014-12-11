/*
 * game_state.cc
 *
 *  Created on: Dec 8, 2014
 *      Author: frejo105
 */

#include "play_state.h"
#include <iostream>

PlayState::PlayState(const int gravity)
    : kGravity { gravity }, player_ { "Hero_Standing_R.png",
        { 50, 340, 30, 50 }, { 1, 0 } }, terrain_ { }
{
  generate_terrain ();
}

PlayState::~PlayState()
{

}

AbstractGameState::StateCommand PlayState::update(
    std::vector<GameInput> const& input)
{
  std::vector<Player::MovementCommand> commands { translate_input ( input ) };

  do_player_update ( commands );
  return StateCommand::kNone;
}

std::pair<int, int> PlayState::get_viewport() const
{
  return std::make_pair ( player_.get_x () - 400, 0 );
}

std::vector<Sprite const*> PlayState::get_sprites() const
{
  std::vector<Sprite const*> all_sprites { &player_ };
  return all_sprites;
}

std::string PlayState::get_background() const
{
  return background_;
}

void PlayState::generate_terrain()
{
  terrain_.push_back ( { 0, 394, 149, 146 } );
  terrain_.push_back ( { 145, 540, 584, 20 } );
  terrain_.push_back ( { 433, 310, 113, 21 } );
  terrain_.push_back ( { 604, 355, 58, 38 } );
  terrain_.push_back ( { 733, 440, 82, 100 } );
  terrain_.push_back ( { 929, 440, 671, 129 } );
}

std::vector<Player::MovementCommand> PlayState::translate_input(
    std::vector<GameInput> const& input)
{
  using MovementCommand = Player::MovementCommand;

  std::vector<Player::MovementCommand> commands;

  for (GameInput i : input)
  {
    switch (i)
    {
      case GameInput::kUp:
        commands.push_back ( MovementCommand::kJump );
        break;
      case GameInput::kLeft:
        commands.push_back ( MovementCommand::kMoveLeft );
        break;
      case GameInput::kRight:
        commands.push_back ( MovementCommand::kMoveRight );
        break;
      default:
        break;
    }
  }

  return commands;
}

void PlayState::do_player_update(std::vector<Player::MovementCommand> commands)
{
  Rectangle before { player_ };
  player_.order_player ( commands );
  player_.handle_gravity ( kGravity );
  std::vector<Rectangle *> collisions { check_terrain_collision ( player_ ) };
  if (collisions.size () != 0)
  {
    for (Rectangle * r : collisions)
    {
      handle_collision ( player_, before, *r );
    }
  }
}

void PlayState::handle_collision(Sprite& sprite, Rectangle const& moving_from,
                                 Rectangle const& collision_target)
{
  int moving_bottom { moving_from.get_y () + moving_from.get_height () };
  int moving_right { moving_from.get_x () + moving_from.get_width () };
  if (moving_right <= collision_target.get_x ()) // Moving object was enteirly to the left
  {
    sprite.set_x ( collision_target.get_x () - sprite.get_width () );
  }
  if (moving_bottom <= collision_target.get_y ()) // Moving object was enteirly above
  {
    sprite.set_y ( collision_target.get_y () - sprite.get_height () );
    sprite.reset_y_velocity ();
  }
  if (moving_from.get_x ()
      >= collision_target.get_x () + collision_target.get_width ()) // Moving object was to the right
  {
    sprite.set_x ( collision_target.get_x () + collision_target.get_width () );
  }
}

std::vector<Rectangle*> PlayState::check_terrain_collision(Rectangle const& r)
{
  std::vector<Rectangle *> collisions;
  for (Rectangle& t : terrain_)
  {
    if (r.intersect ( t ))
    {
      collisions.push_back ( &t );
    }
  }
  return collisions;
}
