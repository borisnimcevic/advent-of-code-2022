#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

typedef struct {
  uint width;
  uint debth;
} position_t;

std::vector<std::vector<char>> field;

void createField(const uint64_t col, const uint64_t row) {
  std::vector<char> temp_row;
  for (uint64_t x = 0; x < row + 2; x++) {
    for (uint64_t y = 0; y < col + 3; y++) {
      temp_row.push_back('.');
    }
    field.push_back(temp_row);
    temp_row.clear();
  }
}

void printField() {
  for (auto row : field) {
    for (auto col : row) {
      std::cout << col;
    }
    std::cout << std::endl;
  }
}

void drawVertical(const int up, const int down, const int width) {
  for (int debth = up; debth <= down; debth++) {
    field.at(debth).at(width) = '#';
  }
}

void drawHorizontal(const int left, const int right, const int debth) {
  for (int width = left; width <= right; width++) {
    field.at(debth).at(width) = '#';
  }
}

void drawLine(const position_t current_pos, const position_t target_pos) {
  if (current_pos.width == target_pos.width) {
    if (current_pos.debth > target_pos.debth) {
      drawVertical(target_pos.debth, current_pos.debth, current_pos.width);

    } else {
      drawVertical(current_pos.debth, target_pos.debth, current_pos.width);
    }
  }
  if (current_pos.debth == target_pos.debth) {
    if (current_pos.width > target_pos.width) {
      drawHorizontal(target_pos.width, current_pos.width, current_pos.debth);
    } else {
      drawHorizontal(current_pos.width, target_pos.width, current_pos.debth);
    }
  }
}

int main() {
  // std::string file_path = "../test.txt";
  std::string file_path = "../input.txt";

  std::ifstream file(file_path);

  if (!file) {
    std::cerr << "Cannot find the file." << std::endl;
  }

  uint64_t offset = std::numeric_limits<uint64_t>::max();
  uint64_t width_max = 0;
  uint64_t debth_max = 0;

  std::string line;
  while (std::getline(file, line)) {

    std::istringstream ss(line);
    uint64_t num;
    while (ss >> num) {
      if (num > width_max)
        width_max = num;
      if (num < offset)
        offset = num;

      ss >> num;
      if (num > debth_max)
        debth_max = num;
    }
  }
  // std::cout << "width max = " << width_max << std::endl;
  // std::cout << "debth max = " << debth_max << std::endl;
  // std::cout << "offset = " << offset << std::endl;
  // std::cout << "Hello world" << std::endl;

  offset--; // so there's an empty line on the left
  createField(width_max - offset, debth_max);
  // printField();

  std::ifstream file_again(file_path);

  position_t current_pos;
  while (std::getline(file_again, line)) {

    std::istringstream ss(line);
    uint64_t num;
    ss >> current_pos.width;
    current_pos.width -= offset;
    ss >> current_pos.debth;
    while (ss >> num) {
      position_t target_pos;
      target_pos.width = num;
      target_pos.width -= offset;
      ss >> num;
      target_pos.debth = num;
      drawLine(current_pos, target_pos);
      current_pos.width = target_pos.width;
      current_pos.debth = target_pos.debth;
    }
  }
  printField();
}
