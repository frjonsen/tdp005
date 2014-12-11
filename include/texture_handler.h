/*
 * texture_handler.h
 *
 *  Created on: Dec 10, 2014
 *      Author: frejo105
 */

#ifndef TEXTURE_HANDLER_H_
#define TEXTURE_HANDLER_H_

#include <string>
#include <map>
#include "texture.h"
#include "renderer.h"

class TextureHandler
{
  const std::string resource_path_;
  Renderer& renderer_;
  std::map<std::string, Texture*> loaded_textures_{};

  void load_texture(std::string texture_name);

public:
  TextureHandler(Renderer& renderer, std::string resource_path);
  ~TextureHandler();

  TextureHandler(TextureHandler const&) = delete;
  TextureHandler(TextureHandler&&) = delete;

  TextureHandler& operator=(TextureHandler const&) = delete;
  TextureHandler& operator=(TextureHandler&&) = delete;

  Texture* get_texture(std::string texture_name);
};

#endif /* INCLUDE_TEXTURE_HANDLER_H_ */
