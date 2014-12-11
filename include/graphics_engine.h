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
#include <texture_handler.h>

class GraphicsEngine
{
public:
  struct Viewport
  {
    Viewport();
    Viewport(std::pair<int, int> coords)
        : x { std::get<0> (coords) }, y { std::get<1> (coords) }
    {
    }
    int x;
    int y;
  }
  ;
private:

  const int kWorldWidth;
  const int kWorldHeight;

  Window window_;
  Renderer renderer_;
  Viewport viewport_ { std::make_pair(0, 0) };
  TextureHandler texture_handler_;

  std::string background_ { "" };

  bool calc_visible_area(Sprite const* sprite, Rectangle& out) const;
  void get_visible_sprites(std::vector<Sprite const*> const& sprites,
                           std::vector<Sprite const*>& visible) const;
  void draw_screen(std::vector<Sprite const*> const& sprites);
  void draw_background();

public:
  GraphicsEngine(std::string window_title, const int window_width,
                 const int window_height, const int world_width,
                 const int world_height);
  ~GraphicsEngine();

  GraphicsEngine(GraphicsEngine const&) = delete;
  GraphicsEngine(GraphicsEngine&&) = delete;

  GraphicsEngine& operator=(GraphicsEngine const&) = delete;
  GraphicsEngine& operator=(GraphicsEngine&&) = delete;

  Renderer& get_renderer();

  void set_viewport(Viewport viewport);
  void set_background(std::string texture);

  void redraw_screen(std::vector<Sprite const*> const& sprites);
};

#endif /* GRAPHICS_ENGINE_H_ */
