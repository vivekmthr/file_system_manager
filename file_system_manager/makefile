# Makefile for Assignment 01
# matt russell
# comp15 2020 summer

# This file will build tests for any COMP15 assignment

# To use it, do the following:
#     1) Create one or more .h files with your testing functions
#     2) Name each file XXXX_tests.h, where XXXX is anything you want.
#     3) Create any rules you need to build .cpp files.

CXX=g++
CXXFLAGS=-std=c++11

default: hash_tests

hash_tests: hash_tests.o hash_table.o
	$(CXX) $(CXXFLAGS) -O2 -o gerp hash_tests.o hash_table.o

hash_tests.o: hash_tests.cpp index_dir.h fill_hash.h
	$(CXX) $(CXXFLAGS) -c hash_tests.cpp

hash_table.o: hash_table.cpp hash_table.h vector_ops.h 
	$(CXX) $(CXXFLAGS) -c hash_table.cpp







# --- clean destroys all the .o files
clean:
	-@rm -rf *.o 2>/dev/null