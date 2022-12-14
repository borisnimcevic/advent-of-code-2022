#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

enum status {
  FALLING,
  STUCK,
  SATURATED,
};

typedef struct {
  uint width;
  uint debth;
} position_t;

std::vector<std::vector<char>> field;
uint64_t offset = std::numeric_limits<uint64_t>::max();
uint64_t width_max = 0;
uint64_t debth_max = 0;

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

bool isDownAvailable(position_t *current_position) {
  if (field.at(current_position->debth + 1).at(current_position->width) ==
      '.') {
    return true;
  }
  return false;
}

bool isLeftAvailable(position_t *current_position) {
  if (field.at(current_position->debth + 1).at(current_position->width - 1) ==
      '.') {
    return true;
  }
  return false;
}

bool isRightAvailable(position_t *current_position) {
  if (field.at(current_position->debth + 1).at(current_position->width + 1) ==
      '.') {
    return true;
  }
  return false;
}
void moveDown(position_t *current_position) { current_position->debth++; }
void moveLeft(position_t *current_position) {
  current_position->debth++;
  current_position->width--;
}

void moveRight(position_t *current_position) {
  current_position->debth++;
  current_position->width++;
}

status moveSand(position_t *current_position) {
  if (current_position->debth > debth_max) {
    return SATURATED;
  }

  if (isDownAvailable(current_position)) {
    moveDown(current_position);
    return FALLING;
  }

  if (isLeftAvailable(current_position)) {
    moveLeft(current_position);
    return FALLING;
  }

  if (isRightAvailable(current_position)) {
    moveRight(current_position);
    return FALLING;
  }
  return STUCK;
}

void dropSand(const position_t start_position) {
  status sand_status = FALLING;
  while (sand_status != SATURATED) {
    position_t current_position = start_position;
    sand_status = FALLING;
    while (sand_status == FALLING) {
      sand_status = moveSand(&current_position);
    }
    if (sand_status == STUCK) {
      field.at(current_position.debth).at(current_position.width) = 'o';
    }
    // printField();
    // std::cout << std::endl;
  }
}

uint64_t countSand() {
  uint64_t sum = 0;
  for (auto row : field) {
    for (auto col : row) {
      if (col == 'o') {
        sum++;
      }
    }
  }
  return sum;
}

int main() {
  // std::string file_path = "../test.txt";
  std::string file_path = "../input.txt";

  std::ifstream file(file_path);

  if (!file) {
    std::cerr << "Cannot find the file." << std::endl;
  }

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

  position_t start_position;
  start_position.debth = 0;
  start_position.width = 500 - offset;
  dropSand(start_position);
  std::cout << "sand at rest = " << countSand() << std::endl;
  printField();
}






