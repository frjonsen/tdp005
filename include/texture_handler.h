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

/**
 * Used to handle loading and caching textures from harddrive
 */
class TextureHandler
{
  /// Path to directory where textures are stored
  const std::string resource_path_;

  /// Renderer used to initialize textures
  Renderer& renderer_;

  /// Cached textures
  std::map<std::string, Texture*> loaded_textures_{};

  /// Load texture from storage
  void load_texture(std::string texture_name);

public:
  /**
   * Initialize texture handler
   * @param renderer Renderer used to initialize textures
   * @param resource_path Path to texture directory
   */
  TextureHandler(Renderer& renderer, std::string resource_path);
  ~TextureHandler();

  /// Deleted copy constructor
  TextureHandler(TextureHandler const&) = delete;

  /// Deleted move constructor
  TextureHandler(TextureHandler&&) = delete;

  /// Deleted assignment operator
  TextureHandler& operator=(TextureHandler const&) = delete;

  /// Deleted move-assignment operator
  TextureHandler& operator=(TextureHandler&&) = delete;

  /**
   * Get a texture. If texture is requested for the first time, it will be read
   * from storage and cached in an internal container.
   * @param texture_name Filename of the texture
   * @return A pointer to the request Texture
   */
  Texture* get_texture(std::string texture_name);
};

#endif /* INCLUDE_TEXTURE_HANDLER_H_ */
