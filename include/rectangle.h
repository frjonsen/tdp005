/*
 * rectangle.h
 *
 *  Created on: Nov 24, 2014
 *      Author: frejo105
 */

#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include <SDL2/SDL.h>

class Rectangle
{
public:
  Rectangle(const int x, const int y, const int width, const int height);
  ~Rectangle();

  Rectangle(Rectangle const&);
  Rectangle(Rectangle&&);

  Rectangle& operator=(Rectangle const&);
  Rectangle& operator=(Rectangle);

  const SDL_Rect* get_rect() const;

  int get_y() const;
  int get_x() const;
  int get_width() const;
  int get_height() const;

  void set_y(const int y);
  void set_x(const int x);
  void set_width(const int width);
  void set_height(const int height);

  bool contain(const int x, const int y) const;
  bool intersect(Rectangle const& other) const;

private:
  SDL_Rect* rect_;
};

#endif /* RECTANGLE_H_ */
