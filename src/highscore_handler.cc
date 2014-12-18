/*
 * highscore_handler.cc
 *
 *  Created on: 16 dec 2014
 *      Author: alest170
 */

#include <highscore_handler.h>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <time.h>
#include <sstream>

 void Highscore::add_score(int points_)
 {
   score_ = points_;
 }

std::string Highscore::get_date()
{
  time_t theTime = time ( NULL );
  struct tm *aTime = localtime ( &theTime );

  int day = aTime->tm_mday;
  int month = aTime->tm_mon + 1;
  int year = aTime->tm_year + 1900;

  std::string date_ = std::to_string ( year ) + "-" + std::to_string ( month )
      + "-" + std::to_string ( day );

  return date_;
}

std::vector<std::string> Highscore::get_lines(std::istream& stream)
{
  std::vector<std::string> lines;
  std::string line;

  while( getline ( stream, line ) )
  {
    lines.push_back ( line );
  }
  return lines;
}

std::vector<std::string> Highscore::get_highscore()
{
  std::ifstream file ( "highscore.txt" );
  std::vector<std::string> lines { get_lines ( file ) };
  file.close ();

  return lines;
}

std::pair<int, std::string> Highscore::parse_lines(std::string line)
    {
      std::string number;
      std::string date;
      std::stringstream ss{line};
      std::pair<int, std::string> parsed_pair_;

      ss >> number;
      ss >> date;

      parsed_pair_ = std::make_pair (std::stoi(number), date);

      return parsed_pair_;
    }

void Highscore::handle_highscore()
{
  std::vector<std::string> iHighscore{get_highscore()};
  std::vector<std::pair<int, std::string>> pair_vect_;
  std::ofstream write;

  std::cout << "so far so good" << std::endl;

  for ( unsigned int i = 0; i < iHighscore.size(); ++i )
  {
    pair_vect_.push_back(parse_lines(iHighscore.at(i)));
  }
  std::cout << "efter loop: \n" << "score: "<< score_<< "Datum: " << get_date() << std::endl;

  pair_vect_.push_back(std::make_pair(score_, (get_date())));

  std::sort(pair_vect_.begin(),pair_vect_.end());
  std::reverse(pair_vect_.begin(), pair_vect_.end());

  write.open("highscore.txt", std::ios::trunc);

  for( unsigned int i = 0; i < ((pair_vect_.size()) -1); ++i )
  {
    std::string pair_score = std::to_string(std::get<0>(pair_vect_.at(i)));
    std::string pair_date = std::get<1>(pair_vect_.at(i));
    std::string output = pair_score + " " + pair_date;
    std::cout << output << std::endl;

    write << output << std::endl;
  }
  write.close();

}

