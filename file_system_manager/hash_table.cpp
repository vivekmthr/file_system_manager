

#include "hash_table.h"
#include "Instance.h"
#include <chrono>
using std::cout;
using std::endl;


/*
 * Constructor
 * Purpose : depending on the size passed in, allocates a table of about 
 * 60-80% load factor.
 * Arguments : int size
 * Returns : none
 * Effects : none
 * Notes : None
 */
Hash_table::Hash_table(int size) {
  if (size == 0) {
    table = new Hash_node* [20] { nullptr };
    table_size = 20;
  } else if (size < 50) {
    table = new Hash_node* [5000] { nullptr };
    table_size = 5000;
  } else {
    table = new Hash_node* [30011] { nullptr };
    table_size = 30011;
  }
}

/*
 * Insert
 * Purpose : Inserts a given key, it's value, and the path of the value
 * into the table
 * Arguments : key, value, path
 * Returns : a boolean representing whether a new key was added, or an 
 * instance was added to a previously existing key
 * Effects : none
 * Notes : none
*/
bool Hash_table::insert(std::string key, std::string value, std::string* path) {
  int table_location = hash(key);
  if (table[table_location] == nullptr) {
    Hash_node* new_node = new Hash_node();
    table[table_location] = new_node;
  }
  bool check = table[table_location]->vec.insert_or_modexisting(key, value, path);   
  return check;
}

/*
 * Find
 * Purpose : Find a given key in the table and returns the value associated    * with it
 * Arguments : key to find
 * Returns : A vector of instances of the given key
 * Effects : none
 * Notes : none
*/
std::vector<Instance> Hash_table::hash_find(std::string key) {
  int table_location = hash(key);
  if (table[table_location] == nullptr) {
    std::vector<Instance> instances;
    Instance instance("KNF", nullptr);
    instances.push_back(instance);
    return instances;
  }
  std::vector<Instance> vector = table[table_location]->vec.find(key);
  return vector;
}

/*
 * Find
 * Purpose : cleans up heap allocated memory
 * Arguments : none
 * Returns : none
 * Effects : none
 * Notes : none
*/
void Hash_table::clear_mem() {
  for (int i = 0; i < table_size; i++) {
    delete table[i];
  }
  delete[] table;
}

/*
 * print_table
 * Purpose : prints table for testing purposes
 * Arguments : none
 * Returns : none
 * Effects : none
 * Notes : none
*/
void Hash_table::print_table() {
  for (int i = 0; i < table_size; i++) {
    if (table[i] != nullptr) {
      table[i]->vec.print();
    }
  }
  cout << endl;
}

/*
 * hash
 * Purpose : hashes a string into an int to go into the table
 * Arguments : an input string
 * Returns : none
 * Effects : none
 * Notes : none
*/
int Hash_table::hash(std::string input) {
  int result = std::hash<std::string>{}(input);
  return abs(result % table_size);
}