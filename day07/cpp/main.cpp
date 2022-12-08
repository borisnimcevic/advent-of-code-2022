#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

class Dir {
public:
  Dir *parent;
  std::string name;
  std::vector<Dir *> children;
  std::vector<uint64_t> values;

  Dir(std::string name1) { name = name1; }
};

void addChild(Dir **head_ref, std::string dir_name) {
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

void goToChild(Dir *current, std::string word) {
  // std::cout << "Going to child " << word << std::endl;
  for (auto child : current->children) {
    if (child->name == word) {
      current = child;
      return;
    }
  }
}

void printDFS(Dir *dir, int indent) {
  if (dir->children.size() == 0) {
    for (int i = 0; i < indent; i++) {
      std::cout << " ";
    }
    std::cout << dir->name << std::endl;
    return;
  }

  for (auto child : dir->children) {
    printDFS(child, indent + 1);
  }

  for (int i = 0; i < indent; i++) {
    std::cout << " ";
  }
  std::cout << dir->name << std::endl;
}

void printDirs(Dir *head) {
  while (head->parent != nullptr) {
    head = head->parent;
  }

  int indent = 0;
  printDFS(head, indent);
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
              addChild(&current, word);
            } else {
              goToChild(current, word);
            }
          }
        }
      }

      // std::cout << word << std::endl;
    }
  }
  printDirs(current);
}
