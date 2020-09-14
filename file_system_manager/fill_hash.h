

#include <fstream>
#include <locale>
#include <sstream>
#include "hash_table.h"
#include "key_table.h"
#include "string_ops.h"


std::vector<std::string> file_names;

void loop_through_file(std::string path,
                       std::string filename,
                       Hash_table* table,
                       Hash_table* only_lower_case,
                       Key_table* files);

bool bool_string_to_lower(std::string str, std::string* new_str);



/*
 * add_words_from_file
 * Purpose : Fills the primary hash_table (Stores key value pairs) 
 * with the words from a file
 * Arguments : Pointer to hash_table h (the primary hash_table), a pointer
 * to h_lower, which stores all the uppercase instances to allow case           * sensitiviity, and the key_table which stores all the filenames,
 * and the filename
 * Returns : none
 * Effects : none
 * Notes : The path stuff wasn't working so I found a solution on stack
 * overflow
 */
void add_words_from_file(Hash_table* table,
                         std::string filename,
                         Hash_table* only_lower_case,
                         Key_table* files) {
  std::string path = __FILE__;  
  // removes file name
  path = path.substr(0, 1 + path.find_last_of('\\'));
  // adds input file to path
  path += filename;  
  loop_through_file(path, filename, table, only_lower_case, files);
}


/*
 * loop_through_file
 * Purpose : loops through a file and adds every word to the necessary hash
 * table
 * Arguments : Pointer to hash_table h (the primary hash_table), a pointer
 * to h_lower, which stores all the uppercase instances to allow case           * sensitiviity, pointer to the key_table which stores all the filenames,
 * string path of the file.
 * Returns : none
 * Effects : none
 * Notes : none
 */
void loop_through_file(std::string path,
                       std::string filename,
                       Hash_table* table,
                       Hash_table* only_lower_case,
                       Key_table* files) {
  std::ifstream infile;
  std::string file_line;
  infile.open(path);
  int line_no = 1;

  while (std::getline(infile, file_line)) {
    std::stringstream line(file_line);
    std::string key;
    Key_table key_table(800);

    while (line >> key) {
      key = stripNonAlphaNum(key);
      std::string keylower, curr_value;
      bool is_lower_case = bool_string_to_lower(key, &keylower);
      bool check = false;
      std::string* Pcurr_value = files->get_pointer_to_key(filename);
      curr_value += std::to_string(line_no);
      curr_value += ": " + file_line;
      check = key_table.insert(key);

        if (check) {
          if (is_lower_case) {
            table->insert(key, curr_value, Pcurr_value);
          } else {
            table->insert(key, curr_value, Pcurr_value);
            only_lower_case->insert(keylower, curr_value, Pcurr_value);
          }
        }
    }
    line_no++;
  }
}

/*
 * String_to_lower
 * Purpose : Converts a string to lower case and returns true, if the string
 * was already lowercase
 * Arguments : a copy of the original string, and pointer to it
 * Returns : none
 * Effects : none
 * Notes : none
 */
bool bool_string_to_lower(std::string str, std::string* new_str) {
  int j = 0;
  bool is_lower = true;
  for (int i = 0; i < str.size(); i++) {
    if ((str[i] > 64 && str[i] < 91)) {
      *(new_str) += std::tolower(str[i]);
      is_lower = false;
    } else {
      *(new_str) += str[i];
    }
    j++;
  }
  return is_lower;
}



