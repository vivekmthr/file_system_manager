/*
 * COMP15 Homework 4 , Spring 2020
 * key_table.h
 * By : Vivek Mathur
 * Completed : july 31st , 2020
 *
 * Key_table funtion defintions + declarations
 * Purpose : Contains my implementations for the 
 * key_table class
 */


#ifndef KEY_TABLE
#define KEY_TABLE
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;

class Key_table {
  struct Table_node {
    // each Table_node contains a vector of keys
    Table_node() {
      std::vector<std::string> vec;
      this->vec = vec;
    }
    std::vector<std::string> vec;
  };

 public:
  /*
   * Constructor
   * Purpose : depending on the size passed in, allocates a table of about
   * 60-80% load factor.
   * Arguments : int size
   * Returns : none
   * Effects : none
   * Notes : None
   */
  Key_table(int size) {
    table = new Table_node* [size * 2] { nullptr };
    table_size = size * 2;
  }

  ~Key_table() { clear_mem(); }

  /*
   * Insert
   * Purpose : Inserts a given key into the table
   * Arguments : key
   * Returns : a boolean representing whether a new key was added, or not
   * Effects : none
   * Notes : none
   */
  bool insert(std::string key) {
    int table_location = hash(key);
    if (table[table_location] == nullptr) {
      Table_node* new_node = new Table_node();
      table[table_location] = new_node;
    }

    for (int i = 0; i < table[table_location]->vec.size(); i++) {
      if (key == table[table_location]->vec.at(i)) {
        return false;
      }
    }

    table[table_location]->vec.push_back(key);
    return true;
  }

  /*
   * Find
   * Purpose : Find a given key in the table and return the key
   * Arguments : key to find
   * Returns : key
   * Effects : none
   * Notes : none
   */
  std::string hash_find(std::string key) {
    int table_location = hash(key);
    if (table[table_location] == nullptr) {
      return "KNF";
    }
    for (int i = 0; i < table[table_location]->vec.size(); i++) {
      if (key == table[table_location]->vec.at(i)) {
        return key;
      }
    }
    return "KNF";
  }

  /*
   * get_pointer_to_key
   * Purpose : returns a pointer to a given key
   * Arguments : key to find
   * Returns : pointer to given key
   * Effects : none
   * Notes : none
   */
  std::string* get_pointer_to_key(std::string key) {
    int table_location = hash(key);
    if (table[table_location] == nullptr) {
      return nullptr;
    }
    for (int i = 0; i < table[table_location]->vec.size(); i++) {
      if (key == table[table_location]->vec.at(i)) {
        return &table[table_location]->vec.at(i);
      }
    }
    return nullptr;
  }

  /*
   * Destructor cleans up memory
   * Purpose : returns a pointer to a given key
   * Arguments : key to find
   * Returns : pointer to given key
   * Effects : none
   * Notes : none
   */
  void clear_mem() {
    for (int i = 0; i < table_size; i++) {
      delete table[i];
    }
    delete[] table;
  }

 private:
  // hash table is a pointer to an array of pointers to hash nodes
  Table_node** table;
  int table_size;

  /*
   * hash
   * Purpose : hashes a string into an int to go into the table
   * Arguments : an input string
   * Returns : none
   * Effects : none
   * Notes : none
   */
  int hash(std::string input) {
    int result = std::hash<std::string>{}(input);
    return abs(result % table_size);
  }
};

#endif