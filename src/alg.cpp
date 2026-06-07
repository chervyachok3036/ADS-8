// Copyright 2021 NNTU-CS
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "bst.h"

static bool IsEnglishLetter(char ch) {
  return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

static char ToLower(char ch) {
  if (ch >= 'A' && ch <= 'Z') return ch + ('a' - 'A');
  return ch;
}

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "File error: " << filename << "\n";
    return;
  }

  std::string word;
  char ch;

  while (file.get(ch)) {
    if (IsEnglishLetter(ch)) {
      word += ToLower(ch);
    } else if (!word.empty()) {
      tree.insert(word);
      word.clear();
    }
  }

  if (!word.empty()) {
    tree.insert(word);
  }
}

static bool ByFreqDesc(const std::pair<std::string, int>& a,
                       const std::pair<std::string, int>& b) {
  return a.second > b.second;
}

void printFreq(BST<std::string>& tree) {
  std::vector<std::pair<std::string, int>> items;
  tree.collectInfo(items);
  std::sort(items.begin(), items.end(), ByFreqDesc);

  std::ofstream out("result/freq.txt");

  for (const auto& entry : items) {
    std::cout << entry.first << " " << entry.second << "\n";
    if (out.is_open()) {
      out << entry.first << " " << entry.second << "\n";
    }
  }
}
