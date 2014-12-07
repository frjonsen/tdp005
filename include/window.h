#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <SDL2/SDL.h>
#include <string>

class Window
{
public:
	Window(std::string title, int width, int height);
	~Window();
	Window(Window const&) = delete;

	Window& operator=(Window const&) = delete;

	SDL_Window* get_window() const;

  const int kWidth;
  const int kHeight;

private:
	SDL_Window* window_;
};

#endif
