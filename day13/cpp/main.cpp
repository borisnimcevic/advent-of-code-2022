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

enum status {
  KEEP_GOING,
  GOOD,
  BAD,
};

status compareSides(List *left_list, List *right_list);

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

void convertToList(List *my_list) {
  uint64_t temp_num = my_list->num;
  my_list->num = 9999;
  my_list->isList = true;
  List *new_list = new List;
  new_list->isList = false;
  new_list->num = temp_num;
  my_list->items.push_back(new_list);
}

status correnctInputs(List *left_list, List *right_list) {
  if (!left_list->isList) {
    convertToList(left_list);
  } else {
    convertToList(right_list);
  }
  return compareSides(left_list, right_list);
}

status compareSides(List *left_list, List *right_list) {
  // numbers;
  if (!left_list->isList && !right_list->isList) {
    if (left_list->num < right_list->num) {
      return GOOD;
    }

    if (left_list->num > right_list->num) {
      return BAD;
    }

    if (left_list->num == right_list->num) {
      return KEEP_GOING;
    }
  }

  // list
  else if (left_list->isList && right_list->isList) {
    const size_t left_size = left_list->items.size();
    const size_t right_size = right_list->items.size();
    const size_t length = (left_size < right_size) ? left_size : right_size;
    for (size_t i = 0; i < length; i++) {
      const status temp_status =
          compareSides(left_list->items.at(i), right_list->items.at(i));
      if (temp_status != KEEP_GOING) {
        return temp_status;
      }
    }

    if (right_size > left_size) {
      return GOOD;
    } else if (left_size == right_size) {
      return KEEP_GOING;
    } else {
      return BAD;
    }
  }

  // mixed
  else {
    return correnctInputs(left_list, right_list);
  }
  return KEEP_GOING;
}

int main() {
  // std::ifstream file("../test.txt");
  std::ifstream file("../input.txt");

  if (!file) {
    std::cerr << "Cannot find the file." << std::endl;
  }

  std::string left_line;
  std::string right_line;
  std::string space_line;
  uint64_t counter = 0;
  std::vector<uint64_t> summary;
  while (std::getline(file, left_line)) {
    counter++;
    std::cout << "counter = " << counter << std::endl;
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

    status good = compareSides(left_list, right_list);
    if (good == KEEP_GOING) {
      std::cout << "keep going" << std::endl;
    }
    if (good == GOOD) {
      summary.push_back(counter);
      std::cout << "good" << std::endl;
    }
    if (good == BAD) {
      std::cout << "bad" << std::endl;
    }
  }

  uint64_t sum = 0;
  for (auto var : summary) {
    sum += var;
  }
  std::cout << "sum = " << sum << std::endl;
}
