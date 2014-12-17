/*
 * texture.h
 *
 *  Created on: Nov 24, 2014
 *      Author: frejo105
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <SDL2/SDL.h>

class Renderer;
class Surface;

/**
 * Wrapper class for SDL_Texture
 */
class Texture
{
public:
  /**
   * Initialize texture
   * @param renderer Renderer used to initialize the texture
   * @param surface Surface to copy texture data from
   * @param width Width of texture in pixels
   * @param height Height of texture in pixels
   */
  Texture(Renderer& renderer, SDL_Surface* surface, int width, int height);

  /**
   * Initialize texture
   * @param renderer Renderer used to initialize the texture
   * @param surface Surface to copy texture data from
   * @param width Width of texture in pixels
   * @param height Height of texture in pixels
   */
  Texture(Renderer& renderer, Surface& surface, int width, int height);

  /// Deleted copy constructor
  Texture(Texture const&) = delete;
  ~Texture();
  /// Deleted assignment operator
  Texture& operator=(Texture const&) = delete;

  /// Get the internal SDL_Texture
  SDL_Texture* get_texture() const;
  /// Width of texture in pixels
  const int kWidth;
  /// Height of texture in pixels
  const int kHeight;
private:
  /// Internal SDL_Texture
  SDL_Texture* texture_;

};

#endif /* TEXTURE_H_ */
