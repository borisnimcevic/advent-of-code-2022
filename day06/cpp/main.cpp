#include <fstream>
#include <iostream>
#include <set>

uint32_t findMatch_better(const std::string *const input,
                          const uint8_t offset) {
  std::set<char> char_set;
  for (auto index = 0; index < input->size(); index++) {
    if (char_set.end() == char_set.find(input->at(index))) {
      char_set.insert(input->at(index));
      if (char_set.size() == offset) {
        return index + 1; // becasue the solution 1-indexed
      }
    } else {
      index -= char_set.size();
      char_set.clear();
    }
  }
  return 0;
}

int main() {
  // std::ifstream file("../test.txt");
  std::ifstream file("../input.txt");

  if (!file) {
    std::cerr << "Cannot find the file." << std::endl;
  }

  std::string line;
  std::getline(file, line);
  std::cout << "part one: " << findMatch_better(&line, 4) << std::endl;
  std::cout << "part two: " << findMatch_better(&line, 14) << std::endl;
}
