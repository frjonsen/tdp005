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

Highscore::Highscore(int gamescore_)
    : score_ { gamescore_ } {}

std::string get_date()
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

std::vector<std::string> get_lines(std::istream& stream)
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

  std::cout << lines.at ( 0 ) << std::endl;

  return lines;
}

std::pair<int, std::string> parse_lines(std::string line)
    {
      std::string number;
      std::string date;
      std::stringstream ss{line};

      ss >> number;
      ss >> date;
      //std::cout << number << std::endl;
     // std::cout << date << std::endl;

      return std::make_pair(std::stoi(number), date);
    }

void Highscore::handle_highscore()
{
  std::vector<std::string> iHighscore{get_highscore()};
  std::vector<std::pair<int, std::string>> splitted;
  std::ofstream write;

  for ( unsigned int i = 0; i < iHighscore.size(); ++i )
  {
    splitted.push_back(parse_lines(iHighscore.at(i)));
  }
  splitted.push_back(std::make_pair(score_, get_date()));
  sort(splitted.begin(),splitted.end());

  write.open("highscore.txt");

  for( unsigned int i = 0; i < splitted.size(); ++i )
  {
    int pair_score = std::get<0>(splitted.at(i));
    std::string pair_date = std::get<1>(splitted.at(i));
    std::string output = pair_score + " " + pair_date;

    write << 34;
  }
  write.close();

}

