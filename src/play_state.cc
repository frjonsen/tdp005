/*
 * game_state.cc
 *
 *  Created on: Dec 8, 2014
 *      Author: frejo105
 */

#include "play_state.h"
#include <iostream>

/*
PlayState::PlayState(const int gravity)
    : kGravity { gravity }, player_ { "Hero_Standing_R.png",
        { 50, 200, 27, 53 }, { 1, 0 } }, terrain_ { }
*/
PlayState::PlayState()
{
  generate_terrain();
}

PlayState::~PlayState()
{
  for (Projectile* p : active_projectiles_)
  {
    delete p;
  }
}

AbstractGameState::StateCommand PlayState::update(
    std::list<GameInput> const& input)
{
  std::list<Player::MovementCommand> commands { translate_input (input) };

  do_player_update (commands);
  do_projectile_updates ();
  --time_;
  if (time_ == 0) return StateCommand::kOutOfTime;
  return StateCommand::kNone;
}

std::pair<int, int> PlayState::get_viewport() const
{
  return std::make_pair (player_.get_x () - 400, 0);
}

std::list<Sprite const*> PlayState::get_sprites() const
{
  std::list<Sprite const*> all_sprites {};
  for (Projectile* p : active_projectiles_)
  {
    all_sprites.push_back (p);
  }
  all_sprites.push_back (&player_);
  return all_sprites;
}

std::list<TextTexture> PlayState::get_texts() const
{
  return std::list<TextTexture> { };
}

std::string PlayState::get_background() const
{
  return background_;
}

void PlayState::generate_terrain()
{
  terrain_.push_back ( { -50, 0, 50, 800 });
  terrain_.push_back ( { 0, 301, 135, 163 });
  terrain_.push_back ( { 136, 449, 527, 20 });
  terrain_.push_back ( { 300, 227, 153, 14 });
  terrain_.push_back ( { 535, 272, 53, 14 });
  terrain_.push_back ( { 662, 353, 93, 247 });
  terrain_.push_back ( { 875, 589, 337, 11 });
  terrain_.push_back ( { 1211, 546, 73, 54 });
  terrain_.push_back ( { 1284, 589, 865, 11 });
  terrain_.push_back ( { 2148, 558, 46, 42 });
  terrain_.push_back ( { 2193, 502, 207, 98 });
  terrain_.push_back ( { 875, 351, 129, 155 });
  terrain_.push_back ( { 876, 507, 223, 14 });
  terrain_.push_back ( { 989, 309, 68, 80 });
  terrain_.push_back ( { 990, 349, 806, 77 });
  terrain_.push_back ( { 1796, 298, 89, 99 });
  terrain_.push_back ( { 1747, 397, 332, 45 });
  terrain_.push_back ( { 1747, 446, 372, 14 });
  terrain_.push_back ( { 1147, 222, 479, 15 });
  terrain_.push_back ( { 1683, 69, 232, 14 });
  terrain_.push_back ( { 1996, 216, 93, 15 });
  terrain_.push_back ( { 2200, 159, 200, 14 });
  terrain_.push_back ( { 2400, 0, 50, 800 });
}

std::list<Player::MovementCommand> PlayState::translate_input(
    std::list<GameInput> const& input)
{
  using MovementCommand = Player::MovementCommand;

  std::list<Player::MovementCommand> commands;

  for (GameInput i : input)
  {
    switch (i)
    {
      case GameInput::kUp:
        commands.push_back (MovementCommand::kJump);
        break;
      case GameInput::kLeft:
        commands.push_back (MovementCommand::kMoveLeft);
        break;
      case GameInput::kRight:
        commands.push_back (MovementCommand::kMoveRight);
        break;
      case GameInput::kSpace:
      {
        Projectile* projectile = player_.fire ();
        if (projectile != nullptr)
        {
          active_projectiles_.push_back (projectile);
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
  using p_list = std::list<Projectile*>;
  for (p_list::iterator it { active_projectiles_.begin () };
      it != active_projectiles_.end (); ++it)
  {
    (*it)->update ();

    std::list<Rectangle*> terrain_collisions { check_terrain_collision (**it) };

    if (terrain_collisions.size () > 0)
    {
      delete_projectile(it);
    }

  }
}

void PlayState::delete_projectile(std::list<Projectile*>::iterator& it)
{
  // Assign it to temp to avoid risk of invalidated iterator
  std::list<Projectile*>::iterator temp { it };
  --it;
  delete *temp;
  active_projectiles_.erase (temp);
}

void PlayState::do_player_update(std::list<Player::MovementCommand> commands)
{
  Rectangle before { player_ };
  player_.order_player (commands);
  player_.handle_gravity (kGravity);
  std::list<Rectangle *> collisions { check_terrain_collision (player_) };
  if (collisions.size () != 0)
  {
    for (Rectangle * r : collisions)
    {
      handle_collision (player_, before, *r);
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
    sprite.set_x (collision_target.get_x () - sprite.get_width ());
  }
  else if (moving_from.get_x ()
      >= collision_target.get_x () + collision_target.get_width ()) // Moving object was to the right
  {
    sprite.set_x (collision_target.get_x () + collision_target.get_width ());
  }
  else if (moving_bottom <= collision_target.get_y ()) // Moving object was enteirly above
  {
    sprite.set_y (collision_target.get_y () - sprite.get_height ());
    sprite.reset_y_velocity ();
  }
  else if (moving_from.get_y () // Moving object was enteirly below
  >= collision_target.get_y () + collision_target.get_height ())
  {
    sprite.set_y (collision_target.get_y () + collision_target.get_height ());
    sprite.reset_y_velocity ();
  }
}

std::list<Rectangle*> PlayState::check_terrain_collision(Rectangle const& r)
{
  std::list<Rectangle *> collisions;
  for (Rectangle& t : terrain_)
  {
    if (r.intersect (t))
    {
      collisions.push_back (&t);
    }
  }
  return collisions;
}
