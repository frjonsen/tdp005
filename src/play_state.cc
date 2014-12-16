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
  generate_terrain ();
  generate_enemies ();
}

PlayState::~PlayState()
{
  for (Projectile* p : active_projectiles_)
  {
    delete p;
  }
  for (Enemy* e : enemies_)
  {
    delete e;
  }
}

AbstractGameState::StateCommand PlayState::update(
    std::list<GameInput> const& input)
{
  do_enemy_update ();
  std::list<Player::MovementCommand> commands { translate_input (input) };

  do_player_update (commands);
  do_projectile_updates ();
  --time_;
  if (time_ <= 0) return StateCommand::kOutOfTime;
  if (((player_.get_x ()) > 2280) && ((player_.get_y ()) < 110))
  {
    return StateCommand::kWin;
  }
  if ((player_.get_y ()) > 600)
  {
    return StateCommand::kFell;
  }
  if (player_.get_hp () <= 0)
  {
    return StateCommand::kKilled;
  }

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
  for (Enemy* e : enemies_)
  {
    all_sprites.push_back (e);
  }
  all_sprites.push_back (&player_);
  return all_sprites;
}

std::list<TextTexture> PlayState::get_texts() const
{
  return std::list<TextTexture> {
      { std::to_string (player_.get_hp ()), 100, 100 }, { std::to_string (
          time_ / 60), 500, 100 } };
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

void PlayState::generate_enemies()
{
  enemies_.push_back (new WalkerEnemy (400, 100));
  Enemy* e { new WalkerEnemy (350, 300) };
  e->reverse_direction ();
  enemies_.push_back (e);
  enemies_.push_back (new SpitterEnemy (1300, 225));
  enemies_.push_back (new RunnerEnemy (1350, 450));
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
      delete_projectile (it);
    }
  }

  // Do enemy collision
  for (std::list<Projectile*>::iterator p_it { active_projectiles_.begin () };
      p_it != active_projectiles_.end (); ++p_it)
  {
    if ((*p_it)->owner_ == Projectile::ProjectileOwner::kPlayer)
    {
      for (std::list<Enemy*>::iterator e_it { enemies_.begin () };
          e_it != enemies_.end (); ++e_it)
      {
        if ((*p_it)->intersect (**e_it))
        {
          (*e_it)->take_damage ((*p_it)->kDamage);
          if ((*e_it)->get_hp () < 0)
          {
            delete *e_it;
            enemies_.erase (e_it);

          }
          delete_projectile (p_it);
          break;
        }
      }
    }
    else if ((*p_it)->owner_ == Projectile::ProjectileOwner::kEnemy
        && (*p_it)->intersect (player_))
    {
      player_.take_damage ((*p_it)->kDamage);
      delete_projectile (p_it);
      break;
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

// Do terrain collision
  std::list<Rectangle *> collisions { check_terrain_collision (player_) };
  if (collisions.size () != 0)
  {
    for (Rectangle * r : collisions)
    {
      handle_collision (player_, before, *r);
    }
  }
}

void PlayState::do_enemy_update()
{

  for (std::list<Enemy*>::iterator it { enemies_.begin () };
      it != enemies_.end (); ++it)
  {
    Rectangle before { **it };
    (*it)->update ();
    if ((*it)->kIsRanged)
    {
      Projectile* p { (*it)->fire (player_) };
      if (p != nullptr)
      {
        active_projectiles_.push_back (p);
      }
    }
    (*it)->handle_gravity (kGravity);

    // Do player collision
    if ((*it)->intersect (player_))
    {
      Direction direction { handle_collision (**it, before, player_) };
      if ((*it)->kType == Enemy::EnemyType::kWalker
          && direction == Direction::kBelow) // Player hit enemy from above
      {
        std::list<Enemy*>::iterator temp { it };
        --it;
        delete *temp;
        enemies_.erase (temp);
        player_.jump ();
      }
      else
      {
        int x_velocity { direction == Direction::kLeft ? 10 : -10 };
        player_.take_damage (10);
        player_.set_stunned (30, x_velocity);
      }
    }
    if ((*it)->kType == Enemy::EnemyType::kSpitter) continue;
    // Do terrain collision
    std::list<Rectangle *> collisions { check_terrain_collision (**it) };
    if (collisions.size () != 0)
    {
      for (Rectangle * r : collisions)
      {
        Direction d { handle_collision (**it, before, *r) };
        if (d == Direction::kLeft || d == Direction::kRight) (*it)->reverse_direction ();
      }
    }

  }
}

PlayState::Direction PlayState::handle_collision(
    Sprite& sprite, Rectangle const& moving_from,
    Rectangle const& collision_target)
{
  Direction direction { get_collision_direction (sprite, moving_from,
                                                 collision_target) };
  switch (direction)
  {
    case Direction::kLeft: // Moving object was enteirly to the left
      sprite.set_x (collision_target.get_x () - sprite.get_width ());
      break;
    case Direction::kRight: // Moving object was to the right
      sprite.set_x (collision_target.get_x () + collision_target.get_width ());
      break;
    case Direction::kAbove:

      sprite.set_y (collision_target.get_y () - sprite.get_height ());
      sprite.reset_y_velocity ();
      break;
    case Direction::kBelow:
      sprite.set_y (collision_target.get_y () + collision_target.get_height ());
      sprite.reset_y_velocity ();
      break;
  }
  return direction;
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

PlayState::Direction PlayState::get_collision_direction(
    Rectangle const& moving_rect, Rectangle const& moving_from,
    Rectangle const& collision_target)
{
  int moving_bottom { moving_from.get_y () + moving_from.get_height () };
  int moving_right { moving_from.get_x () + moving_from.get_width () };
  if (moving_right <= collision_target.get_x ()) // Moving object was enteirly to the left
  {
    return Direction::kLeft;
  }
  else if (moving_from.get_x ()
      >= collision_target.get_x () + collision_target.get_width ()) // Moving object was to the right
  {
    return Direction::kRight;
  }
  else if (moving_bottom <= collision_target.get_y ()) // Moving object was enteirly above
  {
    return Direction::kAbove;
  }
  else if (moving_from.get_y () // Moving object was enteirly below
  >= collision_target.get_y () + collision_target.get_height ())
  {
    return Direction::kBelow;
  }

// If unable to decide direction, make a qualified guess
  if (moving_from.get_x () < collision_target.get_x ())
  {
    return Direction::kLeft;
  }
  return Direction::kRight;
}
