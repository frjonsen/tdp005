#include <SDL2/SDL.h>
#include "window.h"
#include <stdexcept>

Window::Window(std::string title, int width, int height)
    : kWidth { width }, kHeight { height }, window_ { SDL_CreateWindow (
        title.c_str (), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width,
        height, 0) }
{

}

Window::~Window()
{
  SDL_DestroyWindow (window_);
  SDL_Quit ();
}

SDL_Window* Window::get_window() const
{
  return window_;
}
