#ifndef _RENDERER_H_
#define _RENDERER_H_


class Texture;
class Rectangle;
class Window;

class Renderer
{
public:
	Renderer(Window& window);
	~Renderer();
	Renderer(Renderer const&) = delete;

	Renderer& operator=(Renderer const&) = delete;

	SDL_Renderer* get_renderer();

	void set_render_draw_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
	void render_copy(Texture texture, Rectangle const& srcrect,
			Rectangle const& dstrect);
	void render_copy_ex(Texture const& texture, Rectangle const& srcrect, Rectangle const& dstrect,
			double angle, SDL_Point* center, SDL_RendererFlip flip);
	void render_present();
	void clear();

private:
	SDL_Renderer* renderer_;
};

#endif
