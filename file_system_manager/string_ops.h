/*
 * COMP15 Homework 4 , Spring 2020
 * string_ops.h
 * By : Vivek Mathur
 * Completed : july 31st , 2020
 *
 * string_ops.h funtion defintions + declarations
 * Purpose : Contains my implementations for the 
 * string_ops functions, which represents the bucket of the Hash_table class
 */
#ifndef STRING_OPS_h
#define STRING_OPS_H

#include <string>
#include <locale>

/*
 * StripNonAlphaNUm
 * Purpose : strips all leading or lagging non-alphanumeric chars from a string
 * Arguments : a string
 * Returns : string without leading/lagging non alphanumeric chars
 * Effects : none
 * Notes : None
 */
std::string stripNonAlphaNum(std::string key) {
  int first_index = 1000;
  int last_index = 0;
  std::locale loc;
  for (int i = 0; i < key.size(); i++) {
    if (std::isalnum(key[i], loc)) {
      if (i < first_index) {
        first_index = i;
      }
      if (i > last_index) {
        last_index = i;
      }
    }
  }
  if(first_index == 1000){
    return "";
  }
  return key.substr(first_index, last_index - first_index + 1);
}

/*
 * string_to_lower
 * Purpose : Fills the key_table (no values) with all the filepaths,
 * such that they only need to be referenced rather than stored everytime
 * to optimize space.
 * Arguments : A vector of all the files in the directory, and the key_table to fill with
 * Returns : none
 * Effects : None
 * Notes : None
 */
std::string string_to_lower(std::string str) {
  int j = 0;
  std::locale loc;
  while (str[j]) {
    str[j] = std::tolower(str[j], loc);
    j++;
  }
  return str;
}

#endif