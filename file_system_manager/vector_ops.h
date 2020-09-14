/*
 * COMP15 Homework 4 , Spring 2020
 * vector_ops.h
 * By : Vivek Mathur
 * Completed : july 31st , 2020
 *
 * vector_ops.h funtion defintions + declarations
 * Purpose : Contains my implementations for the
 * vec class, which represents the bucket of the Hash_table class
 */

#ifndef VEC
#define VEC

#include <iostream>
#include <string>
#include <vector>
#include "Instance.h"

using std::cout;
using std::endl;

class Vec {
  // each Vec is a vector of vector_nodes, each of which contains
  // a key and an associated vector of the instances of that key
  struct Vector_node {
    Vector_node(std::string key, std::vector<Instance> instances) {
      this->key = key;
      this->instances = instances;
    }
    std::string key;
    std::vector<Instance> instances;
  };

 public:
  Vec() {}

  /*
   * Insert
   * Purpose : Inserts a given key, it's value, and the path of the value
   * into the vector
   * Arguments : key, value, path
   * Returns : a boolean representing whether a new key was added, or an
   * instance was added to a previously existing key
   * Effects : none
   * Notes : none
   */
  bool insert_or_modexisting(std::string key,
                             std::string instance,
                             std::string* path) {
    for (int i = 0; i < vec.size(); i++) {
      if (vec.at(i).key == key) {
        Instance new_instance(instance, path);
        vec.at(i).instances.push_back(new_instance);
        return false;
      }
    }
    std::vector<Instance> instances;
    Instance new_instance(instance, path);
    instances.push_back(new_instance);
    Vector_node new_node(key, instances);
    vec.push_back(new_node);
    return true;
  }

  /*
   * Find
   * Purpose : Find a given key in the table and returns the value associated
   * * with it Arguments : key to find Returns : A vector of instances of the
   * given key Effects : none Notes : none
   */
  std::vector<Instance> find(std::string key) {
    for (int i = 0; i < vec.size(); i++) {
      // if the key exists push into the value vec at that key
      if (vec.at(i).key == key) {
        return vec.at(i).instances;
      }
    }
    std::vector<Instance> instances;
    Instance instance("KNF", nullptr);
    instances.push_back(instance);
    return instances;
  }

  /*
   * Find
   * Purpose : Prints the vector
   * Arguments : none
   * Returns : none
   * Effects : none
   * Notes : only for testing purposes
   */
  void print() {
    for (int i = 0; i < vec.size(); i++) {
      // if the key exists push into the value vec at that key
      cout << "key: " << vec.at(i).key << endl;
    }
  }

 private:
  std::vector<Vector_node> vec;

  std::string string_to_lower(std::string str) {
    int j = 0;
    std::locale loc;
    while (str[j]) {
      str[j] = std::tolower(str[j], loc);
      j++;
    }
    return str;
  }
};

#endif