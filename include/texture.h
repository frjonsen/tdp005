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

class Texture
{
public:
	Texture(Renderer& renderer, SDL_Surface* surface);
	Texture(Renderer& renderer, Surface& surface);
	Texture(Texture const&) = delete;
	~Texture();

	Texture& operator=(Texture const&) = delete;

	SDL_Texture* get_texture() const;
private:
	SDL_Texture* texture_;
};



#endif /* TEXTURE_H_ */
