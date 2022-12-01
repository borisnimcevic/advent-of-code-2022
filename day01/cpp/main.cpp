#include <fstream>
#include <iostream>

int main() {
  const std::ifstream file("../input.txt");

  if (!file) {
    std::cerr << "Cannot find the file." << std::endl;
  }

  std::string line;
  int sum = 0, max1 = 0, max2 = 0, max3 = 0;
  while (std::getline(file, line)) {
    if (line == "") {
      if (sum > max1) {
        max3 = max2;
        max2 = max1;
        max1 = sum;
      } else if (sum > max2) {
        max3 = max2;
        max2 = sum;
      } else if (sum > max3) {
        max3 = sum;
      }
      sum = 0;
    } else {
      sum += std::stoi(line);
    }
  }
  std::cout << max1 << std::endl;
  std::cout << max1 + max2 + max3 << std::endl;
}
