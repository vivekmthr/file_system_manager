/*
 * COMP15 Homework 4 , Spring 2020
 * hash_table.h
 * By : Vivek Mathur
 * Completed : july 31st , 2020
 *
 * hash_table.h funtion defintions + declarations
 * Purpose : Contains my implementations for the
 * hash_table functions, which represents the bucket of the Hash_table class
 */

#ifndef HASH_TABLE
#define HASH_TABLE

#include <string>
#include <vector>
#include "vector_ops.h"
using std::cout;
using std::endl;


class Hash_table {
  struct Hash_node {
    // each hash_node points to a vector of key value pairs
    Hash_node() { vec = Vec(); }
    Vec vec;
  };

 public:
  // constructor
  Hash_table(int size);

  // destructor
  ~Hash_table() { clear_mem(); }

  // Public member functions
  bool insert(std::string key, std::string value, std::string* path);
  void clear_mem();
  std::vector<Instance> hash_find(std::string key);
  std::string* get_pointer_to_key(std::string key);
  void print_table();

 private:
  // hash table is a pointer to an array of pointers to hash nodes
  Hash_node** table;
  int table_size;
  int hash(std::string input);
};

#endif