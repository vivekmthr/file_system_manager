

#include <chrono>
#include <locale>
#include "fill_hash.h"
#include "index_dir.h"


using std::cout;
using std::endl;

void fill_hash_table(Hash_table* h,
                     Hash_table* h_lower,
                     std::vector<std::string>* file_names,
                     Key_table* files);

void fill_files(Key_table* files, std::vector<std::string>* file_names);

void query(Hash_table* h, Hash_table* h_lower);

void query_insensitive(Hash_table* h, Hash_table* h_lower, std::string query);

bool query_table(std::vector<Instance> data, std::string query, 
std::vector <std::string>* lines_added);

bool find_in_vec(std::string find, std::vector<std::string>* lines);

std::string get_line_path(Instance data);

// std::string string_to_lower(std::string str);


/*
 * Main
 * Purpose : fills the main hash_table and instantiates querying
 * Arguments : the directory name through the terminal
 * Returns : 0
 * Effects : None
 * Notes : None
 */
int main(int argc, char** argv) {
  std::string dir_name = argv[1];
  std::vector<std::string> file_names = index_dir(dir_name);
  Hash_table h(file_names.size());
  Hash_table h_lower(10);
  Key_table files(file_names.size());

  // std::vector<std::string> file_names;
  // file_names.push_back("found/found");
  // Hash_table h(0);
  // Hash_table h_lower(10);
  // Key_table files(file_names.size());
  fill_files(&files, &file_names);
  fill_hash_table(&h, &h_lower, &file_names, &files);
  query(&h, &h_lower);
}


/*
 * Fill_files
 * Purpose : Fills the key_table (no values) with all the filepaths,
 * such that they only need to be referenced rather than stored everytime
 * to optimize space.
 * Arguments : A vector of all the files in the directory, and the key_table to fill with
 * Returns : none
 * Effects : None
 * Notes : None
 */
void fill_files(Key_table* files, std::vector<std::string>* file_names) {
  for (int i = 0; i < file_names->size(); i++) {
    files->insert(file_names->at(i));
  }
}


/*
 * fill_hash_table
 * Purpose : Fills the primary hash_table (Stores key value pairs) 
 * with the words from every file
 * Arguments : Pointer to hash_table h (the primary hash_table), a pointer
 * to h_lower, which stores all the uppercase instances to allow case           * sensitiviity, and the key_table which stores all the filenames
 * Returns : none
 * Effects : none
 * Notes : None
 */
void fill_hash_table(Hash_table* h,
                     Hash_table* h_lower,
                     std::vector<std::string>* file_names,
                     Key_table* files) {
  for (int i = 0; i < file_names->size(); i++) {
    add_words_from_file(h, file_names->at(i), h_lower, files);
  }
}

/*
 * Query
 * Purpose : Runs the query loop
 * Arguments : Pointer to hash_table h (the primary hash_table), a pointer
 * to h_lower, which stores all the uppercase instances.
 * Returns : none
 * Effects : none
 * Notes : None
 */
void query(Hash_table* h, Hash_table* h_lower) {
  std::string query;
  std::vector<Instance> data_normal;
  std::vector<Instance> data_lower;
  while (query.substr(0, 2) != "@q") {
    std::cout << "Query? ";
    std::getline(std::cin, query);

    if (query.substr(0, 2) == "@q") {
      cout << "Goodbye! Thank you and have a nice day." << endl;
      break;
    }

    if (query.substr(0, 2) == "@i") {
      query_insensitive(h, h_lower, query);
    }

    else {
     query = stripNonAlphaNum(query);
     std::vector<Instance> data = h->hash_find(query);
     std::vector<std::string> lines_added;
     if(!query_table(data, query, &lines_added))
     cout << query << " Not Found. Try case insensitive search with @i.";
     cout << endl;
    }
  }
}

/*
 * Query_sensitive
 * Purpose : Runs the case sensitive query and prints out the results
 * Arguments : The normal hash table and the query
 * Returns : none
 * Effects : none
 * Notes : None
 */
bool query_table(std::vector<Instance> data, std::string query, std::vector<std::string>* lines_added){
      for (int i = 0; i < data.size(); i++) {
        if (data.at(i).path != nullptr) {
          std::string line_path = get_line_path(data.at(i));
         if (!(find_in_vec(line_path, lines_added))) {
          cout << *(data.at(i).path) << ":";
          cout << data.at(i).line << endl;
          lines_added->push_back(line_path);
        }
        } else {
          return false;
          break;
        }
      }
      return true;
}

void query_insensitive(Hash_table* h, Hash_table* h_lower, std::string query) {
  query = stripNonAlphaNum(query);
  query = query.substr(2, query.size() - 2);
  query = string_to_lower(query);
  std::vector<Instance> data_normal = h->hash_find(query);
  std::vector<Instance> data_lower = h_lower->hash_find(query);
  std::vector<std::string> lines_added;
  bool found1 = query_table(data_normal, query, &lines_added);
  bool found2 = query_table(data_lower, query, &lines_added);
  if(!found1 && !found2){
  cout << query << " Not Found.";
  }
  cout << endl;
}

/*
 * get_line_path
 * Purpose : returns the path of a file
 * Arguments : A instance of the appearance of a word
 * Returns : string containing the file path
 * Effects : none
 * Notes : None
 */
std::string get_line_path(Instance data){
 std::string line_path = *(data.path) + ":";
 for (int i = 0; i < data.line.length(); i++)
 {
   if(data.line[i] == ':'){
     return line_path;
   }
   line_path += data.line[i];
 }
 return "";
}

/*
 * find_in_vec
 * Purpose : finds a given string in a vector
 * Arguments : a string
 * Returns : if it was found or not 
 * Effects : none
 * Notes : None
 */
bool find_in_vec(std::string find, std::vector<std::string>* lines) {
  for (int i = 0; i < lines->size(); i++) {
    if (find == lines->at(i)) {
      return true;
    }
  }
  return false;
}


// std::string stripNonAlphaNum(std::string key) {
//   int first_index = 1000;
//   int last_index = 0;
//   std::locale loc;
//   for (int i = 0; i < key.size(); i++) {
//     if (std::isalnum(key[i], loc)) {
//       if (i < first_index) {
//         first_index = i;
//       }
//       if (i > last_index) {
//         last_index = i;
//       }
//     }
//   }
//   return key.substr(first_index, last_index - first_index + 1);
// }


// std::string string_to_lower(std::string str) {
//   int j = 0;
//   std::locale loc;
//   while (str[j]) {
//     str[j] = std::tolower(str[j], loc);
//     j++;
//   }
//   return str;
// }
