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
        { 50, 200, 30, 53 }, { 1, 0 } }, terrain_ { }
{
  generate_terrain ();
}

PlayState::~PlayState()
{
  for (Projectile* p : active_projectiles_)
  {
    delete p;
  }
}

AbstractGameState::StateCommand PlayState::update(
    std::vector<GameInput> const& input)
{
  std::vector<Player::MovementCommand> commands { translate_input ( input ) };

  do_player_update ( commands );
  do_projectile_updates();
  return StateCommand::kNone;
}

std::pair<int, int> PlayState::get_viewport() const
{
  return std::make_pair ( player_.get_x () - 400, 0 );
}

std::vector<Sprite const*> PlayState::get_sprites() const
{
  std::vector<Sprite const*> all_sprites { };
  for (Projectile* p : active_projectiles_)
  {
    all_sprites.push_back(p);
  }
  all_sprites.push_back( &player_ );
  return all_sprites;
}

std::string PlayState::get_background() const
{
  return background_;
}

void PlayState::generate_terrain()
{
  terrain_.push_back ( { -20, 0, 20, 800 } );
  terrain_.push_back ( { 0, 301, 135, 163 } );
  terrain_.push_back ( { 136, 449, 527, 20 } );
  terrain_.push_back ( { 300, 227, 153, 14 } );
  terrain_.push_back ( { 535, 272, 53, 14 } );
  terrain_.push_back ( { 662, 353, 93, 247 } );
  terrain_.push_back ( { 875, 589, 337, 11 } );
  terrain_.push_back ( { 1211, 546, 73, 54 } );
  terrain_.push_back ( { 1284, 589, 865, 11 } );
  terrain_.push_back ( { 2148, 558, 46, 42 } );
  terrain_.push_back ( { 2193, 502, 207, 98 } );
  terrain_.push_back ( { 875, 351, 129, 155 } );
  terrain_.push_back ( { 876, 507, 223, 14 } );
  terrain_.push_back ( { 989, 309, 68, 80 } );
  terrain_.push_back ( { 990, 349, 806, 77 } );
  terrain_.push_back ( { 1796, 298, 89, 99 } );
  terrain_.push_back ( { 1747, 397, 332, 45 } );
  terrain_.push_back ( { 1747, 446, 372, 14 } );
  terrain_.push_back ( { 1147, 222, 479, 15 } );
  terrain_.push_back ( { 1683, 69, 232, 14 } );
  terrain_.push_back ( { 1996, 216, 93, 15 } );
  terrain_.push_back ( { 2200, 159, 200, 14 } );
  //terrain_.push_back ( { 989, 309, 14, 197 } );
  terrain_.push_back ( { 2400, 0, 20, 800 } );
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
      case GameInput::kSpace: {
        Projectile* projectile = player_.fire ();
        if (projectile != nullptr)
        {
          active_projectiles_.push_back ( projectile );
        }
      }
        break;
      default:
        break;
    }
  }

  return commands;
}

void PlayState::do_projectile_updates()
{
  for (Projectile* k : active_projectiles_)
  {
    k->update();
  }
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
  else if (moving_from.get_x ()
      >= collision_target.get_x () + collision_target.get_width ()) // Moving object was to the right
  {
    sprite.set_x ( collision_target.get_x () + collision_target.get_width () );
  }
  else if (moving_bottom <= collision_target.get_y ()) // Moving object was enteirly above
  {
    sprite.set_y ( collision_target.get_y () - sprite.get_height () );
    sprite.reset_y_velocity ();
  }
  else if (moving_from.get_y ()
      >= collision_target.get_y () + collision_target.get_height ())
  {
    sprite.set_y ( collision_target.get_y () + collision_target.get_height () );
    sprite.reset_y_velocity ();
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
