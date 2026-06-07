// Copyright 2021 NNTU-CS
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cerr << "File error: " << filename << "\n";
    return;
  }

  std::string line;
  while (std::getline(file, line)) {
    if (line.find("*** START OF THE PROJECT GUTENBERG EBOOK") !=
        std::string::npos) {
      break;
    }
  }

  std::string word;
  char ch;

  while (file.get(ch)) {
    unsigned char uch = static_cast<unsigned char>(ch);
    if (std::isalpha(uch) && uch < 128) {
      word += static_cast<char>(std::tolower(uch));
    } else if (!word.empty()) {
      tree.insert(word);
      word.clear();
    }
  }

  if (!word.empty()) {
    tree.insert(word);
  }
}

void printFreq(BST<std::string>& tree) {
  std::vector<BST<std::string>::Entry> entries = tree.getFreqSorted();

  for (const auto& entry : entries) {
    std::cout << entry.value << " " << entry.count << "\n";
  }

  std::ofstream out("result/freq.txt");
  if (!out) {
    std::cerr << "Warning: could not write result/freq.txt\n";
    return;
  }

  for (const auto& entry : entries) {
    out << entry.value << " " << entry.count << "\n";
  }
}
