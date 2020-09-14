/*
 * COMP15 Homework 4 , Spring 2020
 * Instance.h
 * By : Vivek Mathur
 * Completed : july 31st , 2020
 *
 * Instance Struct
 * Purpose : Contains implementation for Instance struct
 */


#ifndef INSTANCE
#define INSTANCE

#include <string>

//An instance represents an instance of a line,
//struct because needs to be fully public
struct Instance {
  Instance(std::string line, std::string* path) {
    this->line = line;
    this->path = path;
  }
  Instance() {
    this->line = "";
    this->path = nullptr;
  }
  std::string line;
  std::string* path;
};

#endif