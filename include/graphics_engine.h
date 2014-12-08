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
#include <tuple>

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
  Texture* background_;

  bool calc_visible_area(Sprite const* sprite, Rectangle& out) const;
  void get_visible_sprites(std::vector<Sprite const*> const& sprites,
                           std::vector<Sprite const*>& visible) const;
  void draw_screen(std::vector<Sprite const*> const& sprites);
  void draw_background();

public:
  GraphicsEngine(std::string window_title, const int window_width,
                 const int window_height);
  ~GraphicsEngine();

  GraphicsEngine(GraphicsEngine const&) = delete;
  GraphicsEngine(GraphicsEngine&&) = delete;

  GraphicsEngine& operator=(GraphicsEngine const&) = delete;
  GraphicsEngine& operator=(GraphicsEngine&&) = delete;

  Renderer& get_renderer();

  void set_viewport(Viewport viewport);
  void set_background(Texture* texture);

  void redraw_screen(std::vector<Sprite const*> const& sprites);
};

#endif /* GRAPHICS_ENGINE_H_ */
