#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

std::pair<size_t, std::string> hash_calculator(std::ifstream & fs, std::string path_name) {
  size_t hashvalue;
  std::string input_line;
  std::string input_lines;
  std::hash<std::string> str_hash;
  while (!fs.eof()) {
    getline(fs, input_line);
    input_lines.append(input_line);
  }
  hashvalue = str_hash(input_lines);
  std::pair<size_t, std::string> cur_pair(hashvalue, path_name);
  return cur_pair;
}

void compare_output(std::pair<size_t, std::string> curpair,
                    std::unordered_map<size_t, std::string> & mymap) {
  std::unordered_map<size_t, std::string>::iterator it = mymap.find(curpair.first);
  //initialization, curpair.first is hash value, curpair.second is filename.
  if (it == mymap.end()) {
    //if not found, insert it
    mymap.insert(curpair);
  }
  else {
    std::cout << "#Removing " << curpair.second << " (duplicate of " << it->second << ")."
              << std::endl;
    std::cout << "rm " << curpair.second << std::endl;
  }
}

//define DIR* to represent a directory stream
//define dirent* to represent a specific file
//function1: DIR * opendir(const * char), open argv[i]
//function2: dirent * readdir(DIR *), read a specific file

void dedup_helper(const std::string & dir, std::unordered_map<size_t, std::string> & mymap) {
  DIR * current_dir;
  dirent * ent;
  //  std::cout << "dir =" << dir << std::endl;
  if ((current_dir = opendir(dir.c_str())) == 0) {
    fprintf(stderr, "Can not open dir!\n");
    exit(EXIT_FAILURE);
  }
  else {
    while ((ent = readdir(current_dir)) != NULL) {
      std::string filename = ent->d_name;  //go to each file
      if (filename == "." || filename == "..") {
        continue;
      }
      else if (ent->d_type == DT_DIR) {
        std::string inner_dir = dir + "/" + filename;
        dedup_helper(inner_dir, mymap);
      }
      else if (ent->d_type == DT_REG) {
        //if it is regular file
        //calculate hash and check if it's in mymap
        std::string path_name = dir + "/" + filename;  //figure path name
        std::ifstream fs(path_name.c_str());           //open file and get file stream
        if (fs.good()) {
          //calculate hash value and compare
          std::pair<size_t, std::string> curpair = hash_calculator(fs, path_name);
          compare_output(curpair, mymap);
          //stop here
        }
        else {
          std::cerr << "Can not open this file.\n";
          exit(EXIT_FAILURE);
        }
      }
      else {
        std::cerr << "We do not process this file type.\n";
      }
    }
  }
  closedir(current_dir);
}
//main function
//define unordered_map, call dedup_helper
int main(int argc, char ** argv) {
  if (argc < 2) {
    fprintf(stderr, "This program needs argument.\n");
    exit(EXIT_FAILURE);
  }

  std::unordered_map<size_t, std::string> mymap;
  std::cout << "#!/bin/bash" << std::endl;
  for (int i = 1; i < argc; i++) {
    const std::string dir = argv[i];
    //std::cout << "In main, dir = " << dir << std::endl;
    dedup_helper(dir, mymap);
    //stop here
  }
  return 0;
}
