/*
 * graphics_engine.cc
 *
 *  Created on: Dec 7, 2014
 *      Author: vakz
 */

#include "graphics_engine.h"
#include "window.h"
#include <stdexcept>
#include <iostream>

GraphicsEngine::GraphicsEngine(const std::string window_title,
                               const int window_width, const int window_height,
                               const int world_width, const int world_height)
    : kWorldWidth { world_width }, kWorldHeight { world_height }, window_ {
        window_title, window_width, window_height }, renderer_ { window_ }, texture_handler_ {
        renderer_, "images/" }
{

  renderer_.set_logical_size (window_.kWidth, window_.kHeight);
  renderer_.set_render_draw_color (0, 0, 0);
  renderer_.clear ();
}

GraphicsEngine::~GraphicsEngine()
{
}

void GraphicsEngine::redraw_screen(std::list<Sprite const*> const& sprites)
{
  std::list<Sprite const*> visible_sprites;
  get_visible_sprites (sprites, visible_sprites);
  draw_screen (sprites);
}

void GraphicsEngine::draw_screen(std::list<Sprite const*> const& sprites)
{
  renderer_.clear ();
  draw_background ();
  for (Sprite const* s : sprites)
  {
    Rectangle corrected_for_viewport { s->get_x () - viewport_.x, s->get_y ()
        - viewport_.y, s->get_width (), s->get_height () };

    Texture* texture { texture_handler_.get_texture (s->get_texture().texture_name) };
    //renderer_.render_copy (texture, s->get_enclosing_rect (),
    //                       corrected_for_viewport);
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (s->get_texture().flip) flip = SDL_FLIP_HORIZONTAL;
    renderer_.render_copy_ex (texture, s->get_enclosing_rect(), corrected_for_viewport, 0, NULL, flip);
  }
  renderer_.render_present ();
}

void GraphicsEngine::draw_background()
{
  Rectangle window { 0, 0, window_.kWidth, window_.kHeight };
  Rectangle viewport { viewport_.x, viewport_.y, window_.kWidth, window_.kHeight };
  Texture* background { texture_handler_.get_texture (background_) };
  renderer_.render_copy (background, viewport, window);
}

void GraphicsEngine::get_visible_sprites(
    std::list<Sprite const*> const& sprites,
    std::list<Sprite const*>& visible) const
{

  Rectangle window { viewport_.x, viewport_.y, window_.kWidth, window_.kHeight };
  for (Sprite const* s : sprites)
  {

    if (s->intersect (window))
    {
      visible.push_back (s);
    }
  }
}

void GraphicsEngine::set_viewport(Viewport viewport)
{
  if (viewport.x < 0) viewport.x = 0;
  if (viewport.y < 0) viewport.y = 0;
  if (viewport.x + window_.kWidth > kWorldWidth) viewport.x = kWorldWidth
      - window_.kWidth;
  if (viewport.y + window_.kHeight > kWorldHeight) viewport.y = kWorldHeight
      - window_.kHeight;
  viewport_ = viewport;
}

void GraphicsEngine::set_background(std::string texture)
{
  background_ = texture;
}
