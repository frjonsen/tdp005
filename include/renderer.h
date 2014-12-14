#ifndef RENDERER_H_
#define RENDERER_H_


class Texture;
class Rectangle;
class Window;

/**
 * Wrapper class for SDL_Renderer
 */
class Renderer
{
public:
  /**
   * Initialize renderer
   * @param window Window to draw in
   */
	Renderer(Window& window);
	~Renderer();
	/// Deleted copy constructor
	Renderer(Renderer const&) = delete;

	/// Deleted assignment constructor
	Renderer& operator=(Renderer const&) = delete;

	/// Return the internal SDL_Renderer
	SDL_Renderer* get_renderer();

	/**
	 * Use this function to set the color used for drawing operations (Rect, Line and Clear).
	 * @param r the red value used to draw on the rendering target
	 * @param g the green value used to draw on the rendering target
	 * @param b the blue value used to draw on the rendering target
	 * @param a the alpha value used to draw on the rendering target
	 */
	void set_render_draw_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

	/**
	 * Use this function to copy a portion of the texture to the current rendering target.
	 * @param texture the source texture
	 * @param srcrect the source Rectangle structure
	 * @param dstrect the destination Rectangle structure
	 */
	void render_copy(Texture* texture, Rectangle const& srcrect,
			Rectangle const& dstrect);

	/**
	 * Use this function to copy a portion of the texture to the current rendering target,
	 * optionally rotating it by angle around the given center and also flipping it
	 * top-bottom and/or left-right
   * @param texture the source texture
   * @param srcrect the source Rectangle structure
   * @param dstrect the destination Rectangle structure
	 * @param angle an angle in degrees that indicates the rotation that will be applied to dstrect
	 * @param center a pointer to a point indicating the point around which dstrect will be rotated
	 * (if NULL, rotation will be done aroud dstrect.w/2, dstrect.h/2)
	 * @param flip an SDL_RendererFlip value stating which flipping actions should be performed on the texture
	 */
	void render_copy_ex(Texture* texture, Rectangle const& srcrect, Rectangle const& dstrect,
			double angle, SDL_Point* center, SDL_RendererFlip flip);

	/**
	 * Use this function to set a device independent resolution for rendering.
	 * @param width the width of the logical resolution
	 * @param height the height of the logical resolution
	 */
	void set_logical_size(int width, int height);

	/**
	 * Set the drawing area for rendering on the current target.
	 * @param viewport the Rectangle structure representing the drawing area
	 */
	void set_viewport(Rectangle const& viewport);

	/**
	 * Use this function to update the screen with any rendering performed since the previous call.
	 */
	void render_present();

	/**
	 * Use this function to clear the current rendering target with the drawing color.
	 */
	void clear();

private:
	/// The internal SDL_Renderer object
	SDL_Renderer* renderer_;
};

#endif
