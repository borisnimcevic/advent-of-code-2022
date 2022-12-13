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
  bool isDecoder = false;
  bool god = false;
};

std::vector<List *> all_items;

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
    if (!my_list->god) {
      std::cout << "[";
    }
    for (size_t i = 0; i < my_list->items.size(); i++) {
      printList(my_list->items.at(i));
    }
  } else {
    std::cout << " " << my_list->num << " ";
    return;
  }
  if (!my_list->god) {
    std::cout << "]";
  }
}

void convertToList(List *my_list) {
  uint64_t temp_num = my_list->num;
  my_list->isList = true;
  List *new_list = new List;
  new_list->isList = false;
  new_list->num = temp_num;
  my_list->items.push_back(new_list);
}

void unconvertList(List *my_list) {
  my_list->isList = false;
  my_list->items.clear();
}

status correnctInputs(List *left_list, List *right_list) {
  bool left_changed = false;
  bool right_changed = false;
  status outcome;
  if (!left_list->isList) {
    convertToList(left_list);
    left_changed = true;
  } else {
    convertToList(right_list);
    right_changed = true;
  }
  outcome = compareSides(left_list, right_list);
  if (left_changed) {
    unconvertList(left_list);
  }
  if (right_changed) {
    unconvertList(right_list);
  }

  return outcome;
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

void swap(List **left, List **right) {
  List *temp = *left;
  *left = *right;
  *right = temp;
}

void bubbleSortList(std::vector<List *> *long_list) {
  const size_t N = long_list->size();
  bool change = true;
  while (change) {
    change = false;
    for (size_t i = 0; i < N - 1; i++) {
      status outcome = compareSides(long_list->at(i)->items.at(0),
                                    long_list->at(i + 1)->items.at(0));
      if (outcome != GOOD) {
        change = true;
        swap(&long_list->at(i), &long_list->at(i + 1));
      }
    }
  }
}

int main() {
  // std::ifstream file("../test-pt1.txt");
  // std::ifstream file("../test-pt2.txt");
  // std::ifstream file("../input-pt1.txt");
  std::ifstream file("../input-pt2.txt");

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
    // left
    std::istringstream left_stream(left_line);
    List *left_list = new List;
    left_list->god = true;
    left_list->isList = true;
    parseLine(&left_stream, left_list);

    // right
    std::getline(file, right_line);
    std::istringstream right_stream(right_line);
    List *right_list = new List;
    right_list->god = true;
    right_list->isList = true;
    parseLine(&right_stream, right_list);

    // space
    std::getline(file, space_line);
    // std::cout << std::endl;

    status good = compareSides(left_list->items.at(0), right_list->items.at(0));
    if (good == GOOD) {
      summary.push_back(counter);
    }

    all_items.push_back(left_list);
    all_items.push_back(right_list);
  }

  uint64_t sum = 0;
  for (auto var : summary) {
    sum += var;
  }
  std::cout << "Part 1 = " << sum << std::endl;

  all_items.at(all_items.size() - 1)->isDecoder = true;
  all_items.at(all_items.size() - 2)->isDecoder = true;

  bubbleSortList(&all_items);

  uint64_t pt2 = 1;
  for (size_t i = 0; i < all_items.size(); i++) {
    if (all_items.at(i)->isDecoder) {
      pt2 *= i + 1;
    }
  }
  std::cout << "Part 2 = " << pt2 << std::endl;
}
