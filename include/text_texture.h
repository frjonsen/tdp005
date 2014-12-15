/*
 * text_texture.h
 *
 *  Created on: Dec 15, 2014
 *      Author: vakz
 */

#ifndef TEXT_TEXTURE_H_
#define TEXT_TEXTURE_H_

#include <string>

struct TextTexture
{
  TextTexture(std::string text, int x, int y) : kText{text}, kX{x}, kY{y} {}
  const std::string kText;
  const int kX;
  const int kY;
};



#endif /* INCLUDE_TEXT_TEXTURE_H_ */
