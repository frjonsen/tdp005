/*
 * graphics_engine.h
 *
 *  Created on: Dec 7, 2014
 *      Author: vakz
 */

#ifndef GRAPHICS_ENGINE_H_
#define GRAPHICS_ENGINE_H_

#include <string>
#include "sprite.h"
#include "rectangle.h"
#include <vector>
#include "window.h"
#include "renderer.h"

using visible_sprite_rect = std::tuple<Sprite const&, Rectangle>;

class GraphicsEngine
{

  Window window_;
  Renderer renderer_;

  bool calc_visible_area(Sprite const& sprite, const int viewport_x,
                         const int viewport_y, Rectangle& out) const;
  void get_visible_sprites(std::vector<Sprite> const& sprites,
                           std::vector<visible_sprite_rect>& visible,
                           const int viewport_x, const int viewport_y) const;

public:
  GraphicsEngine(std::string window_title, const int window_height,
                 const int window_width);
  void redraw_screen(std::vector<Sprite> const& sprites, const int viewport_x,
                     const int viewport_y);
};

#endif /* GRAPHICS_ENGINE_H_ */
