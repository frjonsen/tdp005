/*
 * texture_handler.cc
 *
 *  Created on: Dec 10, 2014
 *      Author: frejo105
 */

#include "texture_handler.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdexcept>
#include "texture.h"
#include "surface.h"
#include <utility>
#include <map>

TextureHandler::TextureHandler(Renderer& renderer, std::string resource_path)
    : resource_path_ { resource_path }, renderer_ ( renderer )
{

}

TextureHandler::~TextureHandler()
{
  for (std::pair<std::string, Texture*> t : loaded_textures_)
  {
    delete t.second;
    t.second = nullptr;
  }
}

void TextureHandler::load_texture(std::string texture_name)
{
  std::string full_path { resource_path_ + texture_name };
  Surface s (IMG_Load (full_path.c_str ()));
  if (s.get_surface () == NULL)
  {
    std::string error = "File name '" + texture_name + "' does not exist";
    throw std::invalid_argument (error.c_str());
  }
  loaded_textures_[texture_name] = new Texture(renderer_, s, s.get_width(), s.get_height());
}

Texture* TextureHandler::get_texture(std::string texture_name)
{
  std::map<std::string, Texture*>::iterator requested_texture { loaded_textures_.find (texture_name) };
  if (requested_texture == loaded_textures_.end ())
  {
    load_texture (texture_name);
  }
  return loaded_textures_.at(texture_name);
}

