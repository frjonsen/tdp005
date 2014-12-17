/*
 * highscore_handler.h
 *
 *  Created on: 16 dec 2014
 *      Author: alest170
 */

#ifndef INCLUDE_HIGHSCORE_HANDLER_H_
#define INCLUDE_HIGHSCORE_HANDLER_H_

#include <vector>
#include <string>

class Highscore
{
public:
  Highscore(int gamescore_);
  //~Highscore();

  void handle_highscore();
  std::vector<std::string> get_highscore();

private:
  int score_;
};



#endif /* INCLUDE_HIGHSCORE_HANDLER_H_ */
