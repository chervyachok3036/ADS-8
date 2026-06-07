// Copyright 2021 NNTU-CS
#include "bst.h"

#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cerr << "File error: " << filename << "\n";
    return;
  }

  std::string word;
  int ch;

  while ((ch = file.get()) != EOF) {
    if (std::isalpha(ch) && static_cast<unsigned char>(ch) < 128) {
      word += static_cast<char>(std::tolower(ch));
    } else if (!word.empty()) {
      tree.Insert(word);
      word.clear();
    }
  }

  if (!word.empty()) {
    tree.Insert(word);
  }
}

void printFreq(BST<std::string>& tree) {
  std::vector<BST<std::string>::Entry> entries = tree.GetFreqSorted();

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
