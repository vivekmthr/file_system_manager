#ifndef LOCATION_H
#define LOCATION_H

#include <string>


class Location {
  public: 
  Location(std::string location, int line_number) {
    file_location = location;
    this->line_number = line_number;
  }
  Location(){
    
  }
  std::string file_location;
  int line_number;
};

#endif