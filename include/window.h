#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <SDL2/SDL.h>
#include <string>

/**
 * Wrapper class for SDL_Window
 */
class Window
{
public:
  /**
   * Initialize window
   * @param title Window title
   * @param width Window width
   * @param height Window height
   */
	Window(std::string title, int width, int height);
	~Window();

	/// Deleted copy constructor
	Window(Window const&) = delete;

	/// Deleted assignment operator
	Window& operator=(Window const&) = delete;

	/// Get the internal SDL_Window
	SDL_Window* get_window() const;

	/// Window width
  const int kWidth;

  /// Window height
  const int kHeight;

private:
  /// Internal SDL_Window
	SDL_Window* window_;
};

#endif
