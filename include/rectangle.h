/*
 * rectangle.h
 *
 *  Created on: Nov 24, 2014
 *      Author: frejo105
 */

#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include <SDL2/SDL.h>

/**
 * Representation of a rectangle
 */
class Rectangle
{
public:
  /**
   * Initialize rectangle
   * @param x X coordinate
   * @param y Y coordinate
   * @param width Width
   * @param height Height
   */
  Rectangle(const int x, const int y, const int width, const int height);
  virtual ~Rectangle();

  /**
   * Copy existing rectangle
   * @param other Rectangle to copy
   */
  Rectangle(Rectangle const& other);

  /**
   * Move data from temporary rectangle
   * @param other Rectangle to move data from
   */
  Rectangle(Rectangle&& other);

  /**
   * Assign same data to this as is in rhs
   * @param rhs Rectangle to copy data from
   * @return this
   */
  Rectangle& operator=(Rectangle const& rhs);
  /**
   * Assign same data, using move-semantics rather than copying
   * @param rhs Rectangle to move data from
   * @return this
   */
  Rectangle& operator=(Rectangle&& rhs);

  /**
   * Get the internal SDL rectangle representation
   * @return Internal SDL_Rect pointer
   */
  const SDL_Rect* get_rect() const;

  /// Get Y coordinate
  int get_y() const;

  /// Get X coordinate
  int get_x() const;

  /// Get width
  int get_width() const;

  /// Get height
  int get_height() const;

  /// Set Y coordinate
  void set_y(const int y);

  /// Set X coordinate
  void set_x(const int x);

  /// Set Width. Must be greater than zero.
  void set_width(const int width);

  /// Set height. Must be greater then zero.
  void set_height(const int height);

  /**
   * Get a minimum rectangle enclosing this.
   * Has the same width and height, but with both coordinates set to zero.
   * @return Enclosing rectangle
   */
  Rectangle get_enclosing_rect() const;

  /**
   * Check if this contains point (x, y)
   * @param x X coordinate
   * @param y Y coordinate
   * @return True if this contains point, else false
   */
  bool contain(const int x, const int y) const;

  /**
   * Check if this is intersecting with other
   * @param other Rectangle to check intersection with
   * @return True if intersecting, else false
   */
  bool intersect(Rectangle const& other) const;

  /**
   * Get the overlapping area of this and other.
   * @param other Rectangle to match overlapping area with
   * @param overlapping Rectangle to store overlapping area in
   * @return True if rectangles have an overlapping area, else false
   */
  bool intersecting_area(Rectangle const& other, Rectangle& overlapping) const;

private:
  /// Underlying SDL_Rect to store coordinates and dimensions in
  SDL_Rect* rect_;
};

#endif /* RECTANGLE_H_ */
