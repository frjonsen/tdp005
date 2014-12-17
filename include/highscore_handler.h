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
/**
 * Handles highscore
 */
class Highscore
{
public:
  /**
   * Adds points to the score_ variable
   * @param points_ points from play state to be added to score_
   */
  void add_score(int points_);

  /**
   * Handles the external highscore.txt file
   * Adds new score from end state to a vector
   * Sorts the vector,
   * then writes the 3 largest scores to the txt file
   */
  void handle_highscore();

  /**
   * Gets the highscore from highscore.txt
   * Creates a vector with lines from file
   * @return vector of lines
   */
  std::vector<std::string> get_highscore();

private:
  /// Score from won game
  int score_;

  /**
   * Gets current local date
   */
  std::string get_date();

  /**
   * Gets lines from highscore.txt
   * @param stream containing content from highscore.txt
   * @return lines from file
   */
  std::vector<std::string> get_lines(std::istream& stream);

  /**
   * Takes lines from file and splits them to a pair
   * Uses a stringstream to split
   * @param line from highscore.txt
   * @return pair containing score and date, as int and string
   */
  std::pair<int, std::string> parse_lines(std::string line);

};



#endif /* INCLUDE_HIGHSCORE_HANDLER_H_ */
