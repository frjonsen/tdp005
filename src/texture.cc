/*
 * texture.cc
 *
 *  Created on: Nov 24, 2014
 *      Author: frejo105
 */

#include "texture.h"
#include "renderer.h"
#include "surface.h"

Texture::Texture(Renderer& renderer, SDL_Surface* surface, int width,
                 int height)
    : kWidth { width }, kHeight { height }, texture_ {
        SDL_CreateTextureFromSurface (renderer.get_renderer (), surface) }
{
}

Texture::Texture(Renderer& renderer, Surface& surface, int width, int height)
: kWidth { width }, kHeight { height }, texture_ {
        SDL_CreateTextureFromSurface (renderer.get_renderer (), surface.get_surface()) } {}

Texture::~Texture()
{
  SDL_DestroyTexture (texture_);
}

SDL_Texture* Texture::get_texture() const
{
  return texture_;
}
