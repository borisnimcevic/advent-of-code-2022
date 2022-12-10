#include <fstream>
#include <iostream>
#include <sstream>

int main() {
  // std::ifstream file("../test.txt");
  std::ifstream file("../input.txt");

  if (!file) {
    std::cerr << "Cannot find the file." << std::endl;
  }

  std::string line;
  while (std::getline(file, line)) {
    std::istringstream ss(line);
    std::string word;
    while (ss >> word) {
    }
  }
  std::cout << "Hello world" << std::endl;
}
