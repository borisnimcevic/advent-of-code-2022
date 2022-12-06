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
  auto start = std::chrono::high_resolution_clock::now();
  auto stop = std::chrono::high_resolution_clock::now();
  auto overhead =
      std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << "timing overhead = " << overhead.count() << "microseconds"
            << std::endl;

  start = std::chrono::high_resolution_clock::now();
  const auto part1 = findMatch(&line, 4);
  stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
      stop - start - overhead);
  std::cout << "part one: " << part1 << ", duration: " << duration.count()
            << " microseconds" << std::endl;

  start = std::chrono::high_resolution_clock::now();
  const auto part2 = findMatch(&line, 14);
  stop = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::microseconds>(
      stop - start - overhead);
  std::cout << "part two: " << part2 << ", duration: " << duration.count()
            << " microseconds" << std::endl;
}
