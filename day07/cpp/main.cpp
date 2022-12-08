#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <tuple>
#include <vector>

std::vector<uint64_t> sizes;
std::vector<uint64_t> all_sizes;
const uint32_t limit = 100000;
const uint64_t total_space = 70000000;
const uint64_t needed_space = 30000000;

class Dir {
public:
  Dir *parent;
  std::string name;
  std::vector<Dir *> children;
  std::vector<std::tuple<std::string, uint64_t>> files;

  Dir(std::string name1) { name = name1; }
};

void addChild(Dir *current, std::string dir_name) {
  // std::cout << "Adding child " << dir_name << " to " << current->name <<
  // std::endl;
  Dir *new_dir = new Dir(dir_name);
  new_dir->parent = current;
  current->children.push_back(new_dir);
}

void addAndGoToChild(Dir **head_ref, std::string dir_name) {
  // std::cout << "Adding child " << dir_name << std::endl;
  Dir *new_dir = new Dir(dir_name);

  Dir *last = *head_ref;

  if (*head_ref == nullptr) {
    new_dir->parent = nullptr;
    *head_ref = new_dir;
    return;
  }

  last->children.push_back(new_dir);
  new_dir->parent = last;
  *head_ref = new_dir;
  return;
}

bool dirExists(Dir *current, std::string word) {
  // std::cout << "Does it exist ? " << word << std::endl;
  if (current == nullptr) {
    return false;
  }

  for (auto child : current->children) {
    if (child->name == word) {
      return true;
    }
  }
  return false;
}

Dir *goToChild(Dir *current, std::string word) {
  // std::cout << "Going to child " << word << std::endl;
  for (auto child : current->children) {
    if (child->name == word) {
      // current = child;
      return child;
    }
  }
  return nullptr;
}

void printFiles(Dir *dir, int indent) {
  for (auto file : dir->files) {
    for (int i = 0; i < indent; i++) {
      std::cout << " ";
    }
    std::cout << std::get<1>(file) << " " << std::get<0>(file) << std::endl;
  }
}
void printDFS(Dir *dir, int indent) {
  if (dir->children.size() == 0) {
    for (int i = 0; i < indent; i++) {
      std::cout << " ";
    }
    std::cout << dir->name << ":" << std::endl;
    printFiles(dir, indent);
    return;
  }

  for (auto child : dir->children) {
    printDFS(child, indent + 1);
  }

  for (int i = 0; i < indent; i++) {
    std::cout << " ";
  }
  std::cout << dir->name << ":" << std::endl;
  printFiles(dir, indent);
}

void printDirs(Dir *head) {
  while (head->parent != nullptr) {
    head = head->parent;
  }

  int indent = 0;
  printDFS(head, indent);
}

uint64_t smallFiles(Dir *dir) {
  if (dir->children.size() == 0) {
    uint64_t sum = 0;

    for (auto file : dir->files) {
      sum += std::get<1>(file);
    }

    if (sum <= limit) {
      sizes.push_back(sum);
    }
    all_sizes.push_back(sum);
    return sum;
  }

  uint64_t sum = 0;
  for (auto child : dir->children) {
    sum += smallFiles(child);
  }
  for (auto file : dir->files) {
    sum += std::get<1>(file);
  }
  if (sum <= limit) {
    sizes.push_back(sum);
  }

  all_sizes.push_back(sum);
  return sum;
}

uint64_t sumSizes(Dir *head) {
  while (head->parent != nullptr) {
    head = head->parent;
  }

  return smallFiles(head);
}
int main() {
  // std::ifstream file("../test.txt");
  std::ifstream file("../input.txt");

  if (!file) {
    std::cerr << "Cannot find the file." << std::endl;
  }

  Dir *current = nullptr;
  std::string line;
  while (std::getline(file, line)) {

    std::istringstream ss(line);
    std::string word;

    while (ss >> word) {

      if (word == "$") {
        ss >> word;
        if (word == "cd") {
          ss >> word;
          // std::cout << "change dir to " << word << std::endl;
          if (word == "..") {
            current = current->parent;
          } else {
            if (!dirExists(current, word)) {
              addAndGoToChild(&current, word);
            } else {
              current = goToChild(current, word);
            }
          }
        }
      }

      else if (word == "dir") {
        ss >> word;
        if (!dirExists(current, word)) {
          addChild(current, word);
        }
      }

      else {
        uint64_t temp_num = std::stoi(word);
        ss >> word;
        std::tuple<std::string, uint64_t> temp_tuple;
        temp_tuple = std::make_tuple(word, temp_num);
        current->files.push_back(temp_tuple);
      }
    }
  }
  // printDirs(current);
  uint64_t current_space = sumSizes(current);
  std::cout << "current_space " << current_space << std::endl;
  uint64_t missing = needed_space - (total_space - current_space);
  std::cout << "missing " << missing << std::endl;
  // uint64_t sum = 0;
  // for (auto num : sizes) {
  //   sum += num;
  // }
  // std::cout << sum << std::endl;
  sort(all_sizes.begin(), all_sizes.end());
  for (auto num : all_sizes) {
    if (num >= missing) {
      std::cout << "to delete " <<  num << std::endl;
      break;
    }
  }
}
