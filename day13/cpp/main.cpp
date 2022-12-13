#include <cstddef>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <vector>

class List {
public:
  uint64_t num;
  std::vector<List *> items;
  bool isList;
};

void parseLine(std::istringstream *ss, List *parent_list) {
  std::string word;
  while (*ss >> word) {
    if (word == "[") {
      List *new_list = new List;
      new_list->isList = true;
      parent_list->items.push_back(new_list);
      parseLine(ss, new_list);
    } else if (word == "]") {
      return;
    } else {
      List *number = new List;
      number->num = std::stoi(word);
      number->isList = false;
      parent_list->items.push_back(number);
    }
  }
}

void printList(List *my_list) {
  if (my_list->isList) {
    std::cout << " > ";
    for (size_t i = 0; i < my_list->items.size(); i++) {
      printList(my_list->items.at(i));
    }
  } else {
    std::cout << " " << my_list->num << " ";
    return;
  }
  std::cout << " < ";
}

bool compareSides(List * left_list, List * right_list) {
  return false;
}

int main() {
  std::ifstream file("../test.txt");
  // std::ifstream file("../input.txt");

  if (!file) {
    std::cerr << "Cannot find the file." << std::endl;
  }

  std::string left_line;
  std::string right_line;
  std::string space_line;
  while (std::getline(file, left_line)) {
    // left
    std::istringstream left_stream(left_line);
    List *left_list = new List;
    left_list->isList = true;
    parseLine(&left_stream, left_list);
    printList(left_list);
    std::cout << std::endl;

    // right
    std::getline(file, right_line);
    std::istringstream right_stream(right_line);
    List *right_list = new List;
    right_list->isList = true;
    parseLine(&right_stream, right_list);
    printList(right_list);
    std::cout << std::endl;

    std::getline(file, space_line);
    std::cout << std::endl;

    bool good = compareSides(left_list, right_list);
  }
}
