#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#define NUMBER_OF_KNOTS 10

struct point {
  int x;
  int y;
};

point T;

void printField(std::vector<std::vector<bool>> field) {
  for (auto row = 0; row < field.size(); row++) {
    for (auto col = 0; col < field.at(0).size(); col++) {
      if (field.at(row).at(col))
        std::cout << "#";
      else
        std::cout << ".";
    }
    std::cout << std::endl;
  }
}

void updateField(std::vector<std::vector<bool>> *field, const std::vector<point> * const knots) {
  const uint8_t index = 9;
  field->at(knots->at(index).x).at(knots->at(index).y) = true;
}

void adjustKnot(point *const H, point *const T) {
  const int x_diff = (H->x - T->x);
  const int y_diff = (H->y - T->y);
  if (abs(x_diff) > 1 || abs(y_diff) > 1) {
    T->x += x_diff / abs(x_diff);
    T->y += y_diff / abs(y_diff);
  }
}

uint64_t countVisits(std::vector<std::vector<bool>> field) {
  uint64_t sum = 0;
  for (auto row : field) {
    for (auto col : row) {
      if (col)
        sum++;
    }
  }
  return sum;
}

void updateKnots(std::vector<point> *knots) {
  for (size_t i = 0; i < knots->size() - 1; i++) {
    adjustKnot(&knots->at(i), &knots->at(i + 1));
  }
}

int main() {
  // std::ifstream file("../test.txt");
  // std::ifstream file("../test2.txt");
  std::ifstream file("../input.txt");

  if (!file) {
    std::cerr << "Cannot find the file." << std::endl;
  }

  std::vector<char> directions;
  std::vector<uint8_t> steps;
  std::string line;
  while (std::getline(file, line)) {
    std::istringstream ss(line);
    char direction;
    uint32_t number;
    ss >> direction;
    ss >> number;

    directions.push_back(direction);
    steps.push_back(number);
  }

  int min_width = 0, max_width = 0, min_height = 0, max_height = 0;
  int x_pos = 0, y_pos = 0;

  for (size_t i = 0; i < directions.size(); i++) {
    if (directions.at(i) == 'R') {
      y_pos += steps.at(i);
    }
    if (directions.at(i) == 'L') {
      y_pos -= steps.at(i);
    }
    if (directions.at(i) == 'U') {
      x_pos += steps.at(i);
    }
    if (directions.at(i) == 'D') {
      x_pos -= steps.at(i);
    }

    if (y_pos > max_width)
      max_width = y_pos;
    if (y_pos < min_width)
      min_width = y_pos;
    if (x_pos > max_height)
      max_height = x_pos;
    if (x_pos < min_height)
      min_height = x_pos;
  }

  const int width = max_width - min_width;
  const int height = max_height - min_height;

  std::vector<bool> row;
  std::vector<std::vector<bool>> field;

  for (auto i = 0; i < width + 1; i++) {
    row.push_back(false);
  }

  for (auto i = 0; i < height + 1; i++) {
    field.push_back(row);
  }

  T.y = -1 * min_width;
  T.x = -1 * min_height;
  std::vector<point> knots;

  for (auto i = 0; i < NUMBER_OF_KNOTS; i++) {
    knots.push_back(T);
  }

  for (auto i = 0; i < directions.size(); i++) {
    int y_offset = 0;
    int x_offset = 0;
    switch (directions.at(i)) {
    case 'R':
      y_offset++;
      break;
    case 'L':
      y_offset--;
      break;
    case 'U':
      x_offset++;
      break;
    case 'D':
      x_offset--;
      break;
    }
    for (auto step = 0; step < steps.at(i); step++) {
      knots.front().y += y_offset;
      knots.front().x += x_offset;
      updateKnots(&knots);
      updateField(&field, &knots);
    }
  }

  std::cout << "visits " << countVisits(field) << std::endl;
}
