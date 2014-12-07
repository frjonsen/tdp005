/*
 * rectangle.cc
 *
 *  Created on: Nov 24, 2014
 *      Author: frejo105
 */

#include "rectangle.h"
#include <iostream>

Rectangle::Rectangle(const int x, const int y, const int width,
                     const int height)
    : rect_ { new SDL_Rect () }
{
  rect_->x = x;
  rect_->y = y;
  rect_->w = width;
  rect_->h = height;
}

Rectangle::Rectangle(Rectangle const& other)
    : rect_ { new SDL_Rect () }
{
  rect_->x = other.get_x ();
  rect_->y = other.get_y ();
  rect_->w = other.get_width ();
  rect_->h = other.get_height ();
}

Rectangle::Rectangle(Rectangle&& other)
    : rect_ { other.rect_ }
{
  other.rect_ = nullptr;
}

Rectangle& Rectangle::operator=(Rectangle const& rhs)
{
  if (this != &rhs)
  {
    Rectangle copy (rhs);
    rect_ = copy.rect_;
    copy.rect_ = nullptr;
  }

  return *this;
}

Rectangle& Rectangle::operator=(Rectangle rhs)
{
  rect_ = rhs.rect_;
  rhs.rect_ = nullptr;

  return *this;
}

Rectangle::~Rectangle()
{
  std::cout << "called" << std::endl;
  delete rect_;
}

const SDL_Rect* Rectangle::get_rect() const
{
  return rect_;
}

int Rectangle::get_x() const
{
  return rect_->x;
}

int Rectangle::get_y() const
{
  return rect_->y;
}

int Rectangle::get_width() const
{
  return rect_->w;
}

int Rectangle::get_height() const
{
  return rect_->h;
}

void Rectangle::set_y(const int y)
{
  if (y >= 0)
  {
    rect_->y = y;
  }
  else
  {
    throw "Y coordinate must be positive";
  }
}

void Rectangle::set_x(const int x)
{
  if (x >= 0)
  {
    rect_->x = x;
  }
  else
  {
    throw "X coordinate must be positive";
  }
}

void Rectangle::set_width(const int width)
{
  if (width >= 0)
  {
    rect_->w = width;
  }
  else
  {
    throw "Width must be greater or equal to zero";
  }
}

void Rectangle::set_height(const int height)
{
  if (height >= 0)
  {
    rect_->h = height;
  }
  else
  {
    throw "Height must be greater or equal to zero";
  }
}

bool Rectangle::contain(const int x, const int y) const
{
  bool check_x { x > rect_->x && x < (rect_->x + rect_->w) };
  return check_x && (y > rect_->y && y < (rect_->y + rect_->h));
}

bool Rectangle::intersect(Rectangle const& other) const
{
  SDL_bool overlaps { SDL_HasIntersection (rect_, other.rect_) };
  return (overlaps == SDL_TRUE);
}

bool Rectangle::intersecting_area(Rectangle const& other, Rectangle& overlapping) const
{
  SDL_Rect intersecting;

  if (SDL_IntersectRect (rect_, other.get_rect (), &intersecting)){
    overlapping.set_x(intersecting.x);
    overlapping.set_y(intersecting.y);
    overlapping.set_width(intersecting.w);
    overlapping.set_height(intersecting.h);

    return true;
  }
  return false;
}
