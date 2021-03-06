#include <SDL2/SDL.h>
#include "window.h"
#include "texture.h"
#include "rectangle.h"
#include "renderer.h"

Renderer::Renderer(Window& window) :
		renderer_
		{ SDL_CreateRenderer(window.get_window(), -1, 0) }
{
}

Renderer::~Renderer()
{
	SDL_DestroyRenderer(renderer_);
}

SDL_Renderer* Renderer::get_renderer()
{
	return renderer_;
}

void Renderer::set_render_draw_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	SDL_SetRenderDrawColor(renderer_, r, g, b, a);
}

void Renderer::render_present()
{
	SDL_RenderPresent(renderer_);
}

void Renderer::clear()
{
	SDL_RenderClear(renderer_);
}

void Renderer::render_copy(Texture* texture, Rectangle const& srcrect,
		Rectangle const& dstrect)
{
	SDL_RenderCopy(renderer_, texture->get_texture(), srcrect.get_rect(),
			dstrect.get_rect());
}

void Renderer::render_copy_ex(Texture* texture, Rectangle const& srcrect,
		Rectangle const& dstrect, double angle, SDL_Point* center,
		SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(renderer_, texture->get_texture(), srcrect.get_rect(),
			dstrect.get_rect(), angle, center, flip);
}

void Renderer::set_logical_size(int width, int height)
{
	SDL_RenderSetLogicalSize(renderer_, width, height);
}

// Must be run BEFORE set_logical_size. Will otherwise be reset
// to cover whole window
void Renderer::set_viewport(Rectangle const& viewport)
{
  SDL_RenderSetViewport(renderer_, viewport.get_rect());
}
