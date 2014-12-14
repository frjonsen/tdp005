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
#include <list>
#include "window.h"
#include "renderer.h"
#include <tuple>
#include <texture_handler.h>

/**
 * Graphics engine, handling all SDL-related functions,
 * such as creation of a window and a renderer, as well
 * as all use of them, such as drawing sprites in the window.
 */
class GraphicsEngine
{
public:
  /**
   * Struct to hold a simple viewport, consisting
   * of x and y coordinates to the upper left corner.
   */
  struct Viewport
  {
    Viewport();
    /**
     * Initialize viewport using a pair
     * @param coords Coordinates as (x, y)
     */
    Viewport(std::pair<int, int> coords)
        : x { std::get<0> (coords) }, y { std::get<1> (coords) }
    {
    }
    /// X coordinate
    int x;
    /// Y coordinate
    int y;
  }
  ;
private:

  /// Actual world width
  const int kWorldWidth;

  /// Actual world height
  const int kWorldHeight;

  /// The window
  Window window_;

  /// The renderer used to draw in the window
  Renderer renderer_;

  /// The current viewport
  Viewport viewport_ { std::make_pair(0, 0) };

  /// The texture handler, used to load and cache textures
  TextureHandler texture_handler_;

  /// The current background used by the engine
  std::string background_ { "" };

  /**
   * Attempt to calculate which sprites are actually in the visible area
   * @param sprites All active sprites
   * @param visible Output parameter to contain all visible sprites
   */
  void get_visible_sprites(std::list<Sprite const*> const& sprites,
                           std::list<Sprite const*>& visible) const;
  /**
   * Redraw screen. Clears everything previously drawn, and redraws the background
   * and all visible sprites
   * @param sprites All active sprites
   */
  void draw_screen(std::list<Sprite const*> const& sprites);

  /**
   * Draw the background, taking viewport into account
   */
  void draw_background();

public:
  /**
   * Initialize graphics engine
   * @param window_title Window title
   * @param window_width Width of the window
   * @param window_height Height of the window
   * @param world_width Width of the actual game world
   * @param world_height Height of the actual game world
   */
  GraphicsEngine(std::string window_title, const int window_width,
                 const int window_height, const int world_width,
                 const int world_height);
  ~GraphicsEngine();

  /// Deleted copy constructor
  GraphicsEngine(GraphicsEngine const&) = delete;
  /// Deleted move constructor
  GraphicsEngine(GraphicsEngine&&) = delete;

  /// Deleted assignment operator
  GraphicsEngine& operator=(GraphicsEngine const&) = delete;
  /// Deleted move-assignment operator
  GraphicsEngine& operator=(GraphicsEngine&&) = delete;

  /**
   * Set the viewport
   * @param viewport Viewport as instance of class Viewport
   */
  void set_viewport(Viewport viewport);

  /**
   * Set the current background to be used in the window
   * @param texture Filename of background
   */
  void set_background(std::string texture);

  /**
   * Update the window. Clears everything previously drawn,
   * and redraws all sprites and the set background.
   * @param sprites A list of all sprites to be drawn.
   */
  void redraw_screen(std::list<Sprite const*> const& sprites);
};

#endif /* GRAPHICS_ENGINE_H_ */
