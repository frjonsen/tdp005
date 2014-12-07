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
    : window_ { window_title, window_width, window_height }, renderer_ { window_ }
{
  renderer_.set_logical_size (window_.kWidth, window_.kHeight);
  renderer_.set_render_draw_color (0, 0, 0);
  renderer_.clear ();
}

void GraphicsEngine::redraw_screen(std::vector<Sprite> const& sprites,
                                   const int viewport_x, const int viewport_y)
{
  std::vector<visible_sprite_rect> visible_sprites;
  get_visible_sprites (sprites, visible_sprites, viewport_x, viewport_y);
}

void GraphicsEngine::get_visible_sprites(
    std::vector<Sprite> const& sprites,
    std::vector<visible_sprite_rect>& visible, const int viewport_x,
    const int viewport_y) const
{
  for (Sprite const& s : sprites)
  {
    visible_sprite_rect vsr { s, Rectangle (0, 0, 0, 0) };
    Rectangle& r = std::get < 1 > (vsr);
    if (calc_visible_area (s, viewport_x, viewport_y, r))
    {
      visible.push_back (vsr);
    }
  }
}

bool GraphicsEngine::calc_visible_area(Sprite const& sprite,
                                       const int viewport_x,
                                       const int viewport_y,
                                       Rectangle& out) const
{
  Rectangle window { viewport_x, viewport_y, window_.kWidth, window_.kHeight };
  return sprite.intersecting_area (window, out);
}
