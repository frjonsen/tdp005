/*
 * graphics_engine.cc
 *
 *  Created on: Dec 7, 2014
 *      Author: vakz
 */

#include "graphics_engine.h"
#include "window.h"
#include <tuple>

GraphicsEngine::GraphicsEngine(const std::string window_title,
                               const int window_width, const int window_height)
    : window_ { window_title, window_width, window_height }, renderer_ { window_ }, viewport_{0,0}
{
  renderer_.set_logical_size (window_.kWidth, window_.kHeight);
  renderer_.set_render_draw_color (0, 0, 0);
  renderer_.clear ();
}

void GraphicsEngine::redraw_screen(std::vector<Sprite const*> const& sprites)
{
  std::vector<visible_sprite_rect> visible_sprites;
  get_visible_sprites (sprites, visible_sprites);
}

void GraphicsEngine::translate_coords_to_viewport(
    std::vector<visible_sprite_rect>& sprites) const
{
  //for (visible_sprite_rect)
}

void GraphicsEngine::get_visible_sprites(
    std::vector<Sprite const*> const& sprites,
    std::vector<visible_sprite_rect>& visible) const
{
  for (Sprite const* s : sprites)
  {
    visible_sprite_rect vsr { s, Rectangle (0, 0, 0, 0) };
    Rectangle& r = std::get < 1 > (vsr);
    if (calc_visible_area (s, r))
    {
      visible.push_back (vsr);
    }
  }
}

bool GraphicsEngine::calc_visible_area(Sprite const* sprite,
                                       Rectangle& out) const
{
  Rectangle window { viewport_.x, viewport_.y, window_.kWidth, window_.kHeight };
  return sprite->intersecting_area (window, out);
}

void GraphicsEngine::set_viewport(Viewport viewport)
{
  viewport_ = viewport;
}

Renderer& GraphicsEngine::get_renderer()
{
  return renderer_;
}
