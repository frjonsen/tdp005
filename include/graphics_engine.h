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

using visible_sprite_rect = std::tuple<Sprite const*, Rectangle>;

class GraphicsEngine
{
public:
  struct Viewport
      {
        int x;
        int y;
      };
private:

  Window window_;
  Renderer renderer_;
  Viewport viewport_;

  bool calc_visible_area(Sprite const* sprite, Rectangle& out) const;
  void get_visible_sprites(std::vector<Sprite const*> const& sprites,
                           std::vector<visible_sprite_rect>& visible) const;
  void translate_coords_to_viewport(
      std::vector<visible_sprite_rect>& sprites) const;

public:
  GraphicsEngine(std::string window_title, const int window_width,
                 const int window_height);
  void redraw_screen(std::vector<Sprite const*> const& sprites);
  void set_viewport(Viewport viewport);
  Renderer& get_renderer();
};

#endif /* GRAPHICS_ENGINE_H_ */
