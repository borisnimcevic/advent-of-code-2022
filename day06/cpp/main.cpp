#include <fstream>
#include <iostream>
#include <set>

uint32_t findMatch(const std::string *const input, const uint8_t offset) {
  std::set<char> char_set;

  for (auto index = 0; index < input->size(); index++) {

    if (char_set.end() != char_set.find(input->at(index))) {
      index -= char_set.size();
      char_set.clear();
      continue;
    }

    char_set.insert(input->at(index));
    if (char_set.size() == offset) {
      return index + 1; // becasue the solution is 1-indexed
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
  std::cout << "part one: " << findMatch(&line, 4) << std::endl;
  std::cout << "part two: " << findMatch(&line, 14) << std::endl;
}
